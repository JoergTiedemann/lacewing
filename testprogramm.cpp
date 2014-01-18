#include <vld.h>

#include "resource.h"

#include <Lacewing.h>
#include <string.h>
#include <atlstr.h>
#include <atltime.h>
#include <wininet.h>

#pragma comment (lib,"liblacewing.lib")

lacewing::eventpump EventPump = lacewing::eventpump_new();

void onGet (lacewing::webserver Webserver, lacewing::webserver_request request)
{
	if(!strcmp(request->url(),"down.html"))
	{
		request->writef("server shutdown"); 
		// Webserver shutdown
		EventPump->post_eventloop_exit();
		return;
	} 


 if(!strcmp(request->url(),""))
 {
	 request->writef("webserver said: site not found"); 
	return;
 }
 else
 {
	 request->guess_mimetype(request->url());
	 request->write_file(request->url());
	 return;
 }
}

void onPost (lacewing::webserver Webserver, lacewing::webserver_request request)
{
}

int main(int argc, char * argv[])
{
	lacewing::webserver Webserver = lacewing::webserver_new(EventPump);
	printf ("Lacewing thread-ID %d\n", GetCurrentThreadId());

	//Webserver->enable_manual_finish(); 
	Webserver->on_get(onGet);
	Webserver->on_post(onPost);

	Webserver->host(8080); /* defaults to port 80 */

	EventPump->start_eventloop ();

	lacewing::webserver_delete (Webserver);
	lacewing::pump_delete (EventPump);
	return 0;
}

