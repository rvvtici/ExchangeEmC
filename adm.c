#include <stdio.h>
#include <string.h>
#define MAX_CPF 12
#define MAX_NOME 200

struct ADM {
    char CPF_ADM[12];
    int SENHA_ADM;
};

int login_ADM(struct ADM adm) { 
    char cpf_escrito[12]; // Array para armazenar o CPF digitado
    int senha_escrita;

    printf("--------------------EFETUE O LOGIN--------------------\n");
    printf("CPF: ");
    scanf("%s", cpf_escrito); // Limita a entrada a 11 caracteres
    printf("SENHA: ");
    scanf("%d", &senha_escrita); // Adicionando o operador &

    while (strcmp(cpf_escrito, adm.CPF_ADM) != 0 || senha_escrita != adm.SENHA_ADM) { // Compara CPF e senha
        printf("CPF ou Senha incorreto(os)! Tente novamente\n");
        printf("--------------------EFETUE O LOGIN--------------------\n");
        printf("CPF: ");
        scanf("%s", cpf_escrito); // Limita a entrada a 11 caracteres
        printf("SENHA: ");
        scanf("%d", &senha_escrita); // Adicionando o operador &
    }
    printf("Login Efetuado com sucesso!\n"); // Mensagem de sucesso
    return 0;

};

int MENU(){
  printf(" ");
  printf("--------------------BEM_VINDO AO MENU--------------------\n");
  printf("1.Cadastro de novo investidor\n");
  printf("2.Excluir investidor\n");
  printf("3.Cadastro de criptomoeda\n");
  printf("4.Excluir criptomoeda\n");
  printf("5.Consultar saldo de um investidor\n");
  printf("6.Consultar extrado de um investidor\n");
  printf("7.Atualizar cotação de criptomoedas\n");
};

int Novo_investidor(){//FUNCAO PARA INCLUIR NOVO INVESTIDOR
  int SENHA_N_INVEST;
  char NOME[MAX_NOME], CPF_N_INVEST[MAX_CPF];
  printf(" ");
  printf("--------------------CADASTRO DO NOVO INVESTIDOR--------------------\n");

    printf("NOME DO INVESTIDOR: ");
    scanf("%s", NOME);  

    printf("CPF DO INVESTIDOR: ");
    scanf("%s", CPF_N_INVEST);  

    printf("SENHA DO INVESTIDOR: ");
    scanf("%d", &SENHA_N_INVEST);  

    // Validação de CPF e senha
    while (strlen(CPF_N_INVEST) != 11 || SENHA_N_INVEST < 100000 || SENHA_N_INVEST > 999999) {
        printf("CPF ou SENHA incorretos! Tente novamente!\n");

        printf("NOME DO INVESTIDOR: ");
        scanf("%s", NOME);

        printf("CPF DO INVESTIDOR: ");
        scanf("%s", CPF_N_INVEST);

        printf("SENHA DO INVESTIDOR: ");
        scanf("%d", &SENHA_N_INVEST);
    }
    
    printf("Cadastro Efetuado!\n");
    return 0;
}

int Excluir_Investidor(struct ADM adm){
  char CPF_INVESTIDOR[12];
  int SENHA_CONF;
  
  printf(" ");
  printf("--------------------EXCLUIR INVESTIDOR--------------------\n");
  printf("Qual é o CPF do investidor: ");
  scanf("%s", CPF_INVESTIDOR);
  
  //FAZER A LOGICA DA PESQUISA DO CPF E APRESENTAR OS DADOS DAQUELE ARQUIVO DO INVESTIDOR
  
  printf("Confirme a exclusao com a senha do administrador: ");
  scanf("%d", &SENHA_CONF);
  
  while (SENHA_CONF != adm.SENHA_ADM) { // Compara senha
    printf("Senha incorreta! Tente novamente\n");
    printf("SENHA: ");
    scanf("%d", &SENHA_CONF); 
  }
  
  printf("Investidor excluido com sucesso!\n");
}

int Cadastro_Cript(){
  float tax_C, tax_V, Cot_In;
  char NOME[MAX_NOME];
  printf(" ");
  printf("--------------------CADASTRO CRIPTOMOEDA--------------------\n");
  
  printf("Nome da Moeda: ");
  scanf("%s", NOME);

  printf("Cotação inicial: ");
  scanf("%f", &Cot_In);

  printf("Taxa de compra(%%): ");
  scanf("%f", &tax_C);

  printf("Taxa de venda(%%): ");
  scanf("%f", &tax_V);

  printf("Moeda Cadastrada com Sucesso!\n");
}

int main(void) {
  struct ADM adm; 
  int opcao;

  strcpy(adm.CPF_ADM, "1"); // CPF ADM
  adm.SENHA_ADM = 12; // SENHA ADM
  login_ADM(adm);
  MENU();
  printf("Opçao: ");
  scanf("%d", &opcao);
  switch(opcao){
    case 1:
      Novo_investidor();
      break;
    case 2:
      Excluir_Investidor(adm);
      break;
    case 3:
      Cadastro_Cript();
      break;
    case 4:
      printf("opção 4\n");
      break;
    case 5:
      printf("opção 5\n");
      break;
    case 6:
      printf("opção 6\n");
      break;
    case 7:
      printf("opção 7\n");
      break;
    default:
      printf("opcao invalida\n");
      break;
    }
  return 0;

}