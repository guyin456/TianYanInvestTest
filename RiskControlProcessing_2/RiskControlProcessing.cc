#include "RiskControlProcessing.h"
#include <assert.h>
using namespace std;

// 为产品添加风控策略
void Product::addRiskStrategy(shared_ptr<RiskStrategy> r) {
    riskStrategy.emplace(r);
}

// 为产品删除风控策略
void Product::deleteRiskStrategy(shared_ptr<RiskStrategy> r) {
    riskStrategy.erase(r);
}

// 每个产品各自的风控检测
bool Product::check(const Order& order) {
    for (auto it = riskStrategy.begin(); it != riskStrategy.end(); it++) {
        if (!it->get()->check(order, this)) {
            return false;
        }
    }
    return true;
}

// 如果风控通过，根据报单更新产品内容
void Product::updateOrder(const Order& order) {
}


// 具体风控策略check逻辑
bool RiskStrategy_A::check(const Order& order, Product* product) {
    // 创业板股票市值不超过30%，每个股票市值占产品总市值比重不超过5%
    // TODO: 实现具体逻辑
    return true;
}

bool RiskStrategy_B::check(const Order& order, Product* product) {
    // 不能持有创业板股票，撤单率不能大于50%
    // TODO: 实现具体逻辑
    return true;
}

bool RiskStrategy_C::check(const Order& order, Product* product) {
    // 每个股票市值占产品总市值比重不超过10%
    // TODO: 实现具体逻辑
    return true;
}

bool RiskStrategy_D::check(const Order& order, Product* product) {
    // 禁止交易指定的股票
    // TODO: 实现具体逻辑
    if (order.instrumentId == forbidenId) {
        std::cerr << "风控检测生效，无法交易禁止股票 " << forbidenId << endl;
        return false;
    }
    return true;
}


void Risk::init() {
    // 初始化全部风控策略
    std::string strategy_name_a = "RiskStrategy_A";
    std::shared_ptr<RiskStrategy> A = std::make_shared<RiskStrategy_A>(50, 50);
    riskStrategyNames_.emplace(strategy_name_a, A);
    std::string strategy_name_b = "RiskStrategy_B";
    std::shared_ptr<RiskStrategy> B = std::make_shared<RiskStrategy_B>(50);
    riskStrategyNames_.emplace(strategy_name_b, B);
    std::string strategy_name_c = "RiskStrategy_C";
    std::shared_ptr<RiskStrategy> C = std::make_shared<RiskStrategy_C>(50);
    riskStrategyNames_.emplace(strategy_name_c, C);
    std::string strategy_name_d = "RiskStrategy_D";
    std::shared_ptr<RiskStrategy> D = std::make_shared<RiskStrategy_D>("123456.SH");
    riskStrategyNames_.emplace(strategy_name_d, D);
    std::string strategy_name_d2 = "RiskStrategy_D2";
    std::shared_ptr<RiskStrategy> D2 = std::make_shared<RiskStrategy_D>("12345.SH");
    riskStrategyNames_.emplace(strategy_name_d2, D2);

    // 初始化全部product
    uint64_t account_id1 = 1;
    std::shared_ptr<Product> product_a = std::make_shared<Product>(account_id1);
    products_.emplace(account_id1, product_a);
    uint64_t account_id2 = 2;
    std::shared_ptr<Product> product_b = std::make_shared<Product>(account_id2);
    products_.emplace(account_id2, product_b);
    uint64_t account_id3 = 3;
    std::shared_ptr<Product> product_c = std::make_shared<Product>(account_id3);
    products_.emplace(account_id3, product_c);

    // 初始化每个产品对应风控策略
    addRiskStrategy(account_id1, strategy_name_a);
    addRiskStrategy(account_id2, strategy_name_b);
    addRiskStrategy(account_id3, strategy_name_c);
    addRiskStrategy(account_id3, strategy_name_d2);

    // 初始化全量风控策略
    addRiskStrategy(strategy_name_d);
}


// 进行风控策略检测
bool Risk::check(const Order& order) {
    auto it = products_.find(order.accountId);
    assert(it != products_.end());
    // 执行该产品对应的风控检测
    if (!it->second->check(order)) {
        return false;
    }
    // 执行全量产品的风控检测
    for (auto it_ = riskStrategy_.begin(); it_ != riskStrategy_.end(); it_++) {
        if(!it_->get()->check(order, it->second.get())) {
            return false;
        }
    }
    return true;
}


// 添加产品信息
void Risk::addProduct(shared_ptr<Product> product) {
    uint64_t accountId = product->getAccountId();
    products_.emplace(accountId, product);

}
// 添加全量风控策略
void Risk::addRiskStrategy(std::string strategy_name) {
    auto it = riskStrategyNames_.find(strategy_name);
    assert(it != riskStrategyNames_.end());
    riskStrategy_.emplace(it->second);
}

// 为某一产品添加风控策略
void Risk::addRiskStrategy(uint64_t accountId, string strategy_name) {
    auto risk_it = riskStrategyNames_.find(strategy_name);
    assert(risk_it != riskStrategyNames_.end());
    auto product_it = products_.find(accountId);
    assert(product_it != products_.end());
    product_it->second->addRiskStrategy(risk_it->second);
}

// 删除全量风控策略
void Risk::deleteRiskStrategy(std::string strategy_name) {
    auto it = riskStrategyNames_.find(strategy_name);
    assert(it != riskStrategyNames_.end());
    riskStrategy_.erase(it->second);
}

// 删除某一产品的风控策略
void Risk::deleteRiskStrategy(uint64_t accountId, string strategy_name) {
    auto risk_it = riskStrategyNames_.find(strategy_name);
    assert(risk_it != riskStrategyNames_.end());
    auto product_it = products_.find(accountId);
    assert(product_it != products_.end());
    product_it->second->deleteRiskStrategy(risk_it->second);
}
