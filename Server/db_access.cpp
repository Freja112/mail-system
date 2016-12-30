#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
// windows.h ���Ͽ��� ���� ������� ���� ��Ҹ� �����Ͽ��� ���ܽ�Ų��.
// ������ �ӵ��� �������� winsock2.h���� �浹�� �Ͼ�� �ʴ´�.
#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <string.h>
#include "RevStruct.h"
#include "sql_info.h"
using namespace std;
#pragma comment ( lib, "ws2_32.lib" )
#pragma pack( 1 ) // ����ü���� 1byte ������ �޸𸮸� Align�϶�� ���þ�

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
		//AfxMessageBox(_T("DB�������"));
		printf("DB���� ����\n");
	}

	if (mysql_query(&mysql, query))
	{ // ���� ��û
		printf("������û ����\n");
		return 0;
	}

	m_res = mysql_store_result(&mysql);
	if (mysql_num_rows(m_res)>0){
		printf("��û�� �α��� ������ ��ġ�ϴ� ������ ����\n");
	}
	else
	{ // ����� m_Res�� ����
		printf("��û�� �α��� ���� ����ġ\n");
		return 0;
	}

	while ((row = mysql_fetch_row(m_res)) != NULL)
	{
		// ���â�� ����� ������ 
		printf("mysql�� ���� ���Դϴ� : %s %s\n", row[0], row[1]);
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
		//AfxMessageBox(_T("DB�������"));
		printf("DB���� ����\n");
	}

	if (mysql_query(&mysql, query))
	{ // ���� ��û
		printf("������û ����\n");
		return;
	}

	m_res = mysql_store_result(&mysql);
	if (mysql_num_rows(m_res)>0){
		printf("���� ���� ��ȸ ��� ����\n");
	}
	else
	{ // ����� m_Res�� ����
		printf("���� ������ �������� ����\n");
		send(s, "0\0", 2, 0);
		return;
	}

	int row_count = (int) mysql_num_rows(m_res);
	_itoa(row_count, send_data, 10);
	//printf("%s\n", send_data);
	send(s, send_data, strlen(send_data) + 1, 0);
	

	while ((row = mysql_fetch_row(m_res)) != NULL)
	{
		// ���â�� ����� ������ 
		printf("mysql�� ���� ���Դϴ� : %s / %s\n", row[0], row[1]);
		strcpy_s(send_data, 70, row[0]);
		strcat_s(send_data, 70, "/");
		strcat_s(send_data, 70, row[1]);
		strcat_s(send_data, 70, "\0");
		//printf("%d : %s\n", strlen(send_data)+1, send_data);

		send(s, send_data, strlen(send_data) + 1, 0);		//+1�� null���ڰ� ���� �ϱ� ���� ����
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
		//AfxMessageBox(_T("DB�������"));
		printf("DB���� ����\n");
	}

	if (mysql_query(&mysql, query))
	{ // ���� ��û
		printf("������û ����\n");
		return;
	}

	if ((m_res = mysql_store_result(&mysql)) == NULL)
	{ // ����� m_Res�� ����
		printf("�������� ����\n");
		return;
	}

	while ((row = mysql_fetch_row(m_res)) != NULL)
	{
		// ���â�� ����� ������ 
		printf("mysql�� ���� ���Դϴ� : %s %s %s\n", row[0], row[1], row[2]);
		strcpy_s(send_data, 563, row[0]);
		strcat_s(send_data, 563, "/");
		strcat_s(send_data, 563, row[1]);
		strcat_s(send_data, 563, "/");
		strcat_s(send_data, 563, row[2]);
		strcat_s(send_data, 563, "\0");

		send(s, send_data, strlen(send_data) + 1, 0);		//+1�� null���ڰ� ���� �ϱ� ���� ����
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
		//AfxMessageBox(_T("DB�������"));
		printf("DB���� ����\n");
		return 0;
	}

	if (mysql_query(&mysql, query))
	{ // ���� ��û
		printf("������û ����\n");
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
		//AfxMessageBox(_T("DB�������"));
		printf("DB���� ����\n");
		return 0;
	}

	if (mysql_query(&mysql, query))
	{ // ���� ��û
		printf("������û ����\n");
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
		//AfxMessageBox(_T("DB�������"));
		printf("DB���� ����\n");
	}

	if (mysql_query(&mysql, query))
	{ // ���� ��û
		printf("������û ����\n");
		return 0;
	}

	return 1;
}