//城堡问题DFS
//建模，没有墙隔开的方块连线构建连通图，节点数就是面积，连通图数量就是房间数
//将走过的方块标记颜色，用了几种颜色就有几个房间
//二进制表示四个方向是否有墙，十进制输入
#include<iostream>
#include<stack>
#include<cstring>
using namespace std;
int R, C;//行列数
int rooms[60][60];
int color[60][60];
int maxRoomArea = 0, roomNum = 0;
int roomArea = 0;
void Dfs(int i, int k) {
	if (color[i][k]) 
		return;
	++roomArea;
	color[i][k] = roomNum;
	//位运算判断每个方向是否有墙，没有就可以往该方向走
	if ((rooms[i][k] & 1) == 0) Dfs(i, k - 1);//向西走
	if ((rooms[i][k] & 2) == 0) Dfs(i - 1, k);//向北；
	if ((rooms[i][k] & 4) == 0) Dfs(i, k + 1);//向东
	if ((rooms[i][k] & 8) == 0) Dfs(i + 1, k);//向南

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
//复杂度：O(R*C)