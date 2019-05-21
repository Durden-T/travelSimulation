#include"log.h"
#include"RouteDesign.h"
#include"graph.h"


void Log::reset(const Time& startTime, const string& startCityName, const string& endCityName, unsigned int mode, const Time& limitTime, vector<string>& passBy, bool changed)
{
	// ���ڵ�ǰϵͳ�ĵ�ǰ����/ʱ��
	time_t now = time(NULL);

	// �� now ת��Ϊ�ַ�����ʽ,��ӡ��ǰʱ��
	char* dt = ctime(&now);

	file << dt;
	if (changed)
		file << "��;�ı�ƻ�";
	file << "����ʱ�䣺" << startTime << ",�������У�" << startCityName << ",Ŀ�ĳ��У�" << endCityName << ",���в��ԣ�" << strategyTable[mode] << ",;�����У�";

	//���Ҫ���;������
	if (!passBy.empty())
	{
		for (int i = 0; i < passBy.size() - 1; ++i)
			file << passBy[i] << ',';
		file << passBy.back();
	}
	else
		file << "��";
	if (mode == minCostWithTimeLimited)
		file << ",����ʱ�䣺" << limitTime;
	file << endl;
}

void Log::update(Graph& G, CostType lastCost, vector<const Edge*>& path)
{
	file << "·�ߣ�" << endl;
	CostType cost = lastCost;
	Time time(0, 0, 0);
	//�����;��Ϣ
	for (const Edge* e : path)
	{
		time.advanceTo(e->startTime);
		cost += e->cost;
		file << time << ":\t" << travelTypeTable[e->type] << '\t' << G.getCityName(e->start) << "->" << G.getCityName(e->end) << "\tĿǰ���ѣ�" << cost << "Ԫ" << endl;
		time.advanceTo(e->arriveTime);
	}
	file << "����ʱ�䣺" << time << ",���ѣ�" << cost << "Ԫ��" << endl;
}

Log::Log()
{
	file.open("C:\\travelSimulation\\log.txt", ios::app);
}
Log::~Log()
{
	file.close();
}
