#pragma once
#include <windows.h>
#include <pdh.h>
#include <pdhmsg.h>


class CPUUsage {
    PDH_HQUERY cpuQuery;
    PDH_HCOUNTER cpuTotal;

public:
    CPUUsage() {
        PdhOpenQuery(NULL, 0, &cpuQuery);
        PdhAddEnglishCounter(cpuQuery, L"\\Processor(_Total)\\% Processor Time", 0, &cpuTotal); // Use wide string literal (L"")
        PdhCollectQueryData(cpuQuery);
    }

    double GetCPUPercentage() {
        PdhCollectQueryData(cpuQuery);
        Sleep(100);  // wait for a sample
        PDH_FMT_COUNTERVALUE counterVal;

        PdhCollectQueryData(cpuQuery);
        PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);

        return counterVal.doubleValue;
    }
};
