#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void main1() {

	int iNum1, iNum2;
	float iResult;

	printf("숫자1 --> "); scanf("%d", &iNum1);
	printf("숫자2 --> "); scanf("%d", &iNum2);
	
	iResult = iNum1 + iNum2;
	printf("%d + %d = %5.1f \n", iNum1, iNum2, iResult);

	iResult = iNum1 - iNum2;
	printf("%d - %d = %5.1f \n", iNum1, iNum2, iResult);

	iResult = iNum1 * iNum2;
	printf("%d * %d = %5.1f \n", iNum1, iNum2, iResult);

	if (iNum2 == 0) {
		printf("0으로 나누면 나빠요!!");
	}
	else {
		iResult = (float)iNum1 / iNum2; // 캐스팅 방식
		printf("%d / %d = %5.1f \n", iNum1, iNum2, iResult);
	}
}