
// clientDlg.h : ͷ�ļ�
#include "Mysocket.h"
#pragma once

typedef struct _SOCKET_STREAM_FILE_INFO {

	TCHAR       szFileTitle[128];                   //�ļ��ı�����
	DWORD       dwFileAttributes;                   //�ļ�������
	FILETIME    ftCreationTime;                     //�ļ��Ĵ���ʱ��
	FILETIME    ftLastAccessTime;                   //�ļ���������ʱ��
	FILETIME    ftLastWriteTime;                    //�ļ�������޸�ʱ��
	DWORD       nFileSizeHigh;                      //�ļ���С�ĸ�λ˫��
	DWORD       nFileSizeLow;                       //�ļ���С�ĵ�λ˫��
	DWORD       dwReserved0;                        //������Ϊ0
	DWORD       dwReserved1;                        //������Ϊ0

} SOCKET_STREAM_FILE_INFO, * PSOCKET_STREAM_FILE_INFO;

// CclientDlg �Ի���
class CclientDlg : public CDialogEx
{
// ����
public:
	CString GetErrorMsg();
	//	��дOnReceive()��
	void OnReceive();
	CclientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLbnSelchangeList1();
private:
	CMysocket m_sConnectSocket;
	CMysocket m_sListenSocket;
public:
	CString m_strMess;
	CListBox m_ctrMessage;
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedDisconnect();
	afx_msg void OnBnClickedClientSend();
	afx_msg void OnEnChangeEmsg();
	afx_msg void ReceiveFile();
	CString m_strIPAddress;
	CString m_strFolder;
	afx_msg void OnBnClickedClientopenfolder();
	CString m_strRecieveFile;
	afx_msg void OnLbnSelchangeLmsg();
	afx_msg void OnBnClickedButton1();
	int m_Port;
};
