#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void main2() {

	// ������ ������ ���� 
	//		char(1byte) ==> -128 ~ +127 . unsigned char ==> 0 ~ 255
	//		short(2byte) ==> -32768 ~ +32767 . unsigned short ==> 0 ~ 65535
	//		int(4byte) ==> -2147483648 ~ +2147483647 . unsigned int ==> 0 ~ 42��
	//		long long(8byte) ==> -900�� ~ +900�� . unsigned long long ==> 0 ~ 1800��
	unsigned char char1 = 128;
	printf("char ==> %d \n", char1);

	// �Ǽ���
	// float(4byte) ==> �Ҽ��� �Ʒ� 7~8���� �ǹ�
	// double(8byte) ==> �Ҽ��� �Ʒ� 15���� �ǹ�
	// �ǹ������� �����͸� �󸶳� �ٿ��ߵ����� �����غ��� ��.
	float float1 = 0.12345678901234567890;
	double double1 = 0.12345678901234567890;
	printf("float ==> %.20f \n", float1);
	printf("double ==> %.20f \n", double1);

	// ������ : char ==> ������ 1����
	char char2 = 'A';
	printf("%d %c \n", char2 + 1, char2 + 1);

	// ���ڿ�
	char string1[100] = "Hello-World...C++";
	printf("���ڿ� ==> %s \n", string1);

	// ����������
	int a = 100;

	// �߿�!! ��򸮰� ��¥��
	printf("a ==> %d \n", a);
	a++; // a += 1,  a = a + 1
	a++;
	printf("a ==> %d \n", a);

	// �ݺ���
	// 1���� 100������ �հ�
	long long result = 0;
	for (int i = 0; i <= 100; i++) {
		result += i;
	}
	printf("1~100������ �հ� : %lld \n", result);

	
	// ���� 1 : 1���� 1000������ Ȧ���� �հ�
	result = 0;
	for (int j = 1; j <= 1000; j+=2) {
		result += j;
	}
	printf("1~1000������ Ȧ���� �հ� : %lld \n", result);

	// ���� 2 : 12345���� 67890�� ¦���� �հ�
	result = 0;
	for (int k = 12346; k <= 67890; k+=2) {
		result += k;
	}
	printf("12345 ~ 67890 ������ ¦���� �հ� : %lld \n", result);

	// ���� 3 : 1234567 ���� 67890000���� 1983�� ����� �հ�
	result = 0;
	for (long long l = 1234567; l <= 6789000; l++) {
		if (l % 1983 == 0) {
			result += l;
		}
	}
	printf("1234567 ~ 67890000 ������ ¦���� �հ� : %lld \n", result);

	// ���� 4 : <��ȭ> 2���� 1000������ �Ҽ��� �հ�
	result = 0;
	printf("�Ҽ� ==> 2, ");
	for (int num = 3; num <= 1000; num+=2) {
		char sosuYN = 'Y';
		for (int div = 2; div < num/2+1; div++) {
			if (num % div == 0) { // ������ ��������?
				sosuYN = 'N';
				break;
			}
		}
		if (sosuYN == 'Y') {
			printf("%d, ", num);
		}
	}
	
	// ���� ������ �ڵ�
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