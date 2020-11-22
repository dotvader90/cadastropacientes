#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

int main()
{
    char op;
    printf("Bem vindo ao sistema covid-19 \n\n");

    do
    {
        printf("Digite 1 para cadastrar usuario. \n\n");
        printf("Digite 2 para logar no sistema. \n\n");
        printf("Digite 9 para encerrar. \n\n");

        fflush(stdin);
        op = getch();

        switch(op)
        {
            case '1':
                cadastrar_usuario();
            break;
            case '2':
                login();
            break;
        }
    }while(op != '9');


    return 0;
}

int cadastrar_usuario()
{
   FILE *fp;
   char usuario[50];
   char senha[10];
   char nome[50];

   printf("\n\nDigite o usuario: ");
   fgets(usuario, sizeof(usuario), stdin);

   printf("Digite o nome: ");
   fgets(nome, sizeof(nome), stdin);

   printf("Digite a senha contendo no maximo 10 caracteres: ");
   fgets(senha, sizeof(senha), stdin);

   char str[110];
   sprintf(str, "%s;%s;%s", strtok(usuario, "\n"), strtok(nome, "\n"), strtok(senha, "\n"));

   fp = fopen("\\data\\cadastroUsuario.txt", "r+");
   fseek(fp, 0, SEEK_END);

   fprintf(fp, "%s", "\n");
   fprintf(fp, "%s", str);

   fclose(fp);

   return 0;
}

void login()
{
   FILE *fp;
   char usuario[50];
   char senha[10];
   char line[110];
   bool logado = false;

   printf("\n\nDigite o usuario: ");
   fgets(usuario, sizeof(usuario), stdin);

   printf("Digite a senha: ");
   fgets(senha, sizeof(senha), stdin);

   fp = fopen("C:\\data\\cadastroUsuario.txt", "r");

   while(fgets(line, sizeof(line), fp) != NULL)
   {
      char delim[] = ";";
      char *ptr = strtok(line, delim);

      if(*usuario == *ptr)
      {
         char nome[50];

         ptr = strtok(NULL, delim);
         strncpy(nome, ptr, sizeof(nome));

         ptr = strtok(NULL, delim);
         if(*senha == *ptr)
         {
             printf("Bem vindo %s! \n", nome);
             printf("%s", "\n\n");

             logado = true;
         }
         break;
      }
   }

   fclose(fp);

   if(logado == false)
   {
     printf("Usuario ou senha invalido! \n");
     printf("%s", "\n\n");
     return 0;
   }

   menu_logado();
   return 0;
}

int menu_logado()
{
    char op;
    do
    {
        printf("Digite 1 para cadastrar paciente. \n\n");
        printf("Digite 9 para encerrar. \n\n");

        op = getch();

        switch(op)
        {
            case '1':
                cadastrar_paciente();
            break;
        }
    }while(op != '9');


    return 0;
}

int cadastrar_paciente()
{
   char nome[100];
   char idade[3];
   int age;
   char cpf[20];
   char telefone[20];
   char endereco[200];
   char cep[20];
   char dtNascimento[10];
   char email[20];
   char dtDiagnostico[10];
   char comorbidade[50];

   printf("\n\nDigite o nome do paciente: ");
   fgets(nome, sizeof(nome), stdin);

   printf("\n\nDigite a idade: ");
   fgets(idade, sizeof(idade), stdin);
   age = atoi(idade);
   fflush(stdin);
   printf("\n\nDigite o CPF: ");
   fgets(cpf, sizeof(cpf), stdin);

   printf("\n\nDigite o telefone: ");
   fgets(telefone, sizeof(telefone), stdin);

   printf("\n\nDigite o endereço (logradouro, numero, bairro, cidade e estado): ");
   fgets(endereco, sizeof(endereco), stdin);

   printf("\n\nDigite o CEP: ");
   fgets(cep, sizeof(cep), stdin);

   printf("\n\nDigite a data de nascimento: ");
   fgets(dtNascimento, sizeof(dtNascimento), stdin);

   fflush(stdin);
   printf("\n\nDigite o email: ");
   fgets(email, sizeof(email), stdin);

   fflush(stdin);

   printf("\n\nDigite a data do diagnostico: ");
   fgets(dtDiagnostico, sizeof(dtDiagnostico), stdin);

   fflush(stdin);

   printf("\n\nDigite a comorbidade: ");
   fgets(comorbidade, sizeof(comorbidade), stdin);

   if(age >= 65 && comorbidade != NULL)
   {
       FILE *fp;
       fp = fopen("C:\\data\\grupoRisco.txt", "r+");
       fseek(fp, 0, SEEK_END);

       char str[20];
       sprintf(str, "%s;%s", strtok(cep, "\n"), strtok(idade, "\n"));
       fprintf(fp, "%s", "\n");
       fprintf(fp, "%s", str);
       fclose(fp);

       printf("\nPaciente em grupo de risco cadastrado em arquivo.\n");

   }

   FILE *fp;
   char str[10000];

   fp = fopen("C:\\data\\pacientesInfectados.txt", "r+");
   fseek(fp, 0, SEEK_END);

   sprintf(str, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;", strtok(nome, "\n"), strtok(idade, "\n"), strtok(cpf, "\n"), strtok(telefone, "\n"),
           strtok(endereco, "\n"), strtok(cep, "\n"), strtok(dtNascimento, "\n"), strtok(email, "\n"), strtok(dtDiagnostico, "\n"),
           strtok(comorbidade, "\n"));

   fprintf(fp, "%s", "\n");
   fprintf(fp, "%s", str);
   fclose(fp);

   return 0;
}
