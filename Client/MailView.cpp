// MailView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MailClient.h"
#include "MailView.h"
#include "afxdialogex.h"


// MailView 대화 상자입니다.

IMPLEMENT_DYNAMIC(MailView, CDialogEx)

MailView::MailView(CWnd* pParent /*=NULL*/)
	: CDialogEx(MailView::IDD, pParent)
	, m_sFrom(_T(""))
	, m_sTitle(_T(""))
	, m_sContent(_T(""))
{
	
}

MailView::~MailView()
{
}

void MailView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FROM, m_sFrom);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_sTitle);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_sContent);
}


BEGIN_MESSAGE_MAP(MailView, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &MailView::OnBnClickedButtonQuit)
END_MESSAGE_MAP()


// MailView 메시지 처리기입니다.


void MailView::OnBnClickedButtonQuit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}
