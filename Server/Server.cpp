// Server.cpp
// ������ ���� ���α׷��Դϴ�.
// ���� Win32 ���α׷����� �ۼ��� �� Thread�� �̿��� ������ �� �κ��Դϴ�.
#define WIN32_LEAN_AND_MEAN
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



void Check(REV_STRUCT *st, void* p) {
	SOCKET s = (SOCKET)p;
	char* ptr;
	char* temp;
	ptr = strtok_s(st->p, "/", &temp);

	if (ptr[0] == '0'){		// �α��� ��û 0/id/pw
		char ID[10];
		char PW[20];

		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(ID, strlen(ptr)+1, ptr);
		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(PW, strlen(ptr)+1, ptr);

		if (MySQL_member(ID, PW)){
			send(s, "1\0", 2, 0);	// �α��� ����
		}
		else{
			send(s, "0\0", 2, 0);	// �α��� ����
		}
	}
	else if (ptr[0] == '1'){	// ������ ��ȸ ��û 1/loginid
		char ID[10];

		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(ID, strlen(ptr) + 1, ptr);

		MySQL_mailbox(ID, (void*)s);
	}
	else if (ptr[0] == '2'){	// ������ ���� �� ��ȸ ��û 2/������id(loginid)/��������
		char ID[10];
		char TITLE[50];

		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(ID, strlen(ptr) + 1, ptr);
		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(TITLE, strlen(ptr) + 1, ptr);

		MySQL_mailview(ID, TITLE, (void*)s);
	}
	else if (ptr[0] == '3'){	// ���� ���� ��û 3/fromid/toid/title/content
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
			send(s, "1\0", 2, 0);	// ���� ���� ����
			printf("���� ���� ��û ���� ����\n");
		}
		else{
			send(s, "0\0", 2, 0);	// ���� ���� ����
			printf("���� ���� ��û ���� ����\n");
		}
	}
	else if (ptr[0] == '4'){	// ���� ���� ��û 4/������id(loginid)/��������
		char ID[10];
		char TITLE[50];

		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(ID, strlen(ptr) + 1, ptr);
		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(TITLE, strlen(ptr) + 1, ptr);

		if (MySQL_maildel(ID, TITLE)){
			send(s, "1\0", 2, 0);	// ���� ���� ����
			printf("���� ���� ��û ���� ����\n");
		}
		else{
			send(s, "0\0", 2, 0);	// ���� ���� ����
			printf("���� ���� ��û ���� ����\n");
		}
	}
	else if (ptr[0] == '5'){	// ȸ�� ���� ��û 5/id/pw
		printf("Ŭ���̾�Ʈ�κ��� ȸ������ ��û\n");
		char ID[10];
		char PW[20];

		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(ID, strlen(ptr) + 1, ptr);
		ptr = strtok_s(NULL, "/", &temp);
		strcpy_s(PW, strlen(ptr) + 1, ptr);

		if (MySQL_join(ID, PW)){
			send(s, "1\0", 2, 0);	// ȸ������ ����
			printf("ȸ������ ����\n");
		}
		else{
			send(s, "0\0", 2, 0);	// ȸ������ ����
			printf("ȸ������ ����\n");
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
			cout << "Error �߻� : " << WSAGetLastError() << endl;
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
		cout << "winsock �ʱ�ȭ ���� : " << WSAGetLastError() << endl;
		return;
	} // if
	//----------------------------------------------------------
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == SOCKET_ERROR) {
		cout << "������ �������� �ʾҽ��ϴ�." << endl;
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
		cout << "���ӵ� Client : " << inet_ntoa(addr.sin_addr) << endl;
		CloseHandle(CreateThread(0, 0, RevPacket, (void*)c_s, 0, 0));
	} // while( 1 )
	closesocket(s);
	//----------------------------------------------------------
	WSACleanup();
}