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
	L.reset(_startTime, _startCityName, _endCityName, _mode, _limitTime, _passBy);//������־

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
	cout << "·�ߣ�" << endl;
	CostType cost = lastCost;
	Time time = startTime;
	//�����;��Ϣ
	for (const Edge* e : path)
	{
		time.advanceTo(e->startTime);
		cost += e->cost;
		cout << time << "��\t" << travelTypeTable[e->type] << '\t' << G.getCityName(e->start) << "->" << G.getCityName(e->end) << "\tĿǰ���ѣ�" << cost << "Ԫ" << endl;
		time.advanceTo(e->arriveTime);
	}
	cout << "����ʱ�䣺" << time << ",���ѣ�" << cost << "Ԫ��" << endl;
	L.update(G, lastCost, path);
}

bool RouteDesign::simulation()
{
	cout << "��ʼģ��,��������������мƻ���" << endl;
	CostType cost = lastCost;
	Time time = startTime;
	//�����;��Ϣ
	for (const Edge* e : path)
	{
		Time t = time;
		t.advanceTo(e->startTime);
		while (time < t)
		{
			cout << time << ":\t��ǰλ��:" << G.getCityName(e->start) << endl;
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
		cout << time << "��\t" << travelTypeTable[e->type] << '\t' << G.getCityName(e->start) << "->" << G.getCityName(e->end) << "\tĿǰ���ѣ�" << cost << "Ԫ" << endl;
		time.advanceTo(e->arriveTime);
	}
	cout << "����ʱ�䣺" << time << ",���ѣ�" << cost << "Ԫ��" << endl;
	return true;
}

void RouteDesign::change()
{
	cout << "Ĭ�ϳ�������Ϊ��ǰ���У��������������ʱ����Ŀ�ĵء�" << endl;
	string endCityName;
	while (!(cin >> startTime >> endCityName) || !G.hasCity(endCityName) || !startTime.valid())
	{
		cout << "�������\n�������������ʱ����Ŀ�ĵء�" << endl;
	}
	endCityName = G.getId(endCityName);

	cout << "��ѡ�����в��ԡ�\n1.����ʱ��\t2.���ٷ���\t3.��ʱ���ٷ���" << endl;
	while (!(cin >> mode) || mode < minTime || mode > minCostWithTimeLimited)//ѡ�����в���
	{
		cout << "�������\n������ѡ�����в��ԡ�\n1.����ʱ��\t2.���ٷ���\t3.��ʱ���ٷ���" << endl;
	}
	if (mode != minCostWithTimeLimited)//����Ҫ����ʱ��
		limitTime = defaultTime;//Ĭ��Ϊ�����ʱ��
	else
	{
		cout << "��������ٵ���ʱ�䡣" << endl;
		while (!(cin >> limitTime))
		{
			cout << "�������\n��������ٵ���ʱ�䡣" << endl;
		}
	}


	cout << "������Ҫ;���ĳ���,#exit�������롣" << endl;//;������
	bool success;//�������������з������� ����:�Ϻ� asd #exit
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
				cout << name << "�����ڣ�����������Ҫ;���ĳ���,#exit�������롣" << endl;
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

	L.reset(startTime, G.getCityName(start), endCityName, mode, limitTime, passByName,true);//������־
}
