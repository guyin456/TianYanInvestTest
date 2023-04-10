#include "MarketProcessing.h"

int main() {
    char instrument[20] = "symbol_A";
    std::string code = "symbol_B";
    double askPrice[5] = {1.1, 1.2, 1.3, 1.4, 1.5};
    uint64_t askVolume[5] = {1000, 1000, 1000, 1000, 1000};
    double bidPrice[5] = {1.0, 0.9, 0.8, 0.7, 0.6};
    uint64_t bidVolume[5] = {1000, 1000, 1000, 1000, 1000};
    const MarketDataA A(instrument, askPrice, askVolume, bidPrice, bidVolume);
    const MarketDataB B(code, askPrice, askVolume, bidPrice, bidVolume);
    onQuoteA(A);
    onQuoteB(B);
}
