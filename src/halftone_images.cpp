#include <halftone_images.h>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace halftone_images;


template<typename T>
T halftone_images::random(int T_min_value, int T_max_value)
{
	return srand();
}

template<typename T>
inline halftone_images::HalftoneImage<T>::HalftoneImage(int m, int n, bool random)
{
	_matrix = new T* (m);
	for (int i = 0; i < m; i++) 
	{
		*_matrix = new T;
		if (random == true) {
			**_matrix =  
		}
		else {

		}
		_matrix++;
	}
}