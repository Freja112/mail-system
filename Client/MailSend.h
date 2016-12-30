#pragma once


// MailSend 대화 상자입니다.

class MailSend : public CDialogEx
{
	DECLARE_DYNAMIC(MailSend)

public:
	MailSend(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~MailSend();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SEND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonQuit();
	CString m_sToID;
	CString m_sTitle;
	CString m_sContent;
	afx_msg void OnBnClickedButtonSend();
	char* LoginID;
};
