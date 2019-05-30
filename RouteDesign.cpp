#include"RouteDesign.h"
#include"graph.h"
#include"log.h"
#include"strategy.h"

RouteDesign::RouteDesign(Graph& _G, Log& _L) :G(_G), L(_L), vertexs(G.getVertexs()) {}

RouteDesign::~RouteDesign()
{
	//ɾ������
	if (strategy)
	{
		delete strategy;
		strategy = nullptr;
	}
}


void RouteDesign::reset()
{
	// ���ڵ�ǰϵͳ�ĵ�ǰ����/ʱ��
	time_t now = time(NULL);
	// �� now ת��Ϊ�ַ�����ʽ,��ӡ��ǰʱ��
	char* dt = ctime(&now);
	//Ĭ�ϵ�ͼΪһ��һ��ѭ�������ô�ʱ���ʽ���ɶ��Խ�ǿ
	cout << "\n��ǰʱ��Ϊ:" << dt << "\n�������������ʱ�䣬����������Ŀ�ĵء�\n��ϵͳʱ���ʽΪ��x y z,��Ϊ��x��yʱz�֡�" << endl;

	string startCityName, endCityName;
	//ѭ����ȡ�û�����,ֱ������Ϸ�
	while (!(cin >> startTime >> startCityName >> endCityName) || !G.hasCity(startCityName) || !G.hasCity(endCityName) || !startTime.valid())
	{
		cout << "�������\n�������������ʱ�䣬����������Ŀ�ĵء�" << endl;
	}

	cout << "��ѡ�����в��ԡ�\n1.����ʱ��\t2.���ٷ���\t3.��ʱ���ٷ���" << endl;
	//ѡ�����в���
	while (!(cin >> mode) || mode < minTime || mode > minCostWithTimeLimited)
	{
		cout << "�������\n������ѡ�����в��ԡ�\n1.����ʱ��\t2.���ٷ���\t3.��ʱ���ٷ���" << endl;
	}

	//����Ҫ����ʱ��
	if (mode != minCostWithTimeLimited)
	{
		//Ĭ��Ϊ�����ʱ��
		limitTime = defaultTime;
	}
	else
	{
		cout << "��������ٵ���ʱ�䡣" << endl;
		while (!(cin >> limitTime))
		{
			cout << "�������\n��������ٵ���ʱ�䡣" << endl;
		}
	}

	cout << "������Ҫ;���ĳ���,#exit�������롣" << endl;
	//;������
	vector<string> passByName;
	//�������������з�������,����:�Ϻ� asd #exit
	bool success;
	do
	{
		string buf;
		//���
		passByName.clear();
		passBy.clear();
		success = true;
		while (cin >> buf && buf != EXIT)
		{
			//�ó����ڵ�ͼ�д���
			if (G.hasCity(buf))
			{
				passByName.push_back(buf);
				passBy.push_back(G.getId(buf));
			}
			else
			{
				//������һ�������ڵĳ���,success��Ϊfalse,����ѭ��
				success = false;
				cout << buf << "�����ڣ�����������Ҫ;���ĳ���,#exit�������롣" << endl;
			}
		}
	} while (!success);

	//������־
	L.reset(startTime, startCityName, endCityName, mode, limitTime, passByName);

	//��ձ���Ľ�����
	path.clear();
	start = G.getId(startCityName);
	end = G.getId(endCityName);
	//����reset˵���ǳ�ʼ����,δ���ļƻ�,lastCost��0
	lastCost = 0;

	//��strategy�Ѵ���,delete
	if (strategy)
	{
		delete strategy;
		strategy = nullptr;
	}

	//�������û�Ҫ��Ĳ��Է��ϵ�strategy
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
	//ί�и�strategyʵ��
	//����·�߷���false
	return strategy->design();
}


void RouteDesign::showResult()
{
	cout << "·�ߣ�" << endl;
	CostType cost = lastCost;
	Time time = startTime;

	//�����;��Ϣ
	for (const Edge* e : path)
	{
		//ʱ��ת�Ƶ�����ʱ��
		time.advanceTo(e->startTime);
		cost += e->cost;
		//��������ߵ���Ϣ
		cout << time << "��\t" << travelTypeTable[e->type] << '\t' << G.getCityName(e->start) << "->" << G.getCityName(e->end) << "\tĿǰ���ѣ�" << cost << "Ԫ" << endl;
		//ʱ��ת�Ƶ�����ʱ��
		time.advanceTo(e->arriveTime);
	}
	cout << "����ʱ�䣺" << time << ",���ѣ�" << cost << "Ԫ��" << endl;

	//����־��д����
	L.showResult(G, lastCost, path);
}

bool RouteDesign::simulation()
{
	cout << "��ʼģ��,��������������мƻ���" << endl;
	CostType cost = lastCost;
	Time time = startTime;
	//�����;��Ϣ
	for (const Edge* e : path)
	{
		//��Ϊ�ߵ�ʱ���ʽ���ǵ����������ͼʱ��ѭ����,��˰ѱߵ�ʱ��ת��Ϊ��ʵ��ʱ��,����t��
		Time t = time;
		t.advanceTo(e->startTime);
		//��ǰδ���ڳ�/�ɻ���,�������ƶ�,����ģ��
		while (time < t)
		{
			//�����ǰ״̬
			cout << time << ":\t��ǰλ��:" << G.getCityName(e->start) << endl;
			Sleep(oneFakeHour);

			//�û�����,Ҫ�ı�ƻ�
			if (_kbhit())
			{
				//���û����µļ���ȡ��,������Ⱦ��������
				while (_kbhit())
				{
					//�����뻺������ȡһ���ַ�
					_getch();
				}
				//��ʱ,��������ӦĬ��Ϊ��ǰ�����ĳ���
				start = e->start;
				//��¼��Ŀǰ�Ļ���,�ۼƵ����ĺ�ļƻ���
				lastCost = cost;
				//����false��ʾ��;�ƻ��ı�
				return false;
			}
			//ģ��ʱ��ǰ��һСʱ
			if (time < t)
			{
				time.addOneHour();
			}
		}
		//time>+t,��time��Ϊt(����ʱ��)
		time = t;
		cost += e->cost;
		//�����ʱ����·����Ϣ
		cout << time << "��\t" << travelTypeTable[e->type] << '\t' << G.getCityName(e->start) << "->" << G.getCityName(e->end) << "\tĿǰ���ѣ�" << cost << "Ԫ" << endl;
		//�ڳ�/�ɻ���,���������ƶ�,��ģ��,ʱ��ֱ��ת�Ƶ�����ʱ��
		time.advanceTo(e->arriveTime);
	}

	cout << "����ʱ�䣺" << time << ",���ѣ�" << cost << "Ԫ��" << endl;
	//��ʾ�ƻ�δ�ı�
	return true;
}

void RouteDesign::change()
{
	cout << "Ĭ�ϳ�������Ϊ��ǰ���У��������������ʱ����Ŀ�ĵء�" << endl;

	string endCityName;
	//ѭ����ȡ�û�����,ֱ������Ϸ�
	while (!(cin >> startTime >> endCityName) || !G.hasCity(endCityName) || !startTime.valid())
	{
		cout << "�������\n�������������ʱ����Ŀ�ĵء�" << endl;
	}

	endCityName = G.getId(endCityName);

	cout << "��ѡ�����в��ԡ�\n1.����ʱ��\t2.���ٷ���\t3.��ʱ���ٷ���" << endl;
	//ѡ�����в���
	while (!(cin >> mode) || mode < minTime || mode > minCostWithTimeLimited)
	{
		cout << "�������\n������ѡ�����в��ԡ�\n1.����ʱ��\t2.���ٷ���\t3.��ʱ���ٷ���" << endl;
	}
	//����Ҫ����ʱ��
	if (mode != minCostWithTimeLimited)
	{
		//Ĭ��Ϊ�����ʱ��
		limitTime = defaultTime;
	}
	else
	{
		cout << "��������ٵ���ʱ�䡣" << endl;
		while (!(cin >> limitTime))
		{
			cout << "�������\n��������ٵ���ʱ�䡣" << endl;
		}
	}

	//;������
	cout << "������Ҫ;���ĳ���,#exit�������롣" << endl;
	//�������������з������� ����:�Ϻ� asd #exit
	bool success;
	vector<string> passByName;
	string name;
	do
	{
		//���
		passByName.clear();
		success = true;
		while (cin >> name && name != EXIT)
		{
			//�ó����ڵ�ͼ�д���
			if (G.hasCity(name))
			{
				passByName.push_back(name);
			}
			else
			{

				//������һ�������ڵĳ���,success��Ϊfalse,����ѭ��
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

	//������־
	L.reset(startTime, G.getCityName(start), endCityName, mode, limitTime, passByName, true);
}