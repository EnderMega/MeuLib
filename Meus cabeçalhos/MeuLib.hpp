#pragma once

// TODO, n�o gosto de que tudo que fa�o aqui tenho que mudar em "undefs.hpp" tbm
// Defini��es para modificar as funcionalidades da biblioteca
#include "Libs\defines.hpp"



namespace Meu {

	#include "Libs\MeuMat.hpp"
	#include "Libs\MeuExtra.hpp"
	//#include 
}



// Usar isso para n�o ter que usar namespaces para typedefs
#ifdef NAMETYPEDEF
using Meu::uchar;
using Meu::ushort;
using Meu::uint;
using Meu::ulong;
using Meu::ulong_long;
#endif

// Undefs usa em "defines.hpp" + definidos pelo usu�rio
#include "Libs\undefs.hpp"
