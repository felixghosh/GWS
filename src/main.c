#include <stdio.h>
#include <string.h>
#include "GCL.h"

int main(){
    tree_map_t* routing_map = new_tree_map((void*)"/about", (void*)"something", &compstring);
    print_tree_map(routing_map, "{%s: %s}");

    return 0;
}