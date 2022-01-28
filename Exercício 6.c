#include <stdio.h>
#include <locale.h>
#include <string.h>

#define MAX 100

typedef struct {
	int mes;
	int ano;
} tData;

typedef struct {
	int cod;
	float leite;
	float alim;
	tData nasc;
	char abate[2];
} tGado;

int contador = 0;

int adicionarGado(tGado gado[contador]) {
	
	if (contador == MAX)
		return 0;
	
	printf("*** Dados para gado ***\n");
	printf("Código: ");
	scanf("%d", &gado[contador].cod);
	printf("Número de litros de leite produzidos por semana: ");
	scanf("%f", &gado[contador].leite);
	printf("Quantidade de alimento ingerida por semana (em kg): ");
	scanf("%f", &gado[contador].alim);
	printf("Mês de nascimento (00): ");
	scanf("%d", &gado[contador].nasc.mes);
	printf("Ano de nascimento (0000): ");
	scanf("%d", &gado[contador].nasc.ano);
	
	int mesAtual = 1, anoAtual = 2022;
	
	int totalIdade = (365 * anoAtual + 30 * mesAtual - 365 * gado[contador].nasc.ano - 30 * gado[contador].nasc.mes) / 365;
	
	printf("Idade do gado: %d\n", totalIdade);
	
	if (totalIdade > 5 || gado[contador].leite < 40)
		strcpy(gado[contador].abate, "S");
	else
		strcpy(gado[contador].abate, "N");
	
	contador++;
	
	return 1;
}

void mostrarGados(tGado gado[]) {
	
	if (contador == 0) {
		printf("*** Não existem gados cadastrados! ***\n");
	} else {
		int i;
		printf("*** Gados cadastrados ***\n");
		for (i = 0; i < contador; i++) {
			printf("Gado %d\n", i+1);
			printf("Código: %d\n", gado[i].cod);
			printf("Número de litros de leite produzidos por semana: %.2f\n", gado[i].leite);
			printf("Quantidade de alimento ingerida por semana: %.2f kg\n", gado[i].alim);
			printf("Mês de nascimento: %d\n", gado[i].nasc.mes);
			printf("Ano de nascimento: %d\n", gado[i].nasc.ano);
			printf("Vai para o abate: %s\n", gado[i].abate);
			printf("--------------------------------------\n");		
		}	
	}
}

void qtdLeite(tGado gado[]) {
	
	int i;
	float soma = 0;
	
	for (i = 0; i < contador; i++)
		soma = soma + gado[i].leite;
	
	printf("A quantidade total de leite produzida por semana na fazenda é %.2f L\n", soma);
}

void qtdAlimento(tGado gado[]) {
	
	int i;
	float soma = 0;
	
	for (i = 0; i < contador; i++)
		soma = soma + gado[i].alim;
	
	printf("A quantidade total de alimento consumido por semana na fazenda é %.2f kg\n", soma);
}

void mostrarAbates(tGado gado[]) {
	
	int i;
	char aux[2] = "S";
	int count = 0;
	
	for (i = 0; i < contador; i++)
		if (strcmp(strupr(gado[i].abate), strupr(aux)) == 0) {
			printf("Gado %d\n", i+1);
			printf("Código: %d\n", gado[i].cod);
			printf("Número de litros de leite produzidos por semana: %.2f\n", gado[i].leite);
			printf("Quantidade de alimento ingerida por semana: %.2f kg\n", gado[i].alim);
			printf("Mês de nascimento: %d\n", gado[i].nasc.mes);
			printf("Ano de nascimento: %d\n", gado[i].nasc.ano);
			printf("Vai para o abate: %s\n", gado[i].abate);
			printf("--------------------------------------\n");	
			count++;
		}
	
	printf("Total de gados para o abatedouro: %d\n", count);
}

void salvarGados(tGado gado[]) {
	
	int i;
	
	FILE *arq;
	arq = fopen("gados.txt", "w");
	
	fprintf(arq, "%d\n", contador);
	
	for (i = 0; i < contador; i++) {
		fprintf(arq, "%d\n", gado[i].cod);
		fprintf(arq, "%f\n", gado[i].leite);
		fprintf(arq, "%f\n", gado[i].alim);
		fprintf(arq, "%d\n", gado[i].nasc.mes);
		fprintf(arq, "%d\n", gado[i].nasc.ano);
		fprintf(arq, "%s\n", gado[i].abate);
	}
	
	printf("Gados salvos com sucesso!\n");
	
	fclose(arq);
}

void carregarGados(tGado gado[]) {
	
	int i;
	
	FILE *arq;
	arq = fopen("gados.txt", "r");
	
	if (arq == NULL) {
		printf("Arquivo não foi encontrado!\n");
		return;
	}
	
	fscanf(arq, "%d\n", &contador);
	printf("Carregando gados\n");
	
	for (i = 0; i < contador; i++) {
		
		fscanf(arq, "%d\n", &gado[i].cod);
		fscanf(arq, "%f\n", &gado[i].leite);
		fscanf(arq, "%f\n", &gado[i].alim);
		fscanf(arq, "%d\n", &gado[i].nasc.mes);
		fscanf(arq, "%d\n", &gado[i].nasc.ano);
		fscanf(arq, "%s\n", &gado[i].abate);
		
		printf("---");
		_sleep(500);
	}
	
	fclose(arq);
	system("cls");
}

int menu() {
	
	int op;
	
	printf("*** Sistema de Catálogo e Controle de Gados ***\n");
	printf("1 - Adicionar gado\n");
	printf("2 - Mostrar gados\n");
	printf("3 - Salvar gados em arquivo\n");
	printf("4 - Quantidade total de leite produzida por semana\n");
	printf("5 - Quantidade total de alimento consumido por semana\n");
	printf("6 - Mostrar animais que devem ir para o abate\n");
	printf("0 - Sair\n");
	scanf("%d", &op);
	
	return op;	
}

int main() {
	
	setlocale(LC_ALL,"Portuguese");
	
	tGado gado[MAX];
	
	int op;
	
	char titulo[30];
	char console[15];
	int numGado;

	carregarGados(gado);
	_sleep(1000);
	
	do {
		system("cls");
		op = menu();
		switch(op) {
			case 1:
				if (adicionarGado(gado) == 1)
					printf("Gado adicionado!\n");
				else
					printf("Limite de gados cadastrados atingido!\n");
				break;
			case 2:
				mostrarGados(gado);
				break;
			case 3:
				salvarGados(gado);
				break;
			case 4:
				qtdLeite(gado);
				break;
			case 5:
				qtdAlimento(gado);
				break;
			case 6:
				mostrarAbates(gado);
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
