/*
MIT License

Copyright (c) 2023 Adwaith Rajesh

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef LIBS_INCLUDE_LINKED_LIST_H
#define LIBS_INCLUDE_LINKED_LIST_H

#include <stdarg.h>
#include <stdio.h>

#ifndef LIBS_LINKED_LIST_NO_SHORT_NAMES

#define ll_init LinkedList_init
#define ll_print LinkedList_print
#define ll_is_empty LinkedList_is_empty
#define ll_append LinkedList_append
#define ll_pop LinkedList_pop
#define ll_append_left LinkedList_append_left
#define ll_pop_left LinkedList_pop_left
#define ll_map LinkedList_map
#define ll_empty LinkedList_empty
#define ll_free LinkedList_free

#ifndef LIBS_LINKED_LIST_NO_ITER
#define ll_iter_init LinkedList_iter_init
#define ll_iter_free LinkedList_iter_free
#define ll_iter_next LinkedList_iter_next
#endif  // not iter

#endif  // LIBS_LINKED_LIST_NO_SHORT_NAMES

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    size_t size;
} LinkedList;

#ifndef LIBS_LINKED_LIST_NO_ITER
typedef struct {
    Node *curr;
} LLIter;
#endif

typedef void NodePrinterFn(Node *);
typedef void *LinkedListMapFn(Node *, va_list);

Node *create_node(void *);
void free_node(Node *);

LinkedList *LinkedList_init();
void LinkedList_print(LinkedList *, NodePrinterFn *);
int LinkedList_is_empty(LinkedList *);
void LinkedList_append(LinkedList *, Node *);
Node *LinkedList_pop(LinkedList *);
void LinkedList_append_left(LinkedList *, Node *);
Node *LinkedList_pop_left(LinkedList *);
void LinkedList_map(LinkedList *, LinkedListMapFn *, ...);
void LinkedList_empty(LinkedList *);
void LinkedList_free(LinkedList *);

#ifndef LIBS_LINKED_LIST_NO_ITER
LLIter *LinkedList_iter_init(LinkedList *);
void LinkedList_iter_free(LLIter *);
Node *LinkedList_iter_next(LLIter *);
#endif

// end of head file
#endif

#ifdef LIBS_LINKED_LIST_IMPLEMENTATION

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static void *_malloc_check(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Could not allocate memory\n");
        exit(1);
    }
    return ptr;
}

Node *create_node(void *data) {
    Node *new_node = (Node *)_malloc_check(malloc(sizeof(Node)));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_node(Node *node) {
    if (node == NULL) return;
    free(node);
}

LinkedList *LinkedList_init() {
    LinkedList *new_list = (LinkedList *)_malloc_check(malloc(sizeof(LinkedList)));

    new_list->head = NULL;
    new_list->size = 0;
    return new_list;
}

void LinkedList_print(LinkedList *list, NodePrinterFn *node_printer) {
    Node *temp = list->head;
    while (temp != NULL) {
        node_printer(temp);
        temp = temp->next;
    }
}

int LinkedList_is_empty(LinkedList *list) {
    return list->size == 0;
}

void LinkedList_append(LinkedList *list, Node *node) {
    if (list->head == NULL) {
        list->head = node;
        list->size++;
        return;
    }

    Node *temp = list->head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = node;
    list->size++;
}

Node *LinkedList_pop(LinkedList *list) {
    if (list->size == 1) {
        Node *temp = list->head;
        list->head = NULL;
        list->size--;
        return temp;
    }
    Node *prev;
    Node *curr = list->head;

    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }

    prev->next = NULL;
    list->size--;
    return curr;
}

void LinkedList_append_left(LinkedList *list, Node *node) {
    if (list->head == NULL) {
        list->head = node;
        list->size++;
        return;
    }
    node->next = list->head;
    list->head = node;
    list->size++;
}

Node *LinkedList_pop_left(LinkedList *list) {
    if (list->head == NULL) return NULL;
    Node *temp = list->head;
    list->head = list->head->next;
    list->size--;
    return temp;
}

void LinkedList_empty(LinkedList *list) {
    Node *temp;
    while (list->head != NULL) {
        temp = list->head;
        list->head = list->head->next;
        free_node(temp);
    }
    list->head = NULL;
    list->size = 0;
}

void LinkedList_free(LinkedList *list) {
    Node *temp;
    while (list->head != NULL) {
        temp = list->head;
        list->head = list->head->next;
        free_node(temp);
    }
    free(list);
}

#ifndef LIBS_LINKED_LIST_NO_ITER

LLIter *LinkedList_iter_init(LinkedList *list) {
    LLIter *new_iter = (LLIter *)_malloc_check(malloc(sizeof(LLIter)));
    new_iter->curr = list->head;
    return new_iter;
}

Node *LinkedList_iter_next(LLIter *iterator) {
    if (iterator->curr == NULL) return NULL;
    Node *curr_val = iterator->curr;
    iterator->curr = iterator->curr->next;
    return curr_val;
}

void LinkedList_iter_free(LLIter *iterator) {
    if (iterator == NULL) return;
    free(iterator);
}

void LinkedList_map(LinkedList *list, LinkedListMapFn *fn, ...) {
    Node *temp = list->head;
    va_list args;
    va_start(args, fn);
    while (temp != NULL) {
        temp->data = fn(temp, args);
        temp = temp->next;
    }
    va_end(args);
}
#endif  // no iter

#endif  // LINS_LINKED_LIST_IMPLEMENTATION
