struct node
{
    int data;
    struct node *next;
};
void displayList(struct node* head);
void freeList(struct node* head);
struct node* creareNod(int data);