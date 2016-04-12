#ifndef __COMMON_H__
#define __COMMON_H__

#include <event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <event2/thread.h>
#include <event2/http.h>
#include <event2/http_struct.h>
#include <event2/keyvalq_struct.h>
#include <event2/http_compat.h>
#include <event2/event_compat.h>
#include <evthread-internal.h>
#include <http-internal.h>

#include "EvHttpServer.h"
#include "EvHttpUtil.h"


#define EVHTTP_OK					200	/**< request completed ok */
#define EVHTTP_NO_CONTENT			204	/**< request does not have content */
#define EVHTTP_MOVEPERM				301	/**< the uri moved permanently */
#define EVHTTP_MOVETEMP				302	/**< the uri moved temporarily */
#define EVHTTP_NOT_MODIFIED			304	/**< page was not modified from last */
#define EVHTTP_BAD_REQUEST			400	/**< invalid http request was made */
#define EVHTTP_ACCESS_TOKEN_INVALID	401	/**< invalid access token */
#define EVHTTP_NOT_AUTHORIZED		403	/**< not allowed to access for this user  */
#define EVHTTP_NOT_FOUND			404	/**< could not find content for uri */
#define EVHTTP_BAD_METHOD			405	/**< method not allowed for this uri */
#define EVHTTP_ENTITY_TOO_LARGE		413	/**<  */
#define EVHTTP_EXPECT_ATION_FAILED	417	/**< we can't handle this expectation */
#define EVHTTP_INTERNAL				500	/**< internal error */
#define EVHTTP_NOT_IMPLEMENTED		501	/**< not implemented */
#define EVHTTP_SERV_UNAVAIL			503	/**< the server is not available */


#endif // __COMMON_H__
