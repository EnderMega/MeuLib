#pragma once

// TODO, não gosto de que tudo que faço aqui tenho que mudar em "undefs.hpp" tbm
// Definições para modificar as funcionalidades da biblioteca
#include "Libs\defines.hpp"



namespace Meu {

	#include "Libs\MeuMat.hpp"
	#include "Libs\MeuExtra.hpp"
	//#include 
}



// Usar isso para não ter que usar namespaces para typedefs
#ifdef NAMETYPEDEF
using Meu::uchar;
using Meu::ushort;
using Meu::uint;
using Meu::ulong;
using Meu::ulong_long;
#endif

// Undefs usa em "defines.hpp" + definidos pelo usuário
#include "Libs\undefs.hpp"
