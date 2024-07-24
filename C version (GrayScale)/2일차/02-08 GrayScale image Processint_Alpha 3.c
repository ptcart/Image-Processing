#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>

// ���� : ������ ũ�Ⱑ 3�� 5��¥���� ó������
#define height 3 // ��
#define width 5  // ��
// (0) �޸� �Ҵ� (= �迭 �غ�)
unsigned char image[height][width];
unsigned char rotateImage[width][height];

void printImage() {
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			printf("%03d ", image[i][k]);
		}
		printf("\n");
	}
	printf("\n");
}

void loadImage() {
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			int pixel = rand() % 256; // rand() : 0~32767���� ������ ����
			image[i][k] = pixel;
		}
	}
}

void addImage(int value) {
	printf("��� ó�� \n");
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			if (image[i][k] + value > 255) {
				image[i][k] = 255;
			}

			else {
				image[i][k] += value;
			}
		}
	}

}
void subImage(int value) {
	printf("��Ӱ� ó�� \n");
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			if (image[i][k] - value < 0) {
				image[i][k] = 0;
			}

			else {
				image[i][k] -= value;
			}
		}
	}
}

void mulImage(int value) {
	printf("���� ���� ó�� \n");
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			if (image[i][k] * value > 255) {
				image[i][k] = 255;
			}
			else if (image[i][k] * value < 0) {
				image[i][k] = 0;
			}
			else {
				image[i][k] *= value;
			}
		}
	}
}
void divImage(int value) {
	printf("���� ������ ó�� \n");
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			if (image[i][k] / value > 255) {
				image[i][k] = 255;
			}
			else if (image[i][k] / value < 0) {
				image[i][k] = 0;
			}
			else {
				image[i][k] /= value;
			}
		}
	}
}

void bwImage() {
	printf("��� ó�� \n");
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {

			if (image[i][k] < 128) {
				image[i][k] = 0;
			}
			else image[i][k] = 255;

		}
	}
	
}

void LRReverseImage() {
	int temp;
	printf("�¿� ����\n");
	for (int i = 0; i < height; i++) {
		for (int k = 0; k <= (width)/2; k++) {
			temp = image[i][k];
			image[i][k] = image[i][width - (k+1)];
			image[i][width - (k+1)] = temp;
		}
		printf("\n");
	}
	printf("\n");
}

void UDReverseImage() {
	int temp;
	printf("���� ����\n");
	for (int i = 0; i < height / 2; i++) {
		for (int k = 0; k < width; k++) {
			temp = image[i][k];
			image[i][k] = image[height - (i + 1)][k];
			image[height - (i + 1)][k] = temp;
		}
		printf("\n");
	}
	printf("\n");

}

void rotatingImage() {
	int temp;
	for (int i = 0; i < height; i++) { // 0~2
		for (int k = 0; k < width; k++) { // 0~4
			rotateImage[k][(height - 1) - i] = image[i][k];
		}
	}
	
}

void rotatePrintImage() {
	for (int i = 0; i < width; i++) {
		for (int k = 0; k < height; k++) {
			printf("%03d ", rotateImage[i][k]);
		}
		printf("\n");
	}
	printf("\n");

}

void binPrintImage2() {
	for (int i = height / 2 - 1; i <= height / 2 + 1; i++) {
		for (int k = width / 2 - 1; k <= width / 2 + 1; k++) {
			printf("%03d ", image[i][k]);
		}
		printf("\n");
	}
	printf("\n");
}

float avgBinPrintImage() {
	float average = 0.0;
	int num = 9; // �̾Ƴ� ���緮 ����
	for (int i = height / 2 - 1; i <= height / 2 + 1; i++) {
		for (int k = width / 2 - 1; k <= width / 2 + 1; k++) {
			average += image[i][k];
		}
	}
	average /= 9.0;
	//printf("��� : %.1f \n", average);
	return average;

}

unsigned char maxBinPrintImage() {
	unsigned char max;
	max = image[height/2-1][width/2-1];
	for (int i = height / 2 - 1; i <= height / 2 + 1; i++) {
		for (int k = width / 2 - 1; k <= width / 2 + 1; k++) {
			if (max < image[i][k]) {
				max = image[i][k];
			}
		}
	}
	return max;
}

unsigned char minBinPrintImage() {
	unsigned char min;
	min = image[height / 2 - 1][width / 2 - 1];
	for (int i = height / 2 - 1; i <= height / 2 + 1; i++) {
		for (int k = width / 2 - 1; k <= width / 2 + 1; k++) {
			if (min > image[i][k]) {
				min = image[i][k];
			}
		}
	}
	return min;
}

void main() {
	srand((unsigned int)time(0)); // Ÿ�̸� �ʱ�ȭ


	// (2) ����(����) --> �޸𸮷� �ε�(loading)
	loadImage();


	// (3) ȭ�鿡 ���
	printImage();

	// (4) ����ó�� �˰��� ����
	// (4-1) ���� ��� ó��(50)
	int value;
	printf("����� �� --> "); scanf("%d", &value);
	addImage(value);
	printImage();

	// (4-2) ���� ��Ӱ� ó��
	// ���� 1 
	printf("��Ӱ��� �� --> ");  scanf("%d", &value);
	subImage(value);
	printImage();

	// (4-3) ��� �����
	// ���� 2
	bwImage();
	printImage();

	// (4-4) �¿� ���� �����
	// ���� 1-1 
	LRReverseImage();
	printImage();
	// (4-5) ���� ���� �����
	// ���� 1-2
	UDReverseImage();
	printImage();
	// (4-6) ���� ���� �����
	// ���� 1-3
	printf("���� �� --> ");  scanf("%d", &value);
	mulImage(value);
	printImage();
	// (4-7) ���� ������ �����
	// ���� 1-4
	printf("���� �� --> ");  scanf("%d", &value);
	divImage(value);
	printImage();
	// (4-8) <��ȭ> ���� 90�� ȸ��
	// ���� 1-5
	rotatingImage();
	rotatePrintImage();

	// (5-1) ������ RAW ������ �о ��հ�/�ִ밪/�ּҰ��� ���ϱ�
	// ���� 2-1

	char filename[100] = "C:/RAW/Etc_Raw(squre)/flower512.raw";  // ���ϸ�
	FILE* rfp; // ���� ������(���� ������)

	// ���� ó�� 3�ܰ�
	// 1�ܰ� : ���� ����
	rfp = fopen(filename, "rb");
	// 2�ܰ� : ������ 512x512�� �ݺ��ؼ� �б�.. �ѹ濡 512x512 �б�
	fread(image, sizeof(unsigned char), height * width, rfp);

	// 3�ܰ� : ���� �ݱ�
	fclose(rfp);

	// (5-1) ������ RAW ������ �о ��հ�/�ִ밪/�ּҰ��� ���ϱ�
	// ���� 2-1
	float average;
	binPrintImage2();
	average = avgBinPrintImage();
	printf("��� : %.1f \n", average);

	unsigned char max;
	max = maxBinPrintImage();
	printf("�ִ� : %d\n", max);

	unsigned char min;
	min = minBinPrintImage();
	printf("�ּڰ� : %d\n", min);



	// (4- ...) �پ��� ����ó�� �˰��� ����.....
}