#ifndef __MMDC_HTTP_SERVER_H__
#define __MMDC_HTTP_SERVER_H__

#include "EvHttpServer/EvHttpServer.h"

namespace maxmob
{
class MMDCHttpServer : public ustd::EvHttpServer
{
public:
	MMDCHttpServer (const unsigned int& port, const int& work_size = 1);
	~MMDCHttpServer (void);

	virtual void start (void);
	virtual void stop (void);
	virtual void registerCallbacks (evhttp* http_server);

private:
	static void onBidRequest (evhttp_request* req, void* param);
	static void onTimer (int fd, short event, void* param);
	static void onGeneralRequest (evhttp_request* req, void* param);

};
}
#endif // End __MMDC_HTTP_SERVER_H__
