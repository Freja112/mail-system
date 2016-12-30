#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
// windows.h 파일에서 자주 사용하지 않은 요소를 컴파일에서 제외시킨다.
// 컴파일 속도가 빨라지고 winsock2.h와의 충돌이 일어나지 않는다.
#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <string.h>
#include "RevStruct.h"
#include "sql_info.h"
using namespace std;
#pragma comment ( lib, "ws2_32.lib" )
#pragma pack( 1 ) // 구조체에서 1byte 단위로 메모리를 Align하라는 지시어

MYSQL_ROW row;
MYSQL_RES *m_res;
MYSQL mysql;

int MySQL_member(char* id, char* pw)
{
	char query[255] = "select * from member where id='";

	//query = "select * from member where id='";
	strcat_s(query, 255, id);
	strcat_s(query, 255, "' and pw='");
	strcat_s(query, 255, pw);
	strcat_s(query, 255, "'\0");

	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0)) {
		//AfxMessageBox(_T("DB연결오류"));
		printf("DB연결 오류\n");
	}

	if (mysql_query(&mysql, query))
	{ // 쿼리 요청
		printf("쿼리요청 실패\n");
		return 0;
	}

	m_res = mysql_store_result(&mysql);
	if (mysql_num_rows(m_res)>0){
		printf("요청한 로그인 정보와 일치하는 데이터 존재\n");
	}
	else
	{ // 결과를 m_Res에 저장
		printf("요청한 로그인 정보 불일치\n");
		return 0;
	}

	while ((row = mysql_fetch_row(m_res)) != NULL)
	{
		// 출력창에 디버깅 용으로 
		printf("mysql에 받은 값입니다 : %s %s\n", row[0], row[1]);
	}

	return 1;
}


void MySQL_mailbox(char* id, void* p){
	SOCKET s = (SOCKET)p;

	char query[255] = "select fromid, title from mail where toid='";
	char send_data[70];

	strcat_s(query, 255, id);
	strcat_s(query, 255, "'\0");

	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0)) {
		//AfxMessageBox(_T("DB연결오류"));
		printf("DB연결 오류\n");
	}

	if (mysql_query(&mysql, query))
	{ // 쿼리 요청
		printf("쿼리요청 실패\n");
		return;
	}

	m_res = mysql_store_result(&mysql);
	if (mysql_num_rows(m_res)>0){
		printf("받은 메일 조회 결과 있음\n");
	}
	else
	{ // 결과를 m_Res에 저장
		printf("받은 메일이 존재하지 않음\n");
		send(s, "0\0", 2, 0);
		return;
	}

	int row_count = (int) mysql_num_rows(m_res);
	_itoa(row_count, send_data, 10);
	//printf("%s\n", send_data);
	send(s, send_data, strlen(send_data) + 1, 0);
	

	while ((row = mysql_fetch_row(m_res)) != NULL)
	{
		// 출력창에 디버깅 용으로 
		printf("mysql에 받은 값입니다 : %s / %s\n", row[0], row[1]);
		strcpy_s(send_data, 70, row[0]);
		strcat_s(send_data, 70, "/");
		strcat_s(send_data, 70, row[1]);
		strcat_s(send_data, 70, "\0");
		//printf("%d : %s\n", strlen(send_data)+1, send_data);

		send(s, send_data, strlen(send_data) + 1, 0);		//+1은 null문자가 들어가게 하기 위해 삽입
		Sleep(500);
	}
}

void MySQL_mailview(char* toid, char* title, void* p){
	SOCKET s = (SOCKET)p;

	char query[255] = "select fromid, title, content from mail where title='";
	char send_data[563];

	strcat_s(query, 255, title);
	strcat_s(query, 255, "'\0");

	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0)) {
		//AfxMessageBox(_T("DB연결오류"));
		printf("DB연결 오류\n");
	}

	if (mysql_query(&mysql, query))
	{ // 쿼리 요청
		printf("쿼리요청 실패\n");
		return;
	}

	if ((m_res = mysql_store_result(&mysql)) == NULL)
	{ // 결과를 m_Res에 저장
		printf("쿼리저장 실패\n");
		return;
	}

	while ((row = mysql_fetch_row(m_res)) != NULL)
	{
		// 출력창에 디버깅 용으로 
		printf("mysql에 받은 값입니다 : %s %s %s\n", row[0], row[1], row[2]);
		strcpy_s(send_data, 563, row[0]);
		strcat_s(send_data, 563, "/");
		strcat_s(send_data, 563, row[1]);
		strcat_s(send_data, 563, "/");
		strcat_s(send_data, 563, row[2]);
		strcat_s(send_data, 563, "\0");

		send(s, send_data, strlen(send_data) + 1, 0);		//+1은 null문자가 들어가게 하기 위해 삽입
	}
}

int MySQL_mailsend(char* toid, char* fromid, char* title, char* content){
	char query[255] = "insert into mail values (null, '";

	strcat_s(query, 255, fromid);
	strcat_s(query, 255, "', '");
	strcat_s(query, 255, toid);
	strcat_s(query, 255, "', '");
	strcat_s(query, 255, title);
	strcat_s(query, 255, "', '");
	strcat_s(query, 255, content);
	strcat_s(query, 255, "')\0");

	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0)) {
		//AfxMessageBox(_T("DB연결오류"));
		printf("DB연결 오류\n");
		return 0;
	}

	if (mysql_query(&mysql, query))
	{ // 쿼리 요청
		printf("쿼리요청 실패\n");
		return 0;
	}

	return 1;
}

int MySQL_maildel(char* toid, char* title){
	char query[255] = "delete from mail where toid='";

	strcat_s(query, 255, toid);
	strcat_s(query, 255, "' and title='");
	strcat_s(query, 255, title);
	strcat_s(query, 255, "'\0");

	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0)) {
		//AfxMessageBox(_T("DB연결오류"));
		printf("DB연결 오류\n");
		return 0;
	}

	if (mysql_query(&mysql, query))
	{ // 쿼리 요청
		printf("쿼리요청 실패\n");
		return 0;
	}

	return 1;
}

int MySQL_join(char* id, char* pw)
{
	char query[255] = "insert into member values ('";

	//query = "select * from member where id='";
	strcat_s(query, 255, id);
	strcat_s(query, 255, "', '");
	strcat_s(query, 255, pw);
	strcat_s(query, 255, "')\0");

	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0)) {
		//AfxMessageBox(_T("DB연결오류"));
		printf("DB연결 오류\n");
	}

	if (mysql_query(&mysql, query))
	{ // 쿼리 요청
		printf("쿼리요청 실패\n");
		return 0;
	}

	return 1;
}