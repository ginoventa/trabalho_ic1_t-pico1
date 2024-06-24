#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// =================================================================================================================
// Definições e variáveis globais
// =================================================================================================================

  //Variáel globais
    int items;
    int option;

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
    fflush(NULL);
    getchar();
}


// =================================================================================================================
// USUÁRIO
// =================================================================================================================

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
        }while(strcmp(password,loginPassword) != 0);

            if(strcmp(password, loginPassword) == 0)
                {
                    file = fopen("usuarios.txt", "a+");//Abre arquivo "users3.txt" e escreve usuário e senha ao final dele
                    if (file == NULL)
                        {
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
                    return;
                }
            }

            printf("\n-> Login failed (incorrect username or password). Try again!\n\n");
        } while(1);
      fclose(file);
      clear_terminal();
      clear_buffer();
      press_to_continue();
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
    //Fechamento de arquivo
    fclose(file);
    //Limpa tela
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
            printf("\n-> Usernames don't match. Try again!\n");
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
           printf("\n-> Password updated successfully.\n");
     } else {//Caso não encontre dados fornecidos
           remove("usuariostemp.txt");//Deleta arquivo temporário
           printf("\n-> Username or password incorrect.\n");
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
        printf("\nChoose an option: ");
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
                       printf("\n-> User was successfuly deleted.\n");
                     
                } else {
                       remove("usuariostemp.txt");//Caso não encontrar respectivos, irá apagar o arquivo temporário criado
                       printf("\n-> Username or password incorrect.\n");
                       
                 }
                    //Limpa tela
                    clear_buffer();
                    press_to_continue();
                    clear_terminal();
            }


    }
void search_user()
{
    clear_terminal();

    char username[50];
    char profile[100];
    int found = 0;

    FILE *file = fopen("usuarios.txt", "r");

    printf("======================================\nFIND USERS\n======================================\n\n");
    printf("Profile username: ");
    scanf("%s", username);

    while (fgets(profile, sizeof(profile), file) != NULL)
    {
        char *search_username = strtok(profile, " ");
        char *search_password = strtok(NULL, "\n");

        if (strcmp(username, search_username) == 0)
        {
            printf("\nProfile data:\n");
            printf("Username - %s\n", search_username);
            printf("Password - %s\n", search_password);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\n%s not found.\n", username);
    }

    // Limpa tela
    clear_buffer();
    press_to_continue();
    clear_terminal();
}


// =================================================================================================================
// Itens
// =================================================================================================================
void quantity_items() //Função responsável por exibir e escanear a quantidade de itens a serem cadastrados
{
    printf("======================================\nADD ITEMS\n======================================\n\n");
    printf("How many items would you like to insert? "); //Pede ao usuário a quantidade de itens que serão cadastrados
    scanf("%d", &items);
    clear_terminal();
}
//-----------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------
typedef struct _no//Permite que, ao armazenar os dados de uma mesma entidade, isto possa ser feito com uma única variável com o intuito de melhorar o gerenciamento de informações
{
    int code;
    char name [50];
    float price;
    bool available;

    struct _no *next; //Cada item tem um ponteiro apontando para o item seguinte
}Item;
//-----------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------
void insertItemAtTheAndOfTheList(Item **list, int code, char name[50], float price, bool available) //procedimento para inserir os itens no final de uma lista
{
    Item *newItem = (Item *) malloc(sizeof(Item)); //Alocação que retorna o ponteiro tipo Item
    Item *aux; //Ponteiro auxiliar para percorrer a lista

    if(newItem)//verificar se a memória foi alocada corretamente
    {
        newItem->code = code;
        strcpy(newItem->name, name);
        newItem->price = price;
        newItem->available = available;

        newItem->next = NULL;

        //eh o primeiro? Verifica se a lista está vazia
        if(*list == NULL) //Se a lista está vazia o conteudo da lista vai ser o novo item cadastrado
            *list = newItem;
        else //Se a lista não está vazia
        {
            aux = *list;
            while (aux->next) //Percorre a lista enquanto próximo for diferente de null
            {
              aux = aux->next;
            }
            aux->next = newItem; //Quando o próximo for null, aux->next vai receber o novo item
        }
    }
    else //Verifica se teve erra de alocação de memória
    {
        printf("**Error allocating memory!**\n");
    }
}
//-----------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------
void printItems(Item *item) //Função para printar a lista completa de itens
{
    if(item == NULL) //Verifica se a lista está vazia
    {
        printf("\n-> Add a new item first!\n");
        return;
    }
    printf("======================================\nINSERTED ITEMS\n======================================\n\n");
    while (item!=NULL)
    {
        printf("%d | %s | $%.2f | %s\n",item->code,item->name,item->price,item->available ? "available" : "NOT available"); //Estrutura que mostra: número, código, nome, preço e disponibilidade dos item.
        item = item->next; //Percorre a lista
    }

}
//-----------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------
void printItem(int code, char name[50], float price, bool available) //Função para printar os dados individuais de cada item
{
    printf("\t-> Item code: %d\n",code);
    printf("\t-> Item name: %s\n",name);
    printf("\t-> Item price: %.2f\n",price);
    printf("\t-> Item availability: %d\n",available);
}
//-----------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------
void itemsRegistration(Item **list) //Função responsável pela exibição e funcionamento da aba de cadastro de itens com 4 tipos diferentes de dados
{
    int c = 0;
    //Gravando as informações dos itens inseridos pelo usuário
    int code;
    char name[50];
    float price = 0;
    bool available;

    for(int q = 0;q<items;q++) //A estrutura for serve para realizar um looping da informação entre chaves a seguir
    {
        printf("\n====================================\nADD ITEMS %d/%d\n====================================\n\n",++c, items);
        printf("+ Enter the item code: "); //Entrada e saída de dados do tipo inteiro
        scanf("%d", &code); //Recebe o código do produto
        getchar(); //É usado entre o scanf e fgets para que o computador não entenda a linha de comando como entrada vazia

        printf("+ Enter the item name: ");
        scanf("%[^\n]", name);
        getchar();

        printf("+ Enter the item price: ");//Dados de entrada e saída do tipo decimal
        scanf("%f", &price);
        getchar();

        printf("+ Is the item available? (1=yes/0=no): "); //Dados do tipo booleano aceita apenas dois valores falso=0 verdadeiro!=0
        scanf("%hhd", &available);

        insertItemAtTheAndOfTheList(list, code, name, price, available); //Adicionar o item na lista
        printf("\n");
        printItem(code,name,price,available); //Printar os dados do item cadastrado

        clear_buffer();
        press_to_continue();
        clear_terminal();
    }
}
//-----------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------
void editItems(Item **list) // Função responsável pela edição de uma item de acordo com o código informado pelo usuário
{
    int option;

    if (*list == NULL) //Verifica se a lista está vazia
    {
        printf("-> Add a new item first!\n");
        return;
    }

    int code;
    printf("======================================\nEDIT ITEMS\n======================================\n\n");
    printf("Item code: "); //Escaneia o código do item a ser editado de acordo com a inserção do usuário
    scanf("%d", &code);

    Item *aux = *list;
    bool found = false;

    while (aux != NULL) //Procura pelo código informado pelo usuário até que chegue ao final da lista
    {
        if (aux->code == code) //Identifica se o item apontado pelo ponteiro apresenta o mesmo código informado pelo usuário
        {
            found = true;

            printf("\n");
            printItem(aux->code, aux->name, aux->price, aux->available); //Exibindo os dados antigos dos itens
            printf("\n");

            printf("(1) Name\t(2) Price\t(3) Availability\t(4) All Information\t(0) Back\n\nChoose an option: ");
            scanf("%d", &option);
            printf("\n");
            // Editando os dados do item encontrado
            switch (option)
            {
              case 0:
                return;
                break;

              case 1: //Editar somente o nome do item
                printf("+ Enter the new item name: ");
                getchar(); // Limpa o buffer do teclado
                scanf("%[^\n]", aux->name);
                printf("\n-> Item edited successfully!\n");
                getchar();
                break;

              case 2: //Editar somente o valor do item
                printf("+ Enter the new item price: ");
                scanf("%f", &(aux->price));
                printf("\n-> Item edited successfully!\n");
                getchar();
                break;

              case 3: //Editar somente a disponibilidade do item
                printf("+ Is the item available? (1=yes/0=no): ");
                scanf("%hhd", &(aux->available));
                printf("\n-> Item edited successfully!\n");
                getchar();
                break;

              case 4: //Editar todas as informações do item, exeto o código
                printf("+ Enter the new item name: ");
                getchar(); // Limpa o buffer do teclado
                scanf("%[^\n]", aux->name);

                printf("+ Enter the new item price: ");
                scanf("%f", &(aux->price));

                printf("+ Is the item available? (1=yes/0=no): ");
                scanf("%hhd", &(aux->available));

                printf("\n-> Item edited successfully!\n");
                getchar();
                break;

              default:
                printf("**Invalid option**");
                break;
            }

        }
        aux = aux->next; //Se o item verificado não apresentar o mesmo código informado pelo usuário, o ponteiro vai para o prŕoximo item
    }

    if (found==false) //Verificação se existe um item com esse código
    {
        printf("\n-> Item with code %d not found.\n", code);
        getchar();
        return;
    }
}
//----------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------
void searchItem (Item **list) //Função responsável pela busca de um item de acordo com código do item
{
    Item *aux;
    bool found = false;

    aux = *list;

    int code;

    if (*list == NULL) //Verifica se a lista está vazia
    {
        printf("-> Add a new item first!\n");
        return;
    }

    printf("======================================\nSEARCH ITEMS\n======================================\n\n");
    printf("Item code: ");
    scanf("%d", &code); //Escaneia o código do item a ser procurado de acordo com a inserção do usuário
    printf("\n");

    while(aux!=NULL) //Verifica se existe um item, isto é, se e lista é diferente de null e se o code é diferente do code inserido pelo usuário
    {
        if(aux->code == code)
        {
            found = true;
            printf("\tItem data: \n");
            printItem(aux->code, aux->name, aux->price, aux->available); //Exibir dados do item
            getchar();
            break;
        }
        aux = aux->next; //Caminha pela lista, se esse elemento não existir em algum momento chegará em null (que é conndição de parada do while)
    }
    if (!found) //Verificação se existe um item com esse código
    {
        printf("-> Item with code %d not found.\n", code);
        getchar();
        return;
    }

}
//----------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------
void removeItem(Item **list) //Função responsável pela remoção de um item da lista
{
    Item *removing = NULL;
    Item *aux;

    bool option;
    bool found = false;

    int code;

    if (*list == NULL) //Verifica se a lista está vazia
    {
        printf("-> Add a new item first!\n");
        return;
    }

    printf("======================================\nREMOVE ITEMS\n======================================\n\n");
    printf("Item code: ");
    scanf("%d", &code); //Escaneia o código do item a ser removido de acordo com a inserção do usuário
    printf("\n");

    if(*list!=NULL)
    {
        //Remoção do primeiro nó da lista
        if((*list)->code==code) //Se o código do primeiro item for igual ao inserido pelo usuário, remove-se o primeiro item
        {
            found=true;

            removing = *list; //Conteúdo a ser removido
            *list = removing->next; //O primeiro nó da lista passa a ser o próximo depois de remover

            printf("Item that will be removed: \n"); //Printa os dados do item que será removido
            printItem(removing->code, removing->name, removing->price, removing->available);

            printf("\nConfirm? (1 = Yes / 0 = No): "); //Pede a confirmação do usuário para remover o item
            scanf("%hhd", &option);
            if(option==true)
            {
                free(removing); //Libera o espaço de memória
                printf("\n-> Item removed successfully!\n");
                getchar();
            }
            else
            {
                printf("\n-> Operation cancelled!\n");
                //Retaura a lista se a operação for cancelada
                removing->next = *list;
                *list = removing;
                getchar();
            }

        }
        else //Se não for o primeiro nó a ser removido, temos que percorrer a lista
        {
            aux = *list;
            while (aux->next!=NULL && aux->next->code!=code)
            {
                aux = aux->next; //Percorre a lista
            }
            if((aux->next)!=NULL)
            {
                found = true;

                removing = aux->next; //O proximo item tem codigo igual ao requerido pelo usuário, cria um ponteiro para o nó que se quer remover
                aux->next = removing->next; //Ponteiro que aponta para o proximo depois de aux->next, mantém a lista ligada

                printf("Item that will be removed: ");
                printItem(removing->code, removing->name, removing->price, removing->available); //Printa os dados do item que será removido

                printf("\nConfirm? (1 = Yes / 0 = No): "); //Pede a confirmação do usuário para remover o item
                scanf("%hhd", &option);
                if(option==true)
                {
                    free(removing); //Libera o espaço de memória
                    printf("\n-> Item removed successfully!\n");
                    getchar();
                }
                else
                {
                    printf("\n-> Operation cancelled!");
                    //Restaura a lista se a operação for cancelada
                    aux->next = removing;
                    getchar();
                }
            }
        }
    }
    if (!found) //Verificação se existe um item com esse código
    {
        printf("-> Item with code %d not found.\n", code);
        getchar();
        return;
    }
}
//----------------------------------------------------------------------------------------------------------------


// =================================================================================================================
// MENU
// =================================================================================================================
void itemsMenu(Item **list) //Função responsável pela exibição do menu de configurações dos items
{

    int option;

    do
    {
        clear_terminal();
        printf("===========================================================================================\n\t\t\t\t\tITEMS MENU\n===========================================================================================\n");
        printf("1. Add items\n");
        printf("2. Edit items\n");
        printf("3. Search items\n");
        printf("4. List items\n");
        printf("5. Delete items\n");
        printf("0. Back");
        printf("\n\nChoose an option: ");
        scanf("%d",&option);
        clear_buffer();

        switch (option)
        {
          case 0: //Caso para retornar para o menu principal
            return;
            break;
          case 1: //Caso para adicionar um novo item
            clear_terminal();
            quantity_items();
            itemsRegistration(list);
            break;
          case 2: //Caso para editar um item
            clear_terminal();
            editItems(list);
            press_to_continue();
            //clear_terminal();
            break;
          case 3: //Caso para pesquisar um item
            clear_terminal();
            searchItem(list);
            press_to_continue();
            break;
          case 4: //Caso para imprimir a lista de itens
            clear_terminal();
            printItems(*list);
            press_to_continue();
            break;
          case 5: //Caso para deletar um item
            clear_terminal();
            removeItem(list);
            press_to_continue();
            break;
          default:
            printf("\n**Invalid option. Please try again!**\n");
            press_to_continue();
            break;
        }
  }while (option!=0);
}
//----------------------------------------------------------------------------------------------------------------

void edit_menu()//Função de menu para edição, inclui: edição de nome de usuário, deleção, edição de senha e listagem de todos os usuários cadastrados
{
    do{
        printf("======================================\nEDIT USERS\n======================================\n\n");
        printf("1. Change password\n");
        printf("2. Change username\n");
        printf("3. Delete account\n");
        printf("4. Registered profiles\n");
        printf("5. Search profiles\n");
        printf("0. Home\n");
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
                 search_user();
                 break;
              case 0:
                  return;
                  break;
              default:
                printf("Invalid option. Try again!");
                break;
            }}while(option != 0);
}

//----------------------------------------------------------------------------------------------------------------
int mainMenu() //Função responsável pela exibição do menu principal do programa
{
    int option;
    Item *list = NULL;
    do //Ocorre a repetição do menu até que opção para fechar o programa seja ativada
    {
        clear_terminal();
        printf("===========================================================================================\n\t\t\t\t\tMAIN MENU\n===========================================================================================\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Edit Profiles\n");
        printf("4. Items\n");
        printf("0. Exit\n");

        printf("\nChoose an option: ");
        scanf("%d",&option);
        clear_buffer();
        clear_terminal();

        switch (option)
        {
          case 0: //Encerra o programa
            exit(1);
            break;
          case 1:
            login();
            break;
          case 2:
            user_registration();
            return mainMenu();
            break;
          case 3:
            edit_menu();
            break;
          case 4: //Acessa o menu de configurações de itens
            //if() -> Fazer a verificação se o usuário está logado para poder configurar itens
            itemsMenu(&list);
            break;
          default:
            printf("\n**Invalid option. Please, try again!**\n");
            press_to_continue();
            clear_terminal();
            break;
        }
    }while (option!=0);
}


//----------------------------------------------------------------------------------------------------------------

// =================================================================================================================
// MAIN
// =================================================================================================================
int main()
{
    mainMenu();
}
