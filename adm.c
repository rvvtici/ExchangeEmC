#include <stdio.h>
#include <string.h>
#define MAX_CPF 12
#define MAX_NOME 200

struct ADM {
    char CPF_ADM[12];
    int SENHA_ADM;
};


int conferirCPF(long long cpf){
    int linha_busca = 0;
    long long cpf_busca;    

    FILE *fp = fopen("adm.txt", "r");

    if(fp == NULL){
            printf("erro na abertura do arquivo usuarios.txt para leitura.\n");
            return 1;
    };
    
    while (fscanf(fp, "%lld", &cpf_busca) != EOF){
        linha_busca++;
        if (linha_busca == 1)
            break;
        
    };

    if (cpf == cpf_busca)
        return 1;
    fclose(fp);
}

int conferir_senha(int senha){
    int senha_busca;
    int linha_busca = 0;

    FILE *fp = fopen ("adm.txt", "r");
    if(fp == NULL){
        printf("erro na abertura do arquivo para leitura (conferir senha).\n");
        return 1;
    };

    while (fscanf(fp, "%d", &senha_busca) != EOF){
        linha_busca++;        // armazena a senha correta, já que a 2ª linha
        if (linha_busca == 2) // no user[].txt, contem a senha do usuario.
            break;
    }
    if (senha == senha_busca)
        return 1;
    
    fclose(fp);
    return 0;
};

void MENU(){
    printf("\n--------------------------\n");
    printf("1. Cadastro de novo investidor\n");
    printf("2. Excluir investidor\n");
    printf("3. Cadastro de criptomoeda\n");
    printf("4. Excluir criptomoeda\n");
    printf("5. Consultar saldo de um investidor\n");
    printf("6. Consultar extrato de um investidor\n");
    printf("7. Atualizar cotacoes\n");
    printf("8. Menu\n");
    printf("0. Sair\n");
    printf("--------------------------\n");
};

void remover_CPF_do_arquivo(const char *cpf_remover) {//FUNÇÂO PARA REMOVER O USUARIO DO USUARIOS.TXT
  char cpf_atual[MAX_CPF];
  FILE *arquivo = fopen("usuarios.txt", "r");
  FILE *arquivo_temp = fopen("temp.txt", "w");

  if (arquivo == NULL || arquivo_temp == NULL) {
    printf("Erro ao abrir os arquivos para leitura/escrita.\n");
    return;
  }
  while (fgets(cpf_atual, sizeof(cpf_atual), arquivo) != NULL) {//LE AS LINHAS DO ARQUIVO
    cpf_atual[strcspn(cpf_atual, "\n")] = 0;//REMOVE A LINHA SE EXISTIR

    if (strcmp(cpf_atual, cpf_remover) != 0) {//ESCRITURA NO ARQUIVO TEMPORARIO
      fprintf(arquivo_temp, "%s\n", cpf_atual);
    }
  }
  fclose(arquivo);
  fclose(arquivo_temp);

  remove("usuarios.txt");//EXCLUI O ARQUIVO
  rename("temp.txt", "usuarios.txt");//RENOMEIA O ARQUIVO TEMPORARIO PARA O USUARIO.TXT
}

void contar_criptomoedas(int *qtde_linhas){ //contar qtde de criptomoedas
    FILE *fp = fopen("criptomoedas.txt", "r");

    if(fp == NULL){
        printf("erro na abertura do arquivo para leitura (criptomoedas.txt).\n");
        return;
    };

    char c;
    *qtde_linhas = 1;
    while((c = fgetc(fp)) != EOF){
        if (c == '\n')
            (*qtde_linhas)++;
    }

    fclose(fp);
}

void quantidade_investidores(int *quantidade_cpfs){
    int maximo_cpfs = 20;
    long long cpfs[maximo_cpfs];

    FILE *arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para cadastro (usuarios.txt)\n");
        return;
    }

    while (fscanf(arquivo, "%lld", &cpfs[*quantidade_cpfs]) != EOF && *quantidade_cpfs < maximo_cpfs) {
        (*quantidade_cpfs)++;
    }

    for (int j = 0; j < *quantidade_cpfs; j++)
        printf("cpf[%d] == %lld\n", j, cpfs[j]);

    fclose(arquivo);
}

int Novo_investidor(){//FUNCAO PARA INCLUIR NOVO INVESTIDOR
    int SENHA_N_INVEST;
    char NOME[MAX_NOME];
    long long CPF_N_INVEST;

    //contador cpfs e nova linha de cpf ao usuarios.txt
    int maximo_cpfs = 20;
    long long cpfs[maximo_cpfs];

    FILE *arquivo = fopen("usuarios.txt", "a+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para cadastro (usuarios.txt)\n");
        return 1;
    }

    int quantidade_cpfs = 0;
    int i = 0;

    while (fscanf(arquivo, "%lld", &cpfs[quantidade_cpfs]) != EOF && quantidade_cpfs < maximo_cpfs) {
        quantidade_cpfs++;
    }

    for (int j = 0; j < quantidade_cpfs; j++)
        printf("cpf[%d] == %lld\n", j, cpfs[j]);

    while(1){
        printf("Nome do investidor: ");
        scanf("%s", NOME);  
        printf("CPF do investidor (11 digitos): ");
        scanf("%lld", &CPF_N_INVEST);  
        printf("Senha do investidor (6 digitos): ");
        scanf("%d", &SENHA_N_INVEST);

        for (int j = 0; j < quantidade_cpfs; j++){
            printf("cpf[%d] == %lld\n", j, cpfs[j]);
            if(CPF_N_INVEST == cpfs[j]){
                printf("CPF de investidor ja cadastrado.\nCadastro cancelado.\n");
                return 0;}
        }if (CPF_N_INVEST < 10000000000 || CPF_N_INVEST > 99999999999 || SENHA_N_INVEST < 100000 || SENHA_N_INVEST > 999999){
            printf("CPF ou SENHA invalidos! Tente novamente!\n");
            continue;
        }

        else
            break;
    }

    fprintf(arquivo, "%lld\n", CPF_N_INVEST); // adiciona uma nova linha com o novo cpf no usuarios.txt
    fclose(arquivo);

    char nome[20];
    sprintf(nome, "user%d.txt", quantidade_cpfs + 1);
    FILE *arquivo_investidor = fopen (nome, "w");
    if(arquivo_investidor == NULL){
        printf("erro na criacao do txt de novo investidor\n");
        return 1;
    };
    fprintf(arquivo_investidor, "%lld\n",CPF_N_INVEST); //escrevendo informacoes no user%d.txt
    fprintf(arquivo_investidor, "%d\n", SENHA_N_INVEST);
    fprintf(arquivo_investidor,"%s\n", NOME);
    int quantidade_criptomoedas;
    contar_criptomoedas(&quantidade_criptomoedas);    
    for(int i = 0; i < quantidade_criptomoedas/5; i++) // 3 criptomoedas = 15/5 (5 linhas por cripto no criptomoedas.txt)
        fprintf(arquivo_investidor, "0.0\n");
    fclose(arquivo_investidor);
    // printf("quantidade criptomoedas: %d", quantidade_criptomoedas/5);

    //novo arquivo user%dextrato.txt, com extrato vazio.
    char nome2[20];
    sprintf(nome2, "user%dextrato.txt", quantidade_cpfs + 1);
    FILE *fp = fopen (nome2, "w");
    if(fp == NULL){
        printf("erro na criacao do txt de extrato de novo investidor\n");
        return 1;
    };

    printf("Cadastro efetuado!\n");
}

int Excluir_Investidor(){//FUNÇÂO PARA EXCLUIR QLQR INVESTIDOR
    long long cpf_investidor;
    int senha_login;
    int linha_usuario;

            while(1){
                printf("Digite o CPF de investidor: ");
                scanf("%lld", &cpf_investidor);
                if (buscar_linha_investidor(cpf_investidor, &linha_usuario))
                    break;
                else{
                    printf("Insira um CPF valido.\n");
                    continue;}
            }
    
    //FAZER A LOGICA DA PESQUISA DO CPF E APRESENTAR OS DADOS DAQUELE ARQUIVO DO INVESTIDOR
    consultar_saldo(cpf_investidor, linha_usuario);
    
    printf("Confirme a exclusao com a senha do administrador: ");
    scanf("%d", &senha_login);
    
    while(1){ //senha valida
        printf("Senha: ");
        scanf("%d", &senha_login);


        if (conferir_senha(senha_login)){
            printf("Login efetuado com sucesso!\n");
            break;
        }else{
            printf("Senha incorreta. Insira sua senha novamente.\n");
            continue;
        }
    }

    char nome_arquivo[50];
    snprintf(nome_arquivo, sizeof(nome_arquivo), "user%d.txt", linha_usuario);

    if (remove(nome_arquivo) == 0) {
        printf("Arquivo do investidor excluído com sucesso!\n");
    } else {
        printf("Erro ao excluir o arquivo do investidor. Verifique se o CPF está correto.\n");
        return -1;
    }

    remover_CPF_do_arquivo(cpf_investidor);//REMOVENDO DO USUARIOS.TXT
    printf("Investidor excluído com sucesso!\n");
    
    printf("Investidor excluido com sucesso!\n");
    return 0;
}

void Cadastro_Cript(){
    float tax_C, tax_V, Cot_In;
    char NOME[MAX_NOME], sigla[4];

    printf("Nome da moeda: ");
    scanf("%s", NOME);
    printf("Sigla da moeda (3 caracteres): ");
    scanf("%s", sigla);
    printf("Cotacao base: ");
    scanf("%f", &Cot_In);
    printf("Taxa de compra (%%): ");
    scanf("%f", &tax_C);
    printf("Taxa de venda (%%): ");
    scanf("%f", &tax_V);

    FILE *arquivo_Cripto  = fopen("criptomoedas.txt", "a");//CRIANDO ARQUIVO DAS CRIPTOMOEDAS
    if (arquivo_Cripto  == NULL) {
        printf("Erro ao cadastrar nova criptomoeda!\n");
        return;
    }
    //ESCREVENDO AS INFORMAÇOES NOS ARQUIVOS
    fprintf(arquivo_Cripto, "%s\n", NOME);
    fprintf(arquivo_Cripto, "%s\n", sigla);
    fprintf(arquivo_Cripto,"%f\n", Cot_In);
    fprintf(arquivo_Cripto, "%f\n", tax_C);
    fprintf(arquivo_Cripto, "%f\n", tax_V);
    fclose(arquivo_Cripto);
        
    printf("Moeda %s (%s) cadastrada com sucesso!\n", NOME, sigla);

    //adicionando nova linha a todos os usuarios, respectivo a nova moeda adicionada.
    int quantidade_cpfs = 0;
    quantidade_investidores(&quantidade_cpfs);
    printf("quantidade cpfs: %d", quantidade_cpfs);

    for (int i = 0; i < quantidade_cpfs; i++){
        char nome[20];
        sprintf(nome, "user%d.txt", i+1);
        FILE *fp = fopen(nome, "a");
        if (fp == NULL) {
            printf("erro ao abrir o arquivo para escrita (cadastro criptomoedas, user%d.txt).\n", i+1);
            return;}
        fprintf(fp, "0\n");
        fclose(fp);  
    }
   
}

// int Excluir_Cript(struct ADM adm){
//   char MOEDA[MAX_NOME];
//   int SENHA_CONFI;

//   printf(" ");
//   printf("--------------------EXCLUIR CRIPTOMOEDA--------------------\n");
//   printf("Qual sera a Criptomoeda de exclusao?: ");
//   scanf("%s", MOEDA);
//   //PEGAR O ARQUIVO QUE É DA CRIPTOMOEDA REFERENCE E PRINTAR
//   printf("Digite a senha para a confirmacao: ");
//   scanf("%d", &SENHA_CONFI);

//   while (SENHA_CONFI != adm.SENHA_ADM) { // Compara senha
//     printf("Senha incorreta! Tente novamente\n");
//     printf("Digite a senha para a confirmacao: ");
//     scanf("%d", &SENHA_CONFI); 
//   }
//   if (remove(MOEDA) == 0) {
//     printf("Criptomoeda excluída com sucesso!\n");
//   } else {
//     printf("Erro ao excluir a criptomoeda. Certifique-se de que o arquivo existe.\n");
//   }

//   return 0;
// }

int buscar_linha_investidor(long long cpf, int *linha_usuario){
    long long cpf_busca;
    *linha_usuario = 1;

    FILE *fp = fopen("usuarios.txt", "r");

    if(fp == NULL){
        printf("erro na abertura do arquivo usuarios.txt para leitura.\n");
        return 1;
    };
    
    while (fscanf(fp, "%lld", &cpf_busca) != EOF){
        if (cpf_busca == cpf){
            return 1; // cpf valido
            break;
        }else
            (*linha_usuario)++;
    };
    fclose(fp);
    printf("linha1: %d\n", linha_usuario);
    return 0;
}

void lerdadoscriptomoedas(char sigla[][4], char nome[][20], float *cotacao, float *taxavenda, float *taxacompra){
    FILE *fp = fopen("criptomoedas.txt", "r");

    if (fp == NULL){
        printf("erro\n");
        return;
    }
    
    for (int i = 0; i < 4; i++){
        fscanf(fp, "%s", sigla[i]);
        fscanf(fp, "%s", nome[i]);
        fscanf(fp, "%f", &cotacao[i]);
        fscanf(fp, "%f", &taxacompra[i]);
        fscanf(fp, "%f", &taxavenda[i]);
    }
}

void consultar_saldo(long long cpf_investidor, int linha_usuario){
    char nome[10];
    sprintf(nome, "user%d.txt", linha_usuario);
    FILE *fp = fopen (nome, "r");
    
    if(fp == NULL)
        printf("erro na abertura do arquivo para leitura (conferir saldo).\n");

    long long cpf;
    int senha;
    char nome_investidor[200];

    int quantidade_moedas = 0;
    contar_criptomoedas(&quantidade_moedas); // contar qtde criptomoedas
    quantidade_moedas = quantidade_moedas/5; //5 lihnas por criptomoeda no .txt

    float moedas[quantidade_moedas];
    fscanf(fp, "%lld", &cpf);   // cpf (descartavel, usando apenas pra pular pra próxima linha)
    fscanf(fp, "%d", &senha);   // senha (descartavel, igual o cpf)
    fscanf(fp, "%s", nome_investidor);   // nome (descartavel, igual o cpf)
    for (int k = 0; k < quantidade_moedas; k++) // saldo: reais, btc, eth, xrp (ficam da 3 a 6 linha)
        fscanf(fp, "%f", &moedas[k]);

    char sigla_cripto[4][4];
    char nome_cripto[4][20];
    float cotacao[4];
    float taxavenda[4];
    float taxacompra[4]; //adquirir nomes e siglas das criptomoedas
    lerdadoscriptomoedas(sigla_cripto, nome_cripto, cotacao, taxavenda, taxacompra);

    printf("Saldo atual: R$ %.2f\n", moedas[0]);
    for (int j = 0; j < quantidade_moedas; j++)
        printf("%s: %.6f %s\n", nome_cripto[j], moedas[j+1], sigla_cripto[j]);

    fclose(fp);
}

int Consultar_Extrato(){
  char CPF_INVESTIDOR[12];

  printf(" ");
  printf("--------------------CONSULTAR EXTRATO--------------------\n");
  printf("CPF do investidor para consulta: ");
  scanf("%s", CPF_INVESTIDOR);

  // while(CPF_INVESTIDOR != CPF NO ARQUIVO){
  //   printf("CPF INVALIDO TENTE NOVAMENTE!");
  //   printf("CPF do investidor para consulta: ");
  //   scanf("%s", CPF_INVESTIDOR);
  // }if(CPF_INVESTIDOR == CPF ARQUIVO){
  //   printf("ARQUIVOOOO");

  // }
  return 0;
}

int Atualizar_Cripto(){
  
  return 0;
}

int main(void) {
    long cpf_login;
    int senha_login;
    printf("Boas vindas ao programa administrador da Exchange de Criptomoedas.\nPor favor, insira o CPF e senha de administrador.\n");

    while(1){
        printf("CPF: "); //cpf valido
        scanf("%ld", &cpf_login);

        if (conferirCPF(cpf_login)) 
            break;                  
        else{
            printf("Insira um CPF valido.\n");
            continue;}
    }

    while(1){ //senha valida
        printf("Senha: ");
        scanf("%d", &senha_login);


        if (conferir_senha(senha_login)){
            printf("Login efetuado com sucesso!\n");
            break;
        }else{
            printf("Senha incorreta. Insira sua senha novamente.\n");
            continue;
        }
    }

    MENU();
    int opcao;
    do{
        printf("\nSelecione a operacao desejada ou digite 8 para ver o menu novamente: ");
        scanf("%d", &opcao);

        switch(opcao){
        case 1:
            printf("\n1. Cadastro de novo investidor:\n");
            Novo_investidor();
            break;
        case 2:
            printf("\n2. Excluir investidor:\n");
            Excluir_Investidor();
            // Excluir_Investidor(adm);
            break;
        case 3:
            printf("\n3. Cadastro de criptomoeda:\n");
            Cadastro_Cript();
            break;
        case 4:
            printf("\n4. Excluir criptomoeda:\n");
            // Excluir_Cript(adm);
            break;
        case 5:
            printf("\n5. Consultar saldo de um investidor:\n");
            long long cpf_investidor;
            int linha_usuario;

            while(1){
                printf("Digite o CPF de investidor: ");
                scanf("%lld", &cpf_investidor);
                if (buscar_linha_investidor(cpf_investidor, &linha_usuario))
                    break;
                else{
                    printf("Insira um CPF valido.\n");
                    continue;}
            }
            consultar_saldo(cpf_investidor, linha_usuario);
            break;
        case 6:
            printf("\n6. Consultar extrato de um investidor:\n");
            Consultar_Extrato();
            break;
        case 7:
            printf("\n7. Atualizar cotacoes:\n");
            Atualizar_Cripto();
            break;
        case 8:
            printf("\n8. Menu:\n");
            MENU();
            break;
        case 0:
            printf("\nVoce saiu do sistema. Ate logo!\n");
            break;
        default:
            printf("\nOpcao invalida\n");
            break;
        }
    } while (opcao != 0);
  return 0;
}