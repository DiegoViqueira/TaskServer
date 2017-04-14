/* 
                        Periodic Task Service
@Autor: Diego Viqueira
@Date: 25/11/2016

*/
// STD LIBRARIES
#include <iostream>
#include <vector>
#include <time.h>
#include <string>

//BOOST LIBRARIES
#include "boost/asio.hpp"
#include "boost/thread.hpp"
#include "boost/scoped_ptr.hpp"

#include "Task.hpp"

#ifndef __TASK_SERVER_H_
#define __TASK_SERVER_H_

class ServiceTask : boost::enable_shared_from_this<ServiceTask>
{
public:

	//Constuctor of Service Task implemetacion
	ServiceTask();

	//Destructor shuts down the private io_service.
	~ServiceTask();
	
	//add new task
	void addTask(boost::shared_ptr<Task> oTask);

	//run all task scheduled
	void run();

	//stop all task scheduled
	void stop();


private:

	/// Private io_service 
	boost::asio::io_service work_io_service_;

	/// Work for the private io_service to perform. If we do not give the
	/// io_service some work to do then the io_service::run() function will exit
	/// immediately.
	boost::scoped_ptr<boost::asio::io_service::work> work_;

	// Vector of Task 
	// To Know all Task Names an Pointers to instances
	map<string, boost::shared_ptr<Task>> m_oTask;

	// Threads for All Task
	boost::thread_group  m_ThreadGroup;

	// Vector of Futures 
	// To know the result of the execution of a Task
	vector<pair<string, boost::shared_future<bool>>> m_futures;

};



#endif
