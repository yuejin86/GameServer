#include "Master.h"
#include <iostream>

using namespace std;
Master::Master()
{

}

Master::~Master()
{

}

int Master::run()
{
	cout << "The GameServer is running!"<<endl;
	if (!StartDB())
	{
		cout<<"BD Start Error!"<<endl;
	}

	if (!StartNetWork())
	{
		cout<<"StartNetWork Error!"<<endl;
	}
	system("pause");
	return 0;
}

bool Master::StartDB()
{
	return true;
}

bool Master::StartNetWork()
{
	return true;
}
