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
#include<windows.h>     //Sleep()
#include<conio.h>       //_kbhit() ����������������


using namespace std;


#define CostType double
#define Id unsigned int
#define NONE nullptr


//���в���
enum { minTime = 1, minCost, minCostWithTimeLimited };
//��ͨ��ʽ
enum { CAR, TRAIN, PLANE };
const string EXIT("#exit");
const string DEFAULT_FILE("graph.txt");
//ģ��һСʱ��ʵ��ʱ��
const time_t oneFakeHour(2000);

#ifndef TIME_H

#include"time.h"
//Ĭ�ϳ�ʼ����Time�������ж�
const Time defaultTime;

#endif


#endif