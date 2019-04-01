#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Struct da Matriz
typedef struct MB
{
    char nome_matriz[20];
    //Ponteiro que representa uma matriz dinamica
    float **M;
    int totalL, totalC; //dimensão da matriz
} Matriz;

//Struct da lista que contém as matrizes
typedef struct Lista_Encadeada
{
    Matriz MD;
    struct Lista_Encadeada *prox;
} ListaLinear;

//Prototipos
void inicializa_lista(ListaLinear **N);
void declara_matriz(ListaLinear **N);
ListaLinear *Cria_Nodo();
int inicializa_matriz(int lin, int col, Matriz *mat);
void imprime_matriz(Matriz mat);
void insere_inicio_lista(ListaLinear **N, Matriz matriz);
int imprime_uma_matriz(ListaLinear *N, char *nome_matriz);

void main()
{
    int ret;
    char nome[20];

    ListaLinear *MyList;
    inicializa_lista(&MyList);
    declara_matriz(&MyList);
    printf("Digite o nome da matriz para buscar: ");
    setbuf(stdin, NULL);
    fgets(nome, 19, stdin);
    if(!imprime_uma_matriz(MyList, nome)){
        printf("Nao encontrado");
    }
}

ListaLinear *Cria_Nodo()
{ //aloca memória para o nodo{
    ListaLinear *p;
    p = (ListaLinear *)malloc(sizeof(ListaLinear));
    if (!p)
    {
        printf("Problema de alocação");
        exit(0);
    }
    return p;
}

void inicializa_lista(ListaLinear **N) //inicializa a lista
{
    *N = NULL;
}

//PRONTA: Le nome e dimensões da matriz e insere na lista
void declara_matriz(ListaLinear **N)
{
    //Cria variavel do tipo Matriz
    Matriz mat;

    printf("Digite o nome da matriz: ");
    setbuf(stdin, NULL);
    fgets(mat.nome_matriz, 19, stdin);

    printf("O nome da matriz é: %s", mat.nome_matriz);
    do
    {
        printf("Digite as dimensões [l c] da matriz: ");
        scanf("%d %d", &mat.totalL, &mat.totalC);
    } while (mat.totalL <= 0 || mat.totalC <= 0);

    if (!inicializa_matriz(mat.totalL, mat.totalC, &mat))
    {
        printf("Erro de alocação!!");
        exit(0);
    }

    insere_inicio_lista(N, mat);
}

//PRONTA: Aloca memoria para matriz e lê os elementos
int inicializa_matriz(int lin, int col, Matriz *mat)
{
    mat->M = (float **)malloc(lin * sizeof(float));

    if (!mat->M)
    {
        return 0;
    }

    for (int i = 0; i < lin; i++)
    {
        *((mat->M) + i) = (float *)malloc(col * sizeof(float));
        if (!(*((mat->M) + i)))
        {
            return 0;
        }
    }

    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("Entre com o elemento de %d x %d: ", i, j);
            scanf("%f",*((mat->M)+i)+j);
        }
    }
    return 1;
}

//TEMP: Imprime a matriz
void imprime_matriz(Matriz mat)
{
    for(int i=0;i<mat.totalL;i++)
    {
        for(int j=0;j<mat.totalC;j++)
        {
            printf("%.2f ",*(*((mat.M)+i)+j));
        }
        printf("\n");
    }
}

//PRONTA: Insere matriz no inicio da lista
void insere_inicio_lista(ListaLinear **N, Matriz matriz)
{
    ListaLinear *novo;
    novo = Cria_Nodo();
    novo->MD = matriz;
    novo->prox = *N;
    *N = novo;
}

//PRONTA: Busca pelo nome e imprime uma matriz 
int imprime_uma_matriz(ListaLinear *N, char *nome_matriz)
{
    int achou = 0;
    ListaLinear *aux;
    for (aux = N; aux != NULL; aux = aux->prox)
    {
        if (!strcmp(aux->MD.nome_matriz,nome_matriz))
        {
            imprime_matriz(aux->MD);
            achou = 1;
            break;
        }
    }
    if (achou)
        return 1;
    return 0;
}