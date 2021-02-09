#include <iostream>
#include <queue>

using namespace std;

//�ڵ�ṹ Ĭ�Ϲ��캯���½�����
struct node
{
	int x, y, z;

	node() {}
	node(int x, int y, int z) :
		x(x), y(y), z(z) {}
};

//ԭʼ���� ���ʾ���
int m, n, l,t;
int a[60][1286][128];
bool v[60][1286][128];

//��������ı仯���� �ֱ��Ӧһ���ڵ����������ǰ��ڵ�
int dx[6] = { 1,0,0,-1,0,0 };
int dy[6] = { 0,1,0,0,-1,0 };
int dz[6] = { 0,0,1,0,0,-1 };

bool jude(int x, int y, int z)
{
	if (x < 0 || x >= l || y < 0 || y >= m || z < 0 || z >= n)
		return false;
	if (a[x][y][z] == 0 || v[x][y][z] == true)
		return false;

	return true;
}

int bfs(int x, int y, int z)
{
	int cnt = 0;
	node brain(x, y, z);
	queue<node> q;
	q.push(brain);
	v[x][y][z] = true;
	while (!q.empty())
	{
		node tmp = q.front();
		q.pop();
		cnt++;
		for (int i = 0; i < 6; i++)
		{
			int nx = tmp.x + dx[i];
			int ny = tmp.y + dy[i];
			int nz = tmp.z + dz[i];
			if (!jude(nx, ny ,nz))
				continue;
			node newN(nx, ny, nz);
			q.push(newN);
			v[nx][ny][nz] = true;
		}
	}
	if (cnt >= t)
		return cnt;
	else
		return 0;
}

int main()
{
	cin >> m >> n >> l >> t;
	for (int i = 0; i < l; i++)
		for (int j = 0; j < m; j++)
			for (int k = 0; k < n; k++)
				cin >> a[i][j][k];

	int ans = 0;
	for (int i = 0; i < l; i++)
		for (int j = 0; j < m; j++)
			for (int k = 0; k < n; k++)
				if (a[i][j][k] == 1 && v[i][j][k] == false)
					ans += bfs(i, j, k);

	cout << ans;
	return 0;

}