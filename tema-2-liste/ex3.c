//Realizați o listă dublu înlănțuită în care să căutați elementul de la mijloc și să îl ștergeți.
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
    struct node *prev;
};

struct node *head = NULL;
struct node *last = NULL;
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


struct node* deleteMid()
{
    int nr_elemente = 0;
    if(head == NULL)
        return NULL;
    struct node* curr = head;
    while(curr != NULL)
    {
        nr_elemente ++;
        curr = curr->next;
    }
    if(nr_elemente % 2)
    //pentru numar impar
    {
        curr = head;
        struct node* curr2 = last;
        while(curr != curr2)
        {
            curr = curr->next;
            curr2 = curr2->prev;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        free(curr);
    }
    else
    //pentru numar par
    {
        curr = head;
        struct node* curr2 = last;
        while(curr->next != curr2)
        {
            curr = curr->next;
            curr2 = curr2->prev;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        free(curr);
        curr2->prev->next = curr2->next;
        curr2->next->prev = curr2->prev;
        free(curr2);
    }
}

int main()
{
    struct node* current;
    //alocare manuala
    //element 1
    head = (struct node*) malloc(sizeof(struct node));
    head->data = 1;
    head->next = (struct node*) malloc(sizeof(struct node));
    head->prev = NULL;
    (head->next)->prev = head;
    current = head->next;
    //element 2
    current->data = 2;
    current->next = (struct node*) malloc(sizeof(struct node));
    (current->next)->prev = current;
    current = current->next;
    //element 3
    current->data = 3;
    current->next = (struct node*) malloc(sizeof(struct node));
    (current->next)->prev = current;
    current = current->next;
    //element 4
    current->data = 4;
    current->next = (struct node*) malloc(sizeof(struct node));
    (current->next)->prev = current;
    current = current->next;
    //element 5
    /*
    current->data = 5;
    current->next = (struct node*) malloc(sizeof(struct node));
    (current->next)->prev = current;
    current = current->next;
    */
    //element 6
    current->data = 6;
    current->next = NULL;
    last = current;

    displayList();
    deleteMid();
    displayList();

    freeList();
    return 0;
}