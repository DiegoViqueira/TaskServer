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

#ifdef TASK_SERVER_IMPORT
	#define TASK_SERVER_API __declspec(dllimport)	
	# pragma message ("Importing Task Server...")
#else
	#define TASK_SERVER_API __declspec(dllexport)
	# pragma message ("Exporting Task Server...")
#endif

#ifndef __TASK_SERVER_H_
#define __TASK_SERVER_H_
namespace service_task
{

class TASK_SERVER_API ServiceTask
{
public:

	 static boost::shared_ptr< ServiceTask > Build_Service();

	 //add new task
	 virtual void addTask(boost::shared_ptr<Task> oTask) = 0;

	 //run all task scheduled
	 virtual void run() = 0;

	 //stop all task scheduled
	 virtual void stop() = 0;
  };


}
#endif
