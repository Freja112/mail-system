// MailClientDlg.cpp : 구현 파일
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


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMailClientDlg 대화 상자



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


// CMailClientDlg 메시지 처리기

BOOL CMailClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	if (dlg.DoModal() == IDOK)
		AfxMessageBox(_T("안녕하세요?"));
	m_lMenu.InsertString(0, _T("받은메일함"));
	m_lMenu.InsertString(1, _T("메일 쓰기"));
	
	LoginID = dlg.m_sID;
	m_cStaticID.SetWindowTextW(LoginID);


	
	char *szText[2] = { "Title", "From" };
	int nWid[2] = { 65, 208 };
	LV_COLUMN lCol;

	lCol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;  //구조체의 기능을 확장할 플래그를 지정
	lCol.fmt = LVCFMT_LEFT;  //칼럼의 정렬을 왼쪽정렬로 지정(_CENTER, _LEFT, _RIGHT중 선택)

	for (int i = 0; i < 2; i++){
		wchar_t wtext[20];
		mbstowcs(wtext, szText[i], strlen(szText[i]) + 1);
		lCol.pszText = wtext;  //칼럼의 제목을 지정
		lCol.iSubItem = i;  //서브아이템의 인덱스를 지정
		lCol.cx = nWid[i];  //칼럼의 넓이를 지정
		m_ListC.InsertColumn(i, &lCol);  //LVCOLUMN구조체로 만들어진 값을 토대로 리스트 컨트롤에 칼럼을 삽입
	}
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMailClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMailClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMailClientDlg::OnLbnSelchangeMenu()		// 좌측 메인 메뉴를 눌렀을 때의 이벤트
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_lMenu.GetCurSel();
	
	if (index == 0){		// 첫번째 메뉴인 받은 편지함을 눌렀을 때
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




			char szText[50] = "";  //문자열을 저장할 변수 선언

			//int nIndex = 0;  //목록의 인덱스를 저장할 변수선언

			LVITEM lItem;  //이 구조체를 이용해서 목록에 대한 정보를 작성

			lItem.mask = LVIF_TEXT;  //이 구조체의 pszText확장
			lItem.iItem = nIndex;  //목록의 번호를 지정

			lItem.iSubItem = 0;  //세부 항목의 번호를 지정-최상목록이므로 0을 줍니다.
			//sprintf(szText, "%s", title);  //m_strName변수가 CSstrin형이라 szText변수로 바로 값을 전송할 수가 없다. 따라서 sprintf()함수이용
			wchar_t wtext[20];
			mbstowcs(wtext, title, strlen(title) + 1);
			lItem.pszText = wtext;  //목록내용 지정
			m_ListC.InsertItem(&lItem);   //최상목록추가


			lItem.iSubItem = 1;  //세부항목번호 1로 지정.
			//sprintf(szText, "%s", fromID);
			mbstowcs(wtext, fromID, strlen(fromID) + 1);
			lItem.pszText = wtext;  //목록내용 지정
			m_ListC.SetItem(&lItem);  //하위목록추가는 SetItem함수를 사용

			//m_strName = "";  //새로운목록추가를위해 칸 비우기.
			//m_strMail = "";

			nIndex++;   //새로운목록추가하기위해 1증가

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//closesocket(dlg.s);
	//WSACleanup();
	OnOK();
}


void CMailClientDlg::OnNMClickSubmenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	index = pNMItemActivate->iItem;

	*pResult = 0;
}


void CMailClientDlg::OnNMDblclkSubmenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (index >= 0 && index < m_ListC.GetItemCount()) // 표시된 아이템들중에 클릭시 아래 코드 실행 
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (index >= 0 && index < m_ListC.GetItemCount()) // 표시된 아이템들중에 클릭시 아래 코드 실행 
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
			AfxMessageBox(_T("메일 성공적으로 삭제하였습니다."));


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




				char szText[50] = "";  //문자열을 저장할 변수 선언

				//int nIndex = 0;  //목록의 인덱스를 저장할 변수선언

				LVITEM lItem;  //이 구조체를 이용해서 목록에 대한 정보를 작성

				lItem.mask = LVIF_TEXT;  //이 구조체의 pszText확장
				lItem.iItem = nIndex;  //목록의 번호를 지정

				lItem.iSubItem = 0;  //세부 항목의 번호를 지정-최상목록이므로 0을 줍니다.
				//sprintf(szText, "%s", title);  //m_strName변수가 CSstrin형이라 szText변수로 바로 값을 전송할 수가 없다. 따라서 sprintf()함수이용
				wchar_t wtext[20];
				mbstowcs(wtext, title, strlen(title) + 1);
				lItem.pszText = wtext;  //목록내용 지정
				m_ListC.InsertItem(&lItem);   //최상목록추가


				lItem.iSubItem = 1;  //세부항목번호 1로 지정.
				//sprintf(szText, "%s", fromID);
				mbstowcs(wtext, fromID, strlen(fromID) + 1);
				lItem.pszText = wtext;  //목록내용 지정
				m_ListC.SetItem(&lItem);  //하위목록추가는 SetItem함수를 사용

				//m_strName = "";  //새로운목록추가를위해 칸 비우기.
				//m_strMail = "";

				nIndex++;   //새로운목록추가하기위해 1증가

				Sleep(500);
			}

			closesocket(s);
			WSACleanup();
		}
		else{
			AfxMessageBox(_T("메일 삭제 실패"));
		}

	}
}
