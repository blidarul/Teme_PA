//Realizați un program care să șteargă duplicatele dintr-o listă simplu înlănțuită nesortată.
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

void displayList()
{
    struct node *p = head;
    printf("\n");
    while(p != NULL)
    {
        printf("%d  ",p->data);
        p = p->next;
    }
}

void freeList()
{
    struct node *p = head;
    struct node *prev = NULL;
    while(p->next != NULL)
    {
        prev = p;
        p = p->next;
        if(prev != NULL)
            free(prev);
    }
}

struct node* stergere(int data)
{
    struct node *curr = head;
    struct node *prev = NULL;
    if(head == NULL)
        return NULL;
    while(curr->data != data)
    {
        if(curr->next == NULL)
            return NULL;
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }

    if(curr == head)
    {
        head = head->next;
    }
    else
    {
        struct node* aux = curr;
        prev->next = curr->next;
        free(curr);
    }
}

int nrAparitii(int nr)
{
    struct node *p = head;
    int n = 0;
    while(p != NULL)
    {
        if(p->data == nr)
            n++;
        p = p->next;
    }
    return n;
}

int main()
{
    //alocare manuala
    //element 1
    head = (struct node*) malloc(sizeof(struct node));
    head->data = 2;
    head->next = (struct node*) malloc(sizeof(struct node));
    current = head->next;
    //element 2
    current->data = 4;
    current->next = (struct node*) malloc(sizeof(struct node));
    current = current->next;
    //element 3
    current->data = 5;
    current->next = (struct node*) malloc(sizeof(struct node));
    current = current->next;
    //element 4
    current->data = 2;
    current->next = (struct node*) malloc(sizeof(struct node));
    current = current->next;
    //element 5
    current->data = 7;
    current->next = (struct node*) malloc(sizeof(struct node));
    current = current->next;
    //element 6
    current->data = 4;
    current->next = NULL;

    current = head;
    while(current != NULL)
    {   
        int nr = current->data;
        if(nrAparitii(nr) > 1)
        {
            struct node* aux = stergere(nr);
            if(aux != NULL)
                aux;
        }
        current = current->next;
    }

    displayList();
    freeList();
    return 0;
} 