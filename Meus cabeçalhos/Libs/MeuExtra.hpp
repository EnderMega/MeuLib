#pragma once

#define TAMMATRIZ(matriz) (sizeof matriz / sizeof matriz[0])

#define NUMPARACHAR(num) (num+48)	// Só funciona para um número/letra

#define PARAMIN(chr) (chr+32)	// Esperado que seja um caractere
#define PARAMAI(chr) (chr-32)	// Esperado que seja um caractere

#define DESREF(x) *(Meu::uinptr)(x)

// Macro de funções

#define ZerarMat(Destino, tamanho) Meu::MatSet(Destino, 0, tamanho)
// Em vez dessa, pode se usar "ZerarMat" e somar "começo" a "Destino" e subtrair de "tamanho"
#define ZerarParteMat(Destino, tamanho, começo) Meu::MatSet(Destino, 0, tamanho, começo)

inline namespace MeuExtra {

	// § Extra
	
	template<typename T>
	// Passar um número e uma matriz de retorno
	// Pode ser usado a macro "NUMPARACHAR" para UM número/letra no lugar se preferido
	// INCOMPLETO, números como por exemplo "105" vão cortar o zero
	tipo_função constexpr void NumParaChar(T num, char* retorno)
	{
		int tempnum = 0;
		int casas = 0;

		for (long long i = 0; num != 0; i++)
		{
			casas = 0;
			tempnum = num;

			while (tempnum > 9)
			{
				++casas;
				tempnum /= 10;
			}

			retorno[i] = tempnum + 48;

			num -= tempnum * Meu::Pot<int, int>(10, casas);

			// Isso tá horrível
			if (num == 0 && casas > 0)
				for (long long a = 1; casas > 0; a++, casas--)
					retorno[i + a] = 48;
		}
	}

	// § Matrizes

	template <typename T, typename ret>
	// Tamanho da matriz
	// Pode ser usado a macro "TAMMATRIZ" no lugar se preferido
	inline_template constexpr ret TamMatriz(T* matriz)
	{
		return sizeof matriz / sizeof matriz[0];
	}

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

	template <typename T1, typename T2>
	// Substitui espaços pelo segundo parâmetro
	// A função não se responsabiliza se o substituto for maior que 'char'
	inline_template void SubstEspaços(T1* texto, T2 subst)
	{
		for (long long i = 0; texto[i]; i++)
			if (texto[i] == ' ')
				texto[i] = subst;
	}

	/**********************************************************************************************************************/

	template <typename T1, typename T2>
	// Compara matrizes
	// É esperado que seja uma matriz terminada com 0 ou '\0', tudo depois de 0 ou '\0' é ignorado
	// e é esperado que elas tenham o MESMO TAMANHO ou o 0 ou '\0' de uma matrix, apareça antes de a outra acabar
	inline_template bool CompMat(T1* Matriz1, T2* Matriz2)
	{
		for (long long i = 0; Matriz1[i] || Matriz2[i]; i++)
		{
			if (!(Matriz1[i] == Matriz2[i]))
				return false;
		}

		return true;
	}
	
	// Outra versão da de baixo, não testei, mas acredito ser mais lenta
	/*template <typename T1, typename T2>
	// Compara matrizes
	// Essa versão aceita caracteres 0 ou '\0' mas requer o tamanho de ambas as matrizes
	// é esperado que ambas tenham o mesmo tamanho
	inline_template bool CompMat(T1* Matriz1, T2* Matriz2, long long tam)
	{
		for (int i = 0; Matriz1[i] == Matriz2[i]; i++);

		if (i = tam)
			return true;
		else
			return false;
	}*/

	template <typename T1, typename T2, typename tamT>
	// Compara matrizes
	// Essa versão aceita caracteres 0 ou '\0' mas requer o tamanho de ambas as matrizes
	// é esperado que ambas tenham o mesmo tamanho, o "tam"
	inline_template bool CompMat(T1* Matriz1, T2* Matriz2, tamT tam)
	{
		for (long long i = 0; i < tam; i++)
		{
			if (!(Matriz1[i] == Matriz2[i]))
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
	inline_template bool CompMatIg(T1* Matriz1, T2* Matriz2)
	{
		for (int i = 0; Matriz1[i] || Matriz2[i]; i++)
		{
			if (64 < Matriz1[i] && Matriz1[i] < 123)	// Verifica se é um caractere (Letra)
			{
				if (!(PARAMAI(Matriz1[i]) == Matriz2[i]) || !(Matriz1[i] == PARAMAI(Matriz2[i])))
					return false;
			}	// Eu sei que não precisa dessas chaves, mas o else _tava_ unindo com o if errado
			else
				if (!(Matriz1[i] == Matriz2[i]))
					return false;
				
		}

		return true;
	}*/
		
	// Compara matrizes e ignora capitalização
	// [Designada para char(s)]
	// É esperado que seja uma matriz terminada com 0 ou '\0', tudo depois de 0 ou '\0' é ignorado
	// e é esperado que elas tenham o MESMO TAMANHO ou o 0 ou '\0' de uma matrix, apareça antes de a outra acabar
	tipo_função bool CompMatIg(const char* Matriz1, const char* Matriz2)
	{
		for (long long i = 0; Matriz1[i] || Matriz2[i]; i++)
		{
			if (!(Matriz1[i] == Matriz2[i]))
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

	/**********************************************************************************************************************/

	// Não sei se vale a pena ter "começo" se eu posso só somar a "Destino" e subtrair de "TamDest" antes de chamar a função

	template <typename T1, typename T2, typename tamT, typename comT>
	// Copia uma matriz para a outra
	// É esperado que "Origem" seja uma matriz terminada com 0 ou '\0', tudo depois de 0 ou '\0' é ignorado
	// "Origem" deve ser do MESMO TAMANHO OU MAIOR que "Destino"
	// "começo" é de onde começar a escrever em "Destino"
	// *Além de copiar a string, ela retorna "true" se a string de "Origem" foi copiada por completo e "false" se o oposto*
	// Pode ser usado a versão sem "começo", pois começo é o equivalente a somar a "Destino" e subtrair de "TamDest"
	inline_template constexpr bool CopyMat(T1* Destino, T2* Origem, tamT TamDest, comT começo)
	{
		for (long long i = 0; i < TamDest - começo; ++i)
		{
			if (!Origem[i])
			{
				Destino[começo + i] = 0;
				return true;	// Acabou
			}
			Destino[começo + i] = Origem[i];
		}
		return false;			// Ainda não acabou
	}
	
	template <typename T1, typename T2, typename tamT>
	// Copia uma matriz para a outra
	// É esperado que "Origem" seja uma matriz terminada com 0 ou '\0', tudo depois de 0 ou '\0' é ignorado
	// "Origem" deve ser do MESMO TAMANHO OU MAIOR que "Destino"
	// *Além de copiar a string, ela retorna "true" se a string de "Origem" foi copiada por completo e "false" se o oposto*
	inline_template constexpr bool CopyMat(T1* Destino, T2* Origem, tamT TamDest)
	{
		for (long long i = 0; i < TamDest; ++i)
		{
			if (!Origem[i])
			{
				Destino[i] = 0;
				return true;	// Acabou
			}
			Destino[i] = Origem[i];
		}
		return false;			// Ainda não acabou
	}
	
	template <typename T, typename tamT>
	// Copia uma matriz para a outra
	// É esperado que "Origem" seja uma matriz terminada com 0 ou '\0', tudo depois de 0 ou '\0' é ignorado
	// "Origem" deve ser do MESMO TAMANHO OU MAIOR que "Destino"
	// *Além de copiar a string, ela retorna "true" se a string de "Origem" foi copiada por completo e "false" se o oposto*
	inline_template constexpr bool CopyMat(T* Destino, T* Origem, tamT TamDest)
	{
		for (long long i = 0; i < TamDest; ++i)
		{
			if (!Origem[i])
			{
				Destino[i] = 0;
				return true;	// Acabou
			}
			Destino[i] = Origem[i];
		}
		return false;			// Ainda não acabou
	}

	/**********************************************************************************************************************/

	// Não sei se preciso dessa se eu tenho a de baixo

	template <typename T, typename tamT>
	// Diferentemente de std::memset, esse não funciona byte a byte, ele vai usar colocar o "valor"
	// em cada espaço (Como em uma matriz).
	// "tamanho" não deve ser o sizeof(matriz) mas a quantidade de elementos, pode ser usado a macro TAMMATRIZ para isso
	inline_template void MatSet(T* Destino, T valor, tamT tamanho)
	{
		for (long long i = 0; i < tamanho; ++i)
			*(Destino + i) = valor;
	}

	template <typename T1, typename T2, typename tamT>
	// Diferentemente de std::memset, esse não funciona byte a byte, ele vai usar colocar o "valor"
	// em cada espaço (Como em uma matriz).
	// "tamanho" não deve ser o sizeof(matriz) mas a quantidade de elementos, pode ser usado a macro TAMMATRIZ para isso
	inline_template void MatSet(T1* Destino, T2 valor, tamT tamanho)
	{
		for (long long i = 0; i < tamanho; ++i)
			*(Destino + i) = valor;
	}

	// Não sei se preciso dessa se eu tenho a de baixo

	template <typename T, typename tamT, typename comT>
	// Diferentemente de std::memset, esse não funciona byte a byte, ele vai usar colocar o "valor"
	// em cada espaço (Como em uma matriz).
	// "tamanho" não deve ser o sizeof(matriz) mas a quantidade de elementos, pode ser usado a macro TAMMATRIZ para isso
	// "começo" de onde começar a modificar os valores
	inline_template void MatSet(T* Destino, T valor, tamT tamanho, comT começo)
	{
		for (long long i = 0 + começo; i < tamanho; ++i)
			*(Destino + i) = valor;
	}

	
	template <typename T1, typename T2, typename tamT, typename comT>
	// Diferentemente de std::memset, esse não funciona byte a byte, ele vai usar colocar o "valor"
	// em cada espaço (Como em uma matriz).
	// "tamanho" não deve ser o sizeof(matriz) mas a quantidade de elementos, pode ser usado a macro TAMMATRIZ para isso
	// "começo" de onde começar a modificar os valores
	inline_template void MatSet(T1* Destino, T2 valor, tamT tamanho, comT começo)
	{
		for (long long i = 0 + começo; i < tamanho; ++i)
			*(Destino + i) = valor;
	}

	/**********************************************************************************************************************/

	template <typename T, typename ret>
	// Retorna quantos elementos tem em uma matriz
	// É esperado que seja uma matriz terminada com 0 ou '\0', tudo depois de 0 ou '\0' é ignorado.
	// Ela não considera o caractere nulo (0 ou '\0')
	inline_template constexpr ret QuantEleMat(T* matriz)
	{
		ret quantidade = 0;

		for (; matriz[quantidade]; quantidade++);

		/*while (matriz[quantidade])
			++quantidade;*/

		return quantidade;
	}

	template <typename T1, typename tamT, typename ret>
	// Retorna quantos elementos tem em uma matriz até o 0 ou '\0' mais próximo
	// Usar essa função caso não tenha certeza se a matriz está cheia ou não é terminada com 0 ou '\0',
	// tudo depois de 0 ou '\0' é ignorado.
	// Ela não considera o caractere nulo (0 ou '\0')
	inline_template constexpr ret QuantEleMat(T1* matriz, tamT tam)
	{
		ret quantidade = 0;

		while (matriz[quantidade] && quantidade < tam)
			++quantidade;

		return quantidade;
	}

	template <typename T1, typename tamT, typename ret>
	// Retorna quantos elementos tem em uma matriz até o 0 ou '\0' mais próximo
	// Usar essa função caso não tenha certeza se a matriz está cheia ou não é terminada com 0 ou '\0',
	// tudo depois de 0 ou '\0' é ignorado.
	// "estado" é (true) se está cheia ou (false) se não cheia
	// Ela não considera o caractere nulo (0 ou '\0')
	inline_template constexpr ret QuantEleMat(T1* matriz, tamT tam, bool* estado)
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


}
