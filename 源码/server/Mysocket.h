#pragma once

// CMysocket ����Ŀ��

class CMysocket : public CAsyncSocket
{
public:
	CMysocket();
	virtual ~CMysocket();
	void SetParent(CDialog *pWnd);
	//��д
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
private:
	CDialog* m_pWnd;
};

