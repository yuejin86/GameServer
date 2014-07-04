#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include <boost/thread/thread.hpp>

class ServerThread
{
public:
	ServerThread();
	~ServerThread();
	void Start();
	void Stop();
	void join();
private:
	virtual void Run() = 0;
private:
	boost::thread* m_thread;
};

class LogicalThread : public ServerThread
{
	void Run();
};

#endif