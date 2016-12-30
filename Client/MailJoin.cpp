// MailJoin.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MailClient.h"
#include "MailJoin.h"
#include "afxdialogex.h"


// MailJoin 대화 상자입니다.

IMPLEMENT_DYNAMIC(MailJoin, CDialogEx)

MailJoin::MailJoin(CWnd* pParent /*=NULL*/)
	: CDialogEx(MailJoin::IDD, pParent)
	, m_sID(_T(""))
	, m_sPW(_T(""))
{

}

MailJoin::~MailJoin()
{
}

void MailJoin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_sID);
	DDX_Text(pDX, IDC_EDIT_PW, m_sPW);
}


BEGIN_MESSAGE_MAP(MailJoin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &MailJoin::OnBnClickedButtonQuit)
	ON_BN_CLICKED(IDC_BUTTON_JOIN, &MailJoin::OnBnClickedButtonJoin)
END_MESSAGE_MAP()


// MailJoin 메시지 처리기입니다.


void MailJoin::OnBnClickedButtonQuit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}


void MailJoin::OnBnClickedButtonJoin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	char *ip = "127.0.0.1";
	char str[34] = "5/";
	char* ch;
	int nLength = m_sID.GetLength();
	ch = new char[nLength + 1];
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)m_sID, -1, ch, nLength + 1, NULL, NULL);
	strcat_s(str, 34, ch);
	strcat_s(str, 34, "/");
	delete[] ch;

	nLength = m_sPW.GetLength();
	ch = new char[nLength + 1];
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)m_sPW, -1, ch, nLength + 1, NULL, NULL);
	strcat_s(str, 34, ch);
	strcat_s(str, 34, "\0");
	delete[] ch;

	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		return;
	}
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == SOCKET_ERROR) {
		return;
	}
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8081);
	addr.sin_addr.s_addr = inet_addr(ip);
	if (connect(s, (SOCKADDR*)&addr, sizeof(addr)) == -1) {
		return;
	}
	REV_STRUCT pkt;
	pkt.size = strlen(str) + 5;
	int size = pkt.size;
	pkt.size = htonl(size);
	strcpy_s(pkt.p, size, str);
	int n = send(s, (char*)&pkt, size, 0);
	int n2 = recv(s, pkt.p, sizeof(pkt.p), 0);
	//AfxMessageBox((CString)pkt.p);
	closesocket(s);
	WSACleanup();

	if (!strcmp(pkt.p, "1")){
		AfxMessageBox(_T("회원가입 성공"));
		OnOK();
	}
	else{
		AfxMessageBox(_T("회원가입 실패"));
	}
}
