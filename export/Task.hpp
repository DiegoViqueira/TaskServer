/* 
                       Task Interface
@Autor: Diego Viqueira
@Date: 25/11/2016
*/

#ifndef __TASK_H_
#define __TASK_H_

    Class Task
    {
        Public: 
        virtual const char* name()=0;
        virtual int strat()=0;
        virtual void stop()=0;
    }

#endif
