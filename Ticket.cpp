#include<iostream>
using namespace std;

//定义全局变量，舱位，票，各类型舱位剩余数,便于其它函数全局访问
int surplusF=5;
int surplusE=20;

int flag=0;
char seat_type;
int seatNumber;
string name;

//座位
struct Seat{
    char type;
    int number;
    bool isReservation;
}seats[25];

//票
struct Ticket{
    Seat seat;
    string passenger_name;
}tickets[25];

bool check(string name);//检测是否已购票
void input();//用于执行输入
void printSeat(char seatType);//显示剩余座位
void reservation(string name,int seatNumber,char seatType);//购票
void printTickets(string name);//显示已购票信息
void printError();//显示输入不合法

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

bool check(string name)
{
    for(int i=0;i<25;i++){
        if(name==tickets[i].passenger_name)
            return true;
    }
    return false;
}

//负责输入，之所以单独写成函数，是因为非法输入的时候需要递归调用
void input()
{
    flag=0;
    cout<<"\n舱位类型(F/E):";
    cin>>seat_type;
    cin.get();
    switch(seat_type){
        case 'F':
            if(surplusF>0)
                cout<<"\n可选座位号:";
            printSeat('F');
            if(flag!=0)break;
            cin>>seatNumber;
            cin.get();
            reservation(name,seatNumber,'F');
            break;
        case 'E':
            if(surplusE>0)
                cout<<"\n可选座位号:";
            printSeat('E');
            if(flag!=0)break;
            cin>>seatNumber;
            cin.get();
            reservation(name,seatNumber,'E');
            break;
        default:
            printError();
            input();
            break;
        }
}

//输出可选的座位号
void printSeat(char seatType)
{
    int full=0;
    for(int i=0;i<25;i++){
        if(seats[i].isReservation==false){
            if(seatType=='F'){
                if(surplusF==0){
                    cout<<"\n此舱位全部订完，请重新选择舱位类型:\n";
                    full++;
                    break;
                }
                cout<<seats[i].number<<" ";
                if(i==4) break;
            }
            if(seatType=='E'){
                if(surplusE==0){
                    cout<<"\n此舱位全部订完，请重新选择舱位类型:\n";
                    full++;
                    break;
                }
                if(i>4){
                    cout<<seats[i].number<<" ";
                }
            }
        }
    }
    if(full==0){
        cout<<"\n";
        cout<<"\n座位号:";
    }else{
        input();
        flag++;
    }

}

//输入无效
void printError()
{
    cout<<"\n输入无效！"<<endl;
}

//购票，即改变seats tickets 属性值
void reservation(string name,int seatNumber,char seatType)
{
    if(seatNumber<1&&seatNumber>20){
        printError();
    }
    else{
        switch(seatType){
            case 'F':
                if(seatNumber>0&&seatNumber<6){
                    if(seats[seatNumber-1].isReservation==false){
                        seats[seatNumber-1].isReservation=true;
                        tickets[seatNumber-1].seat=seats[seatNumber-1];
                        tickets[seatNumber-1].passenger_name=name;
                        surplusF--;
                        cout<<"\n 恭喜 "+name+" 订票成功!"<<endl;
                        break;
                    }else{
                        printError();
                        //input();
                    }
                }else
                    printError();
                break;
            case 'E':
                if(seatNumber>0&&seatNumber<=20){
                    if(seats[seatNumber+4].isReservation==false){
                        seats[seatNumber+4].isReservation=true;
                        tickets[seatNumber+4].seat=seats[seatNumber+4];
                        tickets[seatNumber+4].passenger_name=name;
                        surplusE--;
                        cout<<"\n 恭喜 "+name+" 订票成功!"<<endl;
                        break;
                    }else{
                        printError();
                    }
                }else
                    printError();
                break;
        }
    }
}

void printTickets(string name)
{
    cout<<"================================================="<<endl;
    cout<<"               订  票  信  息                    "<<endl;
    cout<<"================================================="<<endl;
    cout<<"  舱位类型        座位号        乘客姓名         "<<endl;
    cout<<"\n";
    for(int i=0;i<25;i++){
        if(name==tickets[i].passenger_name){
                switch(tickets[i].seat.type){
                case 'F':
                    cout<<"  头等舱           ";
                    break;
                case 'E':
                    cout<<"  经济舱           ";
                    break;
                }
            cout<<tickets[i].seat.number<<"             "<<tickets[i].passenger_name<<endl;
            cout<<"\n";
            break;
        }
        else if(name==""){
            if(tickets[i].seat.isReservation==true){
            switch(tickets[i].seat.type){
                case 'F':
                    cout<<"  头等舱           ";
                    break;
                case 'E':
                    cout<<"  经济舱           ";
                    break;
            }
            cout<<tickets[i].seat.number<<"             "<<tickets[i].passenger_name<<endl;
            cout<<"\n";
            }
        }
    }
    cout<<"================================================="<<endl;
}
