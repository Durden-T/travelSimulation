#ifndef GRAPH_H
#define GRAPH_H



/*
地图格式：
出发城市 抵达城市 交通类型（0汽车，1火车，2飞机） 出发时间（0 y z,意为第0天y时z分） 抵达时间 花费 然后下一行
（在输入地图时，时间中的第x天始终为0，不影响）
假设地图一天一循环
*/

#include"common.h"
#include"time.h"


struct Edge //简单数据聚合，不需要封装
{
	Edge(Id _start = INT_MAX, Id _end = INT_MAX, unsigned int _type = INT_MAX, Time _startTime = defaultTime, Time _arriveTime = defaultTime, CostType _cost = INT_MAX) : start(_start), end(_end), type(_type), startTime(_startTime), arriveTime(_arriveTime), cost(_cost) {}

	Id start;//出发城市的id
	Id end;//抵达城市的id
	unsigned int  type;//交通方式
	Time startTime, arriveTime;
	CostType cost;
};


struct Vertex //简单数据聚合，不需要封装
{
	Vertex(string _cityName) :cityName(_cityName) {}

	string cityName;
	vector<Edge> to;//从此城市出发能到达的城市
};


class Graph
{
public:
	Graph(ifstream& file);

	unsigned int size() const;

	Id addCity(const string& cityName);

	bool hasCity(const string& cityName);

	Id getId(const string& cityName);

	Vertex* getCity(const string& cityName);

	const string& getCityName(Id id);

	const vector<Vertex>& getVertexs();//获取vertexs的接口，供RouteDesign使用


private:
	vector<Vertex> vertexs;//所有城市
	//城市名与ID的hash表，基本全程均使用Id而不是string或引用来标识，减少空间，提高效率
	unordered_map<string, Id> cities;
};



inline unsigned int Graph::size() const
{
	return vertexs.size();
}


inline bool Graph::hasCity(const string& cityName)
{
	return cities.count(cityName);
}


inline Id Graph::getId(const string& cityName)
{
	return cities[cityName];
}


inline const string& Graph::getCityName(Id id)
{
	return vertexs[id].cityName;
}


inline const vector<Vertex>& Graph::getVertexs()
{
	return vertexs;
}



inline Vertex* Graph::getCity(const string& cityName)
{
	return &vertexs[cities[cityName]];
}



#endif