#include <iostream>
#include <string>
#include </mnt/c/Users/cring/Documents/GitHub/E5PRJ3/RPIkode/uwebsocketGit/uwebsockets/src/uWS.h>
#include <thread>
#include <sstream>

struct Data
{
  uWS::Hub &h;
  void operator()(uWS::WebSocket<uWS::SERVER> *ws,
		  char *message, size_t length,
		  uWS::OpCode opCode) {
        std::cout << "Data: " << std::string(message, length) << std::endl;
        ws->send(message, length, opCode);
  }

};


void async(uWS::Hub* h)
{
  int counter = 0;
  
  for(;;)
  {
    sleep(1);

    std::ostringstream ss;
    ss << "Number of broadcasts hejsa#" << counter++;
    
    h->broadcast(ss.str().c_str(),ss.str().length(), uWS::OpCode::TEXT);
  }
  
}



int main()
{
  uWS::Hub hub;

  Data d { hub };
  hub.onMessage(d);
  if (hub.listen(3000)) {
    std::thread th(async, &hub);
    hub.run();
  }
}


  // Som lambda - optional!
  /*
    hub.onMessage([](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
    std::cout << "Data: " << std::string_view(message, length) << std::endl;
    ws->send(message, length, opCode);
    });
  */
