//life.h
#ifndef _life_h_
#define _life_h_

#include <fstream>
#include <unistd.h>
//#include <cstdio> potrzebny wczesniej do scanf
#include <iostream>

class life{

private:
    enum{L=22,H=80};
    bool **cell;
    bool flag;
    char fname[20];


public:
    life();
    ~life();
    void proceed();
    void generation();
    int count(int i,int j);
    void show();
    void set();
    void prepared();



};
#endif // _life_h_
