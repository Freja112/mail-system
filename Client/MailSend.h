#pragma once


// MailSend ��ȭ �����Դϴ�.

class MailSend : public CDialogEx
{
	DECLARE_DYNAMIC(MailSend)

public:
	MailSend(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~MailSend();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SEND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonQuit();
	CString m_sToID;
	CString m_sTitle;
	CString m_sContent;
	afx_msg void OnBnClickedButtonSend();
	char* LoginID;
};
