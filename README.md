# Ticket
C++实现一个简单的航空购票程序(主要是结构体的使用，未涉及面向对象编程)

=====

题目要求：

编写一个航空订票程序：

假设一等舱5个座位，编号为1~5，经济舱20个座位，编号为1~20

具体要求如下：

当程序开始时，提示输入乘客姓名，一个名字只能订一个座位，如果该名字已经订过座位了，则提示该乘客座位已定及座位号，否则提示输入舱位类型；

当输入舱位类型后，如果该舱位已全部订出，则提示此舱全部订完，重新选择舱位类型；否则显示可以选择的座位号，注意已经被订出的座位号不能出现，提示输入座位号；

舱位类型：只能输入”F”或”E”，一等舱为F，经济舱为E，如果输入其它字符则提示输入无效。

座位号：只能输入前面列出可以选择的座位号，若输入其它则提示输入无效。

程序可以为多个乘客订票，直到输入名字为”.”;

最后程序按照舱位类型与座位号排序打印出所有订票信息（座位号及对应乘客姓名）


1，变量
--------
不过既然提到了结构体用来存储票的信息（其实这就是面向对象思想的早期）。联系实际，一个结构体代表一个事物，结构体中的字段代表这个事物的属性；这样的话，我们可以提取出两个结构体：座位Seat和票Ticket，由于题目给定总共25个座位，意味着25张票，则将它们声明成全局变量。

    //座位,那么座位有3个基本属性：座位类型（F/E），座位编号，座位预定状态（是否已经被预定）
    struct Seat{
        char type;
        int number;
        bool isReservation;
    }seats[25];

    //票，票有两个属性，即票需要表明：谁预定了哪个座位，第一个Seat就是我们前面定义的那个结构体。
    struct Ticket{
        Seat seat;
        string passenger_name;
    }tickets[25];

2，函数
--------
我们需要将一些输出输入的操作提取成函数，简化我们的代码，这里之所以将输入提取成input()函数，是因为我们需要不断输入，即使出错，所以为了便于递归调用就封装成函数；

    bool check(string name);//检测是否已购票
    void input();//用于执行输入
    void printSeat(char seatType);//显示剩余座位
    void reservation(string name,int seatNumber,char seatType);//购票
    void printTickets(string name);//显示已购票信息
    void printError();//显示输入不合法

3，主体逻辑
--------
main函数非常简单，首先需要将座位和票信息初始化，即将它们编号，预定状态全为“未预定”，然后执行输入，一个while循环，如果不符合条件就直接跳出while，执行printTickets()打印出所有的订票信息；

    int main()
    {
    //初始化舱位和票
    for(int i=0;i<25;i++){
        if(i<5){
            seats[i].type='F';
            seats[i].number=i+1;
        }else{
            seats[i].type='E';
            seats[i].number=i+1-5;
        }
        seats[i].isReservation=false;
        tickets[i].seat=seats[i];
        tickets[i].passenger_name=" ";
    }

    cout<<"================================================="<<endl;
    cout<<"               欢迎使用CT票务系统                   "<<endl;
    cout<<"================================================="<<endl;
    cout<<"乘客姓名:";
    while(cin>>name){
            if(name==".")break;
            if(surplusF+surplusE==0){
                cout<<"\n很遗憾所有票已购完！\n";
                break;
            }
            if(check(name)){
                cout<<"\n您已购票,购票信息:\n"<<endl;
                printTickets(name);
            }else{
                cout<<"\n舱位类型 F:一等舱 E:经济舱\n";
                input();
            }
            cout<<"\n乘客姓名:";
    }
    printTickets("");
    return 0;

    }

5，实现效果

<img src="https://github.com/msAndroid/Ticket/screenshot.gif" alt="Drawing"  />

License
--------

    Copyright 2015 florent37, Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

