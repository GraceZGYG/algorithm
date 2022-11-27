//�Ǳ�����DFS
//��ģ��û��ǽ�����ķ������߹�����ͨͼ���ڵ��������������ͨͼ�������Ƿ�����
//���߹��ķ�������ɫ�����˼�����ɫ���м�������
//�����Ʊ�ʾ�ĸ������Ƿ���ǽ��ʮ��������
#include<iostream>
#include<stack>
#include<cstring>
using namespace std;
int R, C;//������
int rooms[60][60];
int color[60][60];
int maxRoomArea = 0, roomNum = 0;
int roomArea = 0;
void Dfs(int i, int k) {
	if (color[i][k]) 
		return;
	++roomArea;
	color[i][k] = roomNum;
	//λ�����ж�ÿ�������Ƿ���ǽ��û�оͿ������÷�����
	if ((rooms[i][k] & 1) == 0) Dfs(i, k - 1);//������
	if ((rooms[i][k] & 2) == 0) Dfs(i - 1, k);//�򱱣�
	if ((rooms[i][k] & 4) == 0) Dfs(i, k + 1);//��
	if ((rooms[i][k] & 8) == 0) Dfs(i + 1, k);//����

}
int main() {
	cin >> R >> C;
	for (int i = 1; i <= R; ++i)
		for (int k = 1; k <= C; ++k)
			cin >> rooms[i][k];
	memset(color, 0, sizeof(color));
	for(int i=1;i<=R;++i)
		for (int k = 1; k <= C; ++k) {
			if (!color[i][k]) {
				++roomNum; roomArea = 0;
				Dfs(i, k);
				maxRoomArea = max(roomArea, maxRoomArea);
			}
		}
	cout << roomNum << endl;
	cout << maxRoomArea << endl;

}
//���Ӷȣ�O(R*C)