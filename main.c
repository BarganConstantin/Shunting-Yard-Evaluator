#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h> //pentru functia tolower()

typedef struct node
{
    char denumirea[50];
    char tara[50];
    char regizorul[50];
    char genul[50];
    int anul;
    struct node *left;
    struct node *right;
}
node;

typedef struct queue
{
    node *adr;
    struct queue *next;
} 
queue;

typedef struct stack
{
    node *adr;
    struct stack *next;
}
stack;

node *root = NULL;
queue *queue_first = NULL;
queue *queue_last = NULL;
stack *stack_top = NULL;

void eliberare(node *t);
int inaltime(node *t);
int nr_noduri(node *t);
void modificare(); //modificare a unei caracteristici dorite sau a tuturor odata
void insert_data_queue(node *v); //introducerea nodurilor din arbore in coada
void cautare_element(); //functia ce realizeaza cautarea dupa toate caracteristicile
void print_node(node *tmp); //afisarea datelor din nod
void show();//afisarea arborelui dupa 3 metode
void preorder(node *tmp);
void inorder(node *tmp);
void postorder(node *tmp);
void push(node *a); //introducere nod in stack
node *pop();//eliminare nod din stack
node *initiere_nod(); //returneaza un nod cu datele introduse
void create();//crearea arborelui
void meniu();
int citire_numar(); //citire numere naturale de la 0, in caz contrar intoarce -1
void iesire();

int main()
{
    int cmd;
    do
    {
        meniu();
        printf("\nIntroduceti comanda dorita: ");
        cmd = citire_numar();
        while (cmd < 0 || cmd > 7)
        {
            printf("\n*** Numarul introdus trebuie sa fie natural de la 0 pina la 7 !!! ***\n");
            printf("\nIntroduceti comanda dorita: ");
            cmd = citire_numar();
        }
        int a, nr_nod;
        switch (cmd)
        {
            case 1:
                if (root != NULL)
                {
                    printf("\nArborele a fost deja creat\n");
                    printf("Pentru a crea un arbore nou, trebuie sa o stergeti pe cel anterior\n");
                    break;
                }
                printf("\n\t\t*** Crearea nodurilor arborelui binar ***\n\n");
            	create();
                break;
            case 2:
                if (root == NULL)
                {
                    printf("Arborele inca nu a fost creat!\n");
                    break;
                }
            	show();
                break;
            case 3:
                if (root == NULL)
                    {
                        printf("Arborele inca nu a fost creat!\n");
                        break;
                    }
            	cautare_element();
                break;
            case 4:
                if (root == NULL)
                {
                    printf("Arborele inca nu a fost creat!\n");
                    break;
                }
            	modificare();
                break;
            case 5:
                if (root == NULL)
                {
                    printf("Arborele inca nu a fost creat!\n");
                    break;
                }
            	nr_nod = nr_noduri(root);
                printf("\nArborele contine %d noduri\n", nr_nod);
                break;
            case 6:
                if (root == NULL)
                {
                    printf("Arborele inca nu a fost creat!\n");
                    break;
                }
            	a = inaltime(root);
                printf("\nInaltimea arborelui este %d\n", a);
                break;
            case 7:
                if (root == NULL)
                {
                    printf("Arborele inca nu a fost creat, sau memoria pentru acesta a fost deja eliberata anterior!\n");
                    break;
                }
            	eliberare(root);
                break;
            case 0:
                iesire();
                break;
        }
    }
    while (cmd != 0);

    return 0;
}

void eliberare(node *t)
{
    if(!t) return;
	eliberare(t->left);
	eliberare(t->right);
	free(t);
}

int inaltime(node *t)
{
	int l,r;
	if(!t) return -1;
	l=inaltime(t->left);
	r=inaltime(t->right);
	if(l>r) return (l+1);
	else{
		return (r+1);
	}
}

int nr_noduri(node *t)
{
    int n;
	if(!t) return 0;
	n=1+nr_noduri(t->left)+nr_noduri(t->right);
	return n;  
}

void modificare()
{
    printf("\n\t\t*** Modificarea elementului in lista ***\n\n");

    insert_data_queue(root); //introducem arborele in coada
    //afisam toate denumirile de film cu pozitia acestora in coada
    queue *tmp = queue_first;
    int k = 1;
    while (tmp != NULL)
    {
        printf("%d. %s", k, tmp->adr->denumirea);
        k++;
        tmp = tmp->next;
    }

    printf("\nIntroduceti pozitia filmului caracteristicile caruia doriti sa modificati: ");
    int p = citire_numar(); //pozitia elementului ce trebuie modificat
    while (p <= -1 || p < 1 || p > k)
        {
            printf("\n#pozitia elementului trebuie sa fie un numar natural conform pozitiilor afisate anterior\n");
            printf("Introduceti pozitia filmului caracteristicile caruia doriti sa modificati: ");
            p = citire_numar();
        }
    printf("Ati ales filmul cu pozitia: %d\n", p);
    int q;
    printf("\n1 - modificare tuturor caracteristicilor\n");
    printf("2 - modificarea doar a unei caracteristici\n0 - inapoi la meniul principal\n");
    printf("\nComanda aleasa: ");
    q = citire_numar();
    while(q < 0 || q > 2)
    {
        printf("\nComanda aleasa trebuie sa 0, 1 sau 2\n");
        printf("Comanda aleasa: ");
        q = citire_numar();
    }
    if (q == 1)
    {
        tmp = queue_first;
        k = 1;
        while (k != p)
        {
            tmp = tmp->next;
            k++;
        }
        printf("Introduceti denumirea noua: ");
        fgets(tmp->adr->denumirea, 50, stdin);
        fgets(tmp->adr->denumirea, 50, stdin);

        printf("Introduceti tara: ");
        fgets(tmp->adr->tara, 50, stdin);

        printf("Introduceti regizorul: ");
        fgets(tmp->adr->regizorul, 50, stdin);

        printf("Introduceti genul filmului: ");
        fgets(tmp->adr->genul, 50, stdin);

        printf("Introduceti anul filmului: ");
        tmp->adr->anul = citire_numar();
            while (tmp->adr->anul <= -1)
            {
                printf("\n#Anul trebuie sa fie alcatuit din numere naturale\n");
                printf("Anul: ");
                tmp->adr->anul = citire_numar();
            }
    }
    else if (q == 2)
    {
        tmp = queue_first;
        k = 1;
        while (k != p)
        {
            tmp = tmp->next;
            k++;
        }
        printf("Ce caracteristica doriti sa-i modificati:\n1. Denumirea\n2. Tara\n3. Regizorul\n4. Genul filmului\n5. Anul\n->");
        int caracteristica = citire_numar();

        while (caracteristica < 1 || caracteristica > 5)
            {
                printf("\n#numarul caracteristicii poate fi de la 1 pina la 5\n");
                printf("Incercati din nou: ");
                caracteristica = citire_numar();
            }

        switch (caracteristica)
        {
            case 1:
                printf("\nIntroduceti denumirea noua: ");
                fgets(tmp->adr->denumirea, 50, stdin);
                fgets(tmp->adr->denumirea, 50, stdin);
                break;
            case 2:
                printf("\nIntroduceti tara: ");
                fgets(tmp->adr->tara, 50, stdin);
                fgets(tmp->adr->tara, 50, stdin);
                break;
            case 3:
                printf("\nIntroduceti regizorul: ");
                fgets(tmp->adr->regizorul, 50, stdin);
                fgets(tmp->adr->regizorul, 50, stdin);
                break;
            case 4:
                printf("\nIntroduceti genul filmului: ");
                fgets(tmp->adr->genul, 50, stdin);
                fgets(tmp->adr->genul, 50, stdin);
                break;
            case 5:
                printf("\nIntroduceti anul filmului: ");
                tmp->adr->anul = citire_numar();
                while (tmp->adr->anul <= -1)
                {
                    printf("\n#Anul trebuie sa fie alcatuit din numere naturale\n");
                    printf("Anul: ");
                    tmp->adr->anul = citire_numar();
                }
                break;
        }
    }
    //eliberarea cozii
    while (queue_first != NULL)
    {
        tmp = queue_first;
        queue_first = queue_first->next;
        free(tmp);
    }
    if (q == 0)
    {
        return;
    }
    printf("\t\t*** Modificarea sa efectuat cu succes! ***\n");
}

void insert_data_queue(node *v) //introducerea adreselor nodurilor in coada 
{   
    if (v == NULL) return;
    queue *tmp = (queue *)malloc(sizeof(queue));
    if (tmp == NULL)
    {
        printf("Eroare!\n");
        exit(0);
    }
    tmp->adr = v;
    if (queue_first == NULL)
    {
        queue_first = tmp;
        queue_last = tmp;
    }
    else
    {
        queue_last->next = tmp;
        queue_last = tmp;
    }
    insert_data_queue(v->left);
    insert_data_queue(v->right);

}

void cautare_element()
{
    printf("\n\t\t*** Cautarea elementului in lista ***\n\n");

    if (root == NULL)
    {
        printf("-> Datele inca nu au fost inscrise, iar memoria pentru acestea nu a fost alocata!\n");
        return;
    }

    insert_data_queue(root); //introducem arborele in coada
    
    printf("Dupa care caracteristica doriti sa cautati filmul:\n1. Denumirea\n2. Tara\n3. Regizorul\n4. Genul filmului\n5. Anul\n->");
    int caracteristica = citire_numar();

    while (caracteristica < 1 || caracteristica > 5)
        {
            printf("\n#numarul caracteristicii poate fi de la 1 pina la 5\n");
            printf("Incercati din nou: ");
            caracteristica = citire_numar();
        }

    char str[50];
    bool rezultat = false; //va arata daca sa gasit ceea ce se cauta
    queue *tmp = NULL;
    int k;
    switch (caracteristica)
    {
        case 1:
            printf("Introduceti denumirea: ");
            fgets(str, 50, stdin);
            fgets(str, 50, stdin);

            printf("\nRezultat:\n");

            for (int i = 0; str[i] != '\0'; i++)
            {
                str[i] = tolower(str[i]);
            }

            tmp = queue_first;

    
            while (tmp != NULL)
            {
                char temp[50];
                strcpy(temp, tmp->adr->denumirea);
                for (int j = 0; temp[j] != '\0'; j++)
                {
                    temp[j] = tolower(temp[j]);
                }

                if (strcmp(str, temp) == 0)
                {
                    printf("Denumirea: %s", tmp->adr->denumirea);
                    printf("Tara: %s", tmp->adr->tara);
                    printf("Regizorul: %s", tmp->adr->regizorul);
                    printf("Genul filmului: %s", tmp->adr->genul);
                    printf("Anul: %d\n", tmp->adr->anul);
                    printf("\n");
                    rezultat = true;
                }
                tmp = queue_first->next;
                free(queue_first);
                queue_first = tmp;
            }
            if (rezultat == false)
            {
                printf("-> Nu sa gasit nimic\n");
            }
            break;

        case 2:
            printf("Introduceti tara: ");
            fgets(str, 50, stdin);
            fgets(str, 50, stdin);

            printf("\nRezultat:\n");

            for (int i = 0; str[i] != '\0'; i++)
            {
                str[i] = tolower(str[i]);
            }

            tmp = queue_first;

    
            while (tmp != NULL)
            {
                char temp[50];
                strcpy(temp, tmp->adr->tara);
                for (int j = 0; temp[j] != '\0'; j++)
                {
                    temp[j] = tolower(temp[j]);
                }

                if (strcmp(str, temp) == 0)
                {
                    printf("Denumirea: %s", tmp->adr->denumirea);
                    printf("Tara: %s", tmp->adr->tara);
                    printf("Regizorul: %s", tmp->adr->regizorul);
                    printf("Genul filmului: %s", tmp->adr->genul);
                    printf("Anul: %d\n", tmp->adr->anul);
                    printf("\n");
                    rezultat = true;
                }
                tmp = queue_first->next;
                free(queue_first);
                queue_first = tmp;
            }
            if (rezultat == false)
            {
                printf("-> Nu sa gasit nimic\n");
            }
            break;

        case 3:
            printf("Introduceti regizorul: ");
            fgets(str, 50, stdin);
            fgets(str, 50, stdin);

            printf("\nRezultat:\n");

            for (int i = 0; str[i] != '\0'; i++)
            {
                str[i] = tolower(str[i]);
            }

            tmp = queue_first;

    
            while (tmp != NULL)
            {
                char temp[50];
                strcpy(temp, tmp->adr->regizorul);
                for (int j = 0; temp[j] != '\0'; j++)
                {
                    temp[j] = tolower(temp[j]);
                }

                if (strcmp(str, temp) == 0)
                {
                    printf("Denumirea: %s", tmp->adr->denumirea);
                    printf("Tara: %s", tmp->adr->tara);
                    printf("Regizorul: %s", tmp->adr->regizorul);
                    printf("Genul filmului: %s", tmp->adr->genul);
                    printf("Anul: %d\n", tmp->adr->anul);
                    printf("\n");
                    rezultat = true;
                }
                tmp = queue_first->next;
                free(queue_first);
                queue_first = tmp;
            }
            if (rezultat == false)
            {
                printf("-> Nu sa gasit nimic\n");
            }
            break;

        case 4:
            printf("Introduceti genul filmului: ");
            fgets(str, 50, stdin);
            fgets(str, 50, stdin);

            printf("\nRezultat:\n");

            for (int i = 0; str[i] != '\0'; i++)
            {
                str[i] = tolower(str[i]);
            }
            printf("\nRezultat:\n");
            tmp = queue_first;

    
            while (tmp != NULL)
            {
                char temp[50];
                strcpy(temp, tmp->adr->genul);
                for (int j = 0; temp[j] != '\0'; j++)
                {
                    temp[j] = tolower(temp[j]);
                }

                if (strcmp(str, temp) == 0)
                {
                    printf("Denumirea: %s", tmp->adr->denumirea);
                    printf("Tara: %s", tmp->adr->tara);
                    printf("Regizorul: %s", tmp->adr->regizorul);
                    printf("Genul filmului: %s", tmp->adr->genul);
                    printf("Anul: %d\n", tmp->adr->anul);
                    printf("\n");
                    rezultat = true;
                }
                tmp = queue_first->next;
                free(queue_first);
                queue_first = tmp;
            }
            if (rezultat == false)
            {
                printf("-> Nu sa gasit nimic\n");
            }
            break;

        case 5:
            printf("Introduceti anul filmului: ");
            int anul = citire_numar();
            while (anul <= -1)
            {
                printf("\n#Anul trebuie sa fie alcatuit din numere naturale\n");
                printf("Anul: ");
                anul = citire_numar();
            }
            printf("\nRezultat:\n");
            tmp = queue_first;
            while (tmp != NULL)
            {
                if (anul == tmp->adr->anul)
                {
                    printf("Denumirea: %s", tmp->adr->denumirea);
                    printf("Tara: %s", tmp->adr->tara);
                    printf("Regizorul: %s", tmp->adr->regizorul);
                    printf("Genul filmului: %s", tmp->adr->genul);
                    printf("Anul: %d\n", tmp->adr->anul);
                    printf("\n");
                    rezultat = true;
                }
                tmp = queue_first->next;
                free(queue_first);
                queue_first = tmp;
            }
            if (rezultat == false)
            {
                printf("-> Nu sa gasit nimic!\n");
            }
            break;
        }
    printf("\n\t\t*** Cautarea elementului s-a finalizat ***\n\n");
}

void preorder(node *tmp)
{
    if (tmp != NULL)
    {
        print_node(tmp);
		preorder(tmp->left);
		preorder(tmp->right);
    }   
}
    
void inorder(node *tmp)
{
    if (tmp != NULL)
    {
		inorder(tmp->left);
        print_node(tmp);
		inorder(tmp->right);
    }
}

void postorder(node *tmp)
{
    if (tmp != NULL)
    {
		postorder(tmp->left);
		postorder(tmp->right);
        print_node(tmp);
    }
}

void print_node(node *tmp)
{
    printf("\n");
    printf("Denumirea: %s", tmp->denumirea);
    printf("Tara: %s", tmp->tara);
    printf("Regizorul: %s", tmp->regizorul);
    printf("Genul filmului: %s", tmp->genul);
    printf("Anul: %d\n", tmp->anul);
}

void show()
{
    printf("1 - preordine\n2 - inordine\n3 - postordine\n0 - inapoi\n\n");
    printf("optiune: ");
    int answer = citire_numar();
    while(answer < 0 || answer > 3)
    {
        printf("\n\n#alegeti o optiune din cele propuse\n");
        answer = citire_numar();
    }
    switch(answer)
    {
        case 1:
            preorder(root);
            break;
        case 2:
            inorder(root);
            break;
        case 3:
            postorder(root);
            break;
        case 0:
            return;
            break;
    }
}

void create()
{   
    int answer;
    printf("Creati radacina? (0-nu/1-da)\n");
    answer = citire_numar();
    while(answer < 0 || answer > 1)
    {
        printf("\n\n#(0-nu/1-da)\n");
        answer = citire_numar();
    }
    if (answer == 0) return;
    node *tmp = (node *)malloc(sizeof(node));
    if (tmp == NULL)
    {
        printf("Eroare!\n");
        exit(0);
    }
    tmp = initiere_nod();
    push(tmp);
    root = tmp;
    while (stack_top != NULL)
    {
        tmp = pop();
        printf("Creati copilul drept al nodului %s? (0-nu/1-da)\n", tmp->denumirea);
        answer = citire_numar();
        while(answer < 0 || answer > 1)
        {
            printf("\n\n#(0-nu/1-da)\n");
            answer = citire_numar();
        }
        if (answer != 0)
        {
            node *d = (node *)malloc(sizeof(node));
            if (d == NULL)
            {
                printf("Eroare!\n");
                exit(0);
            }
            d = initiere_nod();
            tmp->right = d;
            push(d);
        }
        else 
        {
            tmp->right = NULL;
        }

        printf("Creati copilul sting al nodului %s? (0-nu/1-da)\n", tmp->denumirea);
        answer = citire_numar();
        while(answer < 0 || answer > 1)
        {
            printf("\n\n#(0-nu/1-da)\n");
            answer = citire_numar();
        }
        if (answer != 0)
        {
            node *s = (node *)malloc(sizeof(node));
            if (s == NULL)
            {
                printf("Eroare!\n");
                exit(0);
            }
            s = initiere_nod();
            tmp->left = s;
            push(s);
        }
        else 
        {
            tmp->left = NULL;
        }
    }
}

node *pop()
{
    node *v = stack_top->adr;
    stack *t = stack_top;
    stack_top = t->next;
    free(t);
    return v;
}

void push(node *a)
{
    stack *tmp = (stack *)malloc(sizeof(stack));
    if (tmp == NULL)
    {
        printf("Eroare!\n");
        exit(0);
    }
    tmp->adr = a;
    tmp->next = stack_top;
    stack_top = tmp;
}

node *initiere_nod()
{
    node *tmp = (node *)malloc(sizeof(node));
    if (tmp == NULL)
    {
        printf("Eroare!\n");
        exit(0);
    }
    printf("Denumirea: ");
    fgets(tmp->denumirea, 50, stdin);
    fgets(tmp->denumirea, 50, stdin);
    printf("Tara: ");
    fgets(tmp->tara, 50, stdin);
    printf("Regizorul: ");
    fgets(tmp->regizorul, 50, stdin);
    printf("Genul filmului: ");
    fgets(tmp->genul, 50, stdin);
    printf("Anul: ");
    tmp->anul = citire_numar();
    while (tmp->anul <= -1)
        {
            printf("\n#Anul trebuie sa fie alcatuit din numere naturale\n");
            printf("Anul: ");
            tmp->anul = citire_numar();
        }
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

void meniu()
{
    printf("\n\t\t\t*** Meniul principal ***\n");
    printf("\n1 - createa nodurilor arborelui binar oarecare in memoria dinamica si introducerea informatiei despre nodurile arborelui de la tastatura in mod interactiv\n");
    printf("2 - Afisarea informatiei despre nodurile arborelui la ecran\n");
    printf("3 - Cautarea nodului in arbore\n");
    printf("4 - Modificarea informatiei unui nod din arbore\n");
    printf("5 - Determinarea numarului de noduri.\n");
    printf("6 - Determinarea inaltimii arborelui.\n");
    printf("7 - Eliberarea memoriei alocate pentru lista.\n");
    printf("0 - Iesire din program\n");
}

int citire_numar()
{
    char a[10];
    scanf("%s", a);
    int number = -1;
    bool num = true;

    //verificam daca toate simbolurile sunt cifre
    for (int i = 0; a[i] != '\0'; i++)
    {
        if (a[i] >= '0' && a[i] <= '9')
        {
            continue;
        }

        num = false;
        break;
    }
    //transformam din caracter in cifre numarul introdus anterior
    if (num == true)
    {
        number = 0;

        int len = strlen(a);
        int temp = pow(10, len) / 10;
        for (int i = 0; a[i] != '\0'; i++)
        {
            number = number + (temp * (a[i] - 48));
            temp = temp / 10;
        }
    }
    return number;
}

void iesire()
{
    printf("->Iesire\n");
    exit(0);
}