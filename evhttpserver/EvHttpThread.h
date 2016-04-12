#ifndef __EVHTTP_THREAD_H__
#define __EVHTTP_THREAD_H__

#include "ustd/thread.h"
#include "common.h"

namespace ustd
{

class EvHttpThread : public base_thread
{
public:
	EvHttpThread (const evutil_socket_t& evsock, EvHttpServer* server);
	~EvHttpThread (void);

public:
	void run (void);
	bool hasStart (void);
	void stop (void);
	void waitUntilStart (void);

private:
	evhttp*				http_server_;
	event_base*			evbase_;
	evutil_socket_t		evsock_;
	EvHttpServer*		server_;
	bool				has_start_;
}; // class EvHttpThread
}
#endif // __EVHTTP_THREAD_H__
