#ifndef LOG_H
#define LOG_H



#include"common.h"

//ǰ������,�������
struct Edge;
class Graph;


//���ǵ�����ÿͣ�ÿ�δ�����־ʱ����־��Ϊ����ʱ��
class Log
{
public:
	//Singleton method
	static Log& Instance()
	{
		static Log Instance;
		return Instance;
	}

	//���û��µ�����д��log,changed����Ĭ��Ϊfalse,��Ϊtrue��־��ε�reset����;�ı��
	void reset(const Time& startTime, const string& startCityName, const string& endCityName, unsigned int mode, const Time& limitTime, vector<string>& passBy, bool changed = false);

	//���ǵ�������;�������ı�,������lastCost,���ʱcost��lastCost��ʼ����
	void showResult(Graph& G, CostType lastCost, vector<const Edge*>& path);

protected:
	//Singleton method
	Log();
	~Log();


private:
	//�ļ������
	ofstream file;
	//���Ա�,��enum��ϱ���coding,��߿ɶ���
	vector<string> strategyTable{ "", "����ʱ��", "���ٻ���", "��ʱ���ٻ���" };
	vector<string> travelTypeTable{ "����", "��", "�ɻ�" };
};



#endif
