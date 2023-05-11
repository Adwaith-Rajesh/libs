#define LIBS_LINKED_LIST_IMPLEMENTATION
// #define LIBS_LINKED_LIST_NO_SHORT_NAMES
#include "linked_list.h"

static void _node_printer(Node *data) {
    if (data == NULL) return;
    printf("%s\n", (char *)data->data);
}

int main(int argc, char **argv) {
    LinkedList *list = ll_init();

    for (int i = 0; i < argc; i++) {
        ll_append_left(list, create_node(argv[i]));
    }
    // LinkedList_print(list, _node_printer);

    LLIter *list_iter = LinkedList_iter_init(list);

    Node *iter_val = ll_iter_next(list_iter);  // gets the first value
    for (; iter_val != NULL; iter_val = ll_iter_next(list_iter)) {
        printf("iter val: ");
        _node_printer(iter_val);
    }

    printf("pop\n");
    size_t size = list->size;
    for (int i = 0; i < size; i++) {
        printf("pop val: ");
        Node *pop_node = ll_pop(list);
        _node_printer(pop_node);
        free_node(pop_node);
    }

    ll_iter_free(list_iter);
    ll_free(list);
    return 0;
}
