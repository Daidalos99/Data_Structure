#include "MyDoubleVector.h"
#include <iostream>
#include <algorithm> //for std::copy
#include <cassert> // for assert
#include <cstdlib> // for size_t

MyDoubleVector::MyDoubleVector(size_t init_capacity)
// Postcondition: dynamically allocate memory of size 'init_capacity', and initial size = 0
{
	data = new value_type[init_capacity];
	capacity = init_capacity;
	size = 0;
}

MyDoubleVector::MyDoubleVector(const MyDoubleVector& v)
// Postcondition: dynamically allocate memory new memory and perform deep copy
{
	data = new value_type[v.Capacity()];
	capacity = v.Capacity();
	size = v.size;
	std::copy(v.data, v.data + capacity, data);
}

MyDoubleVector::~MyDoubleVector()
// Precondition: object should exist
// Postcondition: free the memory of the object
{
	delete [] data;
}

MyDoubleVector& MyDoubleVector::operator=(const MyDoubleVector& v)
// Precondition: allocated memory should exist
// Postcondition: conduct deep copy
{
	if (this == &v) return *this;
	if (capacity != v.capacity) 
	{
		delete[] data;
		data = new value_type[v.capacity];
		capacity = v.capacity;
	}
	size = v.size;
	std::copy(v.data, v.data + capacity, data);
	return *this;
}

void MyDoubleVector::operator+=(const MyDoubleVector& v)
// Postcondition: add all the elements of parameter vector to object vector
{
	if (size + v.size > capacity) reserve(size + v.size);
	std::copy(v.data, v.data + v.size, data + size);
	size += v.size;
}

double MyDoubleVector::operator[] (size_t idx)
// Precondition: idx < size
// Postcondition: return idx_th element
{
	assert(idx < size);
	return data[idx];
}

MyDoubleVector MyDoubleVector::operator+(const MyDoubleVector& v)
// Precondition: size == v.size
// Postcondition: return the vector sum of 2 operand vectors
{
	assert(size == v.size);
	MyDoubleVector sum(v.capacity);
	sum.size = size;
	for (size_t i = 0; i < v.size; i++)
	{
		sum.data[i] = data[i] + v.data[i];
	}
	return sum;
}

MyDoubleVector MyDoubleVector::operator-(const MyDoubleVector& v)
// Precondition: size == v.size
// Postcondition: return the vector difference of 2 operand vectors
{
	assert(size == v.size);
	MyDoubleVector dif(v.capacity);
	dif.size = size;
	for (size_t i = 0; i < v.size; i++)
	{
		dif.data[i] = data[i] - v.data[i];
	}
	return dif;
}

double MyDoubleVector::operator*(const MyDoubleVector& v)
// Precondition: size == v.size
// Postcondition:  return the dot product value of 2 operand vectors
{
	assert(size == v.size);
	double sum = 0;
	for (size_t i = 0; i < v.size; i++)
	{
		sum += data[i] * v.data[i];
	}
	return sum;
}

MyDoubleVector& MyDoubleVector::operator-()
// Postcondition: change signs of all the vector elements
{
	for(size_t i = 0; i < size; i++)
	{
		data[i] = -data[i];
	}
	return *this;
}

bool MyDoubleVector::operator==(const MyDoubleVector& v)
// Precondition: (*data == *v.data && size == v.size)
// Postcondition: returns wether or not 2 vectors are same
{	
	if (*data == *v.data && size == v.size)
	{
		std::cout << "same!" << std::endl;

		return true;
	}
	else
	{
		std::cout << "not same!" << std::endl;
		return false;
	}
}

MyDoubleVector& MyDoubleVector::operator()(value_type n)
// Postcondition: initialize all elements of object vector to n
{
	for (size_t i = 0; i < size; i++)
	{
		data[i] = n;
	}
	return *this;
}

void MyDoubleVector::pop_back()
// Precondition: size >= 1
// Postcondition: eliminate the last element of the object vector
{
	assert(size >= 1);
	data[--size] = NULL;
}

void MyDoubleVector::push_back(value_type x)
// Postcondition: insert x to the last of the object vector
{
	if(size < capacity) data[size++] = x;
	else 
	{
		reserve(size + 1);
		data[size++] = x;
	}
}

size_t MyDoubleVector::Capacity() const
// Postcondition: return vector capacity
{
	return capacity;
}

size_t MyDoubleVector::Size() const
// Postcondition: return # of vector element
{
	return size;
}

void MyDoubleVector::reserve(size_t new_capacity)
// Precondition: new_capacity >= 0
// Postcondition: request the memory capacity to hold n elements
{
	assert(new_capacity >= 0);
	value_type *larger_vector;
	if(new_capacity == capacity) return;
	if(new_capacity < size) new_capacity = size;

	larger_vector = new value_type[new_capacity];
	std::copy(data, data + size, larger_vector);
	delete[] data;
	data = larger_vector;
	capacity = new_capacity;
}

bool MyDoubleVector::empty() const
// Postcondition: check whether the object vector is empty or not
{
	if (size == 0) 
	{
		std::cout << "Vector is empty!" << std::endl;
		return true;
	}
	else 
	{
		std::cout << "Vector is not empty!" << std::endl;
		return false;
	}
}

void MyDoubleVector::clear()
// Postcondition: clear all the elements of the object vector
{
	for (size_t i = 0; i < size; i++)
	{
		data[i] = NULL;
	}
	size = 0;	
}