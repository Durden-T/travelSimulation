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
const string DEFAULT_FILE("graph.txt");
//模拟一小时的实际时间
const time_t oneFakeHour(2000);

#ifndef TIME_H

#include"time.h"
//默认初始化的Time，用于判断
const Time defaultTime;

#endif


#endif