/*
* § O porque desse arquivo §
* Esse é o pináculo de esforço pra nada.
* O compilador "tenta" OTIMIZAR inicialização de matrizes usando memset(), tipo:
* 
* char mat[100] = {};
* 
* E caso não desejamos linkar a .dll que possui memset() temos que implementar a nossa própria.
* 
* VISUAL STUDIOS (MSVC):
* AVISO, caso ele reclame, não pode ter "otimização do programa inteiro" /GL, pra destivar isso vai em:
* C/C++ -> Otimização -> Otimização do programa inteiro = não
*/

/*
* Meus recursos sobre CRT:
* 
* Handmade Hero (network): https://hero.handmade.network/forums/code-discussion/t/94-guide_-_how_to_avoid_c_c++_runtime_on_windows
*	> Video do Casey lendo o link de cima: https://www.youtube.com/watch?v=sE4tUVaxiV0
* Minha resposta no Stackoverflow: https://stackoverflow.com/questions/62746429/how-to-disable-crt-completely
* CRT-free in 2023: tips and tricks: https://nullprogram.com/blog/2023/02/15/
*	> Esse é interessante pois ele fala de MSVC, clang e gcc/g++
*	> Ele fala do problema de loops infinitos de `memset()`
* Memset sendo gerado sem você pedir: https://www.reddit.com/r/C_Programming/comments/vgnuzv/when_the_c_compiler_generates_memset_calls_behind/
*/

extern "C"
{
	// "Float used"

#ifdef EXTERNO
	extern int _fltused;
#else
	int _fltused/* = 0x9875*/;
#endif
	
	//int _fltused;

//#ifdef _MSVC_LANG
//#pragma function(memset) // ESPECÍFICO MSVC
//#else
//__attribute((section(".text.memset")))	// GCC/G++
//#endif
	// Não use esse normalmente, está aqui apena pela obrigação do compilador.
	void* memset(void* ptr, int val, size_t tam)
#ifdef EXTERNO
	;
#else
	{
		char* dest = (char*)ptr;
	
		while (tam--)
			*dest++ = (char)val;
	
		return dest;
	}
#endif
}


/*
* Copiei do código de MEMZ
extern "C"
{
	int _fltused;

#ifdef _M_IX86 // following functions are needed only for 32-bit architecture

	__declspec(naked) void _ftol2()
	{
		__asm
		{
			fistp qword ptr[esp - 8]
			mov   edx, [esp - 4]
			mov   eax, [esp - 8]
			ret
		}
	}

	__declspec(naked) void _ftol2_sse()
	{
		__asm
		{
			fistp dword ptr[esp - 4]
			mov   eax, [esp - 4]
			ret
		}
	}

#if 0 // these functions are needed for SSE code for 32-bit arch, TODO: implement them
	__declspec(naked) void _dtol3()
	{
		__asm
		{
		}
	}


	__declspec(naked) void _dtoui3()
	{
		__asm
		{
		}
	}


	__declspec(naked) void _dtoul3()
	{
		__asm
		{
		}
	}


	__declspec(naked) void _ftol3()
	{
		__asm
		{
		}
	}


	__declspec(naked) void _ftoui3()
	{
		__asm
		{
		}
	}


	__declspec(naked) void _ftoul3()
	{
		__asm
		{
		}
	}


	__declspec(naked) void _ltod3()
	{
		__asm
		{
		}
	}


	__declspec(naked) void _ultod3()
	{
		__asm
		{
		}
	}
#endif

#endif

}
*/