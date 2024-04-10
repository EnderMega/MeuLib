// Pode usar tanto ASCII como UTF-16 livremente
// Primeiramente chama a fun��o `InicializarConsole()` e depois pode usar normalmente.
struct meuconsole {

	HANDLE saida;
	HANDLE entrada;
	DWORD bytes;

	// Ao ler a entrada, se todos os bytes n�o foram lidos (removidos) fica algums no buffer do console. Assim, na
	// pr�xima vez que ler vair receber esses bytes e sair sem deixar o usu�rio digitar.
	bool deixar_restante = false;

	DWORD vmax_tam;	// Por padr�o recebe tudo, pode mudar isto para o padr�o do m�ximo que recebe
	// N�o adianta `usar vmax_tam = x`, pois, _por algum motivo_, por estarmos declarando o objeto de forma globa o valor fica 0.

	// Inicializar o meu console
	// ret = 0; tudu certo. ret = 1; tudu erradu.
	// ret = 2; saida deu errado. ret = 3; entrada deu errado.
	// Caso der errado usar `GetLastError()` [padr�o do windows.h] para ver o c�digo de erro.
	char InicializarConsole()
	{
		saida = GetStdHandle(STD_OUTPUT_HANDLE);
		entrada = GetStdHandle(STD_INPUT_HANDLE);

		vmax_tam = 1024;

		if (saida == INVALID_HANDLE_VALUE && entrada == INVALID_HANDLE_VALUE)
			return 1;
		else if (saida == INVALID_HANDLE_VALUE)
			return 2;
		else if (entrada == INVALID_HANDLE_VALUE)
			return 3;

		return 0;
	}

	void cls()
	{
		COORD tl = { 0,0 };
		CONSOLE_SCREEN_BUFFER_INFO s;
		GetConsoleScreenBufferInfo(saida, &s);
		DWORD written, cells = s.dwSize.X * s.dwSize.Y;
		FillConsoleOutputCharacterW(saida, ' ', cells, tl, &written);
		FillConsoleOutputAttribute(saida, s.wAttributes, cells, tl, &written);
		SetConsoleCursorPosition(saida, tl);
	}

	// Um sinples "esperar um enter", Melhor do que usar um Sleep(~)
	void enter()
	{
		char tmep;

		FlushConsoleInputBuffer(entrada);	// N�o tem o teste de if, por se n�o n�o pausaria.

		ReadConsoleA(entrada, &tmep, 1, &bytes, 0);
	}

	// ----- Fun��es: (especialmente para escrita) Pode ser mais r�pida do que os overloads, se j� conhecer o tamanho do que -----
	//ser escrito talvez seja melhor essa e para leitura � poss�vel definir o m�ximo a se receber.

	DWORD EscConsole(const char* texto, DWORD tam)
	{
		WriteConsoleA(saida, texto, tam, &bytes, 0);
		return bytes;
	}

	DWORD LerConsole(char* texto, DWORD max_tam)
	{
		if (!deixar_restante)
		{
			FlushConsoleInputBuffer(entrada);
			WaitForSingleObject(entrada, INFINITE);
		}

		ReadConsoleA(entrada, texto, max_tam, &bytes, 0);
		return bytes;
	}

	// UFT-16
	DWORD EscConsole(const wchar_t* texto, DWORD tam)
	{
		WriteConsoleW(saida, texto, tam, &bytes, 0);
		return bytes;
	}

	// UFT-16
	DWORD LerConsole(wchar_t* texto, DWORD max_tam)
	{
		if (!deixar_restante)
		{
			FlushConsoleInputBuffer(entrada);
			WaitForSingleObject(entrada, INFINITE);
		}

		ReadConsoleW(entrada, texto, max_tam, &bytes, 0);
		return bytes;
	}

	// ----- Overloads: Menos coisas para escrever. -----

	// EscreverConsole(), mas sem ter que passar o tamanho
	meuconsole operator<<(const char* texto)
	{
		DWORD tam = 0;
		for (; texto[tam]; tam++);

		WriteConsoleA(saida, texto, tam, &bytes, 0);
		meuconsole mc = *this;
		return mc;
	}

	// Confiar que voc� passou uma matriz com o tamanho suficiente
	//ou pode mudar o m�ximo a receber na vari�vel `vmax_tam`.
	DWORD operator>>(char* texto)
	{
		if (!deixar_restante)
			FlushConsoleInputBuffer(entrada);

		ReadConsoleA(entrada, texto, vmax_tam, &bytes, 0);
		return bytes;
	}

	// EscreverConsole(), mas sem ter que passar o tamanho
	// UFT-16
	meuconsole operator<<(const wchar_t* texto)
	{
		DWORD tam = 0;
		for (; texto[tam]; tam++);

		WriteConsoleW(saida, texto, tam, &bytes, 0);
		meuconsole mc = *this;
		return mc;
	}

	// Confiar que voc� passou uma matriz com o tamanho suficiente
	//ou pode mudar o m�ximo a receber na vari�vel `vmax_tam`.
	// UFT-16
	DWORD operator>>(wchar_t* texto)
	{
		if (!deixar_restante)
			FlushConsoleInputBuffer(entrada);

		ReadConsoleW(entrada, texto, vmax_tam, &bytes, 0);
		return bytes;
	}
} 
#ifndef EXTERNO
csl;
#else
;
extern meuconsole csl;
#endif
