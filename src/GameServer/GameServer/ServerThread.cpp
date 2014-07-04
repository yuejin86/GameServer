#include "ServerThread.h"
#include <boost/function/function0.hpp>  
#include <iostream>
#include "Master.h"

ServerThread::ServerThread()
{
	m_thread = NULL;
}

ServerThread::~ServerThread()
{
	if (m_thread != NULL)
	{
		delete m_thread;
		m_thread = NULL;
	}
}

void ServerThread::Start()
{
	if (m_thread == NULL)
	{
       boost::function0<void> fun = boost::bind(&ServerThread::Run, this);  
       m_thread = new boost::thread(fun);
	}
}

void ServerThread::Stop()
{
	if (m_thread != NULL)
	{
		//m_thread->join();
		m_thread->interrupt();
	}
}

void ServerThread::join()
{
	if (m_thread != NULL)
	{
		m_thread->join();
	}
}

void LogicalThread::Run()
{

	while(!sMaster.IsStopNow())
	{
		std::cout << "This is Logical Thread! " << std::endl;
		boost::this_thread::sleep(boost::posix_time::seconds(5));  
	}
}