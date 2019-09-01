#pragma once

#ifndef DEFINES_H
#define DEFINES_H

#include <iostream>
#include <WS2tcpip.h>
#include <vector> 
#include <string>
#include <io.h>
#include <map>

#include <fcntl.h>      /* Needed only for _O_RDWR definition */
#include <stdlib.h>
#include <stdio.h>
#include <share.h>

//Get random numbers every run
#include <cstdlib>
#include <ctime>

#include <algorithm> // fill function

#include "Card.h" //Card class

#pragma comment (lib, "ws2_32.lib")

#define MAX_CARD_NRS 51
#define BUF_SIZE_SENT 31
#define BUF_SIZE_RECEIVE 31

#endif