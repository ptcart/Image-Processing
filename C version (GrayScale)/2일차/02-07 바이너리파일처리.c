#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define height 512
#define width 512
unsigned char image[height][width];

void printImage2() {
	for (int i = height / 2 - 5; i < height / 2 + 5; i++) {
		for (int k = width / 2 - 5; k < width / 2 + 5; k++) {
			printf("%03d ", image[i][k]);
		}
		printf("\n");
	}
	printf("\n");
}


void main7() {
	char filename[100] = "C:/RAW/Etc_Raw(squre)/flower512.raw";  // 파일명
	FILE* rfp; // 파일 포인터(파일 설명자)

	// 파일 처리 3단계
	// 1단계 : 파일 열기
	rfp = fopen(filename, "rb");
	// 2단계 : 파일을 512x512번 반복해서 읽기.. 한방에 512x512 읽기
	fread(image, sizeof(unsigned char), height * width, rfp);

	// 3단계 : 파일 닫기
	fclose(rfp);
	printImage2();
}