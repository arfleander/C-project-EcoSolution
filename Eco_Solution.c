#include <stdio.h>
#include <ctype.h>
#include <string.h>

void main(){
    login();
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
    int opcao = 0;

    do{
        printf("\n\nSelecione a opcao que deseja acessar: \n1-Gerar Relatorios \n2-Cadastrar uma nova empresa \n3-Cadastrar um novo funcionario\n");
        scanf("%d", &opcao);

        //verifica qual opcao o usuario escolher
        switch(opcao){
        case 1:
            printf("Opcao para gerar relatorios");
            //gerarelat();
            break;
        case 2:
            printf("Opcao para cadastrar empresas");
            //cadastraemp();
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
