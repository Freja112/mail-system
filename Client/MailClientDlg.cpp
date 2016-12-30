// MailClientDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MailClient.h"
#include "MailClientDlg.h"
#include "afxdialogex.h"
#include "Login.h"
#include "MailView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMailClientDlg ��ȭ ����



CMailClientDlg::CMailClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMailClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMailClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MENU, m_lMenu);
	DDX_Control(pDX, IDC_STATIC_ID, m_cStaticID);
	DDX_Control(pDX, IDC_SUBMENU, m_ListC);
}

BEGIN_MESSAGE_MAP(CMailClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_MENU, &CMailClientDlg::OnLbnSelchangeMenu)
	ON_BN_CLICKED(IDC_EXIT, &CMailClientDlg::OnBnClickedExit)
	ON_NOTIFY(NM_CLICK, IDC_SUBMENU, &CMailClientDlg::OnNMClickSubmenu)
	ON_NOTIFY(NM_DBLCLK, IDC_SUBMENU, &CMailClientDlg::OnNMDblclkSubmenu)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CMailClientDlg::OnBnClickedButtonDel)
END_MESSAGE_MAP()


// CMailClientDlg �޽��� ó����

BOOL CMailClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	if (dlg.DoModal() == IDOK)
		AfxMessageBox(_T("�ȳ��ϼ���?"));
	m_lMenu.InsertString(0, _T("����������"));
	m_lMenu.InsertString(1, _T("���� ����"));
	
	LoginID = dlg.m_sID;
	m_cStaticID.SetWindowTextW(LoginID);


	
	char *szText[2] = { "Title", "From" };
	int nWid[2] = { 65, 208 };
	LV_COLUMN lCol;

	lCol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;  //����ü�� ����� Ȯ���� �÷��׸� ����
	lCol.fmt = LVCFMT_LEFT;  //Į���� ������ �������ķ� ����(_CENTER, _LEFT, _RIGHT�� ����)

	for (int i = 0; i < 2; i++){
		wchar_t wtext[20];
		mbstowcs(wtext, szText[i], strlen(szText[i]) + 1);
		lCol.pszText = wtext;  //Į���� ������ ����
		lCol.iSubItem = i;  //����������� �ε����� ����
		lCol.cx = nWid[i];  //Į���� ���̸� ����
		m_ListC.InsertColumn(i, &lCol);  //LVCOLUMN����ü�� ������� ���� ���� ����Ʈ ��Ʈ�ѿ� Į���� ����
	}
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMailClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMailClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMailClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMailClientDlg::OnLbnSelchangeMenu()		// ���� ���� �޴��� ������ ���� �̺�Ʈ
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = m_lMenu.GetCurSel();
	
	if (index == 0){		// ù��° �޴��� ���� �������� ������ ��
		char str[13] = "1/";
		char* ch;
		int nLength = LoginID.GetLength();
		ch = new char[nLength + 1];
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)LoginID, -1, ch, nLength + 1, NULL, NULL);
		strcat_s(str, 13, ch);
		strcat_s(str, 13, "\0");
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
		int count = atoi(pkt.p);
		int nIndex = 0;
		m_ListC.DeleteAllItems();
		for (int i = 0; i < count; i++){
			recv(s, pkt.p, sizeof(pkt.p), 0);


			char* ptr;
			char* temp;
			ptr = strtok_s(pkt.p, "/", &temp);

			char fromID[10];
			char title[50];
			strcpy_s(fromID, strlen(ptr) + 1, ptr);
			ptr = strtok_s(NULL, "/", &temp);
			strcpy_s(title, strlen(ptr) + 1, ptr);




			char szText[50] = "";  //���ڿ��� ������ ���� ����

			//int nIndex = 0;  //����� �ε����� ������ ��������

			LVITEM lItem;  //�� ����ü�� �̿��ؼ� ��Ͽ� ���� ������ �ۼ�

			lItem.mask = LVIF_TEXT;  //�� ����ü�� pszTextȮ��
			lItem.iItem = nIndex;  //����� ��ȣ�� ����

			lItem.iSubItem = 0;  //���� �׸��� ��ȣ�� ����-�ֻ����̹Ƿ� 0�� �ݴϴ�.
			//sprintf(szText, "%s", title);  //m_strName������ CSstrin���̶� szText������ �ٷ� ���� ������ ���� ����. ���� sprintf()�Լ��̿�
			wchar_t wtext[20];
			mbstowcs(wtext, title, strlen(title) + 1);
			lItem.pszText = wtext;  //��ϳ��� ����
			m_ListC.InsertItem(&lItem);   //�ֻ����߰�


			lItem.iSubItem = 1;  //�����׸��ȣ 1�� ����.
			//sprintf(szText, "%s", fromID);
			mbstowcs(wtext, fromID, strlen(fromID) + 1);
			lItem.pszText = wtext;  //��ϳ��� ����
			m_ListC.SetItem(&lItem);  //��������߰��� SetItem�Լ��� ���

			//m_strName = "";  //���ο����߰������� ĭ ����.
			//m_strMail = "";

			nIndex++;   //���ο����߰��ϱ����� 1����

			Sleep(500);
		}

		closesocket(s);
		WSACleanup();
	}
	else if (index == 1){
		char* ch;
		int nLength = LoginID.GetLength();
		ch = new char[nLength + 1];
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)LoginID, -1, ch, nLength + 1, NULL, NULL);

		MailSend send_dlg;
		send_dlg.LoginID = ch;
		send_dlg.DoModal();
	}
}


void CMailClientDlg::OnBnClickedExit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//closesocket(dlg.s);
	//WSACleanup();
	OnOK();
}


void CMailClientDlg::OnNMClickSubmenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	index = pNMItemActivate->iItem;

	*pResult = 0;
}


void CMailClientDlg::OnNMDblclkSubmenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if (index >= 0 && index < m_ListC.GetItemCount()) // ǥ�õ� �����۵��߿� Ŭ���� �Ʒ� �ڵ� ���� 
	{
		// do somthing
		CString data1 = m_ListC.GetItemText(index, 0);
		MailView dlg;
		char* ch;
		int nLength = data1.GetLength();
		ch = new char[nLength + 1];
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)data1, -1, ch, nLength + 1, NULL, NULL);
		strcat_s(dlg.title, 50, ch);
		delete[] ch;
		nLength = LoginID.GetLength();
		ch = new char[nLength + 1];
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)LoginID, -1, ch, nLength + 1, NULL, NULL);
		strcat_s(dlg.LoginID, 10, ch);
		delete[] ch;

		char *ip = "127.0.0.1";
		char str[64] = "2/";
		strcat_s(str, 64, dlg.LoginID);
		strcat_s(str, 64, "/");
		strcat_s(str, 64, dlg.title);
		strcat_s(str, 64, "\0");

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

		char* ptr;
		char* temp;
		ptr = strtok_s(pkt.p, "/", &temp);
		dlg.m_sFrom = (CString)ptr;
		ptr = strtok_s(NULL, "/", &temp);
		dlg.m_sTitle = (CString)ptr;
		ptr = strtok_s(NULL, "/", &temp);
		dlg.m_sContent = (CString)ptr;
		
		dlg.DoModal();
	}
	*pResult = 0;
}


void CMailClientDlg::OnBnClickedButtonDel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (index >= 0 && index < m_ListC.GetItemCount()) // ǥ�õ� �����۵��߿� Ŭ���� �Ʒ� �ڵ� ���� 
	{
		CString data1 = m_ListC.GetItemText(index, 0);

		char str[64] = "4/";

		char* ch;
		int nLength = LoginID.GetLength();
		ch = new char[nLength + 1];
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)LoginID, -1, ch, nLength + 1, NULL, NULL);
		strcat_s(str, 10, ch);
		strcat_s(str, 64, "/");
		delete[] ch;

		nLength = data1.GetLength();
		ch = new char[nLength + 1];
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)data1, -1, ch, nLength + 1, NULL, NULL);
		strcat_s(str, 64, ch);
		strcat_s(str, 64, "\0");
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
		//AfxMessageBox((CString)pkt.p);

		closesocket(s);
		WSACleanup();
		


		if (!strcmp(pkt.p, "1")){
			AfxMessageBox(_T("���� ���������� �����Ͽ����ϴ�."));


			char str[13] = "1/";
			char* ch;
			int nLength = LoginID.GetLength();
			ch = new char[nLength + 1];
			WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)LoginID, -1, ch, nLength + 1, NULL, NULL);
			strcat_s(str, 13, ch);
			strcat_s(str, 13, "\0");
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
			int count = atoi(pkt.p);
			int nIndex = 0;
			m_ListC.DeleteAllItems();
			for (int i = 0; i < count; i++){
				recv(s, pkt.p, sizeof(pkt.p), 0);


				char* ptr;
				char* temp;
				ptr = strtok_s(pkt.p, "/", &temp);

				char fromID[10];
				char title[50];
				strcpy_s(fromID, strlen(ptr) + 1, ptr);
				ptr = strtok_s(NULL, "/", &temp);
				strcpy_s(title, strlen(ptr) + 1, ptr);




				char szText[50] = "";  //���ڿ��� ������ ���� ����

				//int nIndex = 0;  //����� �ε����� ������ ��������

				LVITEM lItem;  //�� ����ü�� �̿��ؼ� ��Ͽ� ���� ������ �ۼ�

				lItem.mask = LVIF_TEXT;  //�� ����ü�� pszTextȮ��
				lItem.iItem = nIndex;  //����� ��ȣ�� ����

				lItem.iSubItem = 0;  //���� �׸��� ��ȣ�� ����-�ֻ����̹Ƿ� 0�� �ݴϴ�.
				//sprintf(szText, "%s", title);  //m_strName������ CSstrin���̶� szText������ �ٷ� ���� ������ ���� ����. ���� sprintf()�Լ��̿�
				wchar_t wtext[20];
				mbstowcs(wtext, title, strlen(title) + 1);
				lItem.pszText = wtext;  //��ϳ��� ����
				m_ListC.InsertItem(&lItem);   //�ֻ����߰�


				lItem.iSubItem = 1;  //�����׸��ȣ 1�� ����.
				//sprintf(szText, "%s", fromID);
				mbstowcs(wtext, fromID, strlen(fromID) + 1);
				lItem.pszText = wtext;  //��ϳ��� ����
				m_ListC.SetItem(&lItem);  //��������߰��� SetItem�Լ��� ���

				//m_strName = "";  //���ο����߰������� ĭ ����.
				//m_strMail = "";

				nIndex++;   //���ο����߰��ϱ����� 1����

				Sleep(500);
			}

			closesocket(s);
			WSACleanup();
		}
		else{
			AfxMessageBox(_T("���� ���� ����"));
		}

	}
}
