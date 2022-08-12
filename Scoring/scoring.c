#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>



struct Input {
	char name[10]; //�̸�
	char dap[5];//�Է��� ��
};

typedef struct {
	struct Input in;//�̸��� �Է��� ���� �����ϴ� ���ڵ� 
	char ox[5]; //OXǥ�� 
	int score; //���� 
	char dr[10];//�հ�, ���հ� ����
}Output;

char jungdap[5] = { '1', '2', '1', '2', '3' }; //����.

int Menu();
void AddData();
void Display(struct Input* in, int n);
void DelFile();
void SearchRec(struct Input* in); //�����Լ� ����
FILE* fp; //���� ���� ������ fq ����;
int Menu() {
	int x;
	puts("<<�޴�>>\n\n");
	puts("-----------------------");
	puts("1. �� ��");
	puts("2. ä �� �� ��");
	puts("3. ���� ����");
	puts("4. ���ڵ� �˻�");
	puts("5. �� ��");
	puts("-----------------------");
	printf("����(1-5):");
	scanf_s("%d", &x);
	return x;
}
void AddData() {

	struct Input in;
	//FILE *fp
	fopen_s(&fp, "data.txt", "a");  // &fp�� �ִ� data.txt�� ���� ������ ���� ���ο� ������ �߰�

	fflush(stdin);
	printf("�̸��Է�: ");
	scanf_s("%s", &in.name, sizeof(in.name));

	char name[10] = { 0 };
	printf("�����Է� :");
	for (int i = 0; i < 5; i++) {
		in.dap[i] = _getche();
	}

	fwrite(&in, sizeof(in), 1, fp); // ����ü ���� in�� �ִ� ���� sizeof(in) ��ŭ ���Ͽ� �ѹ� ���ش�.

	fclose(fp);

	_getch();
	//�ڵ带 �ۼ��մϴ�. 
}

void Display(struct Input* in, int n) {

	Output* out = (Output*)malloc(n * sizeof(Output));
	FILE* fp;
	fopen_s(&fp, "data.txt", "a");
	int i, j;
	system("cls");
	printf("\n\n\t\t<<ä�� ���>>\n\n");
	printf("%25s", "���� :");
	for (j = 0; j < 5; j++)
		printf("%3c", jungdap[j]);



	for (i = 0; i < n; i++) {
		out[i].in = in[i];
		puts("\n---------------------------------\n");
		printf("[No.%-2d%6s]�� �Է��� ��: ", i + 1, out[i].in.name);
		for (j = 0; j < 5; j++) {
			printf("%3c", out[i].in.dap[j]);
		}

		printf("\n\t\t\t   ");


		out[i].score = 0;//��� score �� �ʱ�ȭ
		for (int j = 0; j < 5; j++)
		{
			if (jungdap[j] == out[i].in.dap[j]) { //�Է°��� ������ ������� 
				out[i].score += 20;//score���� 20�� �����ش�
				out[i].ox[j] = 'O';//out[i].ox[j]�� 'O'����
			}
			else
				out[i].ox[j] = 'X'; // �ƴҰ�� 'X'����

			printf("%3c", out[i].ox[j]);
		}

		if (out[i].score >= 80)//score���� 80�̻��� ���
			strcpy_s(out[i].dr, sizeof(out[i].dr), "�հ�");
		//����ü Output�� �ִ� ��� dr�� "�հ�" ���ڿ� ����, out�� ����ü Output�� �����ͺ���
		else
			strcpy_s(out[i].dr, sizeof(out[i].dr), "���հ�");
		//����ü Output�� �ִ� ��� dr�� "���հ�" ���ڿ� ����
		printf(" %3d�� %7s", out[i].score, out[i].dr); //������ �հݿ��� ���
	}
	fclose(fp); //���� �ݱ�
	_getch();
	//�ڵ带 �ۼ��մϴ�. 

}


void DelFile() {
	int a;
	printf("���� ������ �����Ͻðڽ��ϱ�(Y/N)?");
	fflush(stdin);
	a = _getch();
	if (a == 'y' || a == 'Y') {
		system("del data.txt");
		puts("������ �����Ǿ����ϴ�");
	}
	else
		puts("���� ������ ���");
	/*puts("���� ������ ��ҵǾ����ϴ�");*/
	_getch();
}

void SearchRec(struct Input* in)
{
	int rec;
	printf("�˻��� ���ڵ� ��ȣ�� ? ");
	scanf_s("%d", &rec);
	Display(in + (rec - 1), 1);
}

void main() {
	struct Input* in = NULL;//����ü ������ in ����
	int x, n = 0;
	while (1) {
		system("cls");
		x = Menu();
		if (x == 5) return;

		if (x == 2 || x == 4)
		{
			fopen_s(&fp, "data.txt", "r");
			if (fp == NULL)
			{
				puts("���� ã�� ����");
				return;
			}
			fseek(fp, 0, SEEK_END); //������ ������ ��ġ�� �̵�
			n = ftell(fp) / sizeof(struct Input); //ftell(fp)�� ������ ��ġ�� ��ġ ���� ��ȯ 
			fseek(fp, 0, SEEK_SET);//������ ó�� ��ġ�� �̵��Ѵ�.
			in = (struct Input*)malloc(n * sizeof(struct Input));
			//in ����ü ������ ���ڿ��� �����ϱ� ���� �����Ҵ�
			for (int i = 0; i < n; i++)
				fread(&in[i], sizeof(struct Input), 1, fp);
			fclose(fp);
		}
		switch (x)
		{
		case 1:
			AddData();
			break;
		case 2:
			Display(in, n);
			break;
		case 3:
			DelFile();
			break;
		case 4:
			SearchRec(in);
			break;
		}
	}
}
