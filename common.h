#ifndef  COMMON_H
#define COMMON_H

/*��������˸�ģ��ķ�װ��ƣ����ݽӿڶ���ʵ�ֱ�̣���϶ȵ�*/

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


enum { minTime = 1, minCost, minCostWithTimeLimited };//���в���
enum { CAR, TRAIN, PLANE };//��ͨ��ʽ
const string EXIT ("#exit");
const time_t oneFakeHour(500);

#ifndef TIME_H

#include"time.h"
const Time defaultTime;//TimeĬ�ϳ�ʼ���������ж�

#endif


#endif