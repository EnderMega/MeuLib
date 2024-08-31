#pragma once

// S� anotando aqui, pq � algo interessante
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
typedef unsigned long long ptrtam;	// Tamanho de uma ponteiro
//typedef unsigned __int64 ptrtam;	// Tamanho de uma ponteiro
#else
typedef unsigned int ptrtam;		// Tamanho de uma ponteiro
#endif



#define QUAD(x) (x*x)
#define CUBO(x) (x*x*x)

#define MEUPI 3.14159265358
#define MEUPIf 3.1415927f

#define PGRAUS(rad) (rad * 180 / MEUPI)

inline namespace MeuMat {

// � Classes matem�ticas
#pragma region Classes matematicas

	struct Vec2 { float x, y; };

	//struct Vec3 { float x, y, z; };

	//struct Ang3 { float yaw, pitch, roll; };

	// Medo que os unions poss�o diminuir a performance.
	// Pelo que testei com "godbolt.com" o c�digo assembly � o mesmo.
	
	// Pode ser usado como posi��es cardinais (Vec3) ou �ngulos (Ang3)
	// (utiliza _unions_ ent�o s�o apenas 3 floats)
	typedef struct Vec3 {

		union {
			float x, yaw, r;
		};
		union {
			float y, pitch, g;
		};
		union {
			float z, roll, b;
		};

		// Operadores de assinala��o:

		void operator+=(Vec3 vec)
		{
			x += vec.x;
			y += vec.y;
			z += vec.z;
		}
		
		void operator-=(Vec3 vec)
		{
			x += vec.x;
			y += vec.y;
			z += vec.z;
		}

		void operator*=(Vec3 vec)
		{
			x *= vec.x;
			y *= vec.y;
			z *= vec.z;
		}

		void operator/=(Vec3 vec)
		{
			x /= vec.x;
			y /= vec.y;
			z /= vec.z;
		}

		// Operadores de compara��o:

		bool operator==(Vec3 vec)
		{
			if (x == vec.x &&
				y == vec.y &&
				z == vec.z)
				return true;

			return false;
		}

		bool operator!=(Vec3 vec)
		{
			if (x != vec.x &&
				y != vec.y &&
				z != vec.z)
				return true;

			return false;
		}

		// Operadores matem�ticos:

		Vec3 operator+(Vec3 vec)
		{
			vec.x += x;
			vec.y += y;
			vec.z += z;

			return vec;
		}

		Vec3 operator-(Vec3 vec)
		{
			vec.x -= x;
			vec.y -= y;
			vec.z -= z;

			return vec;
		}

		Vec3 operator*(Vec3 vec)
		{
			vec.x *= x;
			vec.y *= y;
			vec.z *= z;

			return vec;
		}

		Vec3 operator/(Vec3 vec)
		{
			vec.x /= x;
			vec.y /= y;
			vec.z /= z;

			return vec;
		}
	}Ang3, *ptrVec3, *ptrAng3;

	struct Vec4 { float x, y, z, w; };

#pragma endregion

// � Aritim�tica
#pragma region Aritimetica

	template <typename ret, typename T>
	// Como eu sou burro e n�o achei na internet, se usar negativos na base vai retornar '-1' kkk
	// TESTAR
	CONSTEXPR ret Pot(T base, int exp)
	{
		bool neg = false;

		// Para casos negativos
		// N�o � um erro, mas n�o quero lidar agora
		if (base < 0)
			return -1;	// Sei l� como lidar com erros, ent�o retorna '-1' e boa kkk

		if (exp < 0)
		{
			neg = true;
			exp *= -1;
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

		for (long long i = 1; i < exp; i++)	// i come�a em 1 para remover a linha exp -= 1;
			Resultado *= base;

		if (neg)
		{
			if (!Resultado)
				return -1;

			return 1 / Resultado;
		}

		return Resultado;
	}

	// Sobrecarga para float, pois n�o pode ter caso switch para float
	// Como eu sou burro e n�o achei na internet, se usar negativos vai retornar '-1'
	CONSTEXPR float Pot(float base, int exp)
#ifdef EXTERNO
		;
#else
	{
		bool neg = false;

		// Para casos negativos
		// N�o � um erro, mas n�o quero lidar agora
		if (base < 0)
			return -1;	// Sei l� como lidar com erros, ent�o retorna '-1' e boa kkk

		if (exp < 0)
		{
			neg = true;
			exp *= -1;
		}

		if (exp == 0)
			return 1;
		if (exp == 1)
			return base;
		if (exp == 2)
			return QUAD(base);
		if (exp == 3)
			return CUBO(base);

		if (base == 0)
			return 0;
		if (base == 1)
			return 1;


		float Resultado = base;

		//exp -= 1;

		for (int i = 1; i < exp; i++)	// i come�a em 1 para remover a linha exp -= 1;
			Resultado *= base;

		if (neg)
		{
			if (!Resultado)
				return -1;

			return 1 / Resultado;
		}

		return Resultado;
	}
#endif

	// Sobrecarga para double, pois n�o pode ter caso switch para double
	// Como eu sou burro e n�o achei na internet, se usar negativos vai retornar '-1'
	CONSTEXPR double Pot(double base, int exp)
#ifdef EXTERNO
		;
#else
	{
		bool neg = false;

		// Para casos negativos
		// N�o � um erro, mas n�o quero lidar agora
		if (base < 0)
			return -1;	// Sei l� como lidar com erros, ent�o retorna '-1' e boa kkk

		if (exp < 0)
		{
			neg = true;
			exp *= -1;
		}

		if (exp == 0)
			return 1;
		if (exp == 1)
			return base;
		if (exp == 2)
			return QUAD(base);
		if (exp == 3)
			return CUBO(base);

		if (base == 0)
			return 0;
		if (base == 1)
			return 1;

		double Resultado = base;

		//exp -= 1;

		for (int i = 1; i < exp; i++)	// i come�a em 1 para remover a linha exp -= 1;
			Resultado *= base;

		if (neg)
		{
			if (!Resultado)
				return -1;

			return 1 / Resultado;
		}

		return Resultado;
	}
#endif

	CONSTEXPR float RaizQuad(float raiz)
#ifdef EXTERNO
		;
#else
	{
		float precisao = 0.000001f;
		float b = raiz, a = 1;
		while ((b - a) >= precisao) {
			b = (b + a) / 2;
			a = raiz / b;
		}
		return b;
	}
#endif

	template<typename T>
	// Ainda precisa ser testado
	// N�o existe factorial de valor negativo, ent�o por favor, n�o crie o template como "unsigned ~"
	CONSTEXPR T Factorial(T valor)
	{
		T res = 1;

		if (!valor)
			return 1;

		if (valor == 1)
			return 1;
		if (valor == 2)
			return 2;

		// Quero testar se � diferente de 1 pois se for 1 n�o tem por que multiplicar
		// Entretando estou pensado se vale mais eu passa pelo loop ou testar todas as vezes
		//while (valor != 1 || valor > 0)

		while (valor > 0)	// N�o existe factorial de valor negativo
		{
			res *= valor;
			--valor;
		}

		return res;
	}

#pragma endregion

// � Trigonometria
#pragma region Trigonometria

	// Calcula a hipotenusa
	// N�o � o melhor theorema de pit�goras, mas sei l�, melhor ter do que n�o ter?
	CONSTEXPR float Hip(float cat1, float cat2)
#ifdef EXTERNO
		;
#else
	{
		float Hip = RaizQuad(QUAD(cat1) + QUAD(cat2));

		return Hip;
	}
#endif

#pragma endregion

}
