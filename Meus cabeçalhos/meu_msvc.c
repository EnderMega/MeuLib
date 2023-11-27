/*
* § O porque desse arquivo §
* Esse é o pináculo de esforço pra nada.
* O compilador "tenta" OTIMIZAR inicialização de matrizes usando memset(), tipo:
* 
* char mat[100] = {};
* 
* E caso não desejamos linkar a .dll que possui memset() temos que implementar a nossa própria.
* 
* AVISO, caso ele reclame, não pode ter "otimização do programa inteiro" /GL, pra destivar isso vai em:
* C/C++ -> Otimização -> Otimização do programa inteiro = não
*/

extern "C"
{
#ifdef EXTERNO
	extern int _fltused;
#else
	int _fltused/* = 0x9875*/; 
#endif
	
	//int _fltused;

#pragma warning( push )
#pragma warning( disable : 28251 )
#pragma warning( disable : 6001 )

#pragma function(memset)
	// Por chatices do compilador eu tenho que implementar meu próprio memset
	// Não use esse normalmente, está aqui apena pela obrigação do compilador.
	void* __cdecl memset(void* destino, int val, size_t tam)
#ifdef EXTERNO
	;
#else
	{
		char* dest = (char*)destino;
	
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


#pragma warning( pop )