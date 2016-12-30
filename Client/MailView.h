#pragma once


// MailView 대화 상자입니다.

class MailView : public CDialogEx
{
	DECLARE_DYNAMIC(MailView)

public:
	MailView(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~MailView();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_VIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	char title[50];
	char LoginID[10];
	afx_msg void OnBnClickedButtonQuit();
	CString m_sFrom;
	CString m_sTitle;
	CString m_sContent;
};
