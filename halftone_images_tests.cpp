#include "halftone_images.cpp"

int main() {
	HalftoneImage<char> h(3, 3, false);
	h(0, 2) = 'a';
	cout << h;
		return 0;
}