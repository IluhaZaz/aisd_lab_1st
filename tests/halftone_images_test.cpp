#include <halftone_images.h>
#include <iostream>
#include <cstdlib>
using namespace std;
using namespace halftone_images;

int main() {
	setlocale(LC_ALL, "Russian");
	
	HalftoneImage<bool> h(2, 3, 0);
	return 0;
}
