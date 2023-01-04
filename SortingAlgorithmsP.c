#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <time.h> 

void insertionSort(int *vetor, int n);
void selectionSort(int *vetor, int n);
void quickSort(int *vetor, int inicio, int fim);
void mergeSort(int *vetor, int inicio, int fim);
void merge(int *vetor, int inicio, int pivo, int fim);
void print_vetor(int *vetor, int n);
void verificar(int *vetor, int n);

int main()
{
    SetConsoleOutputCP(65001);
    int *vetorInsertionSort, *vetorSelectionSort, *vetorMergeSort,
        *vetorQuickSort;
    int n, exit, option;
    clock_t t;

    srand(time(NULL));
    do
    {
        printf("\n\n               Programa Sorting da Cecilia!               \n\n");
        printf(" 1 Criar vetor ja preenchido.\n");
        printf(" 2 Imprimir vetor. \n");
        printf(" 3 INSERTION SORT.\n");
        printf(" 4 SELECTION SORTT.\n");
        printf(" 5 QUICK SORT.\n");
        printf(" 6 MERGE SORT.\n");
        printf(" 7 Limpar vetor.\n");
        printf(" 0 Sair.\n");
        scanf("%d", &option);
        getchar();

        switch (option)
        {
        case 1:
            printf("\n\nDigite o tamanho do vetor: ");
            scanf("%d", &n);

            vetorInsertionSort = (int *)malloc(n * sizeof(int));
            vetorSelectionSort = (int *)malloc(n * sizeof(int));
            vetorMergeSort = (int *)malloc(n * sizeof(int));
            vetorQuickSort = (int *)malloc(n * sizeof(int));

            for (int i = 0; i < n; i++)
            {
                vetorInsertionSort[i] = rand() % 99999;
                vetorSelectionSort[i] = vetorInsertionSort[i];
                vetorMergeSort[i] = vetorInsertionSort[i];
                vetorQuickSort[i] = vetorInsertionSort[i];
            }
            break;

        case 2:
            printf("\nVetor: ");
            print_vetor(vetorInsertionSort, n);
            break;

        case 3:
            t = clock(); // armazena tempo
            insertionSort(vetorInsertionSort, n);
            t = clock() - t; // tempo final - tempo inicial
            print_vetor(vetorInsertionSort, n);
            printf("\ntempo insertion sort: %.8lf milissegundos\n", ((double)t) / ((CLOCKS_PER_SEC) / 1000));
            verificar(vetorInsertionSort, n);
            break;

        case 4:
            t = clock(); // armazena tempo
            selectionSort(vetorSelectionSort, n);
            t = clock() - t; // tempo final - tempo inicial
            print_vetor(vetorSelectionSort, n);
            printf("\ntempo Selection Sort: %.8lf milissegundos\n", ((double)t) / ((CLOCKS_PER_SEC) / 1000));
            verificar(vetorSelectionSort, n);
            break;

        case 5:
            t = clock(); // armazena tempo
            quickSort(vetorQuickSort, 0, (n - 1));
            t = clock() - t; // tempo final - tempo inicial
            print_vetor(vetorQuickSort, n);
            printf("\ntempo Quick Sort: %.8lf milissegundos\n", ((double)t) / ((CLOCKS_PER_SEC) / 1000));
            verificar(vetorQuickSort, n);
            break;

        case 6:
            t = clock(); // armazena tempo
            mergeSort(vetorMergeSort, 0, (n - 1));
            t = clock() - t; // tempo final - tempo inicial
            print_vetor(vetorMergeSort, n);
            printf("\ntempo Merge Sort: %.8lf milissegundos\n", ((double)t) / ((CLOCKS_PER_SEC) / 1000));
            verificar(vetorMergeSort, n);
            break;

        case 7:
            free(vetorInsertionSort);
            free(vetorSelectionSort);
            free(vetorQuickSort);
            free(vetorMergeSort);
            n = 0;
            break;
        case 0:
            exit = 0;
            break;
        default:
            printf("INvalida");
            break;
        }

    } while (exit);

    free(vetorInsertionSort);
    free(vetorSelectionSort);
    free(vetorQuickSort);
    free(vetorMergeSort);
    return 0;
}

void swap(int *primeiro, int *segundo)
{
    int aux = *primeiro;
    *primeiro = *segundo;
    *segundo = aux;
}

void print_vetor(int *vetor, int n)
{
    printf("[");
    for (int i = 0; i < n; i++)
    {
        if (i < n - 1)
        {
            printf("%d, ", vetor[i]);
        }
        else
        {
            printf("%d", vetor[i]);
        }
    }
    printf("]\n");
}

void verificar(int *vetor, int n)
{

    if (n > 1)
    {
        for (int i = 1; i < n; i++)
        {
            if (vetor[i - 1] > vetor[i])
            {
                printf("Cuidado, vetor nao ordenado\n");
                return;
            }
        }
    }
    printf("Uhul! Vetor esta ordenado\n");
}

void insertionSort(int *vetor, int n)
{

    int aux = 0, j = 0; // precisamos percorrer do primeiro valor ao ultimo

    for (int i = 1; i < n; i++)
    {                   // comecamos desde i=1, que e o segundo valor do vetor
        aux = vetor[i]; // guardamos o valor que estamos apontando em i, em uma variavel temporaria

        for (j = i; ((j > 0) && (aux < vetor[j - 1])); j--)
        {
            vetor[j] = vetor[j - 1];
        }
        vetor[j] = aux;
    }
}

void selectionSort(int *vetor, int n)
{
    int i, j, menor, troca;
    for (i = 0; i < n - 1; i++)
    {
        menor = i;
        for (j = i + 1; j < n; j++)
        {
            if (vetor[j] < vetor[menor])
            {
                menor = j;
            }
        }
        if (i != menor)
        {
            troca = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = troca;
        }
    }
}

void quickSort(int *vetor, int inicio, int fim)
{ // inicio inicio do vetor e fim o fim

    int pivo;
    int i = inicio;
    int j = fim;

    pivo = vetor[(inicio + fim) / 2]; // escolhemos um pivo, que é um indice (no caso é o do pivo) pois pegamos o lado direiro+esquerdo e dividimos por 2
    do
    {
        while (vetor[i] < pivo)
        { // fazemos dois laços pois ele vai encontrar o primeiro elemento do subconjunto que estamos trabalhando
            // fazemos isso ate encontrarmos um elemento no vetor que seja menor que nosso elemento central
            i++; // i marca um elemento menor que o pivo
        }
        while (pivo < vetor[j])
        {        // fazemos isso ate ele achar um elemento maior que o pivo
            j--; // j marca maior que o pivo
        }

        if (i <= j)
        {                               // aqui verificamos se os elementos i e j ja se cruzaram (pois se sim, nao temos mais trabalho)
            swap(&vetor[i], &vetor[j]); // se nao se cruzaram, fazemos o swap(troca)
            i++;
            j--;
        }

    } while (i <= j);
    if (inicio < j)
    { // marcador do comeco da nossa sublista do lado esq, se for menor que o j, quer dizer que o j nao chegou ate o final da esq(ou seja faltou um pedaço para ser ordenado)
        quickSort(vetor, inicio, j);
    }
    if (i < fim)
    {                             // ja o i vem da inicio para fim, se sobrar um pedaço, chamamos o quicksort dnv
        quickSort(vetor, i, fim); // se sobrou 2 pedaços chamamos o quick sorte 2 vezes, que é a recursao
        // por fim temos tudo ordenado
    }
}

void mergeSort(int *vetor, int inicio, int fim)
{
    int pivo;
    if (inicio < fim)
    {
        pivo = floor(inicio + fim) / 2;
        mergeSort(vetor, inicio, pivo);
        mergeSort(vetor, pivo + 1, fim);
        merge(vetor, inicio, pivo, fim);
    }
}

void merge(int *vetor, int inicio, int pivo, int fim)
{

    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = pivo + 1;
    temp = (int *)malloc(tamanho * sizeof(int));

    if (temp != NULL)
    {
        for (i = 0; i < tamanho; i++)
        {
            if (!fim1 && !fim2)
            {
                if (vetor[p1] < vetor[p2])
                    temp[i] = vetor[p1++];
                else
                    temp[i] = vetor[p2++];

                if (p1 > pivo)
                    fim1 = 1;
                if (p2 > fim)
                    fim2 = 1;
            }
            else
            {
                if (!fim1)
                    temp[i] = vetor[p1++];
                else
                    temp[i] = vetor[p2++];
            }
        }
        for (j = 0, k = inicio; j < tamanho; j++, k++)
            vetor[k] = temp[j];
    }
    free(temp);
}
