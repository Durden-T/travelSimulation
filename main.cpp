#include"RouteDesign.h"
#include"graph.h"
#include"common.h"
#include"log.h"



int main()
{
	cout << "��ӭʹ��������·ģ��ϵͳ��\nĬ�ϵ�ͼ�ļ�Ϊ��ǰĿ¼�� graph.txt��" << endl;
	//���δ�������
	Log& L = Log::Instance();
	Graph& G = Graph::Instance(DEFAULT_FILE);
	RouteDesign& R = RouteDesign::Instance(G, L);

	while (true)
	{
		//������Ҫ��
		R.reset();
		//���·��
	c:if (R.design())
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
			goto c;
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