#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>

// 가정 : 영상의 크기가 3행 5열짜리를 처리하자
#define height 3 // 행
#define width 5  // 열
// (0) 메모리 할당 (= 배열 준비)
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
	srand((unsigned int)time(0)); // 타이머 초기화
	

	// (2) 영상(파일) --> 메모리로 로딩(loading)

	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			int pixel = rand() % 256; // rand() : 0~32767까지 랜덤한 숫자
			image[i][k] = pixel;
		}
	}

	// (3) 화면에 출력
	printImage1();
	
	// (4) 영상처리 알고리즘 구현
	// (4-1) 영상 밝게 처리(50)
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
	printf("밝게 처리 \n");
	printImage1();

	// (4-2) 영상 어둡게 처리
	// 퀴즈 1 
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
	printf("어둡게 처리 \n");
	printImage();

	// (4-3) 흑백 만들기
	// 퀴즈 2
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			
			if (image[i][k] < 128) {
				image[i][k] = 0;
			}
			else image[i][k] = 255;
				
		}
	}
	printf("흑백 처리 \n");
	printImage1();
	
	


	// (4-4) 다양한 영상처리 알고리즘 적용.....
}