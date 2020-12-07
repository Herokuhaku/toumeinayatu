#pragma once

template<class T>
class Vector2Temple
{
public:
	Vector2Temple();
	Vector2Temple(T x,T y);
	~Vector2Temple();
	T x;
	T y;
	// ������Z�q
	Vector2Temple& operator = (const Vector2Temple& vec);
	// �Y�������Z�q
	T& operator [] (int no);

	// �P�����Z�q
	Vector2Temple& operator += (const Vector2Temple& vec);
	Vector2Temple& operator -= (const Vector2Temple& vec);
	Vector2Temple& operator *= (int k);
	Vector2Temple& operator /= (int k);
	Vector2Temple operator  +  ()const;
	Vector2Temple operator  -  ()const;

	Vector2Temple& operator += (int k);
	// ��r���Z�q
	bool operator == (const Vector2Temple& vec) const;
	bool operator != (const Vector2Temple& vec) const;
	bool operator <= (const Vector2Temple& vec) const;
	bool operator <  (const Vector2Temple& vec) const;

	bool operator >= (const Vector2Temple& vec) const;
	bool operator >  (const Vector2Temple& vec) const;
};

// Vector2Temple + T
template<class T>
Vector2Temple<T> operator+(const Vector2Temple<T>& vec,T num);
// Vector2Temple - T
template<class T>
Vector2Temple<T> operator-(const Vector2Temple<T>& vec, T num);
// Vector2Temple * T
template<class T>
Vector2Temple<T> operator*(const Vector2Temple<T>& vec, T num);
// T * Vector2Temple
template<class T>
Vector2Temple<T> operator*(T num, const Vector2Temple<T>& vec);
// Vector2Temple / T
template<class T>
Vector2Temple<T> operator/(const Vector2Temple<T>& vec, T num);
// Vector2Temple % T
template<class T>
Vector2Temple<T> operator%(const Vector2Temple<T>& vec, T num);
// Vector2Temple + Vector2Temple
template<class T>
Vector2Temple<T> operator+(const Vector2Temple<T>& vec1,const Vector2Temple<T>&vec2);
// Vector2Temple - Vector2Temple
template<class T>
Vector2Temple<T> operator-(const Vector2Temple<T>& vec1,const Vector2Temple<T>&vec2);

using Vector2 = Vector2Temple<int>;
using Vector2f = Vector2Temple<float>;
using Vector2d = Vector2Temple<double>;

#include "./dateil/Vector2.h"