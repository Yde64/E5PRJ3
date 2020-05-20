#include "spiMaster.h"
#include <math.h>

spiMaster::spiMaster(int data)
{
  data_ = data;
}

void spiMaster::listen()
{
  int spi, gpio, log, sek, ms, times, count = 0;
  int buf[20];
  char buf2[200];
  char buf3[200];
  char buf4[200];

  while(1)
  {
    
    gpio = open("/dev/mygpio22", O_RDWR);
    read(gpio, buf3, 2);

    cout << "mygpio[0]: " << buf3[0] << endl;

    if (buf3[0] == 1)
    {
      spi = open("/dev/SPI_0", O_RDONLY);
      sleep(0.1);
      read(spi, buf, 3);
      close(spi);

      sek = buf[0];
      ms = buf[1];

      cout << "sek: " << sek << endl;
      cout << "ms: " << ms << endl;

      times = open("/www/pages/count.txt", O_RDWR | O_CREAT);
      read(times, buf4, 4);

      cout << "buf4 start: " << buf4 << endl;


      log = open("/www/pages/log.txt", O_WRONLY | O_APPEND | O_CREAT);
      sprintf(buf2, "%s: Chug tid: %i:%is\n", buf4, sek, ms);
      dprintf(log, buf2, strlen(buf2)); 
      close(log);

      for(int i = 0; i < 4; i++)
      {
        if((buf4[i] >= '0') && (buf4[i] <= '9'))
        {
          count = (buf4[i] - '0') * pow(10, -i);
        }
      }
      cout << "count: " << count << endl;
      count++;
      cout << "count++: " << count << endl;

      sprintf(buf4, "%i", count);

      cout << "buf4: " << buf4 << endl;

      write(times, buf4, 1);
      close(times);


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