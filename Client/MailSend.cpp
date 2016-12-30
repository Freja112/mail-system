// MailSend.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MailClient.h"
#include "MailSend.h"
#include "afxdialogex.h"


// MailSend ��ȭ �����Դϴ�.

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


// MailSend �޽��� ó�����Դϴ�.


void MailSend::OnBnClickedButtonQuit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}


void MailSend::OnBnClickedButtonSend()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		AfxMessageBox(_T("���� ���������� �����Ͽ����ϴ�."));
		OnOK();
	}
	else{
		AfxMessageBox(_T("���� ���� ����"));
	}
}
