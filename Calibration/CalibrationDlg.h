
// CalibrationDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CCalibrationDlg ��ȭ ����
class CCalibrationDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CCalibrationDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALIBRATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListBox cList;
	CEdit cEdit;
//	CEdit cResult;
	afx_msg void OnLbnDblclkList2();
	CListBox cList_fail;
	CProgressCtrl m_progress;
};
