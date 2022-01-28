#include <stdio.h>
#include <locale.h>
#include <string.h>

#define MAX 100

typedef struct {
	char titulo[30];
	char autor[15];
	int ano;
	int prateleira;
} tlivro;

int contador = 0;

void carregarLivros(tlivro livro[]) {
	
	int i;
	
	FILE *arq;
	arq = fopen("livros.txt", "r");
	
	if (arq == NULL) {
		printf("Arquivo não foi encontrado!\n");
		return;
	}
	
	fscanf(arq, "%d\n", &contador);
	printf("Carregando livros\n");
	
	for (i = 0; i < contador; i++) {
		fgets(livro[i].titulo, 30, arq);
		livro[i].titulo[strcspn(livro[i].titulo, "\n")] = 0;
		fgets(livro[i].autor, 15, arq);
		livro[i].autor[strcspn(livro[i].autor, "\n")] = 0;
		fscanf(arq, "%d", &livro[i].ano);
		fscanf(arq, "%d", &livro[i].prateleira);
		printf("---");
		_sleep(500);
	}
	
	fclose(arq);
	system("cls");
}

int adicionarLivro(tlivro livro[contador]) {
	
	if (contador == MAX)
		return 0;
	
	printf("*** Cadastro de livro ***\n");
	printf("Título: ");
	fflush(stdin);
	gets(livro[contador].titulo);
	printf("Autor: ");
	fflush(stdin);
	gets(livro[contador].autor);
	printf("Ano: ");
	scanf("%d", &livro[contador].ano);
	printf("Prateleira: ");
	scanf("%d", &livro[contador].prateleira);
	
	contador++;
	
	return 1;
}

void buscarTitulo(tlivro livro[], char titulo[30]) {
	
	int i;
	int existe = 0;
	
	char tituloAux[30];
	
	for (i = 0; i < contador; i++) {
		strcpy(tituloAux, livro[i].titulo);
		
		if (strcmp(strupr(tituloAux), strupr(titulo)) == 0) {
			printf("Livro %d\n", i+1);
			printf("Título: %s\n", livro[i].titulo);
			printf("Prateleira: %d\n", livro[i].prateleira);
			printf("--------------------------------------\n");	
			existe = 1;
		}
	}
	
	if (!existe)
		printf("Livro não encontrado!\n");
}

void mostrarLivros(tlivro livro[]) {
	
	if (contador == 0) {
		printf("*** Não existem livros cadastrados! ***\n");
	} else {
		int i;
		printf("*** Livros cadastrados ***\n");
		for (i = 0; i < contador; i++) {
			printf("Livro %d\n", i+1);
			printf("Título: %s\n", livro[i].titulo);
			printf("Autor: %s\n", livro[i].autor);
			printf("Ano: %d\n", livro[i].ano);
			printf("Prateleira: %d\n", livro[i].prateleira);
			printf("--------------------------------------\n");		
		}	
	}
}

void livrosMaisNovos(tlivro livro[], int ano) {
	
	int i;
	int existe = 0;
	
	printf("*** Livros mais novos que o ano %d ***\n", ano);
	
	for (i = 0; i < contador; i++) {
		if (livro[i].ano > ano) {
			printf("Livro %d\n", i+1);
			printf("Título: %s\n", livro[i].titulo);
			printf("Autor: %s\n", livro[i].autor);
			printf("Ano: %d\n", livro[i].ano);
			printf("Prateleira: %d\n", livro[i].prateleira);
			printf("--------------------------------------\n");
			existe = 1;
		}
	}
	
	if (!existe)
		printf("Não existem livros mais novos que o ano %d\n", ano);
}

void salvarLivros(tlivro livro[]) {
	
	int i;
	
	FILE *arq;
	arq = fopen("livros.txt", "w");
	fprintf(arq, "%d\n", contador);
	
	for (i = 0; i < contador; i++) {
		fprintf(arq, "%s\n", livro[i].titulo);
		fprintf(arq, "%s\n", livro[i].autor);
		fprintf(arq, "%d\n", livro[i].ano);
		fprintf(arq, "%d\n", livro[i].prateleira);
	}
	
	printf("Livros salvos com sucesso!\n");
	
	fclose(arq);
}

void removerLivro(tlivro livro[], int numLivro) {
	
	int i;
	int existe = 0;

	for (i = 0; i < contador; i++) {
		if(numLivro == i+1) {
			livro[i] = livro[contador-1];
			contador--;
			existe = 1;
		}
	}
	
	if (!existe)
		printf("Livro não encontrado!\n");  
	else
		printf("Livro removido com sucesso!\n");
}

void alterarLivro(tlivro livro[], int numLivro) {
	
	int i;
	int existe = 0;
	
	for (i = 0; i < contador; i++) {
		if (numLivro == i+1) {
			printf("*** Dados para livro ***\n");
			printf("Título: ");
			fflush(stdin);
			gets(livro[i].titulo);
			printf("Autor: ");
			fflush(stdin);
			gets(livro[i].autor);
			printf("Ano: ");
			scanf("%d", &livro[i].ano);
			printf("Prateleira: ");
			scanf("%d", &livro[i].prateleira);
			existe = 1;
		}
	}

	if (!existe)
		printf("Livro não encontrado!\n");
	else
		printf("Livro alterado com sucesso!\n");	
}

int menu() {
	
	int op;
	
	printf("*** Sistema de Cadastro de Livros ***\n");
	printf("1 - Adicionar livro\n");
	printf("2 - Procurar livro por título\n");
	printf("3 - Mostrar livros cadastrados\n");
	printf("4 - Mostrar livros mais novos que o ano digitado\n");
	printf("5 - Salvar livros em arquivo\n");
	printf("6 - Remover livro\n");
	printf("7 - Alterar dados de um registro\n");
	printf("0 - Sair\n");
	scanf("%d", &op);
	
	return op;
}

int main() {
	
	setlocale(LC_ALL,"Portuguese");
	
	tlivro livro[MAX];
	
	int op;
	
	char titulo[30];
	int ano;
	int numLivro;
	
	carregarLivros(livro);
	_sleep(1000);
	
	do {
		system("cls");		
		op = menu();
		switch(op) {
			case 1:
				if (adicionarLivro(livro) == 1)
					printf("Livro adicionado!\n");
				else
					printf("Limite de livros cadastrados atingido!\n");
				break;
			case 2:
				printf("Título do livro: ");
				fflush(stdin);
				gets(titulo);
				buscarTitulo(livro, titulo);
				break;
			case 3:
				mostrarLivros(livro);
				break;
			case 4:
				printf("Ano (0000): ");
				scanf("%d", &ano);
				livrosMaisNovos(livro, ano);
				break;
			case 5:
				salvarLivros(livro);
				break;
			case 6:
				mostrarLivros(livro);
				printf("Número do livro que desejas remover: ");
				scanf("%d", &numLivro);
				removerLivro(livro, numLivro);
				break;
			case 7:
				mostrarLivros(livro);
				printf("Número do livro que desejas alterar: ");
				scanf("%d", &numLivro);
				alterarLivro(livro, numLivro);
				break;
			case 0:
				printf("Saindo...\n");
				break;
			default:
				printf("Opção inválida!\n");			
		}
		getch();
	} while (op != 0);
	
	return 0;
}
