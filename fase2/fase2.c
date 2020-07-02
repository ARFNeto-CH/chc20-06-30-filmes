#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	char* arquivo = "filme.txt";
	char   entrada[80];
	strcpy(entrada, arquivo);
	if (argc > 1) strcpy(entrada, argv[1]);
	printf("Arquivo de entrada: %s\n", entrada);
	FILE* F = fopen(entrada, "r");
	int N = 60; // maior tamanho de linha
	char linha[60];
	if (F == NULL) return -1;
	while (fgets(linha, N, F) != 0)
		printf("[%2d] %s", strlen(linha), linha);
	fclose(F);
	return 0;
};
// fim