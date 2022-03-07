
// serverDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "server.h"
#include "serverDlg.h"
#include "afxdialogex.h"
//#include "Mysocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CserverDlg �Ի���




CserverDlg::CserverDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CserverDlg::IDD, pParent)
	, m_Port(8000)
	, m_strPath(_T("d:\\serverFiles\\"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strMsg = _T("");
}

void CserverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LRECVD, m_ctlRecvd);
	DDX_Text(pDX, IDC_EMSG, m_strMsg);
	DDX_Text(pDX, IDC_EMSG_PORT, m_Port);
	DDX_Text(pDX, IDC_EDIT_Path, m_strPath);
}

BEGIN_MESSAGE_MAP(CserverDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BSEND, &CserverDlg::OnBnClickedBsend)
	ON_BN_CLICKED(IDC_SERVERSTART, &CserverDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_SERVERCLOSE, &CserverDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_SERVERSENDFILE, &CserverDlg::OnBnClickedSendFile)
	ON_BN_CLICKED(IDC_SERVERCLOSE2, &CserverDlg::OnBnClickedServerclose2)
END_MESSAGE_MAP()


// CserverDlg ��Ϣ�������

BOOL CserverDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_sConnectSocket.SetParent(this);
	m_sListenSocket.SetParent(this);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CserverDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CserverDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CserverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CserverDlg::GetErrorMsg()
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,0, GetLastError(), 
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //Ĭ������
		(LPTSTR)&lpMsgBuf, 0, NULL );
	//��ʾ
	//MessageBox(0,(LPCTSTR)lpMsgBuf,_T("GetLastError"),MB_OK|MB_ICONINFORMATION );
	CString m_strError;
	m_strError.Format("������룺%d  \n������Ϣ��%s",GetLastError(), (LPCTSTR)lpMsgBuf);
	
	//�ͷ��ڴ�
	::LocalFree( lpMsgBuf );
    return m_strError;
}

void CserverDlg::OnAccept()
{
	//ʹ��m_sConnectSocket���ܣ�������recv
	if (m_sListenSocket.Accept(m_sConnectSocket) == SOCKET_ERROR)
	{
		//������Ϣ���
		CString m_ErrorMsg;
		m_ErrorMsg = GetErrorMsg();
		MessageBox(m_ErrorMsg);
		return;
	}
	else {
		m_sConnectSocket.GetPeerName(client_IP, client_Port);
		AfxMessageBox(client_IP);
	}
}

void CserverDlg::OnReceive()
{
	char *pBuf = new char[1025];
	int iBufSize = 1024;
	int iRcvd = m_sConnectSocket.Receive(pBuf,iBufSize);
	CString strRecvd;
	if(iRcvd == SOCKET_ERROR)
	{
		CString m_ErrorMsg;
		m_ErrorMsg = GetErrorMsg();
		MessageBox(m_ErrorMsg);
		return;
	}
	else
	{
		pBuf[iRcvd] = NULL;
		strRecvd = pBuf;
		if (strRecvd == "aFile") {
			recvFile();
		}
		else {
			strRecvd = "�Է�˵ : "+strRecvd; 
			m_ctlRecvd.AddString(strRecvd);
		}
		UpdateData(FALSE);
	}
	delete[] pBuf;
}

void CserverDlg::OnClose()
{
    m_sConnectSocket.Close();
}

void CserverDlg::OnBnClickedBsend()
{	
	UpdateData(TRUE);
	if(m_strMsg !="")
	{  
		SendMsg(m_strMsg);
	}
	else {
		AfxMessageBox("���벻�ÿ�");
	}
}

void CserverDlg::SendMsg(CString msg)
{
	CString m_strMessage = msg;
	if (m_sConnectSocket.Send(LPCTSTR(m_strMessage), m_strMessage.GetLength()) == SOCKET_ERROR)
	{
		CString m_ErrorMsg;
		m_ErrorMsg = GetErrorMsg();
		MessageBox(m_ErrorMsg);
		return;
	}
	else
	{
		if (msg == "aFile")//���������ļ�����ͨ��Ϣ
			return;
		m_strMessage = "�Լ�˵: " + m_strMessage;
		m_ctlRecvd.AddString(m_strMessage);
		m_strMsg = "";
		UpdateData(FALSE);
	}
}

void CserverDlg::recvFile()
{
	AfxSocketInit(NULL);
	CSocket sockClient;
	sockClient.Create();

	CString	szIP = client_IP;

	if (!sockClient.Connect((LPCTSTR)szIP, 9800))
	{
		AfxMessageBox("�Է�δ����");
		return;
	}

	SOCKET_STREAM_FILE_INFO StreamFileInfo;
	sockClient.Receive(&StreamFileInfo, sizeof(SOCKET_STREAM_FILE_INFO));

	UpdateData(TRUE);
	CString strFolderPath = m_strPath;
	if (!PathFileExists(strFolderPath))//�ļ����Ƿ����
	{
		CreateDirectory(strFolderPath, NULL);//��������ھʹ���
	}
	CString strFileName;
	strFileName.Format("%s", StreamFileInfo.szFileTitle);
	strFileName = strFolderPath + strFileName;
	CFile destFile(strFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

	UINT dwRead = 0;
	while (dwRead < StreamFileInfo.nFileSizeLow)
	{
		byte* data = new byte[1024];
		memset(data, 0, 1024);

		UINT dw = sockClient.Receive(data, 1024);
		destFile.Write(data, dw);

		dwRead += dw;
		delete[] data;
	}
	SetFileTime((HANDLE)destFile.m_hFile, &StreamFileInfo.ftCreationTime,
		&StreamFileInfo.ftLastAccessTime, &StreamFileInfo.ftLastWriteTime);
	destFile.Close();
	SetFileAttributes(StreamFileInfo.szFileTitle, StreamFileInfo.dwFileAttributes);

	sockClient.Close();
	m_ctlRecvd.AddString("���յ����ļ�" + strFileName);
	//m_strRecieveFile = strFolderPath + strFileName;

	UpdateData(FALSE);
}

void CserverDlg::OnBnClickedStart()
{
	UpdateData(1);
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return ;
	}
	//�����׽��־�������ض��Ķ˿�
	m_sListenSocket.Create(m_Port);
	//��������
	if (m_sListenSocket.Listen() == SOCKET_ERROR)
	{
		//������Ϣ���
		CString m_ErrorMsg;
		m_ErrorMsg = GetErrorMsg();
		MessageBox(m_ErrorMsg);
		return;
	}
	CString str;
	str.Format("%d", m_Port);
	AfxMessageBox(str);
	
	GetDlgItem(IDC_SERVERSTART)->EnableWindow(FALSE);
	GetDlgItem(IDC_SERVERCLOSE)->EnableWindow(TRUE);
}


void CserverDlg::OnBnClickedClose()
{
	m_sListenSocket.Close();
	m_sConnectSocket.Close();
	GetDlgItem(IDC_SERVERSTART)->EnableWindow(TRUE);
    GetDlgItem(IDC_SERVERCLOSE)->EnableWindow(FALSE);
}


void CserverDlg::OnBnClickedSendFile()
{
	CFileDialog	Dlg(TRUE);
	if(Dlg.DoModal()!=IDOK)
		return;
	
	CFile myFile;
	if(!myFile.Open(Dlg.GetPathName(), CFile::modeRead | CFile::typeBinary))
	{
		AfxMessageBox("�ļ�������!");
		return;
	}
	CString strFileName = myFile.GetFileTitle();
	CSocket sockSrvr;
	sockSrvr.Create(8800);

	sockSrvr.Listen();

	m_ctlRecvd.AddString("���ڷ����ļ�" + strFileName);
	UpdateData(FALSE);

	//��ʾ�Է��ڷ����ļ���
	//�ͻ����յ�����Ϣ�󣬴���Connect(IP, 8800)

	SendMsg("aFile");


	CSocket sockRecv;
	sockSrvr.Accept(sockRecv);

	SOCKET_STREAM_FILE_INFO	StreamFileInfo;
	WIN32_FIND_DATA FindFileData;

	FindClose(FindFirstFile(Dlg.GetPathName(),&FindFileData));
    memset(&StreamFileInfo,0,sizeof(SOCKET_STREAM_FILE_INFO));
	CString strFileTitle = myFile.GetFileTitle();
	strcpy_s(StreamFileInfo.szFileTitle, strFileTitle.GetLength()+1, strFileTitle);
	//ע��һ��Ҫ��1����Ϊ������������"\0"

    StreamFileInfo.dwFileAttributes		=		FindFileData.dwFileAttributes;
    StreamFileInfo.ftCreationTime       =       FindFileData.ftCreationTime;
    StreamFileInfo.ftLastAccessTime     =       FindFileData.ftLastAccessTime;
    StreamFileInfo.ftLastWriteTime      =       FindFileData.ftLastWriteTime;
    StreamFileInfo.nFileSizeHigh        =       FindFileData.nFileSizeHigh;
    StreamFileInfo.nFileSizeLow         =       FindFileData.nFileSizeLow;

	sockRecv.Send(&StreamFileInfo,sizeof(SOCKET_STREAM_FILE_INFO), 0);

	UINT dwRead=0;
	while(dwRead<StreamFileInfo.nFileSizeLow)
	{
		byte* data = new byte[1024];
		UINT dw=myFile.Read(data, 1024);
		sockRecv.Send(data, dw);

		dwRead+=dw;
		delete[] data;
	}
	myFile.Close();
	sockRecv.Close();

	m_ctlRecvd.AddString(strFileName+"�ļ��������");
	UpdateData(FALSE);
}


void CserverDlg::OnBnClickedServerclose2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(1);
	ShellExecute(NULL, "open", m_strPath, NULL, NULL, SW_SHOWNORMAL);
}

