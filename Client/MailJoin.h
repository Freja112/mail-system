#pragma once


// MailJoin 대화 상자입니다.

class MailJoin : public CDialogEx
{
	DECLARE_DYNAMIC(MailJoin)

public:
	MailJoin(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~MailJoin();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_JOIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonQuit();
	afx_msg void OnBnClickedButtonJoin();
	CString m_sID;
	CString m_sPW;
};
