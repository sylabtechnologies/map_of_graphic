// THEMAP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "interval_map.h"
using namespace std;

template<class K, class V>
void testtest()
{
}

int main()
{

	interval_map<int, char> mymap('Z');
	mymap.assign(0, 4, 'A');
	mymap.assign(3, 6, 'B');
	mymap.assign(5, 100, 'B');
	mymap.assign(1, 2, 'X');

	int the_range = 100;
	/*
	srand(15235325);
	vector<int> test_a, test_b;

	auto gen = [the_range]()->int {return (rand() * the_range) / RAND_MAX; };

	for (int i = 0; i < 100;i++)
	{
		int temp = gen();
		test_a.push_back(temp);
	}

	the_range = 20;
	for (int i = 0; i < 100;i++)
	{
		int temp = test_a[i];
		temp += gen();
		test_b.push_back(temp);
	}

	// fill as 20 = 0
	// 0  = 20
	// 31 = 51
	// 49 = 69
	vector<char> filler(300, 'Z');
	vector<char> tester(300, '?');
	interval_map<int, char> mymap('Z');

	*/


	/*
	auto indx = [](int i)->int { return i + 20; };

	the_range = 26;
	for (int i = 0; i < 100;i++)
	{
		if (test_a[i] == test_b[i]) continue;

		char tchar = 'A' + gen();
		mymap.assign(test_a[i], test_b[i], tchar);

		for (int j = indx(test_a[i]); j < indx(test_b[i]); j++)
			filler[j] = tchar;

		tester = mymap.fill_it();

		if (filler != tester)
		{
			cout << "not equal" << endl;
			break;
		}

		*/


		/*
		for (int j = 0; j < 300; j++)
		{
			if (filler[j] != tester[j])
			{
				cout << "not equal" << endl;
				break;
			}
		}
		*/

		// cout << i << endl;
	    // }

    return 0;
}

