#ifndef ROUTEDESIGN_H
#define ROUTEDESIGN_H



#include"common.h"


//前向声明,分离编译
struct Edge;
struct Vertex;
class Graph;
class Log;
class Strategy;



class RouteDesign
{
public:
	//Singleton method
	static RouteDesign& Instance(Graph& G, Log& L)
	{
		static RouteDesign Instance(G, L);
		return Instance;
	}

	//从用户处获得新配置
	void reset();

	//把不同旅行策略的相同代码抽出放到design，具体实现委托给strategy执行
	//若没有这样的路径返回false，否则返回true
	bool design();

	//展示结果
	void showResult();

	//开始模拟，若中途要求改变计划返回false，否则返回true
	bool simulation();

	//改变计划
	void change();

protected:
	//Singleton method
	RouteDesign(Graph& _G, Log& _L);
	~RouteDesign();


private:
	//算法策略
	Strategy* strategy;
	Time startTime;
	//要求的限时
	Time limitTime;
	//开始,结束城市的Id
	Id start, end;
	//旅行策略
	unsigned int mode;
	//要求路过的城市
	vector<Id> passBy;
	//结果路径
	vector<const Edge*> path;
	//中途改变计划时记录的上次花费
	CostType lastCost;

	Graph& G;
	Log& L;
	//从G的接口中获取的城市vector,传给strategy使用
	const vector<Vertex>& vertexs;
	//旅行方式表
	vector<string> travelTypeTable{ "汽运", "火车", "飞机" };
};



#endif