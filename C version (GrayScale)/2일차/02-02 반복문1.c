#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void main2() {

	// 정수형 데이터 형식 
	//		char(1byte) ==> -128 ~ +127 . unsigned char ==> 0 ~ 255
	//		short(2byte) ==> -32768 ~ +32767 . unsigned short ==> 0 ~ 65535
	//		int(4byte) ==> -2147483648 ~ +2147483647 . unsigned int ==> 0 ~ 42억
	//		long long(8byte) ==> -900경 ~ +900경 . unsigned long long ==> 0 ~ 1800경
	unsigned char char1 = 128;
	printf("char ==> %d \n", char1);

	// 실수형
	// float(4byte) ==> 소수점 아래 7~8까지 의미
	// double(8byte) ==> 소수점 아래 15까지 의미
	// 실무에서는 데이터를 얼마나 줄여야될지를 생각해봐야 함.
	float float1 = 0.12345678901234567890;
	double double1 = 0.12345678901234567890;
	printf("float ==> %.20f \n", float1);
	printf("double ==> %.20f \n", double1);

	// 문자형 : char ==> 영문자 1글자
	char char2 = 'A';
	printf("%d %c \n", char2 + 1, char2 + 1);

	// 문자열
	char string1[100] = "Hello-World...C++";
	printf("문자열 ==> %s \n", string1);

	// 증감연산자
	int a = 100;

	// 중요!! 헷깔리게 안짜기
	printf("a ==> %d \n", a);
	a++; // a += 1,  a = a + 1
	a++;
	printf("a ==> %d \n", a);

	// 반복문
	// 1부터 100까지의 합계
	long long result = 0;
	for (int i = 0; i <= 100; i++) {
		result += i;
	}
	printf("1~100까지의 합계 : %lld \n", result);

	
	// 퀴즈 1 : 1부터 1000까지의 홀수의 합계
	result = 0;
	for (int j = 1; j <= 1000; j+=2) {
		result += j;
	}
	printf("1~1000까지의 홀수의 합계 : %lld \n", result);

	// 퀴즈 2 : 12345부터 67890의 짝수의 합계
	result = 0;
	for (int k = 12346; k <= 67890; k+=2) {
		result += k;
	}
	printf("12345 ~ 67890 까지의 짝수의 합계 : %lld \n", result);

	// 퀴즈 3 : 1234567 부터 67890000까지 1983의 배수의 합계
	result = 0;
	for (long long l = 1234567; l <= 6789000; l++) {
		if (l % 1983 == 0) {
			result += l;
		}
	}
	printf("1234567 ~ 67890000 까지의 짝수의 합계 : %lld \n", result);

	// 퀴즈 4 : <심화> 2부터 1000까지의 소수의 합계
	result = 0;
	printf("소수 ==> 2, ");
	for (int num = 3; num <= 1000; num+=2) {
		char sosuYN = 'Y';
		for (int div = 2; div < num/2+1; div++) {
			if (num % div == 0) { // 나누어 떨어지니?
				sosuYN = 'N';
				break;
			}
		}
		if (sosuYN == 'Y') {
			printf("%d, ", num);
		}
	}
	
	// 내가 생각한 코드
	// result = 0;
	//int cnt = 0;
	//for (int m = 2; m <= 1000; m++) {
	//	cnt = 0;
	//	for (int n = 2; n <= m; n++) {
	//		
	//		if (m % n != 0) {
	//			
	//		}
	//		else if(m % n == 0)
	//		{
	//			cnt += 1;
	//		}
	//	}

	//	if (cnt == 1) {
	//		printf("%d, ", m);
	//	}
	//	
	//	//printf("\n");
	//}


}