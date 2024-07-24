#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void main6() {
	char filename[100] = "C:/Windows/win.ini"; // 파일명
	FILE* rfp; // 파일 포인터 (파일 설명자)

	char str[200]; // 읽어올 한줄

	// 파일 처리 3단계
	// 1단게 : 파일 열기
	rfp = fopen(filename, "r");
	// 2단계 : 파일 읽거나 쓰기 (작업하기)
	while (1) { // 0: False, 0외는: True
		fgets(str, 200, rfp);
		if (feof(rfp))  break;
		printf("%s", str);
	}
	// 3단계 : 파일 닫기
	fclose(rfp);
}