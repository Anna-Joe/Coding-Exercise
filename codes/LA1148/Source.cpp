#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//��������ֱ���� ĳ�˵���� �� ���������
//����V���� ��������� �����ű�ʶ�û������ֱ�ʶ��Ա��ţ�
//����a���� ��Ա����� ��1��ʶ���ˣ�-1��ʶ���ˣ�
int main()
{
	int n;//��Ա����
	cin >> n;
	vector<int> v(n+1);

	for (int i = 1; i < n+1; i++)
	{
		cin >> v[i];
	}
	for (int i = 1; i < n+1; i++)
	{
		for (int j = i + 1; j < n+1; j++)
		{
			vector<int> a(n + 1, 1);//��ʼ��n��1 Ĭ�϶��Ǻ���
			vector<int> liar;//�ѻ���Ա

			a[i] = a[j] = -1;//ij��ʶ����
			for (int k = 1; k < n+1; k++)
				if (v[k] * a[abs(v[k])] < 0)liar.push_back(k);
			if (liar.size() == 2 && (a[liar[0]] + a[liar[1]] == 0))//��˵�ѳ�ԱΪ���ˣ�����һ��һ��ʱ ���
			{
				cout << i << " " << j;
				return 0;
			}
		}
	}
	cout << "No Solution";
	return 0;
}