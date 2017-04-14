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
	Task(const char * identifier) :m_sIdentifier(identifier){};
	virtual ~Task() {};
	const char * name(){ return m_sIdentifier.c_str();}
	virtual bool start() = 0;
	virtual bool stop()  =0 ;
	
private:
	string m_sIdentifier;
	

};



#endif
