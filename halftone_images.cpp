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
				else if (first._matrix[i][j] * other._matrix[i][j] < std::numeric_limits<T>::min())
					h._matrix[i][j] = std::numeric_limits<T>::min();
				else
					h._matrix[i][j] = first._matrix[i][j] * other._matrix[i][j];
			}
		}
		return h;
	}

	friend HalftoneImage<T> operator+(const HalftoneImage<T>& first, const HalftoneImage<T>& other)
	{
		if (first._m != other._m || first._n != other._n)
			throw runtime_error("In operator + : different size");
		HalftoneImage<T> h(first._m, first._n, false);
		for (int i = 0; i < first._m; i++)
		{
			for (int j = 0; j < first._n; j++)
			{
				if (first._matrix[i][j] + other._matrix[i][j] > std::numeric_limits<T>::max())
					h._matrix[i][j] = std::numeric_limits<T>::max();
				else if(first._matrix[i][j] + other._matrix[i][j] <  std::numeric_limits<T>::min())
					h._matrix[i][j] = std::numeric_limits<T>::min();
				else
					h._matrix[i][j] = first._matrix[i][j] + other._matrix[i][j];
			}
		}
		return h;
	}

	friend HalftoneImage<T> operator-(const HalftoneImage<T>& first, const HalftoneImage<T>& other)
	{
		if (first._m != other._m || first._n != other._n)
			throw runtime_error("In operator - : different size");
		HalftoneImage<T> h(first._m, first._n, false);
		for (int i = 0; i < first._m; i++)
		{
			for (int j = 0; j < first._n; j++)
			{
				if (first._matrix[i][j] - other._matrix[i][j] > std::numeric_limits<T>::max())
					h._matrix[i][j] = std::numeric_limits<T>::max();
				else if (first._matrix[i][j] - other._matrix[i][j] < std::numeric_limits<T>::min())
					h._matrix[i][j] = std::numeric_limits<T>::min();
				else
					h._matrix[i][j] = first._matrix[i][j] - other._matrix[i][j];
			}
		}
		return h;
	}

	friend HalftoneImage operator * (const HalftoneImage& first, T constant)
	{
		HalftoneImage<T> h(first._m, first._n, false);
		for (int i = 0; i < first._m; i++)
		{
			for (int j = 0; j < first._n; j++)
			{
				if (first._matrix[i][j] * constant > std::numeric_limits<T>::max())
					h._matrix[i][j] = std::numeric_limits<T>::max();
				else if (first._matrix[i][j] * constant < std::numeric_limits<T>::min())
					h._matrix[i][j] = std::numeric_limits<T>::min();
				else
					h._matrix[i][j] = first._matrix[i][j] * constant;
			}
		}
		return h;
	}

	friend HalftoneImage<T> operator+(const HalftoneImage<T>& first, T constant)
	{
		HalftoneImage<T> h(first._m, first._n, false);
		for (int i = 0; i < first._m; i++)
		{
			for (int j = 0; j < first._n; j++)
			{
				if (first._matrix[i][j] + constant > std::numeric_limits<T>::max())
					h._matrix[i][j] = std::numeric_limits<T>::max();
				else if (first._matrix[i][j] + constant < std::numeric_limits<T>::min())
					h._matrix[i][j] = std::numeric_limits<T>::min();
				else
					h._matrix[i][j] = first._matrix[i][j] + constant;
			}
		}
		return h;
	}

	friend HalftoneImage<T> operator-(const HalftoneImage<T>& first, T constant)
	{
		HalftoneImage<T> h(first._m, first._n, false);
		for (int i = 0; i < first._m; i++)
		{
			for (int j = 0; j < first._n; j++)
			{
				if (first._matrix[i][j] - constant > std::numeric_limits<T>::max())
					h._matrix[i][j] = std::numeric_limits<T>::max();
				else if (first._matrix[i][j] - constant < std::numeric_limits<T>::min())
					h._matrix[i][j] = std::numeric_limits<T>::min();
				else
					h._matrix[i][j] = first._matrix[i][j] - constant;
			}
		}
		return h;
	}

	friend bool operator!=(HalftoneImage<T> a, HalftoneImage<T> b)
	{
		return !(a == b);
	}
	
	void swap(HalftoneImage& rhs) {
		for (int i = 0; i < _m; i++)
		{
			std::swap(_matrix[i], rhs._matrix[i]);
		}
	}
	
	
	HalftoneImage& operator=(HalftoneImage rhs)
	{
		if (_m != rhs._m || _n != rhs._n)
			throw runtime_error("In operator = : different size");
		rhs.swap(*this);
		return *this;
	}
	
	~HalftoneImage()
	{
		for (int i = 0; i < _m; i++)
		{
			delete[] _matrix[i];
		}
		delete[] _matrix;
	}
	
	HalftoneImage(const HalftoneImage& other)
	{
		_m = other._m;
		_n = other._n;
		_matrix = new T * [_m];
		for (int i = 0; i < _m; i++)
		{
			_matrix[i] = new T[_n];
			for (int j = 0; j < _n; j++) 
			{
				_matrix[i][j] = other._matrix[i][j];
			}
		}
	}
	
	float count_fill_factor()
	{
		double cff = 0;
		float denominator = _m * _n * std::numeric_limits<T>::max();
		for (int i = 0; i < _m; i++)
		{
			for (int j = 0; j < _n; j++)
			{
				cff += _matrix[i][j] / denominator;
			}
		}
		return cff;
	};

	int get_n()
	{
		return _n;
	}

	int get_m()
	{
		return _m;
	}
};

template <typename T>
T invert(T value) 
{
	return -1 * value;
}
template<>
bool invert(bool value) 
{
	if (value == 1)
		return 0;
	else
		return 1;

}
template<>
char invert(char value)
{
	return 'a' + ('z' - value);
}

class Point {
public:
	float _x;
	float _y;
	Point(float x, float y)
	{
		_x = x;
		_y = y;
	}
};

float get_lenear_func_value_at_x(Point a, Point b, float x)
{
	float k = (a._y - b._y) * 1.0 / (a._x - b._x);
	float c = a._y - k * a._x;
	return k * x + c;
}

template<typename T>
void invert_values_above_line(HalftoneImage<T>& h, Point a, Point b)
{
	for (int i = 0; i < h.get_m(); i++)
	{
		for (int j = 0; j < h.get_n(); j++)
		{
			if (h.get_m() - i - 1 >= get_lenear_func_value_at_x(a, b, j) && h.get_m() - i - 1 >= get_lenear_func_value_at_x(a, b, j + 1))
			{
				h(i, j) = invert(h(i,j));
			}
		}
	}
}

	template <typename T>
	HalftoneImage<T> operator !(HalftoneImage<T> f)
	{
		HalftoneImage<T> h(f.get_m(), f.get_n(), false);
		for (int i = 0; i < f.get_m(); i++)
		{
			for (int j = 0; j < f.get_n(); j++)
			{
				h(i, j) = -1 * f(i, j);
			}
		}
		return h;
	}

	template<>
	HalftoneImage<bool> operator !(HalftoneImage<bool> f)
	{
		HalftoneImage<bool> h(f.get_m(), f.get_n(), false);
		for (int i = 0; i < f.get_m(); i++)
		{
			for (int j = 0; j < f.get_n(); j++)
			{
				if (f(i, j) == 1)
					h(i, j) = 0;
				else
					h(i, j) = 1;
			}
		}
		return h;
	}

	template<>
	HalftoneImage<char> operator !(HalftoneImage<char> f)
	{
		HalftoneImage<char> h(f.get_m(), f.get_n(), false);
		for (int i = 0; i < f.get_m(); i++)
		{
			for (int j = 0; j < f.get_n(); j++)
			{
				h(i, j) = 'a' + ('z' - f(i, j));
			}
		}
		return h;
	}

	template <typename T>
	bool operator==(HalftoneImage<T> a, HalftoneImage<T> b)
	{
		if (a.get_m() != b.get_m() || a.get_n() != b.get_n())
			return false;
		for (int i = 0; i < a.get_m(); i++)
		{
			for (int j = 0; j < a.get_n(); j++)
			{
				if (a(i, j) != b(i, j))
				{
					return false;
				}
			}
		}
		return true;
	}

	template <>
	bool operator==(HalftoneImage<float> a, HalftoneImage<float> b)
	{
		if (a.get_m() != b.get_m() || a.get_n() != b.get_n())
			return false;
		for (int i = 0; i < a.get_m(); i++)
		{
			for (int j = 0; j < a.get_n(); j++)
			{
				if (a(i, j) - b(i, j) > std::numeric_limits<float>::min())
				{
					return false;
				}
			}
		}
		return true;
	}
