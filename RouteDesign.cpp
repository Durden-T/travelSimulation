#include"RouteDesign.h"
#include"graph.h"
#include"log.h"
#include"strategy.h"

RouteDesign::RouteDesign(Graph& _G, Log& _L) :G(_G), L(_L), vertexs(G.getVertexs()) {}

RouteDesign::~RouteDesign()
{
	//删除策略
	if (strategy)
	{
		delete strategy;
		strategy = nullptr;
	}
}


void RouteDesign::reset()
{
	// 基于当前系统的当前日期/时间
	time_t now = time(NULL);
	// 把 now 转换为字符串形式,打印当前时间
	char* dt = ctime(&now);
	//默认地图为一天一个循环，采用此时间格式，可读性较强
	cout << "\n当前时间为:" << dt << "\n请依次输入出发时间，出发城市与目的地。\n本系统时间格式为：x y z,意为第x天y时z分。" << endl;

	string startCityName, endCityName;
	//循环获取用户输入,直至输入合法
	while (!(cin >> startTime >> startCityName >> endCityName) || !G.hasCity(startCityName) || !G.hasCity(endCityName) || !startTime.valid())
	{
		cout << "输入错误。\n请重新输入出发时间，出发城市与目的地。" << endl;
	}

	cout << "请选择旅行策略。\n1.最少时间\t2.最少费用\t3.限时最少费用" << endl;
	//选择旅行策略
	while (!(cin >> mode) || mode < minTime || mode > minCostWithTimeLimited)
	{
		cout << "输入错误。\n请重新选择旅行策略。\n1.最少时间\t2.最少费用\t3.限时最少费用" << endl;
	}

	//不需要限制时间
	if (mode != minCostWithTimeLimited)
	{
		//默认为无穷大时间
		limitTime = defaultTime;
	}
	else
	{
		cout << "请输入最迟到达时间。" << endl;
		while (!(cin >> limitTime))
		{
			cout << "输入错误。\n请输入最迟到达时间。" << endl;
		}
	}

	cout << "请输入要途经的城市,#exit结束输入。" << endl;
	//途经城市
	vector<string> passByName;
	//控制连续输入中发生错误,例如:上海 asd #exit
	bool success;
	do
	{
		string buf;
		//清空
		passByName.clear();
		passBy.clear();
		success = true;
		while (cin >> buf && buf != EXIT)
		{
			//该城市在地图中存在
			if (G.hasCity(buf))
			{
				passByName.push_back(buf);
				passBy.push_back(G.getId(buf));
			}
			else
			{
				//输入了一个不存在的城市,success设为false,继续循环
				success = false;
				cout << buf << "不存在，请重新输入要途经的城市,#exit结束输入。" << endl;
			}
		}
	} while (!success);

	//配置日志
	L.reset(startTime, startCityName, endCityName, mode, limitTime, passByName);

	//清空保存的结果结果
	path.clear();
	start = G.getId(startCityName);
	end = G.getId(endCityName);
	//调用reset说明是初始运行,未更改计划,lastCost赋0
	lastCost = 0;

	//若strategy已存在,delete
	if (strategy)
	{
		delete strategy;
		strategy = nullptr;
	}

	//创造与用户要求的策略符合的strategy
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
	//委托给strategy实现
	//若无路线返回false
	return strategy->design();
}


void RouteDesign::showResult()
{
	cout << "路线：" << endl;
	CostType cost = lastCost;
	Time time = startTime;

	//输出沿途信息
	for (const Edge* e : path)
	{
		//时间转移到出发时间
		time.advanceTo(e->startTime);
		cost += e->cost;
		//输出这条边的信息
		cout << time << "：\t" << travelTypeTable[e->type] << '\t' << G.getCityName(e->start) << "->" << G.getCityName(e->end) << "\t目前花费：" << cost << "元" << endl;
		//时间转移到到达时间
		time.advanceTo(e->arriveTime);
	}
	cout << "到达时间：" << time << ",花费：" << cost << "元。" << endl;

	//在日志中写入结果
	L.showResult(G, lastCost, path);
}

bool RouteDesign::simulation()
{
	cout << "开始模拟,按任意键更改旅行计划。" << endl;
	CostType cost = lastCost;
	Time time = startTime;
	//输出沿途信息
	for (const Edge* e : path)
	{
		//因为边的时间格式都是当天出发（地图时间循环）,因此把边的时间转化为现实的时间,存在t中
		Time t = time;
		t.advanceTo(e->startTime);
		//当前未处于车/飞机上,可自由移动,可以模拟
		while (time < t)
		{
			//输出当前状态
			cout << time << ":\t当前位置:" << G.getCityName(e->start) << endl;
			Sleep(oneFakeHour);

			//用户按键,要改变计划
			if (_kbhit())
			{
				//将用户按下的键读取掉,避免污染后续输入
				while (_kbhit())
				{
					//从输入缓冲区读取一个字符
					_getch();
				}
				//此时,出发城市应默认为当前所处的城市
				start = e->start;
				//记录到目前的花费,累计到更改后的计划中
				lastCost = cost;
				//返回false表示中途计划改变
				return false;
			}
			//模拟时间前进一小时
			if (time < t)
			{
				time.addOneHour();
			}
		}
		//time>+t,将time改为t(出发时间)
		time = t;
		cost += e->cost;
		//输出此时这条路径信息
		cout << time << "：\t" << travelTypeTable[e->type] << '\t' << G.getCityName(e->start) << "->" << G.getCityName(e->end) << "\t目前花费：" << cost << "元" << endl;
		//在车/飞机上,不能自由移动,不模拟,时间直接转移到到达时间
		time.advanceTo(e->arriveTime);
	}

	cout << "到达时间：" << time << ",花费：" << cost << "元。" << endl;
	//表示计划未改变
	return true;
}

void RouteDesign::change()
{
	cout << "默认出发城市为当前城市，请依次输入出发时间与目的地。" << endl;

	string endCityName;
	//循环获取用户输入,直至输入合法
	while (!(cin >> startTime >> endCityName) || !G.hasCity(endCityName) || !startTime.valid())
	{
		cout << "输入错误。\n请重新输入出发时间与目的地。" << endl;
	}

	endCityName = G.getId(endCityName);

	cout << "请选择旅行策略。\n1.最少时间\t2.最少费用\t3.限时最少费用" << endl;
	//选择旅行策略
	while (!(cin >> mode) || mode < minTime || mode > minCostWithTimeLimited)
	{
		cout << "输入错误。\n请重新选择旅行策略。\n1.最少时间\t2.最少费用\t3.限时最少费用" << endl;
	}
	//不需要限制时间
	if (mode != minCostWithTimeLimited)
	{
		//默认为无穷大时间
		limitTime = defaultTime;
	}
	else
	{
		cout << "请输入最迟到达时间。" << endl;
		while (!(cin >> limitTime))
		{
			cout << "输入错误。\n请输入最迟到达时间。" << endl;
		}
	}

	//途经城市
	cout << "请输入要途经的城市,#exit结束输入。" << endl;
	//控制连续输入中发生错误 比如:上海 asd #exit
	bool success;
	vector<string> passByName;
	string name;
	do
	{
		//清空
		passByName.clear();
		success = true;
		while (cin >> name && name != EXIT)
		{
			//该城市在地图中存在
			if (G.hasCity(name))
			{
				passByName.push_back(name);
			}
			else
			{

				//输入了一个不存在的城市,success设为false,继续循环
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

	//配置日志
	L.reset(startTime, G.getCityName(start), endCityName, mode, limitTime, passByName, true);
}