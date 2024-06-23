#include<stdio.h>
#include<string.h>
#include<stdlib.h>

    typedef unsigned char bool; //Definição do tipo de variável booleana
    #define false 0
    #define true !false

void clear_terminal() //Função que realiza a limpeza do terminal, de acordo com o sistema operacional, na execução de cada aba do programa
    {
        #ifdef __linux__
          system("clear");
        #else
          system("cls");
        #endif
    }
void clear_buffer() //Função para que o caracter gerado pela tecla enter não atrapalhe o funcionamento da função "clique_continuar"
    {
        getchar();
    }
void press_to_continue() //Função que realiza a instrução de ordenamento e transição entre as funcionalidades do programa
    {
        printf("\n\nPress ENTER to continue... ");
        getchar();
    }

int option;

// =================================================================================================================
// Tópico 1
// =================================================================================================================
void menu()
    {

        printf("======================================\nHELLO, USER!\n======================================\n\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Edit profiles\n");
        printf("4. Exit\n");
        printf("\nChoose an option: ");
        scanf("%d", &option); //Recebe a opção
        clear_buffer();
        press_to_continue();
        clear_terminal();

    }

void user_registration() //Função responsável pela exibição e funcionamento da aba de cadastramento do usuário
    {
        //Declaração de file e variável
        char user[50];
        char password[50];
        char loginPassword[20];
        FILE *file;

        clear_terminal();
        printf("======================================\nADD USER\n======================================\n\n");
        //Mostrando exemplos dos dados a ser cadastrados
        printf("Username: usuario\n");
        printf("Password: senha\n\n");
        //Cadastrando os dados
        printf("-> username: ");
            scanf("%s", user); //Recebe o cadastramento do usuário
        printf("-> password: ");
            scanf("%s", password); //Recebe o cadastramento da senha do usuário
        do{printf("-> confirm password: ");
           scanf("%s", loginPassword); //Recebe uma confirmação da senha
            if(strcmp(password, loginPassword) == 0)
                {
                    file = fopen("usuarios.txt", "a+");//Abre arquivo "users3.txt" e escreve usuário e senha ao final dele
                    if (file == NULL) {
                        printf("\n\nError opening file!\n");
                        exit(1);
                    }
                    fprintf(file, "%s %s\n", user, password);//Grava senha e nome do usuário em um arquivo '.txt'
                    printf("\nThe user was successfully registered!\n");
                    fclose(file);
                    clear_buffer();
                    press_to_continue();
                    clear_terminal();
                 }
        else
            printf("\nThe passwords do not match. Try again!\n\n");

        }while(strcmp(password,loginPassword) != 0);

    }
void login() //Função responsável pela exibição e funcionamento da aba de login
    {
        //Declaração de variáveis e file
        int controlUser = 1, controlPassword = 1;
        char loginPassword[20], loginUser[20], user[50], password[50];
        FILE *file;

        printf("======================================\nLogin\n======================================\n\n");
        do {
            //Obtêm senha e usuário para login
            printf("Enter your username: ");
                scanf("%s", user);
            printf("Enter your password: ");
                scanf("%s", password);
            //Abre arquivo em modo leitura
            file = fopen("usuarios.txt", "r");
            if (file == NULL)
                {
                  printf("\nError opening file.\n");
                  exit(1);
                }

            while (fscanf(file,"%s %s\n", loginUser, loginPassword) != EOF) {//Lê arquivo todo até chegar ao fim, buscando por duas strings específicas
                controlUser = strcmp(user, loginUser);
                controlPassword = strcmp(password, loginPassword);
                if (controlUser == 0 && controlPassword == 0) {//Se encontrar, no arquivo, senha e usuário digitados executará o login
                    printf("\n-> Login successful\n");
                    clear_buffer();
                    press_to_continue();
                    clear_terminal();
                }
            }

            printf("\n-> Login failed (incorrect username or password). Try again!\n\n");
        } while(1);
      fclose(file);
    }

void users_list()
{
    clear_buffer();
    press_to_continue();
    clear_terminal();

    FILE *file = fopen("usuarios.txt", "r");//abre arquivo para leitura, apenas

    if (file == NULL ) {
        printf("\nError opening file!\n");
        exit(1);
    }
    //Declaração de variáveis
    char profile[50];
    int user_count = 1;

    printf("======================================\nUSERS LIST\n======================================\n");
    printf("List of registered users:\n\n");
    while(fgets(profile, sizeof(profile),file)!=NULL)//Busca string com tamanho de profile[50]
    {

        char *username=strtok(profile," ");//Define que a string a ser definida para o ponteiro username irá até encontrar o primeiro " "
        if(username != NULL)
        {

            printf("%d. %s\n",user_count, username);
        }
        user_count++;//Contagem de usuários cadastrados
    }
    fclose(file);
    clear_buffer();
    press_to_continue();
    clear_terminal();
}

void edit_username()
{
    clear_buffer();
    clear_terminal();

    //Abertura de arquivo que carrega dados dos usuários (login e senha) e um arquivo temporário, para leitura e escrita, respectivamente
    FILE *file = fopen("usuarios.txt", "r");
    FILE *temp_file = fopen("usuariostemp.txt", "w");

    //Declaração de variáveis
    char username[50];
    char new_username[50];
    char confirm_username[50];
    char profile[100];
    int found = 0;

    //Atesta se o arquivo foi aberto corretamente
    if (file == NULL || temp_file == NULL) {
        printf("Error opening file!");
        exit(1);
    }
     printf("======================================\nEDIT USER\n======================================\n\n");
     printf("Enter username: ");
     scanf("%s", username);

    do{//Recebe novo nome de usuário
        printf("\nEnter new username: ");
        scanf("%s", new_username);
        printf("Confirm username: ");
        scanf("%s", confirm_username);
        if(strcmp(new_username, confirm_username) != 0)//Autenticação se novo nome de usuário é igual sua confirmação
        {
            printf("\nUsernames don't match. Try again!\n");
        }
     }while(strcmp(new_username, confirm_username) != 0);//EStrutura de loop, que se repete até serem iguais

    while (fgets(profile, sizeof(profile), file) != NULL) {//Busca por strings no arquivo até achar "null"
        char *search_username, *search_password;//Ponteiros que apontaram para dados encontrados
        search_username = strtok(profile, " ");//Busca string até " "
        search_password = strtok(NULL, "\n");//Busca string até "\n"

        if (search_username != NULL) {
            search_username[strcspn(search_username, "\n")] = 0;
        }

        if (strcmp(username, search_username) == 0) {//Condição found=1, define que o usuário digitado foi achado na lista
            found = 1;
            fprintf(temp_file, "%s %s\n", new_username, search_password);//Escreve usuário novo e senha antiga em um arquivo .txt temporário
        } else {
            fprintf(temp_file, "%s %s\n", search_username, search_password);//Escreve senha e usuário antigo em um arquivo .txt temporário
        }
    }
    //Fecha arquivo
    fclose(file);
    fclose(temp_file);

    if (found) {//Encontrou usuário digitado
        remove("usuarios.txt");//Apaga arquivo original de dados do usuário
        rename("usuariostemp.txt","usuarios.txt");//Renomeia arquivo temporário com nome do arquivo original
        printf("\n->Username updated successfully.\n");
    } else {
        remove("usuariostemp.txt");
        printf("\n->Username not found.\n");
    }
    //Limpa tela
    clear_buffer();
    press_to_continue();
    clear_terminal();
}


void edit_password() {

    clear_buffer();
    press_to_continue();
    clear_terminal();

    char username[50];
    char password[50];
    char new_password[50];
    char confirm_password[50];
    char profile[100];
    int found = 0;


    FILE *file = fopen("usuarios.txt", "r");
    FILE *temp_file = fopen("usuariostemp.txt", "w");

    if (file == NULL || temp_file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("======================================\nEDIT USER\n======================================\n\n");
    //Recebe credenciais
    printf("Enter username: ");
    scanf("%s",username);
    printf("Enter current password: ");
    scanf("%s", password);


    do{//Recebe senha nova
        printf("\nEnter new password: ");
        scanf("%s", new_password);
        printf("Confirm password: ");
        scanf("%s", confirm_password);
        if(strcmp(new_password, confirm_password) != 0) //Verificação de igualdade das senhas digitadas
        {
            printf("\n->Usernames don't match. Try again!\n");
        }
     }while(strcmp(new_password, confirm_password) != 0);//Estrutura de repetição até que ambas as senhas sejam iguais



    while (fgets(profile, sizeof(profile), file) != NULL) {//Procura por todos os dados de file, até que encontre NULL
        char *search_username, *search_password;//Declaração de ponteiros
        search_username = strtok(profile, " ");//Define a string como até o primeiro " ", procurando 'username'
        search_password = strtok(NULL, "\n");//Define a string como até o primeiro "\n", procurando 'password'

        if (strcmp(username, search_username) == 0 && strcmp(password, search_password) == 0) {//Faz comparação entre o usuário e senha achados e os digitados
            found = 1;
            fprintf(temp_file, "%s %s\n", username, new_password);//Redefine a senha encontrados com uma nova senha em um arquivo txt temporário
        } else {
            fprintf(temp_file, "%s %s\n", search_username, search_password);//Caso não encontre a senha digitada irá mantê-la, escrevendo a mesma senha em um arquivo txt
        }
    }
    //Fechamento de arquivo
     fclose(file);
     fclose(temp_file);

     if (found) {//Caso encontre senha e usuário respectivos para aqueles que foram digitados
           remove("usuarios.txt");//Deleta o arquivo original que guarda os dados dos usuários
           rename("usuariostemp.txt", "usuarios.txt");//Renomeia o arquivo temporário como o arquivo original
           printf("\n->Password updated successfully.\n");
     } else {//Caso não encontre dados fornecidos
           remove("usuariostemp.txt");//Deleta arquivo temporário
           printf("\n->Username or password incorrect.\n");
     }

    clear_buffer();
    press_to_continue();
    clear_terminal();
}


void delete_account()
    {
        clear_buffer(); //Limpeza de tela e transição
        press_to_continue();
        clear_terminal();

        FILE *file = fopen("usuarios.txt", "r"); //Comando que abre o arquivo de usuário para leitura e um arquivo temporário para escrita
        FILE *temp_file = fopen("usuariostemp.txt","w");

        //Declaração de variáveis usadas no bloco
        char username[50];
        char password[50];
        char profile[100];
        int found = 0;
        int option3;

        printf("=============================\nDELETE ACCOUNT\n=============================");
        printf("\n\nAre you sure you want to delete your account\n");
        printf("1. Yes\n2. No\n");
        printf("Choose an option: ");
        scanf("%d", &option3); //Recebe opção
        if(option3 == 1)
            {
                //Recebe usuário e senha cadastrados
                printf("\nEnter credentials:");
                printf("\nUsername - ");
                scanf("%49s",username);
                printf("Password - ");
                scanf("%49s", password);
                while (fgets(profile, sizeof(profile), file) != NULL) {//Procura por todos os dados de file, até que encontre NULL
                    char *search_username = strtok(profile," "); //Define a string como até o primeiro " ", procurando 'username'
                    char *search_password = strtok(NULL, "\n");//Define a string como até o primeiro "\n", procurando 'password'

                        if (strcmp(username, search_username) == 0 && strcmp(password, search_password) == 0) {//Faz comparação entre o usuário e senha achados e os digitados
                            found = 1; //Define found = 1 quando forem iguais
                            fprintf(temp_file,'\0' ,'\0' ,username, password);//Redefine o usuário e senha encontrados como nulo em um arquivo txt novo
                        } else {
                            fprintf(temp_file, "%s %s\n", search_username, search_password);//Caso não encontrar um respectivo, escreve usuário e senha novamente no arquivo temporario
                        }
                }
                //Fechamento de arquivo
                fclose(file);
                fclose(temp_file);
                if (found) {//Caso encontre senha e usuário respectivos para aqueles que foram digitados
                       remove("usuarios.txt");//Apaga o arquivo original
                       rename("usuariostemp.txt", "usuarios.txt");//Renomeia o arquivo temporário, com as mudanças feitas, como o arquivo original
                       printf("\n->User was successfuly deleted.\n");
                } else {
                       remove("usuariostemp.txt");//Caso não encontrar respectivos, irá apagar o arquivo temporário criado
                       printf("\n->Username or password incorrect.\n");
                 }
                    //Limpa tela
                    clear_buffer();
                    press_to_continue();
                    clear_terminal();
            }


    }
int edit_menu()//Função de menu para edição, inclui: edição de nome de usuário, deleção, edição de senha e listagem de todos os usuários cadastrados
{
    do{
        printf("======================================\nEDIT USERS\n======================================\n\n");
        printf("1. Change password\n");
        printf("2. Change username\n");
        printf("3. Delete account\n");
        printf("4. Registered profiles\n");
        printf("5. Home\n");
        printf("\nChoose an option: ");
        scanf("%d", &option);
            switch(option)
            {
              case 1:
                 edit_password();
                 break;
              case 2:
                 edit_username();
                 break;
              case 3:
                 delete_account();
                 break;
              case 4:
                 users_list();
                 break;
              case 5:
                 main();
              default:
                printf("Invalid option. Try again!");
                break;
            }}while(option != 5);
}

int main()
    {
        clear_terminal();
       do{menu();
        switch(option)
            {case 1:
                login();
                break;
             case 2:
                user_registration();
                return main();
             case 3:
                edit_menu();
                break;
             case 4:
                exit(1);
                break;
             default:
                printf("\n->Invalid option. Try again!\n");
                return main();

            }}while(option!=4);

    }
