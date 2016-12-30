#include "mysql.h"
#pragma comment(lib,"libmysql.lib")
#define DB_ADDRESS "localhost"
#define DB_ID "root"
#define DB_PASS "1234"
#define DB_NAME "maildb"
extern MYSQL_ROW row;		// mysql 의 행을 맡는다.

extern MYSQL_RES *m_res;	// mysql의 결과를 받아온다

extern MYSQL mysql;		// mysql의 전체적인 연동을 담당한다.

int MySQL_member(char* id, char* pw);										// 로그인 기능 0
void MySQL_mailbox(char* id, void* p);										// 메일함 조회 기능 1
void MySQL_mailview(char* toid, char* title, void* p);						// 선택 메일 상세 조회 기능 2
int MySQL_mailsend(char* toid, char* fromid, char* title, char* content);	// 메일 쓰기 기능 3
int MySQL_maildel(char* toid, char* title);									// 선택 메일 삭제 기능 4
int MySQL_join(char* id, char* pw);											// 회원 가입 기능 5