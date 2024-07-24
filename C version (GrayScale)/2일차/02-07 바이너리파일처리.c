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
	char filename[100] = "C:/RAW/Etc_Raw(squre)/flower512.raw";  // ���ϸ�
	FILE* rfp; // ���� ������(���� ������)

	// ���� ó�� 3�ܰ�
	// 1�ܰ� : ���� ����
	rfp = fopen(filename, "rb");
	// 2�ܰ� : ������ 512x512�� �ݺ��ؼ� �б�.. �ѹ濡 512x512 �б�
	fread(image, sizeof(unsigned char), height * width, rfp);

	// 3�ܰ� : ���� �ݱ�
	fclose(rfp);
	printImage2();
}