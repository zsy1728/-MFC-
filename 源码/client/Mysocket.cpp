// Mysocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "client.h"
#include "Mysocket.h"
#include "clientDlg.h"

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

void CMysocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	((CclientDlg*)m_pWnd)->OnReceive();
	CAsyncSocket::OnReceive(nErrorCode);
}

