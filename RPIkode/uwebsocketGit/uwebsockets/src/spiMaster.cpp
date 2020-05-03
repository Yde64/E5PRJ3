#include "spiMaster.h"

spiMaster::spiMaster(int data)
{
  data_ = data;
}

void spiMaster::listen()
{
  int spi, gpio, log, sek, ms;
  int buf[20];
  char buf2[40];

  while(1)
  {
    
    gpio = open("/dev/mygpio22", O_RDWR);
    read(gpio, buf, 2);

    cout << "mygpio[0]: " << buf[0] << endl;

    if (buf[0] == 1)
    {
      spi = open("/dev/SPI_0", O_RDONLY);
      read(spi, buf, 3);
      close(spi);

      sek = buf[0];
      ms = buf[1];


      log = open("/www/pages/log.txt", O_WRONLY | O_APPEND | O_CREAT);
      sprintf(buf2, "%i:  Chug tid: %is,%i0s\n", count_, sek, ms);
      dprintf(log, buf2, strlen(buf2)); 
      count_++;
      close(log);


      write(gpio, "0", 2);
      
    }
  close(gpio);
  sleep(1);

  }
}

int spiMaster::getdata()
{
return 0;
}
void spiMaster::setcount(int count)
{
  count_ = count;
}