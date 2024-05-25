#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"

// Define your data structures here
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
void add_item(struct inventory *inv, struct item new_item);
{
    if (inv->num_items < 100)
    {
        inv->items[inv->num_items++] = new_item;
    }
    else
    {
        printf("Inventory is full\n");
    } 
}

void print_item(struct item i)
{
    printf("Item: %s\n", i.name);
    printf("Weight: %.2f\n", i.weight);
    printf("Quantity: %d\n", i.quantity);

    printf("inventory: %s\n");

}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        usage();
        return 1;
    }
/*
    struct inventory player_inventory;
    player_inventory.num_items = 0;
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-w") == 0){
            player_inventory.max_weight = atof(argv[i+1]);
        }
        else if(strcmp(argv[i], "-m") == 0){
            player_inventory.money.cp = atoi(argv[i+1]);
            player_inventory.money.sp = atoi(argv[i+2]);
            player_inventory.money.ep = atoi(argv[i+3]);
            player_inventory.money.gp = atoi(argv[i+4]);
            player_inventory.money.pp = atoi(argv[i+5]);
        }
        else if(strcmp(argv[i], "-c") == 0){
            player_inventory.camp_file = argv[i+1];
        }
        else{
            player_inventory.num_items = atoi(argv[i]);
        }
    }
*/
    return 0;
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