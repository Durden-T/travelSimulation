#ifndef LOG_H
#define LOG_H



#include"common.h"
//#include "time.h"


class Time;
class RouteDesign;
class Graph;
struct Edge;


class Log
{
public:
	static Log& Instance()//Singleton
	{
		static Log Instance;
		return Instance;
	}


	void reset(const Time& startTime, const string& startCityName, const string& endCityName, unsigned int mode, const Time& limitTime, vector<string>& passBy,bool changed=false);//��ȡ�µ��û����룬д��log��֪ͨRouteDesign�������

	void update(Graph& G, CostType lastCost,vector<const Edge*>& path);

protected:
	//Singleton
	Log();
	~Log();


private:
	ofstream file;
	vector<string> strategyTable{ "", "����ʱ��", "���ٻ���", "��ʱ���ٻ���" };//���Ա���enum��ϱ���coding
	vector<string> travelTypeTable = { "����", "��", "�ɻ�" };
};



#endif
