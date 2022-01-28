#include <stdio.h>
#include <locale.h>
#include <string.h>

#define MAX 100

typedef struct {
	char data[11];
	char nomePessoa[30];
	char emprestado[2];
} tData;

typedef struct {
	char titulo[30];
	char console[15];
	int ano;
	int ranking;
	tData emprestimo;
} tJogo;

int contador = 0;

int adicionarJogo(tJogo jogo[contador]) {
	
	if (contador == MAX)
		return 0;
	
	printf("*** Dados para jogo ***\n");
	printf("Título: ");
	fflush(stdin);
	gets(jogo[contador].titulo);
	printf("Console: ");
	fflush(stdin);
	gets(jogo[contador].console);
	printf("Ano: ");
	scanf("%d", &jogo[contador].ano);
	printf("Ranking: ");
	scanf("%d", &jogo[contador].ranking);
	
	strcpy(jogo[contador].emprestimo.data, "00/00/0000");
	strcpy(jogo[contador].emprestimo.nomePessoa, "Sem nome");
	strcpy(jogo[contador].emprestimo.emprestado, "N");
	
//	memcpy(jogo[contador].emprestimo.data, "00/00/0000", sizeof(jogo[contador].emprestimo.data));
//	memcpy(jogo[contador].emprestimo.nomePessoa, "Sem nome", sizeof(jogo[contador].emprestimo.data));
//	memcpy(jogo[contador].emprestimo.emprestado, "N", sizeof(jogo[contador].emprestimo.data));
	
	contador++;
	
	return 1;
}

void mostrarJogos(tJogo jogo[]) {
	
	if (contador == 0) {
		printf("*** Não existem jogos cadastrados! ***\n");
	} else {
		int i;
		printf("*** Jogos cadastrados ***\n");
		for (i = 0; i < contador; i++) {
			printf("Jogo %d\n", i+1);
			printf("Título: %s\n", jogo[i].titulo);
			printf("Console: %s\n", jogo[i].console);
			printf("Ano: %d\n", jogo[i].ano);
			printf("Ranking: %d\n", jogo[i].ranking);
//			printf("Data de alocação: %s\n", jogo[i].emprestimo.data);
//			printf("Alocatário: %s\n", jogo[i].emprestimo.nomePessoa);
//			printf("Emprestado: %s\n", jogo[i].emprestimo.emprestado);
			printf("--------------------------------------\n");		
		}	
	}
}

void salvarJogos(tJogo jogo[]) {
	
	int i;
	
	FILE *arq;
	arq = fopen("jogos.txt", "w");
	fprintf(arq, "%d\n", contador);
	
	for (i = 0; i < contador; i++) {
		fprintf(arq, "%s\n", jogo[i].titulo);
		fprintf(arq, "%s\n", jogo[i].console);
		fprintf(arq, "%d\n", jogo[i].ano);
		fprintf(arq, "%d\n", jogo[i].ranking);
		fprintf(arq, "%s\n", jogo[i].emprestimo.data);
		fprintf(arq, "%s\n", jogo[i].emprestimo.nomePessoa);
		fprintf(arq, "%s\n", jogo[i].emprestimo.emprestado);
	}
	
	printf("Jogos salvos com sucesso!\n");
	
	fclose(arq);
}

void buscarJogoTitulo(tJogo jogo[], char titulo[30]) {
	
	int i;
	int existe = 0;
	
	char tituloAux[30];
	
	for (i = 0; i < contador; i++) {
		strcpy(tituloAux, jogo[i].titulo);
		
		if (strcmp(strupr(tituloAux), strupr(titulo)) == 0) {
			printf("Jogo %d\n", i+1);
			printf("Título: %s\n", jogo[i].titulo);
			printf("Console: %s\n", jogo[i].console);
			printf("Ano: %d\n", jogo[i].ano);
			printf("Ranking: %d\n", jogo[i].ranking);
			printf("Emprestado: %s\n", jogo[i].emprestimo.emprestado);
			printf("--------------------------------------\n");	
			existe = 1;
		}
	}
	
	if (!existe)
		printf("Jogo não encontrado!\n");   
}

void mostrarJogosConsole(tJogo jogo[], char console[15]) {
	
	int i;
	int existe = 0;
	
	char consoleAux[15];
	
	for (i = 0; i < contador; i++) {
		strcpy(consoleAux, jogo[i].console);
		
		if (strcmp(strupr(consoleAux), strupr(console)) == 0) {
			printf("Jogo %d\n", i+1);
			printf("Título: %s\n", jogo[i].titulo);
			printf("Console: %s\n", jogo[i].console);
			printf("Ano: %d\n", jogo[i].ano);
			printf("Ranking: %d\n", jogo[i].ranking);
			printf("Emprestado: %s\n", jogo[i].emprestimo.emprestado);
			printf("--------------------------------------\n");	
			existe = 1;
		}
	}
	
	if (!existe)
		printf("Console não encontrado!\n");
}

void emprestimoJogo(tJogo jogo[], int numJogo) {
	
	int i;
	int existe = 0;
	
	for (i = 0; i < contador; i++) {
		if (numJogo == i+1) {
			printf("Data atual (00/00/0000): ");
			fflush(stdin);
			gets(jogo[i].emprestimo.data);
			printf("Nome do locatário: ");
			fflush(stdin);
			gets(jogo[i].emprestimo.nomePessoa);
			
			fflush(stdin);
			strcpy(jogo[i].emprestimo.emprestado, "S");
//			memcpy(jogo[i].emprestimo.emprestado, "S", sizeof(jogo[contador].emprestimo.emprestado));
			
			existe = 1;
		}
	}
	
	if (!existe)
		printf("Jogo não encontrado!\n");
	else
		printf("Jogo emprestado com sucesso!\n"); 
}

void devolucaoJogo(tJogo jogo[], int numJogo) {
	
	int i;
	char aux[2] = "S";
	int existe = 0;
	
	for (i = 0; i < contador; i++) {
		
		if (numJogo == i+1 && strcmp(strupr(jogo[i].emprestimo.emprestado), strupr(aux)) == 0) {
			
			strcpy(jogo[i].emprestimo.emprestado, "N");
//			memcpy(jogo[i].emprestimo.emprestado, "N", sizeof(jogo[contador].emprestimo.emprestado));
			
			existe = 1;
		}
	}
	
	if (!existe)
		printf("Jogo não encontrado!\n");
	else
		printf("Jogo devolvido com sucesso!\n");
}

void mostrarEmprestimos(tJogo jogo[]) {
	
	int i;
	char aux[2] = "S";
	int existe = 0;
	
	for (i = 0; i < contador; i++) {
		if (strcmp(strupr(jogo[i].emprestimo.emprestado), strupr(aux)) == 0) {
			
			printf("Jogo %d\n", i+1);
			printf("Título: %s\n", jogo[i].titulo);
			printf("Console: %s\n", jogo[i].console);
			printf("Ano: %d\n", jogo[i].ano);
			printf("Ranking: %d\n", jogo[i].ranking);
			printf("Emprestado: %s\n", jogo[i].emprestimo.emprestado);
			printf("Data de alocação: %s\n", jogo[i].emprestimo.data);
			printf("Alocatário: %s\n", jogo[i].emprestimo.nomePessoa);
			printf("--------------------------------------\n");	
			
			existe = 1;
		}
	}
	
	if (!existe)
		printf("Não há jogos alocados!\n"); 
}

void carregarJogos(tJogo jogo[]) {
	
	int i;
	
	FILE *arq;
	arq = fopen("jogos.txt", "r");
	
	if (arq == NULL) {
		printf("Arquivo não foi encontrado!\n");
		return;
	}
	
	fscanf(arq, "%d\n", &contador);
	printf("Carregando jogos\n");
	
	for (i = 0; i < contador; i++) {
		
		fgets(jogo[i].titulo, 30, arq);
		jogo[i].titulo[strcspn(jogo[i].titulo, "\n")] = 0;
		fgets(jogo[i].console, 15, arq);
		jogo[i].console[strcspn(jogo[i].console, "\n")] = 0;
		fscanf(arq, "%d\n", &jogo[i].ano);
		fscanf(arq, "%d\n", &jogo[i].ranking);
		
		fscanf(arq, "%[^\n]\n", &jogo[i].emprestimo.data);
		fscanf(arq, "%[^\n]\n", &jogo[i].emprestimo.nomePessoa);
		fscanf(arq, "%[^\n]\n", &jogo[i].emprestimo.emprestado);
		
//		fgets(jogo[i].emprestimo.data, 11, arq);
//		jogo[i].emprestimo.data[strcspn(jogo[i].emprestimo.data, "\n")] = 0;
//		fgets(jogo[i].emprestimo.nomePessoa, 30, arq);
//		jogo[i].emprestimo.nomePessoa[strcspn(jogo[i].emprestimo.nomePessoa, "\n")] = 0;
//		fgets(jogo[i].emprestimo.emprestado, 2, arq);
//		jogo[i].emprestimo.emprestado[strcspn(jogo[i].emprestimo.emprestado, "\n")] = 0;
		
		printf("---");
		_sleep(500);
	}
	
	fclose(arq);
	system("cls");
}

int menu() {
	
	int op;
	
	printf("*** Sistema de Catálogo e Controle de Jogos ***\n");
	printf("1 - Adicionar jogo\n");
	printf("2 - Mostrar jogos\n");
	printf("3 - Salvar jogos em arquivo\n");
	printf("4 - Buscar jogo por título\n");
	printf("5 - Mostrar jogos por console\n");
	printf("6 - Realizar empréstimo de um jogo\n");
	printf("7 - Devolução de jogo emprestado\n");
	printf("8 - Mostrar jogos emprestados\n");
	printf("0 - Sair\n");
	scanf("%d", &op);
	
	return op;	
}

int main() {
	
	setlocale(LC_ALL,"Portuguese");
	
	tJogo jogo[MAX];
	
	int op;
	
	char titulo[30];
	char console[15];
	int numJogo;

	carregarJogos(jogo);
	_sleep(1000);
	
	do {
		system("cls");
		op = menu();
		switch(op) {
			case 1:
				if (adicionarJogo(jogo) == 1)
					printf("Jogo adicionado!\n");
				else
					printf("Limite de jogos cadastrados atingido!\n");
				break;
			case 2:
				mostrarJogos(jogo);
				break;
			case 3:
				salvarJogos(jogo);
				break;
			case 4:
				printf("Título do jogo: ");
				fflush(stdin);
				gets(titulo);
				buscarJogoTitulo(jogo, titulo);
				break;
			case 5:
				printf("Nome do console: ");
				fflush(stdin);
				gets(console);
				mostrarJogosConsole(jogo, console);
				break;
			case 6:
				mostrarJogos(jogo);
				printf("Número do jogo a ser emprestado: ");
				scanf("%d", &numJogo);
				emprestimoJogo(jogo, numJogo);
				break;
			case 7:
				mostrarJogos(jogo);
				printf("Número do jogo a ser devolvido: ");
				scanf("%d", &numJogo);
				devolucaoJogo(jogo, numJogo);
				break;
			case 8:
				mostrarEmprestimos(jogo);
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
