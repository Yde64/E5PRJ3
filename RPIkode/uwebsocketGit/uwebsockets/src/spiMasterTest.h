#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include </mnt/c/Users/cring/Documents/GitHub/E5PRJ3/RPIkode/uwebsocketGit/uwebsockets/src/uWS.h>

using namespace std;

class spiMasterTest
{
public:
spiMaster(int data = 0);
void listen();
int getdata();
void setcount(int count);

private:
int data_;
int count_;
};