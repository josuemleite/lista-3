#include <stdio.h>
#include <locale.h>
#include <string.h>

#define MAX 100

typedef struct {
	char nome[40];
	float potencia;
	float tempoMedio;
} teletrodomestico;

int contador = 0;

int adicionarEletrodomestico(teletrodomestico eletrodomestico[contador]) {
	
	if (contador == MAX)
		return 0;
	
	printf("*** Dados para eletrodom�stico ***\n");
	printf("Nome: ");
	fflush(stdin);
	gets(eletrodomestico[contador].nome);
	printf("Pot�ncia (em kW): ");
	scanf("%f", &eletrodomestico[contador].potencia);
	printf("Tempo m�dio ativo por dia (em hora): ");
	scanf("%f", &eletrodomestico[contador].tempoMedio);
	
	contador++;
	
	return 1;
}

void mostrarEletrodomesticos(teletrodomestico eletrodomestico[]) {
	
	if (contador == 0) {
		printf("*** N�o existem eletrodom�sticos cadastrados! ***\n");
	} else {
		int i;
		printf("*** Eletrodom�sticos cadastrados ***\n");
		for (i = 0; i < contador; i++) {
			printf("Eletrodom�stico %d\n", i+1);
			printf("Nome: %s\n", eletrodomestico[i].nome);
			printf("Pot�ncia: %.2f kW\n", eletrodomestico[i].potencia);
			printf("Tempo m�dio ativo por dia: %.2f h\n", eletrodomestico[i].tempoMedio);
			printf("--------------------------------------\n");		
		}	
	}
}

void salvarEletrodomesticos(teletrodomestico eletrodomestico[]) {
	
	int i;
	
	FILE *arq;
	arq = fopen("eletrodomesticos.txt", "w");
	fprintf(arq, "%d\n", contador);
	
	for (i = 0; i < contador; i++) {
		fprintf(arq, "%s\n", eletrodomestico[i].nome);
		fprintf(arq, "%f\n", eletrodomestico[i].potencia);
		fprintf(arq, "%f\n", eletrodomestico[i].tempoMedio);
	}
	
	printf("Eletrodom�sticos salvos com sucesso!\n");
	
	fclose(arq);
}

void buscarEletrodomestico(teletrodomestico eletrodomestico[], char nome[40]) {
	
	int i;
	int existe = 0;
	
	char nomeAux[40];
	
	for (i = 0; i < contador; i++) {
		strcpy(nomeAux, eletrodomestico[i].nome);
		
		if (strcmp(strupr(nomeAux), strupr(nome)) == 0) {
			printf("Eletrodom�stico %d\n", i+1);
			printf("Nome: %s\n", eletrodomestico[i].nome);
			printf("Pot�ncia: %.2f kW\n", eletrodomestico[i].potencia);
			printf("Tempo m�dio ativo por dia: %.2f h\n", eletrodomestico[i].tempoMedio);
			printf("--------------------------------------\n");	
			existe = 1;
		}
	}
	
	if (!existe)
		printf("Eletrodom�stico n�o encontrado!\n");   
}

void buscarEletrodomesticoPorGasto(teletrodomestico eletrodomestico[], float valorX) {
	
	int i;
	float consumoDiario;
	int existe = 0;
	
	for (i = 0; i < contador; i++) {
		consumoDiario = eletrodomestico[i].potencia * eletrodomestico[i].tempoMedio;
		if (consumoDiario > valorX) {
			printf("Eletrodom�stico %d\n", i+1);
			printf("Nome: %s\n", eletrodomestico[i].nome);
			printf("Pot�ncia: %.2f kW\n", eletrodomestico[i].potencia);
			printf("Tempo m�dio ativo por dia: %.2f h\n", eletrodomestico[i].tempoMedio);
			printf("Consumo m�dio di�rio: %.2f kW/h\n", consumoDiario);
			printf("--------------------------------------\n");
			existe = 1;
		}
	}
	
	if(!existe)
		printf("N�o h� eletrodom�sticos que gastam mais que %.2f kW/h\n", valorX);
}

void consumoTotal(teletrodomestico eletrodomestico[], float valorKw) {
	
	int i;
	float consumoDiario = 0;
	
	for (i = 0; i < contador; i++)
		consumoDiario += eletrodomestico[i].potencia * eletrodomestico[i].tempoMedio;
	
	printf("Consumo di�rio: %.2f kW/h\n", consumoDiario);
	printf("Consumo di�rio: R$%.2f\n", consumoDiario * valorKw);
	printf("Consumo mensal: %.2f kW/h\n", consumoDiario * 30);
	printf("Consumo mensal: R$%.2f\n", (consumoDiario * 30) * valorKw);
}

void carregarEletrodomesticos(teletrodomestico eletrodomestico[]) {
	
	int i;
	
	FILE *arq;
	arq = fopen("eletrodomesticos.txt", "r");
	
	if (arq == NULL) {
		printf("Arquivo n�o foi encontrado!\n");
		return;
	}
	
	fscanf(arq, "%d\n", &contador);
	printf("Carregando eletrodom�sticos\n");
	
	for (i = 0; i < contador; i++) {
		fgets(eletrodomestico[i].nome, 40, arq);
		eletrodomestico[i].nome[strcspn(eletrodomestico[i].nome, "\n")] = 0;
		fscanf(arq, "%f\n", &eletrodomestico[i].potencia);
		fscanf(arq, "%f\n", &eletrodomestico[i].tempoMedio);
		printf("---");
		_sleep(500);
	}
	
	fclose(arq);
	system("cls");
}

int menu() {
	
	int op;
	
	printf("*** Sistema de Cadastro de Eletrodom�sticos ***\n");
	printf("1 - Adicionar eletrodom�stico\n");
	printf("2 - Mostrar eletrodom�sticos\n");
	printf("3 - Salvar eletrodom�sticos em arquivo\n");
	printf("4 - Buscar eletrodom�stico por nome\n");
	printf("5 - Buscar eletrodom�sticos por gasto\n");
	printf("6 - Mostrar consumos di�rio e mensal\n");
	printf("0 - Sair\n");
	scanf("%d", &op);
	
	return op;
}

int main() {
	
	setlocale(LC_ALL,"Portuguese");
	
	teletrodomestico eletrodomestico[MAX];
	
	int op;
	
	char nome[40];
	float valorKw;
	float valorX;
	
	carregarEletrodomesticos(eletrodomestico);
	_sleep(1000);
	
	do {
		system("cls");
		op = menu();
		switch(op) {
			case 1:
				if (adicionarEletrodomestico(eletrodomestico) == 1)
					printf("Eletrodom�stico adicionado!\n");
				else
					printf("Limite de eletrodom�sticos cadastrados atingido!\n");
				break;
			case 2:
				mostrarEletrodomesticos(eletrodomestico);
				break;
			case 3:
				salvarEletrodomesticos(eletrodomestico);
				break;
			case 4:
				printf("Nome do eletrodom�stico: ");
				fflush(stdin);
				gets(nome);
				buscarEletrodomestico(eletrodomestico, nome);
				break;
			case 5:
				printf("Valor base (em kW/h): ");
				scanf("%f", &valorX);
				buscarEletrodomesticoPorGasto(eletrodomestico, valorX);
				break;
			case 6:
				printf("Valor do kW/h: R$");
				scanf("%f", &valorKw);
				consumoTotal(eletrodomestico, valorKw);
				break;
			case 0:
				printf("Saindo...\n");
				break;
			default:
				printf("Op��o inv�lida!\n");
		}
		getch();
	} while (op != 0);
	
	return 0;
}
