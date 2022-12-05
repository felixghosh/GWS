#ifndef GCL_H
#define GCL_h

#include <stdbool.h>

//GCL - Ghosh C Library
//This is a library of some useful data structures for use in other programs


//util
int compstring(void* d1, void* d2);


//linked_list
typedef struct linked_list_t{
	struct linked_list_t* next;
	struct linked_list_t* prev;
	void* data;
} linked_list_t;

linked_list_t* new_linked_list(void* data);
void free_linked_list(linked_list_t** list);
void prepend_linked_list(linked_list_t** list, void* data);
void append_linked_list(linked_list_t** list, void* data);
int length_linked_list(linked_list_t* list);
void print_linked_list(linked_list_t* list);


//tree_set
typedef struct tree_set_t{
    struct tree_set_t* left;
    struct tree_set_t* right;
    void* data;
    int (*cmp)(void*, void*);
}tree_set_t;

tree_set_t* new_tree_set(void* data, int (*cmp)(void*, void*));
void free_tree_set(tree_set_t* set);
void insert_tree_set(tree_set_t* set, void* data);
void remove_tree_set(tree_set_t* set, void* data);
bool contains_tree_set(tree_set_t* set, void* data);
void print_tree_set(tree_set_t* set, const char* format);
void print_structure_tree_set(tree_set_t* set, const char* format);


//tree_map
typedef struct entry_t{
    void* key;
    void* value;
}entry_t;

typedef struct tree_map_t{
    struct tree_map_t* left;
    struct tree_map_t* right;
    entry_t entry;
    int (*cmp)(void*, void*);
}tree_map_t;

tree_map_t* new_tree_map(void* key, void* value, int (*cmp)(void*, void*));
void free_tree_map(tree_map_t* map);
void insert_tree_map(tree_map_t* map, void* key, void* value);
void remove_tree_map(tree_map_t* map, void* key);
bool contains_tree_map(tree_map_t* map, void* key);
void print_tree_map(tree_map_t* map, const char* format);
void print_structure_tree_map(tree_map_t* map, const char* format);
void* get_tree_map(tree_map_t* map, void* key);

#endif