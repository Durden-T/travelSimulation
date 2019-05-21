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


	void reset(const Time& startTime, const string& startCityName, const string& endCityName, unsigned int mode, const Time& limitTime, vector<string>& passBy,bool changed=false);//获取新的用户输入，写入log并通知RouteDesign进行设计

	void update(Graph& G, CostType lastCost,vector<const Edge*>& path);

protected:
	//Singleton
	Log();
	~Log();


private:
	ofstream file;
	vector<string> strategyTable{ "", "最少时间", "最少花费", "限时最少花费" };//策略表，与enum结合便于coding
	vector<string> travelTypeTable = { "汽运", "火车", "飞机" };
};



#endif
