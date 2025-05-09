//Realizați un algoritm care să verifice că o listă simplu înlănțuită este palindrom.
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node* head = NULL;

void displayNumber()
{
    struct node *p = head;
    while(p != NULL)
    {
        printf("%d",p->data);
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

struct node* ePalindrom()
{
    if(head == NULL)
    {
        printf("Lista nu exista.");
        return NULL;
    }
    printf("\nNumarul ");
    displayNumber();
    struct node* curr = head;
    int nr = 0;
    while(curr != NULL)
    {
        nr = nr*10 + curr->data;
        curr = curr->next;
    }
    curr = head;
    while(curr != NULL)
    {
        if(curr->data != nr % 10)
        {
            printf(" nu este palindrom.");
            return NULL;
        }
        nr /= 10;
        curr = curr->next;
    }
    printf(" este palindrom.");
    return NULL;
}

int main()
{
    struct node* current;
    //alocare manuala
    //element 1
    head = (struct node*) malloc(sizeof(struct node));
    head->data = 3;
    head->next = (struct node*) malloc(sizeof(struct node));
    current = head->next;
    //element 2
    current->data = 1;
    current->next = (struct node*) malloc(sizeof(struct node));
    current = current->next;
    //element 3
    current->data = 2;
    current->next = (struct node*) malloc(sizeof(struct node));
    current = current->next;
    //element 4
    current->data = 2;
    current->next = (struct node*) malloc(sizeof(struct node));
    current = current->next;
    //element 5
    current->data = 1;
    current->next = (struct node*) malloc(sizeof(struct node));
    current = current->next;
    //element 6
    current->data = 2;
    current->next = NULL;

    ePalindrom();

    freeList();
    return 0;
}