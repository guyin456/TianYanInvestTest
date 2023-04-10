#include <vector>
#include "ReturnTriggerProcessing.h"
int main()
{
    Strategy s(true, 10); // 内部报单
    vector<MarketData> MarketDatas;
    for (int i=0; i<1000; i++) {
        MarketData md(i, i);
        s.onMarketData(md);
    }
    while(1) {}

    return 0;
}
