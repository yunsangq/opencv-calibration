
// CalibrationDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Calibration.h"
#include "CalibrationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include "opencv2\opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalibrationDlg 대화 상자



CCalibrationDlg::CCalibrationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CALIBRATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalibrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, cList);
	DDX_Control(pDX, IDC_EDIT1, cEdit);
	DDX_Control(pDX, IDC_LIST4, cList_fail);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}

BEGIN_MESSAGE_MAP(CCalibrationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCalibrationDlg::OnBnClickedOk)
	ON_LBN_DBLCLK(IDC_LIST2, &CCalibrationDlg::OnLbnDblclkList2)
END_MESSAGE_MAP()


// CCalibrationDlg 메시지 처리기

BOOL CCalibrationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCalibrationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCalibrationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCalibrationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString load_path;

void CCalibrationDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	TCHAR* pszFile = new TCHAR[32767];

	CFileDialog dlg(true, NULL, NULL, OFN_ALLOWMULTISELECT, _T("png Files(*.png)|*.png|"));
	ZeroMemory(pszFile, 32767 * sizeof(TCHAR));
	dlg.m_ofn.lpstrFile = pszFile;
	dlg.m_ofn.nMaxFile = 32767;
	dlg.m_ofn.nFileOffset = 0;

	m_progress.SetRange(0, 100);
	m_progress.SetPos(0);

	if (dlg.DoModal() == IDOK) {
		cList.ResetContent();
		cList_fail.ResetContent();
		cEdit.SetWindowTextW(_T(""));

		POSITION pos = dlg.GetStartPosition();
		int error = 0;
		int success = 0;

		CString tmp_folder = dlg.GetFolderPath() + "\\drawChessboard";
		load_path = tmp_folder;

		CFileFind find;
		bool test = find.FindFile(tmp_folder);
		if(test == FALSE)
			CreateDirectory(tmp_folder, NULL);

		CString filename;

		vector<vector<Point3f>> objectPoints;
		vector<vector<Point2f>> imagePoints;
		Mat cameraMatrix;
		Mat distCoeffs;
		int flag = 0;

		Size boardSize(7, 4);
		Size imageSize;

		m_progress.SetPos(40);

		while (pos) {
			CString filepath = dlg.GetNextPathName(pos);
			CT2CA pszConvertedAnsiString(filepath);
			string tmp(pszConvertedAnsiString);
			
			try {				
				filename = filepath.Right(filepath.GetLength() - filepath.ReverseFind('\\') - 1);
				CString tmp_path = tmp_folder + "\\" + filename;
				CT2CA pszConvertedAnsiString(tmp_path);
				string path(pszConvertedAnsiString);

				vector<cv::Point2f> imageCorners;
				vector<cv::Point3f> objectCorners;

				for (int i = 0; i < boardSize.height; i++) {
					for (int j = 0; j < boardSize.width; j++) {
						objectCorners.push_back(Point3f(i, j, 0.0f));
					}
				}
				
				Mat img = imread(tmp, 1);
				if (img.empty()) {
					MessageBox(_T("이미지를 열지 못했습니다."));
				}
				imageSize = img.size();
				Mat img_gray;
				cvtColor(img, img_gray, COLOR_BGR2GRAY);
				
				bool found = findChessboardCorners(img, boardSize, imageCorners);				
				cornerSubPix(img_gray, imageCorners, Size(5, 5), Size(-1, -1),
					TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 30, 0.1));
				
				drawChessboardCorners(img, boardSize, Mat(imageCorners), found);

				if (imageCorners.size() == boardSize.area()) {
					imagePoints.push_back(imageCorners);
					objectPoints.push_back(objectCorners);
					success++;
					imwrite(path, img);
					cList.AddString(filename);
				}
				else {
					cList_fail.AddString(filename);
					error++;
				}				
			}
			catch (cv::Exception e) {
				error++;
				cList_fail.AddString(filename);
				string ex = e.what();
				CA2T wt(ex.c_str());
				MessageBox(wt);
			}
		}
		delete[] pszFile;
		m_progress.SetPos(40);

		vector<Mat> rvecs, tvecs;
		double rms = calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs, flag | CV_CALIB_FIX_K4 | CV_CALIB_FIX_K5);
		
		m_progress.SetPos(90);

		CString result_para;
		CString temp_str;
		temp_str.Format(_T("rms = %f\r\n"), rms);
		result_para += temp_str;
		temp_str.Format(_T("fx = %f\r\n"), cameraMatrix.at<double>(0, 0));
		result_para += temp_str;
		temp_str.Format(_T("fy = %f\r\n"), cameraMatrix.at<double>(1, 1));
		result_para += temp_str;
		temp_str.Format(_T("cx = %f\r\n"), cameraMatrix.at<double>(0, 2));
		result_para += temp_str;
		temp_str.Format(_T("cy = %f\r\n"), cameraMatrix.at<double>(1, 2));
		result_para += temp_str;
		temp_str.Format(_T("k1 = %f\r\n"), distCoeffs.at<double>(0, 0));
		result_para += temp_str;
		temp_str.Format(_T("k2 = %f\r\n"), distCoeffs.at<double>(0, 1));
		result_para += temp_str;
		temp_str.Format(_T("p1 = %f\r\n"), distCoeffs.at<double>(0, 2));
		result_para += temp_str;
		temp_str.Format(_T("p2 = %f\r\n"), distCoeffs.at<double>(0, 3));
		result_para += temp_str;

		cEdit.SetWindowTextW(result_para);
		
		m_progress.SetPos(100);

		string result_msg = to_string(success) + "개의 체스보드 검출 성공, " + to_string(error) + "개의 체스보드 검출 실패.";
		CA2T wt(result_msg.c_str());
		MessageBox(wt);		
	}
}

void CCalibrationDlg::OnLbnDblclkList2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Mat img;
	int idx = cList.GetCurSel();
	CString name;
	cList.GetText(idx, name);
	
	CString tmp = load_path + "\\" + name;
	CT2CA pszConvertedAnsiString(tmp);
	string path(pszConvertedAnsiString);
	
	img = imread(path);

	namedWindow("name");
	imshow("name", img);
	char ch = waitKey(0);
	if(ch==27)
		destroyWindow("name");
}
