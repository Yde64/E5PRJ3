#include <string>
#include <stdio.h>
#include <iostream>
#include </mnt/c/Users/cring/Documents/GitHub/E5PRJ3/RPIkode/uwebsocketGit/uwebsockets/src/uWS.h>

using namespace std;

class spiMaster
{
public:
spiMaster(int data = 0);
void listen();
int getdata();

private:
int data_;

};