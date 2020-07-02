#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	// a filmoteca vai ser como
	// todo programa em C
	// int argc, char** argc
	int     T; // total de filmes
	char** filme; // cada um
	// mas vamos manter um registro da capacidade maxima
	// para nao ficar criando um por um mas sim bloco a
	// bloco
	int     bloco; // aloca em blocos desse tamanho
	int     capacidade; // atualizado em multiplos de bloco
}	Filmoteca;

int     insere_filme(char*, int, Filmoteca*); // poe o filme na lista

int     main(int argc, char** argv)
{
	// entrada
	char* arquivo = "filme5.txt";
	char   entrada[80];
	strcpy(entrada, arquivo);
	if (argc > 1) strcpy(entrada, argv[1]);
	printf("Arquivo de entrada: %s\n", entrada);

	FILE* F = fopen(entrada, "r");
	if (F == NULL) return -1;

	// agora cria a filmoteca
	Filmoteca Filmes;
	Filmes.bloco = 1024; // vai criar em multiplos de 1K
	Filmes.capacidade = 0;
	Filmes.T = 0; // vazia claro
	Filmes.filme = NULL; // deixa vazio por enquanto
	// agora cria um bloco de ponterios para os filmes

	int N = 60; // maior tamanho de linha
	char linha[60];
	while (fgets(linha, N, F) != 0)
	{
		int len = strlen(linha);
		//printf("[%2d] %s", len, linha);
		insere_filme(linha, len, &Filmes);
	};
	fclose(F);
	printf("Final: lidos %d filmes\n\n", Filmes.T);
	for (int i = 0; i < Filmes.T; i += 1)
		printf("%s", Filmes.filme[i]);
	return 0;
};

// insere o filme 'F' na filmoteca 'FS'.
// 'Len' e o tamanho da linha
// insere o filme 'F' na filmoteca 'FS'.
// 'Len' e o tamanho da linha
int     insere_filme(char* F, int Len, Filmoteca* FS)
{	// cabe?
	if (FS->T >= FS->capacidade)
	{	// nao cabe mais, ou estava vazio
		FS->capacidade += FS->bloco; // novo tamanho
		char** novo = realloc(FS->filme, sizeof(char*) * FS->capacidade);
		if (novo != NULL) FS->filme = novo;
	};	// if()
	// acha a posicao para o filme
	// coloca ele no fim
	int pos = FS->T;
	for (; pos > 0; pos = pos - 1)
	{
		if (strcmp(FS->filme[pos - 1], F) > 0)
			FS->filme[pos] = FS->filme[pos - 1];
		else
			break;
	};	// for()
	// achou o lugar
	FS->filme[pos] = (char*)malloc(Len);
	strcpy(FS->filme[pos], F);
	FS->T += 1;
	return FS->T; // devolve o total de filmes atualizado
};

// fim