#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "utlist.h"
#include <time.h>

struct node {
    int data;
    struct node* next;
};
typedef struct node Node;

static Node *mainlist = NULL;

int datacmp (Node* a, Node* b)
{
	if (a->data > b->data) {
		return 1;
	} else if (a->data < b->data) {
		return -1;
	} else {
		return 0;
	}
}

int print_menu(int selection)
{
	printf("\n\t.::Linked List Menu::.\n");
	printf("\n>Enter 1 to add data into list");
	printf("\n>Enter 2 to show list info");
	printf("\n>Enter 3 to delete entire list");
	printf("\n>Enter 4 to search an element in list");
	printf("\n>Enter 5 to delete a specific element");
	printf("\n>Enter 6 to sort the list");
	printf("\n>Enter 7 to exit");
	printf("\n>>>Enter here: ");

	while (!scanf("%d", &selection)) {
		while (getchar() != '\n');
		printf("\nPlease enter a valid menu option: ");
	}

	return selection;
}

void list_append ()
{
	char user_yn;
	Node* newnode = malloc(sizeof(Node));

	printf("\nEnter the data you want to add: ");

	while (!scanf("%d", &(newnode->data))) {
		printf("\nPlease enter a valid data: ");
		while (getchar() != '\n');
	}

	LL_APPEND(mainlist, newnode);

	printf("\nElement added. More? (y/n): ");
	scanf(" %c", &user_yn);

	if(user_yn == 'y') {
		list_append(mainlist);
	}

	return;
}

void list_print ()
{
	Node* elt,* tmp;
			LL_FOREACH_SAFE(mainlist,elt,tmp) {
					if(elt->next) {
						printf("%d -> ", elt->data);
					} else {
						printf("%d", elt->data);
					}
		    	}
			return;
}

int list_length ()
{
	int len = 0;
	Node* elt,* tmp;
	LL_FOREACH_SAFE(mainlist,elt,tmp) {
			len++;
		    	}
	return len;
}

void list_info ()
{
	printf("\n___INFO___\nList: ");
	list_print();
	printf("\n\nList length: %d\n", list_length());
	return;
}

void list_delete ()
{
	if((mainlist) == NULL) {
		printf("\nERR: List is already empty.\n");
		return;
	}
	char user_yn;

	printf("\nWARNING! Are you sure? This will erase entire list! (y/n): ");
	scanf(" %c", &user_yn);

	if(user_yn == 'y'){
		Node *elt, *tmp;

		LL_FOREACH_SAFE(mainlist,elt,tmp) {
			LL_DELETE(mainlist,elt);
			free(elt);
	    	}
		printf("\nList Deleted.\n");
	}
	return;
}

void list_search ()
{
	if (mainlist == NULL) {
		printf("\nERR: You can't search a list which has 0 elements.\n");
		return;
	}

	Node *elt, *tmp;
	int place = 1;
	printf("\nEnter the value you want to search for: ");

	int user_value;

	while (!scanf("%d", &user_value)) {
		printf("You can't search that. Please enter a valid data: ");
		while (getchar() != '\n');
	}

	LL_FOREACH_SAFE(mainlist, elt, tmp) {

		if (elt->data == user_value) {
			printf("\nElement found at position %d.\n", place);
			break;
		}
		place++;
	}

	if(elt == NULL) {
		printf("\nElement is not in the list.\n");
	}
	return;

}

void list_sort ()
{
	if (mainlist == NULL || mainlist->next == NULL) {
		printf("\nERR: You can't sort a list with single or no elements.\n");
		return;
	}

	LL_SORT(mainlist, datacmp);
	printf("\nList sorted.\n");

	return;
}

void node_delete ()
{
	if(mainlist == NULL) {
		printf("\nERR: List is empty.\n");
		return;
	}

	Node *elt, *tmp;
	printf("\nEnter the value you want to delete: ");

	int user_value;
	while (!scanf("%d", &user_value)) {
		printf("\nPlease enter a valid data: ");
		while (getchar() != '\n');
	}

	LL_FOREACH_SAFE(mainlist, elt, tmp) {
		if (elt->data == user_value) {
			LL_DELETE(mainlist, elt);
			free(elt);
			printf("\nElement found and deleted.\n");
			break;
		}
	}

	if(elt == NULL) {
		printf("\nElement is not in the list.\n");
	}

	return;
}

void silent_list_delete ()
{
	if((mainlist) == NULL) {
		return;
	} else {
		Node *elt, *tmp;
			LL_FOREACH_SAFE(mainlist,elt,tmp) {
				LL_DELETE(mainlist,elt);
				free(elt);
			}
	  }

	return;
}

void append_and_search (int a, int b, int c)
{

        clock_t begin, end;
        double time_spent;

        begin = clock();
        int i;

        for (i = 1; i <= a; i++) {

            Node *newnode = malloc(sizeof(Node));
            newnode->data = i;

            LL_PREPEND(mainlist, newnode);
        }

        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        printf("\nConstruction: %.8f\n", time_spent);
        int counter;

        for (counter = 0; counter<10000; counter++) {

            begin = clock();

            int found_elements = 0;
            int j = 1;
            Node *elt;

            for (j = b; j < c; j++) {

                LL_FOREACH(mainlist, elt) {

                    if (elt->data == j) {
                        found_elements++;
                        continue;
                    }
                }
        }

        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        printf("Search: %.8f ", time_spent);

        printf("| Elements: %d/%d\n", found_elements, c-b);
    }
}

int main (int argc, char* argv[])
{

    if (argc < 4) {
        printf("\nERROR: Too few arguments.\nAt least 3 arguments expected.\n");
        return 1;

    }

    append_and_search(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

	int user_menu_choice = 0;
	int exit_request = 0;

	while(!exit_request){
	    user_menu_choice = print_menu(user_menu_choice);

		switch (user_menu_choice)
		{
			case 1:
			        list_append();
					break;

			case 2:
			        list_info();
					break;

			case 3:
			        list_delete();
					break;

			case 4:
			        list_search();
					break;

			case 5:
			        node_delete();
					break;

			case 6:
			        list_sort();
					break;

			case 7:
			        exit_request = 1;
					break;

			default:
			        printf("\nERR: Please enter option 1-7.\n");
					break;
		}
	}

	silent_list_delete();
	return 0;
}
