#include <iostream>
#include "ReportProcessing.h"
using namespace std;

// 定义具体的被观察者
int Api::attach(const function<void()> observer) {
    observers.emplace(++observerId, observer);
    return observerId;
}

void Api::detach(int observerId) {
    observers.erase(observerId);
}

void Api::notify() {
    for (auto it = observers.begin(); it != observers.end(); it++) {
        it->second();
    }
}

// 从市场收到订单的回报
void Api::onRtnOrder(const OrderRtn& rtn) {
    // 把回报发送给其他模块
    notify();
}

void ModuleA::update() {
    // 处理回报
    std::cout << "Module A update" << std::endl;
}

void ModuleB::update() {
    // 处理回报
    std::cout << "Module B update" << std::endl;
}

void ModuleC::update() {
    // 处理回报
    std::cout << "Module C update" << std::endl;
}


