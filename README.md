I have implemented a C library (**generic_doubly_linked_list_library.c**) that can
be used as a C++ STL list, map, set, stack, queue, deque, multimap, multiset,
unordered_map, unordered_set, unordered_multimap, and unordered_multiset
(basically almost all C++ STL data structures).

For using this library as different C++ STL data structures you have to use
different combinations of functions provided in this library.

Another unique feature of this library is that it copies user's data into its
elements, so the user doesn't have to keep his/her copy of data around. User's
data safely resides in the elements.

**I have included the code of the library in this mail and also the code of the
test programs that show how to use this library as a 'sorted list' and 'map'.**
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
<br>
<br>

**An example of using this library as a 'list' is:**

```
gdlll_add_element_to_front(...);
...
...
elem = gdlll_get_front_element(...);
```
<br>

**An example of using this library as a 'sorted list' is:**

```
gdlll_add_element_sorted_ascending(...);
...
...
elem = gdlll_get_front_element(...);
```
<br>

**An example of using this library as a 'set' is:**

```
if (gdlll_peek_matching_element(...) == NULL) {
    gdlll_add_element_sorted_ascending(...);
}
```
<br>

**An example of using this library as an 'unordered set' is:**

```
if (gdlll_peek_matching_element(...) == NULL) {
    gdlll_add_element_to_front(...);
}
```
<br>

**An example of using this library as a 'map' is:**

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

dup_elem = gdlll_peek_matching_element(gc, mm, get_struct_len(mm), 
                                       compare_elems);                   
if (dup_elem == NULL) {                                                  
    gdlll_add_element_sorted_ascending(...);                   
} else { // if you want to replace existing value of the key            
    gdlll_replace_data_in_matching_element(...);
}                                                                        
```

---- End of README ----
