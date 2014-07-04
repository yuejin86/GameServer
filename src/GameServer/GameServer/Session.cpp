#include "Session.h"
#include "WorldSocket.h"

Session::Session(uint32 id, WorldSocket* wSocket) : m_AccountId(id), m_Socket(wSocket)
{

}

Session::~Session()
{
	if (m_Socket)
	{
		delete m_Socket;
		m_Socket = NULL;
	}
}

int Session::Update(uint32 diff)
{
	if (m_Socket && m_Socket->IsClose())
		return -1;

	return 0;
}