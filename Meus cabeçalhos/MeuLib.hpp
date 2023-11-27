#pragma once

// TODO, não gosto de que tudo que faço aqui tenho que mudar em "undefs.hpp" tbm
// Talvez, em vez de um arquivo pra isso eu podia só usar uma região, assim fica mais fácil
// Definições para modificar as funcionalidades da biblioteca
#include "Libs\defines.hpp"



/*
* Macros que eu uso comumente:
* 
* #define NAMETYPEDEF
* #define MEU_CRT
* (#define EXTERNO)
* 
*/

#pragma region extra, que eu tenho que tirar daqui
// Interessante
// 
//SYSTEM_INFO info;
//GetSystemInfo(&info);
//printf(
//	"PageSize: %d bytes. Area a alocar: %llu\n",
//	info.dwPageSize, sizeof(Area));
// 
/***************************************************/
// 
// // tera alocado um multiplo de pagesize?
//size_t page = 0;
//if (sizeof(Area) % info.dwPageSize == 0)
//page = sizeof(area);
//else
//page = (1 + sizeof(area) / info.dwPageSize) * info.dwPageSize;
//printf(
//	"VirtualAlloc() pode alocar %llu paginas\n",
//	page / info.dwPageSize);
/***************************************************/
//void* operator new(size_t tam)
//{
//
//}
//
//void operator delete(void*)
//{
//
//}
#pragma endregion

#pragma region GUIA
/****************************************************************************/
//////////////////////////  "ENTRE ASPAS UM GUIA"  ///////////////////////////
/****************************************************************************/
/*
* Ao usar o EXTERNO:
* Caso eu declare EXTERNO, na UT que eu queira usar como referência para as definições
* não pode ter funções "constexpr", isso significa que a UT de referência precisa ter a
* macro NCONSTEXPR nela pra não dar problema de "simbolo externo não resolvido".
* 
* Isso pode circulado caso a função em questão seja usada na UT das definições.
* O porque disso? Eu não sei, mas é uma maneira de "circular" o problema, por mais que curativos não sejam legais.
*/

// Eu recomendo que esse seja o primeiro include ou o segundo (sendo o primeiro bibliotecas externas que uso aqui
// entretando não incluo, que no caso é <windows.h>).
// Isto é recomendado pois os defines do usuário e os usados dentro daqui são des-definidos ao fim do cabeçalho.

/*
* TODO TODO TODO
* !!!AO CRIAR NOVAS FUNÇÕES!!!
* Caso ela *NÃO SEJA template* eu devou envolver o bloco de código com:

_tipo_ nomefunção()
#ifdef EXTERNO
		;
#else
{
	// Bloco de código;
}
#endif

* É meio chato fazer isso, mas prefiro fazer isso do que ter todas as funções não template com inline ou static.
* SUPOSTAMENTE o inline não lineriza, mas faz com que todas as chamadas sejam ligadas para um função,
* entretanto eu não confio que não vai ser lineralizada quando eu não quero. E eu não quero static, pq eu não quero
* uma cópia da função pra cada UT (Unidade de tradução).
* 
* Nome de funções eu não uso 'ç'
*/
#pragma endregion


#ifdef MEU_CRT
#include "meu_msvc.c"
#endif

// Se quiser que loops usem long long
#ifdef LL_LOOP
typedef unsigned long long loop_tipo;
#else
typedef unsigned int loop_tipo;
#endif

// Sim, baita preguiça
#ifdef MEU_ARCAICO
#define Meu meu
#defien QuantEleMat MatTam
#endif

namespace meu {

	#include "Libs\MeuMat.hpp"
	#include "Libs\MeuExtra.hpp"
	#include "Libs\Estruturas.hpp"
	//#include 
}



// Usar isso para não ter que usar namespaces para typedefs
#ifdef NAMETYPEDEF
using meu::uchar;
using meu::ushort;
using meu::uint;
using meu::ulong;
using meu::ulong_long;

using meu::ptrtam;
using meu::voidptr;

using meu::byte;

using meu::COR;
#endif

// Undefs usados em "defines.hpp" + definidos pelo usuário
#include "Libs\undefs.hpp"
