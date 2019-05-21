#include"graph.h"



Graph::Graph(ifstream& file)
{
	//准备临时变量
	string buf;
	Id startId, endId;
	unsigned int type;
	Time startTime, arriveTime;
	CostType cost;
	string startCityName, endCityName;


	while (getline(file, buf) && buf != EXIT)//每次读取一行,输入#exit退出
	{
		istringstream input(buf);//分割行 获取有效信息

		if (input >> startCityName >> endCityName >> type >> startTime >> arriveTime >> cost && startTime.valid() && arriveTime.valid() && type >= CAR && type <= PLANE)//读取并检测是否合法
		{
			startId = hasCity(startCityName) ? getId(startCityName) : addCity(startCityName);
			endId = hasCity(endCityName) ? getId(endCityName) : addCity(endCityName);
			getCity(startCityName)->to.emplace_back(startId, endId, type, startTime, arriveTime, cost);
		}
		else
		{
			//cout << buf << endl;
			cout << "地图文件错误，程序即将退出。" << endl;
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