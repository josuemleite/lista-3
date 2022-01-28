#include <stdio.h>
#include <locale.h>
#include <string.h>

#define MAX 10

typedef struct {
	char nome[40];
	char genero[40];
	int integrantes;
	int ranking;
} tbanda;

int contador = 0;

int adicionarBanda(tbanda banda[contador]) {
	
	if (contador == MAX)
		return 0;
	
	printf("*** Dados para banda ***\n");
	printf("Nome: ");
	fflush(stdin);
	gets(banda[contador].nome);
	printf("Gênero: ");
	fflush(stdin);
	gets(banda[contador].genero);
	printf("Integrantes: ");
	scanf("%d", &banda[contador].integrantes);
	printf("Ranking (valor entre 1 e 10, inclusive): ");
	scanf("%d", &banda[contador].ranking);
	
	contador++;
	
	return 1;
}

void mostrarBandas(tbanda banda[]) {
	
	if (contador == 0) {
		printf("*** Não existem bandas cadastradas! ***\n");
	} else {
		int i;
		printf("*** Bandas cadastradas ***\n");
		for (i = 0; i < contador; i++) {
			printf("Banda %d\n", i+1);
			printf("Nome: %s\n", banda[i].nome);
			printf("Gênero: %s\n", banda[i].genero);
			printf("Integrantes: %d\n", banda[i].integrantes);
			printf("Ranking: %d\n", banda[i].ranking);
			printf("--------------------------------------\n");		
		}	
	}
}

void salvarBandas(tbanda banda[]) {
	
	int i;
	
	FILE *arq;
	arq = fopen("bandas.txt", "w");
	fprintf(arq, "%d\n", contador);
	
	for (i = 0; i < contador; i++) {
		fprintf(arq, "%s\n", banda[i].nome);
		fprintf(arq, "%s\n", banda[i].genero);
		fprintf(arq, "%d\n", banda[i].integrantes);
		fprintf(arq, "%d\n", banda[i].ranking);
	}
	
	printf("Bandas salvas com sucesso!\n");
	
	fclose(arq);
}

void buscarBandaRanking(tbanda banda[], int rankingBusca) {
	
	int i;
	int existe = 0;
	
	int rankingAux;
	
	for (i = 0; i < contador; i++) {
		if (rankingBusca == banda[i].ranking) {
			printf("Banda %d\n", i+1);
			printf("Nome: %s\n", banda[i].nome);
			printf("Gênero: %s\n", banda[i].genero);
			printf("Integrantes: %d\n", banda[i].integrantes);
			printf("Ranking: %d\n", banda[i].ranking);
			printf("--------------------------------------\n");	
			existe = 1;
		}
	}
	
	if (!existe)
	   	printf("Banda não encontrada!\n"); 
}

void buscarBandaGenero(tbanda banda[], char generoBusca[40]) {
	
	int i;
	int existe = 0;
	
	char generoAux[40];
	
	for (i = 0; i < contador; i++) {
		strcpy(generoAux, banda[i].genero);
		
		if (strcmp(strupr(generoAux), strupr(generoBusca)) == 0) {
			printf("Banda %d\n", i+1);
			printf("Nome: %s\n", banda[i].nome);
			printf("Gênero: %s\n", banda[i].genero);
			printf("Integrantes: %d\n", banda[i].integrantes);
			printf("Ranking: %d\n", banda[i].ranking);
			printf("--------------------------------------\n");	
			existe = 1;
		}
	}
	
	if (!existe)
		printf("Banda não encontrada!\n");   
}

void bandaFavorita(tbanda banda[], char nomeBanda[40]) {
	
	int i;
	int existe = 0;
	
	char nomeBandaAux[40];
	
	for (i = 0; i < contador; i++) {
		strcpy(nomeBandaAux, banda[i].nome);
		
		if (strcmp(strupr(nomeBandaAux), strupr(nomeBanda)) == 0) {
			if (banda[i].ranking >= 1 && banda[i].ranking <= 3)
				printf("A banda %s está entre as tuas favoritas!\n", banda[i].nome);
			else
				printf("A banda %s não está entre as tuas favoritas!\n", banda[i].nome);
			existe = 1;
		}
	}
	
	if (!existe)
		printf("Banda não encontrada!\n");  
	
}

void removerBanda(tbanda banda[], int numBusca) {
	
	int i;
	int existe = 0;

	for (i = 0; i < contador; i++) {
		if(numBusca == i+1) {
			banda[i] = banda[contador-1];
			contador--;
			existe = 1;
		}
	}
	
	if (!existe)
		printf("Banda não encontrada!\n");  
	else
		printf("Banda removida com sucesso!\n");
}

void alterarBanda(tbanda banda[], int numBanda) {
	
	int i;
	int existe = 0;
	
	for (i = 0; i < contador; i++) {
		if (numBanda == i+1) {
			printf("*** Dados para banda ***\n");
			printf("Nome: ");
			fflush(stdin);
			gets(banda[i].nome);
			printf("Gênero: ");
			fflush(stdin);
			gets(banda[i].genero);
			printf("Integrantes: ");
			scanf("%d", &banda[i].integrantes);
			printf("Ranking (valor entre 1 e 10, inclusive): ");
			scanf("%d", &banda[i].ranking);
			existe = 1;
		}
	}

	if (!existe)
		printf("Banda não encontrada!\n");
	else
		printf("Banda alterada com sucesso!\n");	
}

void carregarBandas(tbanda banda[]) {
	
	int i;
	
	FILE *arq;
	arq = fopen("bandas.txt", "r");
	
	if (arq == NULL) {
		printf("Arquivo não foi encontrado!\n");
		return;
	}
	
	fscanf(arq, "%d\n", &contador);
	printf("Carregando bandas\n");
	
	for (i = 0; i < contador; i++) {
		fgets(banda[i].nome, 40, arq);
		banda[i].nome[strcspn(banda[i].nome, "\n")] = 0;
		fgets(banda[i].genero, 40, arq);
		banda[i].genero[strcspn(banda[i].genero, "\n")] = 0;
//		fscanf(arq, "%s\n", &banda[i].nome);
//		fscanf(arq, "%s", &banda[i].genero);
		fscanf(arq, "%d\n", &banda[i].integrantes);
		fscanf(arq, "%d\n", &banda[i].ranking);
		printf("---");
		_sleep(500);
	}
	
	fclose(arq);
	system("cls");
}

int menu() {
	
	int op;
	
	printf("*** Sistema de Cadastro de Bandas ***\n");
	printf("1 - Adicionar banda\n");
	printf("2 - Mostrar bandas\n");
	printf("3 - Salvar bandas em arquivo\n");
	printf("4 - Buscar banda por ranking\n");
	printf("5 - Buscar banda por gênero\n");
	printf("6 - Mostrar se a banda está entre as bandas favoritas (ranking de 1 a 3)\n");
	printf("7 - Remover banda\n");
	printf("8 - Alterar dados de um registro\n");
	printf("0 - Sair\n");
	scanf("%d", &op);
	
	return op;
}

int main() {
	
	setlocale(LC_ALL,"Portuguese");
	
	tbanda banda[MAX];
	int ranking;
	char generoBusca[40];
	char nomeBanda[40];
	int numBusca;
	int numBanda;
	int op;
	
	carregarBandas(banda);
	_sleep(1000);
	
	do {
		system("cls");		
		op = menu();
		switch(op) {
			case 1:
				if (adicionarBanda(banda) == 1)
					printf("Banda adicionada!\n");
				else
					printf("Limite de bandas cadastradas atingido!\n");
				break;
			case 2: 
				mostrarBandas(banda);
				break;
			case 3:
				salvarBandas(banda);
				break;
			case 4:
				printf("Valor do ranking (1 a 10): ");
				scanf("%d", &ranking);
				buscarBandaRanking(banda, ranking);
				break;
			case 5:
				printf("Gênero da banda: ");
				fflush(stdin);
				gets(generoBusca);
				buscarBandaGenero(banda, generoBusca);
				break;
			case 6:
				printf("Nome da banda: ");
				fflush(stdin);
				gets(nomeBanda);
				bandaFavorita(banda, nomeBanda);
				break;				
			case 7:
				mostrarBandas(banda);
				printf("Número da banda que desejas remover: ");
				scanf("%d", &numBusca);
				removerBanda(banda, numBusca);
				break;
			case 8:
				mostrarBandas(banda);
				printf("Número da banda que desejas alterar: ");
				scanf("%d", &numBanda);
				alterarBanda(banda, numBanda);
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
