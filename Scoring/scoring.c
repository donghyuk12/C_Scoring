#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>



struct Input {
	char name[10]; //이름
	char dap[5];//입력할 답
};

typedef struct {
	struct Input in;//이름과 입력한 값을 저장하는 레코드 
	char ox[5]; //OX표시 
	int score; //점수 
	char dr[10];//합격, 불합격 판정
}Output;

char jungdap[5] = { '1', '2', '1', '2', '3' }; //정답.

int Menu();
void AddData();
void Display(struct Input* in, int n);
void DelFile();
void SearchRec(struct Input* in); //전역함수 선언
FILE* fp; //전역 파일 포인터 fq 선언;
int Menu() {
	int x;
	puts("<<메뉴>>\n\n");
	puts("-----------------------");
	puts("1. 추 가");
	puts("2. 채 점 출 력");
	puts("3. 파일 삭제");
	puts("4. 레코드 검색");
	puts("5. 종 료");
	puts("-----------------------");
	printf("선택(1-5):");
	scanf_s("%d", &x);
	return x;
}
void AddData() {

	struct Input in;
	//FILE *fp
	fopen_s(&fp, "data.txt", "a");  // &fp에 있는 data.txt를 열어 파일의 끝에 새로운 내용을 추가

	fflush(stdin);
	printf("이름입력: ");
	scanf_s("%s", &in.name, sizeof(in.name));

	char name[10] = { 0 };
	printf("정답입력 :");
	for (int i = 0; i < 5; i++) {
		in.dap[i] = _getche();
	}

	fwrite(&in, sizeof(in), 1, fp); // 구조체 변수 in에 있는 값을 sizeof(in) 만큼 파일에 한번 써준다.

	fclose(fp);

	_getch();
	//코드를 작성합니다. 
}

void Display(struct Input* in, int n) {

	Output* out = (Output*)malloc(n * sizeof(Output));
	FILE* fp;
	fopen_s(&fp, "data.txt", "a");
	int i, j;
	system("cls");
	printf("\n\n\t\t<<채점 결과>>\n\n");
	printf("%25s", "정답 :");
	for (j = 0; j < 5; j++)
		printf("%3c", jungdap[j]);



	for (i = 0; i < n; i++) {
		out[i].in = in[i];
		puts("\n---------------------------------\n");
		printf("[No.%-2d%6s]이 입력한 답: ", i + 1, out[i].in.name);
		for (j = 0; j < 5; j++) {
			printf("%3c", out[i].in.dap[j]);
		}

		printf("\n\t\t\t   ");


		out[i].score = 0;//멤버 score 값 초기화
		for (int j = 0; j < 5; j++)
		{
			if (jungdap[j] == out[i].in.dap[j]) { //입력값과 정답이 같을경우 
				out[i].score += 20;//score값에 20씩 더해준다
				out[i].ox[j] = 'O';//out[i].ox[j]에 'O'저장
			}
			else
				out[i].ox[j] = 'X'; // 아닐경우 'X'저장

			printf("%3c", out[i].ox[j]);
		}

		if (out[i].score >= 80)//score값이 80이상일 경우
			strcpy_s(out[i].dr, sizeof(out[i].dr), "합격");
		//구조체 Output에 있는 멤버 dr에 "합격" 문자열 복사, out은 구조체 Output의 포인터변수
		else
			strcpy_s(out[i].dr, sizeof(out[i].dr), "불합격");
		//구조체 Output에 있는 멤버 dr에 "불합격" 문자열 복사
		printf(" %3d점 %7s", out[i].score, out[i].dr); //점수와 합격여부 출력
	}
	fclose(fp); //파일 닫기
	_getch();
	//코드를 작성합니다. 

}


void DelFile() {
	int a;
	printf("정말 파일을 삭제하시겠습니까(Y/N)?");
	fflush(stdin);
	a = _getch();
	if (a == 'y' || a == 'Y') {
		system("del data.txt");
		puts("파일이 삭제되었습니다");
	}
	else
		puts("파일 삭제가 취소");
	/*puts("파일 삭제가 취소되었습니다");*/
	_getch();
}

void SearchRec(struct Input* in)
{
	int rec;
	printf("검색할 레코드 번호는 ? ");
	scanf_s("%d", &rec);
	Display(in + (rec - 1), 1);
}

void main() {
	struct Input* in = NULL;//구조체 포인터 in 선언
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
				puts("파일 찾기 실패");
				return;
			}
			fseek(fp, 0, SEEK_END); //파일의 마지막 위치로 이동
			n = ftell(fp) / sizeof(struct Input); //ftell(fp)로 현재의 위치의 위치 값을 반환 
			fseek(fp, 0, SEEK_SET);//파일의 처음 위치로 이동한다.
			in = (struct Input*)malloc(n * sizeof(struct Input));
			//in 구조체 변수에 문자열을 삽입하기 위해 동적할당
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
