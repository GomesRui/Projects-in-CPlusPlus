// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once



#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <exception>

//using namespace std;

using std::cout;
using std::string;
using std::vector;
using std::min;
using std::max;
using std::to_string;
using std::endl;
using std::exception;

__declspec(dllexport) string range_me(vector<int> startingVector, string op);

string range_me(vector<int> startingVector, string op);

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>



// TODO: reference additional headers your program requires here
