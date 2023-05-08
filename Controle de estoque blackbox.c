#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

void menu();
void cadastrar();
void visualizar();
void pesquisar();
void alterar();
void excluir();
void insertionSort(int opcao);
int exibeCampos(int codigo, int opcao);
FILE *abreArq(char modo);
int lerArq();

FILE *arquivo;

struct componentesele
{
    char nome[40];
    char fornecedor[50];
    int codigo;
    int quantidade;
    float precoUnit;
    float precoTotal;
} compELE[100];

int indice = 0;
int i = 0;

int main()
{
    setlocale(LC_ALL, "Portuguese");

    arquivo = fopen("arquivo.dat", "rb");
    if (arquivo == NULL)
    {	
        abreArq('g');
    }
    fclose(arquivo);
    
    indice = lerArq();
    
    menu();
}

void menu()
{
    char opcao;

    do
    {
        system("cls");
        printf("=================== MENU ===================\n");
        printf("A - Incluir\n");
        printf("B - Visualizar todos os itens cadastrados\n");
        printf("C - Pesquisar um item individual\n");
        printf("D - Alterar\n");
        printf("E - Excluir\n");
        printf("F - Finalizar o Programa\n");

        printf("\n\nDigite uma opcao: ");
        scanf("%s%*c", &opcao);

        switch (opcao)
        {
        case 'A':
        case 'a':
            cadastrar();
            break;
        case 'B':
        case 'b':
            visualizar();
            break;
        case 'C':
        case 'c':
            pesquisar();
            break;
        case 'D':
        case 'd':
            alterar();
            break;
        case 'E':
        case 'e':
            excluir();
            break;
        case 'f':
        case 'F':
            printf("Encerrando...\n\n");
            break;
        default:
            printf("Opcao invalida! \n\n");
            break;
        }
        system("pause");
    } while (opcao != 'f' && opcao != 'F');
}

void cadastrar()
{
    int i = 0;

    system("cls");
    
    abreArq('a');
    
    printf("=== Cadastro do componente eletronico ===\n\n");
    if (indice < 100)
    {
        srand(time(NULL));
        compELE[indice].codigo = (rand() % 100);
        
        for (i = 0; i < indice; i++)
        {
            if (compELE[i].codigo == compELE[indice].codigo)
            {
                compELE[indice].codigo = (rand() % 100);   
                i = -1;         
            }
        }

        printf("Nome do Componente Eletronico: ");
        gets(compELE[indice].nome);
        printf("Fornecedor de componente eletronico: ");
        gets(compELE[indice].fornecedor);
        printf("Quantidade do Componente Eletronico:");
        scanf("%i%*c", &compELE[indice].quantidade);
        printf("Pre�o unitario do Componente Eletronico:");
        scanf("%f%*c", &compELE[indice].precoUnit);
        compELE[indice].precoTotal = compELE[indice].precoUnit * compELE[indice].quantidade;
        printf("\nCodigo gerado: %i", compELE[indice].codigo);
        fwrite(&compELE[indice], sizeof(compELE[indice]), 1, arquivo);
        printf("\nItem cadastrado com sucesso \n\n");
        indice++;
    }
    else
    {
        printf("Erro! Numero de ferramentas cadastradas excedeu o limite ");
	}
	
	fclose(arquivo);

}
void visualizar()
{
    int i, opcao, codigo = 9999;

    system("cls");

    if (indice > 0)
    {
        printf("\nOp��es de visualiza��o: ");
        printf("\n1 - Crescente ");
        printf("\n2 - Decrescente \n");
        printf("\nDigite a op��o de visualiza��o: ");
        scanf("%i%*c", &opcao);

        switch (opcao)
        {
        case 1:
            system("cls");
            printf("=========== Componentes cadastrados ===========\n");
            exibeCampos(codigo, opcao);
            break;
        case 2:
            system("cls");
            printf("=========== Componentes cadastrados ===========\n");
            exibeCampos(codigo, opcao);
            break;
        default:
            printf("Digite uma op��o v�lida \n\n");
            break;
        }
    }
    else
    {
        printf("N�o h� componentes cadastrados\n ");
    }
}

void pesquisar()
{
    int codigo, achou = 0, i = 0;
    int opcao;

    system("cls");
    printf("==== Pesquisa de componentes eletronicos ====\n");
    if (indice > 0)
    {
        printf("\nDigite o codigo do componente: ");
        scanf("%i", &codigo);

        system("cls");
        printf("==== Pesquisa de componentes eletronicos ====\n");
        achou = exibeCampos(codigo, opcao);
        
        if (achou == 0)
        {
            printf("N�o h� produtos cadastrados com esse codigo \n\n");
        }
    }
    else
    {
        printf("N�o h� componentes cadastrados\n\n");
    }
}

void alterar()
{
    int codigo, achou, i = 0;
    char opcao;

    system("cls");
    
    lerArq();
    
    printf("==== Altera��o de componentes eletronicos ====\n");
    if (indice > 0)
    {
        printf("\nDigite o codigo do Componente Eletronico:");
        scanf("%i", &codigo);

        system("cls");
        printf("==== Altera��o de componentes eletronicos ====\n");

        achou = exibeCampos(codigo, opcao);

        if (achou == 1)
        {
            printf("\nDeseja realmente alterar? S/N ");
            scanf("%s%*c", &opcao);
            printf("\n");

            if (opcao == 'S' || opcao == 's')
            {
                printf("Nome do Componente Eletronico: ");
                gets(compELE[i].nome);
                printf("Fornecedor de componente eletronico: ");
                gets(compELE[i].fornecedor);
                printf("Quantidade do Componente Eletronico:");
                scanf("%i%*c", &compELE[i].quantidade);
                printf("Pre�o unitario do Componente Eletronico:");
                scanf("%f%*c", &compELE[i].precoUnit);
                
                abreArq('g');
                for (i = 0; i < indice; i++)
                {
                    fwrite(&compELE[i], sizeof(compELE[i]), 1, arquivo);
                }

                printf("\nItem alterado com sucesso \n\n");
            }else if(opcao == 'N' || opcao == 'n'){
                printf("\nComponente n�o foi alterado\n\n");
            }
            else{
                printf("\nDigite uma op��o v�lida \n\n");
            }
        }
        else
        {
            printf("N�o h� produtos cadastrados com esse codigo \n\n");
        }
    }
    else
    {
        printf("N�o h� componentes cadastrados \n\n");
    }
    fclose(arquivo);
}

void excluir()
{
    int codigo, achou, x = 0;
    char opcao;

    system("cls");
    printf("==== Exclus�o de componentes eletronicos ====\n");
    if (indice > 0)
    {
        printf("\nDigite o codigo do Componente Eletronico:");
        scanf("%i", &codigo);

        system("cls");
        printf("==== Exclus�o de componentes eletronicos ====\n");
        achou = exibeCampos(codigo, opcao);

        if (achou == 1)
        {
            printf("\nDeseja realmente excluir? S/N ");
            scanf("%s%*c", &opcao);

            if (opcao == 'S' || opcao == 's')
            {
                for (x = i; x < indice; x++)
                {
                    compELE[x] = compELE[x + 1];
                }
                indice--;
                abreArq('g');
                for (i = 0; i < indice; i++)
                {
                    fwrite(&compELE[i], sizeof(compELE[i]), 1, arquivo);
                }
                printf("\nComponente excluido com sucesso\n\n ");
            }
            else
            {
               printf("\nComponente n�o excluido \n\n");
            }
        }
        else
        {
        	printf("N�o h� produtos cadastrados com esse codigo\n\n ");
        }
    }
    else
    {
        printf("N�o h� componentes cadastrados\n\n ");
    }
    fclose(arquivo);
}

void insertionSort(int opcao)
{
    int value, j, i;

    if (opcao == 1)
    {
        for (i = 1; i < indice; i++)
        {
            value = compELE[i].codigo;
            j = i - 1;

            while ((j >= 0) && (value < compELE[j].codigo))
            {
                compELE[j + 1].codigo = compELE[j].codigo;
                j--;
            }
            compELE[j + 1].codigo = value;
        }
    }else if (opcao == 2)
    {
        for (i = 1; i < indice; i++)
        {
            value = compELE[i].codigo;
            j = i - 1;

            while ((j >= 0) && (value > compELE[j].codigo))
            {
                compELE[j + 1].codigo = compELE[j].codigo;
                j--;
            }
            compELE[j + 1].codigo = value;
        }
    }
    
    
}
int exibeCampos(int codigo, int opcao)
{   
    int achou = 0, i = 0;
	
	abreArq('l');
	lerArq();
    
    if (codigo == 9999)
    {   
        if (opcao == 1)
        {
            insertionSort(opcao);
            for (i = 0; i < indice; i++)
            {
                printf("\nFerramenta: %s", compELE[i].nome);
                printf("\nFornecedor do Componente Eletronico: %s", compELE[i].fornecedor);
                printf("\nCodigo: %i", compELE[i].codigo);
                printf("\nQuantidade: %i", compELE[i].quantidade);
                printf("\nPre�o unitario: R$%0.2f", compELE[i].precoUnit);
                printf("\nPre�o total do estoque: R$%0.2f\n\n", compELE[i].precoTotal);
                printf("\n=======================================\n");
            }
        }
        else if (opcao == 2)
        {
            insertionSort(opcao);
            for (i = 0; i < indice; i++)
            {
                printf("\nFerramenta: %s", compELE[i].nome);
                printf("\nFornecedor do Componente Eletronico: %s", compELE[i].fornecedor);
                printf("\nCodigo: %i", compELE[i].codigo);
                printf("\nQuantidade: %i", compELE[i].quantidade);
                printf("\nPre�o unitario: R$%0.2f", compELE[i].precoUnit);
                printf("\nPre�o total do estoque: R$%0.2f", compELE[i].precoTotal);
                printf("\n=======================================\n");
            }
        }
        fclose(arquivo);
    }
    else
    {
        for (i = 0; i < indice; i++)
        {
            if (codigo == compELE[i].codigo)
            {
                printf("\nFerramenta: %s", compELE[i].nome);
                printf("\nFornecedor do Componente Eletronico: %s", compELE[i].fornecedor);
                printf("\nCodigo: %i", compELE[i].codigo);
                printf("\nQuantidade: %i", compELE[i].quantidade);
                printf("\nPre�o unitario: R$%0.2f", compELE[i].precoUnit);
                printf("\nPre�o total do estoque: R$%0.2f", compELE[i].precoTotal);
                achou = 1;
                break;
            }
        }
        fclose(arquivo);
        return achou;
    }
    
}

FILE *abreArq(char modo)
{

    if (modo == 'g')
    {
        arquivo = fopen("arquivo.dat", "wb");
    }
    else if (modo == 'l')
    {
        arquivo = fopen("arquivo.dat", "rb");
    }
    else if (modo == 'a')
    {
        arquivo = fopen("arquivo.dat", "ab");
    }

    if (arquivo == NULL)
    {
        printf("Erro de abertura do arquivo ");
        getchar();
        exit(0);
    }

    return arquivo;
}

int lerArq()
{
	int i = 0;
	
    abreArq('l');

    while (fread(&compELE[i], sizeof(compELE[i]), 1, arquivo))
    {
        i++;
    }
    fclose(arquivo);
    insertionSort(1);
    return i;
}

