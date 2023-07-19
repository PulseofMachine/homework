#include <iostream>

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
    ShowMenu();
    int Chioce = 0;
    std::cin >> Chioce;
    switch (Chioce)
    {
    case 0:
        std::cout << "--系统已退出--" << std::endl;
        break;
    case 1:
        std::cout << "--开始录入电影放映信息--" << std::endl;
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

int main()
{
    GetChoice();

    return 0;
}
