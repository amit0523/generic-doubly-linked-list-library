
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
 * For more information about this license, please visit
 * <https://unlicense.org>.
 */

/*
 * Author: Amit Choudhary
 * Email: amitchoudhary0523 AT gmail DOT com
 */

#ifndef _GENERIC_DOUBLY_LINKED_LIST_LIBRARY_H_
#define _GENERIC_DOUBLY_LINKED_LIST_LIBRARY_H_

// gdlll means generic doubly linked list library.
// gdllc means generic doubly linked list container.
// gdll means generic doubly linked list.

// Everything happened successfully.
#define GDLLL_SUCCESS 0

// 'gdllc_ptr' argument is NULL.
#define GDLLL_GDLLC_PTR_IS_NULL -1

// 'data_ptr' argument is NULL.
#define GDLLL_DATA_PTR_IS_NULL -2

// 'data_size' argument is <= 0.
#define GDLLL_DATA_SIZE_IS_INVALID -3

// There are no elements in the container.
#define GDLLL_CONTAINER_IS_EMPTY -4

// No memory available.
#define GDLLL_NO_MEMORY -5

// Matching element was not found in the list.
#define GDLLL_MATCHING_ELEMENT_NOT_FOUND -6

// The function pointer given by the user for comparing elements is NULL.
#define GDLLL_COMPARE_ELEMENTS_FUNC_PTR_IS_NULL -7

// This is used only for initializing error variables.
#define GDLLL_ERROR_INIT_VALUE -99

struct element
{
    void *data_ptr;
    long data_size;
    struct element *prev;
    struct element *next;
};

/*
 * The user needs to give a function pointer to compare elements in some
 * functions of this library. Below is the signature of the elements comparator
 * function.
 *
 * The return value of this function should be -1 if 'first' is less than the
 * 'second', 0 if 'first' is equal to the 'second', and 1 if 'first' is greater
 * than the 'second'.
 */
typedef int (*compare_elements_function)(struct element *first,
                                         struct element *second);

struct gdll_container
{
    struct element *first;
    struct element *last;
    long total_number_of_elements;
    // This function pointer will be called before freeing 'data_ptr' member of
    // the element structure. This will be needed if the user has allocated some
    // memory in 'data_ptr' and the user wants to free it before the 'data_ptr'
    // member is freed by this library. So, if the user has a need for it then
    // the user can give a valid function pointer to call when initializing this
    // library (by calling the function 'gdlll_init_gdll_container'). The user
    // may also give NULL function pointer if the user doesn't need this
    // functionality.
    void (*call_function_before_deleting_data)(void *data_ptr, long data_size);
};

struct gdll_container *gdlll_init_gdll_container(
                            void *function_ptr_to_call_before_deleting_data);

// This function doesn't check the validity of its arguments. It is the
// responsibility of the calling function to check the arguments it is passing
// to this function.
static struct element *gdlll_create_standalone_element(void *data_ptr,
                                                       long data_size);

// This function doesn't check the validity of its arguments. It is the
// responsibility of the calling function to check the arguments it is passing
// to this function. This function just removes the element from the list,
// it doesn't decrement total_number_of_elements by 1. Decrementing has to be
// done in the calling function. This function should not be called if the
// number of elements in the container is 0. The calling function should first
// check whether the number of elements in the container is 0 or not.
static void gdlll_remove_element_from_list(struct gdll_container *gdllc_ptr,
                                           struct element *elem_ptr);

// This function doesn't check the validity of its arguments. It is the
// responsibility of the calling function to check the arguments it is passing
// to this function. This function just inserts the element in the list at the
// appropriate place, it doesn't increment total_number_of_elements by 1.
// Incrementing has to be done in the calling function. This function should not
// be called if the number of elements in the container is 0. The calling
// function should first check whether the number of elements in the container
// is 0 or not.
static void gdlll_insert_element_before_element(struct gdll_container *gdllc_ptr,
                                          struct element *elem_to_insert_ptr,
                            struct element *elem_before_which_to_insert_ptr);

// If gdllc_ptr is NULL, then this function returns 0
long gdlll_get_total_number_of_elements_in_gdll_container(
                                            struct gdll_container *gdllc_ptr);

int gdlll_add_element_to_front(struct gdll_container *gdllc_ptr, void *data_ptr,
                               long data_size);

int gdlll_add_element_to_back(struct gdll_container *gdllc_ptr, void *data_ptr,
                              long data_size);

int gdlll_add_element_sorted_ascending(struct gdll_container *gdllc_ptr,
                                       void *data_ptr, long data_size,
                                       compare_elements_function comp_func);

int gdlll_add_element_sorted_descending(struct gdll_container *gdllc_ptr,
                                        void *data_ptr, long data_size,
                                        compare_elements_function comp_func);

// All gdlll_get_* functions remove the element from the list and then return
// the element. If you don't want the element to be removed from the list then
// use gdlll_peek_* functions. If there are no elements in the container
// then NULL is returned.
struct element *gdlll_get_front_element(struct gdll_container *gdllc_ptr);

struct element *gdlll_get_last_element(struct gdll_container *gdllc_ptr);

struct element *gdlll_get_matching_element(struct gdll_container *gdllc_ptr,
                                           void *data_ptr, long data_size,
                                           compare_elements_function comp_func);

// All gdlll_peek_* functions return the element without removing it from the
// list. If there are no elements in the container then NULL is returned.
struct element *gdlll_peek_front_element(struct gdll_container *gdllc_ptr);

struct element *gdlll_peek_last_element(struct gdll_container *gdllc_ptr);

struct element *gdlll_peek_matching_element(struct gdll_container *gdllc_ptr,
                                            void *data_ptr, long data_size,
                                           compare_elements_function comp_func);

int gdlll_replace_data_in_matching_element(struct gdll_container *gdllc_ptr,
                                         void *old_data_ptr, long old_data_size,
                                         void *new_data_ptr, long new_data_size,
                                         compare_elements_function comp_func);

void gdlll_delete_front_element(struct gdll_container *gdllc_ptr);

void gdlll_delete_last_element(struct gdll_container *gdllc_ptr);

void gdlll_delete_matching_element(struct gdll_container *gdllc_ptr,
                                   void *data_ptr, long data_size,
                                   compare_elements_function comp_func);

void gdlll_delete_standalone_element(struct gdll_container *gdllc_ptr,
                                     struct element *element_to_delete);

void gdlll_delete_all_elements_in_gdll_container(
                                            struct gdll_container *gdllc_ptr);

void gdlll_delete_gdll_container(struct gdll_container *gdllc_ptr);

#endif

