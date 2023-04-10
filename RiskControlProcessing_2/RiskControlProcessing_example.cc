#include "RiskControlProcessing.h"
#include <vector>

int main () {
    Risk risk;
    // 初始化风控关系
    risk.init();
    
    vector<Order> orders;

    Order order1("123456.SH", 1);
    orders.push_back(order1);
    Order order2("12345.SH", 1);
    orders.push_back(order2);
    Order order3("12345.SH", 2);
    orders.push_back(order3);
    Order order4("12345.SH", 3);
    orders.push_back(order4);
    // 已经添加风控不可交易123456.SH股票
    for (auto order : orders) {
        if ( risk.check(order) ) {
            std::cout << "产品 " << order.accountId << " 中交易股票 " <<  order.instrumentId << " 风控检测成功" << endl;
        } else {
            std::cout << "产品 " << order.accountId << " 中交易股票 " <<  order.instrumentId << " 风控检测失败" << endl;
        }
    }

}
