#pragma once
#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>
#include <set>
#include <string.h>
using namespace std;

struct Order
{
    string instrumentId;  //股票代码，如: 111111.SH, 222222.SH
    uint64_t accountId; //报单账户（对应某个产品）
    double price;       //报单价格
    int32_t qty;        //报单数量
    // 其他字段...
    Order(string instrumentid, uint64_t accountid) : instrumentId(instrumentid), accountId(accountid) {}
};


struct Stock {
    string instrumentId; //股票代码
    // 其他字段，表示股票属性
    enum sector {Business, other};
    double currPrice;
    // ...
};

class RiskStrategy;

// 产品类
class Product {
    uint64_t accountId;
    // 该产品所有风控策略
    set<shared_ptr<RiskStrategy>> riskStrategy;
    // 其他字段
    // 每个产品中的各个 股票 -- 持有量
    unordered_map<string, double> stockDetails;
    // ...
    public:
        Product(uint64_t id) { accountId = id;}

        // 为产品添加风控策略
        void addRiskStrategy(shared_ptr<RiskStrategy> r);

        // 为产品添加风控策略
        void deleteRiskStrategy(shared_ptr<RiskStrategy> r);

        // 每个产品各自的风控检测
        bool check(const Order& order) ;

        // 如果风控通过，根据报单更新产品内容
        void updateOrder(const Order& order);

        uint64_t getAccountId() {return accountId;}
};


// 风险检测类, 派生类定义具体check逻辑
class RiskStrategy {
    public:
        virtual bool check(const Order& order, Product* product) = 0;
        virtual ~RiskStrategy() {}
};

class RiskStrategy_A : public RiskStrategy {
    public:
        RiskStrategy_A(double max_business_sector_value_ratio, double max_stock_value_ratio) :
            max_business_sector_value_ratio_(max_business_sector_value_ratio), max_stock_value_ratio_(max_stock_value_ratio) {}

        bool check(const Order& order, Product* product);

        ~RiskStrategy_A() {}
    private:
        double max_business_sector_value_ratio_;
        double max_stock_value_ratio_;
};

class RiskStrategy_B : public RiskStrategy {
    public:
        RiskStrategy_B(double max_cancel_rate) : max_cancel_rate_(max_cancel_rate) {}
        bool check(const Order& order, Product* product);
    private:
        double max_cancel_rate_;
};

class RiskStrategy_C : public RiskStrategy {
    public:
        RiskStrategy_C(double max_stock_value_ratio) : max_stock_value_ratio_(max_stock_value_ratio) {}
        bool check(const Order& order, Product* product);
    private:
        double max_stock_value_ratio_;
};

class RiskStrategy_D : public RiskStrategy {
    public:
        RiskStrategy_D(string forbidenid) {
            forbidenId = forbidenid;
        }
        bool check(const Order& order, Product* product);
    private:
        string forbidenId;
};

class Risk {
    private:
        // accountId --> product
        unordered_map<uint64_t, std::shared_ptr<Product>> products_;
        // 添加的全局product风控策略
        set<shared_ptr<RiskStrategy>> riskStrategy_;
        // 风控名 --> 风控策略指针
        unordered_map<std::string, std::shared_ptr<RiskStrategy>> riskStrategyNames_;

    public:
        Risk() {}
        // 初始化
        void init();
        // 进行风控策略检测
        bool check(const Order& order);
        // 添加产品信息
        void addProduct(shared_ptr<Product> prouct);
        // 添加全量风控策略
        void addRiskStrategy(string strategy_name);
        // 为某一产品添加风控策略
        void addRiskStrategy(uint64_t accountId, string strategy_name);

        // 删除全量风控策略
        void deleteRiskStrategy(string strategy_name);

        // 删除某一产品的风控策略
        void deleteRiskStrategy(uint64_t accountId, string strategy_name);
};
