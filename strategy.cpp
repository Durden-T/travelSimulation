#include"strategy.h"
#include"RouteDesign.h"
#include"graph.h"

/*
算法：将必经点全排列,求出中间路径,然后起点与中间路径,中间路径与终点连接,遍历所有的必经点排列,找出最优解
考虑到图规模不大,直接穷举法解决,在这种规模的数据下效率甚至比其他算法高,并且返回的必定为最优解（而不是逼近最优解）
*/

bool MinTime::design()
{
	//若无必经点
	if (passBy.empty())
	{
		//直接返回简单的两点Dijkstra
		return Dijkstra(start, end, path, startTime) != defaultTime;
	}
	//ans初始为最大时间
	Time ans = defaultTime;
	//记录是否成功
	bool success = false;
	//tmp路径
	vector<const Edge*> tmpPath;

	do
	{
		//每次都需要清空
		tmpPath.clear();
		int nextStart;
		Time t;
		Time cur = startTime;

		nextStart = tmpPath.size();
		//连接起点与当前的排列过的passBy的第一个
		t = Dijkstra(start, passBy.front(), tmpPath, cur);
		//若无结果,直接进行下一次排列
		if (t == defaultTime)
			continue;
		//若赶不上自动切换下一天
		cur.advanceTo(tmpPath[nextStart]->startTime).advanceTo(t);

		nextStart = tmpPath.size();
		//连接当前的排列过的passBy的各个结点
		t = midDijkstra(tmpPath, cur);
		//若无结果,直接进行下一次排列
		if (t == defaultTime)
			continue;
		//若赶不上自动切换下一天
		cur.advanceTo(tmpPath[nextStart]->startTime).advanceTo(t);

		nextStart = tmpPath.size();
		//连接当前的排列过的passBy的最后一个与终点
		t = Dijkstra(passBy.back(), end, tmpPath, cur);
		//若无结果,直接进行下一次排列
		if (t == defaultTime)
			continue;
		//若赶不上自动切换下一天
		cur.advanceTo(tmpPath[nextStart]->startTime).advanceTo(t);

		//运行到此处,说明之前的结果都有效,success设为true
		success = true;
		//当前时间小于ans
		if (cur < ans)
		{
			ans = cur;
			//tmpPath赋给真实路径
			path.swap(tmpPath);
		}
		//全排列
	} while (next_permutation(passBy.begin(), passBy.end()));

	return success;
}

Time MinTime::Dijkstra(Id start, Id end, vector<const Edge*>& path, const Time& startTime)
{
	vector<const Edge*> tmpPath(vertexs.size(), nullptr);
	vector<Time> time(vertexs.size());
	//出发时间
	time[start] = startTime;
	//记录已知的结点
	vector<bool> known(vertexs.size(), false);
	//自定义比较函数
	auto cmp = [&](const Id a, const Id b)
	{
		return time[a] > time[b];
	};
	priority_queue<Id, vector<Id>, decltype(cmp)> PQ(cmp);
	//将起始城市放入堆中
	PQ.push(start);
	while (!PQ.empty() && !known[end])
	{
		Id t = PQ.top();
		PQ.pop();
		//标记已搜索
		known[t] = true;
		//对所有边
		for (const Edge& e : vertexs[t].to)
		{
			Time tmpTime = time[t];
			//若赶不上自动切换下一天
			tmpTime.advanceTo(e.startTime).advanceTo(e.arriveTime);
			//未搜索过且时间小于当前时间
			if (!known[e.end] && time[e.end] > tmpTime)
			{
				time[e.end] = tmpTime;//更新当前时间
				tmpPath[e.end] = &e;//写入路径
				PQ.push(e.end);//置入搜索候选区
			}
		}
	}
	
	//结果有效
	if (time[end] != defaultTime)
	{
		//将tmpPath中的数据转移到path中
		const Edge* e = tmpPath[end];
		int last = path.size();
		while (e)
		{
			path.emplace_back(e);
			//e变为上一条边
			e = tmpPath[e->start];
		}
		//因为逆序插入,现在需要把新插入的顺序逆转
		reverse(path.begin() + last, path.end());
	}
	//返回最终到达时间
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
			//连接i和i+1
			Time t = Dijkstra(passBy[i], passBy[i + 1], path, ans);
			//若无结果
			if (t == defaultTime)
				continue;
			//时间转移
			ans.advanceTo(path[nextStart]->startTime).advanceTo(t);
		}
	}
	return ans;
}


//之后的算法类似

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
	auto cmp = [&](const Id a, const Id b)//自定义比较函数
	{
		return cost[a] > cost[b];
	};
	priority_queue<Id, vector<Id>, decltype(cmp)> PQ(cmp);
	PQ.push(start);//将起始城市放入堆中
	while (!PQ.empty() && !known[end])
	{
		Id t = PQ.top();
		PQ.pop();
		known[t] = true;//标记已搜索
		for (const Edge& e : vertexs[t].to)//对所有边
			//最少花费，不考虑时间
			if (!known[e.end] && cost[e.end] > cost[t] + e.cost)//未搜索过且花费小于当前花费
			{
				cost[e.end] = cost[t] + e.cost;//更新花费
				tmpPath[e.end] = &e;//写入路径
				PQ.push(e.end);//置入搜索候选区
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
	auto cmp = [&](const Id a, const Id b)//自定义比较函数
	{
		return cost[a] > cost[b];
	};
	priority_queue<Id, vector<Id>, decltype(cmp)> PQ(cmp);
	PQ.push(start);//将起始城市放入堆中
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