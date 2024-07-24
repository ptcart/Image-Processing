#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void main3() {
	
	// 5개짜리 배열(ary1)을 준비하고, 값을 100부터 104까지 대입하기.. 그리고 합계 내기.
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
	printf("합계 : %lld \n", result);


	// 3X4 크기의 배열(ary2)를 준비하고, 값을 100부터 대입하기...그리고 합계내기
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
	printf("합계 : %lld", result);
}