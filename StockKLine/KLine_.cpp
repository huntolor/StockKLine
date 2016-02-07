#include "stdafx.h"
#include "KLine.h"


CKLine::CKLine()
{
	SetColor(defRgbBack, defRgbYAxis, defRgbGraph);

	m_pPlotData = NULL;
	SetNumPlot(defNumPlot);

	m_nNumYAxis = defNumYAxis;
	m_penRed.CreatePen(PS_SOLID, 1, 0x0000FF);
	m_penGreen.CreatePen(PS_SOLID, 1, 0x00FF00);
	m_brushRed.CreateSolidBrush(0x0000FF);
	m_brushGreen.CreateSolidBrush(0x00FF00);

	SetRange(defLower, defUpper);
}


CKLine::~CKLine()
{
	m_penRed.DeleteObject();
	m_penGreen.DeleteObject();
	m_brushRed.DeleteObject();
	m_brushGreen.DeleteObject();
}

/****************************************************************************
Desc: �F��ݒ肷��.
Arg: �w�i�̐F
Y ���̐F
�O���t�̐F
Return: ---
****************************************************************************/
void CKLine::SetColor(COLORREF rgbBack, COLORREF rgbYAxis, COLORREF rgbGraph)
{
	m_rgbBack = rgbBack;
	m_rgbYAxis = rgbYAxis;
	m_rgbGraph = rgbGraph;

	m_penYAxis.DeleteObject();
	m_penGraph.DeleteObject();

	m_penYAxis.CreatePen(PS_DOT, 1, m_rgbYAxis);
	m_penGraph.CreatePen(PS_SOLID, 1, m_rgbGraph);
}


/****************************************************************************
Desc: �v���b�g����ݒ肷��.
Arg: �v���b�g��
Return: ---
****************************************************************************/
void CKLine::SetNumPlot(unsigned int nNum)
{
	ASSERT(nNum > 1);

	m_nNumPlot = nNum;

	if (m_pPlotData) delete[] m_pPlotData;
	m_pPlotData = new double[m_nNumPlot];

	::ZeroMemory(m_pPlotData, sizeof(double) * m_nNumPlot);
}

/****************************************************************************
Desc: Y ���̐���ݒ肷��.
Arg: Y ���̐�
Return: ---
****************************************************************************/
void CKLine::SetNumYAxis(unsigned int nNum)
{
	m_nNumYAxis = nNum;
}

/****************************************************************************
Desc: �O���t�̎��l�͈̔͂�ݒ肷��.
Arg: ����
���
Return: ---
****************************************************************************/
void CKLine::SetRange(double fLower, double fUpper)
{
	if (fLower > fUpper) {
		double tmp = fLower;
		fLower = fUpper;
		fUpper = tmp;
	}

	ASSERT(fUpper - fLower != 0);

	m_nLower = fLower * 100;
	m_nUpper = fUpper * 100;

}

/****************************************************************************
Desc: �v���b�g����.
Arg: �l
Return: ---
****************************************************************************/
void CKLine::Plot(double fValue)
{
	for (int i = m_nNumPlot - 1; i > 0; i--) {
		m_pPlotData[i] = m_pPlotData[i - 1];
	}

	m_pPlotData[0] = fValue;

	InvalidateRect(NULL, FALSE);
}

void CKLine::SetKLineData(PRICES* pHistory, int nCount)
{
	ASSERT(m_nNumPlot > 1);
	ASSERT(m_nUpper - m_nLower != 0);

	m_pHistory = pHistory;
	m_nDataCount = nCount;

	InvalidateRect(NULL, FALSE);
}

/****************************************************************************
Desc: �O���t��`�悷��.
Arg: �O���t�̕�
�O���t�̍���
Return: ---
****************************************************************************/
void CKLine::Draw(CDC* pDC, int nWidth, int nHeight)
{
	CPen* pOldPen;

	//-----------------------------------------------------------------------
	// �w�i
	pDC->FillSolidRect(0, 0, nWidth, nHeight, m_rgbBack);

	//-----------------------------------------------------------------------
	// Y ��

	//double YAxisX;	// Y ���� X �ʒu
	//double YAxisSpace = (double)nWidth / (m_nNumYAxis + 1); // Y ���̊Ԋu

	//pOldPen = pDC->SelectObject(&m_penYAxis);
	//CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	//for(int i = 1; i <= m_nNumYAxis; i++){
	//	YAxisX = nWidth - YAxisSpace * i;
	//	pDC->MoveTo((int)YAxisX, 0);
	//	pDC->LineTo((int)YAxisX, nHeight);
	//}

	//-----------------------------------------------------------------------
	// �O���t

	ASSERT(m_nNumPlot > 1);
	ASSERT(m_nUpper - m_nLower != 0);

	double PlotX;	// �v���b�g���� X �ʒu
	double PlotSpace = (double)nWidth / (m_nNumPlot - 1);	// �v���b�g�̊Ԋu
	int rcWidth = (int)(PlotSpace / 2.0);
	int rcTop, rcLeft, rcRight, rcBottom, lineTop, lineBottom;

	nHeight--;	// PlotY = nHeight �̈ʒu�ɂ͐���`��ł��Ȃ�����



	for (int j = 0; j < m_nNumPlot; j++) {
		if (j >= m_nDataCount)
			continue;
		PRICES* pData = m_pHistory + j;

		if (pData->close >= pData->open)
		{
			pDC->SelectObject(&m_penRed);
			pDC->SelectObject(&m_brushRed);
		}
		else
		{
			pDC->SelectObject(&m_penGreen);
			pDC->SelectObject(&m_brushGreen);
		}

		PlotX = nWidth - PlotSpace * j;
		rcLeft = PlotX - rcWidth / 2;
		rcRight = PlotX + rcWidth / 2;
		rcTop = nHeight * (1.0 - (double)(pData->open * 100 - m_nLower) / (double)(m_nUpper - m_nLower));
		rcBottom = nHeight * (1.0 - (double)(pData->close * 100 - m_nLower) / (double)(m_nUpper - m_nLower));
		lineTop = nHeight * (1.0 - (double)(pData->high * 100 - m_nLower) / (double)(m_nUpper - m_nLower));
		lineBottom = nHeight * (1.0 - (double)(pData->low * 100 - m_nLower) / (double)(m_nUpper - m_nLower));
		CRect rect(rcLeft, rcTop, rcRight, rcBottom);

		pDC->Rectangle(rect);
		pDC->MoveTo((int)PlotX, (int)lineTop);
		pDC->LineTo((int)PlotX, (int)lineBottom);
	}

	//pDC->SelectObject(pOldBrush);
	//pDC->SelectObject(pOldPen);

}


/****************************************************************************

Message Handlers

****************************************************************************/
BEGIN_MESSAGE_MAP(CKLine, CStatic)
	//{{AFX_MSG_MAP(CKLine)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/****************************************************************************
Desc: �O���t�̕`��.
Arg: ---
Return: ---
****************************************************************************/
void CKLine::OnPaint()
{
	CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

	CDC MemDC;
	CBitmap Bitmap;
	CBitmap* pOldBitmap;
	CRect rcClient;

	GetClientRect(&rcClient);
	int nWidth = rcClient.Width();
	int nHeight = rcClient.Height();

	MemDC.CreateCompatibleDC(&dc);
	Bitmap.CreateCompatibleBitmap(&dc, nWidth, nHeight);
	pOldBitmap = MemDC.SelectObject(&Bitmap);

	// �O���t�`��
	Draw(&MemDC, nWidth, nHeight);

	dc.BitBlt(0, 0, nWidth, nHeight, &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pOldBitmap);

}