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
	char**  filme; // cada um
	// mas vamos manter um registro da capacidade maxima
	// para nao ficar criando um por um mas sim bloco a
	// bloco
	int     bloco; // aloca em blocos desse tamanho
	int     capacidade; // atualizado em multiplos de bloco
}	Filmoteca;

int         carrega_filmes(const char*, Filmoteca*);
int         grava_filmes(const char*, Filmoteca*);
int         insere_filme(char*, int, Filmoteca*); // poe o filme na lista
Filmoteca*  nova_filmoteca(int);

int         main(int argc, char** argv)
{
	// entrada
	char* arquivo = "filmes.txt";
	char   entrada[80];
	strcpy(entrada, arquivo);
	if (argc > 1) strcpy(entrada, argv[1]);
	printf("Arquivo de entrada: %s\n", entrada);

	Filmoteca* Filmes = nova_filmoteca(1024); // bloco de 1024 filmes
	carrega_filmes(entrada, Filmes);
	printf("Final: lidos %d filmes\n\n", Filmes->T);

	// saida
	char* arquivo_saida = "temp.txt";
	char    saida[80];
	strcpy(saida, arquivo_saida);
	if (argc > 2) strcpy(saida, argv[2]);
	printf("Arquivo de saida: %s\n", saida);
	grava_filmes(saida, Filmes);

	return 0;
};

int         carrega_filmes(const char* entrada, Filmoteca* Filmes)
{	// le os filmes a partir do arquivo e carrega na
	// filmoteca, ja na ordem
	FILE* F = fopen(entrada, "r");
	if (F == NULL) return -1;
	int N = 60; // maior tamanho de linha
	char linha[60];
	while (fgets(linha, N, F) != 0)
		insere_filme(linha, strlen(linha), Filmes);
	fclose(F);
	return Filmes->T;
};

int         grava_filmes(const char* saida, Filmoteca* Filmes)
{
	FILE* O = fopen(saida, "w");
	if (O == NULL) return -2;
	for (int i = 0; i < Filmes->T; i += 1)
	{	int len = strlen(Filmes->filme[i]);
		fwrite(Filmes->filme[i], len, 1, O);
	};
	return 0;
};

// insere o filme 'F' na filmoteca 'FS'.
// 'Len' e o tamanho da linha
// insere o filme 'F' na filmoteca 'FS'.
// 'Len' e o tamanho da linha
int         insere_filme(char* F, int Len, Filmoteca* FS)
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

Filmoteca*  nova_filmoteca(int bloco)
{
	Filmoteca*
		F = (Filmoteca*)malloc(sizeof(Filmoteca));
	F->bloco = bloco; // vai criar em multiplos de 1K
	F->capacidade = 0;
	F->T = 0; // vazia claro
	F->filme = NULL; // deixa vazio por enquanto
	return F;
};
// fim