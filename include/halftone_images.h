#pragma once
#include <random>
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
		const char* alf = "àáâãäå¸æçèéêëìíîïğñòóôõö÷øùúûüışÿÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		srand(time(NULL));
		return (alf[rand() % 119]);
	}

	template<>
	bool random<bool>()
	{
		srand(time(NULL));
		return rand() % 2;
	}

}