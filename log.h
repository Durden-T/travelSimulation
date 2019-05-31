#ifndef LOG_H
#define LOG_H



#include"common.h"

//前向声明,分离编译
struct Edge;
class Graph;


//考虑到多个旅客，每次创建日志时，日志名为创建时间
class Log
{
public:
	//Singleton method
	static Log& Instance()
	{
		static Log Instance;
		return Instance;
	}

	//将用户新的输入写入log,changed参数默认为false,若为true标志这次的reset是中途改变的
	void reset(const Time& startTime, const string& startCityName, const string& endCityName, unsigned int mode, const Time& limitTime, vector<string>& passBy, bool changed = false);

	//考虑到可能中途发生过改变,传参数lastCost,输出时cost从lastCost开始计算
	void showResult(Graph& G, CostType lastCost, vector<const Edge*>& path);

protected:
	//Singleton method
	Log();
	~Log();


private:
	//文件输出流
	ofstream file;
	//策略表,与enum结合便于coding,提高可读性
	vector<string> strategyTable{ "", "最少时间", "最少花费", "限时最少花费" };
	vector<string> travelTypeTable{ "汽运", "火车", "飞机" };
};



#endif
