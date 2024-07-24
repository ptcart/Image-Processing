#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h> // GUI ��� ����
#include <math.h>

///////////////////
// ���� ���� �����
///////////////////
HWND  hwnd; //  ���� ȭ��(�ܺ�, ������)
HDC hdc; // ���� ȭ��(����, ����)


int oriH, oriW, tarH, tarW;
unsigned char** oriImage = NULL;
unsigned char** tarImage = NULL;

unsigned char** comImage = NULL;

char filename[200];  // ���ϸ�

///////////////////
// �Լ� �����
///////////////////
// ���� �Լ���
void loadImage(); void saveImage(); void displayImage(int x, int y); void printMenu();
void mallocOriImage(); void mallocTarImage(); void mallocTarImage2(); void freeOriImage(); void freeTarImage(); void freeTarImage2();
void mallocComImage(); void freeComImage();
// ����ó�� �Լ���
// ȭ���� ó��
void equalImage();
void addImage(); void mulImage(); void divImage();
void reverseImage();
void binaryImage();
void gammaImage();
void orImage(); void andImage(); void xorImage(); void notImage(); void postRising(); void rangeImage(); void paraImage();
void zoomOut(); void zoomIn(); void zoomIn2(); void zoomIn3(); void rotate(); void rotate2(); void move1(); void UDmirror(); void LRmirror(); void rotatezoom();
void histoStretch(); void endIn(); void histoEqual(); void histoSpecification();
void emboss(); void blurr(); void sharpening(); void edge1(); void edge2();

void printMenu() {
	puts("\n GrayScale Image Processing (GA 2)");
	puts("\n 1.����  2.����  9.����");
	puts("\n -------------------------------------ȭ�� �� ó��--------------------------------------------");
	puts("\n A.���Ͽ���  B.���/��Ӱ�  C.����  D.����ȭ");
	puts("\n E.��������  F.AND  G.OR  H.XOR  I.NOT  J.����Ʈ����¡  K.�������� ��ȯ  L.�Ķ󺼶� ��ȯ ");
	puts("\n -------------------------------------������ ó��-------------------------------------");
	puts("\n M.Ȯ��(������)  N.Ȯ��(�����)  O.���  P.ȸ��  Q.ȸ��(����)  R.�̵�  S.���Ϲ���  T.�¿����  %.ȸ��Ȯ��  ^.Ȯ��(�缱�� ����)");
	puts("\n -------------------------------------������׷��� �̿��� ȭ�� �� ó��-------------------------------------");
	puts("\n U.����-��  W.��Ȱȭ  X.������׷� ��Ʈ��Ī  Y.��ȭ");
	puts("\n -------------------------------------ȭ�ҿ���ó�� / ��������-------------------------------------");
	puts("\n Z.������  !.����  @.������  #.��������  $.������");
}
///////////////////
// ���� �ڵ��
///////////////////
void main() {
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);  // ����10��.  ����11(hwnd--> NULL)

	char key = 0;
	while (key != '9') {
		printMenu();
		key = _getch();
		system("cls");
		switch (key) {
		case '1': loadImage(); break;
		case '2': saveImage(); break;
		case 'A':
		case 'a': equalImage(); break;
		case 'B':
		case 'b': addImage(); break;
		case 'C':
		case 'c': reverseImage(); break;
		case 'D':
		case 'd': binaryImage(); break;
		case 'E':
		case 'e': gammaImage(); break;
		case 'F':
		case 'f': andImage(); break;
		case 'G':
		case 'g': orImage();  break;
		case 'H':
		case 'h': xorImage(); break;
		case 'I':
		case 'i': notImage(); break;
		case 'J':
		case 'j': postRising(); break;
		case 'K':
		case 'k': rangeImage(); break;
		case 'L':
		case 'l':  paraImage(); break;
		case 'M':
		case 'm':  zoomIn(); break;
		case 'N':
		case 'n':  zoomIn2(); break;
		case 'O':
		case 'o':  zoomOut(); break;
		case 'P':
		case 'p':  rotate(); break;
		case 'Q':
		case 'q':  rotate2(); break;
		case 'R':
		case 'r':  move1();  break;
		case 'S':
		case 's':  UDmirror(); break;
		case 'T':
		case 't':  LRmirror(); break;
		case 'U':
		case 'u':  endIn(); break;
		case 'W':
		case 'w':  histoEqual(); break;
		case 'X':
		case 'x':  histoStretch(); break;
		case 'Y':
		case 'y':  paraImage(); break;
		case 'Z':
		case 'z':  emboss(); break;
		case '!':  blurr(); break;
		case '@':  sharpening(); break;
		case '#':  edge1(); break;
		case '$':  edge2(); break;
		case '%':  rotatezoom(); break;
		case '^':  zoomIn3(); break;

		case '9': freeOriImage(); freeTarImage(); break;
		}
	}
	puts("�ȳ��� ������~~ ����� ��������...");


}

////////////////////
/// �Լ� ���Ǻ�
////////////////
void mallocOriImage() {
	oriImage = (unsigned char**)malloc(sizeof(unsigned char*) * oriH);
	for (int i = 0; i < oriH; i++)
		oriImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * oriW);
}
void mallocTarImage() {
	tarImage = (unsigned char**)malloc(sizeof(unsigned char*) * tarH);
	for (int i = 0; i < tarH; i++)
		tarImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * tarW);
}
void mallocComImage() {
	comImage = (unsigned char**)malloc(sizeof(unsigned char*) * oriH);
	for (int i = 0; i < oriH; i++) {
		comImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * oriW);
	}
}
void freeOriImage() {
	if (oriImage == NULL)
		return;
	for (int i = 0; i < oriH; i++)
		free(oriImage[i]);
	free(oriImage);
	oriImage = NULL;
}
void freeTarImage() {
	if (tarImage == NULL)
		return;
	for (int i = 0; i < tarH; i++)
		free(tarImage[i]);
	free(tarImage);
	tarImage = NULL;
}
void freeComImage() {
	if (comImage == NULL)
		return;
	for (int i = 0; i < tarH; i++)
		free(comImage[i]);
	free(comImage);
	comImage = NULL;
}
void loadImage() {
	char fullname[200] = "C:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("���ϸ�-->"); scanf("%s", tmpName);  // cat01, dog05, etc11
	strcat(fullname, tmpName);
	strcat(fullname, ".raw");
	strcpy(filename, fullname);

	//(�߿�!) ���������� ũ�⸦ �ľ�!
	FILE* rfp;
	rfp = fopen(filename, "rb");
	if (!rfp) {
		printf("���ϸ� Ʋ����~ \n");
		return;
	}
	fseek(rfp, 0L, SEEK_END); // ������ ������ �̵�
	long long fsize = ftell(rfp);
	fclose(rfp);
	// ���� ���� ũ��
	oriH = oriW = sqrt(fsize);
	// 2���� �޸� �Ҵ�
	freeOriImage();
	mallocOriImage();

	// ���� --> �޸�
	rfp = fopen(filename, "rb");
	for (int i = 0; i < oriH; i++)
		fread(oriImage[i], sizeof(unsigned char), oriW, rfp);
	fclose(rfp);
	//printf("%d ", oriImage[50][50]);
	equalImage();

}
void saveImage() {
	char fullname[200] = "C:/RAW/Pet_RAW(squre)/Pet_RAW(512x512)/";
	char tmpName[50];
	printf("���� ���ϸ�-->"); scanf("%s", tmpName);  // out01, out02 ....
	strcat(fullname, tmpName);
	strcat(fullname, "_512.raw");
	strcpy(filename, fullname);

	FILE* wfp;
	wfp = fopen(filename, "wb");
	// �޸� >> ����
	for (int i = 0; i < tarH; i++) {
		fwrite(tarImage[i], sizeof(unsigned char), tarW, wfp);
	}
	fclose(wfp);
	printf("%s �� �����", filename);
}
void displayImage(int x, int y) {
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			int px = tarImage[i][k];
			SetPixel(hdc, k + x, i + y, RGB(px, px, px));
		}
	}
}
/// <summary>
///  ����ó�� �Լ���
/// </summary>
void equalImage() {
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = oriImage[i][k];
		}
	}
	///////////////////////////////
	displayImage(30, 530);
}
void addImage() {
	equalImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	int value;
	printf("���� ��(-255~+255) :");  scanf("%d", &value);
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			int pixel = oriImage[i][k] + value;
			if (pixel > 255)
				pixel = 255;
			if (pixel < 0)
				pixel = 0;
			tarImage[i][k] = (unsigned char)pixel;
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void mulImage() {
	equalImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	int value;
	printf("���� �� :");  scanf(" %d", &value);
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			int pixel = oriImage[i][k] * value;
			if (pixel > 255)
				pixel = 255;
			if (pixel < 0)
				pixel = 0;
			tarImage[i][k] = (unsigned char)pixel;
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void divImage() {
	equalImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	int value;
	printf("���� �� :");  scanf("%d", &value);
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			int pixel = oriImage[i][k] / value;
			if (pixel > 255)
				pixel = 255;
			if (pixel < 0)
				pixel = 0;
			tarImage[i][k] = (unsigned char)pixel;
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void reverseImage() {  // ���� : 0>255, 1>254, 2>253..... 254>1, 255>0
	equalImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = 255 - oriImage[i][k];
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void binaryImage() {
	equalImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = oriImage[i][k];
		}
	}

	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			if (tarImage[i][k] < 127) {
				tarImage[i][k] = 0;
			}
			else tarImage[i][k] = 255;
		}
	}
	/////////////////////////////////
	displayImage(300, 550);
}
void gammaImage() {
	equalImage();
	int gamma;
	printf("���� ���� : "); scanf("%d", &gamma);
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();
	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = oriImage[i][k] / gamma;
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void orImage() {
	equalImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();
	// comImage[oriH][oriW] ũ��� �Ҵ�
	freeComImage();
	mallocComImage();

	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW / 2; k++) {
			comImage[i][k] = 0;
		}
		for (int k = oriW / 2; k < oriW; k++) {
			comImage[i][k] = 255;
		}
	}
	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = oriImage[i][k];
		}
	}

	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			if ((tarImage[i][k] | comImage[i][k]) >= 255) {
				tarImage[i][k] = 255;
			}
			else if ((tarImage[i][k] | comImage[i][k]) <= 0) {
				tarImage[i][k] = 0;
			}
			else
				tarImage[i][k] = tarImage[i][k] | comImage[i][k];
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void andImage() {
	equalImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();
	// comImage[oriH][oriW] ũ��� �Ҵ�
	freeComImage();
	mallocComImage();
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW / 2; k++) {
			comImage[i][k] = 0;
		}
		for (int k = oriW / 2; k < oriW; k++) {
			comImage[i][k] = 255;
		}
	}
	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = oriImage[i][k];
		}
	}
	// and �˰���
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			if ((tarImage[i][k] & comImage[i][k]) >= 255) {
				tarImage[i][k] = 255;
			}
			else if ((tarImage[i][k] & comImage[i][k]) < 0) {
				tarImage[i][k] = 0;
			}
			else
				tarImage[i][k] = tarImage[i][k] & comImage[i][k];
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void xorImage() {
	equalImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();
	// comImage[oriH][oriW] ũ��� �Ҵ�
	freeComImage();
	mallocComImage();
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW / 2; k++) {
			comImage[i][k] = 0;
		}
		for (int k = oriW / 2; k < oriW; k++) {
			comImage[i][k] = 255;
		}
	}
	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = oriImage[i][k];
		}
	}
	// xor �˰���
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			if ((tarImage[i][k] ^ comImage[i][k]) >= 255) {
				tarImage[i][k] = 255;
			}
			else if ((tarImage[i][k] ^ comImage[i][k]) < 0) {
				tarImage[i][k] = 0;
			}
			else
				tarImage[i][k] = tarImage[i][k] ^ comImage[i][k];
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void notImage() {
	equalImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = oriImage[i][k];
		}
	}
	// not �˰���
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			if (!(tarImage[i][k]) >= 255) {
				tarImage[i][k] = 255;
			}
			else if (!(tarImage[i][k]) < 0) {
				tarImage[i][k] = 0;
			}
			else
				tarImage[i][k] = !tarImage[i][k];
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void postRising() {
	equalImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = oriImage[i][k];
		}
	}
	int value;
	int div;
	printf("��� �� : "); scanf("%d", &value);
	div = 255 / value;
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			for (int m = 0; m < value; m++) {
				if (tarImage[i][k] >= div * m && tarImage[i][k] < div * (m + 1)) {
					tarImage[i][k] = div * m;
					break;
				}
			}
		}
	}

	/////////////////////////////
	displayImage(300, 550);
}
void rangeImage() {
	equalImage();
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�

	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = oriImage[i][k];
		}
	}
	int start;
	int end;
	printf("���� ��(2�� / 0~255) : "); scanf("%d %d", &start, &end);
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			if (start <= tarImage[i][k] && tarImage[i][k] <= end)
				tarImage[i][k] = 255;
		}
	}
	/////////////////////////////
	displayImage(300, 550);
}
void paraImage() {
	equalImage();
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�

	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = oriImage[i][k];
		}
	}
	double value;
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			value = 255.0 - 255.0 * pow((tarImage[i][k] / 128.0 - 1.0), 2);
			tarImage[i][k] = (unsigned char)value;
		}
	}
	/////////////////////////////
	displayImage(300, 550);
}
void zoomOut() {
	equalImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	int scale;
	printf("��� ����:"); scanf("%d", &scale);
	tarH = (int)(oriH / scale);
	tarW = (int)(oriW / scale);
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriH; k++) {
			tarImage[i / scale][k / scale] = oriImage[i][k];
		}
	}

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarH; k++) {
			tarImage[i][k] = oriImage[i * scale][k * scale]; //����� ���
		}
	}

	///////////////////////////////
	displayImage(700, 600);
}
void zoomIn() {
	equalImage();
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	int scale;
	printf("Ȯ�� ����:"); scanf("%d", &scale);
	tarH = (int)(oriH * scale);
	tarW = (int)(oriW * scale);
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�	
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i * scale][k * scale] = oriImage[i][k];
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void zoomIn2() {
	equalImage();
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	int scale;
	printf("Ȯ�� ����:"); scanf("%d", &scale);
	tarH = (int)(oriH * scale);
	tarW = (int)(oriW * scale);
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�	
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			tarImage[i][k] = oriImage[i / scale][k / scale];
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void zoomIn3() {
	equalImage();
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	int scale;
	printf("Ȯ�� ����:"); scanf("%d", &scale);
	tarH = (int)(oriH * scale);
	tarW = (int)(oriW * scale);
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�	
	mallocTarImage();

	int iScale;
	int kScale;
	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			iScale = i / scale;
			kScale = k / scale;
			tarImage[i][k] = oriImage[iScale][kScale];
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}

void rotate() {
	equalImage();
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�

	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	int angle;
	printf("ȸ������ : "); scanf("%d", &angle);
	//ȸ�� ����
	// tar_X = cos * oriX - sin * oriY
	// tar_y = sin * oriX + cos * oriY

	//radian = degree * 3.141592 / 180.0

	double radian = angle * 3.141592 / 180.0;
	int tarX, tarY, oriX, oriY;
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			oriX = i;
			oriY = k;
			tarX = cos(radian) * oriX - sin(radian) * oriY;
			tarY = sin(radian) * oriX + cos(radian) * oriY;

			if ((0 <= tarX && tarX < tarH) && (0 <= tarY && tarY < tarW))
				tarImage[tarX][tarY] = oriImage[oriX][oriY];
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void rotate2() {
	equalImage();
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�

	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	int angle;
	printf("ȸ������ : "); scanf("%d", &angle);
	//ȸ�� ����
	// oriX = cos * (tarX - Cx) + sin(tarY - Cy) + Cx
	// oriY = -sin * (tarX - Cx) + cos * (tarY - Cy) + Cy
	int Cx = oriH / 2;
	int Cy = oriW / 2;
	//radian = degree * 3.141592 / 180.0
	double radian = angle * 3.141592 / 180.0;
	int tarX, tarY, oriX, oriY;
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			tarX = i;
			tarY = k;
			oriX = cos(radian) * (tarX - Cx) + sin(radian) * (tarY - Cy) + Cx;
			oriY = -sin(radian) * (tarX - Cx) + cos(radian) * (tarY - Cy) + Cy;

			if ((0 <= oriX && oriX < oriH) && (0 <= oriY && oriY < oriW))
				tarImage[tarX][tarY] = oriImage[oriX][oriY];
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void move1() {
	equalImage();
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�

	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	int dX;
	int dY;
	printf("X �� : "); scanf("%d", &dX);
	printf("Y �� : "); scanf("%d", &dY);
	//�̵� ����
	// tarX = oriX + dX
	// tarY = oriY + dY

	int tarX, tarY, oriX, oriY;
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			oriX = i;
			oriY = k;
			tarX = oriX + dX;
			tarY = oriY + dY;
			if ((0 <= tarX && tarX < tarH) && (0 <= tarY && tarY < tarW))
				tarImage[tarX][tarY] = oriImage[oriX][oriY];
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void UDmirror() {
	equalImage();
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****

	// ���� ���� ����
	// tarX = oriX 
	// tarY = -Y + 2Y0
	int X0 = oriW / 2;
	int tarX, tarY, oriX, oriY;
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			oriX = i;
			oriY = k;
			tarX = (-1 * (oriX + 1)) + 2 * X0;
			tarY = oriY;

			tarImage[tarX][tarY] = oriImage[oriX][oriY];
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void LRmirror() {
	equalImage();
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****

	// ���� ���� ����
	// tarX = oriX 
	// tarY = -Y + 2Y0
	int Y0 = oriH / 2;
	int tarX, tarY, oriX, oriY;
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			oriX = i;
			oriY = k;
			tarX = oriX;
			tarY = (-1 * (oriY + 1)) + 2 * Y0;

			tarImage[tarX][tarY] = oriImage[oriX][oriY];
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void rotatezoom() {
	equalImage();
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	int angle;
	printf("ȸ������ : "); scanf("%d", &angle);

	double radian = angle * 3.141592 / 180.0;
	double radian90 = (90 - angle) * 3.141592 / 180.0;

	tarH = oriH * cos(radian) + oriW * cos(radian90);
	tarW = oriH * cos(radian90) + oriW * cos(radian);

	int oriCx = oriH / 2;
	int oriCy = oriW / 2;
	int tarCx = tarH / 2;
	int tarCy = tarW / 2;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	mallocTarImage();
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			tarImage[i][k] = 0;
		}
	}
	// *** ��¥ ����ó�� �˰��� ****
	int tarX, tarY, oriX, oriY;
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			tarX = i;
			tarY = k;
			oriX = cos(radian) * (tarX - tarCx) + sin(radian) * (tarY - tarCy) + oriCx;
			oriY = -sin(radian) * (tarX - tarCx) + cos(radian) * (tarY - tarCy) + oriCy;
			if ((0 <= oriX && oriX < oriH) && (0 <= oriY && oriY < oriW))
				tarImage[tarX][tarY] = oriImage[oriX][oriY];
		}
	}

	///////////////////////////////
	displayImage(300, 550);
}
void histoStretch() {
	equalImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// ���� : new = (old - low) / (high - low) * 255.0
	int low, high;
	low = high = oriImage[0][0];

	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			if (oriImage[i][k] < low) {
				low = oriImage[i][k];
			}
			if (oriImage[i][k] > high) {
				high = oriImage[i][k];
			}
		}
	}


	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = (double)(oriImage[i][k] - low) / (high - low) * 255;
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void endIn() {
	equalImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// ���� : new = (old - low) / (high - low) * 255.0
	int low, high;
	low = high = oriImage[0][0];

	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			if (oriImage[i][k] < low) {
				low = oriImage[i][k];
			}
			if (oriImage[i][k] > high) {
				high = oriImage[i][k];
			}
		}
	}

	low = low + 50;
	high = high - 50;
	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			double newVal = (double)(oriImage[i][k] - low) / (high - low) * 255;
			if (newVal < 0.0)
				newVal = 0;
			else if (newVal > 255.0)
				newVal = 255;
			tarImage[i][k] = newVal;
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
void histoEqual() {
	equalImage();
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�

	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = oriImage[i][k];
		}
	}

	// 1�ܰ� : �󵵼� ������׷� ����
	int hist[256] = { 0, };

	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			hist[tarImage[i][k]]++;
		}
	}
	// 2�ܰ� : ���� ������׷� ����
	int sum[256];
	sum[0] = hist[0];
	for (int i = 1; i < 256; i++) {
		sum[i] = hist[i] + sum[i - 1];
	}
	// 3�ܰ� : ����ȭ�� ������׷� ����
	double n[256] = { 0.0, };
	for (int i = 0; i < 256; i++) {
		n[i] = sum[i] * (1.0 / (oriW * oriH)) * 255.0;
	}
	// 4�ܰ� : �������� ����ȭ�� ������ ġȯ
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			tarImage[i][k] = (unsigned char)n[oriImage[i][k]];
		}
	}
	///////////////////////////////
	displayImage(300, 550);
}
double** mallocDouble(int h, int w) {
	double** memory;
	memory = (double**)malloc(sizeof(double*) * h);
	for (int i = 0; i < h; i++)
		memory[i] = (double*)malloc(sizeof(double) * w);
	return memory;
}
void freeDouble(double** memory, int h) {
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		free(memory[i]);
	free(memory);
	memory = NULL;
}
void emboss() {
	equalImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	//const int MSIZE = 3; // ����ũ ũ��
#define MSIZE 3
	double mask[MSIZE][MSIZE] = {
		{ 1.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0,-1.0 } };

	// �ӽ� ����� �޸� �غ�
	double** tmpOriImage, ** tmpTarImage;
	tmpOriImage = mallocDouble(oriH + 2, oriW + 2);
	tmpTarImage = mallocDouble(tarH, tarW);
	// �ӽ� ���� �̹����� 127 ä���(��հ��� �� ������...)
	for (int i = 0; i < oriH + 2; i++) {
		for (int k = 0; k < oriW + 2; k++) {
			tmpOriImage[i][k] = 127.0;
		}
	}
	// ���� -> �ӽ� ����
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tmpOriImage[i + 1][k + 1] = oriImage[i][k];
		}
	}
	// ȸ�� ���� ---> ����ũ�� �ܾ�鼭 ����ϱ�
	double S = 0; // �� ���� ���� ����ũ ���� �հ�

	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			S = 0.0; // ���� �ʱ�ȭ
			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S += mask[m][n] * tmpOriImage[i + m][k + n];
				}
			}
			tmpTarImage[i][k] = S;
			tarImage[i][k] = oriImage[i][k];
		}
	}
	// Post Processing (��ó��). ����ũ �հ谡 0�̸� 127������ ����.
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			tmpTarImage[i][k] += 127.0;
		}
	}
	// �ӽ� Ÿ�� --> Ÿ��
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			double v = tmpTarImage[i][k];
			if (v < 0.0) {
				v = 0.0;
			}
			if (v > 255.0) {
				v = 255.0;
			}
			tarImage[i][k] = v;
		}
	}


	freeDouble(tmpOriImage, oriH + 2);
	freeDouble(tmpTarImage, tarH);
	///////////////////////////////
	displayImage(300, 550);
}
void blurr() {
	equalImage();
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	//const int MSIZE = 3; // ����ũ ũ��
#define MSIZE 3
	double mask[MSIZE][MSIZE] = {
		{ 1.0 / 9, 1.0 / 9, 1.0 / 9 },
		{ 1.0 / 9, 1.0 / 9, 1.0 / 9 },
		{ 1.0 / 9, 1.0 / 9, 1.0 / 9 } };

	// �ӽ� ����� �޸� �غ�
	double** tmpOriImage, ** tmpTarImage;
	tmpOriImage = mallocDouble(oriH + 2, oriW + 2);
	tmpTarImage = mallocDouble(tarH, tarW);
	// �ӽ� ���� �̹����� 127 ä���(��հ��� �� ������...)
	for (int i = 0; i < oriH + 2; i++) {
		for (int k = 0; k < oriW + 2; k++) {
			tmpOriImage[i][k] = 127.0;
		}
	}
	// ���� -> �ӽ� ����
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tmpOriImage[i + 1][k + 1] = oriImage[i][k];
		}
	}
	// ȸ�� ���� ---> ����ũ�� �ܾ�鼭 ����ϱ�
	double S = 0; // �� ���� ���� ����ũ ���� �հ�
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			S = 0.0; // ���� �ʱ�ȭ
			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S += mask[m][n] * tmpOriImage[i + m][k + n];
				}
			}
			tmpTarImage[i][k] = S;
			tarImage[i][k] = oriImage[i][k];
		}
	}
	// �ӽ� Ÿ�� --> Ÿ��
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			double v = tmpTarImage[i][k];
			if (v < 0.0) {
				v = 0.0;
			}
			if (v > 255.0) {
				v = 255.0;
			}
			tarImage[i][k] = v;
		}
	}


	freeDouble(tmpOriImage, oriH + 2);
	freeDouble(tmpTarImage, tarH);
	///////////////////////////////
	displayImage(300, 550);
}
void sharpening() {
	equalImage();
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	//const int MSIZE = 3; // ����ũ ũ��
#define MSIZE 3
	double mask[MSIZE][MSIZE] = {
		{ -1.0, -1.0, -1.0 },
		{ -1.0,  9.0, -1.0 },
		{ -1.0, -1.0, -1.0 } };

	// �ӽ� ����� �޸� �غ�
	double** tmpOriImage, ** tmpTarImage;
	tmpOriImage = mallocDouble(oriH + 2, oriW + 2);
	tmpTarImage = mallocDouble(tarH, tarW);
	// �ӽ� ���� �̹����� 127 ä���(��հ��� �� ������...)
	for (int i = 0; i < oriH + 2; i++) {
		for (int k = 0; k < oriW + 2; k++) {
			tmpOriImage[i][k] = 127.0;
		}
	}
	// ���� -> �ӽ� ����
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tmpOriImage[i + 1][k + 1] = oriImage[i][k];
		}
	}
	// ȸ�� ���� ---> ����ũ�� �ܾ�鼭 ����ϱ�
	double S = 0; // �� ���� ���� ����ũ ���� �հ�
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			S = 0.0; // ���� �ʱ�ȭ
			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S += mask[m][n] * tmpOriImage[i + m][k + n];
				}
			}
			tmpTarImage[i][k] = S;
			tarImage[i][k] = oriImage[i][k];
		}
	}
	// �ӽ� Ÿ�� --> Ÿ��
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			double v = tmpTarImage[i][k];
			if (v < 0.0) {
				v = 0.0;
			}
			if (v > 255.0) {
				v = 255.0;
			}
			tarImage[i][k] = v;
		}
	}


	freeDouble(tmpOriImage, oriH + 2);
	freeDouble(tmpTarImage, tarH);
	///////////////////////////////
	displayImage(300, 550);
}
void edge1() {
	equalImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	//const int MSIZE = 3; // ����ũ ũ��
#define MSIZE 3
	double mask[MSIZE][MSIZE] = {
		{ 0.0, 0.0, 0.0 },
		{ -1.0, 1.0, 0.0 },
		{ 0.0, 0.0,-0.0 } };

	// �ӽ� ����� �޸� �غ�
	double** tmpOriImage, ** tmpTarImage;
	tmpOriImage = mallocDouble(oriH + 2, oriW + 2);
	tmpTarImage = mallocDouble(tarH, tarW);
	// �ӽ� ���� �̹����� 127 ä���(��հ��� �� ������...)
	for (int i = 0; i < oriH + 2; i++) {
		for (int k = 0; k < oriW + 2; k++) {
			tmpOriImage[i][k] = 127.0;
		}
	}
	// ���� -> �ӽ� ����
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tmpOriImage[i + 1][k + 1] = oriImage[i][k];
		}
	}
	// ȸ�� ���� ---> ����ũ�� �ܾ�鼭 ����ϱ�
	double S = 0; // �� ���� ���� ����ũ ���� �հ�

	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			S = 0.0; // ���� �ʱ�ȭ
			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S += mask[m][n] * tmpOriImage[i + m][k + n];
				}
			}
			tmpTarImage[i][k] = S;
			tarImage[i][k] = oriImage[i][k];
		}
	}
	// �ӽ� Ÿ�� --> Ÿ��
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			double v = tmpTarImage[i][k];
			if (v < 0.0) {
				v = 0.0;
			}
			if (v > 255.0) {
				v = 255.0;
			}
			tarImage[i][k] = v;
		}
	}


	freeDouble(tmpOriImage, oriH + 2);
	freeDouble(tmpTarImage, tarH);
	///////////////////////////////
	displayImage(500, 500);
}
void edge2() {
	equalImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	//const int MSIZE = 3; // ����ũ ũ��
#define MSIZE 3
	double mask[MSIZE][MSIZE] = {
		{ 0.0, -1.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 0.0, 0.0 } };

	// �ӽ� ����� �޸� �غ�
	double** tmpOriImage, ** tmpTarImage;
	tmpOriImage = mallocDouble(oriH + 2, oriW + 2);
	tmpTarImage = mallocDouble(tarH, tarW);

	// �ӽ� ���� �̹����� 127 ä���(��հ��� �� ������...)
	for (int i = 0; i < oriH + 2; i++) {
		for (int k = 0; k < oriW + 2; k++) {
			tmpOriImage[i][k] = 127.0;
		}
	}
	// ���� -> �ӽ� ����
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tmpOriImage[i + 1][k + 1] = oriImage[i][k];
		}
	}

	// ȸ�� ���� ---> ����ũ�� �ܾ�鼭 ����ϱ�
	double S = 0; // �� ���� ���� ����ũ ���� �հ�

	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			S = 0.0; // ���� �ʱ�ȭ
			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S += mask[m][n] * tmpOriImage[i + m][k + n];
				}
			}
			tmpTarImage[i][k] = S;
			tarImage[i][k] = oriImage[i][k];
		}
	}
	// �ӽ� Ÿ�� --> Ÿ��
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			double v = tmpTarImage[i][k];
			if (v < 0.0) {
				v = 0.0;
			}
			if (v > 255.0) {
				v = 255.0;
			}
			tarImage[i][k] = v;
		}
	}


	freeDouble(tmpOriImage, oriH + 2);
	freeDouble(tmpTarImage, tarH);
	///////////////////////////////
	displayImage(500, 500);
}