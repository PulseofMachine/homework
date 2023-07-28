#include <windows.h>
#include <iostream>
#include <string>

long long int DateNow()
{
    SYSTEMTIME time;
    GetLocalTime(&time);
    long long int Date;
    Date = time.wYear * 10000 + time.wMonth * 100 + time.wDay;
    return Date;
}

long long int TimeNow()
{
    SYSTEMTIME time;
    GetLocalTime(&time);
    long long int Time;
    Time = time.wHour * 100 + time.wMinute;
    return Time;
}