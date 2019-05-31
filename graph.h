#ifndef GRAPH_H
#define GRAPH_H



/*
地图格式：
出发城市 抵达城市 交通类型（0汽车，1火车，2飞机） 出发时间（0 y z,意为第0天y时z分） 抵达时间 花费 然后下一行
（在输入地图时，时间中的第x天始终为0）
假设地图一天一循环
*/

#include"common.h"
#include"time.h"


//Edge,Vertex为简单数据聚合，不需要封装
struct Edge
{
	Edge(Id _start = INT_MAX, Id _end = INT_MAX, unsigned int _type = INT_MAX, Time _startTime = defaultTime, Time _arriveTime = defaultTime, CostType _cost = INT_MAX) : start(_start), end(_end), type(_type), startTime(_startTime), arriveTime(_arriveTime), cost(_cost) {}

	//出发城市的id
	Id start;
	//抵达城市的id
	Id end;
	//交通方式
	unsigned int type;
	Time startTime, arriveTime;
	CostType cost;
};


struct Vertex //简单数据聚合，不需要封装
{
	Vertex(string _cityName) :cityName(_cityName) {}

	string cityName;
	// 从此城市出发的边
	vector<Edge> to;
};


class Graph
{
public:
	//Singleton method
	static Graph& Instance(const string& file)
	{
		static Graph Instance(file);
		return Instance;
	}

	//增加城市，返回该城市的Id
	Id addCity(const string& cityName);

	//若已有该城市返回true，否则返回false
	bool hasCity(const string& cityName);

	//返回该城市的Id
	Id getId(const string& cityName);

	//获取该城市的结点指针
	Vertex* getCity(const string& cityName);

	const string& getCityName(Id id);

	//获取vertexs的接口，供RouteDesign使用
	const vector<Vertex>& getVertexs();

protected:
	//Singleton method
	//以文件输入流file初始化Graph
	Graph(const string& file);

	~Graph() = default;
private:
	//所有城市
	vector<Vertex> vertexs;
	//hash表,将城市名映射到Id,全程均使用Id而不是string/引用/指针来标识，减少使用的空间，提高效率
	unordered_map<string, Id> cities;
};



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