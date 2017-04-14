/* 
                        Periodic Task Service - Implementation
@Autor: Diego Viqueira
@Date: 25/11/2016

*/

//Constuctor of Service Task implemetacion
ServiceTask::ServiceTask() : work_io_service_(), // Construct the IO Service
	work_(new boost::asio::io_service::work(work_io_service_)) //Construct the Work 
{
	std::cout << "ServiceTask ()[" << boost::this_thread::get_id() << "] - Builded." << std::endl;
};

//Destructor shuts down the private io_service.
ServiceTask::~ServiceTask()
{
	/// Indicate that we have finished with the private io_service. Its
	/// io_service::run() function will exit once all other work has completed.
	work_.reset();
	//wait for all threads to join
	m_ThreadGroup.join_all();
	//clear vector of all futures 
	m_futures.clear();
	//clear vector of task	
	m_oTask.clear();

	//stop the io_service
	work_io_service_.stop();
	std::cout << "ServiceTask ()[" << boost::this_thread::get_id() << "] - Destructed." << std::endl;

}

//add new task
void ServiceTask::addTask(boost::shared_ptr<Task> oTask)
{

	//insert new task to vector of task to execute
	m_oTask.insert(std::make_pair(string(oTask->name()), oTask));

}

//run all task scheduled
void ServiceTask::run()
{
	std::cout << "ServiceTask::run() [" << boost::this_thread::get_id() << "] - Start Runing." << std::endl;

	// for each task 
	for (auto temp_Map : m_oTask)
	{
		cout << "ServiceTask::run() Adding Tash - " << temp_Map.first << endl;

		//create new thread to io_service
		m_ThreadGroup.create_thread(boost::bind(&boost::asio::io_service::run, &work_io_service_));

		//add the task to package task
		//that it's to  can put the task to io_service
		boost::shared_ptr<task_t> task = boost::make_shared<task_t>(
			boost::bind(&Task::start, temp_Map.second));

		//geting the future 
		boost::shared_future<bool> fut(task->get_future());

		//insert future into Map
		//to handle response of each task
		m_futures.push_back(std::make_pair(temp_Map.first, fut));

		//posting task into io service
		//that put thread to run
		work_io_service_.post(boost::bind(&task_t::operator(), task));

	}


	//control future's responces for each thread
	//while have futures to control
	while (m_futures.size() != 0)
	{
		//sleeping to control responses
		Sleep(2 * 1000);

		//iterating futures responses
		for (std::vector<pair <string, boost::shared_future<bool>>>::iterator it = m_futures.begin(); it != m_futures.end();)
		{
			//if the task in thread has finished
			if (it->second.wait_for (boost::chrono::seconds(0)) == boost::future_status::ready)
			{
				bool result = false;
				try
				{	//get the response of task finished
					result = it->second.get();

					cout << "ServiceTask::run() Task [" << it->first << "] Result : " << result << endl;

				}
				catch (...)
				{
					//exception occurred in task 
					cout << "ServiceTask::run() Task [" << it->first << "] Exception Happend." << endl;
					
					//mark the result as false to stop all task
					result = false;
				}



				//obtaining the rigth task to erase
				map<string, boost::shared_ptr<Task>>::iterator it_task = m_oTask.find(it->first);

				if (it_task != m_oTask.end())
					it_task->second->stop(); //stopping the task
											 //this is for security to clean variables
											 //but the  implementation should do all the stuff


											 //erasing
				//it = m_futures.erase(it);
				
				if ( result == true )
				{
					//add the task to package task
					//that it's to  can put the task to io_service
					boost::shared_ptr<task_t> task = boost::make_shared<task_t>(
						boost::bind(&Task::start, it_task->second));

					//geting the future 
					boost::shared_future<bool> fut(task->get_future());

					it->second= fut;

					//posting task into io service
					//that put thread to run
					work_io_service_.post(boost::bind(&task_t::operator(), task));

				}
				else
				{

					cout << "ServiceTask::run() stoping task - " << it->first << endl;
					//erasing
					it = m_futures.erase(it);

					// mark the next future to end
					if ( it != m_futures.end() )
					it->second.future_->mark_finished_with_result(false);
				}
				continue;
			}


			//increment the iterator
			it++;

		}
	}

	


};

void ServiceTask::stop()
{

};



