#pragma once
#include <iostream>
#include <string.h>

class MarketData {
    public:
        virtual double getMidPrice () const = 0;
        virtual std::string getSymbol () const = 0;
        virtual ~MarketData() {}
};

class MarketDataA : public MarketData {
    char instrumentId[20];  //股票代码
    double askPrice1;       //申卖价一
    uint64_t askVolume1;    //申卖量一
    double bidPrice1;       //申买价一
    uint64_t bidVolume1;    //申买量一
    double askPrice2;       //申卖价二
    uint64_t askVolume2;    //申卖量二
    double bidPrice2;       //申买价二
    uint64_t bidVolume2;    //申买量二
    double askPrice3;       //申卖价三
    uint64_t askVolume3;    //申卖量三
    double bidPrice3;       //申买价三
    uint64_t bidVolume3;    //申买量三
    double askPrice4;       //申卖价四
    uint64_t askVolume4;    //申卖量四
    double bidPrice4;       //申买价四
    uint64_t bidVolume4;    //申买量四
    double askPrice5;       //申卖价五
    uint64_t askVolume5;    //申卖量五
    double bidPrice5;       //申买价五
    uint64_t bidVolume5;    //申买量五
    // 其余字段
    // .......
    public:
        MarketDataA(char instrument[20], double askPrice[5], uint64_t askVolume[5], double bidPrice[5], uint64_t bidVolume[5]);

        double getMidPrice () const;

        std::string getSymbol () const;

        ~MarketDataA(){}
};

class MarketDataB : public MarketData {
    std::string code;       //股票代码
    double askPrice[5];     //申卖价
    uint64_t askVolume[5];  //申卖量
    double bidPrice[5];     //申买价
    uint64_t bidVolume[5];  //申买量
    // 其余字段
    // .......
    public:
        MarketDataB(std::string code,  double ask_price[5], uint64_t ask_volume[5], double bid_price[5], uint64_t bid_volume[5]);

        double getMidPrice () const;

        std::string getSymbol () const;

        ~MarketDataB(){}
};

void printMidPrice(const MarketData* M);

void onQuoteA(const MarketDataA& quote);

void onQuoteB(const MarketDataB& quote);
