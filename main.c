#include <stdio.h>
#include <stdlib.h>

long long cpf;
int senha;
int cpf_confirmado = 0;
int senha_confirmada = 0;
int linha_usuario = 0;

int criar_usuarios (char *nome, long long cpf, int senha){
    FILE *fp = fopen(nome, "w");

    if(fp == NULL){
            printf("Erro na abertura do arquivo para leitura.\n");
            return 1;
    };

    fprintf(fp, "%lld\n", cpf);
    fprintf(fp, "%d\n", senha);
    for (int a = 0; a < 4; a ++) // saldo, btc, eth, xrp = 0 (1 linha pra cada)
        fprintf(fp, "%f\n", 0);

    fclose(fp);
    return 0;
}

int usuarios_txt() {
    FILE *fp = fopen("usuarios.txt", "w");

    if(fp == NULL){
            printf("Erro na abertura do arquivo para leitura.\n");
            return 1;
    };

    // fprintf(fp, "%lld\n", 12345678901);
    // fprintf(fp, "%lld\n", 98765432100);
    // fprintf(fp, "%lld\n", 12345678987);
    fprintf(fp, "%lld\n", 123);
    fprintf(fp, "%lld\n", 456);
    fprintf(fp, "%lld\n", 111);


    fclose(fp);
    return 0;
}

int conferirCPF(long long cpf){ //tambem pega em qual linha do usuarios.txt o cpf está. se estiver na 2 = user2.txt
    FILE *fp = fopen("usuarios.txt", "r");

    if(fp == NULL){
            printf("Erro na abertura do arquivo para leitura.\n");
            return 1;
    };

    long long cpf_busca;
    linha_usuario = 1;

    while (fscanf(fp, "%lld", &cpf_busca) != EOF){
        if (cpf_busca == cpf){
            cpf_confirmado = 1;
            break;
        }
        else
        linha_usuario++;
    }

    fclose(fp);
    return 0;
}

int conferir_senha(int senha){
    char nome[10];

    sprintf(nome, "user%d.txt", linha_usuario);
    FILE *fp = fopen (nome, "r");

    if(fp == NULL){
        printf("Erro na abertura do arquivo para conferir senha.\n");
        return 1;
    };

    int linha_arquivo = 0;
    int senha_busca;

    while (fscanf(fp, "%d", &senha_busca) != EOF){
        linha_arquivo++;
        if (linha_arquivo == 2)
            break;
    }

    if (senha == senha_busca)
        senha_confirmada = 1;

    fclose(fp);
    return 0;
};

void menu(){
    printf("---------------\n");
    printf("1. Consultar saldo\n");
    printf("2. Consultar extrato\n");
    printf("3. Depositar fundos\n");
    printf("4. Sacar fundos\n");
    printf("5. Compra de criptomoedas\n");
    printf("6. Venda de criptomoedas\n");
    printf("7. Atualizar cotacoes\n");
    printf("8. Menu\n");
    printf("0. Sair\n");
    printf("---------------\n");
};

int consultar_saldo(){
 
}

int depositar_fundos(){
  
}

int sacar_fundos(){

}

int consultar_extrato(){
   
}

int compra_criptomoedas(){

}

int venda_criptomoedas(){
    
}

int criar_arquivo_cotacao(){
 
}

int ler_arquivo_cotacao() {
    
}

void atualizar_moeda() {
   
}

int main(void){
    // por enquanto, criando os 3 usuarios.txt bem no começo.

    // criar_usuarios("user1.txt",(long long)12345678901, 123456);
    // criar_usuarios("user2.txt",(long long)98765432100, 123123);
    // criar_usuarios("user3.txt", (long long)12345678987, 321321);
    criar_usuarios("user1.txt",(long long)123, 123);
    criar_usuarios("user2.txt",(long long)456, 456);
    criar_usuarios("user3.txt", (long long)111, 111);

    //cria usuarios.txt com cpf dos 3 usuarios.
    usuarios_txt();

    printf("Boas vindas ao Exchange de Criptomoedas.\nPor favor, insira seu CPF e senha.\n");

        //cpf valido
        while(1){
        printf("CPF: ");
        scanf("%lld", &cpf);
        conferirCPF(cpf);

        if (cpf_confirmado == 1){
            break;
        }
        else
            printf("Insira um CPF valido.\n");
        }

        //senha valida
        while(1){
        printf("Senha: ");
        scanf("%d", &senha);
        conferir_senha(senha);

        if (senha_confirmada == 1){
            printf("Login confirmado!\n");
            break;
        }
        else
            printf("Senha incorreta. Insira sua senha novamente.\n");
        }
        if(senha_confirmada==1 && cpf_confirmado==1)
        menu();

        int i = 0;

        while(i>=0 && i<=8){
            printf("Selecione a operacao desejada ou digite 8 para ver o menu novamente: ");
            scanf("%d", &i);

            switch(i){
                case 1:
                    printf("1. Consultar saldo:\n");
                    consultar_saldo();
                    break;
                case 2:
                    printf("2. Consultar extrato:\n");
                    consultar_extrato(linha_usuario);
                    break;

                case 3:
                    printf("3. Depositar fundos:\n");
                    depositar_fundos();
                    break;
                case 4:
                    printf("4. Sacar fundos:\n");
                    sacar_fundos();
                    break;
                case 5:
                    printf("5. Compra de criptomoedas\n");
                    compra_criptomoedas();
                    break;
                case 6:
                    printf("6. Venda de criptomoedas\n");
                    venda_criptomoedas();
                    break;
                case 7:
                    printf("Atualizar cotacao de criptomoedas\n");
                    float btc, eth, xrp;
                    int selecao = 0;
                    criar_arquivo_cotacao("cotacao_criptomoedas.txt");
                    ler_arquivo_cotacao("cotacao_criptomoedas.txt", &btc, &eth, &xrp);
                    while (1) {
                        printf("Selecione 1 para atualizar a cotacao ou 0 para sair: ");
                        scanf("%d", &selecao);

                        if (selecao == 1) {
                            atualizar_moeda("cotacao_criptomoedas.txt", &btc, &eth, &xrp);
                            ler_arquivo_cotacao("cotacao_criptomoedas.txt", &btc, &eth, &xrp);
                        }else if (selecao == 0)
                            break;
                        else 
                            printf("Insira um digito valido.\n");

                    }
                    break;
                case 8:
                    menu();
                    break;
                    default:
                    printf("saindo...\n");
            //         //quando sair, zerar senha e cpf
                    // break;
        };//final do switch
    };//final while (pra inserir o i)
}//final int main(void)