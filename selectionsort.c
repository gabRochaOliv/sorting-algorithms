#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para misturar o vetor
void mistureVetor(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if ((rand() / (double)RAND_MAX) < 0.5)
        {
            int j = (int)((n - 1) * (rand() / (double)RAND_MAX));
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
}

// Implementação do Selection Sort
void selectionSort(int arr[], int n, int *iteracoes)
{
    *iteracoes = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            (*iteracoes)++;
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int main()
{
    int tamanhos[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    // Abrir arquivo para armazenar os resultados
    FILE *fp_selection = fopen("SelectionSortIteracoesCasoMedio.txt", "w");
    if (fp_selection == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    srand(time(0)); // Iniciar os números aleatórios

    // Loop pelos tamanhos de vetor
    for (int i = 0; i < num_tamanhos; i++)
    {
        int tam = tamanhos[i];

        int *arr = (int *)malloc(tam * sizeof(int));
        if (arr == NULL)
        {
            printf("Erro ao alocar memória.\n");
            fclose(fp_selection);
            return 1;
        }

        // Preencher o array com valores crescentes
        for (int j = 0; j < tam; j++)
        {
            arr[j] = j;
        }

        // Executar 30 repetições para obter o caso médio
        for (int j = 0; j < 30; j++)
        {
            mistureVetor(arr, tam);
            int iteracoes;

            // Selection Sort
            selectionSort(arr, tam, &iteracoes);
            fprintf(fp_selection, "%d ", iteracoes);
        }
        fprintf(fp_selection, "\n");
        free(arr); // Liberar memória do array
    }

    // Fechar arquivo
    fclose(fp_selection);

    return 0;
}