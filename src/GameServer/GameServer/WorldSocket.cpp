#include "WorldSocket.h"

WorldSocket::WorldSocket() : m_IsClose(false)
{

}

WorldSocket::~WorldSocket()
{

}

bool WorldSocket::IsClose() const
{
	return m_IsClose;
}

void WorldSocket::Close()
{
	m_IsClose = true;
}