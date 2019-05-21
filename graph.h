#ifndef GRAPH_H
#define GRAPH_H



/*
��ͼ��ʽ��
�������� �ִ���� ��ͨ���ͣ�0������1�𳵣�2�ɻ��� ����ʱ�䣨0 y z,��Ϊ��0��yʱz�֣� �ִ�ʱ�� ���� Ȼ����һ��
���������ͼʱ��ʱ���еĵ�x��ʼ��Ϊ0����Ӱ�죩
�����ͼһ��һѭ��
*/

#include"common.h"
#include"time.h"


struct Edge //�����ݾۺϣ�����Ҫ��װ
{
	Edge(Id _start = INT_MAX, Id _end = INT_MAX, unsigned int _type = INT_MAX, Time _startTime = defaultTime, Time _arriveTime = defaultTime, CostType _cost = INT_MAX) : start(_start), end(_end), type(_type), startTime(_startTime), arriveTime(_arriveTime), cost(_cost) {}

	Id start;//�������е�id
	Id end;//�ִ���е�id
	unsigned int  type;//��ͨ��ʽ
	Time startTime, arriveTime;
	CostType cost;
};


struct Vertex //�����ݾۺϣ�����Ҫ��װ
{
	Vertex(string _cityName) :cityName(_cityName) {}

	string cityName;
	vector<Edge> to;//�Ӵ˳��г����ܵ���ĳ���
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

	const vector<Vertex>& getVertexs();//��ȡvertexs�Ľӿڣ���RouteDesignʹ��


private:
	vector<Vertex> vertexs;//���г���
	//��������ID��hash������ȫ�̾�ʹ��Id������string����������ʶ�����ٿռ䣬���Ч��
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