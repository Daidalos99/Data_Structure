// Make a class similar to vector<double> in STL.
// Write a test program that all the members of class work correctly.

#include <iostream>
#include "MyDoubleVector.h"
#include <algorithm>

using namespace std;

int main() 
{
	// Size(), Capacity(), operator[]
	// constructor
	MyDoubleVector a;
	cout << "examine constructor" << endl;
	cout << "a.capacity: " << a.Capacity() << "\t\t" << "a.size: " << a.Size() << endl;
	cout << endl;
	
	// push_back
	a.push_back(1);
	a.push_back(3.14);
	cout << "examine push_back" << endl;
	cout << "a.capacity: " << a.Capacity() << "\t\t" << "a.size: " << a.Size() << endl;
	for (size_t i = 0; i < a.Size(); i++)
	{
		cout << "a[" << i << "]: " << a[i] << "\t\t";
	}
	cout << "\n" << endl;

	// copy constructor
	MyDoubleVector b(a);
	cout << "examine copy constructor" << endl;
	cout << "b.capacity: " << b.Capacity() << "\t\t" << "b.size: " << b.Size() << endl;
	for (size_t i = 0; i < b.Size(); i++)
	{
		cout << "b[" << i << "]: " << b[i] << "\t\t";
	}
	cout << "\n" << endl;

	// pop_back
	b.pop_back();
	cout << "examine pop_back" << endl;
	cout << "b.capacity: " << b.Capacity() << "\t\t" << "b.size: " << b.Size() << endl;
	for (size_t i = 0; i < b.Size(); i++)
	{
		cout << "b[" << i << "]: " << b[i] << "\t\t";
	}
	cout << "\n" << endl;

	// operator=
	MyDoubleVector c;
	c = a;
	cout << "examine operator=" << endl;
	cout << "c.capacity: " << c.Capacity() << "\t\t" << "c.size: " << c.Size() << endl;
	for (size_t i = 0; i < c.Size(); i++)
	{
		cout << "c[" << i << "]: " << c[i] << "\t\t";
	}
	cout << "\n" << endl;

	// operator+=
	a += c;
	cout << "examine operator+=" << endl;
	cout << "a.capacity: " << a.Capacity() << "\t\t" << "a.size: " << a.Size() << endl;
	for (size_t i = 0; i < a.Size(); i++)
	{
		cout << "a[" << i << "]: " << a[i] << "\t\t";
	}
	cout << "\n" << endl;
	
	b.push_back(5.3); // b,c의 사이즈를 맞추기 위해 b에 원소 추가

	//operator+
	MyDoubleVector sum;;
	sum = b + c;
	cout << "examine operator+" << endl;
	for (size_t i = 0; i < sum.Size(); i++)
	{
		cout << "sum[" << i << "]: " << sum[i] << "\t\t";
	}
	cout << "\n" << endl;

	//operator-
	MyDoubleVector dif;
	dif = b - c;
	cout << "examine operator-" << endl;
	for (size_t i = 0; i < dif.Size(); i++)
	{
		cout << "dif[" << i << "]: " << dif[i] << "\t\t";
	}
	cout << "\n" << endl;

	//operator*
	double mul = b * c;
	cout << "examine operator*" << endl;
	cout << "dot product value: " << mul << endl;

	//operator-
	a = -a;
	cout << "examine operator-" << endl;
	for (size_t i = 0; i < a.Size(); i++)
	{
		cout << "a[" << i << "]: " << a[i] << "\t\t";
	}
	cout << "\n" << endl;

	//operator==
	cout << "examine operator==" << endl;
	b == a;
	cout << endl;

	//operator()
	a(5);
	cout << "examine operator()" << endl;
	for (size_t i = 0; i < a.Size(); i++)
	{
		cout << "a[" << i << "]: " << a[i] << "\t\t";
	}
	cout << "\n" << endl;

	//reserve
	MyDoubleVector v1;
	cout << "v1.Capacity(): " << v1.Capacity() << endl;
	v1.reserve(105);
	cout << "examine reserve" << endl;
	cout << "v1.Capacity(): " << v1.Capacity() << endl;
	cout << endl;

	//empty()
	cout << "examine empty" << endl;
	v1.empty();
	a.empty();
	cout << endl;
	
	//clear()
	cout << "examine clear" << endl;
	a.clear();
	for (size_t i = 0; i < a.Size(); i++)
	{
		cout << "a[" << i << "]: " << a[i] << "\t\t";
	}
	cout << "a.Size(): " << a.Size() << endl;
	cout << "\n" << endl;

	return 0;
}
