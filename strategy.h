#ifndef STRATEGY_H
#define STRATEGY_H

#include"common.h"



//ǰ������,�������
struct Edge;
struct Vertex;
class RouteDesign;



class Strategy
{
public:
	Strategy(const Time& _startTime, Id _start, Id _end, vector<Id>& _passBy, vector<const Edge*>& _path, const vector<Vertex>& _vertexs) :startTime(_startTime), start(_start), end(_end), passBy(_passBy), path(_path), vertexs(_vertexs) {}

	virtual ~Strategy() = default;

	//�ɲ�ͬ�ļ̳���ʵ��
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
	//δ������ݳ�Ա,ʹ��Strategy�Ĺ��캯��
	using Strategy::Strategy;

	bool design() override;


private:
	//����ʱ��Ƚϵ�Dijkstra�㷨,����start��end�����ʱ��,����·���浽path��,���޽������defaultTime
	Time Dijkstra(Id start, Id end, vector<const Edge*>& path, const Time& startTime);

	//����ʱ��Ƚ�,��passBy��Id��˳���������㷨,���ؾ���passByȫ�����е����ʱ��,����·���浽path��,���޽������defaultTime
	Time midDijkstra(vector<const Edge*>& path, const Time& startTime);
};

class MinCost :public Strategy
{
public:
	//δ������ݳ�Ա,ʹ��Strategy�Ĺ��캯��
	using Strategy::Strategy;

	bool design() override;


private:
	//���ڻ��ѱȽϵ�Dijkstra�㷨,����start��end�����ٻ���,����·���浽path��,���޽������INT_MAX
	CostType Dijkstra(Id start, Id end, vector<const Edge*>& path);

	//���ڻ��ѱȽ�,��passBy��Id��˳���������㷨,���ؾ���passByȫ�����е����ٻ���,����·���浽path��,���޽������INT_MAX
	CostType midDijkstra(vector<const Edge*>& path);
};

class MinCostWithTimeLimited :public Strategy
{
public:
	//������limitTime,��д���캯��
	MinCostWithTimeLimited(const Time& _startTime, Id _start, Id _end, vector<Id>& _passBy, vector<const Edge*>& _path, const vector<Vertex>& _vertexs, const Time& _limitTime) :Strategy(_startTime, _start, _end, _passBy, _path, _vertexs), limitTime(_limitTime) {}

	bool design() override;


private:
	//���ڻ��ѱȽϵ�,����ʱ��Dijkstra�㷨,����start��end�����ٻ���,����·���浽path��,��ÿһ���ĵ���ʱ�����time��,���޽������INT_MAX
	CostType Dijkstra(Id start, Id end, vector<const Edge*>& path, vector<Time>& time);

	//���ڻ��ѱȽ�,����ʱ�Ľ�passBy��Id��˳���������㷨,���ؾ���passByȫ�����е����ٻ���,����·���浽path��,��ÿһ���ĵ���ʱ�����time��,���޽������INT_MAX
	CostType midDijkstra(vector<const Edge*>& path, vector<Time>& time);

	const Time& limitTime;
};
#endif
