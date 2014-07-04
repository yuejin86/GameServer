#include "Master.h"
#include <iostream>
#include "Common.h"
#include <boost/thread/thread_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include "ServerThread.h"
#include "Session.h"
#include <boost/function/function0.hpp>  
#include "Session.h"

using namespace std;
using boost::asio::ip::tcp;

Master::Master() : m_acceptor(NULL)
{

}

Master::~Master()
{
	if (m_acceptor)
	{
		delete m_acceptor;
		m_acceptor = NULL;
	}
}

int Master::run()
{
	Master::m_IsStop = false;
	cout << "The GameServer is running!"<<endl;
	if (!StartDB())
	{
		cout<<"BD Start Error!"<<endl;
	}

	if (StartNetWork(8099) == -1)
	{
		cout<<"StartNetWork Error!"<<endl;
	}
	HookSignals();

	LogicalThread* logicalThread = new LogicalThread;
	logicalThread->Start();
	logicalThread->join();

// 	while(!IsStopNow())
// 	{
// 		boost::this_thread::sleep(boost::get_system_time() + boost::posix_time::seconds(10));  
// 		cout << "You are a SB"<< endl;
// 	}

	if (logicalThread)
	{
		logicalThread->Stop();
	}

	UnHookSignals();

	return 0;
}

bool Master::StartDB()
{
	return true;
}

int Master::StartNetWork(int16 port)
{

	m_socket = new WorldSocket;
	m_acceptor = new tcp::acceptor(*m_socket, tcp::endpoint(tcp::v4(), port));

	return 0;
}

void Master::OnSignal(int s)
{
	switch (s)
	{
	case SIGINT:
	case SIGTERM:
		m_IsStop = true;
		break;
#ifdef _WIN32
	case SIGBREAK:
		m_IsStop = true;
		break;
#endif
	}

	signal(s, OnSignal);
}

void Master::HookSignals()
{
	signal(SIGINT, OnSignal);
	signal(SIGTERM, OnSignal);
#ifdef _WIN32
	signal(SIGBREAK, OnSignal);
#endif
}

void Master::UnHookSignals()
{
	signal(SIGINT, 0);
	signal(SIGTERM, 0);
#ifdef _WIN32
	signal(SIGBREAK, 0);
#endif
}

void Master::SetStopEvent(bool s)
{
	m_IsStop = s; 
}

void Master::start_accept()
{
	Session* new_session = new Session(1, (WorldSocket*)&m_socket);
	m_acceptor->async_accept(new_session->socket(),
		boost::bind(&Master::handle_accept, this, new_session,
		boost::asio::placeholders::error));
}

void Master::handle_accept(WorldSocket* new_session, const boost::system::error_code& error)
{
	if (!error)
	{
		//new_session;
	}
	else
	{
		delete new_session;
	}

	start_accept();
}

bool Master::m_IsStop = false;