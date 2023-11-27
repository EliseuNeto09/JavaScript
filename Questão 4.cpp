#include <stdio.h>
#include <locale.h>

int main(){
	setlocale(LC_ALL, "Portuguese");
	
	int armazem[3][50], produtos[5] = {0, 0, 0, 0, 0}, i, j, k, soma[3] = {0, 0, 0}, maior = 0, maior2 = 0;
	
	for(i = 0; i < 3; i++){
		for(j = 0; j < 5; j++){
			printf("Insira a quantidade de itens do %i° produto no %i° armazém: ", j+1, i+1);
			scanf("%i", &armazem[i][j]);
			soma[i] = soma[i] + armazem[i][j];
		}
		printf("\n");
	}
	
	for(i = 0; i < 5; i++){
		for(j = 0; j < 3; j++){
				produtos[i] = produtos[i] + armazem[j][i];
		}
	}
	
	for(i = 0; i < 3; i++){
		printf("A quantidade de produtos armazenados no %i armazém é %i.\n", i+1, soma[i]);
	}
	
	printf("\n");
	
	for(i = 0; i < 5; i++){
		printf("A quantidade de itens do produto %i é %i\n", i+1, produtos[i]);
	}
	
	printf("\n");
	
	for(i = 0; i < 5; i++){
		if(produtos[i] > maior){
			maior = produtos[i];
			maior2 = i;
		}
	}
	
	printf("O produto com maior estoque é o produto %i", maior2+1);
}
