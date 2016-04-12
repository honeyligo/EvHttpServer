#include <unistd.h>
#include "MMDCHttpServer.h"

int main()
{
	maxmob::MMDCHttpServer server("127.0.0.1", 8181, 8);
	server.start();
	
	sleep(100000);

	return 0;
}