#include "EvHttpServer.h"
#include "EvHttpThread.h"

namespace ustd
{
// public
EvHttpThread::EvHttpThread (const evutil_socket_t& evsock, EvHttpServer* server)
	: http_server_ (nullptr)
	, evbase_ (nullptr)
	, evsock_ (evsock)
	, server_ (server)
	, has_start_ (false)
{
}

EvHttpThread::~EvHttpThread (void)
{
	stop ();
}

void
EvHttpThread::run (void)
{
	evbase_ = event_base_new();

	const int flags = LEV_OPT_REUSEABLE | LEV_OPT_THREADSAFE;
	evconnlistener* listener = evconnlistener_new (evbase_, nullptr, nullptr, flags, 0, evsock_);
	if(!listener)
	{
		printf("listen port error");
		return;
	}

	http_server_ = evhttp_new (evbase_);
	evhttp_set_max_headers_size (http_server_, server_->getMaxHeadersSize ());
	evhttp_set_max_body_size (http_server_, server_->getMaxBodySize ());
	evhttp_set_allowed_methods(http_server_, EVHTTP_REQ_POST);

	evhttp_bound_socket* bound_socket = evhttp_bind_listener (http_server_, listener);
	if (!bound_socket)
	{
		printf("bind error");
		return;
	}

	server_->registerCallbacks (http_server_);
	evconnlistener_enable (listener);

	has_start_ = true;

	event_base_dispatch (evbase_);
}

bool
EvHttpThread::hasStart (void)
{
	return has_start_;
}

void
EvHttpThread::stop (void)
{
	if (!has_start_)
	{
		return;
	}

	if (evbase_)
	{
		event_base_loopexit (evbase_, nullptr);
	}

	if (http_server_)
	{
		evhttp_free (http_server_);
		http_server_ = nullptr;
	}

	if (evbase_)
	{
		event_base_free (evbase_);
		evbase_ = nullptr;
	}
}

void
EvHttpThread::waitUntilStart (void)
{
	while (!hasStart ())
	{
		pthread_yield();
	}
}
}