#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int size, intervalo;

    printf("Quantidade de Nºs: ");
    scanf("%d", &size);
    printf("\nIntervalo de Nºs: ");
    scanf("%d", &intervalo);

    CreateFileWithNumbers(size, intervalo);

    printf("Arquivo com Numeros Sorteados gerado.\n\n");
    
    ReadValuesFromFile(size);
    
    return 0;
}

int CreateFileWithNumbers(int size, int intervalo){
    
    int i, vet[size];
    FILE *file;
    file = fopen("Sorteados.txt", "w");

    srand(time(NULL));
    for(i=0; i<size; i++){
        vet[i] = rand() % intervalo;
        fprintf(file, "%d ", vet[i]); 
    }
    fclose(file);
}

void ChoiceMethodOrdenation(int *V, int size){
    int choice;

    printf("Informe o método de Ordenação desejado:\n[1] Bubble Sort\n[2] Insertion Sort\n[3] Merge Sort\n[4] Todos\nMétodo(s) desejado(s): ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        BubbleSort(V, size);
        break;
    case 2:
        InsertionSort(V, size);
        break;
    case 3:
        MergeSort(V, size);
        break;
    case 4:
        CallAllMethods(V, size);
        break;
    default:
        printf("Opção Inválida, tente novamente.\n");
        ChoiceMethodOrdenation(V, size);
        break;
    }
}
void CallAllMethods(int *V, int size){
    MergeSort(V, size);
    BubbleSort(V, size);
    InsertionSort(V, size);
}
void ReadValuesFromFile(int size){
    FILE *file;
    int i, vet[size];
    int *V;
    V = &vet;
    
    file = fopen("Sorteados.txt", "r");

    for(i=0; i<size; i++){
        fscanf(file, "%d\n", &vet[i]);
    }
    fclose(file);

    ChoiceMethodOrdenation(V, size);
}

void MergeSort(int *V, int size){
    int inicio = 0;
    int fim = size-1;

    printf("===============================\nNºs Sorteados:\n\n");
    for(int i = 0; i < size; i++) {
		printf("%d ", V[i]);
	}

   
    clock_t begin = clock();
    MergeSortRecursive(V, inicio, fim);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;


     printf("\n\n-------------------------------\nNumeros Ordenados com Merge Sort:\n\n");
	for(int i = 0; i < size; i++) {
		printf("%d ", V[i]);
	}
    printf("\n\nVelocidade do Algoritmo: %f\n===============================\n", time_spent);
}

void MergeSortRecursive(int *V, int inicio, int fim){
    int meio;
    if(inicio < fim){
        meio = (inicio+fim)/2;
        MergeSortRecursive(V, inicio, meio);
        MergeSortRecursive(V, meio+1, fim);
        Merge(V, inicio, meio, fim);
    }
}
void Merge(int *V, int inicio, int meio, int fim){
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;

    temp = (int *) malloc(tamanho*sizeof(int));

    if(temp != NULL){
        for(i=0; i<tamanho; i++){
            if(!fim1 && !fim2){
                if(V[p1] < V[p2])
                    temp[i] = V[p1++];
                else
                    temp[i] = V[p2++];

                if(p1 > meio) fim1 = 1;
                if(p2 > fim) fim2 = 1;
            }else{
                if(!fim1)
                    temp[i] = V[p1++];
                else
                    temp[i] = V[p2++];
            }
        }
        for(j=0, k=inicio; j<tamanho; j++, k++)
            V[k] = temp[j];
    }
    free(temp);
}

void BubbleSort(int *V, int size){
    int i, j, swap;

    printf("===============================\nNºs Sorteados:\n\n");
    for(i = 0; i < size; i++) {
		printf("%d ", V[i]);
	}

    clock_t begin = clock();

    for(i=0; i < size; i++){
        for(j = i + 1; j < size; j++){
            if(V[i] > V[j]){
                swap = V[i]; 
                V[i] = V[j];  
                V[j] = swap; 
            }
        }
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\n-------------------------------\nNumeros Ordenados com Bubble Sort:\n\n");
	for(i = 0; i < size; i++) {
		printf("%d ", V[i]);
	}
    printf("\n\nVelocidade do Algoritmo: %f\n===============================\n", time_spent);
}

void InsertionSort(int *V, int size){
    int i, j, swap;

    printf("\n===============================\nNºs Sorteados:\n\n");
    for(i = 0; i < size; i++){
        printf("%d ", V[i]);
    }
    printf("\n");

    clock_t begin = clock();
    for (i=1; i < size; i++)
    {
        swap = V[i];
        j = i - 1;
        while(j >= 0 && swap < V[j])
        {
            V[j+1] = V[j];
            j--;
        }
        V[j+1] = swap;
    }
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        printf("\n-------------------------------\nNumeros Ordenados com Insertion Sort:\n\n");
	    for(i = 0; i < size; i++) {
			printf("%d ", V[i]);
	    }
        printf("\n\nVelocidade do Algoritmo: %f\n===============================\n", time_spent);
}