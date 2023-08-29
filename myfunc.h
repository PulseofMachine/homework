#include <iostream>
#include <string>
#include <stdio.h>
#include "Now.h"
#include <string.h>
#include <iomanip>
#include <windows.h>
#include <vector>

void Login()
{
    std::cout << "                 ___________________________________________" << std::endl;
    std::cout << "                 |                                         |" << std::endl;
    std::cout << "                 |          欢迎使用电影购票系统           |" << std::endl;
    std::cout << "                 |   在使用之前您需要输入账号密码进行登录  |" << std::endl;
    std::cout << "                 |                                         |" << std::endl;
    std::cout << "                 |_________________________________________|" << std::endl;
    std::cout << std ::endl;
AGAIN:
    std::cout << "-- 请输入账号 --" << std::endl;
    char EName[64];
    std::cin >> EName;
    std::cout << "-- 请输入密码 --" << std::endl;
    char EPassword[64];
    std::cin >> EPassword;
    strcat(EName, "\n"); // fgets会吸收\n
    FILE *fPtr;
    if ((fPtr = fopen("Account.txt", "r")) == NULL)
    {
        std::cout << "--! 账号存储文件出现错误 !--" << std::endl;
        exit(0);
    }
    char Name[64];
    char Password[64];
    fgets(Name, 64, fPtr);
    fgets(Password, 64, fPtr);
    fclose(fPtr);
    // std::cout << "Name is" << Name << std::endl;
    // std::cout << "Password is" << Password << std::endl;
    // std::cout << "EName is" << EName << std::endl;
    // std::cout << "EPassword is" << EPassword << std::endl;
    if (strcmp(EName, Name) == 0 && strcmp(EPassword, Password) == 0)
    {
        std::cout << "-- 登录成功 --" << std::endl;
    }
    else
    {
        std::cout << "--! 输入的账号或密码有误 !--" << std::endl;
        std::cout << "-- 是否重新输入（输入“y”重新输入，输入其他退出程序） --" << std::endl;
        std::string choice;
        std::cin >> choice;
        if (choice == "y")
        {
            goto AGAIN;
        }
        else
        {
            std::cout << "-- 系统已退出 --" << std::endl;
            exit(0);
        }
    }
}

void ShowMenu()
{
    std::cout << "                 ___________________________________________" << std::endl;
    std::cout << "                 |                                         |" << std::endl;
    std::cout << "                 |          欢迎使用电影购票系统           |" << std::endl;
    std::cout << "                 |      请输入相应数字以完成对应的操作     |" << std::endl;
    std::cout << "                 |                                         |" << std::endl;
    std::cout << "                 |      -1   录入电影放映信息              |" << std::endl;
    std::cout << "                 |      -2   购票管理                      |" << std::endl;
    std::cout << "                 |      -3   退票管理                      |" << std::endl;
    std::cout << "                 |      -4   修改电影放映信息              |" << std::endl;
    std::cout << "                 |      -5   输出全部电影放映、交易信息    |" << std::endl;
    std::cout << "                 |      -6   查询管理                      |" << std::endl;
    std::cout << "                 |      -7   统计管理                      |" << std::endl;
    std::cout << "                 |      -8   汇总报表                      |" << std::endl;
    std::cout << "                 |      -9   修改密码                      |" << std::endl;
    std::cout << "                 |      -0   退出系统                      |" << std::endl;
    std::cout << "                 |                                         |" << std::endl;
    std::cout << "                 |_________________________________________|" << std::endl;
    std::cout << std ::endl;
    std::cout << "请在下方输入数字以完成对应操作" << std::endl;
}

void Holdon()
{
    std::cout << "-- 将自动返回主页面 --" << std::endl;
    Sleep(3000);
}

int GetChoice()
{
// void EnterMovieInfo();
// void QuitSystem();
// void BuyTicket();
AGAIN:
    ShowMenu();
    int Choice = 0;
    if (!(std::cin >> Choice) || ((Choice != 0) && (Choice != 1) && (Choice != 2) && (Choice != 3) && (Choice != 4) && (Choice != 5) && (Choice != 6) && (Choice != 7) && (Choice != 8) && (Choice != 9)))
    {
        std::cout << "--! 输入错误请重新输入 !--" << std::endl;
        std::cin.clear();
        std::cin.sync();
        goto AGAIN;
    }
    return Choice;
}

struct MovieData
{
    int number;
    char name[10];
    char type[10];
    int duration;
    long long int display_date;
    long long int display_time;
    char room[10];
    int fare;
    int remain;
};

void EnterMovieInfo()
{
    FILE *fPtr;
    struct MovieData EnterInfo = {0, "", "", 0, 0, 0, "", 0, 0};
    if ((fPtr = fopen("movie_base.dat", "ab+")) == NULL)
    {
        std::cout << "--！文件打开出现错误，请检查文件是否正常 !--" << std::endl;
        exit(0);
    }
AGAIN:
    // 请输入要录入的电影放映信息，顺序为[放映编号] [电影名称] [电影类型] [时长] [放映日期] [放映时间] [放映影厅] [票价] [余票]
    while (1)
    {
        int MovieNumber;
        std::cout << "-- 请先输入电影放映编号 --" << std::endl;
        if (!(std::cin >> MovieNumber))
        {
            std::string choice;
            std::cout << "--! 输入的不是放映编号 !--" << std::endl;
            std::cout << "-- 是否重新录入? (按y以确定,按其他键返回主菜单) --" << std::endl;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                break;
            }
        }
        rewind(fPtr);
        int Repeat = 0;
        while ((fread(&EnterInfo, sizeof(struct MovieData), 1, fPtr)) != (int)NULL)
        {
            // std::cout << "Mn is " << MovieNumber << std::endl;
            // std::cout << "EI is " << EnterInfo.number << std::endl;
            // std::cout << EnterInfo.number << ' ' << EnterInfo.name << ' ' << EnterInfo.type << ' ' << EnterInfo.duration << ' ' << EnterInfo.display_date << ' ' << EnterInfo.display_time << ' ' << EnterInfo.room << ' ' << EnterInfo.fare << ' ' << EnterInfo.remain << std::endl;
            if (MovieNumber == EnterInfo.number)
            {
                std::string choice;
                std::cout << "--! 电影放映信息的编号出现相同，不能录入 !--" << std::endl;
                Repeat = 1;
                std::cout << "-- 是否重新录入? (按y以确定,按其他键返回主菜单) --" << std::endl;
                std::cin >> choice;
                // std::cin.clear();
                // std::cin.sync();
                if (choice == "y")
                {
                    goto AGAIN;
                }
                else
                {
                    break;
                }
            }
        }
        if (Repeat == 0)
        {
            EnterInfo.number = MovieNumber;
            std::cout << "-- 请继续输入要录入的电影放映信息，顺序为[电影名称] [电影类型] [时长] [放映日期YYYYMMDD] [放映时间kkmm] [放映影厅] [票价] [余票]" << std::endl;
            std::cin >> EnterInfo.name;
            std::cin >> EnterInfo.type;
            std::cin >> EnterInfo.duration;
            std::cin >> EnterInfo.display_date;
            std::cin >> EnterInfo.display_time;
            std::cin >> EnterInfo.room;
            std::cin >> EnterInfo.fare;
            std::cin >> EnterInfo.remain;
            fseek(fPtr, 0, SEEK_END);
            fwrite(&EnterInfo, sizeof(struct MovieData), 1, fPtr);
            std::cout << "-- 信息录入成功! 是否继续录入? (按y以确定,按其他键返回主菜单) --" << std::endl;
            // std::cout << EnterInfo.number << ' ' << EnterInfo.name << ' ' << EnterInfo.type << ' ' << EnterInfo.duration << ' ' << EnterInfo.display_date << ' ' << EnterInfo.display_time << ' ' << EnterInfo.room << ' ' << EnterInfo.fare << ' ' << EnterInfo.remain << std::endl;
            std::string choice;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                fclose(fPtr); // 加上这个关闭文件，不然会出现这样的bug：按其他键返回主菜单后实际上信息没录进去。
                break;
            }
        }
        fclose(fPtr);
        break;
    }
}

// void QuitSystem()
// {
//     exit(0);
// }

void BuyTicket()
{
    void SaveDeal(const struct MovieData *p, int BuyNumber);
    std::cout << "-- 请输入要购买电影的编号 --" << std::endl;
    int SearchMovie;
    std::cin >> SearchMovie;
    FILE *fPtr;
    struct MovieData EnterInfo = {0, "", "", 0, 0, 0, "", 0, 0};
    if ((fPtr = fopen("movie_base.dat", "rb+")) == NULL)
    {
        std::cout << "--！文件打开出现错误，请检查文件是否正常 !--" << std::endl;
        exit(0);
    }

    int Found = 0;
    int Round = 0;
    rewind(fPtr);
    while ((fread(&EnterInfo, sizeof(struct MovieData), 1, fPtr)) != (int)NULL)
    {
        // std::cout << "sn is " << SearchMovie << std::endl;
        // std::cout << "EI is " << EnterInfo.number << std::endl;
        // std::cout << EnterInfo.number << ' ' << EnterInfo.name << ' ' << EnterInfo.type << ' ' << EnterInfo.duration << ' ' << EnterInfo.display_date << ' ' << EnterInfo.display_time << ' ' << EnterInfo.room << ' ' << EnterInfo.fare << ' ' << EnterInfo.remain << std::endl;

        if (SearchMovie == EnterInfo.number)
        {
            Found = 1;
            int HaveRemain = 0;
            std::cout << "-- 成功找到该电影\"" << EnterInfo.name << "\" -" << std::endl;
            // std::cout << EnterInfo.remain << std::endl;
            // std::cout << EnterInfo.name << std::endl;

            if (EnterInfo.remain > 0)
            {
                HaveRemain = 1;
                int TimeOut = 0;
                long long int datenow = DateNow();
                long long int timenow = TimeNow();
                // std::cout << "Datenow is" << datenow << "Time now is " << timenow << std::endl;
                // std::cout << "displaydate is" << EnterInfo.display_date << "displaytime now is " << EnterInfo.display_time << std::endl;
                // std::cout << EnterInfo.number << ' ' << EnterInfo.name << ' ' << EnterInfo.type << ' ' << EnterInfo.duration << ' ' << EnterInfo.display_date << ' ' << EnterInfo.display_time << ' ' << EnterInfo.room << ' ' << EnterInfo.fare << ' ' << EnterInfo.remain << std::endl;
                if (datenow > EnterInfo.display_date)
                {
                    TimeOut = 1;
                }
                if (datenow == EnterInfo.display_date && timenow > EnterInfo.display_time)
                {
                    TimeOut = 1;
                }
                if (TimeOut == 1)
                {
                    std::cout << "--! 抱歉，该电影已经开始放映/放映结束了 !--" << std::endl;
                    std::cout << "-- 将自动返回主菜单 --" << std::endl;
                    Sleep(2000);
                    break;
                }
                if (TimeOut == 0)
                {

                    std::cout << "-- 检查完成，该电影票可以购买 --" << std::endl;
                AGAIN:
                    std::cout << "-- 请输入要购买的电影票数量 当前电影票剩余量：" << EnterInfo.remain << "张" << std::endl;
                    int BuyNumber = 0;
                    if (!(std::cin >> BuyNumber) || BuyNumber > EnterInfo.remain || BuyNumber <= 0)
                    {
                        std::string choice;
                        std::cout << "--! 输入的不是数字/大于剩余票量/小于等于0 !--" << std::endl;
                        std::cout << "-- 是否重新录入? (按y以确定,按其他键返回主菜单) --" << std::endl;
                        std::cin.clear();
                        std::cin.sync();
                        std::cin >> choice;
                        if (choice == "y")
                        {
                            goto AGAIN;
                        }
                        else
                        {
                            break;
                        }
                    }
                    EnterInfo.remain -= BuyNumber;
                    // std::cout << "-- 当前电影票剩余量：" << EnterInfo.remain << "张" << std::endl;
                    // std::cout << "round is" << Round << std::endl;
                    // std::cout << " Round * sizeof(struct MovieData) is" << Round * sizeof(struct MovieData) << std::endl;
                    // std::cout << EnterInfo.number << ' ' << EnterInfo.name << ' ' << EnterInfo.type << ' ' << EnterInfo.duration << ' ' << EnterInfo.display_date << ' ' << EnterInfo.display_time << ' ' << EnterInfo.room << ' ' << EnterInfo.fare << ' ' << EnterInfo.remain << std::endl;
                    fseek(fPtr, Round * sizeof(struct MovieData), SEEK_SET);
                    fwrite(&EnterInfo, sizeof(struct MovieData), 1, fPtr);
                    SaveDeal(&EnterInfo, BuyNumber);
                    fclose(fPtr);
                    std::cout << "-- 将自动返回主菜单 --" << std::endl;
                    Sleep(2000);
                }
            }
            if (HaveRemain == 0)
            {
                std::cout << "--! 抱歉，该电影票已售空 !--" << std::endl;
            }
        }
        Round++;
    }
    if (Found == 0)
    {
        std::cout << "--! 抱歉，未找到该电影 !--" << std::endl;
        std::cout << "-- 将自动返回主菜单 --" << std::endl;
        Sleep(2000);
    }
}

struct DealData
{
    int number;
    char name[10];
    long long int display_date;
    long long int display_time;
    char room[10];
    long long int deal_date;
    long long int deal_time;
    char dealtype[10];
    double dealprice;
    int dealnumber;
    // 电影编号、电影名称、放映日期、放映时间、放映影厅、交易日期、交易时间、交易类型、交易金额、交易数量。
};

void SaveDeal(const struct MovieData *p, int BuyNumber)
{
    FILE *dfPtr;
    struct DealData DealInfo = {0, "", 0, 0, "", 0, 0, "购票", 0, 0};
    if ((dfPtr = fopen("movie_deal.dat", "ab+")) == NULL)
    {
        std::cout << "--！交易录入出现错误，请检查文件是否正常 !--" << std::endl;
        exit(0);
    }
    DealInfo.number = p->number;
    strcpy(DealInfo.name, p->name);
    DealInfo.display_date = p->display_date;
    DealInfo.display_time = p->display_time;
    strcpy(DealInfo.room, p->room);
    DealInfo.deal_date = DateNow();
    DealInfo.deal_time = TimeNow();
    DealInfo.dealprice = BuyNumber * p->fare;
    DealInfo.dealnumber = BuyNumber;
    std::cout << DealInfo.name << ' ' << DealInfo.display_date << ' ' << DealInfo.display_time << ' ' << DealInfo.room << ' ' << DealInfo.deal_date << ' ' << DealInfo.deal_time << ' ' << DealInfo.dealtype << ' ' << DealInfo.dealprice << std::endl;
    fseek(dfPtr, 0, SEEK_END);
    fwrite(&DealInfo, sizeof(struct DealData), 1, dfPtr);
    fclose(dfPtr);
    std::cout << "-- 购买成功，交易信息录入成功 --" << std::endl;
}

void Refund()
{
    void SaveRefund(const struct DealData *p, int RefundNumber);
    void ChangeInfo(int MovieNumber, int RefundNumber);
AGAIN:
    while (1)
    {
        std::cout << "-- 请输入要退票电影的编号 --" << std::endl;
        int SearchMovie;
        if (!(std::cin >> SearchMovie))
        {
            std::string choice;
            std::cout << "--! 输入的不是电影编号 !--" << std::endl;
            std::cout << "-- 是否重新录入? (按y以确定,按其他键返回主菜单) --" << std::endl;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                break;
            }
        }
        FILE *fPtr;
        struct DealData RefundInfo = {0, "", 0, 0, "", 0, 0, "退票", 0, 0};
        if ((fPtr = fopen("movie_deal.dat", "ab+")) == NULL)
        {
            std::cout << "--！文件打开出现错误，请检查文件是否正常 !--" << std::endl;
            exit(0);
        }
        int Found = 0;
        int Round = 0;
        int pos = 0;
        int total = 0;
        rewind(fPtr);
        while ((fread(&RefundInfo, sizeof(struct DealData), 1, fPtr)) != (int)NULL)
        {
            std::cout << "sn is " << SearchMovie << std::endl;
            std::cout << "EI is " << RefundInfo.number << std::endl;
            // std::cout << RefundInfo.number << ' ' <<  RefundInfo.name << ' ' << EnterInfo.type << ' ' << EnterInfo.duration << ' ' << EnterInfo.display_date << ' ' << EnterInfo.display_time << ' ' << EnterInfo.room << ' ' << EnterInfo.fare << ' ' << EnterInfo.remain << std::endl;

            if (SearchMovie == RefundInfo.number)
            {
                pos = Round;
                Found = 1;
                total += RefundInfo.dealnumber;
            }
            Round++;
        }
        if (Found == 1)
        {
            fseek(fPtr, pos * sizeof(struct DealData), SEEK_SET);
            fread(&RefundInfo, sizeof(struct DealData), 1, fPtr);
            std::cout << "-- 成功找到该电影\"" << RefundInfo.name << "\" -" << std::endl;
            int TimeOut = 0;
            long long int datenow = DateNow();
            long long int timenow = TimeNow();
            // std::cout << "Datenow is" << datenow << "Time now is " << timenow << std::endl;
            // std::cout << "displaydate is" << EnterInfo.display_date << "displaytime now is " << EnterInfo.display_time << std::endl;
            // std::cout << EnterInfo.number << ' ' << EnterInfo.name << ' ' << EnterInfo.type << ' ' << EnterInfo.duration << ' ' << EnterInfo.display_date << ' ' << EnterInfo.display_time << ' ' << EnterInfo.room << ' ' << EnterInfo.fare << ' ' << EnterInfo.remain << std::endl;
            if (datenow > RefundInfo.display_date)
            {
                TimeOut = 1;
            }
            if (datenow == RefundInfo.display_date && timenow > RefundInfo.display_time)
            {
                TimeOut = 1;
            }
            if (TimeOut == 1)
            {
                std::cout << "--! 抱歉，该电影已经开始放映/放映结束了，无法退票 !--" << std::endl;
                std::cout << "-- 将自动返回主菜单 --" << std::endl;
                Sleep(2000);
                fclose(fPtr);
                break;
            }
            if (TimeOut == 0)
            {
                std::cout << "-- 检查完成，该电影可以退票 --" << std::endl;
            AGAIN2:
                std::cout << "-- 请输入要退的电影票数量 当前已购电影票数量：" << total << "张 --" << std::endl;
                int RefundNumber = 0;
                if (!(std::cin >> RefundNumber) || RefundNumber > total || RefundNumber <= 0)
                {
                    std::string choice;
                    std::cout << "--! 输入的不是数字/大于可退票量/小于等于0 !--" << std::endl;
                    std::cout << "-- 是否重新录入? (按y以确定,按其他键返回主菜单) --" << std::endl;
                    std::cin.clear();
                    std::cin.sync();
                    std::cin >> choice;
                    if (choice == "y")
                    {
                        goto AGAIN2;
                    }
                    else
                    {
                        fclose(fPtr);
                        break;
                    }
                }
                SaveRefund(&RefundInfo, RefundNumber);
                ChangeInfo(SearchMovie, RefundNumber);
                fclose(fPtr);
                std::cout << "-- 将自动返回主菜单 --" << std::endl;
                Sleep(2000);
                break;
            }
        }
        if (Found == 0)
        {
            std::string choice;
            std::cout << "--! 抱歉，未找到该电影 !--" << std::endl;
            std::cout << "-- 是否重新录入? (按y以确定,按其他键返回主菜单) --" << std::endl;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                break;
            }
        }
    }
}

void SaveRefund(const struct DealData *p, int RefundNumber)
{
    FILE *rfPtr;
    struct DealData DealInfo = {0, "", 0, 0, "", 0, 0, "退票", 0, 0};
    if ((rfPtr = fopen("movie_deal.dat", "ab+")) == NULL)
    {
        std::cout << "--！交易录入出现错误，请检查文件是否正常 !--" << std::endl;
        exit(0);
    }
    DealInfo.number = p->number;
    strcpy(DealInfo.name, p->name);
    DealInfo.display_date = p->display_date;
    DealInfo.display_time = p->display_time;
    strcpy(DealInfo.room, p->room);
    DealInfo.deal_date = DateNow();
    DealInfo.deal_time = TimeNow();
    DealInfo.dealprice = RefundNumber * (p->dealprice / p->dealnumber) * -1;
    DealInfo.dealnumber = RefundNumber;
    std::cout << DealInfo.name << ' ' << DealInfo.display_date << ' ' << DealInfo.display_time << ' ' << DealInfo.room << ' ' << DealInfo.deal_date << ' ' << DealInfo.deal_time << ' ' << DealInfo.dealtype << ' ' << DealInfo.dealprice << std::endl;
    fseek(rfPtr, 0, SEEK_END);
    fwrite(&DealInfo, sizeof(struct DealData), 1, rfPtr);
    fclose(rfPtr);
    std::cout << "-- 退票成功，退票信息录入成功 --" << std::endl;
}

void ChangeInfo(int MovieNumber, int RefundNumber)
{

    FILE *fPtr;
    struct MovieData EnterInfo = {0, "", "", 0, 0, 0, "", 0, 0};
    if ((fPtr = fopen("movie_base.dat", "rb+")) == NULL)
    {
        std::cout << "--！文件打开出现错误，请检查文件是否正常 !--" << std::endl;
        exit(0);
    }
    // 请输入要录入的电影放映信息，顺序为[放映编号] [电影名称] [电影类型] [时长] [放映日期] [放映时间] [放映影厅] [票价] [余票]
    int Round = 0;
    while ((fread(&EnterInfo, sizeof(struct MovieData), 1, fPtr)) != (int)NULL)
    {
        // std::cout << "Mn is " << MovieNumber << std::endl;
        // std::cout << "EI is " << EnterInfo.number << std::endl;
        if (MovieNumber == EnterInfo.number)
        {
            EnterInfo.remain += RefundNumber;
            fseek(fPtr, Round * sizeof(struct MovieData), SEEK_SET);
            fwrite(&EnterInfo, sizeof(struct MovieData), 1, fPtr);
            fclose(fPtr);
        }
        Round++;
    }
    std::cout << EnterInfo.number << ' ' << EnterInfo.name << ' ' << EnterInfo.type << ' ' << EnterInfo.duration << ' ' << EnterInfo.display_date << ' ' << EnterInfo.display_time << ' ' << EnterInfo.room << ' ' << EnterInfo.fare << ' ' << EnterInfo.remain << std::endl;
}

void ChangeMovieInfo()
{
    void ModifyInfo();
    void DeleteInfo();
    while (1)
    {
        std::cout << "-- 请选择要执行的操作(输入对应数字,输入其他视为返回主菜单) --" << std::endl;
        std::cout << "-1 修改电影放映信息  -2 删除电影放映信息" << std::endl;
        int choice = 0;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            ModifyInfo();
            break;
        case 2:
            DeleteInfo();
            break;
        default:
            break;
        }
        std::cin.clear();
        std::cin.sync();
        break;
    }
}
// 放映编号、电影名称、电影类型、时长、放映日期、放映时间、放映影厅、票价、余票
// 注意：在修改电影放映基本信息时，如果该场次的电影已经被购票了，则电影名、放映
// 日期、时间、类型、票价无法再修改，若没有被购票，可以修改除电影放映编号外的信
// 息；在进行删除操作时若该电影未放映完毕或有购票记录，则无法被删除。
void ModifyInfo()
{
    int CheckBuy(int number);
    FILE *fPtr;
    struct MovieData EnterInfo = {0, "", "", 0, 0, 0, "", 0, 0};
    if ((fPtr = fopen("movie_base.dat", "rb+")) == NULL)
    {
        std::cout << "--！文件打开出现错误，请检查文件是否正常 !--" << std::endl;
        exit(0);
    }
AGAIN:
    // 请输入要录入的电影放映信息，顺序为[放映编号] [电影名称] [电影类型] [时长] [放映日期] [放映时间] [放映影厅] [票价] [余票]
    while (1)
    {

        int MovieNumber;
        std::cout << "-- 请先输入要修改的电影的编号 --" << std::endl;
        if (!(std::cin >> MovieNumber))
        {
            std::string choice;
            std::cout << "--! 输入的不是放映编号 !--" << std::endl;
            std::cout << "-- 是否重新录入? (按y以确定,按其他键返回主菜单) --" << std::endl;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                break;
            }
        }
        rewind(fPtr);
        int Round = 0;
        while ((fread(&EnterInfo, sizeof(struct MovieData), 1, fPtr)) != (int)NULL)
        {
            // std::cout << "Mn is " << MovieNumber << std::endl;
            // std::cout << "EI is " << EnterInfo.number << std::endl;
            // std::cout << EnterInfo.number << ' ' << EnterInfo.name << ' ' << EnterInfo.type << ' ' << EnterInfo.duration << ' ' << EnterInfo.display_date << ' ' << EnterInfo.display_time << ' ' << EnterInfo.room << ' ' << EnterInfo.fare << ' ' << EnterInfo.remain << std::endl;
            if (MovieNumber == EnterInfo.number)
            {
                std::string choice;
                std::cout << "-- 成功找到电影" << EnterInfo.name << " --" << std::endl;
                if (CheckBuy(MovieNumber))
                {
                    std::cout << "-- 该电影还没有被购票，可以修改除电影放映编号外的信息。 --" << std::endl;
                CHANGE:
                    std::cout << "-- 以下是该电影的基本信息 --" << std::endl;
                    std::cout << "电影放映编号： " << EnterInfo.number << ' ' << "电影名称：" << EnterInfo.name << ' ' << "电影类型：" << EnterInfo.type << ' ' << "时长：" << EnterInfo.duration << ' ' << "放映日期：" << EnterInfo.display_date << ' ' << "放映时间：" << EnterInfo.display_time << ' ' << "放映影厅：" << EnterInfo.room << ' ' << "票价：" << EnterInfo.fare << ' ' << "余票：" << EnterInfo.remain << std::endl;
                    std::cout << "-- 请输入相应的数字以进行更改（输入其他内容可以返回主菜单） --" << std::endl;
                    //[放映编号] [电影名称] [电影类型] [时长] [放映日期] [放映时间] [放映影厅] [票价] [余票]
                    std::cout << "-- -1 电影名称 -2 电影类型 -3 时长 -4 放映日期 -5 放映时间 -6 放映影厅 -7 票价 -8 余票 --" << std::endl;
                    int ChangePart;
                    std::cin >> ChangePart;
                    // struct MovieData
                    // {
                    //     int number;
                    //     char name[10];
                    //     char type[10];
                    //     char duration[10];
                    //     long long int display_date;
                    //     long long int display_time;
                    //     char room[10];
                    //     int fare;
                    //     int remain;
                    // };
                    switch (ChangePart)
                    {
                    case 1:
                        std::cout << "-- 正在修改电影名称，请输入 --" << std::endl;
                        char Newname[10];
                        //   std::cin >> Newname;
                        if (!(std::cin >> Newname))
                        {
                            std::cout << "--! 输入的不是正确的修改参数! 将自动返回修改选择页。!--" << std::endl;
                            std::cin.clear();
                            std::cin.sync();
                            goto CHANGE;
                        }
                        strcpy(EnterInfo.name, Newname);
                        fseek(fPtr, Round * sizeof(struct MovieData), SEEK_SET);
                        fwrite(&EnterInfo, sizeof(struct MovieData), 1, fPtr);
                        std::cout << "-- 已完成更改 将返回修改选择页 --" << std::endl;
                        goto CHANGE;
                    case 2:
                        std::cout << "-- 正在修改电影类型，请输入 --" << std::endl;
                        char NewType[10];
                        // std::cin >> NewType;
                        if (!(std::cin >> NewType))
                        {
                            std::cout << "--! 输入的不是正确的修改参数! 将自动返回修改选择页。!--" << std::endl;
                            std::cin.clear();
                            std::cin.sync();
                            goto CHANGE;
                        }
                        strcpy(EnterInfo.type, NewType);
                        fseek(fPtr, Round * sizeof(struct MovieData), SEEK_SET);
                        fwrite(&EnterInfo, sizeof(struct MovieData), 1, fPtr);
                        std::cout << "-- 已完成更改 将返回修改选择页 --" << std::endl;
                        goto CHANGE;
                    case 3:
                        std::cout << "-- 正在修改电影时长，请输入 --" << std::endl;
                        int NewDuration;
                        std::cin >> NewDuration;
                        if (!(std::cin >> NewDuration))
                        {
                            std::cout << "--! 输入的不是正确的修改参数! 将自动返回修改选择页。!--" << std::endl;
                            std::cin.clear();
                            std::cin.sync();
                            goto CHANGE;
                        }
                        EnterInfo.duration = NewDuration;
                        fseek(fPtr, Round * sizeof(struct MovieData), SEEK_SET);
                        fwrite(&EnterInfo, sizeof(struct MovieData), 1, fPtr);
                        std::cout << "-- 已完成更改 将返回修改选择页 --" << std::endl;
                        goto CHANGE;
                    case 4:
                        std::cout << "-- 正在修改放映日期，请输入 --" << std::endl;
                        long long int NewDate;
                        std::cin >> NewDate;
                        if (!(std::cin >> NewDate))
                        {
                            std::cout << "--! 输入的不是正确的修改参数! 将自动返回修改选择页。!--" << std::endl;
                            std::cin.clear();
                            std::cin.sync();
                            goto CHANGE;
                        }
                        EnterInfo.display_date = NewDate;
                        fseek(fPtr, Round * sizeof(struct MovieData), SEEK_SET);
                        fwrite(&EnterInfo, sizeof(struct MovieData), 1, fPtr);
                        std::cout << "-- 已完成更改 将返回修改选择页 --" << std::endl;
                        goto CHANGE;
                    case 5:
                        std::cout << "-- 正在修改放映时间，请输入 --" << std::endl;
                        long long int NewTime;
                        std::cin >> NewTime;
                        if (!(std::cin >> NewTime))
                        {
                            std::cout << "--! 输入的不是正确的修改参数! 将自动返回修改选择页。!--" << std::endl;
                            std::cin.clear();
                            std::cin.sync();
                            goto CHANGE;
                        }
                        EnterInfo.display_time = NewTime;
                        fseek(fPtr, Round * sizeof(struct MovieData), SEEK_SET);
                        fwrite(&EnterInfo, sizeof(struct MovieData), 1, fPtr);
                        std::cout << "-- 已完成更改 将返回修改选择页 --" << std::endl;
                        goto CHANGE;
                    case 6:
                        std::cout << "-- 正在修改放映影厅，请输入 --" << std::endl;
                        char NewRoom[10];
                        //  std::cin >> NewRoom;
                        if (!(std::cin >> NewRoom))
                        {
                            std::cout << "--! 输入的不是正确的修改参数! 将自动返回修改选择页。!--" << std::endl;
                            std::cin.clear();
                            std::cin.sync();
                            goto CHANGE;
                        }
                        strcpy(EnterInfo.room, NewRoom);
                        fseek(fPtr, Round * sizeof(struct MovieData), SEEK_SET);
                        fwrite(&EnterInfo, sizeof(struct MovieData), 1, fPtr);
                        std::cout << "-- 已完成更改 将返回修改选择页 --" << std::endl;
                        goto CHANGE;
                    case 7:
                        std::cout << "-- 正在修改票价，请输入 --" << std::endl;
                        int NewFare;
                        std::cin >> NewFare;
                        if (!(std::cin >> NewFare))
                        {
                            std::cout << "--! 输入的不是正确的修改参数! 将自动返回修改选择页。!--" << std::endl;
                            std::cin.clear();
                            std::cin.sync();
                            goto CHANGE;
                        }
                        EnterInfo.fare = NewFare;
                        fseek(fPtr, Round * sizeof(struct MovieData), SEEK_SET);
                        fwrite(&EnterInfo, sizeof(struct MovieData), 1, fPtr);
                        std::cout << "-- 已完成更改 将返回修改选择页 --" << std::endl;
                        goto CHANGE;
                    case 8:
                        std::cout << "-- 正在修改余票量，请输入 --" << std::endl;
                        int NewRemain;
                        std::cin >> NewRemain;
                        if (!(std::cin >> NewRemain))
                        {
                            std::cout << "--! 输入的不是正确的修改参数! 将自动返回修改选择页。!--" << std::endl;
                            std::cin.clear();
                            std::cin.sync();
                            goto CHANGE;
                        }
                        EnterInfo.remain = NewRemain;
                        fseek(fPtr, Round * sizeof(struct MovieData), SEEK_SET);
                        fwrite(&EnterInfo, sizeof(struct MovieData), 1, fPtr);
                        std::cout << "-- 已完成更改 将返回修改选择页 --" << std::endl;
                        goto CHANGE;
                    default:
                        break;
                    }
                }
                else
                {
                    std::cout << "-- 该场次的电影已经被购票了，电影名、放映日期、时间、类型、票价将无法再修改。 --" << std::endl;
                    //[时长]  [放映影厅]  [余票]
                CHANGE2:
                    std::cout << "-- 以下是该电影的基本信息 --" << std::endl;
                    std::cout << "电影放映编号： " << EnterInfo.number << ' ' << "电影名称：" << EnterInfo.name << ' ' << "电影类型：" << EnterInfo.type << ' ' << "时长：" << EnterInfo.duration << ' ' << "放映日期：" << EnterInfo.display_date << ' ' << "放映时间：" << EnterInfo.display_time << ' ' << "放映影厅：" << EnterInfo.room << ' ' << "票价：" << EnterInfo.fare << ' ' << "余票：" << EnterInfo.remain << std::endl;
                    std::cout << "-- 请输入相应的数字以进行更改（输入其他内容可以返回主菜单） --" << std::endl;
                    //[放映编号] [电影名称] [电影类型] [时长] [放映日期] [放映时间] [放映影厅] [票价] [余票]
                    std::cout << "-- -1 时长 -2 放映影厅 -3 余票 --" << std::endl;
                    int ChangePart;
                    std::cin >> ChangePart;

                    // struct MovieData
                    // {
                    //     int number;
                    //     char name[10];
                    //     char type[10];
                    //     char duration[10];
                    //     long long int display_date;
                    //     long long int display_time;
                    //     char room[10];
                    //     int fare;
                    //     int remain;
                    // };
                    switch (ChangePart)
                    {
                    case 1:
                        std::cout << "-- 正在修改电影时长，请输入 --" << std::endl;
                        int NewDuration;
                        std::cin >> NewDuration;
                        if (!(std::cin >> NewDuration))
                        {
                            std::cout << "--! 输入的不是正确的修改参数! 将自动返回修改选择页。!--" << std::endl;
                            std::cin.clear();
                            std::cin.sync();
                            goto CHANGE2;
                        }
                        EnterInfo.duration = NewDuration;
                        fseek(fPtr, Round * sizeof(struct MovieData), SEEK_SET);
                        fwrite(&EnterInfo, sizeof(struct MovieData), 1, fPtr);
                        std::cout << "-- 已完成更改 将返回修改选择页 --" << std::endl;
                        goto CHANGE2;
                    case 2:
                        std::cout << "-- 正在修改放映影厅，请输入 --" << std::endl;
                        char NewRoom[10];
                        // std::cin >> NewRoom;
                        if (!(std::cin >> NewRoom))
                        {
                            std::cout << "--! 输入的不是正确的修改参数! 将自动返回修改选择页。!--" << std::endl;
                            std::cin.clear();
                            std::cin.sync();
                            goto CHANGE2;
                        }
                        strcpy(EnterInfo.room, NewRoom);
                        fseek(fPtr, Round * sizeof(struct MovieData), SEEK_SET);
                        fwrite(&EnterInfo, sizeof(struct MovieData), 1, fPtr);
                        std::cout << "-- 已完成更改 将返回修改选择页 --" << std::endl;
                        goto CHANGE2;
                    case 3:
                        std::cout << "-- 正在修改余票量，请输入 --" << std::endl;
                        int NewRemain;
                        std::cin >> NewRemain;
                        if (!(std::cin >> NewRemain))
                        {
                            std::cout << "--! 输入的不是正确的修改参数! 将自动返回修改选择页。!--" << std::endl;
                            std::cin.clear();
                            std::cin.sync();
                            goto CHANGE2;
                        }
                        EnterInfo.remain = NewRemain;
                        fseek(fPtr, Round * sizeof(struct MovieData), SEEK_SET);
                        fwrite(&EnterInfo, sizeof(struct MovieData), 1, fPtr);
                        std::cout << "-- 已完成更改 将返回修改选择页 --" << std::endl;
                        goto CHANGE2;
                    default:
                        break;
                    }
                    Round++;
                }
            }
        }
        fclose(fPtr);
        break;
    }
}

int CheckBuy(int number)
{
    FILE *CfPtr;
    struct DealData CheckInfo = {0, "", 0, 0, "", 0, 0, "购票", 0, 0};
    if ((CfPtr = fopen("movie_deal.dat", "rb+")) == NULL)
    {
        std::cout << "--！交易信息文件出现错误，请检查文件是否正常 !--" << std::endl;
        exit(0);
    }
    rewind(CfPtr);
    while ((fread(&CheckInfo, sizeof(struct DealData), 1, CfPtr)) != (int)NULL)
    {
        //     std::cout << "sn is " << number << std::endl;
        //   std::cout << "EI is " << CheckInfo.number << std::endl;
        // std::cout << RefundInfo.number << ' ' <<  RefundInfo.name << ' ' << EnterInfo.type << ' ' << EnterInfo.duration << ' ' << EnterInfo.display_date << ' ' << EnterInfo.display_time << ' ' << EnterInfo.room << ' ' << EnterInfo.fare << ' ' << EnterInfo.remain << std::endl;

        if (number == CheckInfo.number)
        {
            fclose(CfPtr);
            return 0;
        }
    }
    fclose(CfPtr);
    return 1;
}

void DeleteInfo()
{
    int CheckBuy(int number);
    int CheckDate(int number);
    FILE *fPtr;
    FILE *nfPtr;
    struct MovieData EnterInfo = {0, "", "", 0, 0, 0, "", 0, 0};
AGAIN:
    // 请输入要录入的电影放映信息，顺序为[放映编号] [电影名称] [电影类型] [时长] [放映日期] [放映时间] [放映影厅] [票价] [余票]
    while (1)
    {

        int MovieNumber;
        std::cout << "-- 请先输入要删除的电影的编号 --" << std::endl;
        if (!(std::cin >> MovieNumber))
        {
            std::string choice;
            std::cout << "--! 输入的不是放映编号 !--" << std::endl;
            std::cout << "-- 是否重新录入? (按y以确定,按其他键返回主菜单) --" << std::endl;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                break;
            }
        }
        // std::cout << "buy is" << CheckBuy(MovieNumber) << std::endl;
        // std::cout << "date is" << CheckDate(MovieNumber) << std::endl;
        if (CheckBuy(MovieNumber) == 1 && CheckDate(MovieNumber) == 1)
        {
            rename("movie_base.dat", "temp.dat");
            if ((fPtr = fopen("temp.dat", "rb")) == NULL)
            {
                std::cout << "--! 文件打开出现错误 !--" << std::endl;
                exit(0);
            }
            if ((nfPtr = fopen("movie_base.dat", "wb")) == NULL)
            {
                std::cout << "--! 文件打开出现错误 !--" << std::endl;
                exit(0);
            }
            int Deleted = 0;
            char name[10];
            while ((fread(&EnterInfo, sizeof(struct MovieData), 1, fPtr)) != (int)NULL)
            {
                std::cout << "nu is " << MovieNumber << std::endl;
                std::cout << "EI is " << EnterInfo.number << std::endl;
                if (MovieNumber == EnterInfo.number)
                {
                    Deleted = 1;
                    strcpy(name, EnterInfo.name);
                }
                else
                {
                    fwrite(&EnterInfo, sizeof(struct MovieData), 1, nfPtr);
                }
            }
            if (Deleted == 1)
            {
                std::cout << "-- 电影\"" << name << "\"已成功删除 --" << std::endl;
                remove("temp.dat");
                std::cout << "-- 将自动返回主菜单 --" << std::endl;
                Sleep(3000);
                break;
            }
            else
            {
                std::cout << "--! 该电影不存在 !--" << std::endl;
                std::cout << "-- 将自动返回主菜单 --" << std::endl;
                Sleep(3000);
                break;
            }
        }
        else
        {
            std::cout << "--! 抱歉，该电影未放映完毕或有购票记录，无法删除 !--" << std::endl;
            std::string choice;
            std::cout << "-- 是否重新输入要删除的电影? (按y以确定,按其他键返回主菜单) --" << std::endl;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                break;
            }
        }
    }
}

int CheckDate(int number)
{
    FILE *fPtr;
    struct MovieData EnterInfo = {0, "", "", 0, 0, 0, "", 0, 0};
    if ((fPtr = fopen("movie_base.dat", "rb+")) == NULL)
    {
        std::cout << "--！文件打开出现错误，请检查文件是否正常 !--" << std::endl;
        exit(0);
    }
    rewind(fPtr);
    while ((fread(&EnterInfo, sizeof(struct MovieData), 1, fPtr)) != (int)NULL)
    {
        // std::cout << "nu is " << number << std::endl;
        // std::cout << "EI is " << EnterInfo.number << std::endl;
        if (EnterInfo.number == number)
        {
            int Time = TimeNow();
            int Date = DateNow();
            std::cout << "date is" << EnterInfo.display_date << std::endl;
            std::cout << "datenow is" << Date << std::endl;
            if (Date > EnterInfo.display_date || (Date == EnterInfo.display_date && Time > EnterInfo.display_time))
            {
                fclose(fPtr);
                return 1;
            }
        }
    }
    fclose(fPtr);
    return 0;
}

struct LinkData
{
    int number;
    char name[10];
    char type[10];
    int duration;
    long long int display_date;
    long long int display_time;
    char room[10];
    int fare;
    int remain;
    struct LinkData *next;
};
struct LinkDealData
{
    int number;
    char name[10];
    long long int display_date;
    long long int display_time;
    char room[10];
    long long int deal_date;
    long long int deal_time;
    char dealtype[10];
    double dealprice;
    int dealnumber;
    struct LinkDealData *next;
    // 电影编号、电影名称、放映日期、放映时间、放映影厅、交易日期、交易时间、交易类型、交易金额、交易数量。
};

void ShowAllInfo()
{
    struct LinkData *CreatMovieBaseList();
    struct LinkDealData *CreatMovieDealList();
    struct LinkData *p;
    struct LinkDealData *q;
    p = CreatMovieBaseList();
    q = CreatMovieDealList();
    while (p != NULL)
    {
        std::cout.setf(std::ios::left);
        std::cout << " ________________________________" << std::endl;
        std::cout << " |         电影信息             |" << std::endl;
        std::cout << " |                              |" << std::endl;
        std::cout << " | "
                  << " 电影放映编号:  " << std::setw(13) << p->number << "|" << std::endl;
        std::cout << " | "
                  << " 电影名:  " << std::setw(19) << p->name << "|" << std::endl;
        std::cout << " | "
                  << " 电影类型: " << std::setw(18) << p->type << "|" << std::endl;
        std::cout << " | "
                  << " 电影时长: " << std::setw(18) << p->duration << "|" << std::endl;
        std::cout << " | "
                  << " 放映日期: " << std::setw(18) << p->display_date << "|" << std::endl;
        std::cout << " | "
                  << " 放映时间: " << std::setw(18) << p->display_time << "|" << std::endl;
        std::cout << " | "
                  << " 放映厅: " << std::setw(20) << p->room << "|" << std::endl;
        std::cout << " | "
                  << " 票价: " << std::setw(22) << p->fare << "|" << std::endl;
        std::cout << " | "
                  << " 余票: " << std::setw(22) << p->remain << "|" << std::endl;
        std::cout << " |______________________________|" << std::endl;
        p = p->next;
    }
    // 电影编号、电影名称、放映日期、放映时间、放映影厅、交易日期、交易时间、交易类型、交易金额、交易数量。
    while (q != NULL)
    {
        std::cout.setf(std::ios::left);
        std::cout << " ________________________________" << std::endl;
        std::cout << " |         交易信息             |" << std::endl;
        std::cout << " |                              |" << std::endl;
        std::cout << " | "
                  << " 电影放映编号:  " << std::setw(13) << q->number << "|" << std::endl;
        std::cout << " | "
                  << " 电影名:  " << std::setw(19) << q->name << "|" << std::endl;
        std::cout << " | "
                  << " 放映日期: " << std::setw(18) << q->display_date << "|" << std::endl;
        std::cout << " | "
                  << " 放映时间: " << std::setw(18) << q->display_time << "|" << std::endl;
        std::cout << " | "
                  << " 放映厅: " << std::setw(20) << q->room << "|" << std::endl;
        std::cout << " | "
                  << " 交易日期: " << std::setw(18) << q->deal_date << "|" << std::endl;
        std::cout << " | "
                  << " 交易时间: " << std::setw(18) << q->deal_time << "|" << std::endl;
        std::cout << " | "
                  << " 交易类型: " << std::setw(20) << q->dealtype << "|" << std::endl;
        std::cout << " | "
                  << " 交易金额: " << std::setw(18) << q->dealprice << "|" << std::endl;
        std::cout << " | "
                  << " 交易数量: " << std::setw(18) << q->dealnumber << "|" << std::endl;
        std::cout << " |______________________________|" << std::endl;
        q = q->next;
    }
    Holdon();
}

struct LinkData *CreatMovieBaseList()
{
    FILE *ptr;
    struct MovieData EnterInfo = {0, "", "", 0, 0, 0, "", 0, 0};
    struct LinkData *head, *p, *q;
    if ((ptr = fopen("movie_base.dat", "rb")) == NULL)
    {
        std::cout << "--! 文件打开出现错误 !--" << std::endl;
        exit(0);
    }
    head = NULL;
    while (fread(&EnterInfo, sizeof(MovieData), 1, ptr) != 0)
    {
        p = (struct LinkData *)malloc(sizeof(struct LinkData));
        p->number = EnterInfo.number;
        strcpy(p->name, EnterInfo.name);
        strcpy(p->type, EnterInfo.type);
        p->duration = EnterInfo.duration;
        p->display_date = EnterInfo.display_date;
        p->display_time = EnterInfo.display_time;
        strcpy(p->room, EnterInfo.room);
        p->fare = EnterInfo.fare;
        p->remain = EnterInfo.remain;
        p->next = NULL;
        if (head == NULL)
        {
            head = p;
        }
        else
        {
            q->next = p;
        }
        q = p;
    }
    fclose(ptr);
    return head;
}
// struct LinkDealData
// {
//     int number;
//     char name[10];
//     long long int display_date;
//     long long int display_time;
//     char room[10];
//     long long int deal_date;
//     long long int deal_time;
//     char dealtype[10];
//     double dealprice;
//     int dealnumber;
//     struct LinkDealData *next;
//     // 电影编号、电影名称、放映日期、放映时间、放映影厅、交易日期、交易时间、交易类型、交易金额、交易数量。
// };
struct LinkDealData *CreatMovieDealList()
{
    FILE *ptr;
    struct DealData DealInfo = {0, "", 0, 0, "", 0, 0, "", 0, 0};
    struct LinkDealData *head, *p, *q;
    if ((ptr = fopen("movie_deal.dat", "rb")) == NULL)
    {
        std::cout << "--! 文件打开出现错误 !--" << std::endl;
        exit(0);
    }
    head = NULL;
    while (fread(&DealInfo, sizeof(DealData), 1, ptr) != 0)
    {
        p = (struct LinkDealData *)malloc(sizeof(struct LinkDealData));
        p->number = DealInfo.number;
        strcpy(p->name, DealInfo.name);
        p->display_date = DealInfo.display_date;
        p->display_time = DealInfo.display_time;
        strcpy(p->room, DealInfo.room);
        p->deal_date = DealInfo.deal_date;
        p->deal_time = DealInfo.deal_time;
        strcpy(p->dealtype, DealInfo.dealtype);
        p->dealprice = DealInfo.dealprice;
        p->dealnumber = DealInfo.dealnumber;
        p->next = NULL;
        if (head == NULL)
        {
            head = p;
        }
        else
        {
            q->next = p;
        }
        q = p;
    }
    fclose(ptr);
    return head;
}

void Inquire()
{
    void InquireMovie();
    void InquireDeal();
    std::cout << "-- 请输入您要查询的信息（输入其他视为返回主页面） --" << std::endl;
    std::cout << "-1 电影放映信息 -2 电影交易信息" << std::endl;
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        InquireMovie();
        break;
    case 2:
        InquireDeal();
        break;
    default:
        break;
    }
    Holdon();
}

void InquireMovie()
{ // 电影放映编号、电影名称、电影类型、放映日期
    struct LinkData *CreatMovieBaseList();

    struct LinkData *p;

    p = CreatMovieBaseList();

AGAIN:
    std::cout << "-- 请选择您要输入的查询信息（输入其他视为返回主页面） --" << std::endl;
    std::cout << "-1 电影放映编号  -2 电影名称 -3 电影类型 -4 放映日期" << std::endl;
    int choice;
    std::cin >> choice;
    int Found = 0;
    switch (choice)
    {
    case 1:
        std::cout << "-- 请输入要查询的电影放映编号 --" << std::endl;
        int SearchNum;
        if (!(std::cin >> SearchNum))
        {
            std::string choice;
            std::cout << "--! 输入的不是放映编号 !--" << std::endl;
            std::cout << "-- 是否返回查询信息主页面? (按y以确定,按其他键返回主菜单) --" << std::endl;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                break;
            }
        }

        while (p != NULL)
        {
            if (p->number == SearchNum)
            {
                if (Found == 0)
                {
                    std::cout << "-- 以下是符合条件的电影的信息 --" << std::endl;
                }
                Found = 1;
                std::cout.setf(std::ios::left);
                std::cout << " ________________________________" << std::endl;
                std::cout << " |         电影信息             |" << std::endl;
                std::cout << " |                              |" << std::endl;
                std::cout << " | "
                          << " 电影放映编号:  " << std::setw(13) << p->number << "|" << std::endl;
                std::cout << " | "
                          << " 电影名:  " << std::setw(19) << p->name << "|" << std::endl;
                std::cout << " | "
                          << " 电影类型: " << std::setw(18) << p->type << "|" << std::endl;
                std::cout << " | "
                          << " 电影时长: " << std::setw(18) << p->duration << "|" << std::endl;
                std::cout << " | "
                          << " 放映日期: " << std::setw(18) << p->display_date << "|" << std::endl;
                std::cout << " | "
                          << " 放映时间: " << std::setw(18) << p->display_time << "|" << std::endl;
                std::cout << " | "
                          << " 放映厅: " << std::setw(20) << p->room << "|" << std::endl;
                std::cout << " | "
                          << " 票价: " << std::setw(22) << p->fare << "|" << std::endl;
                std::cout << " | "
                          << " 余票: " << std::setw(22) << p->remain << "|" << std::endl;
                std::cout << " |______________________________|" << std::endl;
            }
            p = p->next;
        }
        if (Found == 0)
        {
            std::cout << "-- 很抱歉没有找到符合要求的电影 o(TヘTo) --" << std::endl;
        }
        break;
    case 2:
        std::cout << "-- 请输入要查询的电影名称 --" << std::endl;
        char SearchName[10];
        if (!(std::cin >> SearchName))
        {
            std::string choice;
            std::cout << "--! 输入的不是电影名称 !--" << std::endl;
            std::cout << "-- 是否返回查询信息主页面? (按y以确定,按其他键返回主菜单) --" << std::endl;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                break;
            }
        }
        while (p != NULL)
        {
            if (strcmp(p->name, SearchName) == 0)
            {
                if (Found == 0)
                {
                    std::cout << "-- 以下是符合条件的电影的信息 --" << std::endl;
                }
                Found = 1;
                std::cout.setf(std::ios::left);
                std::cout << " ________________________________" << std::endl;
                std::cout << " |         电影信息             |" << std::endl;
                std::cout << " |                              |" << std::endl;
                std::cout << " | "
                          << " 电影放映编号:  " << std::setw(13) << p->number << "|" << std::endl;
                std::cout << " | "
                          << " 电影名:  " << std::setw(19) << p->name << "|" << std::endl;
                std::cout << " | "
                          << " 电影类型: " << std::setw(18) << p->type << "|" << std::endl;
                std::cout << " | "
                          << " 电影时长: " << std::setw(18) << p->duration << "|" << std::endl;
                std::cout << " | "
                          << " 放映日期: " << std::setw(18) << p->display_date << "|" << std::endl;
                std::cout << " | "
                          << " 放映时间: " << std::setw(18) << p->display_time << "|" << std::endl;
                std::cout << " | "
                          << " 放映厅: " << std::setw(20) << p->room << "|" << std::endl;
                std::cout << " | "
                          << " 票价: " << std::setw(22) << p->fare << "|" << std::endl;
                std::cout << " | "
                          << " 余票: " << std::setw(22) << p->remain << "|" << std::endl;
                std::cout << " |______________________________|" << std::endl;
            }
            p = p->next;
        }
        if (Found == 0)
        {
            std::cout << "-- 很抱歉没有找到符合要求的电影 o(TヘTo) --" << std::endl;
        }
        break;
    case 3:
        std::cout << "-- 请输入要查询的电影类型 --" << std::endl;
        char Searchtype[10];
        if (!(std::cin >> Searchtype))
        {
            std::string choice;
            std::cout << "--! 输入的不是电影类型 !--" << std::endl;
            std::cout << "-- 是否返回查询信息主页面? (按y以确定,按其他键返回主菜单) --" << std::endl;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                break;
            }
        }

        while (p != NULL)
        {
            if (strcmp(p->type, Searchtype) == 0)
            {
                if (Found == 0)
                {
                    std::cout << "-- 以下是符合条件的电影的信息 --" << std::endl;
                }
                Found = 1;
                std::cout.setf(std::ios::left);
                std::cout << " ________________________________" << std::endl;
                std::cout << " |         电影信息             |" << std::endl;
                std::cout << " |                              |" << std::endl;
                std::cout << " | "
                          << " 电影放映编号:  " << std::setw(13) << p->number << "|" << std::endl;
                std::cout << " | "
                          << " 电影名:  " << std::setw(19) << p->name << "|" << std::endl;
                std::cout << " | "
                          << " 电影类型: " << std::setw(18) << p->type << "|" << std::endl;
                std::cout << " | "
                          << " 电影时长: " << std::setw(18) << p->duration << "|" << std::endl;
                std::cout << " | "
                          << " 放映日期: " << std::setw(18) << p->display_date << "|" << std::endl;
                std::cout << " | "
                          << " 放映时间: " << std::setw(18) << p->display_time << "|" << std::endl;
                std::cout << " | "
                          << " 放映厅: " << std::setw(20) << p->room << "|" << std::endl;
                std::cout << " | "
                          << " 票价: " << std::setw(22) << p->fare << "|" << std::endl;
                std::cout << " | "
                          << " 余票: " << std::setw(22) << p->remain << "|" << std::endl;
                std::cout << " |______________________________|" << std::endl;
            }
            p = p->next;
        }
        if (Found == 0)
        {
            std::cout << "-- 很抱歉没有找到符合要求的电影 o(TヘTo) --" << std::endl;
        }
        break;
    case 4:
        std::cout << "-- 请输入要查询的电影放映日期 --" << std::endl;
        int SearchDate;
        if (!(std::cin >> SearchDate))
        {
            std::string choice;
            std::cout << "--! 输入的不是放映日期 !--" << std::endl;
            std::cout << "-- 是否返回查询信息主页面? (按y以确定,按其他键返回主菜单) --" << std::endl;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                break;
            }
        }
        while (p != NULL)
        {
            if (p->display_date == SearchDate)
            {
                if (Found == 0)
                {
                    std::cout << "-- 以下是符合条件的电影的信息 --" << std::endl;
                }
                Found = 1;
                std::cout.setf(std::ios::left);
                std::cout << " ________________________________" << std::endl;
                std::cout << " |         电影信息             |" << std::endl;
                std::cout << " |                              |" << std::endl;
                std::cout << " | "
                          << " 电影放映编号:  " << std::setw(13) << p->number << "|" << std::endl;
                std::cout << " | "
                          << " 电影名:  " << std::setw(19) << p->name << "|" << std::endl;
                std::cout << " | "
                          << " 电影类型: " << std::setw(18) << p->type << "|" << std::endl;
                std::cout << " | "
                          << " 电影时长: " << std::setw(18) << p->duration << "|" << std::endl;
                std::cout << " | "
                          << " 放映日期: " << std::setw(18) << p->display_date << "|" << std::endl;
                std::cout << " | "
                          << " 放映时间: " << std::setw(18) << p->display_time << "|" << std::endl;
                std::cout << " | "
                          << " 放映厅: " << std::setw(20) << p->room << "|" << std::endl;
                std::cout << " | "
                          << " 票价: " << std::setw(22) << p->fare << "|" << std::endl;
                std::cout << " | "
                          << " 余票: " << std::setw(22) << p->remain << "|" << std::endl;
                std::cout << " |______________________________|" << std::endl;
            }
            p = p->next;
        }
        if (Found == 0)
        {
            std::cout << "-- 很抱歉没有找到符合要求的电影 o(TヘTo) --" << std::endl;
        }
        break;
    }
}

void InquireDeal()
{ // 电影放映编号、电影名称、电影类型、放映日期

    struct LinkDealData *CreatMovieDealList();

    struct LinkDealData *q;

    q = CreatMovieDealList();
    int Found = 0;
AGAIN:
    std::cout << "-- 请选择您要输入的查询信息（输入其他视为返回主页面） --" << std::endl;
    std::cout << "-1 交易日期 -2 电影名称 " << std::endl;
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        std::cout << "-- 请输入要查询的交易日期（格式YYYYMMDD） --" << std::endl;
        int SearchDate;
        if (!(std::cin >> SearchDate))
        {
            std::string choice;
            std::cout << "--! 输入的不是放映编号 !--" << std::endl;
            std::cout << "-- 是否返回查询信息主页面? (按y以确定,按其他键返回主菜单) --" << std::endl;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                break;
            }
        }

        while (q != NULL)
        {
            if (q->deal_date == SearchDate)
            {
                // struct LinkDealData
                //  {
                //      int number;
                //      char name[10];
                //      long long int display_date;
                //      long long int display_time;
                //      char room[10];
                //      long long int deal_date;
                //      long long int deal_time;
                //      char dealtype[10];
                //      double dealprice;
                //      int dealnumber;
                //      struct LinkDealData *next;
                //      // 电影编号、电影名称、放映日期、放映时间、放映影厅、交易日期、交易时间、交易类型、交易金额、交易数量。
                //  };
                if (Found == 0)
                {
                    std::cout << "-- 以下是符合条件的电影的信息 --" << std::endl;
                }
                Found = 1;
                std::cout.setf(std::ios::left);
                std::cout << " ________________________________" << std::endl;
                std::cout << " |         电影信息             |" << std::endl;
                std::cout << " |                              |" << std::endl;
                std::cout << " | "
                          << " 电影放映编号:  " << std::setw(13) << q->number << "|" << std::endl;
                std::cout << " | "
                          << " 电影名:  " << std::setw(19) << q->name << "|" << std::endl;
                std::cout << " | "
                          << " 放映日期: " << std::setw(18) << q->display_date << "|" << std::endl;
                std::cout << " | "
                          << " 放映时间: " << std::setw(18) << q->display_time << "|" << std::endl;
                std::cout << " | "
                          << " 放映厅: " << std::setw(20) << q->room << "|" << std::endl;
                std::cout << " | "
                          << " 交易日期: " << std::setw(18) << q->deal_date << "|" << std::endl;
                std::cout << " | "
                          << " 交易时间: " << std::setw(18) << q->deal_time << "|" << std::endl;
                std::cout << " | "
                          << " 交易类型: " << std::setw(20) << q->dealtype << "|" << std::endl;
                std::cout << " | "
                          << " 交易金额: " << std::setw(18) << q->dealprice << "|" << std::endl;
                std::cout << " | "
                          << " 交易数量: " << std::setw(18) << q->dealnumber << "|" << std::endl;
                std::cout << " |______________________________|" << std::endl;
            }
            q = q->next;
        }
        if (Found == 0)
        {
            std::cout << "-- 很抱歉没有找到符合要求的电影 o(TヘTo) --" << std::endl;
        }
        break;
    case 2:
        std::cout << "-- 请输入要查询的电影名称 --" << std::endl;
        char SearchName[10];
        if (!(std::cin >> SearchName))
        {
            std::string choice;
            std::cout << "--! 输入的不是电影名称 !--" << std::endl;
            std::cout << "-- 是否返回查询信息主页面? (按y以确定,按其他键返回主菜单) --" << std::endl;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                break;
            }
        }
        while (q != NULL)
        {
            if (strcmp(q->name, SearchName) == 0)
            {
                if (Found == 0)
                {
                    std::cout << "-- 以下是符合条件的电影的信息 --" << std::endl;
                }
                Found = 1;
                std::cout.setf(std::ios::left);
                std::cout << " ________________________________" << std::endl;
                std::cout << " |         电影信息             |" << std::endl;
                std::cout << " |                              |" << std::endl;
                std::cout << " | "
                          << " 电影放映编号:  " << std::setw(13) << q->number << "|" << std::endl;
                std::cout << " | "
                          << " 电影名:  " << std::setw(19) << q->name << "|" << std::endl;
                std::cout << " | "
                          << " 放映日期: " << std::setw(18) << q->display_date << "|" << std::endl;
                std::cout << " | "
                          << " 放映时间: " << std::setw(18) << q->display_time << "|" << std::endl;
                std::cout << " | "
                          << " 放映厅: " << std::setw(20) << q->room << "|" << std::endl;
                std::cout << " | "
                          << " 交易日期: " << std::setw(18) << q->deal_date << "|" << std::endl;
                std::cout << " | "
                          << " 交易时间: " << std::setw(18) << q->deal_time << "|" << std::endl;
                std::cout << " | "
                          << " 交易类型: " << std::setw(20) << q->dealtype << "|" << std::endl;
                std::cout << " | "
                          << " 交易金额: " << std::setw(18) << q->dealprice << "|" << std::endl;
                std::cout << " | "
                          << " 交易数量: " << std::setw(18) << q->dealnumber << "|" << std::endl;
                std::cout << " |______________________________|" << std::endl;
            }
            q = q->next;
        }
        if (Found == 0)
        {
            std::cout << "-- 很抱歉没有找到符合要求的电影 o(TヘTo) --" << std::endl;
        }
    }
}

void Statistic()
{
    // 电影放映信息基本信息：可以按照电影名称、放映日期、放映影厅等条件进行余票统计，统计满足条件对应的余票。
    // 交易信息：可以按照电影名称、交易日期等条件，统计出满足条件对应的购票人数、购票金额、退票人数、退票金额等。
    // void InquireMovie();
    // void InquireDeal();
    void CountRemain();
    void CountDeal();
    std::cout << "-- 请输入您要的信息（输入其他视为返回主页面） --" << std::endl;
    std::cout << "-1 电影放映信息余票统计 -2 电影交易信息" << std::endl;
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        CountRemain();
        break;
    case 2:
        CountDeal();
        break;
    default:
        break;
    }
    Holdon();
}

void CountRemain()
{
    struct LinkData *CreatMovieBaseList();

    struct LinkData *p;

    p = CreatMovieBaseList();

AGAIN:
    std::cout << "-- 请选择您要输入的统计信息，我会统计出满足所有条件的电影的余票和（输入其他视为返回主页面） --" << std::endl;
    std::cout << "-1 电影名称  -2 放映日期 -3 放映影厅 " << std::endl;
    int choice;
    std::cin >> choice;
    int Found = 0;
    int total = 0;
    switch (choice)
    {
    case 1:
        std::cout << "-- 请输入要查询的电影名称 --" << std::endl;
        char SearchName[10];
        if (!(std::cin >> SearchName))
        {
            std::string choice;
            std::cout << "--! 输入的不是电影名称 !--" << std::endl;
            std::cout << "-- 是否返回查询信息主页面? (按y以确定,按其他键返回主菜单) --" << std::endl;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                break;
            }
        }
        while (p != NULL)
        {
            if (strcmp(p->name, SearchName) == 0)
            {
                if (Found == 0)
                {
                    std::cout << "-- 以下是符合条件的电影的余票 --" << std::endl;
                    std::cout << "_________________________" << std::endl;
                }
                Found = 1;
                std::cout.setf(std::ios::left);
                std::cout << "|" << std::setw(8) << p->name << "余票：" << std::setw(7) << p->remain << "张"
                          << "|" << std::endl;
                total += p->remain;
            }
            p = p->next;
        }
        if (Found == 1)
        {
            std::cout << "|_______________________|" << std::endl;
            std::cout << "满足条件的电影的余票总和为：" << total << "张" << std::endl;
        }
        if (Found == 0)
        {
            std::cout << "-- 很抱歉没有找到符合要求的电影 o(TヘTo) --" << std::endl;
        }
        break;

    case 2:
        std::cout << "-- 请输入要查询的电影放映日期 --" << std::endl;
        int SearchDate;
        if (!(std::cin >> SearchDate))
        {
            std::string choice;
            std::cout << "--! 输入的不是放映日期 !--" << std::endl;
            std::cout << "-- 是否返回查询信息主页面? (按y以确定,按其他键返回主菜单) --" << std::endl;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                break;
            }
        }
        while (p != NULL)
        {
            if (p->display_date == SearchDate)
            {

                if (Found == 0)
                {
                    std::cout << "-- 以下是符合条件的电影的余票 --" << std::endl;
                    std::cout << "_________________________" << std::endl;
                }
                Found = 1;
                std::cout.setf(std::ios::left);
                std::cout << "|" << std::setw(8) << p->name << "余票：" << std::setw(7) << p->remain << "张"
                          << "|" << std::endl;
                total += p->remain;

                p = p->next;
            }
            if (Found == 1)
            {
                std::cout << "|_______________________|" << std::endl;
                std::cout << "满足条件的电影的余票总和为：" << total << "张" << std::endl;
            }
            if (Found == 0)
            {
                std::cout << "-- 很抱歉没有找到符合要求的电影 o(TヘTo) --" << std::endl;
            }
            break;
        case 3:
            std::cout << "-- 请输入要查询的电影放映影厅 --" << std::endl;
            char Searchroom[10];
            if (!(std::cin >> Searchroom))
            {
                std::string choice;
                std::cout << "--! 输入的不是电影放映影厅 !--" << std::endl;
                std::cout << "-- 是否返回查询信息主页面? (按y以确定,按其他键返回主菜单) --" << std::endl;
                std::cin.clear();
                std::cin.sync();
                std::cin >> choice;
                if (choice == "y")
                {
                    goto AGAIN;
                }
                else
                {
                    break;
                }
            }

            while (p != NULL)
            {
                if (strcmp(p->room, Searchroom) == 0)
                {
                    if (Found == 0)
                    {
                        std::cout << "-- 以下是符合条件的电影的余票 --" << std::endl;
                        std::cout << "_________________________" << std::endl;
                    }
                    Found = 1;
                    std::cout.setf(std::ios::left);
                    std::cout << "|" << std::setw(8) << p->name << "余票：" << std::setw(7) << p->remain << "张"
                              << "|" << std::endl;
                    total += p->remain;
                }
                p = p->next;
            }
            if (Found == 1)
            {
                std::cout << "|_______________________|" << std::endl;
                std::cout << "满足条件的电影的余票总和为：" << total << "张" << std::endl;
            }
            if (Found == 0)
            {
                std::cout << "-- 很抱歉没有找到符合要求的电影 o(TヘTo) --" << std::endl;
            }
            break;
        }
    }
}

void CountDeal()
{
    struct LinkDealData *CreatMovieDealList();
    struct LinkDealData *q;
    q = CreatMovieDealList();
    // 电影名称、交易日期
AGAIN:
    std::cout << "-- 请选择您要输入的统计信息，我会统计出满足所有条件的电影的余票和（输入其他视为返回主页面） --" << std::endl;
    std::cout << "-1 电影名称  -2 交易日期 " << std::endl;
    int choice;
    std::cin >> choice;
    int Found = 0;
    int BuyP = 0;
    int BuyF = 0;
    int RefP = 0;
    int RefF = 0;
    switch (choice)
    {
        // struct DealData
        //  {
        //      int number;
        //      char name[10];
        //      long long int display_date;
        //      long long int display_time;
        //      char room[10];
        //      long long int deal_date;
        //      long long int deal_time;
        //      char dealtype[10];
        //      double dealprice;
        //      int dealnumber;
        //      // 电影编号、电影名称、放映日期、放映时间、放映影厅、交易日期、交易时间、交易类型、交易金额、交易数量。
        //  };
        //  统计出满足条件对应的购票人数、购票金额、退票人数、退票金额等。
    case 1:
        std::cout << "-- 请输入要查询的电影名称 --" << std::endl;
        char SearchName[10];
        if (!(std::cin >> SearchName))
        {
            std::string choice;
            std::cout << "--! 输入的不是电影名称 !--" << std::endl;
            std::cout << "-- 是否返回查询信息主页面? (按y以确定,按其他键返回主菜单) --" << std::endl;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                break;
            }
        }
        while (q != NULL)
        {
            if (strcmp(q->name, SearchName) == 0 && strcmp(q->dealtype, "购票") == 0)
            {
                Found = 1;
                BuyP += q->dealnumber;
                BuyF += q->dealprice;
            }
            if (strcmp(q->name, SearchName) == 0 && strcmp(q->dealtype, "退票") == 0)
            {
                Found = 1;
                RefP += q->dealnumber;
                RefF += q->dealprice;
            }
            q = q->next;
        }
        if (Found == 1)
        {
            std::cout << "-- 以下是符合条件的电影的相关交易信息 --" << std::endl;
            std::cout.setf(std::ios::left);
            std::cout << " ________________________________" << std::endl;
            std::cout << " |         电影信息             |" << std::endl;
            std::cout << " |                              |" << std::endl;
            std::cout << " | "
                      << " 购票人数: " << std::setw(18) << BuyP << "|" << std::endl;
            std::cout << " | "
                      << " 购票金额: " << std::setw(18) << BuyF << "|" << std::endl;
            std::cout << " | "
                      << " 退票人数: " << std::setw(18) << RefP * -1 << "|" << std::endl;
            std::cout << " | "
                      << " 退票金额: " << std::setw(18) << RefF << "|" << std::endl;
            std::cout << " |______________________________|" << std::endl;
        }
        if (Found == 0)
        {
            std::cout << "-- 很抱歉没有找到符合要求的电影 o(TヘTo) --" << std::endl;
        }
        break;

    case 2:
        std::cout << "-- 请输入要查询的电影交易日期 --" << std::endl;
        int SearchDate;
        if (!(std::cin >> SearchDate))
        {
            std::string choice;
            std::cout << "--! 输入的不是交易日期 !--" << std::endl;
            std::cout << "-- 是否返回查询信息主页面? (按y以确定,按其他键返回主菜单) --" << std::endl;
            std::cin.clear();
            std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                break;
            }
        }
        while (q != NULL)
        {
            if (q->deal_date == SearchDate)
            {
                if (strcmp(q->name, SearchName) == 0 && strcmp(q->dealtype, "购票") == 0)
                {
                    Found = 1;
                    BuyP += q->dealnumber;
                    BuyF += q->dealprice;
                }
                if (strcmp(q->name, SearchName) == 0 && strcmp(q->dealtype, "退票") == 0)
                {
                    Found = 1;
                    RefP += q->dealnumber;
                    RefF += q->dealprice;
                }
            }
            q = q->next;
        }
        if (Found == 1)
        {
            std::cout << "-- 以下是符合条件的电影的相关交易信息 --" << std::endl;
            std::cout.setf(std::ios::left);
            std::cout << " ________________________________" << std::endl;
            std::cout << " |         电影信息             |" << std::endl;
            std::cout << " |                              |" << std::endl;
            std::cout << " | "
                      << " 购票人数: " << std::setw(18) << BuyP << "|" << std::endl;
            std::cout << " | "
                      << " 购票金额: " << std::setw(18) << BuyF << "|" << std::endl;
            std::cout << " | "
                      << " 退票人数: " << std::setw(18) << RefP * -1 << "|" << std::endl;
            std::cout << " | "
                      << " 退票金额: " << std::setw(18) << RefF << "|" << std::endl;
            std::cout << " |______________________________|" << std::endl;
        }
        if (Found == 0)
        {
            std::cout << "-- 很抱歉没有找到符合要求的电影 o(TヘTo) --" << std::endl;
        }
        break;
    }
}

void ChangePassword()
{
    char line[100];
    int linecount = 1;
    std::cout << "-- 请输入新的账号 --" << std::endl;
    char NName[64];
    std::cin >> NName;
    std::cout << "-- 请输入新的密码 --" << std::endl;
    char Npassword[64];
    std::cin >> Npassword;
    strcat(NName, "\n");
    FILE *fPtr, *nfPtr;
    rename("Account.txt", "Temp.txt");
    if ((fPtr = fopen("Temp.txt", "r+")) == NULL)
    {
        std::cout << "--! 文件打开出现错误 !--" << std::endl;
        exit(0);
    }
    if ((nfPtr = fopen("Account.txt", "w+")) == NULL)
    {
        std::cout << "--! 文件打开出现错误 !--" << std::endl;
        exit(0);
    }
    while (fgets(line, sizeof(line), fPtr))
    {
        if (linecount == 1)
        {
            fprintf(nfPtr, NName);
        }
        if (linecount == 2)
        {
            fprintf(nfPtr, Npassword);
        }
        linecount++;
    }
    fclose(fPtr);
    fclose(nfPtr);
    remove("Temp.txt");
}

struct RemainReport
{
    char name[10];
    int remain;
};

void Report()
{
    void MonthDeal();
    void ReportRemain();
    std::cout << "-- 请输入您要汇总的类型（输入其他将返回主页面） --" << std::endl;
    std::cout << "-1 电影的余票量汇总报表 -2 按月统计不同电影交易金额 " << std::endl;
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        ReportRemain();
        break;
    case 2:
        MonthDeal();
        break;
    default:
        break;
    }
    Holdon();
}
void ReportRemain()
{
    struct LinkData *CreatMovieBaseList();
    struct LinkData *p;
    p = CreatMovieBaseList();
    struct RemainReport list[1000];
    int i = 0;
    while (p != NULL)
    {
        strcpy(list[i].name, p->name);
        list[i].remain = p->remain;
        p = p->next;
        i++;
    }

    FILE *file;
    char filename[] = "汇总报表Template.tex";
    char tempFilename[] = "电影的余票量汇总报表.tex";
    char line[100];
    int lineNum = 1;
    int k = 0;

    // 打开原始文件
    file = fopen(filename, "r");
    if (file == NULL)
    {
        std::cout << "--! 生成报表出现错误 !--" << std::endl;
        exit(0);
    }

    // 创建临时文件
    FILE *tempFile = fopen(tempFilename, "w");
    if (tempFile == NULL)
    {
        std::cout << "--! 生成报表出现错误 !--" << std::endl;
        fclose(file);
        exit(0);
    }

    // 逐行读取原始文件内容并写入临时文件
    while (fgets(line, sizeof(line), file))
    {

        // 在第一行和第二行之间插入"你好"两个字
        if (lineNum == 15)
        {
            fprintf(tempFile, "%s\\hline\n\\kaiti%s%s&\\kaiti%d\\\\\n", line, " ", list[k].name, list[k].remain);
            k++;
            while (k != i)
            {
                fprintf(tempFile, "\\hline\n\\kaiti%s%s&\\kaiti%d\\\\\n", " ", list[k].name, list[k].remain);
                k++;
            }
        }
        else
        {
            fprintf(tempFile, "%s", line);
        }
        lineNum++;
    }

    // 关闭文件
    fclose(file);
    fclose(tempFile);
    // WinExec("CreateTex.bat", SW_HIDE);
    system("xelatex 电影的余票量汇总报表.tex");
    system("del *.log");
    system("del *.aux");
    system("start 电影的余票量汇总报表.pdf");
}
struct PrintMonth
{
    char name[10];
    int start;
    int end;
    int mid;
    int buy;
    int refund;
};
void MonthDeal()
{
    struct LinkDealData *CreatMovieDealList();
    struct LinkDealData *q;
    struct PrintMonth List[100];
    int i = 0;
    q = CreatMovieDealList();
    while (q != NULL)
    {
        strcpy(List[i].name, q->name);
        List[i].mid = q->deal_date;
        List[i].start = ((q->deal_date) / 100) * 100 + 1;
        if (((List[i].start / 100) + 1) % 10 == 3)
        {
            List[i].end = ((List[i].start / 10000) + 1) * 10000 + 101;
        }
        else
        {
            List[i].end = List[i].start + 100;
        }
        if (strcmp(q->dealtype, "购票") == 0)
        {
            List[i].buy = q->dealprice;
            List[i].refund = 0;
        }
        else if (strcmp(q->dealtype, "退票") == 0)
        {
            List[i].refund = (q->dealprice) * -1;
            List[i].buy = 0;
        }
        std::cout << "start is " << List[i].start << std::endl;
        std::cout << "end is " << List[i].end << std::endl;
        q = q->next;
        i++;
    }
    struct PrintMonth sort[100];
    strcpy(sort[0].name, List[0].name);
    sort[0].start = List[0].start;
    sort[0].end = List[0].end;
    sort[0].buy = List[0].buy;
    sort[0].refund = List[0].refund;
    int k = 1;
    for (int j = 1; j < i; j++)
    {
        int h = 0;
        while (h < k)
        {
            int flag = 0;
            if (((strcmp(sort[h].name, List[j].name)) == 0) && (sort[h].start == List[j].start))
            {
                sort[h].refund += List[j].refund;
                sort[h].buy += List[j].buy;
                flag = 1;
            }
            if (h == k - 1 && flag == 0)
            {
                strcpy(sort[k].name, List[j].name);
                sort[k].start = List[j].start;
                sort[k].end = List[j].end;
                sort[k].buy = List[j].buy;
                sort[k].refund = List[j].refund;
                k++;
                break;
            }
            h++;
        }
    }
    // for (int l = 0; l < k; l++)
    // {
    //     std::cout << sort[l].name << std::endl;
    //     std::cout << sort[l].start << std::endl;
    //     std::cout << sort[l].end << std::endl;
    //     std::cout << sort[l].buy << std::endl;
    //     std::cout << sort[l].refund << std::endl;
    // }
    FILE *file;
    char filename[] = "汇总报表Template2.tex";
    char tempFilename[] = "电影交易信息.tex";
    char line[200];
    int lineNum = 1;
    int l = 0;

    // 打开原始文件
    file = fopen(filename, "r");
    if (file == NULL)
    {
        std::cout << "--! 生成报表出现错误 !--" << std::endl;
        exit(0);
    }

    // 创建临时文件
    FILE *tempFile = fopen(tempFilename, "w");
    if (tempFile == NULL)
    {
        std::cout << "--! 生成报表出现错误 !--" << std::endl;
        fclose(file);
        exit(0);
    }

    // 逐行读取原始文件内容并写入临时文件
    while (fgets(line, sizeof(line), file))
    {

        // 在第一行和第二行之间插入"你好"两个字
        if (lineNum == 16)
        {
            fprintf(tempFile, "%s\n\\hline\n\\kaiti%s%s&\\kaiti%s%d&\\kaiti%s%d&\\kaiti%s%d&\\kaiti%s%d\\\\\n", line, " ", sort[l].name, " ", sort[l].start, " ", sort[l].end, " ", sort[l].buy, " ", sort[l].refund);
            l++;
            while (l != k)
            {
                fprintf(tempFile, "\\hline\n\\kaiti%s%s&\\kaiti%s%d&\\kaiti%s%d&\\kaiti%s%d&\\kaiti%s%d\\\\\n", " ", sort[l].name, " ", sort[l].start, " ", sort[l].end, " ", sort[l].buy, " ", sort[l].refund);
                l++;
            }
        }
        else
        {
            fprintf(tempFile, "%s", line);
        }
        lineNum++;
    }

    // 关闭文件
    fclose(file);
    fclose(tempFile);
    // WinExec("CreateTex.bat", SW_HIDE);
    system("xelatex 电影交易信息.tex");
    system("del *.log");
    system("del *.aux");
    system("start 电影交易信息.pdf");
}