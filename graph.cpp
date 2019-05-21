#include"graph.h"



Graph::Graph(ifstream& file)
{
	//׼����ʱ����
	string buf;
	Id startId, endId;
	unsigned int type;
	Time startTime, arriveTime;
	CostType cost;
	string startCityName, endCityName;


	while (getline(file, buf) && buf != EXIT)//ÿ�ζ�ȡһ��,����#exit�˳�
	{
		istringstream input(buf);//�ָ��� ��ȡ��Ч��Ϣ

		if (input >> startCityName >> endCityName >> type >> startTime >> arriveTime >> cost && startTime.valid() && arriveTime.valid() && type >= CAR && type <= PLANE)//��ȡ������Ƿ�Ϸ�
		{
			startId = hasCity(startCityName) ? getId(startCityName) : addCity(startCityName);
			endId = hasCity(endCityName) ? getId(endCityName) : addCity(endCityName);
			getCity(startCityName)->to.emplace_back(startId, endId, type, startTime, arriveTime, cost);
		}
		else
		{
			//cout << buf << endl;
			cout << "��ͼ�ļ����󣬳��򼴽��˳���" << endl;
			exit(-1);
		}
	}
}

Id Graph::addCity(const string& cityName)
{
	int id = cities.size();
	cities[cityName] = id;
	vertexs.emplace_back(cityName);
	return id;
}