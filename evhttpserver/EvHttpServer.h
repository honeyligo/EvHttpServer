#ifndef __EVHTTP_SERVER_H__
#define __EVHTTP_SERVER_H__

#include <vector>
#include <string>
#include "common.h"

namespace ustd
{

class EvHttpThread;

class EvHttpServer
{
public:
	static evutil_socket_t bindPort (const std::string& ip, const unsigned short& port);

public:
	EvHttpServer (const std::string& ip, const unsigned int& port, const int& work_size = 1, const int& max_header_size = -1, const int& max_body_size = -1);
	virtual ~EvHttpServer (void);

	virtual void start (void);
	virtual void stop (void);
	virtual bool isStart (void);
	virtual void registerCallbacks (evhttp* http_server) = 0;

private:
	friend class EvHttpThread;
	int getMaxHeadersSize (void) const
	{
		return max_header_size_;
	}

	int getMaxBodySize (void) const
	{
		return max_body_size_;
	}

private:
	std::string						ip_;
	unsigned int					server_port_;
	evutil_socket_t					fd_;
	bool							is_start_;
	const int						network_size_;
	const int						max_header_size_;
	const int						max_body_size_;
	std::vector<EvHttpThread*>		threads_;
};
}
#endif // End __EVHTTP_SERVER_H__
