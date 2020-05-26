#include "spiMasterTest.h"
#include <math.h>

spiMasterTest::spiMasterTest(int data)
{
  data_ = data;
}

void spiMasterTest::listen()
{
  int spi, gpio, log, sek, ms;
  int buf[20];
  char buf2[200];
  char buf3[200];
  cout << "test" << endl;

  

  while(1)
  {
    
    sleep(1);
    cout << "test" << endl;

    buf3[0] = 1;

    //gpio = open("/dev/mygpio22", O_RDWR);
    //read(gpio, buf3, 2);

    //cout << "mygpio[0]: " << buf3[0] << endl;

    if (buf3[0] == 1)
    {
      //Starter SPI kommunikation
      //spi = open("/dev/SPI_0", O_RDONLY);
      //sleep(0.1);
      //read(spi, buf, 3);
      //close(spi);

        sek = 101;
        ms = 5;

     //cout << "sek: " << sek << endl; //DEBUG
     //cout << "ms: " << ms << endl; //DEBUG

        //Tider skrives til log
        log = open("/www/pages/log.txt", O_WRONLY | O_APPEND | O_CREAT);
        sprintf(buf2, "%i: Chug tid: %i:%is\n", count_, sek, ms);
        dprintf(log, buf2, strlen(buf2)); 
        close(log);

      //Tid counter tælles op
        count_++;
      
      //Interrupt nulstilles
      //write(gpio, "0", 2);

        buf3[0] = 0;
      
    }
  

  sleep(1);

  }
}

int spiMasterTest::getdata()
{
return 0;
}

void spiMasterTest::setcount(int count)
{
  cout << "test23" << endl;
  count_ = count;
}