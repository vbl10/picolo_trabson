#include <stdio.h>
#include <utility>
#include <vector>
#include <functional>
#include <math.h>
#include <fstream>
#include <chrono>
#include <iostream>

void quick_sort(std::vector<int> vec, long long int& trocas, long long int& comparacoes) {
    trocas = 0;
    comparacoes = 0;
    auto partition = [&comparacoes, &trocas](int arr[],int low,int high) -> int
    {
        using namespace std;
        //choose the pivot
        
        int pivot=arr[high];
        //Index of smaller element and Indicate
        //the right position of pivot found so far
        int i=(low-1);
        
        for(int j=low;j<=high;j++)
        {
            //If current element is smaller than the pivot
            comparacoes++;
            if(arr[j]<pivot)
            {
                //Increment index of smaller element
                i++;
                swap(arr[i],arr[j]);
                trocas++;
            }
        }
        trocas++;
        swap(arr[i+1],arr[high]);
        return (i+1);
    };
    // The Quicksort function Implement     
    std::function<void(int*, int, int)> _quick_sort = [&partition, &_quick_sort](int arr[],int low,int high) -> void
    {
        // when low is less than high
        if(low<high)
        {
            // pi is the partition return index of pivot
            
            int pi=partition(arr,low,high);
            
            //Recursion Call
            //smaller element than pivot goes left and
            //higher element goes right
            _quick_sort(arr,low,pi-1);
            _quick_sort(arr,pi+1,high);
        }
    };
    _quick_sort(vec.data(), 0, vec.size() - 1);
}

void selectionSort(int arr[], int n, long long int *trocas, long long int *comparacoes) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        std::swap(arr[min_idx], arr[i]);
        (*trocas)++;
    }
}

void insertion_sort(int arr[], int tamanho, long long int *trocas, long long int *comparacoes) {
    int i, chave, j;
    for (i = 1; i < tamanho; i++) {
        chave = arr[i];
        j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            if (arr[j] > chave) {
                (*trocas)++;
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            else break;
        }
        (*trocas)++;
        arr[j + 1] = chave;
    }
}

void improvedBubbleSort(int arr[], int tamanho, long long int *trocas, long long int *comparacoes) {
    int esquerda = 0, direita = tamanho - 1;
    int trocou = 1;
    int i;

    while (trocou) {
        trocou = 0;

        for (i = esquerda; i < direita; i++) {
            (*comparacoes)++;
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                (*trocas)++;
                trocou = 1;
            }
        }

        direita--;

        if (!trocou)
            break;

        for (i = direita; i >= esquerda; i--) {
            (*comparacoes)++;
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                (*trocas)++;
                trocou = 1;
            }
        }

        esquerda++;
    }
}

void bubbleSort(int arr[], int tamanho, long long int *trocas, long long int *comparacoes) {
    int i, j;
    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - i - 1; j++) {
            (*comparacoes)++;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                (*trocas)++;
            }
        }
    }
}

int main() {
    std::vector<int> melhor_caso[3];
    for (int i = 0; i < 3; i++) {
        int tam = (int)std::pow(10, i + 3);
        melhor_caso[i].resize(tam);
        for (int j = 0; j < tam; j++) {
            melhor_caso[i][j] = j;
        }
    }

    std::vector<int> medio_caso[3];
    for (int i = 0; i < 3; i++) {
        int tam = (int)std::pow(10, i + 3);
        melhor_caso[i].resize(tam);
        for (int j = 0; j < tam; j++) {
            medio_caso[i][j] = rand();
        }
    }

    std::vector<int> pior_caso[3];
    for (int i = 0; i < 3; i++) {
        int tam = (int)std::pow(10, i + 3);
        melhor_caso[i].resize(tam);
        for (int j = 0; j < tam; j++) {
            pior_caso[i][j] = tam - i;
        }
    }

    std::chrono::steady_clock::time_point tp1, tp2;
    long long int trocas = 0, comparacoes = 0;
    double tempo = 0.0;
    std::ofstream arquivo("trabson.csv");

    std::cout << arquivo.is_open() << std::endl;

    arquivo << "Algoritimo ; Numero de elementos ; Caso ; Tempo de execucao (s) ; Quantidade de trocas ; Quantidade de comparacoes\n";

    //BUBBLE SORT ================================================================
    for (int i = 0; i < 3; i++) {
        int tam = melhor_caso[i].size();
        arquivo << "Bubble Sort ; " << tam << " ; Melhor ; ";
        tp1 = std::chrono::steady_clock::now();
        bubbleSort(melhor_caso[i].data(), melhor_caso[i].size(), &trocas, &comparacoes);
        tp2 = std::chrono::steady_clock::now();
        tempo = std::chrono::duration<double>(tp2 - tp1).count();
        arquivo << tempo << " ; " << trocas << " ; " << comparacoes << std::endl;

        arquivo << "Bubble Sort ; " << tam << " ; Medio ; ";
        tp1 = std::chrono::steady_clock::now();
        bubbleSort(melhor_caso[i].data(), medio_caso[i].size(), &trocas, &comparacoes);
        tp2 = std::chrono::steady_clock::now();
        tempo = std::chrono::duration<double>(tp2 - tp1).count();
        arquivo << tempo << " ; " << trocas << " ; " << comparacoes << std::endl;

        arquivo << "Bubble Sort ; " << tam << " ; Pior ; ";
        tp1 = std::chrono::steady_clock::now();
        bubbleSort(melhor_caso[i].data(), pior_caso[i].size(), &trocas, &comparacoes);
        tp2 = std::chrono::steady_clock::now();
        tempo = std::chrono::duration<double>(tp2 - tp1).count();
        arquivo << tempo << " ; " << trocas << " ; " << comparacoes << std::endl;
    }

    //IMPROVED BUBBLE SORT ================================================================
    for (int i = 0; i < 3; i++) {
        int tam = melhor_caso[i].size();
        arquivo << "Improved Bubble Sort ; " << tam << " ; Melhor ; ";
        tp1 = std::chrono::steady_clock::now();
        improvedBubbleSort(melhor_caso[i].data(), melhor_caso[i].size(), &trocas, &comparacoes);
        tp2 = std::chrono::steady_clock::now();
        tempo = std::chrono::duration<double>(tp2 - tp1).count();
        arquivo << tempo << " ; " << trocas << " ; " << comparacoes << std::endl;

        arquivo << "Improved Bubble Sort ; " << tam << " ; Medio ; ";
        tp1 = std::chrono::steady_clock::now();
        improvedBubbleSort(melhor_caso[i].data(), medio_caso[i].size(), &trocas, &comparacoes);
        tp2 = std::chrono::steady_clock::now();
        tempo = std::chrono::duration<double>(tp2 - tp1).count();
        arquivo << tempo << " ; " << trocas << " ; " << comparacoes << std::endl;

        arquivo << "Improved Bubble Sort ; " << tam << " ; Pior ; ";
        tp1 = std::chrono::steady_clock::now();
        improvedBubbleSort(melhor_caso[i].data(), pior_caso[i].size(), &trocas, &comparacoes);
        tp2 = std::chrono::steady_clock::now();
        tempo = std::chrono::duration<double>(tp2 - tp1).count();
        arquivo << tempo << " ; " << trocas << " ; " << comparacoes << std::endl;
    }

    //INSERTION SORT ================================================================
    for (int i = 0; i < 3; i++) {
        int tam = melhor_caso[i].size();
        arquivo << "Insertion Sort ; " << tam << " ; Melhor ; ";
        tp1 = std::chrono::steady_clock::now();
        insertion_sort(melhor_caso[i].data(), melhor_caso[i].size(), &trocas, &comparacoes);
        tp2 = std::chrono::steady_clock::now();
        tempo = std::chrono::duration<double>(tp2 - tp1).count();
        arquivo << tempo << " ; " << trocas << " ; " << comparacoes << std::endl;

        arquivo << "Insertion Sort ; " << tam << " ; Medio ; ";
        tp1 = std::chrono::steady_clock::now();
        insertion_sort(melhor_caso[i].data(), medio_caso[i].size(), &trocas, &comparacoes);
        tp2 = std::chrono::steady_clock::now();
        tempo = std::chrono::duration<double>(tp2 - tp1).count();
        arquivo << tempo << " ; " << trocas << " ; " << comparacoes << std::endl;

        arquivo << "Insertion Sort ; " << tam << " ; Pior ; ";
        tp1 = std::chrono::steady_clock::now();
        insertion_sort(melhor_caso[i].data(), pior_caso[i].size(), &trocas, &comparacoes);
        tp2 = std::chrono::steady_clock::now();
        tempo = std::chrono::duration<double>(tp2 - tp1).count();
        arquivo << tempo << " ; " << trocas << " ; " << comparacoes << std::endl;
    }

    //SELECTION SORT ================================================================
    for (int i = 0; i < 3; i++) {
        int tam = melhor_caso[i].size();
        arquivo << "Selection Sort ; " << tam << " ; Melhor ; ";
        tp1 = std::chrono::steady_clock::now();
        selectionSort(melhor_caso[i].data(), melhor_caso[i].size(), &trocas, &comparacoes);
        tp2 = std::chrono::steady_clock::now();
        tempo = std::chrono::duration<double>(tp2 - tp1).count();
        arquivo << tempo << " ; " << trocas << " ; " << comparacoes << std::endl;

        arquivo << "Selection Sort ; " << tam << " ; Medio ; ";
        tp1 = std::chrono::steady_clock::now();
        selectionSort(melhor_caso[i].data(), medio_caso[i].size(), &trocas, &comparacoes);
        tp2 = std::chrono::steady_clock::now();
        tempo = std::chrono::duration<double>(tp2 - tp1).count();
        arquivo << tempo << " ; " << trocas << " ; " << comparacoes << std::endl;

        arquivo << "Selection Sort ; " << tam << " ; Pior ; ";
        tp1 = std::chrono::steady_clock::now();
        selectionSort(melhor_caso[i].data(), pior_caso[i].size(), &trocas, &comparacoes);
        tp2 = std::chrono::steady_clock::now();
        tempo = std::chrono::duration<double>(tp2 - tp1).count();
        arquivo << tempo << " ; " << trocas << " ; " << comparacoes << std::endl;
    }


    //QUICK SORT ================================================================
    for (int i = 0; i < 3; i++) {
        int tam = melhor_caso[i].size();
        arquivo << "Selection Sort ; " << tam << " ; Melhor ; ";
        tp1 = std::chrono::steady_clock::now();
        quick_sort(melhor_caso[i], trocas, comparacoes);
        tp2 = std::chrono::steady_clock::now();
        tempo = std::chrono::duration<double>(tp2 - tp1).count();
        arquivo << tempo << " ; " << trocas << " ; " << comparacoes << std::endl;

        arquivo << "Selection Sort ; " << tam << " ; Medio ; ";
        tp1 = std::chrono::steady_clock::now();
        quick_sort(medio_caso[i], trocas, comparacoes);
        tp2 = std::chrono::steady_clock::now();
        tempo = std::chrono::duration<double>(tp2 - tp1).count();
        arquivo << tempo << " ; " << trocas << " ; " << comparacoes << std::endl;

        arquivo << "Selection Sort ; " << tam << " ; Pior ; ";
        tp1 = std::chrono::steady_clock::now();
        quick_sort(pior_caso[i], trocas, comparacoes);
        tp2 = std::chrono::steady_clock::now();
        tempo = std::chrono::duration<double>(tp2 - tp1).count();
        arquivo << tempo << " ; " << trocas << " ; " << comparacoes << std::endl;
    }
    arquivo.close();
    return 0;
}