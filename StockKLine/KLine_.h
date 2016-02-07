#pragma once

typedef struct StockPrices {
	long date;
	double open;
	double high;
	double low;
	double close;
	long volume;
	double adjClose;
} PRICES;

class CKLine : public CStatic
{
public:
	CKLine();
	~CKLine();

	enum {
		// �F�ݒ�
		defRgbBack = RGB(255, 255, 255),
		defRgbYAxis = RGB(160, 160, 160),
		defRgbGraph = RGB(192, 0, 0),

		// �O���t�̗v�f
		defNumPlot = 18,			// �v���b�g��
		defNumYAxis = 16,			// Y ���̐�

									// �͈�
		defLower = 0,				// ���� 		
		defUpper = 100, 			// ���
	};

	virtual void SetColor(COLORREF rgbBack, COLORREF rgbYAxis, COLORREF rgbGraph);
	virtual void SetNumPlot(unsigned int nNum);
	virtual void SetNumYAxis(unsigned int nNum);
	virtual void SetRange(double fLower, double fUpper);
	virtual void Plot(double fValue);
	virtual void SetKLineData(PRICES* pHistory, int nCount = 1);


protected:

	CPen		m_penYAxis; 		// Y ���`��p�y��
	CPen		m_penGraph; 		// ���C���`��p�y��
	CPen		m_penRed;
	CPen		m_penGreen;
	CBrush		m_brushRed;
	CBrush		m_brushGreen;

	COLORREF	m_rgbBack;			// �w�i�F
	COLORREF	m_rgbYAxis; 		// Y ���̐F
	COLORREF	m_rgbGraph; 		// ���̐F

	int 		m_nNumPlot; 		// �v���b�g��
	int 		m_nNumYAxis;		// Y ���̐�
	int			m_nLower;			// �v���b�g����l�͈̔͂̉���
	int			m_nUpper;			// �v���b�g����l�͈̔͂̏��

	double* 	m_pPlotData;		// �v���b�g����l
	PRICES*		m_pHistory;
	int			m_nDataCount;

	virtual void Draw(CDC* pDC, int nWidth, int nHeight);


	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CKLine)
	afx_msg void OnPaint();
	//}}AFX_MSG
};

