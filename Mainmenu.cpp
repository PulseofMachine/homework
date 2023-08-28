#include <iostream>
#include "myfunc.h"

int main()
{
    Login();
    int Chioce;
    while ((Chioce = GetChoice()) != 0)
    {
        switch (Chioce)
        {
        case 1:
            std::cout << "-- 开始录入电影放映信息 --" << std::endl;
            EnterMovieInfo();
            break;
        case 2:
            std::cout << "-- 进入购票管理 --" << std::endl;
            BuyTicket();
            break;
        case 3:
            std::cout << "-- 进入退票管理 --" << std::endl;
            Refund();
            break;
        case 4:
            std::cout << "-- 开始修改电影放映信息 --" << std::endl;
            ChangeMovieInfo();
            break;
        case 5:
            std::cout << "-- 开始信息输出 --" << std::endl;
            ShowAllInfo();
            break;
        case 6:
            std::cout << "-- 进入查询管理 --" << std::endl;
            Inquire();
            break;
        case 7:
            std::cout << "-- 进入统计管理 --" << std::endl;
            Statistic();
            break;
        case 8:
            std::cout << "-- 正在输出报表 --" << std::endl;
            break;
        case 9:
            std::cout << "-- 开始密码修改 --" << std::endl;
            ChangePassword();
            break;
        }
    }
    std::cout << "--系统已退出--" << std::endl;
    return 0;
}
