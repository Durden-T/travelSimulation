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
//ģ��һСʱ��ʵ��ʱ��
const time_t oneFakeHour(500);

#ifndef TIME_H

#include"time.h"
//Ĭ�ϳ�ʼ����Time�������ж�
const Time defaultTime;

#endif


#endif


/*
1.��������
����֮�������ֽ�ͨ���ߣ��������𳵺ͷɻ���������ĳ�ÿ���ĳһʱ����ϵͳ�������Ҫ��ϵͳ���ݸ��ÿ͵�Ҫ��Ϊ�����һ��������·�������ϵͳ�ܲ�ѯ��ǰʱ���ÿ������ĵص��״̬��ͣ������/���ڽ�ͨ���ߣ���
2.��������
��������������10��
�����������𳵺ͷɻ���ʱ�̱������
����;��վ��Ʊ����Ϣ
����̫�򵥣�������ֻ��1�೵��������
�ÿ͵�Ҫ���������㡢�յ㡢;��ĳЩ���к����в���
���в����У�
���ٷ��ò��ԣ���ʱ�����ƣ��������ټ���
����ʱ����ԣ��޷������ƣ�ʱ�����ټ���
��ʱ���ٷ��ò��ԣ��ڹ涨��ʱ�������������ʡ
����ģ���ѯϵͳ��ʱ��Ϊ����ǰ���ƣ�ÿ10��������ǰ�ƽ�1��Сʱ(�ǲ�ѯ״̬�����󲻼�ʱ)��
�����ǳ����ڻ��˽�ͨ��������ʱ��
ϵͳʱ�侫ȷ��Сʱ
������־�ļ������ÿ�״̬�仯�ͼ������Ϣ���м�¼
ѡ����ĳ�ÿ�������;�пɸ������мƻ���ϵͳӦ����Ӧ�Ĳ���
*/