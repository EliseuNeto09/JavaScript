#include <stdio.h>
#include <string.h>
#include <locale.h>

// Declaração das funções:
void LerNotas(float notaJurado[][5], int qntEquipes);
void CalcularMedia(float NotasJurado1[][5], float NotasJurado2[][5], float NotasJurado3[][5], float NotasJurado4[][5], float NotasJurado5[][5], int qntEquipes, float SomaDasNotas[], float Media[], float MediaPorCriterio[][4]);
void OrdenarRankingBubblesort(int qntEquipes, float Media[], float MediaPorCriterio[][4], char nomeEquipe[][100], int idEquipe[], int catEquipe[]);
// ========================

void main(){

    setlocale(LC_ALL,"Portuguese");

    /*
    Parte 01 - Cadastro das equipes 

    O software deve permitir cadastrar um máximo de dez equipes. Para isso, o sistema deve receber como entrada o código do
    projeto (que não deve se repetir), categoria (gestão, educação ou projeto social) e o nome da equipe.
    */

    // 1.1 Leitura da quantidade de equipes participantes

    int qntEquipes = 0;
 
    printf("Digite a quantidade equipes irão participar do Concurso sobre Inovação Tecnologia (Entre 1 e 10): ");
    scanf("%d", &qntEquipes);

    if(qntEquipes <= 0 || qntEquipes > 10){
        printf("\n\aQuantidade de equipes participantes foi execida ou é invalida.\nMinino: 1. \nMaximo: 10.\n");
		// Enquanto a quantidade de equipes for invalida, o programa pede para digitar novamente e não prossegue para a criação das variáveis que dependem da quantidade de equipes participantes.
        while(qntEquipes < 1 || qntEquipes > 10){
            printf("Insira uma quantidade válida de participantes: ");
            scanf("%d", &qntEquipes);
	    }
    }

    // 1.2 - Leitura dos dados das equipes participantes

    // Declaração das variáveis usadas para todo programa com base no número de equipes participantes

    int idEquipe[qntEquipes - 1], catEquipe[qntEquipes - 1];
    char nomeEquipe[qntEquipes - 1][100];

    system("cls");

    int i, j;
    
    for(i = 0; i < qntEquipes; i++){

        printf("=========  %d equipes estão participando  ========\n", qntEquipes);
        printf("\n========= Preencha os dados da %d equipe: ========\n", i + 1);

       	// Leitura do ID das equipes:
		int auxID;	
    	printf("\nDigite o ID para %dª equipe: ", i + 1);
		// Criar/Lê um dado temporário (auxID) para auxiliar na comparação com os IDs já existentes, se o ID for repetido, o programa não deve permitir o cadastro. Ao final, essa variável é atribuída ao vetor de IDs na posição i. 
    	scanf("%d", &auxID); 
    		
    	for(j = 0; j < i; j++){
			// Enquanto o ID for repetido, o programa não deve permite o cadastro.
			while(auxID == idEquipe[j]){
				printf("\n\aO id \"%d\" já foi cadastrado.\nDigite outro id: ", auxID); 
				scanf("%d", &auxID); 
			}
        }				
        idEquipe[i] = auxID;

    	// Leitura da categoria das equipes:
        printf("\nDigite a categoria do projeto da %dª equipe.\n\n(1) - Educação\n(2) - Gestão\n(3) - Projeto social\n\nCategoria: ", i + 1);
        scanf("%d", &catEquipe[i]);

		// Enquanto a categoria for inválida, o programa deve solicitar ao usuário uma categoria válida
        while((catEquipe[i] != 1) && (catEquipe[i] != 2) && (catEquipe[i] != 3)){
            printf("\n\aCategoria inválida. Digite uma categoria válida: ");
            scanf("%d", &catEquipe[i]);
        }
    	// Leitura do nome das equipes:
        printf("\nDigite o nome da %dª equipe: ", i + 1);
		scanf("%s", nomeEquipe[i]);
		// fgets(nomeEquipe[i], 100, stdin); GERA UM BUG NA IMPRESSÃO DO NOME DA EQUIPE
        system("cls");
    }
    // Mostra dados das equipes cadastradas: 
    system("cls");
    printf("======== Equipes cadastradas ========\n");
    for(i = 0; i < qntEquipes; i++){
        printf("\n[ID = %d] Nome da equipe: \"%s\", Categoria: %d.", idEquipe[i], nomeEquipe[i], catEquipe[i]);
    }
    
    printf("\n\n");
    system("pause");

    // ==============================================

    /* 
	Parte 02 - Ordenar as apresentações das equipes
	
	Logo após o cadastro das equipes, o sistema deve definir a ordem das apresentações respeitado a sequência com que foram cadastradas, mas em
	observância à regra que diz que os projetos de educação devem ser apresentados primeiro, seguidos imediatamente pelos projetos sociais e de gestão.	
	*/
	
	// Algoritmo de ordenação Bubblesort

    int tempIdEquipe, tempCatEquipe, step;
	char tempNomeEquipe[255];
	
	// Loop para acessar cada elemento do array
	for(step = 0; step < qntEquipes - 1; step++){
		// Loop para comparar os elementos do array
		for(i = 0; i < qntEquipes - step - 1; i++){
			// Compara os valores adjacentes no array, da esquerda (i) para a direita (i+1), trocando suas posições se estiverem fora de ordem
			if(catEquipe[i] > catEquipe[i + 1]){
				// Ordena o ID				
				tempIdEquipe = idEquipe[i];
				idEquipe[i] = idEquipe[i + 1];
				idEquipe[i + 1] = tempIdEquipe;
				// Ordena a categoria
				tempCatEquipe = catEquipe[i];
				catEquipe[i] = catEquipe[i + 1];
				catEquipe[i + 1] = tempCatEquipe;
				// Ordenad o nome
				strcpy(tempNomeEquipe, nomeEquipe[i]);
				strcpy(nomeEquipe[i], nomeEquipe[i + 1]);
				strcpy(nomeEquipe[i + 1],tempNomeEquipe);				
			}
		}
	}
	
    system("cls");
	printf("======== Ordem das apresentações: ========\n");
    printf("\nCategorias:\n\n(1) - Educação\n(2) - Gestão\n(3) - Projeto social\n");
    for(i = 0; i < qntEquipes; i++){
        printf("\n[ID = %d] Equipe: \"%s\" de categoria %d será a %dª a se apresentar.", idEquipe[i], nomeEquipe[i], catEquipe[i], i+1);
    }

    // ==============================================
	
	/*
	Parte 03 - Apresentação
	
	O júri será composto por 5 especialistas. Ao final de cada apresentação, cada jurado emitirá 5 notas de 0 a 10 com pesos variados, conforme indicado 
	a seguir. As notas correspondem aos critérios: 
	(a) Nível de Organização da Equipe [PESO 1]; 
	(b) Estratégia de Venda [PESO 1]; 
	(c) Grau de usabilidade do produto [PESO 2]; 
	(d) Nível de maturidade da área que pretendem atuar [PESO 3]; 
	(e) Grau de inovação do produto [PESO 3]. 
	Os jurados devem lançar as notas individuais para cada critério e o sistema deverá realizar o cálculo da média.
	*/
	
	// 3.1 Leitura das Notas

    float NotasJurado1[qntEquipes - 1][5];
	float NotasJurado2[qntEquipes - 1][5];
	float NotasJurado3[qntEquipes - 1][5];
	float NotasJurado4[qntEquipes - 1][5];
	float NotasJurado5[qntEquipes - 1][5];

	// Na estrutra (matriz) das notas dos jurados, as linhas (i) estão relacionadas a uma equipe e cada coluna (j) está relacionado a um critério, assim, cada i se sincronza com todas as outras estruturas.
	// i = 0 -> Equipe 1
	// i = 1 >- Equipe 2
	// i = 2 -> Equipe 3
	// etc...
	// [i][0] = Nota do primeiro critério
	// [i][1] = Nota do segundo critério
	// [i][2] = Nota do terceiro critério
	// [i][3] = Nota do quarto critério
	// [i][4] = Nota do quinto critério
	// [i][5] = Como pode ser obervado na função "LerNotas", é um espaço reservado para a soma da nota de um jurado (i) para um mesma equipe, no entando, não é necessário armazenar essa soma. 

    printf("\n\nCritérios:\n\n(1) Nível de organização da equipe(PESO 1).\n(2) Estratégia de venda(PESO 1).\n(3) Grau de usabilidade do produto(PESO 2).\n(4) Nível de maturidade da área que pretende atuar(PESO 3).\n(5) Grau de inovação do produto(PESO 3).\n");

    printf("\n=====Avaliação do 1º jurado: =====\n");
	LerNotas(NotasJurado1, qntEquipes);
	
	printf("\n===== Avaliação do 2º jurado: =====\n");
	LerNotas(NotasJurado2, qntEquipes);

	printf("\n===== Avaliação do 3º jurado: =====\n");
	LerNotas(NotasJurado3, qntEquipes);
	
	printf("\n===== Avaliação do 4º jurado: =====\n");
	LerNotas(NotasJurado4, qntEquipes);
	
	printf("\n===== Avaliação do 5º jurado: =====\n");
	LerNotas(NotasJurado5, qntEquipes);

    // 3.2 Calculando a média

    float SomaDasNotas[qntEquipes];
	float Media[qntEquipes], MediaPorCriterio[qntEquipes][4];

    CalcularMedia(NotasJurado1, NotasJurado2, NotasJurado3, NotasJurado4, NotasJurado5, qntEquipes, SomaDasNotas,  Media, MediaPorCriterio);

    // ==============================================

    /*
	Parte 04 - Ranking
	
	No final do concurso, o sistema deverá apresentar o ranking com os nomes das equipes, contendo ainda as médias das notas conquistadas em cada critério e sua média geral ponderada classificada em ordem decrescente.
	*/

	// 4.1 Notas das equipes:

    system("cls");
	printf("========================== Notas das equipes: ==========================\n");
	for(i = 0; i < qntEquipes; i++){
		printf("\n================== Equipe %d [ID = %d] ==================\n", i + 1, idEquipe[i]);

		printf("\n================== Notas do 1º jurado ==================\n");
		for(j = 0; j <= 4; j++){
			printf(" || %dº critério: %2.1f ", j + 1, NotasJurado1[i][j]);
		}
		printf("\n================== Notas do 2º jurado ==================\n");
		for(j = 0; j <= 4; j++){
			printf(" || %dº critério: %2.1f ", j + 1, NotasJurado2[i][j]);
		}
		printf("\n================== Notas do 3º jurado ==================\n");
		for(j = 0; j <= 4; j++){
			printf(" || %dº critério: %2.1f ", j + 1, NotasJurado3[i][j]);
		}
		printf("\n================== Notas do 4º jurado ==================\n");
		for(j = 0; j <= 4; j++){
			printf(" || %dº critério: %2.1f ", j + 1, NotasJurado4[i][j]);
		}
		printf("\n================== Notas do 5º jurado ==================\n");
		for(j = 0; j <= 4; j++){
			printf(" || %dº critério: %2.1f ", j + 1, NotasJurado5[i][j]);
		}
		printf("\n");
	}

	// 4.2 Apresentação do ranking - Algoritmo de ordenação Bubblesort para deixar as notas em ordem cresente
	OrdenarRankingBubblesort(qntEquipes, Media, MediaPorCriterio, nomeEquipe, idEquipe, catEquipe);

	printf("\n================== RANKING ==================\n");

	for(i = qntEquipes - 1; i >= 0; i--){
		if(catEquipe[i] == 1){
			printf("\nEducação: \n");
			printf("\nEquipe: [ID = %d] \"%s\"\n", idEquipe[i], nomeEquipe[i]);
			for(j = 0; j <= 4; j++){
				printf("\nMédia %dº critério: %2.1f ", j + 1, MediaPorCriterio[i][j]);
			}
			printf("\n\nMédia: %2.1f\n", Media[i]);
		}
	}

	for(i = qntEquipes - 1; i >= 0; i--){
		if(catEquipe[i] == 2){
			printf("\nGestão: \n");
			printf("\nEquipe: [ID = %d] \"%s\"\n", idEquipe[i], nomeEquipe[i]);
			for(j = 0; j <= 4; j++){
				printf("\nMédia %dº critério: %2.1f ", j + 1, MediaPorCriterio[i][j]);
			}
			printf("\n\nMédia: %2.1f\n", Media[i]);
		}
	}

	for(i = qntEquipes - 1; i >= 0; i--){
		if(catEquipe[i] == 3){
			printf("\nProjeto Social: \n");
			printf("\nEquipe: [ID = %d] \"%s\"\n", idEquipe[i], nomeEquipe[i]);
			for(j = 0; j <= 4; j++){
				printf("\nMédia %dº critério: %2.1f ", j + 1, MediaPorCriterio[i][j]);
			}
			printf("\n\nMédia: %2.1f\n", Media[i]);
		}
	}

    // ==============================================

    /*
	Parte 05 - Equipes vencedora em cada categoria 
	Parte 06 - Desempate por nivel de maturidade
	
	5 - O sistema deverá ainda, na sequência, apresentar qual equipe foi a vencedora em cada categoria (gestão, educação e projeto social).
	6 - Caso duas equipes obtenham a mesma nota, o critério de desempate é a nota relacionada ao nível de maturidade obtida pela equipe.
	*/

    printf("\n========= Vencedores ==========\n");

	printf("\nOBS: Caso o ID da equipe vencedora em determinao critério seja igual a 0, significa que não houve vencedor nessa categoria ou que não houve equipes participando para a mesma.\n");

	printf("\n================================\n");

	int maiorE = 0, maiorG = 0, maiorP = 0, vencedoraE = 0, vencedoraP = 0, vencedoraG = 0;
	float Media4CritE = 0, Media4CritG = 0, Media4CritP = 0;

	for(i = 0; i < qntEquipes; i++){
		if(catEquipe[i] == 1){
			// Caso a nota da equipe i seja maior
			if(Media[i] > maiorE){				
				maiorE = Media[i];
				vencedoraE = idEquipe[i];
				Media4CritE = MediaPorCriterio[i][3]; // [i][3] = Nota do quarto critério - Nível de maturidade da área que pretendem atuar [PESO 3]; 
			// Caso a nota da equipe i seja igual de uma outra equipe
			}else if(Media[i] == maiorE){
				if(MediaPorCriterio[i][3] > Media4CritE){			
					maiorE = Media[i];
					vencedoraE = idEquipe[i];
					Media4CritE = MediaPorCriterio[i][3];
				}
			}	
		}
	}

	for(i = 0; i < qntEquipes; i++){
		if(catEquipe[i] == 2){
			// Caso a nota da equipe i seja maior
			if(Media[i] > maiorE){				
				maiorG = Media[i];
				vencedoraG = idEquipe[i];
				Media4CritG = MediaPorCriterio[i][3]; // [i][3] = Nota do quarto critério - Nível de maturidade da área que pretendem atuar [PESO 3];
			// Caso a nota da equipe i seja igual de uma outra equipe
			}else if(Media[i] == maiorE){
				if(MediaPorCriterio[i][3] > Media4CritG){			
					maiorG = Media[i];
					vencedoraG = idEquipe[i];
					Media4CritG = MediaPorCriterio[i][3];
				}
			}	
		}
	}

	for(i = 0; i < qntEquipes; i++){
		if(catEquipe[i] == 3){
			// Caso a nota da equipe i seja maior
			if(Media[i] > maiorE){				
				maiorP = Media[i];
				vencedoraP = idEquipe[i];
				Media4CritP = MediaPorCriterio[i][3]; // [i][3] = Nota do quarto critério - Nível de maturidade da área que pretendem atuar [PESO 3];
			// Caso a nota da equipe i seja igual de uma outra equipe
			}else if(Media[i] == maiorE){
				if(MediaPorCriterio[i][3] > Media4CritP){			
					maiorP = Media[i];
					vencedoraP = idEquipe[i];
					Media4CritP = MediaPorCriterio[i][3];
				}
			}	
		}
	}

	printf("\nEducação: ID = %d.", vencedoraE);
    printf("\nGestão: ID = %d.", vencedoraG);
	printf("\nProjeto Social: ID = %d.", vencedoraP);

    // ==============================================

    /*
	Parte 07 - Equipes desclassificados
 
	O projeto que obtiver média geral menor que 7 deve ser listado entre os projetos desclassificados.
	*/
	
	for(i = 0; i < qntEquipes; i++){
		if(Media[i] < 7){
			printf("\nEquipe(s) desclassificada(s): ");
			printf("%s", nomeEquipe[i]);
		}
	}

    // ==============================================
	printf("\n");
}

void LerNotas(float NotaJurado[][5], int qntEquipes){

    int i, j;
	
	for (i=0; i<qntEquipes; i++){
		printf("\n====== %dª equipe ========\n\n", i+1);
		for (j=0; j<=4; j++){	
			printf("%dº critério: ", j+1);
			scanf("%f", &NotaJurado[i][j]);
			
			while((NotaJurado[i][j] < 0.0) || (NotaJurado[i][j] > 10.0)){
                printf("\n\aDigite uma nota válida. A nota não pode ser menor que 0 ou maior que 10: ");
            	scanf("%f", &NotaJurado[i][j]);
			}
		}
		// NotaJurado[i][5] = (NotaJurado[i][0] + NotaJurado[i][1] + NotaJurado[i][2] + NotaJurado[i][3] + NotaJurado[i][4]) / 5;
	}
	
//    for (i=0; i<qntEquipes; i++) {
//		printf("\n======= Notas do jurado para %dª equipe: ===========\n", i + 1);
//		for (j=0; j<=4; j++){
//			printf("\n%dº criterio: %.1f", j + 1, NotaJurado[i][j]);
//		}
//		printf("\n\nNota final (Média Geral): %.1f\n", NotaJurado[i][5]);
//	}
}

// OBS PARA DOCENTE: Créditos da função "CalcularMedia" a equipe de Kayky dos Santos, Daniel Mota, Verner Rafael, et. at. que a desenolverem e nos ajudaram a entender o que e como devia ser feito nesta parte.

void CalcularMedia(float NotasJurado1[][5], float NotasJurado2[][5], float NotasJurado3[][5], float NotasJurado4[][5], float NotasJurado5[][5], int qntEquipes, float SomaDasNotas[], float Media[], float MediaPorCriterio[][4]){
	int i, j;
    // i equivale as equipes
	for (i=0; i<qntEquipes; i++){
        // j equivale os critérios
		for (j=0; j<=4; j++){
			if((j == 0) || (j == 1)){
				SomaDasNotas[i] += NotasJurado1[i][j] * 1;
				SomaDasNotas[i] += NotasJurado2[i][j] * 1;
				SomaDasNotas[i] += NotasJurado3[i][j] * 1;
				SomaDasNotas[i] += NotasJurado4[i][j] * 1;
				SomaDasNotas[i] += NotasJurado5[i][j] * 1;
				MediaPorCriterio[i][j] = (NotasJurado1[i][j] + NotasJurado2[i][j] + NotasJurado3[i][j] + NotasJurado4[i][j] + NotasJurado5[i][j])/5;
			}
			if(j == 2){
				SomaDasNotas[i] += NotasJurado1[i][j] * 2;
				SomaDasNotas[i] += NotasJurado2[i][j] * 2;
				SomaDasNotas[i] += NotasJurado3[i][j] * 2;
				SomaDasNotas[i] += NotasJurado4[i][j] * 2;
				SomaDasNotas[i] += NotasJurado5[i][j] * 2;
				MediaPorCriterio[i][j] = (NotasJurado1[i][j] + NotasJurado2[i][j] + NotasJurado3[i][j] + NotasJurado4[i][j] + NotasJurado5[i][j])/5;
			}
			if((j == 3) || (j == 4)){
				SomaDasNotas[i] += NotasJurado1[i][j] * 3;
				SomaDasNotas[i] += NotasJurado2[i][j] * 3;
				SomaDasNotas[i] += NotasJurado3[i][j] * 3;
				SomaDasNotas[i] += NotasJurado4[i][j] * 3;
				SomaDasNotas[i] += NotasJurado5[i][j] * 3;
				MediaPorCriterio[i][j] = (NotasJurado1[i][j] + NotasJurado2[i][j] + NotasJurado3[i][j] + NotasJurado4[i][j] + NotasJurado5[i][j])/5;
			}
		}
	}

	for (i=0; i<qntEquipes; i++){
		Media[i] = SomaDasNotas[i]/((1 + 1 + 2 + 3 + 3) * 5);
	}
}

void OrdenarRankingBubblesort(int qntEquipes, float Media[], float MediaPorCriterio[][4], char nomeEquipe[][100], int idEquipe[], int catEquipe[]){
	
	int tempIdEquipe, tempCatEquipe, step, i, j, aux;
	char tempNomeEquipe[255];
	float tempMedia, tempMediaPorCriterio;

	// Algoritmo de ordenação Bubblesort para deixar as notas em ordem cresente

	for(step = 0; step < qntEquipes - 1; step++){
		for(i = 0; i < qntEquipes - step - 1; i++){
			if(Media[i] > Media[j]){
				// Ordena a media
				tempMedia = Media[i];
				Media[i] = Media[i + 1];
				Media[i + 1] = tempMedia;

				// Ordenad o nome
				strcpy(tempNomeEquipe, nomeEquipe[i]);
				strcpy(nomeEquipe[i], nomeEquipe[i + 1]);
				strcpy(nomeEquipe[i + 1],tempNomeEquipe);

				// Ordena a categoria
				tempCatEquipe = catEquipe[i];
				catEquipe[i] = catEquipe[i + 1];
				catEquipe[i + 1] = tempCatEquipe;

				// Ordena o ID				
				tempIdEquipe = idEquipe[i];
				idEquipe[i] = idEquipe[i + 1];
				idEquipe[i + 1] = tempIdEquipe;

				// Ordena a media por criterio
				for(aux = 0; aux <= 4; aux++){
					tempMediaPorCriterio = MediaPorCriterio[i][aux];
					MediaPorCriterio[i][aux] = MediaPorCriterio[i][aux + 1];
					MediaPorCriterio[i][aux + 1] = tempMediaPorCriterio;
				}								
			}
		}
	}
}
