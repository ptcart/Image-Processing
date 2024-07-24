#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>

// 가정 : 영상의 크기가 3행 5열짜리를 처리하자
#define height 3 // 행
#define width 5  // 열
// (0) 메모리 할당 (= 배열 준비)
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
			int pixel = rand() % 256; // rand() : 0~32767까지 랜덤한 숫자
			image[i][k] = pixel;
		}
	}
}

void addImage(int value) {
	printf("밝게 처리 \n");
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
	printf("어둡게 처리 \n");
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
	printf("영상 곱셈 처리 \n");
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
	printf("영상 나눗셈 처리 \n");
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
	printf("흑백 처리 \n");
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
	printf("좌우 반전\n");
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
	printf("상하 반전\n");
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
	int num = 9; // 뽑아낸 적당량 갯수
	for (int i = height / 2 - 1; i <= height / 2 + 1; i++) {
		for (int k = width / 2 - 1; k <= width / 2 + 1; k++) {
			average += image[i][k];
		}
	}
	average /= 9.0;
	//printf("평균 : %.1f \n", average);
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
	srand((unsigned int)time(0)); // 타이머 초기화


	// (2) 영상(파일) --> 메모리로 로딩(loading)
	loadImage();


	// (3) 화면에 출력
	printImage();

	// (4) 영상처리 알고리즘 구현
	// (4-1) 영상 밝게 처리(50)
	int value;
	printf("밝게할 값 --> "); scanf("%d", &value);
	addImage(value);
	printImage();

	// (4-2) 영상 어둡게 처리
	// 퀴즈 1 
	printf("어둡게할 값 --> ");  scanf("%d", &value);
	subImage(value);
	printImage();

	// (4-3) 흑백 만들기
	// 퀴즈 2
	bwImage();
	printImage();

	// (4-4) 좌우 반전 만들기
	// 과제 1-1 
	LRReverseImage();
	printImage();
	// (4-5) 상하 반전 만들기
	// 과제 1-2
	UDReverseImage();
	printImage();
	// (4-6) 영상 곱셈 만들기
	// 과제 1-3
	printf("곱할 값 --> ");  scanf("%d", &value);
	mulImage(value);
	printImage();
	// (4-7) 영상 나눗셈 만들기
	// 과제 1-4
	printf("나눌 값 --> ");  scanf("%d", &value);
	divImage(value);
	printImage();
	// (4-8) <심화> 영상 90도 회전
	// 과제 1-5
	rotatingImage();
	rotatePrintImage();

	// (5-1) 적당한 RAW 파일을 읽어서 평균값/최대값/최소값을 구하기
	// 과제 2-1

	char filename[100] = "C:/RAW/Etc_Raw(squre)/flower512.raw";  // 파일명
	FILE* rfp; // 파일 포인터(파일 설명자)

	// 파일 처리 3단계
	// 1단계 : 파일 열기
	rfp = fopen(filename, "rb");
	// 2단계 : 파일을 512x512번 반복해서 읽기.. 한방에 512x512 읽기
	fread(image, sizeof(unsigned char), height * width, rfp);

	// 3단계 : 파일 닫기
	fclose(rfp);

	// (5-1) 적당한 RAW 파일을 읽어서 평균값/최대값/최소값을 구하기
	// 과제 2-1
	float average;
	binPrintImage2();
	average = avgBinPrintImage();
	printf("평균 : %.1f \n", average);

	unsigned char max;
	max = maxBinPrintImage();
	printf("최댓값 : %d\n", max);

	unsigned char min;
	min = minBinPrintImage();
	printf("최솟값 : %d\n", min);



	// (4- ...) 다양한 영상처리 알고리즘 적용.....
}