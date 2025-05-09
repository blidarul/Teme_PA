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

struct node* inversareRecursiva(struct node* cap)
{
    if(cap == NULL || cap->next == NULL)
        return cap;
    struct node* aux = inversareRecursiva(cap->next);
    cap->next->next = cap;
    cap->next = NULL;

    head = aux;
}

int main()
{
    //alocare manuala
    //element 1
    head = (struct node*) malloc(sizeof(struct node));
    head->data = 1;
    head->next = (struct node*) malloc(sizeof(struct node));
    current = head->next;
    //element 2
    current->data = 2;
    current->next = (struct node*) malloc(sizeof(struct node));
    current = current->next;
    //element 3
    current->data = 3;
    current->next = (struct node*) malloc(sizeof(struct node));
    current = current->next;
    //element 4
    current->data = 4;
    current->next = (struct node*) malloc(sizeof(struct node));
    current = current->next;
    //element 5
    current->data = 5;
    current->next = (struct node*) malloc(sizeof(struct node));
    current = current->next;
    //element 6
    current->data = 6;
    current->next = NULL;
    
    displayList();
    inversareRecursiva(head);
    displayList();

    freeList();
    return 0;
}