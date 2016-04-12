#ifndef __EVHTTP_UTIL_H__
#define __EVHTTP_UTIL_H__

#include "common.h"

namespace ustd
{
class ncAutoEVBuffer
{
public:
	ncAutoEVBuffer (void)
		: evbuf_ (nullptr)
	{
		evbuf_ = evbuffer_new ();
		if (evbuf_ == 0) 
		{
			return;
		}

		if (evbuffer_enable_locking (evbuf_, nullptr) == -1) 
		{
			return;
		}
	}

	~ncAutoEVBuffer (void)
	{
		evbuffer_free (evbuf_);
	}

	evbuffer* get (void)
	{
		return evbuf_;
	}

private:
	evbuffer* evbuf_;
};

class ncAutoEVKeyValQ
{
public:
	~ncAutoEVKeyValQ (void)
	{
		evhttp_clear_headers (&kvq_);
	}

	evkeyvalq* get (void)
	{
		return &kvq_;
	}

private:
	evkeyvalq kvq_;
};

struct EvHttpBuffer_t
{
	EvHttpBuffer_t ()
		: buffer_ (nullptr)
		, length_ (0)
	{
	}
	char* buffer_;
	size_t length_;
};
}
#endif // End __EVHTTP_UTIL_H__
