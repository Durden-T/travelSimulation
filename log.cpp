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
		file << "��;�ı�ƻ�" << endl;
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

void Log::showResult(Graph& G, CostType lastCost, vector<const Edge*>& path)
{
	file << "·�ߣ�" << endl;
	CostType cost = lastCost;
	Time time(0, 0, 0);

	//�����;��Ϣ
	for (const Edge* e : path)
	{
		//ʱ��ת������ʱ��
		time.advanceTo(e->startTime);
		cost += e->cost;
		//����ߵ���Ϣ
		file << time << ":\t" << travelTypeTable[e->type] << '\t' << G.getCityName(e->start) << "->" << G.getCityName(e->end) << "\tĿǰ���ѣ�" << cost << "Ԫ" << endl;
		//ʱ��ת������ʱ��
		time.advanceTo(e->arriveTime);
	}

	file << "����ʱ�䣺" << time << ",���ѣ�" << cost << "Ԫ��" << endl;
}

Log::Log()
{
	//�����ļ���Ϊ��ǰʱ��
	time_t now = time(NULL);
	// �� now ת��Ϊ�ַ�����ʽ
	char* dt = ctime(&now);
	string f = dt;
	//ʹ�ļ����Ϸ�
	for (char& c : f)
		if (c == ':')
			c = '.';
	f.pop_back();
	f += ".txt";

	//����־������ļ���
	file.open(f, ios::app);
}
Log::~Log()
{
	//�ر��ļ���
	file.close();
}
