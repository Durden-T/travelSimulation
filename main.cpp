#include"RouteDesign.h"
#include"graph.h"
#include"common.h"
#include"log.h"

int main(int argc, char** argv)
{
	//׼����ʱ����
	string buf, startCityName, endCityName;
	Time startTime, limitTime;
	unsigned int mode;
	vector<string> passBy;
	cout << "��ӭʹ��������·ģ��ϵͳ��\nĬ�ϵ�ͼ�ļ�Ϊ��C:\\travelSimulation\\graph.txt\nҪ�ı��ͼ�ļ���ַ�����������������г��������ļ���" << endl;
	//�������������� ���޲�����Ĭ�ϵ�ַ�򿪵�ͼ�������Բ����򿪵�ͼ
	ifstream file(argc == 1 ? "C:\\travelSimulation\\graph.txt" : argv[1]);
	if (!file)//��ʧ��
	{
		cout << "�޷����ļ���" << endl;
		return -1;
	}


	//���δ�������
	Log& L = Log::Instance();
	Graph G(file);
	file.close();
	RouteDesign& R = RouteDesign::Instance(G, L);

	while (true)
	{
		//�����ʾ����Ϊ�Ƚϸ��ӷ���������main�������ڸ��£��޸�,��ȡ����Ϣ�����RouteDesign��
		passBy.clear();

		// ���ڵ�ǰϵͳ�ĵ�ǰ����/ʱ��
		time_t now = time(NULL);

		// �� now ת��Ϊ�ַ�����ʽ,��ӡ��ǰʱ��
		char* dt = ctime(&now);

		//Ĭ�ϵ�ͼΪһ��һ��ѭ������˲��ô�ʱ���ʽ�����㣬�׶�
		cout << "\n��ǰʱ��Ϊ:" << dt << "\n�������������ʱ�䣬����������Ŀ�ĵء�\n��ϵͳʱ���ʽΪ��x y z,��Ϊ��x��yʱz�֡�" << endl;


		while (!(cin >> startTime >> startCityName >> endCityName) || !G.hasCity(startCityName) || !G.hasCity(endCityName) || !startTime.valid())
		{
			cout << "�������\n�������������ʱ�䣬����������Ŀ�ĵء�" << endl;
		}

		cout << "��ѡ�����в��ԡ�\n1.����ʱ��\t2.���ٷ���\t3.��ʱ���ٷ���" << endl;
		while (!(cin >> mode) || mode < minTime || mode > minCostWithTimeLimited)//ѡ�����в���
		{
			cout << "�������\n������ѡ�����в��ԡ�\n1.����ʱ��\t2.���ٷ���\t3.��ʱ���ٷ���" << endl;
		}
		if (mode != minCostWithTimeLimited)//����Ҫ����ʱ��
			limitTime = defaultTime;//Ĭ��Ϊ�����ʱ��
		else
		{
			cout << "��������ٵ���ʱ�䡣" << endl;
			while (!(cin >> limitTime))
			{
				cout << "�������\n��������ٵ���ʱ�䡣" << endl;
			}
		}


		cout << "������Ҫ;���ĳ���,#exit�������롣" << endl;//;������
		bool success;//�������������з������� ����:�Ϻ� asd #exit
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
					cout << buf << "�����ڣ�����������Ҫ;���ĳ���,#exit�������롣" << endl;
				}
			}
		} while (!success);



		//֪ͨR��������
		R.reset(startTime, startCityName, endCityName, mode, limitTime, passBy);


cycle:	if (R.design())//���·��
		{
			R.showResult();
			if (!R.simulation())
			{
				R.change();
				goto cycle;
			}
			cout << "�����ɣ����������������#exit�˳���" << endl;
		}
		else
			cout << "�Ҳ�������Ҫ���·�ߣ����������������#exit�˳���" << endl;

		if (cin >> buf && buf == EXIT)
			break;
	}
	return 0;
}
/*cycle:	if (R.design())//���·��
		{
			while (!R.showResult())
			{
				R.change();
				//ֻ��goto������������ʵ��ѭ�������Ӵ������룬���Ҵ����߼�
				goto cycle;
			}
			cout << "�����ɣ����������������#exit�˳���" << endl;
		}
		else
			cout << "�Ҳ�������Ҫ���·�ߣ����������������#exit�˳���" << endl;

		if (cin >> buf && buf == EXIT)
			break;
	}
	return 0;
}*/