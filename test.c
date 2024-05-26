#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structuren voor items, munten, inventory en nodes
struct item
{
    char name[50];
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
    struct item items[100];
    int num_items;
    struct coin money;
};

struct node
{
    struct item data;
    struct node *next;
};

// Functie om een nieuw item toe te voegen aan de inventory
void add_item(struct inventory *inv, struct item *new_item) {
    if (inv->num_items < 100) {
        // Allocate memory for the new item
        struct item *item_ptr = &(inv->items[inv->num_items]);
        // Copy the contents of new_item to the allocated memory
        strcpy(item_ptr->name, new_item->name);
        item_ptr->weight = new_item->weight;
        item_ptr->quantity = new_item->quantity;
        // Increment the number of items in the inventory
        inv->num_items++;
    } else {
        printf("Inventory is full.\n");
    }
}
// Functie om de totale gewicht van de inventory te berekenen
float calculate_total_weight(struct inventory *inv) {
    float total_weight = 0;
    for (int i = 0; i < inv->num_items; i++) {
        total_weight += inv->items[i].weight * inv->items[i].quantity;
    }
    return total_weight;
}

// Functie om de inventory en totaal gewicht weer te geven
void print_inventory(struct inventory *inv, float max_weight) {
    printf("Inventory:\n");
    for (int i = 0; i < inv->num_items; i++) {
        printf("  Item: %s, Weight: %.2f, Quantity: %d\n", inv->items[i].name, inv->items[i].weight, inv->items[i].quantity);
    }
    float total_weight = calculate_total_weight(inv);
    printf("Total weight: %.2f (Max: %.2f)\n", total_weight, max_weight);
    if (total_weight > max_weight) {
        printf("You are encumbered!\n");
    }
}

// Functie om de inventory rond te gaan
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

void pop(struct node** head_ref) 
{
    if (*head_ref == NULL)
    {
        printf("Inventory is empty.\n");
        return;
    }
    struct node *temp = *head_ref;
    if (*head_ref == (*head_ref)->next) {
        *head_ref = NULL;
    } else {
        struct node *prev = *head_ref;
        while (prev->next != *head_ref) {
            prev = prev->next;
        }
        prev->next = (*head_ref)->next;
        *head_ref = (*head_ref)->next;
    }
    free(temp);
}

// Functie om een nieuw item aan de linked list toe te voegen
void push(struct node** head_ref, struct item new_item)
{
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    new_node->data = new_item;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        new_node->next = new_node;
    } else {
        struct node *temp = *head_ref;
        while (temp->next != *head_ref) {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = *head_ref;
    }
}

// Function to load equipment from a JSON file
void load_equipment(const char *filename, struct inventory *inv) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file: %s\n", filename);
        exit(1);
    }

    // Read JSON content from file
    char buffer[1024];
    fread(buffer, sizeof(buffer), 1, file);
    fclose(file);

    // Parse JSON manually
    char *ptr = strstr(buffer, "\"name\":");
    if (!ptr) {
        printf("Error: Invalid JSON format in file: %s\n", filename);
        exit(1);
    }
    sscanf(ptr, "\"name\":\"%[^\"]\"", inv->items[inv->num_items].name);

    ptr = strstr(buffer, "\"weight\":");
    if (!ptr) {
        printf("Error: Invalid JSON format in file: %s\n", filename);
        exit(1);
    }
    sscanf(ptr, "\"weight\":%f", &inv->items[inv->num_items].weight);

    ptr = strstr(buffer, "\"quantity\":");
    if (!ptr) {
        printf("Error: Invalid JSON format in file: %s\n", filename);
        exit(1);
    }
    sscanf(ptr, "\"quantity\":%d", &inv->items[inv->num_items].quantity);

    inv->num_items++;
}

void parse(int argc, char *argv[], float *max_weight, struct coin *money, char **camp_file, int *num_items, struct inventory *inv) {
    int arg_index = 1;
    while (arg_index < argc) {
        if (strcmp(argv[arg_index], "-w") == 0) {
            if (arg_index + 1 < argc) {
                *max_weight = atof(argv[arg_index + 1]);
                arg_index += 2;
            } else {
                printf("Error: Missing argument for -w option.\n");
                exit(1);
            }
        } else if (strcmp(argv[arg_index], "-m") == 0) {
            if (arg_index + 1 < argc) {
                sscanf(argv[arg_index + 1], "%dgp %dsp %dep %dgp %dpp", &money->gp, &money->sp, &money->ep, &money->gp, &money->pp);
                arg_index += 2;
            } else {
                printf("Error: Missing argument for -m option.\n");
                exit(1);
            }
        } else if (strcmp(argv[arg_index], "-c") == 0) {
            if (arg_index + 1 < argc) {
                *camp_file = argv[arg_index + 1];
                arg_index += 2;
            } else {
                printf("Error: Missing argument for -c option.\n");
                exit(1);
            }
        } else if (isdigit(argv[arg_index][0])) {
            *num_items = atoi(argv[arg_index]);
            if (*num_items == 0) {
                printf("Error: Invalid number of items.\n");
                exit(1);
            } else {
                arg_index++;
            }
        } else {
            if (*num_items == 0) {
                printf("Error: Number of items not specified.\n");
                exit(1);
            }
            load_equipment(argv[arg_index], inv);
            (*num_items)--;
            arg_index++;
        }
    }

    if (*num_items != 0) {
        printf("Error: Number of items specified but not provided.\n");
        exit(1);
    }
}


// Hoofdprogramma
int main(int argc, char *argv[])
{
    float max_weight = 0.0;
    struct coin money = {0, 0, 0, 0, 0};
    char *camp_file = NULL;
    int num_items = 0;

    // Aanmaken van de inventory en linked list
    struct inventory inv;
    inv.num_items = 0;
    struct node *head = NULL;
    // Argumenten parsen en equipment bestanden laden
    parse(argc, argv, &max_weight, &money, &camp_file, &num_items, &inv);

    // Menu voor interactie met de inventory
    int choice;
    do {
        printf("\nInventory Menu:\n");
        printf("1. View inventory\n");
        printf("2. View details of an item\n");
        printf("3. Move item to camp\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                print_inventory(&inv, max_weight);
                break;
            case 2:
                if (inv.num_items == 0) {
                    printf("Inventory is empty.\n");
                } else {
                    printf("Enter the index of the item you want to view (1-%d): ", inv.num_items);
                    int index;
                    scanf("%d", &index);
                    if (index < 1 || index > inv.num_items) {
                        printf("Invalid index.\n");
                    } else {
                        printf("Item: %s\n", inv.items[index - 1].name);
                        printf("Weight: %.2f\n", inv.items[index - 1].weight);
                        printf("Quantity: %d\n", inv.items[index - 1].quantity);
                    }
                }
                break;
            case 3:
                if (inv.num_items == 0) {
                    printf("Inventory is empty.\n");
                } else {
                    printf("Enter the index of the item you want to move to camp (1-%d): ", inv.num_items);
                    int index;
                    scanf("%d", &index);
                    if (index < 1 || index > inv.num_items) {
                        printf("Invalid index.\n");
                    } else {
                        // Voeg het item toe aan het kamp
                        push(&head, inv.items[index - 1]);
                        // Verwijder het item uit de inventory
                        for (int i = index - 1; i < inv.num_items - 1; i++) {
                            inv.items[i] = inv.items[i + 1];
                        }
                        inv.num_items--;
                        printf("Item moved to camp.\n");
                    }
                }
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 4);

    // Geheugen vrijmaken na gebruik
    while (head != NULL) {
        pop(&head);
    }

    return 0;
}