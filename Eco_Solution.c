#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct empresa{
        char nome_legal[31];
        char responsavel[51];
        int CNPJ;
        char nome_fantasia[16];
        char email[41];
        char rua[51];
        int numero;
        char bairro[31];
        char cidade[16];
        char pais[11];
        int mes;
        int ano;
        struct empresa *proximo;
}Empresa;
/*** cria estrutura Empresa para armazenar os dados da empresa ***/

Empresa* empresas = NULL;
/*** inicializa a estrutura Empresa vazia ***/

void main(){
    menuinicial();
    liberar_empresas(&empresas);
}

void login(){
    char autent;

    do{
        printf("\nPossui login cadastrado? (S/N)\n");
        scanf(" %c", &autent);

        /*transforma o caractere em maiúsculo*/
        autent = toupper(autent);

        /*verifica a reposta do usuario*/
        if(autent == 'S'){
            usuariocadastrado();

        }else if(autent == 'N'){
            cadastrarusuario();

        }else{
            printf("\nResposta invalida! Tente novamente.\n");
        }
    }while(autent != 'S' && autent != 'N');
}

void usuariocadastrado(char* novo_user,  char* nova_senha){
    char user[31], senha[21];

    do{
        printf("\nInforme o seu usuario (max 30): ");
        scanf("%30s", user);

        if(strcmp(user, novo_user) == 0){
            printf("\nDigite sua senha (max 20): ");
            scanf("%20s", senha);

            if(strcmp(senha, nova_senha) == 0){
                printf("\nOla %s. Bem-vindo ao menu inicial da Eco Solution!\n", user);
                menuinicial();

            }else{
                printf("\nSenha incorreta. Tente novamente");
            }

        }else{
            printf("\nUsuario incorreto. Tente novamente!");

        }
    }while(1);
}

void cadastrarusuario(){
    char novo_user[31], nova_senha[21];

    printf("\nDigite um nome de usuario (maximo de 30 caracteres): ");
    scanf("%30s", novo_user);

    do{
        if(strlen(novo_user) != 0){

            printf("\nDigite uma senha (maximo de 20 caracteres): ");
            scanf("%20s", nova_senha);

            if(strlen(nova_senha) != 0){

                printf("\nUsuario criado com sucesso!\n");
                break;
            }else{
                printf("\nSenha invalida. Tente novamente!");
            }
        }else{
            printf("\nUsuario invalido. Tente Novamente!");
        }
    }while(strlen(novo_user) != 0 && strlen(nova_senha) != 0);

    usuariocadastrado(novo_user, nova_senha);
}

void menuinicial(){
    int opcao = 0, escolha = 0;

    do{
        printf("\n\nSelecione a opcao que deseja acessar: \n1-Gerar Relatorios \n2-Cadastrar uma nova empresa \n3-Cadastrar um novo funcionario\n");
        scanf("%d", &opcao);

        /*** verifica qual opcao o usuario escolher ***/
        switch(opcao){
        case 1:
            printf("Opcao para gerar relatorios");
            switch(escolha){
            case 1:
                printf("Relatários de faturamento");
                break;
            case 2:
                printf("Relatórios de movimentação");
                break;
            default:
                printf("Opcao invalida! Tente novamente");
            }
        case 2:
            insereemp(&empresas);
            break;
        case 3:
            printf("Opcao para cadastrar funcionarios");
            //cadastrafunc();
            break;
        default:
            printf("Opcao invalida. Tente novamente!");
            break;
        }
    }while(opcao < 1 || opcao > 3); //loop ate escolher valor entre 1 e 3
}

void insereemp(Empresa **empresas){

    char nomel[31], respon[51], nomef[16], email_emp[41], rua_emp[51], bairro_emp[31], cidade_emp[16], pais_emp[11];
    int cnpj, numero_emp, mes_emp, ano_emp;
    /*** cria variaveis auxiliares para armazenar os valores ***/

    Empresa* nova_empresa = malloc(sizeof(Empresa));
    /*** aloca espaço na memória para a estrutura ***/

    printf("\n\nCadastro de nova Empresa!\n");

    printf("\nNome Legal: ");
    scanf("%30s", nomel);

    strncpy(nova_empresa->nome_legal, nomel, sizeof(nova_empresa->nome_legal) - 1);
    /****
    copia o valor de nomel para nova_empresa->nome_legal
    sizeof(nova_empresa->nome_legal) determina o tamanho máximo de caracteres da string nome para nova_empresa->nome_legal
    Simplificando, strncpy copia, no máximo, sizeof(nova_empresa->nome_legal) - 1 caracteres de nome para nova_empresa->nome_legal.
    ****/
    nova_empresa->nome_legal[sizeof(nova_empresa->nome_legal) - 1] = '\0';
    /*** assegura que a string novo->nome_legal seja terminado corretamente com \0 para indicar o fim da string ***/

    printf("\nCNPJ: ");
    scanf("%14d", &cnpj);

    nova_empresa->CNPJ = cnpj;

    printf("\nNome Fantasia: ");
    scanf("%15s", nomef);

    strncpy(nova_empresa->nome_fantasia, nomef, sizeof(nova_empresa->nome_fantasia) - 1);
    nova_empresa->nome_fantasia[sizeof(nova_empresa->nome_fantasia) - 1] = '\0';

    printf("\nResponsavel: ");
    scanf("%50s", respon);

    strncpy(nova_empresa->responsavel, respon, sizeof(nova_empresa->responsavel) - 1);
    nova_empresa->responsavel[sizeof(nova_empresa->responsavel) - 1] = '\0';

    printf("\nEmail: ");
    scanf("%40s", email_emp);

    strncpy(nova_empresa->email, email_emp, sizeof(nova_empresa->email) - 1);
    nova_empresa->email[sizeof(nova_empresa->email) - 1] = '\0';

    printf("\nRua: ");
    scanf("%50s", rua_emp);

    strncpy(nova_empresa->rua, rua_emp, sizeof(nova_empresa->rua) - 1);
    nova_empresa->rua[sizeof(nova_empresa->rua) - 1] = '\0';

    printf("\nNumero: ");
    scanf("%4d", &numero_emp);

    nova_empresa->numero = numero_emp;

    printf("\nBairro: ");
    scanf("%30s", bairro_emp);

    strncpy(nova_empresa->bairro, bairro_emp, sizeof(nova_empresa->bairro) - 1);
    nova_empresa->bairro[sizeof(nova_empresa->bairro) - 1] = '\0';

    printf("\nCidade: ");
    scanf("%15s", cidade_emp);

    strncpy(nova_empresa->cidade, cidade_emp, sizeof(nova_empresa->cidade) - 1);
    nova_empresa->cidade[sizeof(nova_empresa->cidade) - 1] = '\0';

    printf("\nPais: ");
    scanf("%10s", pais_emp);

    strncpy(nova_empresa->pais, pais_emp, sizeof(nova_empresa->pais) - 1);
    nova_empresa->pais[sizeof(nova_empresa->pais) - 1] = '\0';

    printf("\nData de abertura MM/AAAA: ");
    scanf("%2d/%4d", &mes_emp, &ano_emp);

    nova_empresa->mes = mes_emp;
    nova_empresa->ano = ano_emp;

    nova_empresa->proximo = *empresas;
    *empresas = nova_empresa;
    /*** esta adicionando a nova_empresa no inicio da lista
    qualquer empresa anterior à nova_empresa esta agora acessivel atraves do ponteiro proximo ***/

    printf("\nCadastro concluido com sucesso!!");

    menuinicial();
}

/*** funcao para liberar a memoria alocada quando nao necessitar mais dela ***/
void liberar_empresas(Empresa *empresas) {
    while (empresas != NULL) {
        Empresa *temporaria = empresas;
        /** cria uma variavel temporia que aponta para o no da lista empresas **/
        empresas = empresas->proximo;
        /** move o ponteiro empresas para o proximo no da lista continando a remocao **/
        free(temporaria);
        /** libera a memoria alocada para o no atual da lista, que é apontado por temporiaria **/
    }
}

