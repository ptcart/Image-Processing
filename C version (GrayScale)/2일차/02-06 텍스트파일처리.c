#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void main6() {
	char filename[100] = "C:/Windows/win.ini"; // ���ϸ�
	FILE* rfp; // ���� ������ (���� ������)

	char str[200]; // �о�� ����

	// ���� ó�� 3�ܰ�
	// 1�ܰ� : ���� ����
	rfp = fopen(filename, "r");
	// 2�ܰ� : ���� �аų� ���� (�۾��ϱ�)
	while (1) { // 0: False, 0�ܴ�: True
		fgets(str, 200, rfp);
		if (feof(rfp))  break;
		printf("%s", str);
	}
	// 3�ܰ� : ���� �ݱ�
	fclose(rfp);
}