#pragma once

// Caso queira que cada UT tenha sua pr�pria defini��o
#ifdef STATICFUNC
#define tipo_funcao static
#else
#define tipo_fun��o inline
#endif

// Pois "__forceinline" � espec�fico de ms vs
//#ifdef FORCEINLINE	// Ironicamente FORCEINLINE j� � usado em "windows.h"
#ifdef MEUFORCEINLINE
#define tipo_inline __forceinline
#else
#define tipo_inline inline
#endif

// Se as fun��es template devem ser inline, __forceinline ou n�o
#ifdef FORCINLTEMP
#define inline_template __forceinline
#else

// J� que a maior parte do tempo eu uso inline template, procurar por N�O definido � melhor
#ifndef NAOINLTEMP
#define inline_template inline
#else
#define inline_template
#endif

#endif
