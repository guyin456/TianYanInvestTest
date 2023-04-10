#include "ReportProcessing.h"

int main() {
    Api api;
    ModuleA moduleA(&api);
    ModuleB moduleB(&api);
    ModuleC moduleC(&api);

    // 从市场收到订单的回报
    OrderRtn rtn;
    api.onRtnOrder(rtn);

    return 0;
}
