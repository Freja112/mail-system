#pragma once


// MailJoin ��ȭ �����Դϴ�.

class MailJoin : public CDialogEx
{
	DECLARE_DYNAMIC(MailJoin)

public:
	MailJoin(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~MailJoin();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_JOIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonQuit();
	afx_msg void OnBnClickedButtonJoin();
	CString m_sID;
	CString m_sPW;
};
