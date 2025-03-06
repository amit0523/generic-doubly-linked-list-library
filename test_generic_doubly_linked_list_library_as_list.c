
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

int compare(struct element *first, struct element *second)
{
    int i = *(int *)(first->data_ptr);
    int j = *(int *)(second->data_ptr);

    if (i < j) {
        return -1;
    } else if (i == j) {
        return 0;
    } else {
        return 1;
    }

} // end of function compare()

int main (void)
{
    int i = 0;
    int count = 5;
    struct element *elem = NULL;

    struct gdll_container * gc = gdlll_init_gdll_container(NULL);

    printf("\n");
    while (count-- > 0) {
        printf("Please enter an integer: ");
        scanf("%d", &i);
        gdlll_add_element_sorted_descending(gc, &i, sizeof(i), compare);
    }
    printf("\n\n");

    printf("Total number of elements in the list = %ld\n\n",
                gdlll_get_total_number_of_elements_in_gdll_container(gc));

    printf("------------------------------\n");
    printf("Printing values from the list:\n");
    printf("------------------------------\n");

    elem = gdlll_get_front_element(gc);
    while (elem != NULL) {
        printf("%d\n", *(int *)(elem->data_ptr));
        gdlll_delete_standalone_element(gc, elem);
        elem = gdlll_get_front_element(gc);
    }

    printf("\n");

    gdlll_delete_gdll_container(gc);

    return 0;

} // end of function main()

