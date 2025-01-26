
/*
 * License: This file has been released under license GPLv2.
 */

/*
 * Author: Amit Choudhary
 * Email: amitchoudhary0523 AT gmail DOT com
 */

#include "generic_doubly_linked_list_library.h"

#include <stdlib.h>
#include <string.h>

static struct element *gdlll_create_standalone_element(void *data_ptr,
                                                       long data_size)
{
    struct element *elem_ptr = NULL;

    elem_ptr = calloc(sizeof(*elem_ptr), 1);
    if (!elem_ptr) {
        return NULL;
    }

    elem_ptr->data_ptr = calloc((size_t)(data_size), 1);
    if (!(elem_ptr->data_ptr)) {
        free(elem_ptr);
        return NULL;
    }

    memmove(elem_ptr->data_ptr, data_ptr, (size_t)(data_size));
    elem_ptr->data_size = data_size;

    elem_ptr->prev = NULL;
    elem_ptr->next = NULL;

    return elem_ptr;

} // end of gdlll_create_standalone_element() function

static void gdlll_remove_element_from_list(struct gdll_container *gdllc_ptr,
                                           struct element *elem_ptr)
{

    if (elem_ptr == gdllc_ptr->first) {
        gdllc_ptr->first = elem_ptr->next;
        if (gdllc_ptr->first == NULL) {
            gdllc_ptr->last = NULL;
        } else {
            gdllc_ptr->first->prev = NULL;
        }
    } else if (elem_ptr == gdllc_ptr->last) {
        gdllc_ptr->last = elem_ptr->prev;
        if (gdllc_ptr->last == NULL) {
            gdllc_ptr->first = NULL;
        } else {
            gdllc_ptr->last->next = NULL;
        }
    } else {
        elem_ptr->prev->next = elem_ptr->next;
        elem_ptr->next->prev = elem_ptr->prev;
    }

    elem_ptr->prev = NULL;
    elem_ptr->next = NULL;

} // end of gdlll_remove_element_from_list() function

static void insert_element_before_element(struct gdll_container *gdllc_ptr,
                                          struct element *elem_to_insert_ptr,
                            struct element *elem_before_which_to_insert_ptr)
{

    if (elem_before_which_to_insert_ptr == NULL) {

        // add elem_to_insert_ptr to back
        gdllc_ptr->last->next = elem_to_insert_ptr;
        elem_to_insert_ptr->prev = gdllc_ptr->last;
        gdllc_ptr->last = elem_to_insert_ptr;

    } else if (elem_before_which_to_insert_ptr == gdllc_ptr->first) {

        // add elem_to_insert_ptr to front
        elem_to_insert_ptr->next = gdllc_ptr->first;
        elem_to_insert_ptr->next->prev = elem_to_insert_ptr;
        gdllc_ptr->first = elem_to_insert_ptr;

    } else {

        // insert elem_to_insert_ptr before elem_before_which_to_insert_ptr
        elem_to_insert_ptr->next = elem_before_which_to_insert_ptr;
        elem_to_insert_ptr->prev = elem_before_which_to_insert_ptr->prev;
        elem_before_which_to_insert_ptr->prev = elem_to_insert_ptr;
        elem_to_insert_ptr->prev->next = elem_to_insert_ptr;

    }

} // end of insert_element_before_element() function

struct gdll_container *gdlll_init_gdll_container(
                            void *function_ptr_to_call_before_deleting_data)
{

    struct gdll_container *gdllc_ptr = calloc(sizeof(*gdllc_ptr), 1);

    if (!gdllc_ptr)
        return NULL;

    gdllc_ptr->first = NULL;
    gdllc_ptr->last = NULL;
    gdllc_ptr->total_number_of_elements = 0;
    gdllc_ptr->call_function_before_deleting_data =
                                    function_ptr_to_call_before_deleting_data;

    return gdllc_ptr;

} // end of gdlll_init_gdll_container() function

long gdlll_get_total_number_of_elements_in_gdll_container(
                                            struct gdll_container *gdllc_ptr)
{

    if (!gdllc_ptr) {
        return 0;
    }

    return (gdllc_ptr->total_number_of_elements);

} // end of gdlll_get_total_number_of_elements_in_gdll_container() function

int gdlll_add_element_to_front(struct gdll_container *gdllc_ptr, void *data_ptr,
                               long data_size)
{

    struct element *elem_ptr = NULL;

    if (!gdllc_ptr) {
        return GDLLL_GDLLC_PTR_IS_NULL;
    }

    if (!data_ptr) {
        return GDLLL_DATA_PTR_IS_NULL;
    }

    if (data_size <= 0) {
        return GDLLL_DATA_SIZE_IS_INVALID;
    }

    elem_ptr = gdlll_create_standalone_element(data_ptr, data_size);

    if (!elem_ptr) {
        return GDLLL_NO_MEMORY;
    }

    if (gdllc_ptr->first == NULL) {
        gdllc_ptr->first = elem_ptr;
        gdllc_ptr->last = elem_ptr;
    } else {
        elem_ptr->next = gdllc_ptr->first;
        elem_ptr->next->prev = elem_ptr;
        gdllc_ptr->first = elem_ptr;
    }

    gdllc_ptr->total_number_of_elements =
                                    gdllc_ptr->total_number_of_elements + 1;

    return GDLLL_SUCCESS;

} // end of gdlll_add_element_to_front() function

int gdlll_add_element_to_back(struct gdll_container *gdllc_ptr, void *data_ptr,
                              long data_size)
{

    struct element *elem_ptr = NULL;

    if (!gdllc_ptr) {
        return GDLLL_GDLLC_PTR_IS_NULL;
    }

    if (!data_ptr) {
        return GDLLL_DATA_PTR_IS_NULL;
    }

    if (data_size <= 0) {
        return GDLLL_DATA_SIZE_IS_INVALID;
    }

    elem_ptr = gdlll_create_standalone_element(data_ptr, data_size);

    if (!elem_ptr) {
        return GDLLL_NO_MEMORY;
    }

    if (gdllc_ptr->first == NULL) {
        gdllc_ptr->first = elem_ptr;
        gdllc_ptr->last = elem_ptr;
    } else {
        gdllc_ptr->last->next = elem_ptr;
        elem_ptr->prev = gdllc_ptr->last;
        gdllc_ptr->last = elem_ptr;
    }

    gdllc_ptr->total_number_of_elements =
                                    gdllc_ptr->total_number_of_elements + 1;

    return GDLLL_SUCCESS;

} // end of gdlll_add_element_to_back() function

int gdlll_add_element_sorted_ascending(struct gdll_container *gdllc_ptr,
                                       void *data_ptr, long data_size,
                                       compare_elements_function comp_func)
{

    struct element *elem_ptr = NULL;

    if (!gdllc_ptr) {
        return GDLLL_GDLLC_PTR_IS_NULL;
    }

    if (!data_ptr) {
        return GDLLL_DATA_PTR_IS_NULL;
    }

    if (data_size <= 0) {
        return GDLLL_DATA_SIZE_IS_INVALID;
    }

    if (!comp_func) {
        return GDLLL_COMPARE_ELEMENTS_FUNC_PTR_IS_NULL;
    }

    elem_ptr = gdlll_create_standalone_element(data_ptr, data_size);

    if (!elem_ptr) {
        return GDLLL_NO_MEMORY;
    }

    if (gdllc_ptr->first == NULL) {
        gdllc_ptr->first = elem_ptr;
        gdllc_ptr->last = elem_ptr;
    } else {
        struct element *temp = gdllc_ptr->first;
        while ((temp) && (comp_func(elem_ptr, temp) > 0)) {
            temp = temp->next;
        }
        // insert elem_ptr before temp
        insert_element_before_element(gdllc_ptr, elem_ptr, temp);
    }

    gdllc_ptr->total_number_of_elements =
                                    gdllc_ptr->total_number_of_elements + 1;

    return GDLLL_SUCCESS;

} // end of gdlll_add_element_sorted_ascending() function

int gdlll_add_element_sorted_descending(struct gdll_container *gdllc_ptr,
                                        void *data_ptr, long data_size,
                                        compare_elements_function comp_func)
{

    struct element *elem_ptr = NULL;

    if (!gdllc_ptr) {
        return GDLLL_GDLLC_PTR_IS_NULL;
    }

    if (!data_ptr) {
        return GDLLL_DATA_PTR_IS_NULL;
    }

    if (data_size <= 0) {
        return GDLLL_DATA_SIZE_IS_INVALID;
    }

    if (!comp_func) {
        return GDLLL_COMPARE_ELEMENTS_FUNC_PTR_IS_NULL;
    }

    elem_ptr = gdlll_create_standalone_element(data_ptr, data_size);

    if (!elem_ptr) {
        return GDLLL_NO_MEMORY;
    }

    if (gdllc_ptr->first == NULL) {
        gdllc_ptr->first = elem_ptr;
        gdllc_ptr->last = elem_ptr;
    } else {
        struct element *temp = gdllc_ptr->first;
        while ((temp) && (comp_func(elem_ptr, temp) < 0)) {
            temp = temp->next;
        }
        // insert elem_ptr before temp
        insert_element_before_element(gdllc_ptr, elem_ptr, temp);
    }

    gdllc_ptr->total_number_of_elements =
                                    gdllc_ptr->total_number_of_elements + 1;

    return GDLLL_SUCCESS;

} // end of gdlll_add_element_sorted_descending() function

struct element *gdlll_get_front_element(struct gdll_container *gdllc_ptr)
{

    struct element *temp = NULL;

    if (!gdllc_ptr) {
        return NULL;
    }

    if (gdllc_ptr->total_number_of_elements == 0) {
        return NULL;
    }

    temp = gdllc_ptr->first;

    gdlll_remove_element_from_list(gdllc_ptr, gdllc_ptr->first);

    gdllc_ptr->total_number_of_elements =
                                    gdllc_ptr->total_number_of_elements - 1;

    return temp;

} // end of gdlll_get_front_element() function

struct element *gdlll_get_last_element(struct gdll_container *gdllc_ptr)
{

    struct element *temp = NULL;

    if (!gdllc_ptr) {
        return NULL;
    }

    if (gdllc_ptr->total_number_of_elements == 0) {
        return NULL;
    }

    temp = gdllc_ptr->last;

    gdlll_remove_element_from_list(gdllc_ptr, gdllc_ptr->last);

    gdllc_ptr->total_number_of_elements =
                                    gdllc_ptr->total_number_of_elements - 1;

    return temp;

} // end of gdlll_get_last_element() function

struct element *gdlll_get_matching_element(struct gdll_container *gdllc_ptr,
                                           void *data_ptr, long data_size,
                                           compare_elements_function comp_func)
{

    struct element *matching_elem_ptr = NULL;

    if (!gdllc_ptr) {
        return NULL;
    }

    if (!data_ptr) {
        return NULL;
    }

    if (data_size <= 0) {
        return NULL;
    }

    if (!comp_func) {
        return NULL;
    }

    if (gdllc_ptr->total_number_of_elements == 0) {
        return NULL;
    }

    matching_elem_ptr = gdlll_peek_matching_element(gdllc_ptr, data_ptr,
                                                    data_size, comp_func);

    if (matching_elem_ptr == NULL) {
        return NULL;
    }

    gdlll_remove_element_from_list(gdllc_ptr, matching_elem_ptr);

    gdllc_ptr->total_number_of_elements =
                                    gdllc_ptr->total_number_of_elements - 1;

    return matching_elem_ptr;

} // end of gdlll_get_matching_element() function

struct element *gdlll_peek_front_element(struct gdll_container *gdllc_ptr)
{

    if (!gdllc_ptr) {
        return NULL;
    }

    return (gdllc_ptr->first);

} // end of gdlll_peek_front_element() function

struct element *gdlll_peek_last_element(struct gdll_container *gdllc_ptr)
{

    if (!gdllc_ptr) {
        return NULL;
    }

    return (gdllc_ptr->last);

} // end of gdlll_peek_last_element() function

struct element *gdlll_peek_matching_element(struct gdll_container *gdllc_ptr,
                                            void *data_ptr, long data_size,
                                            compare_elements_function comp_func)
{

    struct element *elem_ptr = NULL;
    struct element *temp = NULL;

    if (!gdllc_ptr) {
        return NULL;
    }

    if (!data_ptr) {
        return NULL;
    }

    if (data_size <= 0) {
        return NULL;
    }

    if (!comp_func) {
        return NULL;
    }

    if (gdllc_ptr->total_number_of_elements == 0) {
        return NULL;
    }

    elem_ptr = gdlll_create_standalone_element(data_ptr, data_size);

    if (!elem_ptr) {
        return NULL;
    }

    temp = gdllc_ptr->first;

    while ((temp) && (comp_func(elem_ptr, temp) != 0)) {
        temp = temp->next;
    }

    gdlll_delete_standalone_element(gdllc_ptr, elem_ptr, 0);

    return temp;

} // end of gdlll_peek_matching_element() function

int gdlll_replace_data_in_matching_element(struct gdll_container *gdllc_ptr,
                                         void *old_data_ptr, long old_data_size,
                                         void *new_data_ptr, long new_data_size,
                                         compare_elements_function comp_func)
{

    struct element *matching_elem_ptr = NULL;
    void *temp_data_ptr = NULL;

    if (!gdllc_ptr) {
        return GDLLL_GDLLC_PTR_IS_NULL;
    }

    if (!old_data_ptr) {
        return GDLLL_DATA_PTR_IS_NULL;
    }

    if (old_data_size <= 0) {
        return GDLLL_DATA_SIZE_IS_INVALID;
    }

    if (!new_data_ptr) {
        return GDLLL_DATA_PTR_IS_NULL;
    }

    if (new_data_size <= 0) {
        return GDLLL_DATA_SIZE_IS_INVALID;
    }

    if (!comp_func) {
        return GDLLL_COMPARE_ELEMENTS_FUNC_PTR_IS_NULL;
    }

    if (gdllc_ptr->total_number_of_elements == 0) {
        return GDLLL_CONTAINER_IS_EMPTY;
    }

    matching_elem_ptr = gdlll_peek_matching_element(gdllc_ptr, old_data_ptr,
                                                    old_data_size, comp_func);

    if (matching_elem_ptr == NULL) {
        return GDLLL_MATCHING_ELEMENT_NOT_FOUND;
    }

    temp_data_ptr = calloc((size_t)(new_data_size), 1);
    if (!temp_data_ptr) {
        return GDLLL_NO_MEMORY;
    }

    // Now, call the call_function_before_deleting_data() for 'data_ptr' of the
    // matching element and then free the 'data_ptr' of the matching element
    if (gdllc_ptr->call_function_before_deleting_data) {
        gdllc_ptr->call_function_before_deleting_data(
                    matching_elem_ptr->data_ptr, matching_elem_ptr->data_size);
    }
    free(matching_elem_ptr->data_ptr);

    matching_elem_ptr->data_ptr = temp_data_ptr;
    memmove(matching_elem_ptr->data_ptr, new_data_ptr, (size_t)(new_data_size));
    matching_elem_ptr->data_size = new_data_size;

    return GDLLL_SUCCESS;

} // end of gdlll_replace_data_in_matching_element() function

void gdlll_delete_front_element(struct gdll_container *gdllc_ptr)
{

    struct element *temp_elem_ptr = NULL;

    if (!gdllc_ptr) {
        return;
    }

    temp_elem_ptr = gdllc_ptr->first;

    if (temp_elem_ptr) {
        gdlll_remove_element_from_list(gdllc_ptr, temp_elem_ptr);
        gdlll_delete_standalone_element(gdllc_ptr, temp_elem_ptr, 1);
        gdllc_ptr->total_number_of_elements =
                                    gdllc_ptr->total_number_of_elements - 1;
    }

    return;

} // end of gdlll_delete_front_element() function

void gdlll_delete_last_element(struct gdll_container *gdllc_ptr)
{

    struct element *temp_elem_ptr = NULL;

    if (!gdllc_ptr) {
        return;
    }

    temp_elem_ptr = gdllc_ptr->last;

    if (temp_elem_ptr) {
        gdlll_remove_element_from_list(gdllc_ptr, temp_elem_ptr);
        gdlll_delete_standalone_element(gdllc_ptr, temp_elem_ptr, 1);
        gdllc_ptr->total_number_of_elements =
                                    gdllc_ptr->total_number_of_elements - 1;
    }

    return;

} // end of gdlll_delete_last_element() function

void gdlll_delete_matching_element(struct gdll_container *gdllc_ptr,
                                   void *data_ptr, long data_size,
                                   compare_elements_function comp_func)
{

    struct element *matching_elem_ptr = NULL;

    if (!gdllc_ptr) {
        return;
    }

    if (!data_ptr) {
        return;
    }

    if (data_size <= 0) {
        return;
    }

    if (!comp_func) {
        return;
    }

    if (gdllc_ptr->total_number_of_elements == 0) {
        return;
    }

    matching_elem_ptr = gdlll_peek_matching_element(gdllc_ptr, data_ptr,
                                                    data_size, comp_func);

    if (matching_elem_ptr == NULL) {
        return;
    }

    gdlll_remove_element_from_list(gdllc_ptr, matching_elem_ptr);
    gdlll_delete_standalone_element(gdllc_ptr, matching_elem_ptr, 1);
    gdllc_ptr->total_number_of_elements =
                                    gdllc_ptr->total_number_of_elements - 1;

    return;

} // end of gdlll_delete_matching_element() function

void gdlll_delete_standalone_element(struct gdll_container *gdllc_ptr,
                                     struct element *element_to_delete,
                                     int is_element_from_list)
{

    if (!gdllc_ptr) {
        return;
    }

    if (!element_to_delete) {
        return;
    }

    // Call the call_function_before_deleting_data() for 'data_ptr' of
    // 'element_to_delete' and then free the 'data_ptr' of 'element_to_delete'.
    // Then free the 'element_to_delete'.
    if (is_element_from_list) {
        if (gdllc_ptr->call_function_before_deleting_data) {
            gdllc_ptr->call_function_before_deleting_data(
                    element_to_delete->data_ptr, element_to_delete->data_size);
        }
    }

    free(element_to_delete->data_ptr);

    free(element_to_delete);

    return;

} // end of gdlll_delete_standalone_element() function

void gdlll_delete_all_elements_in_gdll_container(
                                            struct gdll_container *gdllc_ptr)
{

    struct element *temp_elem_ptr = NULL;

    if (!gdllc_ptr) {
        return;
    }

    if (gdllc_ptr->total_number_of_elements == 0) {
        return;
    }

    temp_elem_ptr = gdllc_ptr->first;

    while (temp_elem_ptr) {
        gdlll_delete_front_element(gdllc_ptr);
        temp_elem_ptr = gdllc_ptr->first;
    }

    return;

} // end of gdlll_delete_all_elements_in_gdll_container() function

void gdlll_delete_gdll_container(struct gdll_container *gdllc_ptr)
{

    if (!gdllc_ptr) {
        return;
    }

    gdlll_delete_all_elements_in_gdll_container(gdllc_ptr);

    free(gdllc_ptr);

    return;

} // end of gdlll_delete_gdll_container() function

