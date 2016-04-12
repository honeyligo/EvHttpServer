#include <functional>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>

#include "EvHttpServer/common.h"
#include "MMDCHttpServer.h"

#define REPORT_INTERVAL		5 //sec

namespace maxmob
{
// public
MMDCHttpServer::MMDCHttpServer (const unsigned int& port, const int& work_size)
	: EvHttpServer (port, work_size)
{
}

MMDCHttpServer::~MMDCHttpServer (void)
{
}

// public
void
MMDCHttpServer::start (void)
{
	EvHttpServer::start ();
}

// public
void
MMDCHttpServer::stop (void)
{
	EvHttpServer::stop ();
}

// public
void MMDCHttpServer::registerCallbacks (evhttp* http_server)
{
	struct timeval tv;
	tv.tv_sec = REPORT_INTERVAL;
	tv.tv_usec = 0;

	struct event *report_event = (struct event*)malloc(sizeof(event));

	event_assign(report_event, http_server->base, -1, EV_PERSIST, &MMDCHttpServer::onTimer, nullptr);
	event_add(report_event, &tv);

	evhttp_set_cb(http_server, "/api/bid", &MMDCHttpServer::onBidRequest, nullptr);
	evhttp_set_gencb(http_server, &MMDCHttpServer::onGeneralRequest, nullptr);
}

// private
void 
MMDCHttpServer::onBidRequest (evhttp_request* req, void* param)
{
	evhttp_remove_header (req->output_headers, "Content-Type");
	evhttp_add_header (req->output_headers, "Content-Type", "application/json; charset=UTF-8");

	// write redis
	//////////////////////////////////////////////////////////////////////////


	// send response
	std::string body("{\"method\":\"onBidRequest\"}");
	ustd::ncAutoEVBuffer buf;
	if (evbuffer_add(buf.get (), body.c_str (), body.length ()) == 0)
	{
		evhttp_send_reply(req, EVHTTP_OK, "OK", buf.get ());
	}
}

// private
void MMDCHttpServer::onGeneralRequest (evhttp_request* req, void* param)
{
	evhttp_remove_header (req->output_headers, "Content-Type");
	evhttp_add_header (req->output_headers, "Content-Type", "application/json; charset=UTF-8");

	std::string body("{\"method\":\"onGeneralRequest\"}");
	ustd::ncAutoEVBuffer buf;
	if (evbuffer_add(buf.get (), body.c_str (), body.length ()) == 0)
	{
		evhttp_send_reply(req, EVHTTP_OK, "OK", buf.get ());
	}
}

// private
void MMDCHttpServer::onTimer (int fd, short event, void* param)
{
	// push to report
	printf("onTimerRequest\n");

}

}