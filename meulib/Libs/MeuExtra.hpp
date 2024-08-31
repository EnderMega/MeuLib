#pragma once

#ifdef _WIN64
typedef unsigned long long uinptr;
#else
typedef unsigned int uintptr;
#endif

typedef void* voidptr;	// Escrever "voidptr" é maior do que "void*", mas sei lá kkk

typedef unsigned char byte;



#define TAMMATRIZ(matriz) (sizeof matriz / sizeof matriz[0])

#define NUMPARACHAR(num) (num+48)	// Só funciona para um número/letra

#define PARAMIN(chr) (chr+32)	// Esperado que seja um caractere
#define PARAMAI(chr) (chr-32)	// Esperado que seja um caractere

#pragma region Macros de funcoes

#define ZerarMat(Destino, tamanho) meu::MatSetB(Destino, 0, tamanho)
// Em vez dessa, pode se usar "ZerarMat" e somar "começo" a "Destino" e subtrair de "tamanho"
#define ZerarParteMat(Destino, tamanho, comeco) meu::MatSetB(Destino, 0, tamanho, comeco)

#pragma endregion

#pragma region Cores
#define MEURGB(r, g, b) (0x10000 * r + 0x100 * g + b)

typedef uint COR;

#define VERMELHO	0xff'00'00u	// Macros de cores
#define VERDE		0x00'ff'00u	// Macros de cores
#define AZUL		0x00'00'ffu	// Macros de cores

#define PRETO		0u			// Macros de cores
#define BRANCO		0xff'ff'ffu	// Macros de cores
#pragma endregion

// Avisos de uso de comparadores com valores sem sinal
#pragma warning( push )
#pragma warning( disable : 4018 )

inline namespace MeuExtra {

// § Extra
#pragma region Extra

	// Inverter strings
	void inverter(char* texto, int tam)
#ifdef EXTERNO
		;
#else
	{
		int inver_comeco = 0;
		int inver_fim = tam - 1;

		char temp;

		while (inver_comeco < inver_fim)
		{
			temp = texto[inver_comeco];
			texto[inver_comeco] = texto[inver_fim];
			texto[inver_fim] = temp;
			--inver_fim;
			++inver_comeco;
		}
	}
#endif
	
	// Inverter strings
	void inverter(wchar_t* texto, int tam)
#ifdef EXTERNO
		;
#else
	{
		int inver_comeco = 0;
		int inver_fim = tam - 1;

		char temp;

		while (inver_comeco < inver_fim)
		{
			temp = texto[inver_comeco];
			texto[inver_comeco] = texto[inver_fim];
			texto[inver_fim] = temp;
			--inver_fim;
			++inver_comeco;
		}
	}
#endif

	// Meu atoi ("char" to integer)
	// Deve ser uma matriz terminada em '\0'
	long long matoi(const char* texto)
#ifdef EXTERNO
		;
#else
	{
		uint i = 0;
		long long ret = 0;
		char neg = 1;

		if (*texto == '-')
		{
			++i;
			neg = -1;
		}

		for (; texto[i]; i++)
			ret = ret * 10 + texto[i] - '0';

		ret *= neg;

		return ret;
	}
#endif
	
	// Meu atoi ("char" to integer)
	// Deve ser uma matriz terminada em '\0'
	long long matoi(const wchar_t* texto)
#ifdef EXTERNO
		;
#else
	{
		uint i = 0;
		long long ret = 0;
		char neg = 1;

		if (*texto == L'-')
		{
			++i;
			neg = -1;
		}

		for (; texto[i]; i++)
			ret = ret * 10 + texto[i] - L'0';

		ret *= neg;

		return ret;
	}
#endif

	// meu itoa()
	char* mitoa(int num, char* texto, int base)
#ifdef EXTERNO
		;
#else
	{
		int i = 0;
		bool negativo = false;

		// Lidando com 0 explicitamente
		if (num == 0)
		{
			texto[i++] = '0';
			texto[i] = '\0';
			return texto;
		}

		// No itoa() padrão números negativos só são lidados para base 10
		if (num < 0 && base == 10)
		{
			negativo = true;
			num = -num;
		}

		while (num != 0)
		{
			int temp = num % base;
			texto[i++] = (temp > 9) ? (temp - 10) + 'a' : temp + '0';
			num = num / base;
		}

		if (negativo)
			texto[i++] = '-';

		texto[i] = '\0';

		inverter(texto, i);

		return texto;	// Isso server para poder usar a função dentro de outras funções
	}
#endif
	
	// meu itoa()
	wchar_t* mitoa(int num, wchar_t* texto, int base)
#ifdef EXTERNO
		;
#else
	{
		int i = 0;
		bool negativo = false;

		// Lidando com 0 explicitamente
		if (num == 0)
		{
			texto[i++] = L'0';
			texto[i] = L'\0';
			return texto;
		}

		// No itoa() padrão números negativos só são lidados para base 10
		if (num < 0 && base == 10)
		{
			negativo = true;
			num = -num;
		}

		while (num != 0)
		{
			int temp = num % base;
			texto[i++] = (temp > 9) ? (temp - 10) + L'a' : temp + L'0';
			num = num / base;
		}

		if (negativo)
			texto[i++] = L'-';

		texto[i] = L'\0';

		inverter(texto, i);

		return texto;	// Isso server para poder usar a função dentro de outras funções
	}
#endif

	// TODO NÃO IMPLEMENTADO
	CONSTEXPR void transCharWide(wchar_t* texto)
	{
		
	}

	template <typename T>
	// Testa se "teste" é um dos valores de "lista"
	// "lista" Deve ser terminado em 0
	// Retorna false se não é nem um dos valores da lista e verdadeiro caso o contrário
	CONSTEXPR bool VarIgTeste(T teste, T* lista)
	{
		while (teste != *lista)
		{
			++lista;

			if (!*lista)
				return false;
		}

		return true;
	}

	template <typename T>
	// Super incrível função que troca o valor das variáveis.
	CONSTEXPR inline void trocar(T& var1, T& var2)
	{
		T temp = var2;
		var2 = var1;
		var1 = temp;
	}

#pragma endregion

// § Matrizes
#pragma region Matrizes

	// Substitui espaços pelo segundo parâmetro
	void SubstEspacos(char* texto, char subst)
#ifdef EXTERNO
		;
#else
	{
		for (loop_tipo i = 0; texto[i]; i++)
			if (texto[i] == ' ')
				texto[i] = subst;
	}
#endif

	/**********************************************************************************************************************/

	template <typename T1, typename T2>
	// Compara matrizes
	// Ambas devem acabar ao mesmo tempo, se não ele continua lendo e vê que uma acabou
	// (apareceu o 0 antes da outra) mas a outra não, ai ela vai retornar "falso".
	bool CompMat(T1* Matriz1, T2* Matriz2)
	{
		// Se uma das matrizes começar com 0 ele vai pular o loop e vai falar que é verdadeiro
		if (!(*Matriz1 && *Matriz2))
			return false;

		for (loop_tipo i = 0; Matriz1[i] || Matriz2[i]; i++)
		{
			if (Matriz1[i] != Matriz2[i])
				return false;
		}

		return true;
	}
	
	// Outra versão da de baixo, não testei, mas acredito ser mais lenta
	/*template <typename T1, typename T2>
	// Compara matrizes
	// Essa versão aceita caracteres 0 ou '\0' mas requer o tamanho de ambas as matrizes
	// é esperado que ambas tenham o mesmo tamanho
	bool CompMat(T1* Matriz1, T2* Matriz2, long long tam)
	{
		for (int i = 0; Matriz1[i] == Matriz2[i]; i++);

		if (i = tam)
			return true;
		else
			return false;
	}*/

	template <typename T1, typename T2>
	// Compara matrizes
	// Essa versão aceita caracteres 0 ou '\0' mas requer o tamanho de ambas as matrizes
	// Ele acaba quando a quantidade de caracteres for lida, todo o resto é ignorado.
	bool CompMat(T1* Matriz1, T2* Matriz2, loop_tipo tam)
	{
		for (loop_tipo i = 0; i < tam; i++)
		{
			if (Matriz1[i] != Matriz2[i])
				return false;
		}

		return true;
	}

	/**********************************************************************************************************************/

	// Compara matrizes e ignora capitalização
	// [Designada para char(s)]
	// AMBAS DEVEM ACABAR AO MESMO TEMPO, se não ele continua lendo e vê que uma acabou
	// (apareceu o 0 antes da outra) mas a outra não, retornando "falso".
	bool CompMatIg(const char* Matriz1, const char* Matriz2)
#ifdef EXTERNO
		;
#else
	{
		// Se uma das matrizes começar com 0 ele vai pular o loop e vai falar que é verdadeiro
		if (!(*Matriz1 && *Matriz2))
			return false;

		for (loop_tipo i = 0; Matriz1[i] || Matriz2[i]; i++)
		{
			if (Matriz1[i] != Matriz2[i])
				if ((64 < Matriz1[i] && Matriz1[i] < 123) &&
					(64 < Matriz2[i] && Matriz2[i] < 123))	// Verifica se é um caractere (Letra)
				{
					// É impossível ambos serem verdadeiros, pois "x - 32 = y" nunca vai ser igual a "x = y - 32" (Primeiras duas partes)
					// dessa forma ambos só podem ser iguais se forem falsos, então se ambos os resultados forem iguais (falso e falso)
					// as letras não são iguais e se forem diferentes as letras são iguais.
					if (!((PARAMAI(Matriz1[i]) == Matriz2[i]) != (Matriz1[i] == PARAMAI(Matriz2[i]))))
						return false;
				}
				else
					return false;
		}

		return true;
	}
#endif

	// Compara matrizes e ignora capitalização
	// [Designada para char(s)]
	// Essa versão aceita caracteres 0 ou '\0' mas requer o tamanho de ambas as matrizes
	// Ele acaba quando a quantidade de caracteres for lida, todo o resto é ignorado.
	bool CompMatIg(const char* Matriz1, const char* Matriz2, loop_tipo tam)
#ifdef EXTERNO
		;
#else
	{
		for (loop_tipo i = 0; i < tam; i++)
		{
			if (Matriz1[i] != Matriz2[i])
				if ((64 < Matriz1[i] && Matriz1[i] < 123) &&
					(64 < Matriz2[i] && Matriz2[i] < 123))	// Verifica se é um caractere (Letra)
				{
					// É impossível ambos serem verdadeiros, pois "x - 32 = y" nunca vai ser igual a "x = y - 32" (Primeiras duas partes)
					// dessa forma ambos só podem ser iguais se forem falsos, então se ambos os resultados forem iguais (falso e falso)
					// as letras não são iguais e se forem diferentes as letras são iguais.
					if (!((PARAMAI(Matriz1[i]) == Matriz2[i]) != (Matriz1[i] == PARAMAI(Matriz2[i]))))
						return false;
				}
				else
					return false;
		}

		return true;
	}
#endif

	// Compara matrizes e ignora capitalização
	// [Designada para char(s)]
	// AMBAS DEVEM ACABAR AO MESMO TEMPO, se não ele continua lendo e vê que uma acabou
	// (apareceu o 0 antes da outra) mas a outra não, retornando "falso".
	bool CompMatIg(const wchar_t* Matriz1, const wchar_t* Matriz2)
#ifdef EXTERNO
		;
#else
	{
		// Se uma das matrizes começar com 0 ele vai pular o loop e vai falar que é verdadeiro
		if (!(*Matriz1 && *Matriz2))
			return false;

		for (loop_tipo i = 0; Matriz1[i] || Matriz2[i]; i++)
		{
			if (Matriz1[i] != Matriz2[i])
				if ((64 < Matriz1[i] && Matriz1[i] < 123) &&
					(64 < Matriz2[i] && Matriz2[i] < 123))	// Verifica se é um caractere (Letra)
				{
					// É impossível ambos serem verdadeiros, pois "x - 32 = y" nunca vai ser igual a "x = y - 32" (Primeiras duas partes)
					// dessa forma ambos só podem ser iguais se forem falsos, então se ambos os resultados forem iguais (falso e falso)
					// as letras não são iguais e se forem diferentes as letras são iguais.
					if (!((PARAMAI(Matriz1[i]) == Matriz2[i]) != (Matriz1[i] == PARAMAI(Matriz2[i]))))
						return false;
				}
				else
					return false;
		}

		return true;
	}
#endif

	// Compara matrizes e ignora capitalização
	// [Designada para char(s)]
	// Essa versão aceita caracteres 0 ou '\0' mas requer o tamanho de ambas as matrizes
	// Ele acaba quando a quantidade de caracteres for lida, todo o resto é ignorado.
	bool CompMatIg(const wchar_t* Matriz1, const wchar_t* Matriz2, loop_tipo tam)
#ifdef EXTERNO
		;
#else
	{
		for (loop_tipo i = 0; i < tam; i++)
		{
			if (Matriz1[i] != Matriz2[i])
				if ((64 < Matriz1[i] && Matriz1[i] < 123) &&
					(64 < Matriz2[i] && Matriz2[i] < 123))	// Verifica se é um caractere (Letra)
				{
					// É impossível ambos serem verdadeiros, pois "x - 32 = y" nunca vai ser igual a "x = y - 32" (Primeiras duas partes)
					// dessa forma ambos só podem ser iguais se forem falsos, então se ambos os resultados forem iguais (falso e falso)
					// as letras não são iguais e se forem diferentes as letras são iguais.
					if (!((PARAMAI(Matriz1[i]) == Matriz2[i]) != (Matriz1[i] == PARAMAI(Matriz2[i]))))
						return false;
				}
				else
					return false;
		}

		return true;
	}
#endif

	/**********************************************************************************************************************/

	template<typename T>
	CONSTEXPR void CopyMat(T* Destino, const T* Origem, loop_tipo tamDest)
	{
		for (loop_tipo i = 0; i < tamDest; ++i)
			Destino[i] = Origem[i];
	}

	// Copia byte a byte
	CONSTEXPR void CopyMatB(void* Destino, const void* Origem, loop_tipo tamDest)
#ifdef EXTERNO
		;
#else
	{
		for (loop_tipo i = 0; i < tamDest; ++i)
			((byte*)Destino)[i] = ((byte*)Origem)[i];
	}
#endif

	template<typename T>
	// Feito para strings
	// retorna true se copiou tudo e false se não
	// para de copiar quando encontra um '\0'
	CONSTEXPR bool retCopyMat(T* Destino, const T* Origem, loop_tipo tamDest)
	{
		loop_tipo i = 0;

		for (; i < tamDest || Origem[i]; i++)
			Destino[i] = Origem[i];

		if (i == tamDest)
			return true;
		else
			return false;
	}

	/**********************************************************************************************************************/

	// Não sei se preciso dessa se eu tenho a de baixo

	// MatSet byte a byte
	// O valor a ser setado tem que ser de no máximo um byte e tamanho deve ser dado em bytes [sizeof ~].
	void MatSetB(void* destino, uchar valor, loop_tipo tamanho)
#ifdef EXTERNO
		;
#else
	{
		for (loop_tipo i = 0; i < tamanho; ++i)
			*((char*)destino + i) = valor;
	}
#endif

	template <typename T>
	// Diferentemente de std::memset, esse não funciona byte a byte, ele vai usar colocar o "valor"
	// em cada espaço (Como em uma matriz).
	// "tamanho" não deve ser o sizeof(matriz) mas a quantidade de elementos, pode ser usado a macro TAMMATRIZ para isso
	void MatSet(T* destino, T valor, loop_tipo tamanho)
	{
		for (loop_tipo i = 0; i < tamanho; ++i)
			*(destino + i) = valor;
	}

	/**********************************************************************************************************************/

	template <typename T, typename ret = int>
	// Retorna quantos elementos tem em uma matriz
	// É esperado que seja uma matriz terminada com 0 ou '\0', tudo depois de 0 ou '\0' é ignorado.
	// Ela não considera o caractere nulo (0 ou '\0')
	CONSTEXPR ret MatTam(T* matriz)
	{
		ret quantidade = 0;

		for (; matriz[quantidade]; quantidade++);

		/*while (matriz[quantidade])
			++quantidade;*/

		return quantidade;
	}

	template <typename T1, typename ret = int>
	// Retorna quantos elementos tem em uma matriz até o 0 ou '\0' mais próximo
	// Usar essa função caso não tenha certeza se a matriz está cheia ou não é terminada com 0 ou '\0',
	// tudo depois de 0 ou '\0' é ignorado.
	// Ela não considera o caractere nulo (0 ou '\0')
	CONSTEXPR ret MatTam(T1* matriz, loop_tipo tam)
	{
		ret quantidade = 0;

		while (matriz[quantidade] && quantidade < tam)
			++quantidade;

		return quantidade;
	}

	/**********************************************************************************************************************/



#pragma endregion

}

#pragma warning( pop )
