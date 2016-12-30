// Login.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MailClient.h"
#include "Login.h"
#include "afxdialogex.h"


// Login ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Login, CDialogEx)

Login::Login(CWnd* pParent /*=NULL*/)
	: CDialogEx(Login::IDD, pParent)
	, m_sID(_T(""))
	, m_sPW(_T(""))
{

}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IDEDIT, m_sID);
	DDX_Text(pDX, IDC_PWEDIT, m_sPW);
}


BEGIN_MESSAGE_MAP(Login, CDialogEx)
	ON_BN_CLICKED(IDC_LOGIN, &Login::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &Login::OnBnClickedButtonQuit)
	ON_BN_CLICKED(IDC_BUTTON_JOIN, &Login::OnBnClickedButtonJoin)
END_MESSAGE_MAP()


// Login �޽��� ó�����Դϴ�.


void Login::OnBnClickedLogin()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	char *ip = "127.0.0.1";
	char str[34] = "0/";
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
		AfxMessageBox(_T("�α��� ����"));
		OnOK();
	}
	else{
		AfxMessageBox(_T("�α��� ����"));
	}
}


void Login::OnBnClickedButtonQuit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	exit(1);
}


void Login::OnBnClickedButtonJoin()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	MailJoin join_dlg;
	join_dlg.DoModal();
}
