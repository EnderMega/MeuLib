#pragma once

#define TAMMATRIZ(matriz) (sizeof matriz / sizeof matriz[0])

#define NUMPARACHAR(num) (num+48)	// S� funciona para um n�mero/letra

#define PARAMIN(chr) (chr+32)	// Esperado que seja um caractere
#define PARAMAI(chr) (chr-32)	// Esperado que seja um caractere

#define DESREF(x) *(Meu::uinptr)(x)

// Macro de fun��es

#define ZerarMat(Destino, tamanho) Meu::MatSet(Destino, 0, tamanho)
// Em vez dessa, pode se usar "ZerarMat" e somar "come�o" a "Destino" e subtrair de "tamanho"
#define ZerarParteMat(Destino, tamanho, come�o) Meu::MatSet(Destino, 0, tamanho, come�o)

inline namespace MeuExtra {

	// � Extra
	
	template<typename T>
	// Passar um n�mero e uma matriz de retorno
	// Pode ser usado a macro "NUMPARACHAR" para UM n�mero/letra no lugar se preferido
	// INCOMPLETO, n�meros como por exemplo "105" v�o cortar o zero
	tipo_fun��o constexpr void NumParaChar(T num, char* retorno)
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

			// Isso t� horr�vel
			if (num == 0 && casas > 0)
				for (long long a = 1; casas > 0; a++, casas--)
					retorno[i + a] = 48;
		}
	}

	// � Matrizes

	template <typename T, typename ret>
	// Tamanho da matriz
	// Pode ser usado a macro "TAMMATRIZ" no lugar se preferido
	inline_template constexpr ret TamMatriz(T* matriz)
	{
		return sizeof matriz / sizeof matriz[0];
	}

	// Vers�o template da de baixo
	/*template <typename T1, typename T2>
	// Substitui espa�os pelo segundo par�metro
	// Para essa vers�o que usa dois tipos diferentes, a fun��o n�o se responsabiliza
	// se valores com espa�o maior do que o aceit�vel na matrix forem usados.
	void SubstEspa�os(T1* texto, T2 subst)
	{
		for (int i = 0; texto[i]; i++)
			if (texto[i] == ' ')
				texto[i] = subst;
	}*/

	template <typename T1, typename T2>
	// Substitui espa�os pelo segundo par�metro
	// A fun��o n�o se responsabiliza se o substituto for maior que 'char'
	inline_template void SubstEspa�os(T1* texto, T2 subst)
	{
		for (long long i = 0; texto[i]; i++)
			if (texto[i] == ' ')
				texto[i] = subst;
	}

	/**********************************************************************************************************************/

	template <typename T1, typename T2>
	// Compara matrizes
	// � esperado que seja uma matriz terminada com 0 ou '\0', tudo depois de 0 ou '\0' � ignorado
	// e � esperado que elas tenham o MESMO TAMANHO ou o 0 ou '\0' de uma matrix, apare�a antes de a outra acabar
	inline_template bool CompMat(T1* Matriz1, T2* Matriz2)
	{
		for (long long i = 0; Matriz1[i] || Matriz2[i]; i++)
		{
			if (!(Matriz1[i] == Matriz2[i]))
				return false;
		}

		return true;
	}
	
	// Outra vers�o da de baixo, n�o testei, mas acredito ser mais lenta
	/*template <typename T1, typename T2>
	// Compara matrizes
	// Essa vers�o aceita caracteres 0 ou '\0' mas requer o tamanho de ambas as matrizes
	// � esperado que ambas tenham o mesmo tamanho
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
	// Essa vers�o aceita caracteres 0 ou '\0' mas requer o tamanho de ambas as matrizes
	// � esperado que ambas tenham o mesmo tamanho, o "tam"
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

	// Vers�o template da de baixo
	/*template <typename T1, typename T2>
	// Compara matrizes
	// [Vers�o template, n�o recomendado, pois essa fun��o � feita para ignorar mai�sculas/min�sculas,
	// exemplo, "65 e 97" ser�o considerados iguais; para matrizes puramente iguais use Meu::CompMat()]
	// � esperado que seja uma matriz terminada com '\0', tudo depois de '\0' � ignorado
	// e � esperado que elas tenham o MESMO TAMANHO ou o '\0' de uma matrix, apare�a antes de a outra acabar
	inline_template bool CompMatIg(T1* Matriz1, T2* Matriz2)
	{
		for (int i = 0; Matriz1[i] || Matriz2[i]; i++)
		{
			if (64 < Matriz1[i] && Matriz1[i] < 123)	// Verifica se � um caractere (Letra)
			{
				if (!(PARAMAI(Matriz1[i]) == Matriz2[i]) || !(Matriz1[i] == PARAMAI(Matriz2[i])))
					return false;
			}	// Eu sei que n�o precisa dessas chaves, mas o else _tava_ unindo com o if errado
			else
				if (!(Matriz1[i] == Matriz2[i]))
					return false;
				
		}

		return true;
	}*/
		
	// Compara matrizes e ignora capitaliza��o
	// [Designada para char(s)]
	// � esperado que seja uma matriz terminada com 0 ou '\0', tudo depois de 0 ou '\0' � ignorado
	// e � esperado que elas tenham o MESMO TAMANHO ou o 0 ou '\0' de uma matrix, apare�a antes de a outra acabar
	tipo_fun��o bool CompMatIg(const char* Matriz1, const char* Matriz2)
	{
		for (long long i = 0; Matriz1[i] || Matriz2[i]; i++)
		{
			if (!(Matriz1[i] == Matriz2[i]))
				if ((64 < Matriz1[i] && Matriz1[i] < 123) &&
					(64 < Matriz2[i] && Matriz2[i] < 123))	// Verifica se � um caractere (Letra)
				{
					// � imposs�vel ambos serem verdadeiros, pois "x - 32 = y" nunca vai ser igual a "x = y - 32" (Primeiras duas partes)
					// dessa forma ambos s� podem ser iguais se forem falsos, ent�o se ambos os resultados forem iguais (falso e falso)
					// as letras n�o s�o iguais e se forem diferentes as letras s�o iguais.
					if (!((PARAMAI(Matriz1[i]) == Matriz2[i]) != (Matriz1[i] == PARAMAI(Matriz2[i]))))
						return false;
				}
				else
					return false;
		}

		return true;
	}

	/**********************************************************************************************************************/

	// N�o sei se vale a pena ter "come�o" se eu posso s� somar a "Destino" e subtrair de "TamDest" antes de chamar a fun��o

	template <typename T1, typename T2, typename tamT, typename comT>
	// Copia uma matriz para a outra
	// � esperado que "Origem" seja uma matriz terminada com 0 ou '\0', tudo depois de 0 ou '\0' � ignorado
	// "Origem" deve ser do MESMO TAMANHO OU MAIOR que "Destino"
	// "come�o" � de onde come�ar a escrever em "Destino"
	// *Al�m de copiar a string, ela retorna "true" se a string de "Origem" foi copiada por completo e "false" se o oposto*
	// Pode ser usado a vers�o sem "come�o", pois come�o � o equivalente a somar a "Destino" e subtrair de "TamDest"
	inline_template constexpr bool CopyMat(T1* Destino, T2* Origem, tamT TamDest, comT come�o)
	{
		for (long long i = 0; i < TamDest - come�o; ++i)
		{
			if (!Origem[i])
			{
				Destino[come�o + i] = 0;
				return true;	// Acabou
			}
			Destino[come�o + i] = Origem[i];
		}
		return false;			// Ainda n�o acabou
	}
	
	template <typename T1, typename T2, typename tamT>
	// Copia uma matriz para a outra
	// � esperado que "Origem" seja uma matriz terminada com 0 ou '\0', tudo depois de 0 ou '\0' � ignorado
	// "Origem" deve ser do MESMO TAMANHO OU MAIOR que "Destino"
	// *Al�m de copiar a string, ela retorna "true" se a string de "Origem" foi copiada por completo e "false" se o oposto*
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
		return false;			// Ainda n�o acabou
	}
	
	template <typename T, typename tamT>
	// Copia uma matriz para a outra
	// � esperado que "Origem" seja uma matriz terminada com 0 ou '\0', tudo depois de 0 ou '\0' � ignorado
	// "Origem" deve ser do MESMO TAMANHO OU MAIOR que "Destino"
	// *Al�m de copiar a string, ela retorna "true" se a string de "Origem" foi copiada por completo e "false" se o oposto*
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
		return false;			// Ainda n�o acabou
	}

	/**********************************************************************************************************************/

	// N�o sei se preciso dessa se eu tenho a de baixo

	template <typename T, typename tamT>
	// Diferentemente de std::memset, esse n�o funciona byte a byte, ele vai usar colocar o "valor"
	// em cada espa�o (Como em uma matriz).
	// "tamanho" n�o deve ser o sizeof(matriz) mas a quantidade de elementos, pode ser usado a macro TAMMATRIZ para isso
	inline_template void MatSet(T* Destino, T valor, tamT tamanho)
	{
		for (long long i = 0; i < tamanho; ++i)
			*(Destino + i) = valor;
	}

	template <typename T1, typename T2, typename tamT>
	// Diferentemente de std::memset, esse n�o funciona byte a byte, ele vai usar colocar o "valor"
	// em cada espa�o (Como em uma matriz).
	// "tamanho" n�o deve ser o sizeof(matriz) mas a quantidade de elementos, pode ser usado a macro TAMMATRIZ para isso
	inline_template void MatSet(T1* Destino, T2 valor, tamT tamanho)
	{
		for (long long i = 0; i < tamanho; ++i)
			*(Destino + i) = valor;
	}

	// N�o sei se preciso dessa se eu tenho a de baixo

	template <typename T, typename tamT, typename comT>
	// Diferentemente de std::memset, esse n�o funciona byte a byte, ele vai usar colocar o "valor"
	// em cada espa�o (Como em uma matriz).
	// "tamanho" n�o deve ser o sizeof(matriz) mas a quantidade de elementos, pode ser usado a macro TAMMATRIZ para isso
	// "come�o" de onde come�ar a modificar os valores
	inline_template void MatSet(T* Destino, T valor, tamT tamanho, comT come�o)
	{
		for (long long i = 0 + come�o; i < tamanho; ++i)
			*(Destino + i) = valor;
	}

	
	template <typename T1, typename T2, typename tamT, typename comT>
	// Diferentemente de std::memset, esse n�o funciona byte a byte, ele vai usar colocar o "valor"
	// em cada espa�o (Como em uma matriz).
	// "tamanho" n�o deve ser o sizeof(matriz) mas a quantidade de elementos, pode ser usado a macro TAMMATRIZ para isso
	// "come�o" de onde come�ar a modificar os valores
	inline_template void MatSet(T1* Destino, T2 valor, tamT tamanho, comT come�o)
	{
		for (long long i = 0 + come�o; i < tamanho; ++i)
			*(Destino + i) = valor;
	}

	/**********************************************************************************************************************/

	template <typename T, typename ret>
	// Retorna quantos elementos tem em uma matriz
	// � esperado que seja uma matriz terminada com 0 ou '\0', tudo depois de 0 ou '\0' � ignorado.
	// Ela n�o considera o caractere nulo (0 ou '\0')
	inline_template constexpr ret QuantEleMat(T* matriz)
	{
		ret quantidade = 0;

		for (; matriz[quantidade]; quantidade++);

		/*while (matriz[quantidade])
			++quantidade;*/

		return quantidade;
	}

	template <typename T1, typename tamT, typename ret>
	// Retorna quantos elementos tem em uma matriz at� o 0 ou '\0' mais pr�ximo
	// Usar essa fun��o caso n�o tenha certeza se a matriz est� cheia ou n�o � terminada com 0 ou '\0',
	// tudo depois de 0 ou '\0' � ignorado.
	// Ela n�o considera o caractere nulo (0 ou '\0')
	inline_template constexpr ret QuantEleMat(T1* matriz, tamT tam)
	{
		ret quantidade = 0;

		while (matriz[quantidade] && quantidade < tam)
			++quantidade;

		return quantidade;
	}

	template <typename T1, typename tamT, typename ret>
	// Retorna quantos elementos tem em uma matriz at� o 0 ou '\0' mais pr�ximo
	// Usar essa fun��o caso n�o tenha certeza se a matriz est� cheia ou n�o � terminada com 0 ou '\0',
	// tudo depois de 0 ou '\0' � ignorado.
	// "estado" � (true) se est� cheia ou (false) se n�o cheia
	// Ela n�o considera o caractere nulo (0 ou '\0')
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
