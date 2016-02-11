
// StockKLineDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once

#include "KLine.h"
#include <string>
#include "afxwin.h"

// CStockKLineDlg �_�C�A���O
class CStockKLineDlg : public CDialogEx
{
// �R���X�g���N�V����
public:
	CStockKLineDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^�[

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STOCKKLINE_DIALOG };
#endif
	CKLine	m_KLine;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGetprice();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	BOOL InitStockList();
	void UpdateScrollBar(int nPos, int nMax, int nPage);
	BOOL DrawKLine(std::string strCode);
	void UpdateDateText(int iLast, int nNum = NUM_LINE_DISPLAY);
	CString m_strSearch;
	CString m_strDate0;
	CString m_strDate1;
	CString m_strDate2;
	CString m_strDate3;
	CString m_strDate4;
	CString m_strDate5;
	CString m_strDate6;
	CString m_strDate7;
	CString m_strDate8;
	afx_msg void OnBnClickedFindpattern();
	CString m_strStockInput;
	CString m_strStockName;
	CString m_strStockCode;
	afx_msg void OnBnClickedDownloadall();
};
