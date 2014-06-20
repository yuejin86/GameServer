#ifndef _MASTER_H
#define _MASTER_H
#include <serialization/singleton.hpp>

using namespace boost;

class Master
{
public:
	Master();
	int run();
protected:
	~Master();
private:
	bool StartDB();
	bool StartNetWork();
};

#define sMaster serialization::singleton<Master>::get_mutable_instance()

#endif