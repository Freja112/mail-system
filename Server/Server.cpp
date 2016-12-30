// Server.cpp
// 다음은 서버 프로그램입니다.
// 물론 Win32 프로그램으로 작성할 땐 Thread를 이용해 빠져야 할 부분입니다.
#define WIN32_LEAN_AND_MEAN
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



void Check(REV_STRUCT *st, void* p) {
	SOCKET s = (SOCKET)p;
	char* ptr;
	char* temp;
	ptr = strtok_s(st->p, "/", &temp);

	if (ptr[0] == '0'){		// 로그인 요청 0/id/pw
		char ID[10];
		char PW[20];

		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(ID, strlen(ptr)+1, ptr);
		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(PW, strlen(ptr)+1, ptr);

		if (MySQL_member(ID, PW)){
			send(s, "1\0", 2, 0);	// 로그인 성공
		}
		else{
			send(s, "0\0", 2, 0);	// 로그인 실패
		}
	}
	else if (ptr[0] == '1'){	// 메일함 조회 요청 1/loginid
		char ID[10];

		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(ID, strlen(ptr) + 1, ptr);

		MySQL_mailbox(ID, (void*)s);
	}
	else if (ptr[0] == '2'){	// 선택한 메일 상세 조회 요청 2/수신자id(loginid)/메일제목
		char ID[10];
		char TITLE[50];

		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(ID, strlen(ptr) + 1, ptr);
		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(TITLE, strlen(ptr) + 1, ptr);

		MySQL_mailview(ID, TITLE, (void*)s);
	}
	else if (ptr[0] == '3'){	// 메일 쓰기 요청 3/fromid/toid/title/content
		char ToID[10];
		char FromID[10];
		char TITLE[50];
		char CONTENT[500];

		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(ToID, strlen(ptr) + 1, ptr);
		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(FromID, strlen(ptr) + 1, ptr);
		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(TITLE, strlen(ptr) + 1, ptr);
		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(CONTENT, strlen(ptr) + 1, ptr);

		if (MySQL_mailsend(ToID, FromID, TITLE, CONTENT)){
			send(s, "1\0", 2, 0);	// 메일 쓰기 성공
			printf("메일 전송 요청 정상 수행\n");
		}
		else{
			send(s, "0\0", 2, 0);	// 메일 쓰기 실패
			printf("메일 전송 요청 응답 실패\n");
		}
	}
	else if (ptr[0] == '4'){	// 메일 삭제 요청 4/수신자id(loginid)/메일제목
		char ID[10];
		char TITLE[50];

		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(ID, strlen(ptr) + 1, ptr);
		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(TITLE, strlen(ptr) + 1, ptr);

		if (MySQL_maildel(ID, TITLE)){
			send(s, "1\0", 2, 0);	// 메일 삭제 성공
			printf("메일 삭제 요청 정상 수행\n");
		}
		else{
			send(s, "0\0", 2, 0);	// 메일 삭제 실패
			printf("메일 삭제 요청 응답 실패\n");
		}
	}
	else if (ptr[0] == '5'){	// 회원 가입 요청 5/id/pw
		printf("클라이언트로부터 회원가입 요청\n");
		char ID[10];
		char PW[20];

		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(ID, strlen(ptr) + 1, ptr);
		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(PW, strlen(ptr) + 1, ptr);

		if (MySQL_join(ID, PW)){
			send(s, "1\0", 2, 0);	// 회원가입 성공
			printf("회원가입 성공\n");
		}
		else{
			send(s, "0\0", 2, 0);	// 회원가입 실패
			printf("회원가입 실패\n");
		}
	}
}

DWORD WINAPI RevPacket(void* p) {
	SOCKET s = (SOCKET)p;
	REV_STRUCT pkt = { 0 };

	int current = 0;
	int n = recv(s, (char*)&pkt, 4, 0);
	int total = ntohl(pkt.size);

	current += n;
	while (total > current) {
		n = recv(s, (char*)&pkt + current, total - current, 0);
		if (n > 0) {
			current += n;
			continue;
		}
		else if (n <= 0) {
			cout << "Error 발생 : " << WSAGetLastError() << endl;
			return -1;
		}
	} // while
	Check(&pkt, (void*)s);
	//send(s, (char*)&pkt, total, 0);
	return 0;
}

void main() {
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		cout << "winsock 초기화 실패 : " << WSAGetLastError() << endl;
		return;
	} // if
	//----------------------------------------------------------
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == SOCKET_ERROR) {
		cout << "소켓이 생성되지 않았습니다." << endl;
		return;
	}
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8081);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(s, (SOCKADDR*)&addr, sizeof(addr)) == -1) {
		cout << "Failed binding" << endl;
		return;
	}
	if (listen(s, 5) == -1) {
		cout << "Failed listening" << endl;
		return;
	}
	cout << "Waiting for connencting from Client..." << endl;
	while (1) {
		int size = sizeof(addr);
		SOCKET c_s = accept(s, (SOCKADDR*)&addr, &size);
		cout << "접속된 Client : " << inet_ntoa(addr.sin_addr) << endl;
		CloseHandle(CreateThread(0, 0, RevPacket, (void*)c_s, 0, 0));
	} // while( 1 )
	closesocket(s);
	//----------------------------------------------------------
	WSACleanup();
}