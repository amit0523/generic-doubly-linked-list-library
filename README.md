I have implemented a C library (**generic_doubly_linked_list_library.c**) that can
be used as a **C++ STL list, map, set, stack, queue, deque, multimap, multiset,
unordered_map, unordered_set, unordered_multimap, unordered_multiset, and priority_queue
(and sorted_list too)** (basically as all C++ STL data structures except vector).

_So, now the developers don't need to write code for implementing data structure(s) (like for list, map, set, etc.),
they can simply use this library and speed up their development._

This library has 3 unique features:

1. You can store any data type in this library.
   
2. You can use this library as different C++ STL data structures by using
   different combinations of functions provided in this library. This library
   has only 22 functions (including 3 static functions).

3. This library copies user's data into its elements, so the user
   doesn't have to keep his/her copy of data around. User's data safely resides
   in the elements. However, the library can't do deep copy because it
   doesn't know whether the user data has pointers. So, the user can free
   its top level data but the user should not free embedded pointers.
   These embedded pointers will be freed by the user's callback function
   when an element is getting deleted.

Example:

```
Let's say that you have a structure (as shown below) that you are storing in the element.

struct mydata {
  char *str;
  int val;
}

struct mydata *md = malloc(sizeof(*md));
md->str = malloc(10);
gdlll_add_element_to_front(..., md, ...);
free(md);

Now, you can free 'md' but you should not free 'md->str'. 'md->str' will be freed by
calling your free function (function_ptr_to_call_before_deleting_data) when the element
is getting deleted. This function was provided by you when you initialized the container:
gdlll_init_gdll_container(void *function_ptr_to_call_before_deleting_data).
```


**I have uploaded the code of the C library (generic_doubly_linked_list_library.c) and also the code of the
test programs that show how to use this library as a 'sorted list' and as a 'map'.**
<br>
<br>
<ins>**The source files in this repository are:**</ins>
<br>
<br>
**generic_doubly_linked_list_library.c<br>
generic_doubly_linked_list_library.h<br>
test_generic_doubly_linked_list_library_as_list.c<br>
test_generic_doubly_linked_list_library_as_map.c**
<br>
<hr>

**The functions available in this library are:**
```
gdlll_init_gdll_container()
gdlll_get_total_number_of_elements_in_gdll_container()
gdlll_add_element_to_front()
gdlll_add_element_to_back()
gdlll_add_element_sorted_ascending()
gdlll_add_element_sorted_descending()
gdlll_get_front_element()
gdlll_get_last_element()
gdlll_get_matching_element()
gdlll_peek_front_element()
gdlll_peek_last_element()
gdlll_peek_matching_element()
gdlll_replace_data_in_matching_element()
gdlll_delete_front_element()
gdlll_delete_last_element()
gdlll_delete_matching_element()
gdlll_delete_standalone_element()
gdlll_delete_all_elements_in_gdll_container()
gdlll_delete_gdll_container()

/* static functions */
gdlll_create_standalone_element()
gdlll_remove_element_from_list()
gdlll_insert_element_before_element()
```
<hr>

**Some pseudocode for using this library as a 'list' is:**

```
gdlll_add_element_to_front(...);
or,
gdlll_add_element_to_back(...);
...
...
elem = gdlll_get_front_element(...);
or,
elem = gdlll_get_last_element(...);
or,
elem = gdlll_get_matching_element(...);
```
<br>

**Some pseudocode for using this library as a 'sorted list' is:**

```
gdlll_add_element_sorted_ascending(...);
or,
gdlll_add_element_sorted_descending(...);
...
...
elem = gdlll_get_front_element(...);
or,
elem = gdlll_get_last_element(...);
or,
elem = gdlll_get_matching_element(...);
```
<br>

**Some pseudocode for using this library as a 'set' is:**

```
if (gdlll_peek_matching_element(...) == NULL) {
    gdlll_add_element_sorted_ascending(...);
    or,
    gdlll_add_element_sorted_descending(...);
}
```
<br>

**Some pseudocode for using this library as an 'unordered_set' is:**

```
if (gdlll_peek_matching_element(...) == NULL) {
    gdlll_add_element_to_front(...);
    or,
    gdlll_add_element_to_back(...);
}
```
<br>

**Some pseudocode for using this library as a 'map' is:**

```
For using this library as a 'map', etc, your 'data_ptr' must point to a structure
that has a 'key' member and a 'value' member.

struct mymap
{
    char *key;
    int value;
};

struct mymap *mm;
mm = malloc(sizeof(*mm));
mm->key = malloc(10);
strncpy(mm->key, "abcd", 10);
mm->key[4] = 0;
mm->value = 20;

dup_elem = gdlll_peek_matching_element(gc, mm, sizeof(*mm), compare_elems);
if (dup_elem == NULL) {
    gdlll_add_element_sorted_ascending(gc, mm, sizeof(*mm), compare_elems);
} else { // if you want to replace exisiting value of the key
    gdlll_replace_data_in_matching_element(gc, dup_elem->data_ptr,
                               sizeof (*(struct mymap *)(dup_elem->data_ptr)),
                               mm, sizeof(*mm), compare_elems);
}                                                                        
...
...
elem = gdlll_get_front_element(...);
or,
elem = gdlll_get_last_element(...);
or,
elem = gdlll_get_matching_element(...);
```

---- End of README ----
