#include <mutex>
#include <queue>
#include <condition_variable>
#include "ThreadPool.h"

static int ORDERID = 0;
static int RTNORDERID = 0;

struct MarketData {
    double price;
    int volume;
    MarketData(double p, int v):price(p), volume(v) {}
};

struct Order {
    int orderID;
    double price;
    int volume;
    Order(double p, int v):orderID(ORDERID++), price(p), volume(v) {}
};

struct OrderRtn {
    int orderID;
    int filledVolume;
    bool isCancelled;
    OrderRtn(int v, bool c):orderID(RTNORDERID++), filledVolume(v), isCancelled(c) {}
};

class Strategy {
public:
    Strategy(bool orderInternal, int threadNums) : m_orderInternal(orderInternal) {
        // 初始化内部报单线程
        m_ThreadPool = new ThreadPool(threadNums);
        m_ThreadPool->init();
    }

    // 处理行情
    void onMarketData(const MarketData& md);

    // 内部报单
    void sendOrderInternal(const Order& order);

    // 外部报单
    void sendOrderExternal(const Order& order);

    // 报单处理函数
    void ProcessOrder(const Order& order);

    // 回报，反馈订单的状态，如成交或撤单
    void onRtnOrder(const OrderRtn& rtn);

    ~Strategy() {
        std::cout << "Strategy destory";
        m_ThreadPool->shutdown();
        delete(m_ThreadPool);
    }

private:
    bool m_orderInternal;
    std::mutex m_Lock;
    ThreadPool* m_ThreadPool;
};
