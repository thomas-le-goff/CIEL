#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdlib.h>

typedef int ll_data_t;
struct list;

// creer une nouvelle liste (vide)
struct list *list_create(void);

// compte le nombre de noeuds de la liste
size_t list_count(const struct list *list);

// insere un noeud a la fin de la liste
void list_push(struct list *list, ll_data_t item_data);

// supprime le noeud de fin de la liste
ll_data_t list_pop(struct list *list);

// insere un noeud en debut de liste
void list_unshift(struct list *list, ll_data_t item_data);

// supprime le noeud de debut de la liste
ll_data_t list_shift(struct list *list);

// supprime le premier noeud qui contient la donnee data
void list_delete(struct list *list, ll_data_t data);

// supprime toute la liste
// list sera un pointeur flottant apres cette operation
void list_destroy(struct list *list);

#endif
