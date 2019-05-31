#ifndef GRAPH_H
#define GRAPH_H



/*
��ͼ��ʽ��
�������� �ִ���� ��ͨ���ͣ�0������1�𳵣�2�ɻ��� ����ʱ�䣨0 y z,��Ϊ��0��yʱz�֣� �ִ�ʱ�� ���� Ȼ����һ��
���������ͼʱ��ʱ���еĵ�x��ʼ��Ϊ0��
�����ͼһ��һѭ��
*/

#include"common.h"
#include"time.h"


//Edge,VertexΪ�����ݾۺϣ�����Ҫ��װ
struct Edge
{
	Edge(Id _start = INT_MAX, Id _end = INT_MAX, unsigned int _type = INT_MAX, Time _startTime = defaultTime, Time _arriveTime = defaultTime, CostType _cost = INT_MAX) : start(_start), end(_end), type(_type), startTime(_startTime), arriveTime(_arriveTime), cost(_cost) {}

	//�������е�id
	Id start;
	//�ִ���е�id
	Id end;
	//��ͨ��ʽ
	unsigned int type;
	Time startTime, arriveTime;
	CostType cost;
};


struct Vertex //�����ݾۺϣ�����Ҫ��װ
{
	Vertex(string _cityName) :cityName(_cityName) {}

	string cityName;
	// �Ӵ˳��г����ı�
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

	//���ӳ��У����ظó��е�Id
	Id addCity(const string& cityName);

	//�����иó��з���true�����򷵻�false
	bool hasCity(const string& cityName);

	//���ظó��е�Id
	Id getId(const string& cityName);

	//��ȡ�ó��еĽ��ָ��
	Vertex* getCity(const string& cityName);

	const string& getCityName(Id id);

	//��ȡvertexs�Ľӿڣ���RouteDesignʹ��
	const vector<Vertex>& getVertexs();

protected:
	//Singleton method
	//���ļ�������file��ʼ��Graph
	Graph(const string& file);

	~Graph() = default;
private:
	//���г���
	vector<Vertex> vertexs;
	//hash��,��������ӳ�䵽Id,ȫ�̾�ʹ��Id������string/����/ָ������ʶ������ʹ�õĿռ䣬���Ч��
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