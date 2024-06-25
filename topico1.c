#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// =================================================================================================================
// Definições e variáveis globais
// =================================================================================================================
//Variável usada no tópico 2, 3 e 4 do trabalho
    int items;
    FILE *itens;
    FILE *usuarios;


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
        fflush(NULL);
        getchar();
    }

    void CriarArquivo (FILE *p)
    {
      p = fopen("itens.txt", "a+");
      if (p == NULL) {
        printf("Erro ao abrir arquivo");
      }
      fclose(p);

    }

    void CriarArquivo1 (FILE *p1)
    {
      p1 = fopen("usuarios.txt", "a+");
      if (p1 == NULL) {
        printf("Erro ao abrir arquivo");
      }
      fclose(p1);

    }
// =================================================================================================================
// Usuários
// =================================================================================================================

typedef struct _no1//Permite que, ao armazenar os dados de uma mesma entidade, isto possa ser feito com uma única variável com o intuito de melhorar o gerenciamento de informações
    {
        char username [50];
        char password [50];
        int quant;
        struct _no1 *next1; //Cada item tem um ponteiro apontando para o item seguinte
    }User;


//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
void insertUserAtTheEndOfTheList(User **listuser, char username[50], char password[50]) //insere nome e senha de um usuário no fim da lista em um arquivo
{
    User *newUser = (User *) malloc(sizeof(User));
    User *aux1;

    if (newUser)
    {
        strcpy(newUser->username, username);
        strcpy(newUser->password, password);

        newUser->next1 = NULL;

        if (*listuser == NULL)
            *listuser = newUser;
        else
        {
            aux1 = *listuser;
            while (aux1->next1)
            {
                aux1 = aux1->next1;
            }
            aux1->next1 = newUser;
        }
    }
    else
    {
        printf("**Error allocating memory!**\n");
    }
}


//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
void passFileToListUser(User **listauser, FILE *p1)
{
     char username[50];
     char password[50];

    p1 = fopen("usuarios.txt", "r");

    if (p1 != NULL)
    {
        while (fscanf(p1, "49[^;];%49[^;]\n", username, password) == 2)
        {
            insertUserAtTheEndOfTheList(listauser,username, password);
        }
        fclose(p1);
    }
    else
    {
        printf("Erro ao abrir arquivo");
        exit(0);
    }
}
//-----------------------------------------------------------------------------------------------------------------
//função responsável por passar o que está na lista encadeada diretamente pro file
void passListToFileUser(User *listauser, FILE *p1)
{
    User *auxiliar1 = listauser;
    p1 = fopen("usuarios.txt", "w+");

    if (p1 != NULL)
    {
        while (auxiliar1 != NULL)
        {
            fprintf(p1, "49[^;];%49[^;]\n", auxiliar1->username, auxiliar1->password);
            auxiliar1 = auxiliar1->next1;
        }
        fclose(p1);
    }
    else
    {
        printf("Erro ao abrir arquivo");
    }
}
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
void printUsers(User *user) //Função para printar a lista completa de usuários
{

    if(user == NULL) //Verifica se a lista está vazia
    {
        printf("\n-> Add an user first!\n");
        return;
    }
    printf("===========================================================================================\n\t\t\t\t\tREGISTERED USER\n===========================================================================================\n\n");
    while (user!=NULL)
    {
        printf("%s\n",user->username); //Estrutura que mostra nome de usuário
        user = user->next1; //Percorre a lista
    }

}
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
void printUser(char username[50], char password[50]) //Função para printar os dados individuais de cada usuário
{
    printf("\t-> Username: %s\n",username);
    printf("\t-> Password: %s\n", password);
}
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
void user_registration(User **listuser) //Função responsável pela exibição e funcionamento da aba de cadastramento do usuário
{
    clear_terminal();
    FILE* p1 = fopen("usuarios.txt", "w+");

    //Gravando as informações dos usuários
    char username[50];
    char password[50];

    clear_terminal();
    printf("===========================================================================================\n\t\t\t\t\tADD USER\n===========================================================================================\n\n");
    //Mostrando exemplos dos dados a ser cadastrados
    printf("Username: usuario\n");
    printf("Password: senha\n\n");
    //Cadastrando os dados
    printf("+ username: ");
    scanf("%[^\n]", username); //Recebe o cadastramento do usuário
    getchar();
    printf("+ password: ");
    scanf("%[^\n]", password); //Recebe o cadastramento da senha do usuário
    getchar();


    insertUserAtTheEndOfTheList(listuser, username, password); //Adicionar o item na lista
    printf("\n-> The user was successfully registered!\n");
    passFileToListUser(listuser, usuarios);

    clear_buffer();
    press_to_continue();
    clear_terminal();
}
//----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
void login(bool *controleLogin, User **listuser) //Função responsável pela exibição e funcionamento da aba de login
{
    clear_terminal();
    User *aux1;
    bool found = false;

    aux1 = *listuser;

    char username[50];
    char password[50];


        printf("===========================================================================================\n\t\t\t\t\tLOGIN\n===========================================================================================\n\n");
        //Obtêm senha e usuário para login
        printf("Username: ");
        scanf("%s", username); //Escaneia o código do item a ser procurado de acordo com a inserção do usuário
        printf("Password: ");
        scanf("%s", password); //Escaneia o código do item a ser procurado de acordo com a inserção do usuário
        printf("\n");
        while (aux1!=NULL)
        {   //Lê arquivo todo até chegar ao fim, buscando por duas strings específicas
            if(strcmp(aux1->username, username) == 0 && strcmp(aux1->password, password) == 0)

            {
                printf("\n-> Login successful\n");
                *controleLogin = true;
                clear_buffer();
                press_to_continue();
                clear_terminal();
                return;
            }
            aux1 = aux1->next1; //Caminha pela lista, se esse elemento não existir em algum momento chegará em null (que é conndição de parada do while)
        }

        printf("\n-> Login failed (incorrect username or password). Try again!\n\n");
        *controleLogin = false;
        clear_buffer();
        press_to_continue();
        clear_terminal();



}
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------

void edit_password(User **listuser) // Função responsável pela edição de uma senha de usuário
{
    char username[50];

    if (*listuser == NULL) //Verifica se a lista está vazia
    {
        printf("-> Add a user first!\n");
        return;
    }

    printf("===========================================================================================\n\t\t\t\t\tEDIT PASSWORD\n===========================================================================================\n\n");
    printf("Username: "); //Escaneia o código do item a ser editado de acordo com a inserção do usuário
    scanf("%s", username);

    User *aux1 = *listuser;
    bool found = false;

    while (aux1 != NULL) //Procura pelo código informado pelo usuário até que chegue ao final da lista
    {
        if (strcmp(aux1->username,username) == 0) //Identifica se o item apontado pelo ponteiro apresenta o mesmo código informado pelo usuário
        {
            found = true;

            printf("\n");
            printUser(aux1->username, aux1->password); //Exibindo os dados antigos do usuário
            printf("\n");

            printf("+ Enter the new password: ");
            getchar(); // Limpa o buffer do teclado
            scanf("%[^\n]", aux1->password);
            printf("\n-> Password edited successfully!\n");
            getchar();
            break;

        }
        aux1 = aux1->next1; //Se o item verificado não apresentar o mesmo código informado pelo usuário, o ponteiro vai para o prŕoximo item
        passListToFileUser(*listuser, usuarios);
    }

    if (found==false) //Verificação se existe um usuário com esse nome
    {
        printf("\n-> %s not found.\n", username);
        getchar();
        return;
    }
}

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------

void searchUser (User **listuser) //Função responsável pela busca de um usuário de acordo com seu nome de conta
{
    User *aux1;
    bool found = false;

    aux1 = *listuser;

    char username[50];

    if (*listuser == NULL) //Verifica se a lista está vazia
    {
        printf("-> Add an user first!\n");
        return;
    }

    printf("===========================================================================================\n\t\t\t\t\tSEARCH PROFILE\n===========================================================================================\n\n");
    printf("Username: ");
    scanf("%s", username); //Escaneia o código do item a ser procurado de acordo com a inserção do usuário
    printf("\n");

    while(aux1!=NULL) //Verifica se existe um item, isto é, se e lista é diferente de null e se o code é diferente do code inserido pelo usuário
    {
        if(strcmp(aux1->username, username) == 0)

        {
            found = true;
            printf("\tProfile data: \n");
            printUser(aux1->username, aux1->password); //Exibir dados do usuário
            getchar();
            break;
        }
        aux1 = aux1->next1; //Caminha pela lista, se esse elemento não existir em algum momento chegará em null (que é conndição de parada do while)
    }
    if (!found) //Verificação se existe um item com esse código
    {
        printf("-> %s not found.\n", username);
        getchar();
        return;
    }

}
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------

void removeUser(User **listuser) //Função responsável pela remoção de um item da lista
{
    User *removing1 = NULL;
    User *aux1;

    bool option;
    bool found = false;

    char username[50];

    if (*listuser == NULL) //Verifica se a lista está vazia
    {
        printf("-> Add an user first!\n");
        return;
    }

    printf("===========================================================================================\n\t\t\t\t\tREMOVE PROFILE\n===========================================================================================\n\n");
    printf("Username: ");
    scanf("%s", username); //Escaneia o código do item a ser removido de acordo com a inserção do usuário
    printf("\n");

    if(*listuser!=NULL)
    {
        //Remoção do primeiro nó da lista
        if((*listuser)->username==username) //Se o código do primeiro item for igual ao inserido pelo usuário, remove-se o primeiro item
        {
            found=true;

            removing1 = *listuser; //Conteúdo a ser removido
            *listuser = removing1->next1; //O primeiro nó da lista passa a ser o próximo depois de remover

            printf("Profile that will be removed: \n"); //Printa os dados do item que será removido
            printUser(removing1->username, removing1->password);

            printf("\nConfirm? (1 = Yes / 0 = No): "); //Pede a confirmação do usuário para remover o item
            scanf("%hhc", &option);
            if(option==true)
            {
                free(removing1); //Libera o espaço de memória
                printf("\n-> Profile removed successfully!\n");
                getchar();
            }
            else
            {
                printf("\n-> Operation cancelled!\n");
                //Retaura a lista se a operação for cancelada
                removing1->next1 = *listuser;
                *listuser = removing1;
                getchar();
            }

        }
        else //Se não for o primeiro nó a ser removido, temos que percorrer a lista
        {
            aux1 = *listuser;
            while (aux1->next1!=NULL && aux1->next1->username!=username)
            {
                aux1 = aux1->next1; //Percorre a lista
            }
            if((aux1->next1)!=NULL)
            {
                found = true;

                removing1 = aux1->next1; //O proximo item tem codigo igual ao requerido pelo usuário, cria um ponteiro para o nó que se quer remover
                aux1->next1 = removing1->next1; //Ponteiro que aponta para o proximo depois de aux->next, mantém a lista ligada

                printf("Profile that will be removed: ");
                printUser(removing1->username, removing1->password); //Printa os dados do item que será removido

                printf("\nConfirm? (1 = Yes / 0 = No): "); //Pede a confirmação do usuário para remover o item
                scanf("%hhd", &option);
                if(option==true)
                {
                    free(removing1); //Libera o espaço de memória
                    printf("\n-> Profile removed successfully!\n");
                    getchar();
                }
                else
                {
                    printf("\n-> Operation cancelled!");
                    //Restaura a lista se a operação for cancelada
                    aux1->next1 = removing1;
                    getchar();
                }
            }
        }
        passListToFileUser(*listuser,usuarios);
    }
    if (!found) //Verificação se existe um item com esse código
    {
        printf("-> %s not found.\n", username);
        getchar();
        return;
    }
}

// =================================================================================================================
// Itens
// =================================================================================================================
void quantity_items() //Função responsável por exibir e escanear a quantidade de itens a serem cadastrados
    {
        printf("===========================================================================================\n\t\t\t\t\tADD ITEMS\n===========================================================================================\n\n");
        printf("-------------------------------Enter 0 to return to the menu!-------------------------------\n\n");
        printf("How many items would you like to insert? "); //Pede ao usuário a quantidade de itens que serão cadastrados
        scanf("%d", &items);
        clear_terminal();
    }
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
void passFileToList (Item **lista, FILE *p)
{
    int a;
    char b[50];
    float y;
    bool d;


    p = fopen("itens.txt", "r");

    if (p != NULL)
    {
        while (fscanf(p, "%d;%49[^;];%f;%hhd", &a, b, &y, &d) == 4)
        {
            insertItemAtTheAndOfTheList(lista, a, b, y, d);
        }
        fclose(p);
    }
    else
    {
        printf("Erro ao abrir arquivo");
        exit(0);
    }
}
//-----------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------
//função responsável por passar o que está na lista encadeada diretamente pro file
void passListToFile (Item *lista, FILE *p)
{
    Item *auxiliar = lista;
    p = fopen("itens.txt", "w+");

    if (p != NULL)
    {
        while (auxiliar != NULL)
        {
            fprintf(p, "%d;%s;%.2f;%d\n", auxiliar->code, auxiliar->name, auxiliar->price, auxiliar->available);
            auxiliar = auxiliar->next;
        }
        fclose(p);
    }
    else
    {
        printf("Erro ao abrir arquivo");
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
    printf("===========================================================================================\n\t\t\t\t\tINSERTED ITEMS\n===========================================================================================\n\n");
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
        printf("===========================================================================================\n\t\t\t\t\tADD ITEMS %d/%d\n===========================================================================================\n\n",++c, items);
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
    passListToFile(*list, itens);
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
    printf("===========================================================================================\n\t\t\t\t\tEDIT ITEMS\n===========================================================================================\n\n");
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
        passListToFile(*list, itens);
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

    printf("===========================================================================================\n\t\t\t\t\tSEARCH ITEMS\n===========================================================================================\n\n");
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

    printf("===========================================================================================\n\t\t\t\t\tREMOVE ITEMS\n===========================================================================================\n\n");
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
        passListToFile(*list, itens);
    }
    if (!found) //Verificação se existe um item com esse código
    {
        printf("-> Item with code %d not found.\n", code);
        getchar();
        return;
    }
}
//----------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------


// =================================================================================================================
// MENUs
// =================================================================================================================

void userMenu(User **listuser)//Função de menu para edição, inclui: edição de nome de usuário, deleção, edição de senha e listagem de todos os usuários cadastrados
{
    int option;
    do
    {
        clear_terminal();
        printf("===========================================================================================\n\t\t\t\t\tEDIT USERS\n===========================================================================================\n\n");
        printf("1. Change password\n");
        printf("2. Delete account\n");
        printf("3. Registered profiles\n");
        printf("4. Search User\n");
        printf("0. Back\n");
        printf("\nChoose an option: ");
        scanf("%d", &option);
        clear_buffer();

        switch(option)
        {
          case 0:
            return;
            break;
          case 1:
            clear_terminal();
            edit_password(listuser);
            press_to_continue();
            // clear_terminal();
            break;
          case 2:
            clear_terminal();
            removeUser(listuser);
            press_to_continue();
            // clear_terminal();
            break;
          case 3:
            clear_terminal();
            printUsers(*listuser);
            press_to_continue();
            // clear_terminal();
            break;
          case 4:
            clear_terminal();
            searchUser(listuser);
            press_to_continue();
            // clear_terminal();
            break;
          default:
            printf("\n**Invalid option. Please try again!**\n");
            press_to_continue();
            break;
        }
    } while(option != 0);

}

//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
void itemsMenu(Item **list) //Função responsável pela exibição do menu de configurações dos items
{

    int option;

    do
    {
        clear_terminal();
        printf("===========================================================================================\n\t\t\t\t\tITEMS MENU\n===========================================================================================\n\n");
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
            // clear_terminal();
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
  } while (option!=0);
}
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------

void mainMenu() //Função responsável pela exibição do menu principal do programa
{
    bool controleLogin = false; //Booleano de controle para abrir a aba de menu só quando o usuário estiver logado
    int option;
    Item *list = NULL;
    passFileToList(&list, itens);
    User *listuser;
    passFileToListUser(&listuser,usuarios);
    do //Ocorre a repetição do menu até que opção para fechar o programa seja ativada
    {
        clear_terminal();
        printf("===========================================================================================\n\t\t\t\t\tMAIN MENU\n===========================================================================================\n\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Edit Profiles\n");
        printf("4. Items\n");
        printf("0. Exit\n");

        printf("\nChoose an option: ");
        scanf("%d",&option);
        clear_buffer();

        switch (option)
        {
          case 0: //Encerra o programa
            exit(1);
            break;
          case 1:
            login(&controleLogin, &listuser);
            clear_terminal();
            itemsMenu(&list);
            break;
          case 2:
            user_registration(&listuser);
            break;
          case 3:
            userMenu(&listuser);
            break;
          case 4:
            if(controleLogin == true)
                itemsMenu(&list);
            else
            {
                printf("\n-> You need to be logged in to access the items menu!");
                press_to_continue();
            }
          default:
            printf("\n**Invalid option. Please, try again!**\n");
            press_to_continue();
            clear_terminal();
            break;
        }
      }while (option!=0);
}

// =================================================================================================================
// MAIN
// =================================================================================================================
int main()
{
    CriarArquivo(itens);
    CriarArquivo1(usuarios);
    mainMenu();
}
