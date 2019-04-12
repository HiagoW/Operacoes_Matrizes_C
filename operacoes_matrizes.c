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
int destruir_matriz(ListaLinear **N, char *nome_matriz);
void finaliza_programa(ListaLinear **N);
void multiplica(ListaLinear **N, ListaLinear *M1, ListaLinear *M2);
void listarMatrizes(ListaLinear *N);
void liberaMatriz(Matriz *M);

int main()
{
    int ret, opc;
    char nome1[20], nome2[20], nome[20], resp;
    ListaLinear *MyList, *M1, *M2;
    inicializa_lista(&MyList);
    do
    {
        printf("\n1.Declarar Matriz\n2.Transpor Matriz\n3.Somar Matrizes\n4.Subtrair Matrizes\n");
        printf("5.Dividir matrizes\n6.Multiplicar Matrizes\n7.Imprimir Diagonal\n8.Imprimir Matriz\n");
        printf("9.Destruir Matriz\n10.Listar matrizes\n0.Sair do Programa\nSelecione uma opção: ");
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            declara_matriz(&MyList);
            break;
        case 2:
            do
            {
                printf("Digite o nome das matrizes para transpor: ");
                setbuf(stdin, NULL);
                scanf("%s", nome1);
            } while (!busca_matriz(MyList, nome1, &M1));
            matriz_transposta(&MyList, M1);
            break;
        case 3:
            do
            {
                printf("Digite o nome das matrizes para realizar a operação[nome1 nome2]: ");
                setbuf(stdin, NULL);
                scanf("%s %s", nome1, nome2);
            } while (!busca_matriz(MyList, nome1, &M1) || !busca_matriz(MyList, nome2, &M2));

            operacao_basica(&MyList, M1, M2, '+');
            break;
        case 4:
            do
            {
                printf("Digite o nome das matrizes para realizar a operação[nome1 nome2]: ");
                setbuf(stdin, NULL);
                scanf("%s %s", nome1, nome2);
            } while (!busca_matriz(MyList, nome1, &M1) || !busca_matriz(MyList, nome2, &M2));

            operacao_basica(&MyList, M1, M2, '-');
            break;
        case 5:
            do
            {
                printf("Digite o nome das matrizes para realizar a operação[nome1 nome2]: ");
                setbuf(stdin, NULL);
                scanf("%s %s", nome1, nome2);
            } while (!busca_matriz(MyList, nome1, &M1) || !busca_matriz(MyList, nome2, &M2));

            operacao_basica(&MyList, M1, M2, '/');
            break;
        case 6:
            do
            {
                printf("Digite o nome das matrizes para realizar a operação[nome1 nome2]: ");
                setbuf(stdin, NULL);
                scanf("%s %s", nome1, nome2);
            } while (!busca_matriz(MyList, nome1, &M1) || !busca_matriz(MyList, nome2, &M2));
            multiplica(&MyList, M1, M2);
            break;
        case 7:
            do
            {
                printf("Digite o nome da matriz para imprimir a diagonal principal: ");
                setbuf(stdin, NULL);
                scanf("%s", nome1);
            } while (!busca_matriz(MyList, nome1, &M1));
            imprimir_diagonal(M1);
            break;
        case 8:
            printf("Digite o nome da matriz para imprimir: ");
            setbuf(stdin, NULL);
            scanf("%s", nome);
            if (!imprime_uma_matriz(MyList, nome))
            {
                printf("Nao encontrado\n");
            }
            break;
        case 9:
            printf("Digite o nome da matriz para destruir: ");
            setbuf(stdin, NULL);
            scanf("%s", nome);
            if (!destruir_matriz(&MyList, nome))
            {
                printf("Nao encontrado\n");
            }
            break;
        case 10:
            listarMatrizes(MyList);
            break;
        case 0:
            finaliza_programa(&MyList);
            exit(0);
        default:
            break;
        }
    } while (opc != 0);
}

ListaLinear *Cria_Nodo()
{ //aloca memória para o nodo{
    ListaLinear *p;
    p = (ListaLinear *)malloc(sizeof(ListaLinear));
    if (!p)
    {
        printf("Problema de alocação\n");
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
    ListaLinear *M;

    do{
        printf("Digite o nome da matriz: ");
        setbuf(stdin, NULL);
        scanf("%s", mat.nome_matriz);
    }while(busca_matriz(*N,mat.nome_matriz,&M));

    printf("\nO nome da matriz é: %s\n", mat.nome_matriz);
    do
    {
        printf("Digite as dimensões [l c] da matriz: ");
        scanf("%d %d", &mat.totalL, &mat.totalC);
    } while (mat.totalL <= 0 || mat.totalC <= 0);

    if (!inicializa_matriz(mat.totalL, mat.totalC, &mat))
    {
        printf("Erro de alocação!!\n");
        exit(0);
    }

    insere_inicio_lista(N, mat);
}

//PRONTA: Aloca memoria para matriz e lê os elementos
int inicializa_matriz(int lin, int col, Matriz *mat)
{
    int i, j;
    float **entrada;
    entrada = (float **)malloc(lin * sizeof(float));

    if (!entrada)
    {
        return 0;
    }

    for (i = 0; i < lin; i++)
    {
        *(entrada + i) = (float *)malloc(col * sizeof(float));
        if (!*(entrada + i))
        {
            return 0;
        }
    }

    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("Entre com o elemento de %d x %d: ", i, j);
            scanf("%f", *(entrada + i) + j);
        }
    }
    mat->M = entrada;
    return 1;
}

//TEMP: Imprime a matriz
void imprime_matriz(Matriz mat)
{
    int i, j;
    for (i = 0; i < mat.totalL; i++)
    {
        for (j = 0; j < mat.totalC; j++)
        {
            printf("%.2f ", *(*((mat.M) + i) + j));
        }
        printf("\n");
    }
}

//PRONTA: Insere matriz no inicio da lista
void insere_inicio_lista(ListaLinear **N, Matriz matriz)
{
    int i, j;
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

//PRONTA: Operacoes principais
void operacao_basica(ListaLinear **N, ListaLinear *M1, ListaLinear *M2, char sinal)
{
    Matriz resp, m1, m2;
    int i, j;
    ListaLinear *M;

    if ((M1->MD.totalL != M2->MD.totalL) || (M1->MD.totalC != M2->MD.totalC))
    {
        printf("\nMatrizes com dimensões diferentes!\n");
        return;
    }

    do{
        printf("Digite o nome da matriz resposta: ");
        setbuf(stdin, NULL);
        scanf("%s", resp.nome_matriz);
    }while(busca_matriz(*N,resp.nome_matriz,&M));
    
    m1 = M1->MD;
    m2 = M2->MD;

    if (!inicializa_matriz_resposta(m1.totalL, m1.totalC, &resp))
    {
        printf("Erro de alocação!!\n");
        exit(0);
    }

    switch (sinal)
    {
    case '+':
        for (i = 0; i < m1.totalL; i++)
        {
            for (j = 0; j < m1.totalC; j++)
            {
                resp.M[i][j] = m1.M[i][j] + m2.M[i][j];
            }
        }
        break;
    case '-':
        for (i = 0; i < m1.totalL; i++)
        {
            for (j = 0; j < m1.totalC; j++)
            {
                resp.M[i][j] = m1.M[i][j] - m2.M[i][j];
            }
        }
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
        for (i = 0; i < m1.totalL; i++)
        {
            for (j = 0; j < m1.totalC; j++)
            {
                resp.M[i][j] = m1.M[i][j] / m2.M[i][j];
            }
        }
        break;
    }

    insere_inicio_lista(N, resp);
    if (!imprime_uma_matriz(*N, resp.nome_matriz))
    {
        printf("Nao achou.\n");
    }
}

//PRONTA: Inicializa Matriz Resposta
int inicializa_matriz_resposta(int lin, int col, Matriz *mat)
{
    int i;

    mat->totalL = lin;
    mat->totalC = col;

    mat->M = (float **)malloc(lin * sizeof(float));

    if (!mat->M)
    {
        return 0;
    }

    for (i = 0; i < lin; i++)
    {
        *((mat->M) + i) = (float *)malloc(col * sizeof(float));
        if (!(*((mat->M) + i)))
        {
            return 0;
        }
    }
    return 1;
}

//PRONTA: Gera Transposta
void matriz_transposta(ListaLinear **N, ListaLinear *M)
{
    Matriz resp, m;
    int i, j;
    ListaLinear *M2;

    do{
        printf("Digite o nome da matriz transposta: ");
        setbuf(stdin, NULL);
        scanf("%s", resp.nome_matriz);
    }while(busca_matriz(*N,resp.nome_matriz,&M2));

    m = M->MD;

    if (!inicializa_matriz_resposta(m.totalC, m.totalL, &resp))
    {
        printf("Erro de alocação!!\n");
        exit(0);
    }

    for (i = 0; i < m.totalL; i++)
    {
        for (j = 0; j < m.totalC; j++)
            resp.M[j][i] = m.M[i][j];
    }

    insere_inicio_lista(N, resp);
    if (!imprime_uma_matriz(*N, resp.nome_matriz))
    {
        printf("Nao achou.\n");
    }
}

//PRONTA: Imprime Diagonal
void imprimir_diagonal(ListaLinear *M)
{
    Matriz m;
    int i, j;

    m = M->MD;

    for (i = 0; i < m.totalL; i++)
    {
        for (j = 0; j < m.totalC; j++)
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

//PRONTA: Destroi matriz
int destruir_matriz(ListaLinear **N, char *nome_matriz)
{
    ListaLinear *aux, *aux2;
    aux2=*N;
    for (aux = *N; aux != NULL; aux = aux->prox)
    {
        if (!strcmp(aux->MD.nome_matriz, nome_matriz))
        {
            if(aux==(*N)){
                *N=aux->prox;
            }else if(aux->prox==NULL){
                aux2->prox=NULL;
            }else{
                aux2->prox=aux->prox;
            }
            liberaMatriz(&(aux->MD));
            free(aux);
            printf("Matriz destruida!\n");
            return 1;
        }
        if(aux!=(*N)){
            aux2=aux2->prox;
        }
    }
    return 0;
}

//PRONTA: Destroi todas matrizes
void finaliza_programa(ListaLinear **N)
{
    ListaLinear *aux;
    for (aux = *N; aux != NULL; aux = aux->prox)
    {
        liberaMatriz(&(aux->MD));
        free(aux);
    }
}

//PRONTA: Multiplica Matrizes
void multiplica(ListaLinear **N, ListaLinear *M1, ListaLinear *M2)
{
    Matriz resp, m1, m2;
    int i, j;
    float soma;
    ListaLinear *M;

    if ((M1->MD.totalC != M2->MD.totalL))
    {
        printf("\nNão é possível multiplicar!\n");
        return;
    }
    
    do{
        printf("Digite o nome da matriz resposta: ");
        setbuf(stdin, NULL);
        scanf("%s", resp.nome_matriz);
    }while(busca_matriz(*N,resp.nome_matriz,&M));
    m1 = M1->MD;
    m2 = M2->MD;

    if (!inicializa_matriz_resposta(m1.totalL, m2.totalC, &resp))
    {
        printf("Erro de alocação!!\n");
        exit(0);
    }

    for(int i=0;i<m1.totalL;i++){
        for(int j=0;j<m2.totalC;j++){
            soma=0;
            for(int k=0;k<m1.totalC;k++){
                soma+=m1.M[i][k]*m2.M[k][j];    
            }
            resp.M[i][j]=soma;
        }
    }

    insere_inicio_lista(N, resp);
    if (!imprime_uma_matriz(*N, resp.nome_matriz))
    {
        printf("Nao achou.\n");
    }
}

//PRONTA: Lista matrizes e dimensões
void listarMatrizes(ListaLinear *N)
{
    ListaLinear *aux;
    if(N==NULL){
        printf("\nNão há matrizes\n");
        return;
    }
    for (aux = N; aux != NULL; aux = aux->prox)
    {
        printf("\n%s[%dx%d]\n",aux->MD.nome_matriz,aux->MD.totalL,aux->MD.totalC);
    }
}

//PRONTO: Libera uma matriz
void liberaMatriz(Matriz *M){
    for(int i=0;i<M->totalL;i++){
        free(M->M[i]);
    }
}