// MailView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MailClient.h"
#include "MailView.h"
#include "afxdialogex.h"


// MailView ��ȭ �����Դϴ�.

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


// MailView �޽��� ó�����Դϴ�.


void MailView::OnBnClickedButtonQuit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}
