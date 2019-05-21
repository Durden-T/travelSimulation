#ifndef STRATEGY_H
#define STRATEGY_H

#include"common.h"
struct Edge;
struct Vertex;
//#include"RouteDesign.h"
class RouteDesign;

class Strategy
{
public:
	Strategy(const Time& _startTime, Id _start, Id _end, vector<Id>& _passBy, vector<const Edge*>& _path, const vector<Vertex>& _vertexs) :startTime(_startTime), start(_start), end(_end), passBy(_passBy), path(_path), vertexs(_vertexs) {}

	virtual ~Strategy() = default;

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
	using Strategy::Strategy;

	bool design() override;


private:
	Time Dijkstra(Id start, Id end, vector<const Edge*>& path, const Time& startTime);

	Time midDijkstra(vector<const Edge*>& path, const Time& startTime);
};

class MinCost :public Strategy
{
public:
	using Strategy::Strategy;

	bool design() override;


private:
	CostType Dijkstra(Id start, Id end, vector<const Edge*>& path);

	CostType midDijkstra(vector<const Edge*>& path);
};

class MinCostWithTimeLimited :public Strategy
{
public:
	MinCostWithTimeLimited(const Time& _startTime, Id _start, Id _end, vector<Id>& _passBy, vector<const Edge*>& _path, const vector<Vertex>& _vertexs, const Time& _limitTime) :Strategy(_startTime, _start, _end, _passBy, _path, _vertexs), limitTime(_limitTime) {}
	bool design() override;


private:
	CostType Dijkstra(Id start, Id end, vector<const Edge*>& path, vector<Time>& time);

	CostType midDijkstra(vector<const Edge*>& path, vector<Time>& time);

	const Time& limitTime;
};
#endif
