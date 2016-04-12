#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>
#include <functional>

namespace ustd
{

enum Thread_State
{
	STATE_UNINITIALIZED = 1,
	STATE_RUNNING,
	STATE_SUSPENDED,
	STATE_TERMINATED
};


class base_thread
{
public:
	base_thread();
	virtual ~base_thread();

public:
	Thread_State get_thread_state() const;
	const pthread_t *get_thread_handle() const;
	bool start_thread(const std::function<void(void)> &thread_proc);
	bool stop_thread();

private:
	pthread_t thread_handle_;
	Thread_State thread_state_;
	std::function<void(void)> thread_proc_;

protected:
	static void *thread_proc_func(void *param);
};

}



#endif
