
// Calibration.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCalibrationApp:
// �� Ŭ������ ������ ���ؼ��� Calibration.cpp�� �����Ͻʽÿ�.
//

class CCalibrationApp : public CWinApp
{
public:
	CCalibrationApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCalibrationApp theApp;