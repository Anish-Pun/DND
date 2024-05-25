#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item
{
    char name[50]; // [50] is the maximum length of the name
    float weight;
    int quantity;
};
struct coin
{
    int cp;
    int sp;
    int ep;
    int gp;
    int pp;
};

struct inventory
{
    struct item items[100]; // [100] is the maximum number of items
    int num_items;
    struct coin money;
};

struct node
{
    struct item data;
    struct node *next;
};

void push(struct node** head_ref, struct item new_item)
{
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    new_node->data = new_item;
    new_node->next = *head_ref;
    *head_ref = new_node;
};

void pop(struct node** head_ref) 
{
    if (*head_ref == NULL)
    {
        printf("Inventory is empty.\n");
        return;
    }
    struct node *temp = *head_ref;
    *head_ref = (*head_ref)->next;
    free(temp);
}

void cycle(struct node* head)
{
    if( head == NULL)
    {
        printf("Inventory is empty\n");
        return;
    }
    struct node *current = head;
    do
    {
        printf("Item: %s\n", current->data.name);
        printf("Weight: %.2f\n", current->data.weight);
        printf("Quantity: %d\n", current->data.quantity);
        current = current->next;
    } while (current != head);
}

void usage()
{
    printf("Usage:              Inventory.exe equipment-files [number-of-items] [-w max-weight] [-m money] [-c camp-file]\n");
    printf("Options:\n");
    printf("Number of items     Optional per file to define the number in the inventory\n");
    printf("-w max-weight       Maximum weight before becoming encumbered\n");
    printf("-m money            List of coins and types (cp, sp, ep, gp, pp)\n");
    printf("-c camp-file        Optional camp file for all discovered items during play that stay in camp\n");
}

void parse_json(const char *)
{

}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        usage();
        return 1;
    }
    struct inventory inv;

    return 0;
}
