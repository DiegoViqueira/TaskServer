// TestServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Logger.hpp"
#include "Task.hpp"
#include "TaskServer.hpp"
#include "boost/scoped_ptr.hpp"

// STD LIBRARIES
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

class My_Task :public Task
{
	public:
		My_Task() {};
	My_Task(std::string name):m_sIdentifier(name){};
	const char * name() { return m_sIdentifier.c_str(); }
	bool start() { return true; };
	bool stop() { return false; };

	private:
	string m_sIdentifier;
	
};

int main()
{
	My_Task TEMP;
	ServiceTask mytask;
	boost::shared_ptr<Task> task1(new My_Task("NRO 1"));
	boost::shared_ptr<Task> task2(new My_Task("NRO 2"));
	mytask.addTask(task1);
	mytask.addTask(task2);

	mytask.run();

    return 0;
}

