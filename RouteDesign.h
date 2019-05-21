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

	void reset(const Time& _startTime, const string& _startCityName, const string& _endCityName, unsigned int _mode, const Time& _limitTime, vector<string>& _passBy);//��������

	//�Ѳ�ͬ���в��Ե���ͬ�������ŵ�design�����ؾ���ʵ��
	//��û��������·������false�����򷵻�true
	bool design();

	//չʾ���������;���ļƻ�����false�����򷵻�true
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
	Time limitTime;//��ʱ
	Id start, end;
	unsigned int mode;//���в���
	vector<Id> passBy;//Ҫ��·���ĳ���
	vector<const Edge*> path;//��ƽ��
	CostType lastCost;//��;�ı�ƻ�ʱ��¼�ϴλ���
	Graph& G;
	Log& L;
	const vector<Vertex>& vertexs;

	vector<string> travelTypeTable = { "����", "��", "�ɻ�" };
};



#endif