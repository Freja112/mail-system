#pragma once


// MailView ��ȭ �����Դϴ�.

class MailView : public CDialogEx
{
	DECLARE_DYNAMIC(MailView)

public:
	MailView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~MailView();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	char title[50];
	char LoginID[10];
	afx_msg void OnBnClickedButtonQuit();
	CString m_sFrom;
	CString m_sTitle;
	CString m_sContent;
};
