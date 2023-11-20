#include <utility>
#include <vector>
#include <math.h>
#include <fstream>
#include <chrono>
#include <iostream>
#include <iomanip>

void merge_sort_merge(int arr[], int left, int middle, int right, long long int* trocas, long long int* comparacoes) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        (*comparacoes)++;
        (*trocas)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        (*trocas)++;
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        (*trocas)++;
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}
void merge_sort_aux(int arr[], int left, int right, long long int* trocas, long long int* comparacoes) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        merge_sort_aux(arr, left, middle, trocas, comparacoes);
        merge_sort_aux(arr, middle + 1, right, trocas, comparacoes);
        merge_sort_merge(arr, left, middle, right, trocas, comparacoes);
    }
}
void merge_sort(int arr[], int tam, long long int* trocas, long long int* comparacoes) {
    (*trocas) = 0;
    (*comparacoes) = 0;
    merge_sort_aux(arr, 0, tam - 1, trocas, comparacoes);
}


void radix_sort(int arr[], int tam, long long int* trocas, long long int* comparacoes) {
    *trocas = 0;
    *comparacoes = 0;

    int* front = new int[tam];
    int* back = new int[tam];
    memcpy(front, arr, sizeof(int) * tam);
    
    for (int bit = 0, size_of_int = sizeof(int) * 8; bit < size_of_int; bit++) {
        unsigned int prefix_sum[2] = { 0, 0 };
        int i;
        for (i = 0; i < tam; i++) {
            prefix_sum[(front[i] & (1 << bit)) >> bit]++;
        }
        prefix_sum[1] += prefix_sum[0];
        for (i--; i >= 0; i--) {
            (*trocas)++;
            back[--prefix_sum[(front[i] & (1 << bit)) >> bit]] = front[i];
        }
        std::swap(front, back);
    }
    delete[] back;
    memcpy(arr, front, sizeof(int) * tam);
}

int quick_sort_partition(int arr[], int l, int h, long long int& trocas, long long int& comparacoes)
{
    int x = arr[h];
    int i = (l - 1);

    for (int j = l; j <= h - 1; j++) {
        comparacoes++;
        if (arr[j] <= x) {
            i++;
            trocas++;
            std::swap(arr[i], arr[j]);
        }
    }
    trocas++;
    std::swap(arr[i + 1], arr[h]);
    return (i + 1);
}
void quick_sort_aux(int arr[], int l, int h, long long int& trocas, long long int& comparacoes)
{
    // Create an auxiliary stack 
    std::vector<int> stack(h - l + 1);

    // initialize top of stack 
    int top = -1;

    // push initial values of l and h to stack 
    stack[++top] = l;
    stack[++top] = h;

    // Keep popping from stack while is not empty 
    while (top >= 0) {
        // Pop h and l 
        h = stack[top--];
        l = stack[top--];

        // Set pivot element at its correct position 
        // in sorted array 
        int p = quick_sort_partition(arr, l, h, trocas, comparacoes);

        // If there are elements on left side of pivot, 
        // then push left side to stack 
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        // If there are elements on right side of pivot, 
        // then push right side to stack 
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}
//versão iterativa
void quick_sort(int arr[], int n, long long int* trocas, long long int* comparacoes) {
    *trocas = 0;
    *comparacoes = 0;
    quick_sort_aux(arr, 0, n - 1, *trocas, *comparacoes);
}

void selectionSort(int arr[], int n, long long int* trocas, long long int* comparacoes) {
    *trocas = 0;
    *comparacoes = 0;
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

void insertion_sort(int arr[], int tamanho, long long int* trocas, long long int* comparacoes) {
    *trocas = 0;
    *comparacoes = 0;
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

void improvedBubbleSort(int arr[], int tamanho, long long int* trocas, long long int* comparacoes) {
    *trocas = 0;
    *comparacoes = 0;
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

void bubbleSort(int arr[], int tamanho, long long int* trocas, long long int* comparacoes) {
    *trocas = 0;
    *comparacoes = 0;
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


int main(int n_args, char** p_args) {
    const char* nome_arquivo = n_args > 1 ? p_args[1] : "trabson.csv";
    std::ofstream arquivo(nome_arquivo);
    arquivo.precision(6);
    arquivo.setf(arquivo.scientific);
    std::cout.precision(6);
    std::cout.setf(std::cout.scientific);

    if (arquivo.is_open())
        std::cout << "Arquivo \"" << nome_arquivo << "\" aberto.\n";
    else {
        std::cout << "Falha ao abrir arquivo.\n";
        return 0;
    }
    
    std::vector<const char*> nomes_casos = { "Melhor", "Medio", "Pior" };
   
    //[tam][caso]
    std::vector<int> vec[3][3];
    //melhor caso
    for (int i = 0; i < 3; i++) {
        int tam = (int)std::pow(10, i + 3);
        vec[i][0].resize(tam);
        for (int j = 0; j < tam; j++) {
            vec[i][0][j] = j;
        }
    }
    //medio caso
    for (int i = 0; i < 3; i++) {
        int tam = (int)std::pow(10, i + 3);
        vec[i][1].resize(tam);
        for (int j = 0; j < tam; j++) {
            vec[i][1][j] = rand();
        }
    }
    //pior caso
    for (int i = 0; i < 3; i++) {
        int tam = (int)std::pow(10, i + 3);
        vec[i][2].resize(tam);
        for (int j = 0; j < tam; j++) {
            vec[i][2][j] = tam - j;
        }
    }

    typedef void(*algoritimo_de_ordenamento)(int*, int, long long int*, long long int*);
    std::vector<algoritimo_de_ordenamento> algoritimos = {
        bubbleSort,
        improvedBubbleSort,
        insertion_sort,
        selectionSort,
        quick_sort,
        merge_sort,
        radix_sort
    };
    std::vector<const char*> nomes_algoritimos = {
        "Bubble Sort",
        "Improved Bubble Sort",
        "Insertion Sort",
        "Selection Sort",
        "Quick Sort",
        "Merge Sort",
        "Radix Sort"
    };

    std::vector<int> aux;
    std::chrono::steady_clock::time_point tp1, tp2;
    long long int trocas = 0, comparacoes = 0;
    double tempo = 0.0;

    arquivo 
        << std::left << std::setfill(' ') << std::setw(20)
        << "Algoritimo" << " ; "
        << std::right << std::setfill(' ') << std::setw(20)
        << "Tamanho" << " ; "
        << std::left << std::setfill(' ') << std::setw(20)
        << "Caso" << " ; "
        << std::right << std::setfill(' ') << std::setw(20)
        << "Tempo (s)" << " ; "
        << std::right << std::setfill(' ') << std::setw(20)
        << "Trocas" << " ; "
        << std::right << std::setfill(' ') << std::setw(20)
        << "Comparacoes"
        << std::endl;
    for (int alg = 0; alg < algoritimos.size(); alg++) {
        std::cout 
            << std::left << std::setfill('=') << std::setw(80)
            << std::string(nomes_algoritimos[alg]) + ' '
            << std::endl;
        for (int tam = 0; tam < 3; tam++) {
            std::cout 
                << '\t'
                << vec[tam][0].size()
                << std::endl;
            std::cout
                << "\t\t"
                << std::left << std::setfill(' ') << std::setw(8)
                << "Caso"
                << std::right << std::setfill(' ') << std::setw(17)
                << "Tempo(s)"
                << std::right << std::setfill(' ') << std::setw(15)
                << "Trocas"
                << std::right << std::setfill(' ') << std::setw(15)
                << "Comparacoes"
                << std::endl;

            for (int caso = 0; caso < 3; caso++) {
                std::cout
                    << "\t\t"
                    << std::left << std::setfill(' ') << std::setw(8)
                    << nomes_casos[caso];

                aux = vec[tam][caso];
                
                tp1 = std::chrono::steady_clock::now();
                algoritimos[alg](aux.data(), aux.size(), &trocas, &comparacoes);
                tp2 = std::chrono::steady_clock::now();
                
                tempo = std::chrono::duration<double>(tp2 - tp1).count();
                
                for (int i = 1; i < aux.size(); i++) {
                    if (aux[i] < aux[i - 1]) {
                        std::cout << std::endl << "Algoritimo nao ordenou o conjunto" << std::endl;
                        arquivo.close();
                        system("pause");
                        return 0;
                    }
                }

                std::cout
                    << std::right << std::setfill(' ') << std::setw(17)
                    << tempo
                    << std::right << std::setfill(' ') << std::setw(15)
                    << trocas
                    << std::right << std::setfill(' ') << std::setw(15)
                    << comparacoes
                    << std::endl;

                arquivo 
                    << std::left << std::setfill(' ') << std::setw(20)
                    << nomes_algoritimos[alg] << " ; " 
                    << std::right << std::setfill(' ') << std::setw(20)
                    << vec[tam][caso].size() << " ; "
                    << std::left << std::setfill(' ') << std::setw(20)
                    << nomes_casos[caso] << " ; "
                    << std::right << std::setfill(' ') << std::setw(20)
                    << tempo << " ; "
                    << std::right << std::setfill(' ') << std::setw(20)
                    << trocas << " ; "
                    << std::right << std::setfill(' ') << std::setw(20)
                    << comparacoes
                    << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    arquivo.close();
    std::cout << "Arquivo \"" << nome_arquivo << "\" salvo.\n";

    system("pause");
    return 0;
}
