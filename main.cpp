#include"RouteDesign.h"
#include"graph.h"
#include"common.h"
#include"log.h"

int main(int argc, char** argv)
{
	//准备临时变量
	string buf, startCityName, endCityName;
	Time startTime, limitTime;
	unsigned int mode;
	vector<string> passBy;
	cout << "欢迎使用旅行线路模拟系统。\n默认地图文件为：C:\\travelSimulation\\graph.txt\n要改变地图文件地址请在命令行重新运行程序并输入文件。" << endl;
	//在命令行中运行 若无参数用默认地址打开地图，否则以参数打开地图
	ifstream file(argc == 1 ? "C:\\travelSimulation\\graph.txt" : argv[1]);
	if (!file)//打开失败
	{
		cout << "无法打开文件。" << endl;
		return -1;
	}


	//依次创建单例
	Log& L = Log::Instance();
	Graph G(file);
	file.close();
	RouteDesign& R = RouteDesign::Instance(G, L);

	while (true)
	{
		//输出提示等因为比较复杂繁琐，放在main函数便于更新，修改,获取好信息后调用RouteDesign类
		passBy.clear();

		// 基于当前系统的当前日期/时间
		time_t now = time(NULL);

		// 把 now 转换为字符串形式,打印当前时间
		char* dt = ctime(&now);

		//默认地图为一天一个循环，因此采用此时间格式，方便，易读
		cout << "\n当前时间为:" << dt << "\n请依次输入出发时间，出发城市与目的地。\n本系统时间格式为：x y z,意为第x天y时z分。" << endl;


		while (!(cin >> startTime >> startCityName >> endCityName) || !G.hasCity(startCityName) || !G.hasCity(endCityName) || !startTime.valid())
		{
			cout << "输入错误。\n请重新输入出发时间，出发城市与目的地。" << endl;
		}

		cout << "请选择旅行策略。\n1.最少时间\t2.最少费用\t3.限时最少费用" << endl;
		while (!(cin >> mode) || mode < minTime || mode > minCostWithTimeLimited)//选择旅行策略
		{
			cout << "输入错误。\n请重新选择旅行策略。\n1.最少时间\t2.最少费用\t3.限时最少费用" << endl;
		}
		if (mode != minCostWithTimeLimited)//不需要限制时间
			limitTime = defaultTime;//默认为无穷大时间
		else
		{
			cout << "请输入最迟到达时间。" << endl;
			while (!(cin >> limitTime))
			{
				cout << "输入错误。\n请输入最迟到达时间。" << endl;
			}
		}


		cout << "请输入要途经的城市,#exit结束输入。" << endl;//途经城市
		bool success;//控制连续输入中发生错误 比如:上海 asd #exit
		do
		{
			passBy.clear();
			success = true;
			while (cin >> buf && buf != EXIT)
			{
				if (G.hasCity(buf))
				{
					passBy.push_back(buf);
				}
				else
				{
					success = false;
					cout << buf << "不存在，请重新输入要途经的城市,#exit结束输入。" << endl;
				}
			}
		} while (!success);



		//通知R重新配置
		R.reset(startTime, startCityName, endCityName, mode, limitTime, passBy);


cycle:	if (R.design())//设计路线
		{
			R.showResult();
			if (!R.simulation())
			{
				R.change();
				goto cycle;
			}
			cout << "设计完成，输入任意键继续，#exit退出。" << endl;
		}
		else
			cout << "找不到符合要求的路线，输入任意键继续，#exit退出。" << endl;

		if (cin >> buf && buf == EXIT)
			break;
	}
	return 0;
}
/*cycle:	if (R.design())//设计路线
		{
			while (!R.showResult())
			{
				R.change();
				//只能goto，用其他方法实现循环会增加大量代码，混乱代码逻辑
				goto cycle;
			}
			cout << "设计完成，输入任意键继续，#exit退出。" << endl;
		}
		else
			cout << "找不到符合要求的路线，输入任意键继续，#exit退出。" << endl;

		if (cin >> buf && buf == EXIT)
			break;
	}
	return 0;
}*/