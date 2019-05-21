#include"graph.h"



Graph::Graph(ifstream& file)
{
	//׼����ʱ����
	string buf;
	Id start, end;
	unsigned int type;
	Time startTime, arriveTime;
	CostType cost;
	string startCityName, endCityName;

	//ÿ�ζ�ȡһ��,����#exit�˳�
	while (getline(file, buf) && buf != EXIT)
	{
		//�ָ��� ��ȡ��Ч��Ϣ
		istringstream input(buf);
		//��ȡ������Ƿ�Ϸ�
		if (input >> startCityName >> endCityName >> type >> startTime >> arriveTime >> cost && startTime.valid() && arriveTime.valid() && type >= CAR && type <= PLANE)
		{
			//���ó����Ѵ���,��ȡId,������Ӹó���
			start = hasCity(startCityName) ? getId(startCityName) : addCity(startCityName);
			end = hasCity(endCityName) ? getId(endCityName) : addCity(endCityName);
			//Ϊ�ó�����ӱ�
			getCity(startCityName)->to.emplace_back(start, end, type, startTime, arriveTime, cost);
		}
		else
		{
			cout << "��ͼ�ļ����󣬳��򼴽��˳���" << endl;
			exit(-1);
		}
	}
	//��ȡ��ͼ���,�ر��ļ���
	file.close();
}

Id Graph::addCity(const string& cityName)
{
	//idΪ��ǰ��������
	int id = cities.size();
	//��hash���в���{������,id}
	cities[cityName] = id;
	//��Ӹó���
	vertexs.emplace_back(cityName);
	return id;
}