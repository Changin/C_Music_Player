#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <mmsystem.h>	//음악출력을 위함
#include <io.h>			
#include <wchar.h>
#include <string.h>
#pragma comment(lib,"winmm")	//음악출력을 위함

char path[260] = "C:\\Users\\snow\\Desktop\\Music\\*.wav";
char file[260] = { 0, };

typedef struct _finddata_t FILE_SEARCH;	//파일 탐색 구조체

void printMenu(int num, FILE_SEARCH *file_search);	//메뉴 및 파일 출력
void getFileList(int num, FILE_SEARCH *file_search);	//특정 파일 이름 반환
void playMusic(int menu_select, FILE_SEARCH *file_search);	//음악 재생 및 정지

int main() {
	int menu_select = 0;
	FILE_SEARCH file_search;

	while (1) {
		printMenu(menu_select,&file_search);
		scanf("%d", &menu_select);
		if (menu_select == -1) {	//-1입력하면 프로그램 종료
			exit(0);
		}
		system("cls");
		playMusic(menu_select,&file_search);
	}
	
}

void printMenu(int num, FILE_SEARCH *file_search) {	//메뉴 및 파일 리스트 출력
	int i = 1;
	long h_file;

	if (num == 0) {
		printf("\n\n\n\n\t\t select music (-1 to exit): \n");
	}
	else {
		printf("\n\n\n\n\t\t select music (-1 to exit) (0 to stop): Now Playing... %s\n",file);
	}

	if ((h_file = _findfirst(path, file_search)) == -1L) {	//파일 없거나 각종 오류 발생시 함수 종료
		printf("읽기 오류\n");
		return;
	}
	do {
		//char *file = file_search->name;
		strcpy(file, file_search->name);
		printf("\n\t\t%d : %s\n",i, file);
		i++;
	} while (_findnext(h_file, file_search) == 0);			//파일 리스트 출력
	_findclose(h_file);			//스트림 닫기
}

void getFileList(int num, FILE_SEARCH *file_search) {
	//특정 파일 이름 file에 저장
	long h_file;
	int i = 1;
	if ((h_file = _findfirst(path, file_search)) == -1L) {	//파일 없거나 각종 오류 발생시 함수 종료
		printf("읽기 오류\n");
		return;
	}

	do {
		if (i == num) {	//사용자가 입력한 번호에 대치하는 음악 반환
			strcpy(file, file_search->name);
			_findclose(h_file);
		}
		i++;
	} while (i <= num && (_findnext(h_file, file_search) == 0));

}

void playMusic(int menu_select,FILE_SEARCH *file_search) {
	if (menu_select == 0) {	//0이면 음악 끄기
		PlaySound(NULL, 0, 0);
		return;
	}
	getFileList(menu_select, file_search);
	char pStr[260] = "C:\\Users\\snow\\Desktop\\Music\\"; //음악파일 들어간 경로
	strcat(pStr, file);		//문자열 합치기, 음악파일의 절대경로를 만들어줌
	wchar_t sum[260] = { 0, };	//유니코드 형태의 문자열 저장공간
	mbstowcs(sum, pStr, 260);	//유니코드로 복사
	printf("%ls", sum);
	PlaySound(sum, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	return;
}