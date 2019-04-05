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
int busca_matriz(ListaLinear *N, char *nome_matriz, ListaLinear **M);
void operacao_basica(ListaLinear **N, ListaLinear *M1, ListaLinear *M2, char sinal);
int inicializa_matriz_resposta(int lin, int col, Matriz *mat);
void matriz_transposta(ListaLinear **N, ListaLinear *M);
void imprimir_diagonal(ListaLinear *M);

void main()
{
    int ret;
    char nome1[20], nome2[20], resp;

    ListaLinear *MyList, *M1, *M2;
    inicializa_lista(&MyList);
    do
    {
        declara_matriz(&MyList);
        printf("Inserir outra matriz? s/n: ");
        setbuf(stdin, NULL);
        scanf("%c", &resp);
    } while (resp == 's');
    /*printf("Digite o nome da matriz para buscar: ");
    setbuf(stdin, NULL);
    fgets(nome, 19, stdin);
    if(!imprime_uma_matriz(MyList, nome)){
        printf("Nao encontrado");
    }*/
    /*do
    {
        printf("Digite o nome das matrizes: ");
        setbuf(stdin, NULL);
        scanf("%s %s", nome1, nome2);
    } while (!busca_matriz(MyList, nome1, &M1) || !busca_matriz(MyList, nome2, &M2));

    operacao_basica(&MyList, M1, M2, '+');*/
    do
    {
        printf("Digite o nome da matrizes: ");
        setbuf(stdin, NULL);
        scanf("%s", nome1);
    } while (!busca_matriz(MyList, nome1, &M1));
    matriz_transposta(&MyList, M1);
    imprimir_diagonal(M1);
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
    scanf("%s", mat.nome_matriz);

    printf("\nO nome da matriz é: %s\n", mat.nome_matriz);
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
            scanf("%f", *((mat->M) + i) + j);
        }
    }
    return 1;
}

//TEMP: Imprime a matriz
void imprime_matriz(Matriz mat)
{
    for (int i = 0; i < mat.totalL; i++)
    {
        for (int j = 0; j < mat.totalC; j++)
        {
            printf("%.2f ", *(*((mat.M) + i) + j));
        }
        printf("\n");
    }
}

//PRONTA: Insere matriz no inicio da lista
void insere_inicio_lista(ListaLinear **N, Matriz matriz)
{
    for (int i = 0; i < matriz.totalL; i++)
    {
        for (int j = 0; j < matriz.totalC; j++)
        {
            printf("%.2f", matriz.M[i][j]);
        }
        printf("\n");
    }
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
        if (!strcmp(aux->MD.nome_matriz, nome_matriz))
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

//Busca matriz
int busca_matriz(ListaLinear *N, char *nome_matriz, ListaLinear **M)
{
    int achou = 0;
    ListaLinear *aux;
    for (aux = N; aux != NULL; aux = aux->prox)
    {
        if (!strcmp(aux->MD.nome_matriz, nome_matriz))
        {
            *M = aux;
            achou = 1;
            break;
        }
    }
    if (achou)
        return 1;
    return 0;
}

//PROBLEMA: Matriz resposta sai vazia do for
void operacao_basica(ListaLinear **N, ListaLinear *M1, ListaLinear *M2, char sinal)
{
    if ((M1->MD.totalL != M2->MD.totalL) || (M1->MD.totalC != M2->MD.totalC))
    {
        printf("\nMatrizes com dimensões diferentes!\n");
        return;
    }

    Matriz resp, m1, m2;

    printf("Digite o nome da matriz: ");
    setbuf(stdin, NULL);
    scanf("%s", resp.nome_matriz);

    m1 = M1->MD;
    m2 = M2->MD;

    if (!inicializa_matriz_resposta(m1.totalL, m1.totalC, &resp))
    {
        printf("Erro de alocação!!");
        exit(0);
    }

    switch (sinal)
    {
    case '+':
        for (int i = 0; i < m1.totalL; i++)
        {
            for (int j = 0; j < m1.totalC; j++)
            {
                resp.M[i][j] = m1.M[i][j] + m2.M[i][j];
                printf("%.2f", resp.M[i][j]);
            }
        }
        break;

        /* case '-':
        resp.M[i][j] = m1.M[i][j] - m2.M[i][j];
        break;
    case '/':
        for (int l = 0; l < m1.totalL; l++)
        {
            for (int c = 0; c < m1.totalC; c++)
            {
                if (m2.M[l][c] == 0)
                {
                    printf("\nNão é possível dividir as matrizes!\n");
                    return;
                }
            }
        }
        resp.M[i][j] = m1.M[i][j] / m2.M[i][j];
        break;*/
    }

    for (int i = 0; i < resp.totalL; i++)
    {
        for (int j = 0; j < resp.totalC; j++)
        {
            printf("%.2f", resp.M[i][j]);
        }
        printf("\n");
    }

    insere_inicio_lista(N, resp);
    if (!imprime_uma_matriz(*N, resp.nome_matriz))
    {
        printf("Nao achou.");
    }
}

//PRONTA: Inicializa Matriz Transposta
int inicializa_matriz_resposta(int lin, int col, Matriz *mat)
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
}

//PRONTA: Gera Transposta
void matriz_transposta(ListaLinear **N, ListaLinear *M)
{
    Matriz resp, m;

    printf("Digite o nome da matriz transposta: ");
    setbuf(stdin, NULL);
    scanf("%s", resp.nome_matriz);

    m = M->MD;

    if (!inicializa_matriz_resposta(m.totalC, m.totalL, &resp))
    {
        printf("Erro de alocação!!");
        exit(0);
    }

    for (int i = 0; i < m.totalL; i++)
    {
        for (int j = 0; j < m.totalC; j++)
        {
            resp.M[i][j] = m.M[j][i];
            printf("%.2f", resp.M[i][j]);
        }
        printf("\n");
    }

    insere_inicio_lista(N, resp);
    if (!imprime_uma_matriz(*N, resp.nome_matriz))
    {
        printf("Nao achou.");
    }
}

//PRONTA: Imprime Diagonal
void imprimir_diagonal(ListaLinear *M)
{
    Matriz m;

    m = M->MD;

    for (int i = 0; i < m.totalL; i++)
    {
        for (int j = 0; j < m.totalC; j++)
        {
            if (i == j)
            {
                printf("%.2f", m.M[i][j]);
            }
            else
            {
                printf("    ");
            }
        }
        printf("\n");
    }
}