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

      cout << "Spi buffer[0]: " << buf[0] << endl;
      cout << "Spi buffer[1]: " << buf[1] << endl;
      cout << "Spi buffer[3]: " << buf[3] << endl;
      cout << "Spi buffer[4]: " << buf[4] << endl;
      cout << "Spi buffer[5]: " << buf[5] << endl;
      cout << "Spi buffer[6]: " << 128 << endl;

      sek = buf[0] >> 8;
      ms = buf[0] & 255;
      

      log = open("/www/pages/log.txt", O_WRONLY | O_APPEND | O_CREAT);
      sprintf(buf2, "Chug tid: %i:%i\n", sek, ms);
      dprintf(log, buf2, strlen(buf2)); 

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