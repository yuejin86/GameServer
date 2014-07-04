#ifndef _MASTER_H
#define _MASTER_H
#include <boost/serialization/singleton.hpp>
#include "Common.h"
#include "WorldSocket.h"

using namespace boost;
class Master
{
public:
	Master();
	int run();
	void HookSignals();
	void UnHookSignals();
	static bool IsStopNow(){ return m_IsStop;}
	void start_accept();

protected:
	~Master();
	void handle_accept(WorldSocket* new_session, const boost::system::error_code& error);

private:
	bool StartDB();
	int StartNetWork(int16 port);
	static void SetStopEvent(bool s);
	static void OnSignal(int s);

private:
	static bool m_IsStop;
	asio::ip::tcp::acceptor* m_acceptor;
	boost::asio::io_service* m_socket;
};

#define sMaster serialization::singleton<Master>::get_mutable_instance()

#endif