#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*** cria estrutura DadosResiduos para armazenar o historico dos residuos ambientais ***/
typedef struct dadosresiduos{
    int id_residuos;
    int mes;
    int ano;
    int qtde;
    struct dadosresiduos *proximo;
}DadosResiduos;

/*** cria estrutura Residuos para armazenar os dados dos residuos ambientais ***/
typedef struct residuo{
    char empresa_respon[31];
    int CNPJ;
    char nome[21];
    int id;
    float valor_custo;
    DadosResiduos *historico;
    struct residuo *proximo;
}Residuo;

/*** cria estrutura Funcionario para armazenar os dados dos funcionarios ***/
typedef struct funcionario{
    char empresa_respon[31];
    int CNPJ;
    char nome[31];
    char sobrenome[21];
    char data_nasc[11];
    int CPF;
    char RG[11];
    char genero[11];
    char email[41];
    char estado_civil[10];
    int renda;
    char rua[51];
    int numero;
    char bairro[31];
    char cidade[16];
    char pais[11];
    struct funcionario *proximo;
}Funcionario;

/*** cria estrutura Empresa para armazenar os dados das empresas ***/
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
        Residuo *historico_residuo;
        Funcionario *historico_funcionario;
        struct empresa *proximo;
}Empresa;

/*** inicializa a estrutura Empresa vazia ***/
Empresa* empresas = NULL;

/*** inicializa a estrutura Funcionario vazia ***/
Funcionario* funcionarios = NULL;

/*** inicializa a estrutura Residuos vazia ***/
Residuo* residuos = NULL;

/*** inicializa a estrutura DadosResiduos vazia ***/
DadosResiduos* historico_residuos = NULL;

/** prototipo para a funcao atualizaresiduo ***/
Residuo* atualizaresiduo(Residuo **residuos, DadosResiduos **historico_residuos);

/** prototipo para a funcao gerenciarresiduos ***/
Empresa* gerenciarresiduos(Empresa **empresas, DadosResiduos **historico_residuos, Residuo **residuos);


/*** funcao para usuario acessar no sistema ***/
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

/*** funcao para usuario ja cadastrado entrar no sistema ***/
void usuariocadastrado(char* novo_user,  char* nova_senha){
    char user[31], senha[21];

    do{
        printf("\nInforme o seu usuario (max 30): ");
        scanf("%30s", user);

        if(strcmp(user, novo_user) == 0){
            printf("\nDigite sua senha (max 20): ");
            scanf("%20s", senha);

            if(strcmp(senha, nova_senha) == 0 && senha != ""){
                printf("\n\nOla %s. Bem-vindo ao menu inicial da Eco Solution!\n", user);
                menuprincipal();

            }else{
                printf("\nSenha incorreta. Tente novamente");
            }

        }else{
            printf("\nUsuario incorreto. Tente novamente!");

        }
    }while(1);
}

/*** funcao para cadastrar novo usuario ***/
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

/*** funcao para menu principal para acessar o sistema ***/
void menuprincipal(){
    int opcao = 0, escolha = 0;

    do{
        printf("\nSelecione a opcao que deseja acessar: \n1-Cadastrar uma nova empresa \n2-Cadastrar um novo funcionario \n3-Cadastrar novo residuo \n4-Atualizar residuos \n5-Gerar relatorio de total de residuos por empresa \n6-Gerar relatorio de gastos mensais \n7-Localizar regioes mais poluidas \n8-Localizar industrias menos impactam \n9-Sair\n");
        scanf("%d", &opcao);

        /*** verifica qual opcao o usuario escolher ***/
        switch(opcao){
        case 1:
            insereemp(&empresas);
            break;
        case 2:
            inserefunc(&funcionarios, &empresas);
            break;
        case 3:
            insereresiduo(&residuos, &empresas);
            break;
        case 4:
            atualizaresiduo(&residuos, &historico_residuos);
            break;
        case 5:
            gerenciarresiduos(&empresas, &historico_residuos, &residuos);
            break;
        default:
            printf("\nOpcao invalida. Tente novamente!\n");
            break;
        }
    }while(opcao < 1 || opcao > 3); //loop ate escolher valor entre 1 e 3
}

/*** funcao para cadastrar novas empresas ***/
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

    printf("\nCadastro concluido com sucesso!!\n");

    menuprincipal();
}

/** funcao para cadastrar novos funcionarios ***/
void inserefunc(Funcionario **funcionarios, Empresa **empresas){
    char empresa_responsavel[31], nome_func[31], sobrenome_func[21], data_nascimento[11], rg[11], genero_func[11], email_func[41], estado_func[10], rua_func[51], bairro_func[31], cidade_func[16], pais_func[11];
    int cnpj, cpf, renda_func, numero_func;
    /*** cria variaveis auxiliares para armazenar os valores ***/

    Empresa *aux; /** variavel auxiliar para percorrer a lista empresa **/

    Funcionario* novo_funcionario = malloc(sizeof(Funcionario));
    /*** aloca espaço na memória para a estrutura ***/

    printf("\n\nCadastro de novo Funcionario!\n");

    printf("\nEmpresa responsavel: ");
    scanf("%30s", empresa_responsavel);
    strncpy(novo_funcionario->empresa_respon, empresa_responsavel, sizeof(novo_funcionario->empresa_respon) - 1);
    novo_funcionario->empresa_respon[sizeof(novo_funcionario->empresa_respon) - 1] = '\0';

    /** repete ate que encontre o CNPJ inserido esteja na lista empresas **/
    do{
        printf("\nCNPJ da empresa: ");
        scanf("%14d", &cnpj);

        /** busca na lista empresas **/
        for(aux = *empresas; aux != NULL; aux = aux->proximo){
            /** verifica se o valor é correspondente ao que está na lista empresas **/
            if(aux->CNPJ == cnpj){
                novo_funcionario->CNPJ = cnpj;
                cnpj = (*empresas)->CNPJ; /** vincula o CNPJ do residuo ao CNPJ da empresa **/
                break;
            }else{
                printf("\nCNPJ nao cadastrado! Tente novamente\n");
            }
        }
    }while(aux == NULL);

    printf("\nNome: ");
    scanf("%30s", nome_func);
    strncpy(novo_funcionario->nome, nome_func, sizeof(novo_funcionario->nome) - 1);
    novo_funcionario->nome[sizeof(novo_funcionario->nome) - 1] = '\0';

    printf("\nSobrenome: ");
    scanf("%20s", sobrenome_func);
    strncpy(novo_funcionario->sobrenome, sobrenome_func, sizeof(novo_funcionario->sobrenome) - 1);
    novo_funcionario->sobrenome[sizeof(novo_funcionario->sobrenome) - 1] = '\0';

    printf("\nCPF: ");
    scanf("%11d", &cpf);

    novo_funcionario->CPF = cpf;

    printf("\nRG: ");
    scanf("%10s", rg);

    strncpy(novo_funcionario->RG, rg, sizeof(novo_funcionario->RG) - 1);
    novo_funcionario->RG[sizeof(novo_funcionario->RG) - 1] = '\0';

    printf("\nData de Nascimento (DD/MM/AAAA): ");
    scanf("%10s", data_nascimento);

    strncpy(novo_funcionario->data_nasc, data_nascimento, sizeof(novo_funcionario->data_nasc) - 1);
    novo_funcionario->data_nasc[sizeof(novo_funcionario->data_nasc) - 1] = '\0';

    printf("\nGenero: ");
    scanf("%10s", genero_func);

    strncpy(novo_funcionario->genero, genero_func, sizeof(novo_funcionario->genero) - 1);
    novo_funcionario->genero[sizeof(novo_funcionario->genero) - 1] = '\0';

    printf("\nEmail: ");
    scanf("%40s", email_func);

    strncpy(novo_funcionario->email, email_func, sizeof(novo_funcionario->email) - 1);
    novo_funcionario->email[sizeof(novo_funcionario->email) - 1] = '\0';

    printf("\nEstado Civil: ");
    scanf("%9s", estado_func);

    strncpy(novo_funcionario->estado_civil, estado_func, sizeof(novo_funcionario->estado_civil) - 1);
    novo_funcionario->estado_civil[sizeof(novo_funcionario->estado_civil) - 1] = '\0';

    printf("\nRenda mensal: ");
    scanf("%d", &renda_func);

    novo_funcionario->renda = renda_func;

    printf("\nRua: ");
    scanf("%50s", rua_func);

    strncpy(novo_funcionario->rua, rua_func, sizeof(novo_funcionario->rua) - 1);
    novo_funcionario->rua[sizeof(novo_funcionario->rua) - 1] = '\0';

    printf("\nNumero: ");
    scanf("%4d", &numero_func);

    novo_funcionario->numero = numero_func;

    printf("\nBairro: ");
    scanf("%30s", bairro_func);

    strncpy(novo_funcionario->bairro, bairro_func, sizeof(novo_funcionario->bairro) - 1);
    novo_funcionario->bairro[sizeof(novo_funcionario->bairro) - 1] = '\0';

    printf("\nCidade: ");
    scanf("%15s[^\n]", cidade_func);
    while (getchar() != '\n');

    strncpy(novo_funcionario->cidade, cidade_func, sizeof(novo_funcionario->cidade) - 1);
    novo_funcionario->cidade[sizeof(novo_funcionario->cidade) - 1] = '\0';

    printf("\nPais: ");
    scanf("%10s", pais_func);

    strncpy(novo_funcionario->pais, pais_func, sizeof(novo_funcionario->pais) - 1);
    novo_funcionario->pais[sizeof(novo_funcionario->pais) - 1] = '\0';


    novo_funcionario->proximo = (*empresas)->historico_funcionario;/** vincula o historico do funcionario ao historico da empresa **/
    (*empresas)->historico_funcionario = novo_funcionario; /** atualiza o historico da empresa para apontar para o novo funcionario **/


    printf("\nCadastro concluido com sucesso!!\n");

    menuprincipal();

}

/*** funcao para cadastrar novos residuos ambientais ***/
void insereresiduo(Residuo **residuos, Empresa **empresas){

    /*** cria variaveis auxiliares para armazenar os valores ***/
    char responsavel[31], nome_residuo[21];
    int cnpj, id_residuo;
    float valor_residuo;

    Empresa *aux; /** variavel auxiliar para percorrer a lista empresa **/

    Residuo* novo_residuo = malloc(sizeof(Residuo));
    /*** aloca espaço na memória para a estrutura ***/

    printf("\n\nCadastro de novo Residuo!\n");

    printf("\nEmpresa responsavel: ");
    scanf("%30s", responsavel);

    strncpy(novo_residuo->empresa_respon, responsavel, sizeof(novo_residuo->empresa_respon) - 1);
    novo_residuo->empresa_respon[sizeof(novo_residuo->empresa_respon) - 1] = '\0';

    /** repete ate que encontre o CNPJ inserido esteja na lista empresas **/
    do{
        printf("\nCNPJ da empresa: ");
        scanf("%14d", &cnpj);

        /** busca na lista empresas **/
        for(aux = *empresas; aux != NULL; aux = aux->proximo){
            /** verifica se o valor é correspondente ao que está na lista empresas **/
            if(aux->CNPJ == cnpj){
                novo_residuo->CNPJ = cnpj;
                cnpj = (*empresas)->CNPJ; /** vincula o CNPJ do residuo ao CNPJ da empresa **/
                break;
            }else{
                printf("\nCNPJ nao cadastrado! Tente novamente\n");
            }
        }
    }while(aux == NULL);

    printf("\nNome do residuo: ");
    scanf("%30s", nome_residuo);

    strncpy(novo_residuo->nome, nome_residuo, sizeof(novo_residuo->nome) - 1);
    novo_residuo->nome[sizeof(novo_residuo->nome) - 1] = '\0';

    printf("\nID do Residuo: ");
    scanf("%d", &id_residuo);

    novo_residuo->id = id_residuo;

    printf("\nValor estimado de custo: ");
    scanf("%f", &valor_residuo);

    novo_residuo->proximo = (*empresas)->historico_residuo;/** vincula o historico do funcionario ao historico da empresa **/
    (*empresas)->historico_residuo = novo_residuo; /** atualiza o historico da empresa para apontar para o novo funcionario **/

    printf("\nCadastro concluido com sucesso!!\n");

    menuprincipal();
}

/*** funcao para buscar ID em Residuo e cadastra novos dados em DadosResiduos ***/
Residuo* atualizaresiduo(Residuo **residuos, DadosResiduos **historico_residuos){
    int id_busca, mes_historico, ano_historico, qtde_historico;

    printf("\nAtualizar residuos\n");

    printf("Digite o ID de residuo para buscar: ");
    scanf("%d", &id_busca);

    Residuo* aux; /*** variável auxiliar para percorrer a lista residuos ***/

    /*** busca o item na lista residuos ***/
    for(aux = *residuos; aux != NULL; aux = aux->proximo){
        if(aux->id == id_busca){ /*** verifica se o item é correspondente ***/

            DadosResiduos *atualiza_residuo = malloc(sizeof(DadosResiduos));

            atualiza_residuo->id_residuos = id_busca;

            printf("\nDigite a data da atualizacao (MM/AAAA): ");
            scanf("%2d/%4d", &mes_historico, &ano_historico);

            atualiza_residuo->mes = mes_historico;
            atualiza_residuo->ano = ano_historico;

            printf("\nDigite a quantidade de residuos: ");
            scanf("%d", &qtde_historico);

            atualiza_residuo->qtde = qtde_historico;

            /*** definindo a variavel proximo da DadoResiduos como apontando para o historico existente de Residuo
            garantindo que o novo registro de historicos seja vinculado ao registro existente ***/
            atualiza_residuo->proximo = aux->historico;
            /*** atualizando o campo historico de Residuo para apontar para o novo registro de historico atualiza_residuo
            feito para refletir a atualizacao do historico na estrutura principal Residuo ***/
            aux->historico = atualiza_residuo;

            printf("\nAtualizacao de residuo cadastrada com sucesso!!\n");
            return aux;
        }
    }

    printf("ID de residuos nao encontrado! Tente novamente");
    menuprincipal();
    return NULL; /*** retorna lista vazia caso nao encontre o ID ***/


}

/** funcao para gerar relatorios de total de residuos por empresa e ID **/
Empresa* gerenciarresiduos(Empresa **empresas, DadosResiduos **historico_residuos, Residuo **residuos){
    int cnpj, id_busca, somaqtdes = 0;

    printf("\nRelatorio de total de residuos por empresa!");
    printf("\n\n Digite o CNPJ da empresa para a busca: ");
    scanf("%14d", &cnpj);
    printf("\nDigite o ID do residuo para a busca: ");
    scanf("%d", &id_busca);

    Empresa* auxempresa; /** variável auxiliar para percorrer a lista empresas **/
    Residuo* auxresiduo; /** variável auxiliar para percorrer a lista residuos **/
    DadosResiduos* auxdados; /** variável auxiliar para percorrer a lista dadosresiduos **/


	/*** percorre a lista empresas ***/
    for(auxempresa = *empresas; auxempresa != NULL; auxempresa = auxempresa->proximo){
        /*** percorre a lista residuos ***/
        for(auxresiduo = *residuos; auxresiduo != NULL; auxresiduo = auxresiduo->proximo){
            /** verifica se CNPJ e ID digitados estao nas listas **/
            if(auxempresa->CNPJ == cnpj && auxresiduo->id == id_busca){

                printf("\nCNPJ %d e ID %d encontrados com sucesso! Gerando relatorios...", cnpj, id_busca);

                /** percorre a lista encadeada de historico de dados de residuos **/
                for(auxdados = auxresiduo->historico; auxdados != NULL; auxdados = auxdados->proximo){
                        /** verifica se o id existe na lista dadosresiduos para nao acumular todas as qtdes rda lista **/
                        if(auxdados->id_residuos == id_busca){

                            /** acumula as quantidades encontradas na variavel somaqtdes **/
                            somaqtdes += auxdados->qtde;
                        }
                }

                /** imprime relatorio **/
                printf("\nEmpresa: %s\nCNPJ: %d\nResiduo: %s\nID Residuo: %d\nSoma de quantidades do residuos: %d\n",
                       auxempresa->nome_legal, auxempresa->CNPJ, auxresiduo->nome, auxresiduo->id, somaqtdes);
                       break;
            }else{
                 /*** termina a funcao se o ID nao for encontrado ***/
                printf("ID de residuo ou CNPJ nao encontrado! Tente novamente");
                break;
            }
        }
    }
    /*** termina a funcao se o CNPJ nao for encontrado ***/
	printf("CNPJ nao encontrado! Tente novamente");
    menuprincipal();
}

/*** funcao para liberar a memoria alocada por Empresa quando nao necessitar mais dela ***/
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

/*** funcao para liberar a memoria alocada por Funcionario quando nao necessitar mais dela ***/
void liberar_funcionarios(Funcionario *funcionarios) {
    while (funcionarios != NULL) {
        Funcionario *temporaria = funcionarios;
        funcionarios = funcionarios->proximo;
        free(temporaria);
    }
}

/*** funcao para liberar a memoria alocada por Residuo quando nao necessitar mais dela ***/
void liberar_residuos(Residuo *residuos) {
    while (residuos != NULL) {
        Residuo *temporaria = residuos;
        residuos = residuos->proximo;
        free(temporaria);
    }
}

/*** funcao para liberar a memoria alocada por DadosResiduos quando nao necessitar mais dela ***/
void liberar_dadosresiduos(DadosResiduos *historico_residuos) {
    while (historico_residuos != NULL) {
        DadosResiduos *temporaria = historico_residuos;
        historico_residuos = historico_residuos->proximo;
        free(temporaria);
    }
}


void main(){
    login();
    liberar_empresas(&empresas);
    liberar_funcionarios(&funcionarios);
    liberar_residuos(&residuos);
    liberar_dadosresiduos(&historico_residuos);
}
