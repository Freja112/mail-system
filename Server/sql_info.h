#include "mysql.h"
#pragma comment(lib,"libmysql.lib")
#define DB_ADDRESS "localhost"
#define DB_ID "root"
#define DB_PASS "1234"
#define DB_NAME "maildb"
extern MYSQL_ROW row;		// mysql �� ���� �ô´�.

extern MYSQL_RES *m_res;	// mysql�� ����� �޾ƿ´�

extern MYSQL mysql;		// mysql�� ��ü���� ������ ����Ѵ�.

int MySQL_member(char* id, char* pw);										// �α��� ��� 0
void MySQL_mailbox(char* id, void* p);										// ������ ��ȸ ��� 1
void MySQL_mailview(char* toid, char* title, void* p);						// ���� ���� �� ��ȸ ��� 2
int MySQL_mailsend(char* toid, char* fromid, char* title, char* content);	// ���� ���� ��� 3
int MySQL_maildel(char* toid, char* title);									// ���� ���� ���� ��� 4
int MySQL_join(char* id, char* pw);											// ȸ�� ���� ��� 5