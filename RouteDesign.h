#ifndef ROUTEDESIGN_H
#define ROUTEDESIGN_H



#include"common.h"


//ǰ������,�������
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

	//���û������������
	void reset();

	//�Ѳ�ͬ���в��Ե���ͬ�������ŵ�design������ʵ��ί�и�strategyִ��
	//��û��������·������false�����򷵻�true
	bool design();

	//չʾ���
	void showResult();

	//��ʼģ�⣬����;Ҫ��ı�ƻ�����false�����򷵻�true
	bool simulation();

	//�ı�ƻ�
	void change();

protected:
	//Singleton method
	RouteDesign(Graph& _G, Log& _L);
	~RouteDesign();


private:
	//�㷨����
	Strategy* strategy;
	Time startTime;
	//Ҫ�����ʱ
	Time limitTime;
	//��ʼ,�������е�Id
	Id start, end;
	//���в���
	unsigned int mode;
	//Ҫ��·���ĳ���
	vector<Id> passBy;
	//���·��
	vector<const Edge*> path;
	//��;�ı�ƻ�ʱ��¼���ϴλ���
	CostType lastCost;

	Graph& G;
	Log& L;
	//��G�Ľӿ��л�ȡ�ĳ���vector,����strategyʹ��
	const vector<Vertex>& vertexs;
	//���з�ʽ��
	vector<string> travelTypeTable{ "����", "��", "�ɻ�" };
};



#endif