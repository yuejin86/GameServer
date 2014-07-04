#ifndef SESSION_H
#define SESSION_H
#include "Common.h"

class WorldSocket;
class Session
{
public:
	Session(uint32 id, WorldSocket* wSocket);
	~Session();
	int Update(uint32 diff);
	boost::asio::ip::tcp::socket& socket()
	{
		return  *m_Socket;
	}

private:
	uint32 m_AccountId;
	WorldSocket* m_Socket;
};

#endif