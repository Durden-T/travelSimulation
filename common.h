#ifndef  COMMON_H
#define COMMON_H

/*基本完成了各模块的封装设计，根据接口而非实现编程，耦合度低*/

#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<sstream>
#include<queue>
#include <ctime>
#include<windows.h>     //Sleep()
#include<conio.h>       //_kbhit() 非阻塞检测键盘输入


using namespace std;


#define CostType double
#define Id unsigned int
#define NONE nullptr


//旅行策略
enum { minTime = 1, minCost, minCostWithTimeLimited };
//交通方式
enum { CAR, TRAIN, PLANE };
const string EXIT("#exit");
//模拟一小时的实际时间
const time_t oneFakeHour(500);

#ifndef TIME_H

#include"time.h"
//默认初始化的Time，用于判断
const Time defaultTime;

#endif


#endif


/*
1.问题描述
城市之间有三种交通工具（汽车、火车和飞机）相连，某旅客于某一时刻向系统提出旅行要求，系统根据该旅客的要求为其设计一条旅行线路并输出；系统能查询当前时刻旅客所处的地点和状态（停留城市/所在交通工具）。
2.功能需求
城市总数不少于10个
建立汽车、火车和飞机的时刻表（航班表）
有沿途到站及票价信息
不能太简单（不能总只是1班车次相连）
旅客的要求包括：起点、终点、途经某些城市和旅行策略
旅行策略有：
最少费用策略：无时间限制，费用最少即可
最少时间策略：无费用限制，时间最少即可
限时最少费用策略：在规定的时间内所需费用最省
旅行模拟查询系统以时间为轴向前推移，每10秒左右向前推进1个小时(非查询状态的请求不计时)；
不考虑城市内换乘交通工具所需时间
系统时间精确到小时
建立日志文件，对旅客状态变化和键入等信息进行记录
选做：某旅客在旅行途中可更改旅行计划，系统应做相应的操作
*/