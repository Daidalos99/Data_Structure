#include <iostream>
#include <algorithm>
#include <cstdlib>

class MyDoubleVector {
    typedef double value_type;
private:
    // Member data;
    static const size_t Default_Capacity = 100;
    double* data;
    size_t capacity;
    size_t size;

public:
    // Default function
    MyDoubleVector(size_t init_capacity = Default_Capacity);    // 생성자--
    MyDoubleVector(const MyDoubleVector& v);                    // 복사 생성자--
    ~MyDoubleVector();                                          // 파괴자

    // Operator Overloading 
    MyDoubleVector& operator=(const MyDoubleVector& v);         // =: 깊은 복사--
    void operator+=(const MyDoubleVector& v);                   // +=: 벡터에 매개변수 벡터 원소를 추가--
    double operator[] (size_t idx);                             // []: 요청된 벡터 인덱스값 출력--
    MyDoubleVector operator+(const MyDoubleVector& v);         // +: 벡터합-- 
    MyDoubleVector operator-(const MyDoubleVector& v);         // -: 벡터차--
    double operator*(const MyDoubleVector& v);                  // *: 스칼라곱--
    MyDoubleVector& operator-();                                // -: 원소를 전부 부호바꿈--
    bool operator==(const MyDoubleVector& v);                   // ==: 2개의 벡터의 동일 유무--
    MyDoubleVector& operator()(value_type n);                   // (): 벡터의 원소를 전부 매개변수로 바꿈

    // Member Function
    void pop_back();                                            // 마지막 원소 제거--      
    void push_back(value_type x);                               // 마지막에 원소 추가--
    size_t Capacity() const;                                    // 벡터에 할당된 저장공간 반환--
    size_t Size() const;                                        // 벡터 원소의 개수 반환--
    void reserve(size_t n);                                     // 최소 n개의 원소를 가질 수 있는 저장공간 요청--
    bool empty() const;                                         // 벡터가 비었는지 유무 출력--
    void clear();                                               // 모든 벡터 원소를 제거--
};