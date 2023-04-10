#include "MarketProcessing.h"

MarketDataA::MarketDataA(char instrument[20], double askPrice[5], uint64_t askVolume[5], double bidPrice[5], uint64_t bidVolume[5]) {
    strcpy(instrumentId, instrument);
    askPrice1 = askPrice[0];
    askPrice2 = askPrice[1];
    askPrice3 = askPrice[2];
    askPrice4 = askPrice[3];
    askPrice5 = askPrice[4];
    askVolume1 = askVolume[0];
    askVolume2 = askVolume[1];
    askVolume3 = askVolume[2];
    askVolume4 = askVolume[3];
    askVolume5 = askVolume[4];
    bidPrice1 = bidPrice[0];
    bidPrice2 = bidPrice[1];
    bidPrice3 = bidPrice[2];
    bidPrice4 = bidPrice[3];
    bidPrice5 = bidPrice[4];
    bidVolume1 = bidVolume[0];
    bidVolume2 = bidVolume[1];
    bidVolume3 = bidVolume[2];
    bidVolume4 = bidVolume[3];
    bidVolume5 = bidVolume[4];
}

double MarketDataA::getMidPrice () const{
    return (askPrice1 + bidPrice1) / 2;
}

std::string MarketDataA::getSymbol () const{
    return std::string(instrumentId);
}

MarketDataB::MarketDataB(std::string code,  double ask_price[5], uint64_t ask_volume[5], double bid_price[5], uint64_t bid_volume[5]): code(code) {
    for(int i = 0; i<5; i++) {
        askPrice[i] = ask_price[i];
        askVolume[i] = ask_volume[i];
        bidPrice[i] = bid_price[i];
        bidVolume[i] = bid_volume[i];
    }
}

double MarketDataB::getMidPrice () const{
    return (askPrice[0] + bidPrice[0]) / 2;
}

std::string MarketDataB::getSymbol () const{
    return code;
}

void printMidPrice(const MarketData* M) {
    std::cout << "symbol: " << M->getSymbol() << " , mid price: " << M->getMidPrice() << std::endl;
}

void onQuoteA(const MarketDataA& quote)
{
    printMidPrice(&quote);
}

void onQuoteB(const MarketDataB& quote)
{
    printMidPrice(&quote);
}
