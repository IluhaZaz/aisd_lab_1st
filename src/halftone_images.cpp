#include <halftone_images.h>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <limits>
#include <iostream>
using namespace halftone_images;
using namespace std;


template<typename T>
inline halftone_images::HalftoneImage<T>::HalftoneImage(int m, int n, bool random)
{
	_matrix = new T* (m);
	for (int i = 0; i < m; i++) 
	{
		*_matrix = new T;
		if (random == true) {
			**_matrix = halftone_images::random();
		}
		else {
			**_matrix = 0;
		}
		_matrix++;
	}
}