#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
setlocale(LC_ALL,"Portuguese");
struct letra{
	int dado;

};
typedef struct letra letra;

struct bloco{
    letra letra[5];
	int tag;
};
typedef struct bloco bloco;

letra* ram[100] = {};
bloco* cache[5];

int enviaCPU(letra p){
	printf("O dado foi enviado para a CPU - %d\n", p.dado);
}
void preencherRAM(){
	int i =0;
	for(i = 0; i < 100; i++){
		letra *p = malloc(sizeof(letra));
		p->dado = rand();
		printf("letra %d = %d \n", i, p->dado);
		ram[i] = p;
	}
}
int leirtura(int dado){

	int i, j =0;
	printf("\n\n procurando o dado (%d) na Cache...\n", dado);
	int achou = 0;
	for(i = 0; i < 5; i++){

		if(cache[i] == NULL)
			  continue;

		for(j = 0; j < 5; j++){

			if( cache[i]->letras[j].dado == dado){
				achou = 1;
				cache[i]->tag++;
				enviaCPU( cache[i]->letras[j] );
			}
		}
	}

	if(achou == 1){
	   printf("O dado não foi encontrado na memoria cache");
	   return;
	}

	printf("Procurando o dado (%d) na memoria RAM...\n", dado);

	for(i = 0; i < 100; i++){

		if( ram[i]->dado == dado){

			int nbloco = i/5;
			achou = 1;
			printf("Encontrado %d no bloco %d\n",ram[i]->dado, nbloco  );
			bloco *b = malloc( sizeof(bloco) );
			printf("copiando bloco para a cache\n");
			printf("bloco: \n");

			for(j = 0 ; j < 5; j++){
				printf("\t letra %d = %d\n", j, ram[nbloco*5 + j]->dado);
				b->tag++;
				b->letras[j] = *(ram[nbloco*5 + j]);
			}

			if(achou == 1){
				copiarBloco(b, nbloco);
				return;
			}

		}

	}

	if(achou == 0){
		printf("\nErro ao acessar dado! (%d)", dado);
	}

}

int copiarBloco(bloco* b, int n){
	// LFU
	b->tag++;

	int blocoMenosUtilizado = b->tag;
	int indexBlocoMenosUtilizado = 0;

	int i;
	for ( i = 1; i < 5; i++) {
		if (cache[i] == NULL) {
			continue;
		}

		if (cache[i]->tag < blocoMenosUtilizado) {
			blocoMenosUtilizado = cache[i]->tag;
			indexBlocoMenosUtilizado = i;
		}
	}

	printf("\nBloco copiado para a posicao %d na cache", indexBlocoMenosUtilizado);

	if(cache[indexBlocoMenosUtilizado] != NULL){
		printf("\nAtencao: Bloco %d substituido", indexBlocoMenosUtilizado);
	}

	cache[indexBlocoMenosUtilizado] = b;
}

int main(){
	srand(1);

	preencherRAM();
	leitura(16541);
	leitura(22648);
	leitura(2995);
	leitura(19169);
	leitura(13931);
	leitura(18467);
	leitura(7376);
	leitura(13931);
	return 0;
}
