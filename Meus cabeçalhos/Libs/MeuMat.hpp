#pragma once

// Só anotando aqui, pq é algo intereçante

/*
#   if defined(_WIN32) && !defined(_WIN64)
#       define PYLON_32_BUILD
#   elif defined(_WIN32) && defined(_WIN64)
#       define PYLON_64_BUILD
#   else
#       error unsupported wordsize (32/64 platform)
#   endif
*/

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulong_long;



#ifdef _WIN64
typedef unsigned long long* uinptr;
#else
typedef unsigned int* uintptr;
#endif

typedef void* voidptr;	// Escrever "voidptr" é maior do que "void*", mas sei lá kkk

#define QUAD(x) (x*x)
#define CUBO(x) (x*x*x)

#define MEUPI 3.14159265358
#define MEUPIf 3.1415927f

inline namespace MeuMat {

	// § Classes matemáticas

	struct vec2 { float x, y; };

	struct vec3 { float x, y, z; };

	struct vec4 { float x, y, z, w; };

	// § Aritimética

	template <typename ret, typename T>
	// Como eu sou burro e não achei na internet, se usar negativos na base vai retornar '-1' kkk
	// TESTAR
	inline_template ret Pot(T base, int exp)
	{
		bool neg = false;

		// Para casos negativos
		if (base < 0)
			return -1;	// Sei lá como lidar com erros, então retorna '-1' e boa kkk

		if (exp < 0)
		{
			neg = true;
			exp *= -1;	// Espero que funcione
		}

		switch (base)
		{
		case 0:
			return 0;
		case 1:
			return 1;
		}

		switch (exp)
		{
		case 0:
			return 1;
		case 1:
			return base;
		case 2:
			return QUAD(base);
		case 3:
			return CUBO(base);
		}

		T Resultado = base;

		//exp -= 1;

		for (long long i = 1; i < exp; i++)	// i começa em 1 para remover a linha exp -= 1;
			Resultado *= base;

		if (neg)
			return 1 / Resultado;

		return Resultado;
	}

	// Sobrecarga para float, pois não pode ter caso switch para float
	// Como eu sou burro e não achei na internet, se usar negativos vai retornar '-1'
	tipo_função float Pot(float base, int exp)
	{
		// Para casos negativos
		if (base < 0 || exp < 0)
			return -1;	// Sei lá como lidar com erros, então retorna '-1' e boa kkk

		if (exp == 0)
			return 1;
		else if (base == 0)
			return 0;
		else if (base == 1)
			return 1;

		float Resultado = base;

		//exp -= 1;

		for (int i = 1; i < exp; i++)	// i começa em 1 para remover a linha exp -= 1;
			Resultado *= base;

		return Resultado;
	}

	// Sobrecarga para double, pois não pode ter caso switch para double
	// Como eu sou burro e não achei na internet, se usar negativos vai retornar '-1'
	tipo_função double Pot(double base, int exp)
	{
		// Para casos negativos
		if (base < 0 || exp < 0)
			return -1;	// Sei lá como lidar com erros, então retorna '-1' e boa kkk

		if (exp == 0)
			return 1;
		else if (base == 0)
			return 0;
		else if (base == 1)
			return 1;

		double Resultado = base;

		//exp -= 1;

		for (int i = 1; i < exp; i++)	// i começa em 1 para remover a linha exp -= 1;
			Resultado *= base;

		return Resultado;
	}

	tipo_função float RaizQuad(float raiz)
	{
		float precisao = 0.000001f;
		float b = raiz, a = 1;
		while ((b - a) >= precisao) {
			b = (b + a) / 2;
			a = raiz / b;
		}
		return b;
	}


	// § Trigonometria

	// Calcula a hipotenusa
	template<typename T>
	inline_template T Hip(T cat1, T cat2)
	{
		T Hip = RaizQuad(QUAD(cat1) + QUAD(cat2));

		return Hip;
	}
}
