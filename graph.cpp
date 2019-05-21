#include"graph.h"



Graph::Graph(ifstream& file)
{
	//准备临时变量
	string buf;
	Id start, end;
	unsigned int type;
	Time startTime, arriveTime;
	CostType cost;
	string startCityName, endCityName;

	//每次读取一行,输入#exit退出
	while (getline(file, buf) && buf != EXIT)
	{
		//分割行 获取有效信息
		istringstream input(buf);
		//读取并检测是否合法
		if (input >> startCityName >> endCityName >> type >> startTime >> arriveTime >> cost && startTime.valid() && arriveTime.valid() && type >= CAR && type <= PLANE)
		{
			//若该城市已存在,获取Id,否则添加该城市
			start = hasCity(startCityName) ? getId(startCityName) : addCity(startCityName);
			end = hasCity(endCityName) ? getId(endCityName) : addCity(endCityName);
			//为该城市添加边
			getCity(startCityName)->to.emplace_back(start, end, type, startTime, arriveTime, cost);
		}
		else
		{
			cout << "地图文件错误，程序即将退出。" << endl;
			exit(-1);
		}
	}
	//读取地图完成,关闭文件流
	file.close();
}

Id Graph::addCity(const string& cityName)
{
	//id为当前城市数量
	int id = cities.size();
	//在hash表中插入{城市名,id}
	cities[cityName] = id;
	//添加该城市
	vertexs.emplace_back(cityName);
	return id;
}