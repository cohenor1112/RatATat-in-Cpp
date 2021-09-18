#include "RatATat.h"
#include <string>
#include <time.h>
#include <iostream>
using namespace std;

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif 

void test()
{
	srand(time(NULL));
	RatATat rat;
	rat.add_player("Human");
	rat.play();
}

int main()
{
	test();
	cout << "leaks: " << _CrtDumpMemoryLeaks();
	return 0;
}


