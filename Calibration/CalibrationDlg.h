
// CalibrationDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CCalibrationDlg 대화 상자
class CCalibrationDlg : public CDialogEx
{
// 생성입니다.
public:
	CCalibrationDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALIBRATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
