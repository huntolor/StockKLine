
// StockKLineDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "StockKLine.h"
#include "StockKLineDlg.h"
#include "afxdialogex.h"
#include "StockPrice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define NUM_DAYS_MAX		8000
struct daySummary history[NUM_DAYS_MAX];

// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
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


// CStockKLineDlg �_�C�A���O



CStockKLineDlg::CStockKLineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STOCKKLINE_DIALOG, pParent)
	, m_strStockCode(_T(""))
	, m_strDate0(_T(""))
	, m_strDate1(_T(""))
	, m_strDate2(_T(""))
	, m_strDate3(_T(""))
	, m_strDate4(_T(""))
	, m_strDate5(_T(""))
	, m_strDate6(_T(""))
	, m_strDate7(_T(""))
	, m_strDate8(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStockKLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRAPH, m_KLine);
	DDX_Text(pDX, IDC_EDIT1, m_strStockCode);
	DDV_MaxChars(pDX, m_strStockCode, 9);
	DDX_Text(pDX, IDC_STATIC_DATE0, m_strDate0);
	DDX_Text(pDX, IDC_STATIC_DATE1, m_strDate1);
	DDX_Text(pDX, IDC_STATIC_DATE2, m_strDate2);
	DDX_Text(pDX, IDC_STATIC_DATE3, m_strDate3);
	DDX_Text(pDX, IDC_STATIC_DATE4, m_strDate4);
	DDX_Text(pDX, IDC_STATIC_DATE5, m_strDate5);
	DDX_Text(pDX, IDC_STATIC_DATE6, m_strDate6);
	DDX_Text(pDX, IDC_STATIC_DATE7, m_strDate7);
	DDX_Text(pDX, IDC_STATIC_DATE8, m_strDate8);
}

BEGIN_MESSAGE_MAP(CStockKLineDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GETPRICE, &CStockKLineDlg::OnBnClickedGetprice)
	ON_EN_CHANGE(IDC_EDIT1, &CStockKLineDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_FINDPATTERN, &CStockKLineDlg::OnBnClickedFindpattern)
END_MESSAGE_MAP()


// CStockKLineDlg ���b�Z�[�W �n���h���[

BOOL CStockKLineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
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

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B
	m_strStockCode = _T("000877.sz");
	UpdateData(FALSE);

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

void CStockKLineDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CStockKLineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CStockKLineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStockKLineDlg::OnBnClickedGetprice()
{
	UpdateData(TRUE);

	CStockPrice stockPrice;
	CStringA strA(m_strStockCode);
	std::string strCode((LPCSTR)strA);
	stockPrice.DownloadSingleStockPrices(strCode);

	DrawKLine(strCode);
}

BOOL CStockKLineDlg::DrawKLine(std::string strCode)
{
	std::string strFileName = PRICEFILE_PATH;
	strFileName += strCode;
	strFileName += ".csv";
	FILE* fp = NULL;
	if (fopen_s(&fp, strFileName.c_str(), "r"))
		return FALSE;

	char cYear[16], cMonth[16], cDay[16], cOpen[16], cHigh[16], cLow[16], cClose[16], cVolume[16], cAdjClose[16];

	char temp[256];
	fgets(temp, 256, fp);
	int i;
	for (i = 0; i < NUM_DAYS_MAX; i++) {
		cYear[0] = cMonth[0] = cDay[0] = cOpen[0] = cHigh[0] = cLow[0] = cClose[0] = cVolume[0] = cAdjClose[0] = '\0';
		if (fscanf_s(fp, "%[^-]-%[^-]-%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", cYear, 16, cMonth, 16, cDay, 16, cOpen, 16, cHigh, 16, cLow, 16, cClose, 16, cVolume, 16, cAdjClose, 16) == EOF)
			break;
		history[i].date = strtol(cYear, NULL, 10) * 10000 + strtol(cMonth, NULL, 10) * 100 + strtol(cDay, NULL, 10);
		history[i].open = strtod(cOpen, NULL);
		history[i].high = strtod(cHigh, NULL);
		history[i].low = strtod(cLow, NULL);
		history[i].close = strtod(cClose, NULL);
		history[i].volume = strtol(cVolume, NULL, 10);
		history[i].adjClose = strtod(cAdjClose, NULL);
	}
	fclose(fp);

	
	UpdateScrollBar(i, i, NUM_LINE_DISPLAY);
	UpdateDateText(0, NUM_LINE_DISPLAY);
	

	m_KLine.SetDateRange(0, NUM_LINE_DISPLAY);
	m_KLine.AnalyzeData(history, i);
	m_KLine.RedrawWindow();
	return TRUE;
}

void CStockKLineDlg::UpdateDateText(int iLast, int nNum)
{
	m_strDate0.Format(_T("%d"), history[iLast].date);
	m_strDate1.Format(_T("%d"), history[iLast + nNum * 1 / 8].date);
	m_strDate2.Format(_T("%d"), history[iLast + nNum * 2 / 8].date);
	m_strDate3.Format(_T("%d"), history[iLast + nNum * 3 / 8].date);
	m_strDate4.Format(_T("%d"), history[iLast + nNum * 4 / 8].date);
	m_strDate5.Format(_T("%d"), history[iLast + nNum * 5 / 8].date);
	m_strDate6.Format(_T("%d"), history[iLast + nNum * 6 / 8].date);
	m_strDate7.Format(_T("%d"), history[iLast + nNum * 7 / 8].date);
	m_strDate8.Format(_T("%d"), history[iLast + nNum].date);
	UpdateData(FALSE);
}

void CStockKLineDlg::OnEnChangeEdit1()
{
	// TODO: ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A���̃R���g���[����
	// ���̒ʒm�𑗐M����ɂ́ACDialogEx::OnInitDialog() �֐����I�[�o�[���C�h���A
	// CRichEditCtrl().SetEventMask() ��
	// OR ��Ԃ� ENM_CHANGE �t���O���}�X�N�ɓ���ČĂяo���K�v������܂��B

	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����Ă��������B
}

void CStockKLineDlg::UpdateScrollBar(int nPos, int nMax, int nPage)
{
	SCROLLINFO	info;
	info.cbSize = sizeof(SCROLLINFO);
	info.fMask = SIF_PAGE | SIF_POS | SIF_RANGE;
	info.nMin = 0;
	info.nPos = nPos;

	// �����o�[
	info.nPage = nPage;
	info.nMax = nMax;
	if (!SetScrollInfo(SB_HORZ, &info, TRUE))
		SetScrollRange(SB_HORZ, 0, nPage, TRUE);
}

void CStockKLineDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SCROLLINFO	info;
	info.cbSize = sizeof(SCROLLINFO);
	info.fMask = SIF_PAGE | SIF_POS | SIF_RANGE;
	GetScrollInfo(SB_HORZ, &info);

	int nStep = max(32, info.nPage / 5);
	int nMax = info.nMax;
	int nNew = info.nPos;
	switch (nSBCode) {
	case SB_LINERIGHT:
		nNew += nStep;		break;
	case SB_PAGERIGHT:
		nNew += info.nPage;	break;
	case SB_LINELEFT:
		nNew -= nStep;		break;
	case SB_PAGELEFT:
		nNew -= info.nPage;	break;
	case SB_RIGHT:
		nNew = nMax;		break;
	case SB_LEFT:
		nNew = info.nMin;		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		nNew = (int)nPos;	break;
	default:
		return;
	}
	nNew = min(nMax - (int)info.nPage, max(info.nMin, nNew));

	int nPosOrg = info.nPos;
	if (nNew != nPosOrg) {
		SetScrollPos(SB_HORZ, nNew, TRUE);	// ScrollBar Position
		int iLastData = info.nMax - nNew - info.nPage;
		m_KLine.SetDateRange(iLastData, NUM_LINE_DISPLAY);	// ��ԉE�̈ʒu��0�Ƃ���
		m_KLine.RedrawWindow();
		UpdateDateText(iLastData, NUM_LINE_DISPLAY);
	}
}

void CStockKLineDlg::OnBnClickedFindpattern()
{
	SUMMARY data[4];
	data[0].open = 90;
	data[0].high = 96;
	data[0].low = 90;
	data[0].close = 96;
	
	data[1].open = 89;
	data[1].high = 91;
	data[1].low = 86;
	data[1].close = 89;

	data[2].open = 100;
	data[2].high = 100;
	data[2].low = 92;
	data[2].close = 92;

	data[3].close = 100;

	//data[0].open = 9.2;
	//data[0].low = 9.1;
	//data[0].close = data[0].high = 9.7;
	//data[1].open = 8.9;
	//data[1].high = 9.2;
	//data[1].low = 8.5;
	//data[1].close = 9.0;
	//data[2].open = data[2].high = 9.9;
	//data[2].low = data[2].close = 9.3;
	//data[3].close = 10.0;

	int nCount = m_KLine.FindCount(data, 3);
	//int nCount = m_KLine.FindCount(history + 15, 3);
	if (nCount <= 0)
	{
		AfxMessageBox(_T("Cannot find any similar pattern!"));
		return;
	}

	int nIndex = m_KLine.FindNext(data, 3);
	//int nIndex = m_KLine.FindNext(history + 15, 3);
	if (nIndex != -1)
	{
		//m_KLine.SetDateRange(nIndex, NUM_LINE_DISPLAY);	// ��ԉE�̈ʒu��0�Ƃ���
		m_KLine.SetDateRange(max(nIndex - (int)(NUM_LINE_DISPLAY / 2.0), 0), NUM_LINE_DISPLAY);	// ���������p�^�[����^�񒆂ɒu��
		m_KLine.SetMark(nIndex, 3);
		m_KLine.RedrawWindow();
		UpdateDateText(nIndex, NUM_LINE_DISPLAY);
	}
	else
		AfxMessageBox(_T("Cannot find more similar pattern!"));
}
