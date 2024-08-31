#pragma once

/*==================================================================================*/
/*Nem todos as estruturas estão aqui,
* tipo Vec2,3,4; etc.
* 
* Nem uma dessa estruturas inicializam outras estruturas.
*/
/*==================================================================================*/

/*
* Passa um objeto como cópia, para uma função, com uma matriz é diferente de passar com um ponteiro.
* Normalmente passar uma matriz ou ponteiro não tem diferença.

*   Vou anotar aqui porque eu achei legal. Se eu passar uma matriz para uma função, ela vai decair para ponteiro
* e vai modificar o valor da matriz de verdade, agora se eu passar um objeto que contem uma matriz, ele não
* vai modificar a matriz do objeto verdadeiro.
*   E se eu passar um objeto como cópia, que possui um ponteiro, só vai copiar o valor do ponteiro e não criar
* uma copia da matriz que ele aponta.
*   Finalizando, se eu passo uma matriz ou ponteiro para uma função qualquer modificação dentro da função afeta a
* matriz/ponteiro real; mas se eu passar um objeto que possui uma matriz, a matriz vai ser copiada, mudanças na matriz
* dentro da função não vai causar mudanças no objeto passado; e por último, se eu passar um objeto que possui um ponteiro,
* seja para um valor ou para uma matriz alocada dinâmicamente, a função só copia o valor do ponteiro e não uma copia do valor/matriz,
* assim qualquer mudança nesse ponteiro afetara o valor/matriz real.
*/

#pragma warning( push )
#pragma warning( disable : 26495 )
// Matriz estática
// Não é inicializada
template<typename T, uint tam>
struct matriz {

	T Dados[tam];

	//const uint tamanho = tam;
	
	// Único motivo para isso é para que possa inicializar a matriz usando colchetes, e como é constexpr deve ser de boa,
	// e além disso, eu não ter que manter uma variável "tam"
	constexpr uint tamanho() const { return tam; };

	// Esses só servem para quando "Dados" é privado, oque eu acho estúpido.

	/*T* Dados() { return Dados };
	const T* Dados() const { return Dados };

	T& operator[](uint index) { return Dados[index]; };
	const T& operator[](uint index) const { return Dados[index]; };*/

	void Encher(T valor)
	{
		for (uint i = 0; i < tam; i++)
			Dados[i] = valor;
	}

	void Zerar()
	{
		for (uint i = 0; i < tam; i++)
			Dados[i] = 0;
	}

	// Bem tosco fazer em funções e não macros, mas em fim:
	/*===================================================*/

	// mat.Dados[0] = valor;
	inline void Comeco(T valor) { Dados[0] = valor; }

	// mat.Dados[mat.tamanho - 1] = valor;
	inline void Fim(T valor) { Dados[tam - 1] = valor; }

	/*===================================================*/

	void Trocar(matriz<T, tam>& mat)
	{
		T temp;

		for (uint i = 0; i < tam; i++)
		{
			//Meu::Trocar(Dados[i], mat.Dados[i]);
			temp = mat.Dados[i];

			mat.Dados[i] = Dados[i];
			Dados[i] = temp;
		}
	}
	// Achei esse negócio de referencia legal.

	void Trocar(matriz<T, tam>* mat)
	{
		T temp;

		for (uint i = 0; i < tam; i++)
		{
			//Meu::Trocar(Dados[i], mat->Dados[i]);
			temp = mat->Dados[i];

			mat->Dados[i] = Dados[i];
			Dados[i] = temp;
		}
	}

	// Não, não vou dar sobrecarregar operadores como por exemplo []

	// Operadores de comparação:

	bool operator==(matriz<T, tam>& comp) const
	{
		for (uint i = 0; i < tam; i++)
		{
			if (Dados[i] == comp.Dados[i])
				continue;

			return false;
		}

		return true;
	}

	bool operator!=(matriz<T, tam>& comp) const
	{
		for (uint i = 0; i < tam; i++)
		{
			if (Dados[i] != comp.Dados[i])
				continue;

			return false;
		}

		return true;
	}

	bool operator<(matriz<T, tam>& comp) const
	{
		for (uint i = 0; i < tam; i++)
		{
			if (Dados[i] < comp.Dados[i])
				continue;

			return false;
		}

		return true;
	}

	bool operator<=(matriz<T, tam>& comp) const
	{
		for (uint i = 0; i < tam; i++)
		{
			if (Dados[i] <= comp.Dados[i])
				continue;

			return false;
		}

		return true;
	}

	bool operator>(matriz<T, tam>& comp) const
	{
		for (uint i = 0; i < tam; i++)
		{
			if (Dados[i] > comp.Dados[i])
				continue;

			return false;
		}

		return true;
	}

	bool operator>=(matriz<T, tam>& comp) const
	{
		for (uint i = 0; i < tam; i++)
		{
			if (Dados[i] >= comp.Dados[i])
				continue;

			return false;
		}

		return true;
	}

	// Operadores de assinalação:

	void operator=(const matriz<T, tam>& mat)
	{
		for (uint i = 0; i < tam; i++)
			Dados[i] = mat.Dados[i];
	}
	void operator=(const matriz<T, tam>&& mat) noexcept
	{
		for (uint i = 0; i < tam; i++)
			Dados[i] = mat.Dados[i];
	}
	void operator=(T* ptr)
	{
		for (uint i = 0; i < tam; i++)
			Dados[i] = ptr[i];
	}

	void operator+=(matriz<T, tam>& mat)
	{
		for (uint i = 0; i < tam; i++)
			Dados[i] += mat.Dados[i];
	}
	void operator+=(matriz<T, tam>&& mat)
	{
		for (uint i = 0; i < tam; i++)
			Dados[i] += mat.Dados[i];
	}

	void operator-=(matriz<T, tam>& mat)
	{
		for (uint i = 0; i < tam; i++)
			Dados[i] -= mat.Dados[i];
	}
	void operator-=(matriz<T, tam>&& mat)
	{
		for (uint i = 0; i < tam; i++)
			Dados[i] -= mat.Dados[i];
	}

	void operator*=(matriz<T, tam>& mat)
	{
		for (uint i = 0; i < tam; i++)
			Dados[i] *= mat.Dados[i];
	}
	void operator*=(matriz<T, tam>&& mat)
	{
		for (uint i = 0; i < tam; i++)
			Dados[i] *= mat.Dados[i];
	}

	void operator/=(matriz<T, tam>& mat)
	{
		for (uint i = 0; i < tam; i++)
			Dados[i] /= mat.Dados[i];
	}
	void operator/=(matriz<T, tam>&& mat)
	{
		for (uint i = 0; i < tam; i++)
			Dados[i] /= mat.Dados[i];
	}

	// Operadores matemáticos:

	/*matriz<T, tam> operator+(matriz<T, tam> mat)
	{
		for (uint i = 0; i < tam; i++)
			mat.Dados[i] += Dados[i];

		return mat;
	}

	matriz<T, tam> operator-(matriz<T, tam> mat)
	{
		for (uint i = 0; i < tam; i++)
			mat.Dados[i] -= Dados[i];

		return mat;
	}

	matriz<T, tam> operator*(matriz<T, tam> mat)
	{
		for (uint i = 0; i < tam; i++)
			mat.Dados[i] *= Dados[i];

		return mat;
	}

	matriz<T, tam> operator/(matriz<T, tam> mat)
	{
		for (uint i = 0; i < tam; i++)
			mat.Dados[i] /= Dados[i];

		return mat;
	}*/
};

// Se eu usasse esses argumentos de template, muitas funções não funcionaram, pois o template importava para as funções

// Matriz dinâmica
// Memória não precisa ser zerada
template<typename T/*, ulong_long tam = 0, uint const_crescimento = 10, typename tipoTam = uint*/>
struct matdin {

	// TODO, testar quantas páginas foram alocadas em vez de só testar o "tamanho" alocado.

	// Eu deixo tudo publico pois é bem brega ter que usar uma função para ler uma variável

	uint tamanho = /*tam*/0;				  // Tamanho atual, não modificar fora da classe
	uint const_cres = /*const_crescimento*/10;// Esse pode ser modificado caso queira, TODO, normalmente se duplica o tamanho ou soma a metade
	uint pos = 0;							  // Posição do último elemento, não modificar fora da classe, se = 0 então está vazio
	// Pra quem for ler essa classe, faz mais sentido ler "pos" como apontando para o próximo endereço
	
	T* ptrMem = nullptr;

	// **QUANTO** aumentar e não PARA QUANTO "mudar" o tamanho
	void Crescer(uint tTam)
	{
		T* ptrTemp = ptrMem;
		tamanho += tTam;

		ptrMem = (T*)VirtualAlloc(0, tamanho/* + tTam*/, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		for (uint i = 0; i < pos; i++)
			ptrMem[i] = ptrTemp[i];

		VirtualFree(ptrTemp, 0, MEM_RELEASE);
	}

	// Para qual tamanho dever crescer ou diminuir
	void MudarTam(uint tTam)
	{
		T* ptrTemp = ptrMem;
		tamanho = tTam;

		ptrMem = (T*)VirtualAlloc(0, tTam, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		// Se o novo tamanho for menor do que a quantidade de elementos, vamos ignorar ao resto.
		// Preferi criar uma nova variável do que "recalcular" toda vez no loop.
		uint loop = tTam < pos ? tTam : pos;
		for (uint i = 0; i < loop; i++)
			ptrMem[i] = ptrTemp[i];

		VirtualFree(ptrTemp, 0, MEM_RELEASE);
	}

	// Ajusta o tamanho da matriz para a quantidade de elementos no momento (pos)
	void AjustarTam()
	{
		T* ptrTemp = ptrMem;

		ptrMem = (T*)VirtualAlloc(0, pos, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		for (uint i = 0; i < pos; i++)
			ptrMem[i] = ptrTemp[i];

		VirtualFree(ptrTemp, 0, MEM_RELEASE);

		tamanho = pos;
	}

	// Adicionar na última posição ".apend()"
	void Adicionar(const T& valor)	// const reference para caso tipos mais avançados seja usados
	{
		if (tamanho == pos)
		{
			//Crescer(const_cres);
			T* ptrTemp = ptrMem;

			ptrMem = (T*)VirtualAlloc(0, tamanho + const_cres, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			for (uint i = 0; i < pos; i++)
				ptrMem[i] = ptrTemp[i];

			VirtualFree(ptrTemp, 0, MEM_RELEASE);

			tamanho += const_cres;
		}

#pragma warning( push )
#pragma warning( disable : 6011 )

		ptrMem[pos] = valor;
		//ptrMem[pos++] = valor;	// pós incremento

#pragma warning( pop )

		++pos;
	}
	
	// Adiciona vários valores de uma vez na(s) última(s) posição(ões)
	void Adicionar(T* valor, uint quant)
	{
		// Não causa nem um problema ser zero, mas assim é mais eficiente
		if (!quant)
			return;
		
		if (/*(tamanho == pos) || */(tamanho - pos < quant))
		{
			// Crescer(quant < const_cres ? const_cres : quant);
			T* ptrTemp = ptrMem;
			tamanho += quant < const_cres ? const_cres : quant;

			ptrMem = (T*)VirtualAlloc(0, tamanho/* + (quant < const_cres ? const_cres : quant)*/, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			for (uint i = 0; i < pos; i++)
				ptrMem[i] = ptrTemp[i];

			VirtualFree(ptrTemp, 0, MEM_RELEASE);
		}

		CopyMat(ptrMem + pos, valor, quant);

		pos += quant;
	}

	// Remove último valor
	void Pop()
	{
		if (!pos)
			return;

		ptrMem[pos - 1] = 0;

		--pos;
	}

	// Muda "pos" para a última posição, assim "Acrescentar()" vai adicionar depois de tudo
	void Encher(const T& valor)
	{
		for (uint i = 0; i < tamanho; i++)
			ptrMem[i] = valor;

		pos = tamanho;
	}

	void Zerar()
	{
		for (uint i = 0; i < tamanho; i++)
			ptrMem[i] = 0;
	}

	// Bem tosco fazer em funções e não macros, mas em fim:
	/*===================================================*/

	// mat.ptrMem[0] = valor;
	//inline void Comeco(T valor) { ptrMem[0] = valor; }

	// mat.ptrMem[mat.tamanho - 1] = valor;
	// Não acompanha a posição do último colocado ".Acrescentar()"
	//inline void Fim(T valor) { ptrMem[tamanho - 1] = valor; }


	// Matriz de entrada deve ser do mesmo tamanho ou maior
	// Se for maior, o resto vai ficar lá
	void Trocar(matdin& mat)
	{
		T temp;

		for (uint i = 0; i < tamanho; i++)
		{
			//Meu::Trocar(ptrMem[i], mat.ptrMem[i]);
			temp = mat.ptrMem[i];
			mat.ptrMem[i] = ptrMem[i];
			ptrMem[i] = temp;
		}
	}
	
	// Matriz de entrada deve ser do mesmo tamanho ou maior
	// Se for maior, o resto vai ficar lá
	void Trocar(matdin* mat)
	{
		T temp;

		for (uint i = 0; i < tamanho; i++)
		{
			//Meu::Trocar(ptrMem[i], mat->ptrMem[i]);
			temp = mat->ptrMem[i];
			mat->ptrMem[i] = ptrMem[i];
			ptrMem[i] = temp;
		}
	}

	// Construtor para passar o tamanho
	matdin(uint tam) : tamanho(tam) {}
	// Construtor que não faz nada
	matdin() {}

	// Simplesmente libera a memória
	~matdin() { VirtualFree(ptrMem, 0, MEM_RELEASE); }

	// Operadores de comparação:

	// Matriz de entrada deve ser do mesmo tamanho ou maior
	bool operator==(matdin<T>& comp) const
	{
		for (uint i = 0; i < tamanho; i++)
		{
			if (ptrMem[i] == comp.ptrMem[i])
				continue;

			return false;
		}

		return true;
	}

	// Matriz de entrada deve ser do mesmo tamanho ou maior
	bool operator!=(matdin<T>& comp) const
	{
		for (uint i = 0; i < tamanho; i++)
		{
			if (ptrMem[i] != comp.ptrMem[i])
				continue;

			return false;
		}

		return true;
	}

	// Matriz de entrada deve ser do mesmo tamanho ou maior
	bool operator<(matdin<T>& comp) const
	{
		for (uint i = 0; i < tamanho; i++)
		{
			if (ptrMem[i] < comp.ptrMem[i])
				continue;

			return false;
		}

		return true;
	}

	// Matriz de entrada deve ser do mesmo tamanho ou maior
	bool operator<=(matdin<T>& comp) const
	{
		for (uint i = 0; i < tamanho; i++)
		{
			if (ptrMem[i] <= comp.ptrMem[i])
				continue;

			return false;
		}

		return true;
	}

	// Matriz de entrada deve ser do mesmo tamanho ou maior
	bool operator>(matdin<T>& comp) const
	{
		for (uint i = 0; i < tamanho; i++)
		{
			if (ptrMem[i] > comp.ptrMem[i])
				continue;

			return false;
		}

		return true;
	}

	// Matriz de entrada deve ser do mesmo tamanho ou maior
	bool operator>=(matdin<T>& comp) const
	{
		for (uint i = 0; i < tamanho; i++)
		{
			if (ptrMem[i] >= comp.ptrMem[i])
				continue;

			return false;
		}

		return true;
	}

	// Operadores de assinalação:

	// Se o tamanho da matriz atual for maior, ou menor, ela vai muda para ser igual a da entrada
	// Copia os valores a posição
	void operator=(matdin<T>& mat)
	{
		if (tamanho != mat.tamanho)
		{
			// Como eu vou simplesmente copio da outra para essa eu não tenho que me importar com os dados
			VirtualFree(ptrMem, 0, MEM_RELEASE);
			ptrMem = (T*)VirtualAlloc(0, mat.tamanho, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			tamanho = mat.tamanho;
		}

#pragma warning( push )
#pragma warning( disable : 6011 )
#pragma warning( disable : 6386 )

		for (uint i = 0; i < tamanho; i++)
			ptrMem[i] = mat.ptrMem[i];

#pragma warning( pop )

		pos = mat.pos;
	}

	// Matriz de entrada deve ser do mesmo tamanho ou maior
	void operator+=(matdin<T>& mat)
	{
		for (uint i = 0; i < tamanho; i++)
			ptrMem[i] += mat.ptrMem[i];
	}
	
	// Matriz de entrada deve ser do mesmo tamanho ou maior
	void operator-=(matdin<T>& mat)
	{
		for (uint i = 0; i < tamanho; i++)
			ptrMem[i] -= mat.ptrMem[i];
	}
	
	// Matriz de entrada deve ser do mesmo tamanho ou maior
	void operator*=(matdin<T>& mat)
	{
		for (uint i = 0; i < tamanho; i++)
			ptrMem[i] *= mat.ptrMem[i];
	}
	
	// Matriz de entrada deve ser do mesmo tamanho ou maior
	void operator/=(matdin<T>& mat)
	{
		for (uint i = 0; i < tamanho; i++)
			ptrMem[i] /= mat.ptrMem[i];
	}

	// Operadores matemáticos:

	/*matdin<T> operator+(matdin<T>& mat)
	{
		matdin<T, tamanho> retorno;

		for (uint i = 0; i < tamanho; i++)
			retorno.ptrMem[i] = ptrMem[i] + mat.ptrMem[i];

		return retorno;
	}
	
	matdin<T> operator-(matdin<T>& mat)
	{
		matdin<T, tamanho> retorno;

		for (uint i = 0; i < tamanho; i++)
			retorno.ptrMem[i] = ptrMem[i] - mat.ptrMem[i];

		return retorno;
	}
	
	matdin<T> operator*(matdin<T>& mat)
	{
		matdin<T, tamanho> retorno;

		for (uint i = 0; i < tamanho; i++)
			retorno.ptrMem[i] = ptrMem[i] * mat.ptrMem[i];

		return retorno;
	}
	
	matdin<T> operator/(matdin<T>& mat)
	{
		matdin<T, tamanho> retorno;

		for (uint i = 0; i < tamanho; i++)
			retorno.ptrMem[i] = ptrMem[i] / mat.ptrMem[i];

		return retorno;
	}*/
};

// Lista
// "linked list"
template<typename T>
struct lista {

	T dado;
	lista* prox_nodo = nullptr;
	
	// Para todas as funções relacionadas as "...Fim", cabeca serve como um ponteiro temporário,
	// já nos outros tem que ser a original.
	
	// Caso esteja começando uma linked list, a cabeca deve ser igual a "nullptr/0"
	void adicionarNodo(lista** cabeca, T dado)
	{
		lista* tempNodo = (lista*)VirtualAlloc(0, sizeof(lista), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

#pragma warning( push )
#pragma warning( disable : 6011 )
		tempNodo->dado = dado;
#pragma warning( pop )
		tempNodo->prox_nodo = *cabeca;

		*cabeca = tempNodo;
	}
	
	void adicionarNodo(lista** cabeca, lista* nodo)
	{
		nodo->prox_nodo = *cabeca;
		*cabeca = nodo;
	}

	void adicionarFim(lista* cabeca, T dado)
	{
		for (; cabeca->prox_nodo;) { cabeca = cabeca->prox_nodo; }

		// Não vou testar se é null

		cabeca->prox_nodo = (lista*)VirtualAlloc(0, sizeof(lista), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#pragma warning( push )
#pragma warning( disable : 6011 )
		cabeca->prox_nodo->dado = dado;
#pragma warning( pop )
	}
	
	void adicionarFim(lista* cabeca, lista* nodo)
	{
		for (; cabeca->prox_nodo;) { cabeca = cabeca->prox_nodo; }

		cabeca->prox_nodo = nodo;
	}

	// Vai adicionar depois do nodo indicado
	void adicionarMeio(lista* ref, T dado)
	{
		lista* tempPtr = (lista*)VirtualAlloc(0, sizeof(lista), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		tempPtr->dado = dado;
		tempPtr->prox_nodo = ref->prox_nodo;
		ref->prox_nodo = tempPtr;
	}

	void adicionarMeio(lista* ref, lista* nodo)
	{
		nodo->prox_nodo = ref->prox_nodo;
		ref->prox_nodo = nodo;
	}

	void excNodo(lista** nodo)
	{
		lista* tempPtr = (*nodo)->prox_nodo;

		VirtualFree(*nodo, 0, MEM_RELEASE);

		*nodo = tempPtr;
	}

	void excFim(lista* cabeca)
	{
		for (; cabeca->prox_nodo->prox_nodo;) { cabeca = cabeca->prox_nodo; }

		VirtualFree(cabeca->prox_nodo, 0, MEM_RELEASE);

		cabeca->prox_nodo = nullptr;
	}

	void excComeco(lista** cabeca)
	{
		lista* tempPtr = (*cabeca)->prox_nodo;

		VirtualFree(*cabeca, 0, MEM_RELEASE);

		*cabeca = tempPtr;
	}
};

template<typename T>
struct arvore{

	T dado;
	arvore *direita, *esquerda;

	void novosGalho(T dados1, T dados2)
	{
		arvore* tempPtr = (arvore*)VirtualAlloc(0, 2 * sizeof(arvore), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		arvore* tempPtr2 = tempPtr + sizeof(arvore);

		tempPtr->dado = dados1;
		tempPtr2->dado = dados2;
		direita = tempPtr;
		esquerda = tempPtr2;
	}
};