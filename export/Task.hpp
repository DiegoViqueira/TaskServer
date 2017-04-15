/* 
                       Task Interface
@Autor: Diego Viqueira
@Date: 25/11/2016
*/
#ifndef __TASK_H_
#define __TASK_H_

//STD INCLUDES
#include <string>

//Namespaces
using namespace std;

class Task
{
public:
	Task(){};
	virtual ~Task() {};
	virtual const char * name() = 0;
	virtual bool start() = 0;
	virtual bool stop()  =0 ;
	

	

};



#endif
