#include"RouteDesign.h"
#include"graph.h"
#include"log.h"
#include"strategy.h"

RouteDesign::RouteDesign(Graph& _G, Log& _L) :G(_G), L(_L), vertexs(G.getVertexs()) {}

RouteDesign::~RouteDesign()
{
	if (strategy)
		delete strategy;
}


void RouteDesign::reset(const Time& _startTime, const string& _startCityName, const string& _endCityName, unsigned int _mode, const Time& _limitTime, vector<string>& _passBy)
{
	L.reset(_startTime, _startCityName, _endCityName, _mode, _limitTime, _passBy);//配置日志

	startTime = _startTime;
	start = G.getId(_startCityName);
	end = G.getId(_endCityName);
	mode = _mode;
	limitTime = _limitTime;
	lastCost = 0;

	path.clear();
	passBy.clear();

	for (string& s : _passBy)
		passBy.push_back(G.getId(s));

	if (strategy)
		delete strategy;
	if (mode == minTime)
	{
		strategy = new MinTime(startTime, start, end, passBy, path, vertexs);
	}
	else if (mode == minCost)
	{
		strategy = new MinCost(startTime, start, end, passBy, path, vertexs);
	}
	else
	{
		strategy = new MinCostWithTimeLimited(startTime, start, end, passBy, path, vertexs, limitTime);
	}
}


bool RouteDesign::design()
{
	if (!strategy->design())
		return false;
	return true;
}


void RouteDesign::showResult()
{
	cout << "路线：" << endl;
	CostType cost = lastCost;
	Time time = startTime;
	//输出沿途信息
	for (const Edge* e : path)
	{
		time.advanceTo(e->startTime);
		cost += e->cost;
		cout << time << "：\t" << travelTypeTable[e->type] << '\t' << G.getCityName(e->start) << "->" << G.getCityName(e->end) << "\t目前花费：" << cost << "元" << endl;
		time.advanceTo(e->arriveTime);
	}
	cout << "到达时间：" << time << ",花费：" << cost << "元。" << endl;
	L.update(G, lastCost, path);
}

bool RouteDesign::simulation()
{
	cout << "开始模拟,按任意键更改旅行计划。" << endl;
	CostType cost = lastCost;
	Time time = startTime;
	//输出沿途信息
	for (const Edge* e : path)
	{
		Time t = time;
		t.advanceTo(e->startTime);
		while (time < t)
		{
			cout << time << ":\t当前位置:" << G.getCityName(e->start) << endl;
			Sleep(oneFakeHour);

			if (_kbhit())
			{
				while (_kbhit())
				{
					_getch();
				}
				start = e->start;
				lastCost = cost;
				return false;
			}
			if (time < t)
			{
				time.addOneHour();
			}
		}

		time = t;
		cost += e->cost;
		cout << time << "：\t" << travelTypeTable[e->type] << '\t' << G.getCityName(e->start) << "->" << G.getCityName(e->end) << "\t目前花费：" << cost << "元" << endl;
		time.advanceTo(e->arriveTime);
	}
	cout << "到达时间：" << time << ",花费：" << cost << "元。" << endl;
	return true;
}

void RouteDesign::change()
{
	cout << "默认出发城市为当前城市，请依次输入出发时间与目的地。" << endl;
	string endCityName;
	while (!(cin >> startTime >> endCityName) || !G.hasCity(endCityName) || !startTime.valid())
	{
		cout << "输入错误。\n请重新输入出发时间与目的地。" << endl;
	}
	endCityName = G.getId(endCityName);

	cout << "请选择旅行策略。\n1.最少时间\t2.最少费用\t3.限时最少费用" << endl;
	while (!(cin >> mode) || mode < minTime || mode > minCostWithTimeLimited)//选择旅行策略
	{
		cout << "输入错误。\n请重新选择旅行策略。\n1.最少时间\t2.最少费用\t3.限时最少费用" << endl;
	}
	if (mode != minCostWithTimeLimited)//不需要限制时间
		limitTime = defaultTime;//默认为无穷大时间
	else
	{
		cout << "请输入最迟到达时间。" << endl;
		while (!(cin >> limitTime))
		{
			cout << "输入错误。\n请输入最迟到达时间。" << endl;
		}
	}


	cout << "请输入要途经的城市,#exit结束输入。" << endl;//途经城市
	bool success;//控制连续输入中发生错误 比如:上海 asd #exit
	vector<string> passByName;
	string name;
	do
	{
		passByName.clear();
		success = true;
		while (cin >> name && name != EXIT)
		{
			if (G.hasCity(name))
			{
				passByName.push_back(name);
			}
			else
			{
				success = false;
				cout << name << "不存在，请重新输入要途经的城市,#exit结束输入。" << endl;
			}
		}
	} while (!success);

	passBy.clear();
	for (const string& name : passByName)
	{
		passBy.push_back(G.getId(name));
	}

	path.clear();

	if (strategy)
		delete strategy;
	if (mode == minTime)
	{
		strategy = new MinTime(startTime, start, end, passBy, path, vertexs);
	}
	else if (mode == minCost)
	{
		strategy = new MinCost(startTime, start, end, passBy, path, vertexs);
	}
	else
	{
		strategy = new MinCostWithTimeLimited(startTime, start, end, passBy, path, vertexs, limitTime);
	}

	L.reset(startTime, G.getCityName(start), endCityName, mode, limitTime, passByName,true);//配置日志
}
