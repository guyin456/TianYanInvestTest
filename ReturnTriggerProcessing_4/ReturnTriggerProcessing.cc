#include "ReturnTriggerProcessing.h"

void Strategy::onMarketData(const MarketData& md)
{
    std::unique_lock<std::mutex> lock(m_Lock);
    Order order(md.price, md.volume);
    // 获取策略内部数据，并结合行情做一些计算
    // .......
    if (m_orderInternal)
    {
        sendOrderInternal(order);
    }
    else
    {
        sendOrderExternal(order);
    }
}

void Strategy::ProcessOrder(const Order& order) {
    // 报单处理
    std::cout << "处理报单 id: " << order.orderID << " price : " << order.price << " volume: " << order.volume << std::endl;
    // 认为订单已成交，请完成回报触发逻辑。
    onRtnOrder(OrderRtn(order.volume, false));
}

void Strategy::sendOrderInternal(const Order& order)
{
    // 报到内部程序
    m_ThreadPool->submit([this, order](){ProcessOrder(order);});
}

void Strategy::sendOrderExternal(const Order& order)
{
    // 报到外部程序
    // ....
}

void Strategy::onRtnOrder(const OrderRtn& rtn)
{
    std::unique_lock<std::mutex> lock(m_Lock);
    // 仓位更新，log打印，策略状态维护等
    // ....
}
