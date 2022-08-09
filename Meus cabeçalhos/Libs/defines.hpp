#pragma once

// Caso queira que cada UT tenha sua própria definição
#ifdef STATICFUNC
#define tipo_funcao static
#else
#define tipo_função inline
#endif

// Pois "__forceinline" é específico de ms vs
//#ifdef FORCEINLINE	// Ironicamente FORCEINLINE já é usado em "windows.h"
#ifdef MEUFORCEINLINE
#define tipo_inline __forceinline
#else
#define tipo_inline inline
#endif

// Se as funções template devem ser inline, __forceinline ou não
#ifdef FORCINLTEMP
#define inline_template __forceinline
#else

// Já que a maior parte do tempo eu uso inline template, procurar por NÃO definido é melhor
#ifndef NAOINLTEMP
#define inline_template inline
#else
#define inline_template
#endif

#endif
