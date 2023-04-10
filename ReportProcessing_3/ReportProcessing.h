#pragma once
#include <iostream>
#include <algorithm>
#include <functional>
#include <atomic>
#include <map>

using namespace std;

struct OrderRtn {
    int index;
};

// 定义被观察者接口
class Subject {
public:
    virtual int attach(function<void()> observer) = 0;
    virtual void detach(int observerId) = 0;
    virtual void notify() = 0;
};

// 定义具体的被观察者
class Api : public Subject {
public:
    Api() { observerId = 0; }

    int attach(function<void()> observer) override;

    void detach(int obseverId) override;

    void notify() override;

    // 从市场收到订单的回报
    void onRtnOrder(const OrderRtn& rtn);

private:
    map<int, function<void()>> observers;
    std::atomic<int> observerId;
};

// 定义具体的观察者
class ModuleA {
public:
    ModuleA(Api* api) : api(api) {
        observerId = api->attach([this]() { update(); });
    }

    ~ModuleA() {
        api->detach(observerId);
    }

    // 处理回报
    void update();

private:
    Api* api;
    int observerId;
};

class ModuleB {
public:
    ModuleB(Api* api) : api(api) {
        observerId = api->attach([this]() { update(); });
    }

    ~ModuleB() {
        api->detach(observerId);
    }

    // 处理回报
    void update();

private:
    Api* api;
    int observerId;
};

class ModuleC {
public:
    ModuleC(Api* api) : api(api) {
        observerId = api->attach([this]() { update(); });
    }

    ~ModuleC() {
        api->detach(observerId);
    }

    // 处理回报
    void update();

private:
    Api* api;
    int observerId;
};

