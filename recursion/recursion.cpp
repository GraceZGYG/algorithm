//N�ʺ����⣬��������ʽΪÿ�з�Q��λ�ã��ݹ����
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
	if (k == N) {//N���ʺ��Ѿ��ںã���ʼ���
		for (i = 0; i < N; i++) {
			cout << queenPos[i] + 1 << " ";
		}
		cout << endl;
		return;
	}
	for (i = 0; i < N; i++) {
		int j;
		for (j = 0; j < k; j++) {
			//���Ѿ��ںõĵ�k�бȽϣ��Ƿ��ͻ
			if (queenPos[j] == i || abs(queenPos[j] - i )== abs(k - j)) {
				break;//��ͻ��������һ��
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