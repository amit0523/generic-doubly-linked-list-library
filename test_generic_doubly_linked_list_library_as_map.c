
/*
 * License:
 *
 * This file has been released under "unlicense" license
 * (https://unlicense.org).
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or distribute
 * this software, either in source code form or as a compiled binary, for any
 * purpose, commercial or non-commercial, and by any means.
 *
 * For more information about this license, please visit - https://unlicense.org
 */

/*
 * Author: Amit Choudhary
 * Email: amitchoudhary0523 AT gmail DOT com
 */

#include "generic_doubly_linked_list_library.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SIZE 256
#define NUM_ELEMENTS 5

#define ASC  1 // ascending order.
#define DESC 2 // descending order. Any value other than 1 (ASC).

struct mymap {
    char *key_str;
    long val;
};

// function prototypes for gcc flag -Werror-implicit-function-declaration
static char *get_input_from_stdin_and_discard_extra_characters(char *str,
                                                               long size);
static int compare_elems(struct element *first, struct element *second);
static void free_key_str(struct mymap *mm);
static void populate_map(struct gdll_container *gc, struct mymap *mm,
                         long count, int sorting_order);
static void print_key_and_value_without_removing_elements(
                                                    struct gdll_container *gc);
static void print_key_and_value_by_removing_elements(struct gdll_container *gc);
static void populate_and_print_map(struct gdll_container *gc, struct mymap *mm,
                                   long count, int sorting_order);

static char *get_input_from_stdin_and_discard_extra_characters(char *str,
                                                               long size)
{

    int c = 0;
    long i = 0;

    // If 'size' is 0 then this function will discard all input and return NULL.
    // No need to check 'str' if 'size' is 0.
    if (size == 0) {
        // discard all input
        while ((c = getchar()) && (c != '\n') && (c != EOF));
        return NULL;
    }

    if (str == NULL)
        return NULL;

    if (size < 0)
        return NULL;

    for (i = 0; i < (size - 1); i = i + 1) {

        c = getchar();

        if ((c == '\n') || (c == EOF)) {
            str[i] = 0;
            return str;
        }

        str[i] = (char)(c);

    } // end of for loop

    str[i] = 0;

    // discard rest of input
    while ((c = getchar()) && (c != '\n') && (c != EOF));

    return str;

} // end of function get_input_from_stdin_and_discard_extra_characters()

static int compare_elems(struct element *first, struct element *second)
{

    if ((first == NULL) || (second == NULL)) {
        printf("Error: %s(): One or more arguments are NULL. Exiting..\n\n",
               __FUNCTION__);
        exit(1);
    }

    char *i = ((struct mymap *)(first->data_ptr))->key_str;
    char *j = ((struct mymap *)(second->data_ptr))->key_str;

    return strcmp(i, j);

} // end of function compare_elems()

static void free_key_str(struct mymap *mm)
{

    if (mm == NULL) {
        printf("Error: %s(): Argument 'mm' is NULL.\n", __FUNCTION__);
        return;
    }

    //printf("DEBUG: Freeing key_str.\n");

    free(mm->key_str);

    return;

} // end of function free_key_str()

// populate the map
static void populate_map(struct gdll_container *gc, struct mymap *mm,
                         long count, int sorting_order)
{

    struct element *dup_elem = NULL;

    if ((gc == NULL) || (mm == NULL) || (count <= 0)) {
        printf("Error: %s(): One or more arguments are invalid.\n",
               __FUNCTION__);
        return;
    }

    printf("\n");

    printf("---------------------------------------------------\n");
    printf("Please input the data.\n");
    printf("You will be asked to input the data for %ld elements.\n", count);
    printf("The map elements will be stored in \"%s\" order of keys.\n",
            (sorting_order == ASC) ? "ASCENDING" : "DESCENDING");
    printf("---------------------------------------------------\n");

    while (count-- > 0) {

        printf("\n");

        // Don't free mm->key_str. It will be freed by your callback function
        // when the element will be deleted.
        mm->key_str = calloc(MAX_STR_SIZE, 1);
        if ((mm->key_str) == NULL) {
            printf("No memory..Exiting..\n\n");
            free(mm); // free it here as this one isn't in the library yet
            gdlll_delete_gdll_container(gc);
            exit(1);
        }

        mm->val = -1;

        printf("Please enter a valid string (key) (input is not checked): ");
        get_input_from_stdin_and_discard_extra_characters(mm->key_str,
                                                          MAX_STR_SIZE);
        printf("Please enter a valid integer (input is not checked): ");
        scanf("%ld", &(mm->val));
        get_input_from_stdin_and_discard_extra_characters(NULL, 0);
        dup_elem = gdlll_peek_matching_element(gc, mm, sizeof(*mm),
                                               compare_elems);
        if (dup_elem == NULL) {
            if (sorting_order == ASC) {
                gdlll_add_element_sorted_ascending(gc, mm, sizeof(*mm),
                                                   compare_elems);
            } else {
                gdlll_add_element_sorted_descending(gc, mm, sizeof(*mm),
                                                    compare_elems);
            }
        } else { // if you want to replace the exisiting value of the key
            gdlll_replace_data_in_matching_element(gc, dup_elem->data_ptr,
                                 sizeof (*(struct mymap *)(dup_elem->data_ptr)),
                                 mm, sizeof(*mm), compare_elems);
        }

    } // end of while loop

    return;

} // end of function populate_map()

static void print_key_and_value_without_removing_elements(
                                                    struct gdll_container *gc)
{

    struct element *elem = NULL;
    struct mymap *elem_mm = NULL;

    if (gc == NULL) {
        printf("%s(): Argument 'gc' is NULL.\n", __FUNCTION__);
        return;
    }

    printf("\n");

    printf("--------------------------------------\n");
    printf("Printing keys and values from the map without removing the elements"
           " from the map.\n");
    printf("--------------------------------------\n");

    for (elem = gc->first; elem != NULL; elem=elem->next) {
        elem_mm = (struct mymap *)(elem->data_ptr);
        printf("key:%s, value:%ld\n", elem_mm->key_str, elem_mm->val);
    }

} // end of function print_key_and_value_without_removing_elements()

static void print_key_and_value_by_removing_elements(struct gdll_container *gc)
{

    struct element *elem = NULL;
    struct mymap *elem_mm = NULL;

    if (gc == NULL) {
        printf("%s(): Argument 'gc' is NULL.\n", __FUNCTION__);
        return;
    }

    printf("\n");

    printf("--------------------------------------\n");
    printf("Printing keys and values from the map by removing the elements"
           " from the map.\n");
    printf("--------------------------------------\n");

    elem = gdlll_get_front_element(gc);
    while (elem != NULL) {
        elem_mm = (struct mymap *)(elem->data_ptr);
        printf("key:%s, value:%ld\n", elem_mm->key_str, elem_mm->val);
        gdlll_delete_standalone_element(gc, elem);
        elem = gdlll_get_front_element(gc);
    }

} // end of function print_key_and_value_by_removing_elements()

static void populate_and_print_map(struct gdll_container *gc, struct mymap *mm,
                                   long count, int sorting_order)
{

    if ((gc == NULL) || (mm == NULL) || (count <= 0)) {
        printf("Error: %s(): One or more arguments are invalid.\n",
               __FUNCTION__);
        return;
    }

    // populate the map
    populate_map(gc, mm, count, sorting_order);

    printf("\n\n");

    printf("-------------------------------------------\n");
    printf("Total number of elements in the map = %ld\n",
            gdlll_get_total_number_of_elements_in_gdll_container(gc));
    printf("-------------------------------------------\n");

    // print all keys and values from the map without removing the elements
    // from the map
    print_key_and_value_without_removing_elements(gc);

    // print all keys and values from the map by removing the elements
    // from the map
    print_key_and_value_by_removing_elements(gc);

} // end of function populate_and_print_map()

int main (void)
{

    struct gdll_container *gc = NULL;
    struct mymap *mm = {0};
    long count = NUM_ELEMENTS;

    gc = gdlll_init_gdll_container(free_key_str);
    if (gc == NULL) {
        printf("No memory..Exiting..\n\n");
        exit(1);
    }

    // free 'mm' before exiting the program. 
    mm = calloc(1, sizeof(*mm));
    if (mm == NULL) {
        printf("No memory..Exiting..\n\n");
        gdlll_delete_gdll_container(gc);
        exit(1);
    }

    // populate and print the map (in ascending order of keys)
    populate_and_print_map(gc, mm, count, ASC);

    printf("\n\n\n");

    // populate and print the map (in descending order of keys)
    populate_and_print_map(gc, mm, count, DESC);

    printf("\n");

    free(mm);

    gdlll_delete_gdll_container(gc);

    return 0;

} // end of function main()

