#pragma once

// TODO, n�o gosto de que tudo que fa�o aqui tenho que mudar em "undefs.hpp" tbm
// Talvez, em vez de um arquivo pra isso eu podia s� usar uma regi�o, assim fica mais f�cil
// Defini��es para modificar as funcionalidades da biblioteca
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
* Caso eu declare EXTERNO, na UT que eu queira usar como refer�ncia para as defini��es
* n�o pode ter fun��es "constexpr", isso significa que a UT de refer�ncia precisa ter a
* macro NCONSTEXPR nela pra n�o dar problema de "simbolo externo n�o resolvido".
* 
* Isso pode circulado caso a fun��o em quest�o seja usada na UT das defini��es.
* O porque disso? Eu n�o sei, mas � uma maneira de "circular" o problema, por mais que curativos n�o sejam legais.
*/

// Eu recomendo que esse seja o primeiro include ou o segundo (sendo o primeiro bibliotecas externas que uso aqui
// entretando n�o incluo, que no caso � <windows.h>).
// Isto � recomendado pois os defines do usu�rio e os usados dentro daqui s�o des-definidos ao fim do cabe�alho.

/*
* TODO TODO TODO
* !!!AO CRIAR NOVAS FUN��ES!!!
* Caso ela *N�O SEJA template* eu devou envolver o bloco de c�digo com:

_tipo_ nomefun��o()
#ifdef EXTERNO
		;
#else
{
	// Bloco de c�digo;
}
#endif

* � meio chato fazer isso, mas prefiro fazer isso do que ter todas as fun��es n�o template com inline ou static.
* SUPOSTAMENTE o inline n�o lineriza, mas faz com que todas as chamadas sejam ligadas para um fun��o,
* entretanto eu n�o confio que n�o vai ser lineralizada quando eu n�o quero. E eu n�o quero static, pq eu n�o quero
* uma c�pia da fun��o pra cada UT (Unidade de tradu��o).
* 
* Nome de fun��es eu n�o uso '�'
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

// Sim, baita pregui�a
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



// Usar isso para n�o ter que usar namespaces para typedefs
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

// Undefs usados em "defines.hpp" + definidos pelo usu�rio
#include "Libs\undefs.hpp"
