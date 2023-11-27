#pragma once

#ifdef _WIN64
typedef unsigned long long uinptr;
#else
typedef unsigned int uintptr;
#endif

typedef void* voidptr;	// Escrever "voidptr" é maior do que "void*", mas sei lá kkk

typedef unsigned char byte;



#define TAMMATRIZ(matriz) (sizeof matriz / sizeof matriz[0])

#define NUMPARACHAR(num) (num+48)	// Só funciona para um número/letra e não funciona com UNICODE

#define PARAMIN(chr) (chr+32)	// Esperado que seja um caractere
#define PARAMAI(chr) (chr-32)	// Esperado que seja um caractere

#pragma region Macros de funções

#define ZerarMat(Destino, tamanho) meu::MatSetB(Destino, 0, tamanho)
// Em vez dessa, pode se usar "ZerarMat" e somar "começo" a "Destino" e subtrair de "tamanho"
#define ZerarParteMat(Destino, tamanho, começo) meu::MatSetB(Destino, 0, tamanho, começo)

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
	
	// Passar um número e uma matriz de retorno
	// Pode ser usado a macro "NUMPARACHAR" para UM número/letra no lugar se preferido
	// INCOMPLETO, números como por exemplo "105" vão cortar o zero
	CONSTEXPR void NumParaChar(int num, char* retorno)
#ifdef EXTERNO
		;
#else
	{
		int tempnum = 0;
		int casas = 0;

		for (loop_tipo i = 0; num != 0; i++)
		{
			casas = 0;
			tempnum = num;

			while (tempnum > 9)
			{
				++casas;
				tempnum /= 10;
			}

			retorno[i] = tempnum + 48;

			num -= tempnum * meu::Pot<int, int>(10, casas);

			// Isso tá horrível
			if (num == 0 && casas > 0)
				for (loop_tipo a = 1; casas > 0; a++, casas--)
					retorno[i + a] = 48;
		}
	}
#endif

	template <typename T>
	// Testa se é "teste" é um dos valores de "lista"
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
	CONSTEXPR inline void Trocar(T& var1, T& var2)
	{
		T temp = var2;
		var2 = var1;
		var1 = temp;
	}

#pragma endregion

// § Matrizes
#pragma region Matrizes

	//template <typename T, typename ret>
	//// Tamanho da matriz
	//// Pode ser usado a macro "TAMMATRIZ" no lugar se preferido
	//CONSTEXPR ret TamMatriz(T* matriz)
	//{
	//	return sizeof matriz / sizeof matriz[0];
	//}

	// Versão template da de baixo
	/*template <typename T1, typename T2>
	// Substitui espaços pelo segundo parâmetro
	// Para essa versão que usa dois tipos diferentes, a função não se responsabiliza
	// se valores com espaço maior do que o aceitável na matrix forem usados.
	void SubstEspaços(T1* texto, T2 subst)
	{
		for (int i = 0; texto[i]; i++)
			if (texto[i] == ' ')
				texto[i] = subst;
	}*/

	// Substitui espaços pelo segundo parâmetro
	void SubstEspaços(char* texto, char subst)
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

	// Versão template da de baixo
	/*template <typename T1, typename T2>
	// Compara matrizes
	// [Versão template, não recomendado, pois essa função é feita para ignorar maiúsculas/minúsculas,
	// exemplo, "65 e 97" serão considerados iguais; para matrizes puramente iguais use Meu::CompMat()]
	// É esperado que seja uma matriz terminada com '\0', tudo depois de '\0' é ignorado
	// e é esperado que elas tenham o MESMO TAMANHO ou o '\0' de uma matrix, apareça antes de a outra acabar
	bool CompMatIg(T1* Matriz1, T2* Matriz2)
	{
		for (int i = 0; Matriz1[i] || Matriz2[i]; i++)
		{
			if (64 < Matriz1[i] && Matriz1[i] < 123)	// Verifica se é um caractere (Letra)
			{
				if (!(PARAMAI(Matriz1[i]) == Matriz2[i]) || !(Matriz1[i] == PARAMAI(Matriz2[i])))
					return false;
			}	// Eu sei que não precisa dessas chaves, mas o else _tava_ unindo com o if errado
			else
				if (Matriz1[i] != Matriz2[i])
					return false;
				
		}

		return true;
	}*/
		
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

	// Copia uma string
	// É esperado que "Origem" seja uma matriz terminada com 0 ou '\0', tudo depois de 0 ou '\0' é ignorado
	// "Origem" deve ser do MESMO TAMANHO OU MAIOR que "Destino"
	// *Além de copiar a string, ela retorna "true" se a string de "Origem" foi copiada por completo e "false" se o oposto*
//	CONSTEXPR bool CopyString(void* Destino, const void* Origem, /*tamT*/int tamDest)
//#ifdef EXTERNO
//		;
//#else
//	{
//		//byte* dest = Destino; byte* ori = Origem;
//
//		for (loop_tipo i = 0; i < tamDest; ++i)
//		{
//			if (!((char*)Origem)[i])
//			{
//				((char*)Destino)[i] = 0;
//				return true;	// Acabou
//			}
//			((char*)Destino)[i] = ((char*)Origem)[i];
//		}
//		return false;			// Ainda não acabou
//	}
//#endif

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

	/*template <typename T1, typename T2, typename tamT>
	// Diferentemente de std::memset, esse não funciona byte a byte, ele vai usar colocar o "valor"
	// em cada espaço (Como em uma matriz).
	// "tamanho" não deve ser o sizeof(matriz) mas a quantidade de elementos, pode ser usado a macro TAMMATRIZ para isso
	void MatSet(T1* Destino, T2 valor, tamT tamanho)
	{
		for (loop_tipo i = 0; i < tamanho; ++i)
			*(Destino + i) = valor;
	}*/

	// Não sei se preciso dessa se eu tenho a de baixo

	template <typename T>
	// Diferentemente de std::memset, esse não funciona byte a byte, ele vai usar colocar o "valor"
	// em cada espaço (Como em uma matriz).
	// "tamanho" não deve ser o sizeof(matriz) mas a quantidade de elementos, pode ser usado a macro TAMMATRIZ para isso
	// "começo" de onde começar a modificar os valores
	void MatSet(T* destino, T valor, loop_tipo tamanho, loop_tipo começo)
	{
		for (loop_tipo i = 0 + começo; i < tamanho; ++i)
			*(destino + i) = valor;
	}

	/*template <typename T1, typename T2, typename tamT, typename comT>
	// Diferentemente de std::memset, esse não funciona byte a byte, ele vai usar colocar o "valor"
	// em cada espaço (Como em uma matriz).
	// "tamanho" não deve ser o sizeof(matriz) mas a quantidade de elementos, pode ser usado a macro TAMMATRIZ para isso
	// "começo" de onde começar a modificar os valores
	void MatSet(T1* Destino, T2 valor, tamT tamanho, comT começo)
	{
		for (loop_tipo i = 0 + começo; i < tamanho; ++i)
			*(Destino + i) = valor;
	}*/

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

	template <typename T1, typename ret = int>
	// Retorna quantos elementos tem em uma matriz até o 0 ou '\0' mais próximo
	// Usar essa função caso não tenha certeza se a matriz está cheia ou não é terminada com 0 ou '\0',
	// tudo depois de 0 ou '\0' é ignorado.
	// "estado" é (true) se está cheia ou (false) se não cheia
	// Ela não considera o caractere nulo (0 ou '\0')
	CONSTEXPR ret MatTam(T1* matriz, loop_tipo tam, bool* estado)
	{
		ret quantidade = 0;
		*estado = false;

		while (matriz[quantidade] && quantidade < tam)
			++quantidade;

		if (quantidade == tam)
			*estado = true;

		return quantidade;
	}

	/**********************************************************************************************************************/



#pragma endregion

}

#pragma warning( pop )
