#include <iostream>
#include <string>
#include <stdio.h>
#include "Now.h"
#include <string.h>

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
    std::cout << "                 |      -0  退出系统                       |" << std::endl;
    std::cout << "                 |                                         |" << std::endl;
    std::cout << "                 |_________________________________________|" << std::endl;
    std::cout << std ::endl;
    std::cout << "请在下方输入数字以完成对应操作" << std::endl;
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
    };
    return Choice;
}

struct MovieData
{
    int number;
    char name[10];
    char type[10];
    char duration[10];
    long long int display_date;
    long long int display_time;
    char room[10];
    int fare;
    int remain;
};

void EnterMovieInfo()
{
    FILE *fPtr;
    struct MovieData EnterInfo = {0, "", "", "", 0, 0, "", 0, 0};
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
    struct MovieData EnterInfo = {0, "", "", "", 0, 0, "", 0, 0};
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
                    Sleep(2000);
                    break;
                }
                if (TimeOut == 0)
                {

                    std::cout << "-- 检查完成，该电影票可以购买 --" << std::endl;
                AGAIN:
                    std::cout << "-- 请输入要购买的电影票数量 当前电影票剩余量：" << EnterInfo.remain << "张" << std::endl;
                    int BuyNumber = 0;
                    if (!(std::cin >> BuyNumber) || BuyNumber > EnterInfo.remain)
                    {
                        std::string choice;
                        std::cout << "--! 输入的不是数字或大于剩余票量 !--" << std::endl;
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
    }
}

struct DealData
{
    char name[10];
    long long int display_date;
    long long int display_time;
    char room[10];
    long long int deal_date;
    long long int deal_time;
    char dealtype[10];
    double dealprice;
};

void SaveDeal(const struct MovieData *p, int BuyNumber)
{
    FILE *dfPtr;
    struct DealData DealInfo = {"", 0, 0, "", 0, 0, "购票", 0};
    if ((dfPtr = fopen("movie_deal.dat", "ab+")) == NULL)
    {
        std::cout << "--！交易录入出现错误，请检查文件是否正常 !--" << std::endl;
        exit(0);
    }
    strcpy(DealInfo.name, p->name);
    DealInfo.display_date = p->display_date;
    DealInfo.display_time = p->display_time;
    strcpy(DealInfo.room, p->room);
    DealInfo.deal_date = DateNow();
    DealInfo.deal_time = TimeNow();
    DealInfo.dealprice = BuyNumber * p->fare;
    std::cout << DealInfo.name << ' ' << DealInfo.display_date << ' ' << DealInfo.display_time << ' ' << DealInfo.room << ' ' << DealInfo.deal_date << ' ' << DealInfo.deal_time << ' ' << DealInfo.dealtype << ' ' << DealInfo.dealprice << std::endl;
    fseek(dfPtr, 0, SEEK_END);
    fwrite(&DealInfo, sizeof(struct DealData), 1, dfPtr);
    fclose(dfPtr);
    std::cout << "-- 购买成功，交易信息录入成功 --" << std::endl;
}