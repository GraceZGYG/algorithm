//N皇后问题，输出解的形式为每行放Q的位置，递归求解
#include<iostream>
#include<cmath>
using namespace std;
int N;
int queenPos[100];
void NQueen(int k);
int main() {
	cin >> N;
	NQueen(0);
	return 0;
}
void NQueen(int k) {
	int i;
	if (k == N) {//N个皇后已经摆好，开始输出
		for (i = 0; i < N; i++) {
			cout << queenPos[i] + 1 << " ";
		}
		cout << endl;
		return;
	}
	for (i = 0; i < N; i++) {
		int j;
		for (j = 0; j < k; j++) {
			//和已经摆好的第k行比较，是否冲突
			if (queenPos[j] == i || abs(queenPos[j] - i )== abs(k - j)) {
				break;//冲突，测试下一个
			}
		}
		if (j == k) {
			queenPos[k] = i;
			NQueen(k + 1);
		}
	}


}
//input:4
//output:2 4 1 3
//       3 1 4 2