#include <iostream>
#include <string>
#include </mnt/c/Users/cring/Documents/GitHub/E5PRJ3/RPIkode/uwebsocketGit/uwebsockets/src/uWS.h>
#include <thread>
#include <stdio.h>
#include <sstream>
#include </mnt/c/Users/cring/Documents/GitHub/E5PRJ3/RPIkode/uwebsocketGit/uwebsockets/src/spiMasterTest.h>

using namespace std;
spiMasterTest spi1;

struct Data
{
  uWS::Hub &h;
  void operator()(uWS::WebSocket<uWS::SERVER> *ws,
		  char *message, size_t length,
		  uWS::OpCode opCode) {
        message[length] = '\0';
        cout << "test thread" << endl;
        if (strcmp(message, "SLETLOG") == 0)
        {
          remove("/www/pages/log.txt");
          int fd = open("/www/pages/log.txt", O_WRONLY | O_APPEND | O_CREAT);
          close(fd);
          spi1.setcount(1);
          return;


        }
        //std::cout << "Data: " << std::string(message, length) << std::endl;
        //ws->send(message, length, opCode);
  }

};

void async(uWS::Hub* h)
{
  
  for(;;)

  {
    sleep(1);



/*
    std::ostringstream ss;
    ss << "Number of broadcasts hejs#" << counter++;
    
    h->broadcast(ss.str().c_str(),ss.str().length(), uWS::OpCode::TEXT);
*/
  }
}



int main()
{
  uWS::Hub hub;
  cout << "Test main" << endl;
  //int gpio;


  //gpio = open("/dev/mygpio22", O_RDWR);
  //write(gpio, "0", 2);
  //close(gpio);
  
  spi1.setcount(1);
  


  Data d { hub };
  hub.onMessage(d);
  if (hub.listen(3000)) {
    std::thread th(async, &hub);
    std::thread th2 (&spiMasterTest::listen, &spi1);
    cout << "Test main2" << endl;
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