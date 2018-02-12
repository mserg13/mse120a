// STL_20.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>  
#include <random> 
#include <ctime>

#include <vector> 
#include <algorithm> 
#include <iterator>
using namespace std;

void out(const char *s, const vector<int>&v)
{
	cout << s;
	copy(v.begin(), v.end(),
		ostream_iterator<int>(cout, " "));
	cout << endl;
}
int z;
bool cond(int x)
{
	return x <= z;
}
bool greater0(int value)
{
	return value > 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::mt19937 gen(time(0));
	std::uniform_real_distribution<> urd(0, 1);
	//std::cout << log(urd(gen)) << std::endl;
	//std::cout << urd(gen) << std::endl;
	//std::cout << urd(gen) << std::endl;
	//std::cout << urd(gen) << std::endl;

	double lambda = 0.2;  // время прихода
	double tcurr = 0;
	int N = 5; // число рождающихся частиц

	for (int k = 1; k <= N; k++)
		std::cout << -log(urd(gen)) / lambda << std::endl;
	vector<int> v;
	vector<int>::iterator new_end;
	v.push_back(1); v.push_back(4); v.push_back(1);
	v.push_back(3); v.push_back(1); v.push_back(2);

	out("Initial sequence v:\n", v);
	z = 1;
	new_end = remove_if(v.begin(), v.end(), cond);
	v.erase(new_end, v.end());
	out("After erasing all elements <= 2:\n", v);

	vector<int>::iterator::difference_type result1;
	result1 = count_if(v.begin(), v.end(), greater0);
	cout << "The number of elements in v greater than 0 is: "
		<< result1 << "." << endl;

	//	count_if(v.begin(), v.end(), greater0);
	
	sort(v.begin(), v.end());
	out("After sorting:\n", v);
	vector<int>::iterator i;
	
	//for (i = v.begin(); i != v.end(); ++i)
	/*i = v.begin();
	do
	++i;
	while (p <= *i && i != v.end());*/
	int p = 5;
	i = v.begin();
	v.push_back(100);
	cout << *i << endl;
	while (p > *i && i != v.end())
	{
		if (i == v.end()) { v.push_back(p); }
		else ++i;
		cout << *i << endl;
	}
	vector<int>v1;
	v1.push_back(p);
	copy(v1.begin(), v1.end(), inserter(v, i));

	out("After inserting  element:\n", v);
	v1.pop_back();
	p = 13;
	i = v.begin();
	
	cout << *i << endl;
	while (p > *i && i != v.end())
	{
		if (i == v.end()) { v.push_back(p); }
		else ++i;
		cout << *i << endl;
	}
	
	v1.push_back(p);
	copy(v1.begin(), v1.end(), inserter(v, i));

	out("After inserting  element:\n", v);

	z = 9;
	new_end = remove_if(v.begin(), v.end(), cond);
	v.erase(new_end, v.end());
	out("After erasing all elements <= 2:\n", v);


	result1 = count_if(v.begin(), v.end(), greater0);
	cout << "The number of elements in v greater than 0 is: "
		<< result1 << "." << endl;


	getchar();
	return 0;
}

