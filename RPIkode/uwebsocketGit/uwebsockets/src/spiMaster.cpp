#include "spiMaster.h"

spiMaster::spiMaster(int data)
{
  data_ = data;
}

void spiMaster::listen()
{
  while(1)
  {
      sleep(1);
      cout << "hej ? morten lugter" << endl;
      cout << "hej ? morten er meget dum" << endl;
      cout << "hej ? morten er grim" << endl;
      cout << "hej ? morten er lort i hovedet" << endl;
      cout << "hej ? morten er en kæmpe bøsse " << endl;
  }
}

int spiMaster::getdata()
{
return 0;
}