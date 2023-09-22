#pragma once
namespace halftone_images {
	template <typename T>
	class HalftoneImage {
	private:
		T** _matrix;
	public:
		HalftoneImage(int m, int n, bool random);
		T* operator()(int i, int j) const;
		HalftoneImage operator * (const HalftoneImage& other);
		HalftoneImage operator * (const T& other);
		HalftoneImage operator ! ();
		float count_fill_factor() {};

	};
	template <typename T>
	T random(int T_min_value, int T_max_value);



}