#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void main3() {
	
	// 5��¥�� �迭(ary1)�� �غ��ϰ�, ���� 100���� 104���� �����ϱ�.. �׸��� �հ� ����.
	#define SIZE 5 // const int SIZE = 5;
	int ary1[SIZE];
	int value = 100;
	for (int i = 0; i < SIZE; i++) {
		ary1[i] = value;
		value++;
	}
	long long result = 0;
	for (int i = 0; i < SIZE; i++) {
		result += ary1[i];
	}
	printf("�հ� : %lld \n", result);


	// 3X4 ũ���� �迭(ary2)�� �غ��ϰ�, ���� 100���� �����ϱ�...�׸��� �հ賻��
	#define ROW 3
	#define COL 4
	int ary2[ROW][COL];
	value = 100;
	

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			ary2[i][k] = value;
			value++;
		}
	}

	result = 0;
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			result += ary2[i][k];
		}
	}
	printf("�հ� : %lld", result);
}