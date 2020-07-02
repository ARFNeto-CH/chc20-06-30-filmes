#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	// entrada
	char* arquivo = "filmes.txt";
	char   entrada[80];
	strcpy(entrada, arquivo);
	if (argc > 1) strcpy(entrada, argv[1]);
	printf("Arquivo de entrada: %s\n", entrada);

	// saida
	char*   arquivo_saida = "temp.txt";
	char    saida[80];
	strcpy(saida, arquivo_saida);
	if (argc > 2) strcpy(saida, argv[2]);
	printf("Arquivo de saida: %s\n", saida);

	FILE* F =   fopen(entrada,"r");
	FILE* O =   fopen(saida,"w");

	int N = 60; // maior tamanho de linha
	char linha[60];
	if (F == NULL) return -1;
	while (fgets(linha, N, F) != 0)
	{
		printf("[%2d] %s", strlen(linha), linha);
		fwrite(linha, strlen(linha), 1, O);
	};
	fclose(F);
	return 0;
};
// fim