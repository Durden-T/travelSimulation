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
#include<windows.h>
#include<conio.h>


using namespace std;


#define CostType double
#define Id unsigned int
#define NONE nullptr


enum { minTime = 1, minCost, minCostWithTimeLimited };//旅行策略
enum { CAR, TRAIN, PLANE };//交通方式
const string EXIT ("#exit");
const time_t oneFakeHour(500);

#ifndef TIME_H

#include"time.h"
const Time defaultTime;//Time默认初始化，用于判断

#endif


#endif