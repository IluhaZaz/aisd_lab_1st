#pragma once
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <limits>
#include <iostream>


using namespace std;

template<typename T>
std::uniform_int_distribution<T> getDice(std::true_type)
{
	return std::uniform_int_distribution<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

template<typename T>
std::uniform_real_distribution<T> getDice(std::false_type)
{
	return std::uniform_real_distribution<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

template<typename T>
T random()
{
	std::random_device randomDevice;
	std::mt19937_64 generator(randomDevice());
	auto dice = getDice<T>(std::integral_constant<bool, std::numeric_limits<T>::is_integer>());
	return dice(generator);
}

template<>
char random<char>()
{
	std::random_device rand;
	std::mt19937 gen(rand());
	std::uniform_int_distribution <> distr('a', 'z');
	return (char)distr(gen);
}

template<>
bool random<bool>()
{
	std::random_device rand;
	std::mt19937 gen(rand());
	std::uniform_int_distribution <> distr(0, 1);
	return distr(gen);
}

template <typename T>
class HalftoneImage {
private:
	T** _matrix;
	int _m;
	int _n;
public:

	HalftoneImage(int m, int n, T* data)
	{
		if (m <= 0 || n <= 0)
			throw runtime_error("In HalftoneImage(int m, int n, bool rand) : wrong size");
		_m = m;
		_n = n;
		_matrix = new T * [m];
		for (int i = 0; i < m; i++)
		{
			_matrix[i] = new T[n];
			for (int j = 0; j < n; j++) {
				_matrix[i][j] = data[i * m + j];
			}
		}
	}

	HalftoneImage(int m, int n, bool rand)
	{
		if (m <= 0 || n <= 0)
			throw runtime_error("In HalftoneImage(int m, int n, bool rand) : wrong size");
		_m = m;
		_n = n;
		_matrix = new T* [m];
		for (int i = 0; i < m; i++)
		{
			_matrix[i] = new T[n];
			for (int j = 0; j < n; j++) {
				if (rand == true) {
					_matrix[i][j] = random<T>();
				}
				else {
					_matrix[i][j] = 0;
				}
			}
		}
	}
	
	HalftoneImage(HalftoneImage& other)
	{

	}
	
	friend std::ostream& operator<< (std::ostream& out, const HalftoneImage<T>& h)
	{
		for (int i = 0; i < h._m; i++)
		{ 
			for (int j = 0; j < h._n; j++)
			{
				std::cout << h._matrix[i][j] << " ";
			}
			cout << endl;
		}
			;
		return out;
	}

	T& operator()(int i, int j) const 
	{
		return _matrix[i][j];
	}
	
	friend HalftoneImage operator * (const HalftoneImage& first, const HalftoneImage& other)
	{
		if (first._m != other._m || first._n != other._n)
			throw runtime_error("In operator * : different size");
		HalftoneImage<T> h(first._m, first._n, false);
		for (int i = 0; i < first._m; i++)
		{
			for (int j = 0; j < first._n; j++)
			{
				if (first._matrix[i][j] * other._matrix[i][j] > std::numeric_limits<T>::max())
					h._matrix[i][j] = std::numeric_limits<T>::max();
				else
					h._matrix[i][j] = first._matrix[i][j] * other._matrix[i][j];
			}
		}
		return h;
	}

	friend HalftoneImage<T> operator+(const HalftoneImage<T>& first, const HalftoneImage<T>& other)
	{
		if (first._m != other._m || first._n != other._n)
			throw runtime_error("In operator * : different size");
		HalftoneImage<T> h(first._m, first._n, false);
		for (int i = 0; i < first._m; i++)
		{
			for (int j = 0; j < first._n; j++)
			{
				if (first._matrix[i][j] + other._matrix[i][j] > std::numeric_limits<T>::max())
					h._matrix[i][j] = std::numeric_limits<T>::max();
				else
					h._matrix[i][j] = first._matrix[i][j] + other._matrix[i][j];
			}
		}
		return h;
	}

	friend bool operator==(HalftoneImage<T> a, HalftoneImage<T> b)
	{
		if (a._m != b._m || a._n != b._n)
			return false;
		for (int i = 0; i < a._m; i++)
		{
			for (int j = 0; j < a._n; j++)
				if (a._matrix[i][j] != b._matrix[i][j])
					return false;
		}
		return true;
	}

	friend bool operator!=(HalftoneImage<T> a, HalftoneImage<T> b)
	{
		return !(a == b);
	}
	
	HalftoneImage operator ! ();

	float count_fill_factor() {};

	void swap(HalftoneImage& rhs) {
		for (int i = 0; i < _m; i++)
		{
			std::swap(_matrix[i], rhs._matrix[i]);
		}
		std::swap(this->_matrix, rhs._matrix);
	}

	HalftoneImage& operator=(HalftoneImage rhs)
	{
		if(_m != rhs._m || _n != rhs._n)
			throw runtime_error("In operator = : different size");
		rhs.swap(*this);
		return *this;
	}

	~HalftoneImage()
	{
		for (int i = 0; i < _m; i++)
		{
			delete _matrix[i];
		}
		delete[] _matrix;
	}
	
};



