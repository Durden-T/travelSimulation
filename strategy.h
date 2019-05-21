#ifndef STRATEGY_H
#define STRATEGY_H

#include"common.h"



//前向声明,分离编译
struct Edge;
struct Vertex;
class RouteDesign;



class Strategy
{
public:
	Strategy(const Time& _startTime, Id _start, Id _end, vector<Id>& _passBy, vector<const Edge*>& _path, const vector<Vertex>& _vertexs) :startTime(_startTime), start(_start), end(_end), passBy(_passBy), path(_path), vertexs(_vertexs) {}

	virtual ~Strategy() = default;

	//由不同的继承类实现
	virtual bool design() = 0;

protected:
	const Time& startTime;
	Id start, end;
	vector<Id>& passBy;
	vector<const Edge*>& path;
	const vector<Vertex>& vertexs;
};

class MinTime :public Strategy
{
public:
	//未添加数据成员,使用Strategy的构造函数
	using Strategy::Strategy;

	bool design() override;


private:
	//基于时间比较的Dijkstra算法,返回start到end的最短时间,并把路径存到path中,若无结果返回defaultTime
	Time Dijkstra(Id start, Id end, vector<const Edge*>& path, const Time& startTime);

	//基于时间比较,将passBy中Id按顺序相连的算法,返回经过passBy全部城市的最短时间,并把路径存到path中,若无结果返回defaultTime
	Time midDijkstra(vector<const Edge*>& path, const Time& startTime);
};

class MinCost :public Strategy
{
public:
	//未添加数据成员,使用Strategy的构造函数
	using Strategy::Strategy;

	bool design() override;


private:
	//基于花费比较的Dijkstra算法,返回start到end的最少花费,并把路径存到path中,若无结果返回INT_MAX
	CostType Dijkstra(Id start, Id end, vector<const Edge*>& path);

	//基于花费比较,将passBy中Id按顺序相连的算法,返回经过passBy全部城市的最少花费,并把路径存到path中,若无结果返回INT_MAX
	CostType midDijkstra(vector<const Edge*>& path);
};

class MinCostWithTimeLimited :public Strategy
{
public:
	//增加了limitTime,重写构造函数
	MinCostWithTimeLimited(const Time& _startTime, Id _start, Id _end, vector<Id>& _passBy, vector<const Edge*>& _path, const vector<Vertex>& _vertexs, const Time& _limitTime) :Strategy(_startTime, _start, _end, _passBy, _path, _vertexs), limitTime(_limitTime) {}

	bool design() override;


private:
	//基于花费比较的,有限时的Dijkstra算法,返回start到end的最少花费,并把路径存到path中,把每一步的到达时间存入time中,若无结果返回INT_MAX
	CostType Dijkstra(Id start, Id end, vector<const Edge*>& path, vector<Time>& time);

	//基于花费比较,有限时的将passBy中Id按顺序相连的算法,返回经过passBy全部城市的最少花费,并把路径存到path中,把每一步的到达时间存入time中,若无结果返回INT_MAX
	CostType midDijkstra(vector<const Edge*>& path, vector<Time>& time);

	const Time& limitTime;
};
#endif
