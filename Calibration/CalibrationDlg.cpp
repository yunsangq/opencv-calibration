
// CalibrationDlg.cpp : ���� ����
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

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CCalibrationDlg ��ȭ ����



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


// CCalibrationDlg �޽��� ó����

BOOL CCalibrationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCalibrationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CCalibrationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString load_path;

void CCalibrationDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
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
					MessageBox(_T("�̹����� ���� ���߽��ϴ�."));
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

		string result_msg = to_string(success) + "���� ü������ ���� ����, " + to_string(error) + "���� ü������ ���� ����.";
		CA2T wt(result_msg.c_str());
		MessageBox(wt);		
	}
}

void CCalibrationDlg::OnLbnDblclkList2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
