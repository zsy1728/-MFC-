// Mysocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "server.h"
#include "Mysocket.h"
#include "serverDlg.h"

// CMysocket

CMysocket::CMysocket()
{
}

CMysocket::~CMysocket()
{
}


// CMysocket ��Ա����
void CMysocket::SetParent(CDialog *pWnd)
{
   m_pWnd = pWnd;
}

void CMysocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
    ((CserverDlg*)m_pWnd)->OnAccept();
	CAsyncSocket::OnAccept(nErrorCode);
}



void CMysocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	((CserverDlg*)m_pWnd)->OnClose();
	CAsyncSocket::OnClose(nErrorCode);
}

void CMysocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
    ((CserverDlg*)m_pWnd)->OnReceive();
	CAsyncSocket::OnReceive(nErrorCode);
}
