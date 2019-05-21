#include"strategy.h"
#include"RouteDesign.h"
#include"graph.h"



bool MinTime::design()
{
	if (passBy.empty())
	{
		return Dijkstra(start, end, path,startTime) != defaultTime;
	}
	Time ans = defaultTime;
	bool success = false;
	vector<const Edge*> tmpPath;
	do
	{
		tmpPath.clear();
		int nextStart;
		Time t;
		Time cur = startTime;

		nextStart = tmpPath.size();
		t = Dijkstra(start, passBy.front(), tmpPath,cur);
		if (t == defaultTime)
			continue;
		cur.advanceTo(tmpPath[nextStart]->startTime).advanceTo(t);

		nextStart = tmpPath.size();
		t = midDijkstra(tmpPath, cur);
		if (t == defaultTime)
			continue;
		cur.advanceTo(tmpPath[nextStart]->startTime).advanceTo(t);

		nextStart = tmpPath.size();
		t = Dijkstra(passBy.back(), end, tmpPath, cur);
		if (t == defaultTime)
			continue;
		cur.advanceTo(tmpPath[nextStart]->startTime).advanceTo(t);

		success = true;
		if (cur < ans)
		{
			ans = cur;
			path.swap(tmpPath);
		}
	} while (next_permutation(passBy.begin(), passBy.end()));

	return success;
}

Time MinTime::Dijkstra(Id start, Id end, vector<const Edge*>& path, const Time& startTime)
{
	vector<const Edge*> tmpPath(vertexs.size(), nullptr);
	vector<Time> time(vertexs.size());
	time[start] = startTime;//����ʱ��
	vector<bool> known(vertexs.size(), false);
	auto cmp = [&](const Id a, const Id b)//�Զ���ȽϺ���
	{
		return time[a] > time[b];
	};
	priority_queue<Id, vector<Id>, decltype(cmp)> PQ(cmp);
	PQ.push(start);//����ʼ���з������
	while (!PQ.empty() && !known[end])
	{
		Id t = PQ.top();
		PQ.pop();
		known[t] = true;//���������
		for (const Edge& e : vertexs[t].to)//�����б�
		{
			Time tmpTime = time[t];
			tmpTime.advanceTo(e.startTime).advanceTo(e.arriveTime);//���ϲ����Զ��л���һ��
			if (!known[e.end] && time[e.end] > tmpTime)//δ��������ʱ��С�ڵ�ǰʱ��
			{
				time[e.end] = tmpTime;//���µ�ǰʱ��
				tmpPath[e.end] = &e;//д��·��
				PQ.push(e.end);//����������ѡ��
			}
		}
	}

	if (time[end] != defaultTime)
	{
		const Edge* e = tmpPath[end];
		int last = path.size();
		while (e)
		{
			path.emplace_back(e);
			e = tmpPath[e->start];
		}
		reverse(path.begin() + last, path.end());
	}
	return time[end];
}

Time MinTime::midDijkstra(vector<const Edge*>& path, const Time& startTime)
{
	Time ans = startTime;
	if (passBy.size() != 1)
	{
		for (int i = 0; i < passBy.size() - 1; ++i)
		{
			int nextStart = path.size();
			Time t = Dijkstra(passBy[i], passBy[i + 1], path, ans);
			if (t == defaultTime)
				continue;
			ans.advanceTo(path[nextStart]->startTime).advanceTo(t);
		}
	}
	return ans;
}


bool MinCost::design()
{
	if (passBy.empty())
	{
		return Dijkstra(start, end, path) != INT_MAX;
	}
	CostType ans = INT_MAX;
	bool success = false;
	vector<const Edge*> tmpPath;
	do
	{
		tmpPath.clear();
		CostType before = Dijkstra(start, passBy.front(), tmpPath);
		if (before == INT_MAX)
			continue;
		CostType mid = midDijkstra(tmpPath);
		if (mid == INT_MAX)
			continue;
		CostType after = Dijkstra(passBy.back(), end, tmpPath);
		if (after == INT_MAX)
			continue;
		success = true;
		CostType cur = before + mid + after;
		if (cur < ans)
		{
			ans = cur;
			path.swap(tmpPath);
		}
	} while (next_permutation(passBy.begin(), passBy.end()));
	return success;
}

CostType MinCost::Dijkstra(Id start, Id end, vector<const Edge*>& path)
{
	vector<const Edge*> tmpPath(vertexs.size(), nullptr);
	vector<CostType> cost(vertexs.size(), INT_MAX);
	cost[start] = 0;
	vector<bool> known(vertexs.size(), false);
	auto cmp = [&](const Id a, const Id b)//�Զ���ȽϺ���
	{
		return cost[a] > cost[b];
	};
	priority_queue<Id, vector<Id>, decltype(cmp)> PQ(cmp);
	PQ.push(start);//����ʼ���з������
	while (!PQ.empty() && !known[end])
	{
		Id t = PQ.top();
		PQ.pop();
		known[t] = true;//���������
		for (const Edge& e : vertexs[t].to)//�����б�
			//���ٻ��ѣ�������ʱ��
			if (!known[e.end] && cost[e.end] > cost[t] + e.cost)//δ�������һ���С�ڵ�ǰ����
			{
				cost[e.end] = cost[t] + e.cost;//���»���
				tmpPath[e.end] = &e;//д��·��
				PQ.push(e.end);//����������ѡ��
			}
	}
	if (cost[end] != INT_MAX)
	{
		const Edge* e = tmpPath[end];
		int last = path.size();
		while (e)
		{
			path.emplace_back(e);
			e = tmpPath[e->start];
		}
		reverse(path.begin() + last, path.end());
	}
	return cost[end];
}

CostType MinCost::midDijkstra(vector<const Edge*>& path)
{
	CostType ans = 0;
	if (passBy.size() != 1)
	{
		for (int i = 0; i < passBy.size() - 1; ++i)
		{
			CostType t = Dijkstra(passBy[i], passBy[i + 1], path);
			if (t == INT_MAX)
				return INT_MAX;
			ans += t;
		}
	}
	return ans;
}


bool MinCostWithTimeLimited::design()
{
	if (passBy.empty())
	{
		vector<Time> time(vertexs.size());
		time[start] = startTime;
		return Dijkstra(start, end, path, time) != INT_MAX;
	}
	CostType ans = INT_MAX;
	bool success = false;
	vector<const Edge*> tmpPath;
	do
	{
		tmpPath.clear();
		vector<Time> time(vertexs.size());
		time[start] = startTime;
		CostType before = Dijkstra(start, passBy.front(), tmpPath, time);
		if (before == INT_MAX)
			continue;
		CostType mid = midDijkstra(tmpPath, time);
		if (mid == INT_MAX)
			continue;
		CostType after = Dijkstra(passBy.back(), end, tmpPath, time);
		if (after == INT_MAX)
			continue;
		CostType cur = before + mid + after;
		if (time[end] <= limitTime)
		{
			success = true;
			if (cur < ans)
			{
				ans = cur;
				path.swap(tmpPath);
			}
		}
	} while (next_permutation(passBy.begin(), passBy.end()));
	return success;
}

CostType MinCostWithTimeLimited::Dijkstra(Id start, Id end, vector<const Edge*>& path, vector<Time>& time)
{
	vector<const Edge*> tmpPath(vertexs.size(), nullptr);
	vector<CostType> cost(vertexs.size(), INT_MAX);
	cost[start] = 0;
	vector<bool> known(vertexs.size(), false);
	auto cmp = [&](const Id a, const Id b)//�Զ���ȽϺ���
	{
		return cost[a] > cost[b];
	};
	priority_queue<Id, vector<Id>, decltype(cmp)> PQ(cmp);
	PQ.push(start);//����ʼ���з������
	while (!PQ.empty() && !known[end])
	{

		Id t = PQ.top();
		PQ.pop();
		known[t] = true;
		Time tmpTime = time[t];
		for (const Edge& e : vertexs[t].to)
		{
			tmpTime = time[t];
			tmpTime.advanceTo(e.startTime).advanceTo(e.arriveTime);
			if (!known[e.end] && tmpTime <= limitTime && cost[e.end] > cost[t] + e.cost)
			{
				time[e.end] = tmpTime;
				cost[e.end] = cost[t] + e.cost;
				tmpPath[e.end] = &e;
				PQ.push(e.end);
			}
		}
	}
	if (cost[end] != INT_MAX)
	{
		const Edge* e = tmpPath[end];
		int last = path.size();
		while (e)
		{
			path.emplace_back(e);
			e = tmpPath[e->start];
		}
		reverse(path.begin() + last, path.end());
	}
	return cost[end];
}

CostType MinCostWithTimeLimited::midDijkstra(vector<const Edge*>& path, vector<Time>& time)
{
	CostType ans = 0;
	if (passBy.size() != 1)
	{
		for (int i = 0; i < passBy.size() - 1; ++i)
		{
			CostType t = Dijkstra(passBy[i], passBy[i + 1], path, time);
			if (t == INT_MAX || time[passBy[i + 1]] > limitTime)
				return INT_MAX;
			ans += t;
		}
	}
	return ans;
}