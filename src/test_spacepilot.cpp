#include"3DConnexionBase.hpp"
#include"3DSpacePilotPro.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

using namespace controldev;

int main(int argc, char**argv) {
  
  if(argc != 1) {
    exit(0);
  }
  
//ConnexionBase *c = new  ConnexionBase();
  SpacePilotPro *c = new SpacePilotPro();
  c->init();
  AnalogValues a1;
  ControlButtons b1;
  
  while(1) {
    c->getValue(b1,a1);
    printf("Analog Values: (%f,%f,%f),(%f,%f,%f), \n",a1.tx,a1.ty,a1.tz,a1.rx,a1.ry);
    printf("Button Values: (%d,%d,%d),(%d,%d,%d), \n",b1.button1, b1.button2, b1.button3, b1.button4, b1.button5, b1.button6);
    usleep(40000);
  }
}