#ifndef ROUTEDESIGN_H
#define ROUTEDESIGN_H



#include"common.h"
//#include"graph.h"

class Graph;
struct Edge;
class Log;
struct Vertex;
class Strategy;

class RouteDesign
{
public:
	static RouteDesign& Instance(Graph& G, Log& L)//Singleton method
	{
		static RouteDesign Instance(G, L);
		return Instance;
	}

	void reset(const Time& _startTime, const string& _startCityName, const string& _endCityName, unsigned int _mode, const Time& _limitTime, vector<string>& _passBy);//更新配置

	//把不同旅行策略的相同代码抽出放到design，隐藏具体实现
	//若没有这样的路径返回false，否则返回true
	bool design();

	//展示结果，若中途更改计划返回false，否则返回true
	void showResult();

	bool simulation();

	void change();

protected:
	//Singleton
	RouteDesign(Graph& _G, Log& _L);
	~RouteDesign();


private:
	
	Strategy* strategy;
	Time startTime;
	Time limitTime;//限时
	Id start, end;
	unsigned int mode;//旅行策略
	vector<Id> passBy;//要求路过的城市
	vector<const Edge*> path;//设计结果
	CostType lastCost;//中途改变计划时记录上次花费
	Graph& G;
	Log& L;
	const vector<Vertex>& vertexs;

	vector<string> travelTypeTable = { "汽运", "火车", "飞机" };
};



#endif