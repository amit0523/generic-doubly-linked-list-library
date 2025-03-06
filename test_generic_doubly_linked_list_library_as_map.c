
/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * For more information, please refer to <https://unlicense.org/>
 */

/*
 * Author: Amit Choudhary
 * Email: amitchoudhary0523 AT gmail DOT com
 */

#include "generic_doubly_linked_list_library.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 256
#define NUM_ELEMENTS 5

struct mymap {
    char *key_str;
    int val;
};

char *get_input_from_stdin_and_discard_extra_characters(char *str, long size)
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

    if (!str)
        return str;

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

int compare_elems(struct element *first, struct element *second)
{
    char *i = ((struct mymap *)(first->data_ptr))->key_str;
    char *j = ((struct mymap *)(second->data_ptr))->key_str;

    return strcmp(i, j);

} // end of function compare_elems()

void free_key_str(struct mymap *mm, long mm_len)
{
    free(mm->key_str);
} // end of function free_key_str()

int main (void)
{
    struct mymap *mm = {0};
    int count = NUM_ELEMENTS;
    struct mymap *elem_mm = NULL;
    struct element *elem = NULL;
    struct element *dup_elem = NULL;
    struct gdll_container *gc = NULL;

    gc = gdlll_init_gdll_container(free_key_str);
    if (!gc) {
        printf("No memory..exiting..");
        exit(1);
    }

    // free 'mm' before exiting the program. 
    mm = calloc(sizeof(*mm), 1);
    if (!mm) {
        printf("No memory..exiting..");
        gdlll_delete_gdll_container(gc);
        exit(1);
    }

    while (count-- > 0) {

        // Don't free mm->key_str. It will be freed by your callback function
        // when the element will be deleted.
        mm->key_str = calloc(MAX_STR_LEN, 1);
        if (!(mm->key_str)) {
            printf("No memory..exiting..");
            free(mm); // free it here as this one isn't in the library yet
            gdlll_delete_gdll_container(gc);
            exit(1);
        }

        printf("\n");
        // clear the input buffer
        printf("Please enter a string (key): ");
        get_input_from_stdin_and_discard_extra_characters(mm->key_str,
                                                          MAX_STR_LEN);
        printf("Please enter an integer value: ");
        scanf("%d", &(mm->val));
        get_input_from_stdin_and_discard_extra_characters(NULL, 0);
        dup_elem = gdlll_peek_matching_element(gc, mm, sizeof(*mm),
                                               compare_elems);
        if (dup_elem == NULL) {
            gdlll_add_element_sorted_ascending(gc, mm, sizeof(*mm),
                                               compare_elems);
        } else { // if you want to replace exisiting value of the key
            gdlll_replace_data_in_matching_element(gc, dup_elem->data_ptr,
                                 sizeof (*(struct mymap *)(dup_elem->data_ptr)),
                                 mm, sizeof(*mm), compare_elems);
        }

    } // end of while loop

    printf("\n\n");

    printf("Total number of elements in the map = %ld\n\n",
            gdlll_get_total_number_of_elements_in_gdll_container(gc));


    printf("--------------------------------------\n");
    printf("Printing keys and values from the map:\n");
    printf("--------------------------------------\n");

    elem = gdlll_get_front_element(gc);
    while (elem != NULL) {
        elem_mm = (struct mymap *)(elem->data_ptr);
        printf("key:%s, value:%d\n", elem_mm->key_str, elem_mm->val);
        gdlll_delete_standalone_element(gc, elem);
        elem = gdlll_get_front_element(gc);
    }

    printf("\n");

    free(mm);

    gdlll_delete_gdll_container(gc);

    return 0;

} // end of function main()

