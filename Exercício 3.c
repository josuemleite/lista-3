#include <stdio.h>
#include <locale.h>
#include <string.h>

#define MAX 100

typedef struct {
	char matricula[15];
	char nome[40];
	float notaProva1;
	float notaProva2;
	float notaProva3;
} taluno;

int contador = 0;

void carregarAlunos(taluno aluno[]) {
	
	int i;
	
	FILE *arq;
	arq = fopen("alunos.txt", "r");
	
	if (arq == NULL) {
		printf("Arquivo não foi encontrado!\n");
		return;
	}
	
	fscanf(arq, "%d\n", &contador);
	printf("Carregando alunos(as)\n");
	
	for (i = 0; i < contador; i++) {
		fgets(aluno[i].matricula, 15, arq);
		aluno[i].matricula[strcspn(aluno[i].matricula, "\n")] = 0;
		fgets(aluno[i].nome, 40, arq);
		aluno[i].nome[strcspn(aluno[i].nome, "\n")] = 0;
		fscanf(arq, "%f\n", &aluno[i].notaProva1);
		fscanf(arq, "%f\n", &aluno[i].notaProva2);
		fscanf(arq, "%f\n", &aluno[i].notaProva3);
		printf("---");
		_sleep(500);
	}
	
	fclose(arq);
	system("cls");
}

int adicionarAluno(taluno aluno[contador]) {
	
	if (contador == MAX)
		return 0;
	
	printf("*** Cadastro de aluno(a) ***\n");
	printf("Matrícula: ");
	fflush(stdin);
	gets(aluno[contador].matricula);
	printf("Nome: ");
	fflush(stdin);
	gets(aluno[contador].nome);
	printf("Nota da prova 1: ");
	scanf("%f", &aluno[contador].notaProva1);
	printf("Nota da prova 2: ");
	scanf("%f", &aluno[contador].notaProva2);
	printf("Nota da prova 3: ");
	scanf("%f", &aluno[contador].notaProva3);
	
	contador++;
	
	return 1;
}

void salvarAlunos(taluno aluno[]) {
	
	int i;
	
	FILE *arq;
	arq = fopen("alunos.txt", "w");
	fprintf(arq, "%d\n", contador);
	
	for (i = 0; i < contador; i++) {
		fprintf(arq, "%s\n", aluno[i].matricula);
		fprintf(arq, "%s\n", aluno[i].nome);
		fprintf(arq, "%f\n", aluno[i].notaProva1);
		fprintf(arq, "%f\n", aluno[i].notaProva2);
		fprintf(arq, "%f\n", aluno[i].notaProva3);
	}
	
	printf("Alunos(as) salvos(as) com sucesso!\n");
	
	fclose(arq);
}

void buscarNome(taluno aluno[], char nome[40]) {
	
	int i;
	int existe = 0;
	
	char nomeAux[40];
	
	for (i = 0; i < contador; i++) {
		strcpy(nomeAux, aluno[i].nome);
		
		if (strcmp(strupr(nomeAux), strupr(nome)) == 0) {
			printf("Aluno(a) %d\n", i+1);
			printf("Matrícula: %s\n", aluno[i].matricula);
			printf("Nome: %s\n", aluno[i].nome);
			printf("Nota da prova 1: %.1f\n", aluno[i].notaProva1);
			printf("Nota da prova 2: %.1f\n", aluno[i].notaProva2);
			printf("Nota da prova 3: %.1f\n", aluno[i].notaProva3);
			printf("--------------------------------------\n");	
			existe = 1;
		}
	}
	
	if (!existe)
		printf("Aluno(a) não encontrado(a)!\n");
}

void buscarMatricula(taluno aluno[], char matricula[15]) {
	
	int i;
	int existe = 0;
	
	char matriculaAux[40];
	
	for (i = 0; i < contador; i++) {
		strcpy(matriculaAux, aluno[i].matricula);
		
		if (strcmp(strupr(matriculaAux), strupr(matricula)) == 0) {
			printf("Aluno(a) %d\n", i+1);
			printf("Matrícula: %s\n", aluno[i].matricula);
			printf("Nome: %s\n", aluno[i].nome);
			printf("Nota da prova 1: %.1f\n", aluno[i].notaProva1);
			printf("Nota da prova 2: %.1f\n", aluno[i].notaProva2);
			printf("Nota da prova 3: %.1f\n", aluno[i].notaProva3);
			printf("--------------------------------------\n");	
			existe = 1;
		}
	}
	
	if (!existe)
		printf("Aluno(a) não encontrado(a)!\n");
}

void alunoMaiorMedia(taluno aluno[]) {
	
	int i;
	float media = 0.0;
	float aux = 0.0;
	int posicao;
	int existe = 0;
	
	for (i = 0; i < contador; i++) {
		media = (aluno[i].notaProva1 + aluno[i].notaProva2 + aluno[i].notaProva3) / 3;
		if (media > aux) {
			aux = media;
			posicao = i;
			existe = 1;
		}
	}
	
	if (existe == 1) {
		printf("Aluno(a) %d\n", posicao+1);
		printf("Matrícula: %s\n", aluno[posicao].matricula);
		printf("Nome: %s\n", aluno[posicao].nome);
		printf("Nota da prova 1: %.1f\n", aluno[posicao].notaProva1);
		printf("Nota da prova 2: %.1f\n", aluno[posicao].notaProva2);
		printf("Nota da prova 3: %.1f\n", aluno[posicao].notaProva3);
		printf("Média geral: %.1f\n", aux);
		printf("--------------------------------------\n");
	} else {
		printf("Não existem alunos(as) cadastrados(as)!\n");
	}
}

void mostrarResultado(taluno aluno[]) {
	
	int i;
	float media = 0.0;
	int existe = 0;
	
	for (i = 0; i < contador; i++) {
		media = (aluno[i].notaProva1 + aluno[i].notaProva2 + aluno[i].notaProva3) / 3;
		if (media >= 6) {
			printf("Aluno(a) %d\n", i+1);
			printf("Matrícula: %s\n", aluno[i].matricula);
			printf("Nome: %s\n", aluno[i].nome);
			printf("Nota da prova 1: %.1f\n", aluno[i].notaProva1);
			printf("Nota da prova 2: %.1f\n", aluno[i].notaProva2);
			printf("Nota da prova 3: %.1f\n", aluno[i].notaProva3);
			printf("Média geral: %.1f\n", media);
			printf("Situação: aprovado(a)!\n");
			printf("--------------------------------------\n");
			existe = 1;
		} else {
			printf("Aluno(a) %d\n", i+1);
			printf("Matrícula: %s\n", aluno[i].matricula);
			printf("Nome: %s\n", aluno[i].nome);
			printf("Nota da prova 1: %.1f\n", aluno[i].notaProva1);
			printf("Nota da prova 2: %.1f\n", aluno[i].notaProva2);
			printf("Nota da prova 3: %.1f\n", aluno[i].notaProva3);
			printf("Média geral: %.1f\n", media);
			printf("Situação: reprovado(a)!\n");
			printf("--------------------------------------\n");
			existe = 1;
		}
	}
	
	if(!existe)
		printf("Não existem alunos(as) cadastrados(as)!\n");		
}

void mostrarAlunos(taluno aluno[]) {
	
	if (contador == 0) {
		printf("*** Não existem alunos(as) cadastrados(as)! ***\n");
	} else {
		int i;
		printf("*** Alunos(as) cadastrados(as) ***\n");
		for (i = 0; i < contador; i++) {
			printf("Aluno(a) %d\n", i+1);
			printf("Matrícula: %s\n", aluno[i].matricula);
			printf("Nome: %s\n", aluno[i].nome);
			printf("Nota da prova 1: %.1f\n", aluno[i].notaProva1);
			printf("Nota da prova 2: %.1f\n", aluno[i].notaProva2);
			printf("Nota da prova 3: %.1f\n", aluno[i].notaProva3);
			printf("--------------------------------------\n");		
		}	
	}
}

int menu() {
	
	int op;
	
	printf("*** Sistema de Cadastro de Alunos(as) ***\n");
	printf("1 - Adicionar aluno(a)\n");
	printf("2 - Salvar alunos(as) em arquivo\n");
	printf("3 - Buscar aluno(a) por nome\n");
	printf("4 - Buscar aluno(a) por matrícula\n");
	printf("5 - Mostrar aluno(a) com maior média geral\n");
	printf("6 - Situação dos alunos(as)\n");
	printf("7 - Mostrar alunos(as)\n");
	printf("0 - Sair\n");
	scanf("%d", &op);
	
	return op;
}

int main() {
	
	setlocale(LC_ALL,"Portuguese");
	
	taluno aluno[MAX];
	
	int op;
	
	char nome[40];
	char matricula[15];
	int numaluno;
	
	carregarAlunos(aluno);
	_sleep(1000);
	
	do {
		system("cls");		
		op = menu();
		switch(op) {
			case 1:
				if (adicionarAluno(aluno) == 1)
					printf("Aluno(a) adicionado(a)!\n");
				else
					printf("Limite de alunos(as) cadastrados(as) atingido!\n");
				break;
			case 2:
				salvarAlunos(aluno);
				break;
			case 3:
				printf("Nome do aluno(a): ");
				fflush(stdin);
				gets(nome);
				buscarNome(aluno, nome);
				break;
			case 4:
				printf("Matrícula do aluno(a): ");
				scanf("%d", &matricula);
				buscarMatricula(aluno, matricula);
				break;
			case 5:
				alunoMaiorMedia(aluno);
				break;
			case 6:
				mostrarResultado(aluno);
				break;
			case 7:
				mostrarAlunos(aluno);
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
