#include <iostream>
#include <string>
#include <stdio.h>

void ShowMenu()
{
    std::cout << "                 ___________________________________________" << std::endl;
    std::cout << "                 |                                         |" << std::endl;
    std::cout << "                 |          欢迎使用电影购票系统           |" << std::endl;
    std::cout << "                 |      请输入相应数字以完成对应的操作     |" << std::endl;
    std::cout << "                 |                                         |" << std::endl;
    std::cout << "                 |      -1   录入电影放映信息              |" << std::endl;
    std::cout << "                 |      -2   票务管理                      |" << std::endl;
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

void GetChoice()
{
    void EnterMovieInfo();
    void QuitSystem();
    ShowMenu();
    int Chioce = 0;
    std::cin >> Chioce;
    switch (Chioce)
    {
    case 0:
        std::cout << "--系统已退出--" << std::endl;
        QuitSystem();
        break;
    case 1:
        std::cout << "--开始录入电影放映信息--" << std::endl;
        EnterMovieInfo();
        break;
    case 2:
        std::cout << "--进入票务管理--" << std::endl;
        break;
    case 3:
        std::cout << "--进入退票管理--" << std::endl;
        break;
    case 4:
        std::cout << "--开始修改电影放映信息--" << std::endl;
        break;
    case 5:
        std::cout << "--开始信息输出--" << std::endl;
        break;
    case 6:
        std::cout << "--进入查询管理--" << std::endl;
        break;
    case 7:
        std::cout << "--进入统计管理--" << std::endl;
        break;
    case 8:
        std::cout << "--正在输出报表--" << std::endl;
        break;
    case 9:
        std::cout << "--开始密码修改--" << std::endl;
        break;

    default:
        std::cout << "输入错误请重新输入！" << std::endl;
        GetChoice();
        break;
    }
}

struct MovieData
{
    int number;
    std::string name;
    std::string type;
    std::string duration;
    std::string display_date;
    std::string display_time;
    std::string room;
    int fare;
    int remain;
};

void EnterMovieInfo()
{
    FILE *fPtr;
    struct MovieData EnterInfo = {0, "", "", "", "", "", "", 0, 0};
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
            // std::cin.clear();
            // std::cin.sync();
            std::cin >> choice;
            if (choice == "y")
            {
                goto AGAIN;
            }
            else
            {
                GetChoice();
            }
        }
        rewind(fPtr);
        while ((fread(&EnterInfo, sizeof(struct MovieData), 1, fPtr)) != (int)NULL)
        {
            // std::cout << "Mn is " << MovieNumber << std::endl;
            // std::cout << "EI is " << EnterInfo.number << std::endl;
            if (MovieNumber == EnterInfo.number)
            {
                std::string choice;
                std::cout << "--! 电影放映信息的编号出现相同，不能录入 !--" << std::endl;
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
                    GetChoice();
                }
            }
        }
        EnterInfo.number = MovieNumber;
        break;
    }
    std::cout << "-- 请继续输入要录入的电影放映信息，顺序为[电影名称] [电影类型] [时长] [放映日期] [放映时间] [放映影厅] [票价] [余票]" << std::endl;
    std::cin >> EnterInfo.name;
    std::cin >> EnterInfo.type;
    std::cin >> EnterInfo.duration;
    std::cin >> EnterInfo.room;
    std::cin >> EnterInfo.fare;
    std::cin >> EnterInfo.remain;
    fseek(fPtr, 0, SEEK_END);
    fwrite(&EnterInfo, sizeof(struct MovieData), 1, fPtr);
    std::cout << "-- 信息录入成功! 是否继续录入? (按y以确定,按其他键返回主菜单) --" << std::endl;
    std::string choice;
    // std::cin.clear();
    // std::cin.sync();
    std::cin >> choice;
    if (choice == "y")
    {
        goto AGAIN;
    }
    else
    {
        GetChoice();
    }
}

void QuitSystem()
{
    exit(0);
}