#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>

// ���� : ������ ũ�Ⱑ 3�� 5��¥���� ó������
#define height 3 // ��
#define width 5  // ��
// (0) �޸� �Ҵ� (= �迭 �غ�)
unsigned char image[height][width];

void printImage1() {
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			printf("%03d ", image[i][k]);
		}
		printf("\n");
	}
	printf("\n");
}

void main4() {
	srand((unsigned int)time(0)); // Ÿ�̸� �ʱ�ȭ
	

	// (2) ����(����) --> �޸𸮷� �ε�(loading)

	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			int pixel = rand() % 256; // rand() : 0~32767���� ������ ����
			image[i][k] = pixel;
		}
	}

	// (3) ȭ�鿡 ���
	printImage1();
	
	// (4) ����ó�� �˰��� ����
	// (4-1) ���� ��� ó��(50)
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			if (image[i][k] + 50 > 255) {
				image[i][k] = 255;
			}
			
			else {
				image[i][k] += 50;
			}
		}
	}
	printf("��� ó�� \n");
	printImage1();

	// (4-2) ���� ��Ӱ� ó��
	// ���� 1 
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			if (image[i][k] - 100 < 0) {
				image[i][k] = 0;
			}

			else {
				image[i][k] -= 100;
			}
		}
	}
	printf("��Ӱ� ó�� \n");
	printImage();

	// (4-3) ��� �����
	// ���� 2
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			
			if (image[i][k] < 128) {
				image[i][k] = 0;
			}
			else image[i][k] = 255;
				
		}
	}
	printf("��� ó�� \n");
	printImage1();
	
	


	// (4-4) �پ��� ����ó�� �˰��� ����.....
}