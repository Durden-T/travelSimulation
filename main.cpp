#include"RouteDesign.h"
#include"graph.h"
#include"common.h"
#include"log.h"



int main()
{
	cout << "欢迎使用旅行线路模拟系统。\n默认地图文件为当前目录下 graph.txt。" << endl;
	//依次创建单例
	Log& L = Log::Instance();
	Graph& G = Graph::Instance(DEFAULT_FILE);
	RouteDesign& R = RouteDesign::Instance(G, L);

	while (true)
	{
		//获得设计要求
		R.reset();
		//设计路线
	c:if (R.design())
	{
		//输出设计结果
		R.showResult();
		//开始模拟
		//中途用户要求改变计划
		if (!R.simulation())
		{
			//改变计划
			R.change();
			//重新设计,此处使用goto跳出循环,否则需要大量的额外代码,降低可读性
			goto c;
		}
		cout << "设计完成，输入任意键继续，#exit退出。" << endl;
	}
	  //无路线
	  else
	{
		cout << "找不到符合要求的路线，输入任意键继续，#exit退出。" << endl;
	}

	  string buf;
	  //若用户要求退出
	  if (cin >> buf && buf == EXIT)
		  break;
	}

	return 0;
}