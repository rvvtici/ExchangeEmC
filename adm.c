#include <stdio.h>
#include <string.h>

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

int main(void) {
  struct ADM adm; 

  strcpy(adm.CPF_ADM, "12345678910"); // CPF ADM
  adm.SENHA_ADM = 123456; // SENHA ADM

  login_ADM(adm);

    return 0;
}