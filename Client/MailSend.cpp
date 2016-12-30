// MailSend.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MailClient.h"
#include "MailSend.h"
#include "afxdialogex.h"


// MailSend 대화 상자입니다.

IMPLEMENT_DYNAMIC(MailSend, CDialogEx)

MailSend::MailSend(CWnd* pParent /*=NULL*/)
	: CDialogEx(MailSend::IDD, pParent)
	, m_sToID(_T(""))
	, m_sTitle(_T(""))
	, m_sContent(_T(""))
{

}

MailSend::~MailSend()
{
}

void MailSend::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TO, m_sToID);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_sTitle);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_sContent);
}


BEGIN_MESSAGE_MAP(MailSend, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &MailSend::OnBnClickedButtonQuit)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &MailSend::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// MailSend 메시지 처리기입니다.


void MailSend::OnBnClickedButtonQuit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}


void MailSend::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);


	char str[576] = "3/";

	char* ch;
	int nLength = m_sToID.GetLength();
	ch = new char[nLength + 1];
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)m_sToID, -1, ch, nLength + 1, NULL, NULL);
	strcat_s(str, 576, ch);
	strcat_s(str, 576, "/");
	delete[] ch;


	strcat_s(str, 576, LoginID);
	strcat_s(str, 576, "/");

	nLength = m_sTitle.GetLength();
	ch = new char[nLength + 1];
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)m_sTitle, -1, ch, nLength + 1, NULL, NULL);
	strcat_s(str, 576, ch);
	strcat_s(str, 576, "/");
	delete[] ch;
	
	nLength = m_sContent.GetLength();
	ch = new char[nLength + 1];
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)m_sContent, -1, ch, nLength + 1, NULL, NULL);
	strcat_s(str, 576, ch);
	strcat_s(str, 576, "\0");
	delete[] ch;

	char *ip = "127.0.0.1";
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
	send(s, (char*)&pkt, size, 0);

	recv(s, pkt.p, sizeof(pkt.p), 0);
	
	closesocket(s);
	WSACleanup();



	if (!strcmp(pkt.p, "1")){
		AfxMessageBox(_T("메일 성공적으로 전송하였습니다."));
		OnOK();
	}
	else{
		AfxMessageBox(_T("메일 전송 실패"));
	}
}
