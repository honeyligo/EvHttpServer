#include <string.h>

#include "EvHttpThread.h"
#include "EvHttpServer.h"

namespace ustd
{
// public
EvHttpServer::EvHttpServer (const std::string& ip, const unsigned int& port, const int& work_size /* = 1 */, const int& max_header_size /* = -1 */, const int& max_body_size /* = -1 */)
	: ip_(ip)
	, server_port_(port)
	, fd_ (-1)
	, is_start_ (false)
	, network_size_ (work_size)
	, max_header_size_ (max_header_size)
	, max_body_size_ (max_body_size)
	, threads_ ()
{
	evthread_use_pthreads ();
}

// public static
evutil_socket_t
EvHttpServer::bindPort (const std::string& ip, const unsigned short& port)
{
	sockaddr_in in;
	memset (&in, 0, sizeof (in));
	in.sin_family = AF_INET;
	in.sin_port = htons (port);
	in.sin_addr.s_addr = inet_addr(ip.c_str());

	evutil_socket_t fd = socket (AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
	{
		return -1;
	}

	if (evutil_make_socket_nonblocking (fd) < 0)
	{
		evutil_closesocket (fd);
		return -1;
	}

	int on = 1;
	if (setsockopt (fd, SOL_SOCKET, SO_KEEPALIVE, (const char *)&on, sizeof (on)) < 0)
	{
		evutil_closesocket (fd);
		return -1;
	}

	if (evutil_make_listen_socket_reuseable (fd) < 0)
	{
		evutil_closesocket (fd);
		return -1;
	}

	if (::bind (fd, (sockaddr*)&in, sizeof (sockaddr_in)) < 0)
	{
		evutil_closesocket (fd);
		return -1;
	}

	listen (fd, 128);
	return fd;
}

EvHttpServer::~EvHttpServer (void)
{
	if (isStart ())
	{
		stop ();
	}
}

// public
void
EvHttpServer::start (void)
{
	if (is_start_ || ip_.empty() || server_port_ <= 0)
	{
		return;
	}
	is_start_ = true;
	
	fd_ = bindPort (ip_, server_port_);
	if (fd_ == -1)
	{
		return;
	}

	for (size_t i = 0; i < network_size_; ++i)
	{
		EvHttpThread* httpThread = new EvHttpThread (server_port_, fd_, this);
		threads_.push_back (httpThread);
		httpThread->start_thread(std::bind(&EvHttpThread::run, httpThread));
		httpThread->waitUntilStart ();
	}
}

// public
void
EvHttpServer::stop (void)
{
	if (!is_start_)
	{
		return;
	}

	is_start_ = false;

	for (std::vector<EvHttpThread*>::iterator it = threads_.begin (); it != threads_.end (); ++it)
	{
		(*it)->stop ();
		delete *it;
	}
	threads_.clear ();

	if (fd_ != -1)
	{
		evutil_closesocket(fd_);
		fd_ = -1;
	}
}

// public
bool
EvHttpServer::isStart (void)
{
	return is_start_;
}

}