#include "thread.h"

namespace ustd
{

base_thread::base_thread()
{
	this->thread_proc_ = nullptr;
	this->thread_state_ = STATE_UNINITIALIZED;
}

base_thread::~base_thread()
{
	this->stop_thread();
}

bool base_thread::start_thread(const std::function<void(void)> &thread_proc)
{
	if (STATE_RUNNING == this->thread_state_ || STATE_SUSPENDED == this->thread_state_)
	{
		return true;
	}

	this->thread_proc_ = thread_proc;

	int ret = pthread_create(&this->thread_handle_, nullptr, &thread_proc_func, this);

	if (0 == ret)
	{
		this->thread_state_ = STATE_RUNNING;
		return true;
	}

	return false;
}

bool base_thread::stop_thread()
{
	if (STATE_UNINITIALIZED == this->thread_state_ || STATE_TERMINATED == this->thread_state_)
	{
		return true;
	}

	this->thread_state_ = STATE_TERMINATED;

	void *thread_status;
	int ret = pthread_join(this->thread_handle_, &thread_status);
	if (0 == ret)
	{
		return true;
	}

	return false;
}

void *base_thread::thread_proc_func(void *param)
{
	base_thread *this_ptr_ = (base_thread *)param;

	std::function<void(void)> thread_proc = this_ptr_->thread_proc_;

	if (thread_proc != nullptr)
	{
		thread_proc();
	}

	pthread_exit(nullptr);
}

Thread_State base_thread::get_thread_state() const
{
	return (this->thread_state_);
}

const pthread_t *base_thread::get_thread_handle() const
{
	return (&this->thread_handle_);
}

}

