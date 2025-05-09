#include <stdio.h>
#include <stdlib.h>

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

int main()
{
    struct node* head1 = creareNod(1);
    head1->next = creareNod(2);
    head1->next->next = creareNod(3);
    head1->next->next->next = creareNod(4);
    printf("Lista 1:");
    displayList(head1);

    struct node* head2 = creareNod(10);
    head2->next = creareNod(11);
    head2->next->next = creareNod(12);
    head2->next->next->next = creareNod(13);
    printf("\nLista 2:");
    displayList(head2);

    struct node* current = head1;
    struct node* prev = NULL;
    while(current != NULL)
    {
        prev = current;
        current = current->next;
    }
    prev->next = head2;

    printf("\nLista combinata:");
    displayList(head1);
    
    freeList(head1);
    return 0;
}