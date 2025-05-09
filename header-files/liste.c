#include <stdlib.h>
#include <stdio.h>

struct node
{
    int data;
    struct node *next;
};

void displayList(struct node* head)
{
    struct node *p = head;
    printf("\n");
    while(p != NULL)
    {
        printf("%d  ",p->data);
        p = p->next;
    }
}

void freeList(struct node* head)
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

struct node* creareNod(int data)
{
    struct node* nod =(struct node*) malloc(sizeof(struct node));
    nod->data = data;
    nod->next = NULL;
    return nod;
}
