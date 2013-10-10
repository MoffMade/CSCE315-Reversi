/* 
 * File:   main.cpp
 * Author: Cory
 *
 * Created on October 8, 2013, 2:33 PM
 */

#include "stdhf.h"
#include "gameServer.h"
#include "gameClient.h"
using namespace std; 
/*
 * 
 */
int main(int argc, char** argv) {
    serverEngine e;
    e.runGame();
    return 0;
}

