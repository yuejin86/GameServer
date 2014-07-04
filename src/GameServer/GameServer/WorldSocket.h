#ifndef WORLD_SOCKET_H
#define WORLD_SOCKET_H
#include <boost/asio.hpp>

class WorldSocket : public boost::asio::io_service
{
public:
	WorldSocket();
	~WorldSocket();
	bool IsClose() const;
	void Close();
private:
	bool m_IsClose;
};

#endif