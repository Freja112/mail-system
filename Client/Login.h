#pragma once
#include "MailJoin.h"

// Login ��ȭ �����Դϴ�.

class Login : public CDialogEx
{
	DECLARE_DYNAMIC(Login)

public:
	Login(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Login();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogin();
	CString m_sID;
	CString m_sPW;
	afx_msg void OnBnClickedButtonQuit();
	afx_msg void OnBnClickedButtonJoin();
};
