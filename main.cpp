#include"RouteDesign.h"
#include"graph.h"
#include"common.h"
#include"log.h"

int main(int argc, char** argv)
{
	cout << "��ӭʹ��������·ģ��ϵͳ��\nĬ�ϵ�ͼ�ļ�Ϊ��C:\\travelSimulation\\graph.txt\nҪ�ı��ͼ�ļ���ַ�����������������г��������ļ���" << endl;
	//�������������� ���޲�����Ĭ�ϵ�ַ�򿪵�ͼ�������Բ����򿪵�ͼ
	ifstream file(argc == 1 ? "C:\\travelSimulation\\graph.txt" : argv[1]);
	//��ʧ��
	if (!file)
	{
		cout << "�޷����ļ���" << endl;
		return -1;
	}

	//���δ�������
	Log& L = Log::Instance();
	Graph G(file);
	RouteDesign& R = RouteDesign::Instance(G, L);

	while (true)
	{
		//������Ҫ��
		R.reset();
		//���·��
cycle:  if (R.design())
		{
			//�����ƽ��
			R.showResult();
			//��ʼģ��
			//��;�û�Ҫ��ı�ƻ�
			if (!R.simulation())
			{
				//�ı�ƻ�
				R.change();
				//�������,�˴�ʹ��goto����ѭ��,������Ҫ�����Ķ������,���Ϳɶ���
				goto cycle;
			}
			cout << "�����ɣ����������������#exit�˳���" << endl;
		}
		//��·��
		else
		{
			cout << "�Ҳ�������Ҫ���·�ߣ����������������#exit�˳���" << endl;
		}

		string buf;
		//���û�Ҫ���˳�
		if (cin >> buf && buf == EXIT)
			break;
	}

	return 0;
}