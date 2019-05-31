#include"log.h"
#include"RouteDesign.h"
#include"graph.h"


void Log::reset(const Time& startTime, const string& startCityName, const string& endCityName, unsigned int mode, const Time& limitTime, vector<string>& passBy, bool changed)
{
	// 基于当前系统的当前日期/时间
	time_t now = time(NULL);
	// 把 now 转换为字符串形式,打印当前时间
	char* dt = ctime(&now);
	file << dt;
	if (changed)
		file << "中途改变计划" << endl;
	file << "出发时间：" << startTime << ",出发城市：" << startCityName << ",目的城市：" << endCityName << ",旅行策略：" << strategyTable[mode] << ",途径城市：";

	//输出要求的途经城市
	if (!passBy.empty())
	{
		for (int i = 0; i < passBy.size() - 1; ++i)
			file << passBy[i] << ',';
		file << passBy.back();
	}
	else
		file << "无";
	if (mode == minCostWithTimeLimited)
		file << ",限制时间：" << limitTime;

	file << endl;
}

void Log::showResult(Graph& G, CostType lastCost, vector<const Edge*>& path)
{
	file << "路线：" << endl;
	CostType cost = lastCost;
	Time time(0, 0, 0);

	//输出沿途信息
	for (const Edge* e : path)
	{
		//时间转到出发时间
		time.advanceTo(e->startTime);
		cost += e->cost;
		//输出边的信息
		file << time << ":\t" << travelTypeTable[e->type] << '\t' << G.getCityName(e->start) << "->" << G.getCityName(e->end) << "\t目前花费：" << cost << "元" << endl;
		//时间转到到达时间
		time.advanceTo(e->arriveTime);
	}

	file << "到达时间：" << time << ",花费：" << cost << "元。" << endl;
}

Log::Log()
{
	//设置文件名为当前时间
	time_t now = time(NULL);
	// 把 now 转换为字符串形式
	char* dt = ctime(&now);
	string f = dt;
	//使文件名合法
	for (char& c : f)
		if (c == ':')
			c = '.';
	f.pop_back();
	f += ".txt";

	//打开日志的输出文件流
	file.open(f, ios::app);
}
Log::~Log()
{
	//关闭文件流
	file.close();
}
