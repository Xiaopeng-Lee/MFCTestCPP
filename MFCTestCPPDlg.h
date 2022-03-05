
// MFCTestCPPDlg.h: 头文件
//

#pragma once


// CMFCTestCPPDlg 对话框
class CMFCTestCPPDlg : public CDialogEx
{
// 构造
public:
	CMFCTestCPPDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTESTCPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CStatic m_Picture;
	afx_msg void OnStnClickedTestStatic();
	afx_msg void OnBnClickedButton1();
};
