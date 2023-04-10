set -x
export PATH=/home/distcc/clang-11.1.0/bin/:$PATH
cd MarketProcessing_1
clang++ -std=c++11 -c MarketProcessing.cc -o MarketProcessing.o
ar rcs libMarketProcessing.a MarketProcessing.o
clang++ -std=c++11 MarketProcessing_example.cc -L./ -lMarketProcessing -o MarketProcessing_example
cd -

cd RiskControlProcessing_2
clang++ -std=c++11 -c RiskControlProcessing.cc -o RiskControlProcessing.o
ar rcs libRiskControlProcessing.a RiskControlProcessing.o
clang++ -std=c++11 RiskControlProcessing_example.cc -L./ -lRiskControlProcessing -o RiskControlProcessing_example
cd -

cd ReportProcessing_3
clang++ -std=c++11 -c ReportProcessing.cc -o ReportProcessing.o
ar rcs libReportProcessing.a ReportProcessing.o
clang++ -std=c++11 ReportProcessing_example.cc -L./ -lReportProcessing  -o ReportProcessing_example
cd -

cd ReturnTriggerProcessing_4
clang++ -std=c++11 -c ReturnTriggerProcessing.cc -o ReturnTriggerProcessing.o
ar rcs libReturnTriggerProcessing.a ReturnTriggerProcessing.o
clang++ -std=c++11 ReturnTriggerProcessing_example.cc -L./ -lReturnTriggerProcessing -pthread -o ReturnTriggerProcessing_example
cd -
