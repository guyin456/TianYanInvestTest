#pragma once
#include<iostream>
#include<thread>
#include<mutex>
#include<queue>
#include <functional>
#include <future>
#include <utility>
#include<condition_variable>

using namespace std;

template <typename T>
class SafeQueue {
    private:
        queue<T> m_queue;
        mutex mtx;
        condition_variable condition;

    public:
        SafeQueue() {
        }
        
        bool empty() {
            std::unique_lock<mutex> lock(mtx);
            return m_queue.size();
        }

        size_t size() {
            std::unique_lock<mutex> lock(mtx);
            return m_queue.size();
        }

        void enqueue(const T& t) {
            std::unique_lock<mutex> lock(mtx);
            m_queue.push(t);
            condition.notify_all();
        }

        T dequeue() {
            std::unique_lock<mutex> lock(mtx);
            while(m_queue.size() == 0) {
                condition.wait(lock);
            }
            T front = m_queue.front();
            m_queue.pop();
            return front;
        }

        ~SafeQueue(){}
};

class ThreadPool {
    private:
        bool m_shutdown;
        SafeQueue<std::function<void()>> m_queue;
        std::vector<std::thread> m_threads;
        std::mutex m_conditional_mutex;
        std::condition_variable m_conditional_lock;

        class ThreadWorker {
            private:
                int m_id; // 工作 id
                ThreadPool *m_pool; // 所属线程池
            public:
                ThreadWorker(ThreadPool *pool, const int id): m_pool(pool), m_id(id) {}

                void operator()() {
                    std::function<void()> func;
                    bool dequeued;
                    while(!m_pool->m_shutdown) {
                        std::unique_lock<std::mutex> lock(m_pool->m_conditional_mutex);
                        if (!m_pool->m_queue.empty()) {
                            m_pool->m_conditional_lock.wait(lock);
                        }
                        func = m_pool->m_queue.dequeue();
                        std::cout << "线程id : " << m_id << endl;
                        func();
                    }
                }
        };

    public:
        ThreadPool(int thread_num): m_threads(std::vector<std::thread>(thread_num)), m_shutdown(false) {}

        void init() {
            for(int i = 0; i < m_threads.size(); i++) {
                m_threads[i] = std::thread(ThreadWorker(this, i));
            }
        }

        void shutdown() {
            m_shutdown = true;
            m_conditional_lock.notify_all();
            for (int i = 0; i < m_threads.size(); i++) {
                if(m_threads[i].joinable()) {
                    m_threads[i].join();
                }
            }
        }

        template <typename F, typename ... Args>
        auto submit(F && f, Args && ... args) -> std::future<decltype(f(args...))> {
            std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
            auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
            std::function<void()> warpper_func = [task_ptr] () {
                (*task_ptr)();
            };
            m_queue.enqueue(warpper_func);
            m_conditional_lock.notify_one();
            return task_ptr->get_future();
        }

};
