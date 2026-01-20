#include "linked_list.h"

struct list_node
{
   struct list_node *prev, *next;
   ll_data_t data;
};

struct list
{
   struct list_node *first, *last;
};

struct list *list_create(void)
{
   struct list *list;

   list = malloc(sizeof(*list));
   list->first = NULL;
   list->last = NULL;

   return list;
}

void list_destroy(struct list *list)
{
   struct list_node *c = list->first;
   while (c != NULL)
   {
      struct list_node *n = c->next;
      free(c);
      c = n;
   }

   free(list);
}

void list_push(struct list *list, ll_data_t item_data)
{
   struct list_node *nn;
   nn = malloc(sizeof(*nn));

   nn->data = item_data;
   nn->next = NULL;
   nn->prev = list->last;

   list->last = nn;

   if (nn->prev != NULL)
   {
      nn->prev->next = nn;
   }

   if (list->first == NULL)
   {
      list->first = nn;
   }
}

ll_data_t list_pop(struct list *list)
{
   struct list_node *c = list->last;

   if (c == NULL)
   {
      return 0;
   }

   ll_data_t data = c->data;

   list->last = c->prev;

   // in case of single element list
   if (c->prev != NULL)
   {
      c->prev->next = NULL;
   }
   else
   {
      list->first = NULL;
   }

   free(c);

   return data;
}

void list_unshift(struct list *list, ll_data_t item_data)
{
   struct list_node *nn;
   nn = malloc(sizeof(*nn));

   nn->data = item_data;
   nn->next = list->first;
   nn->prev = NULL;

   list->first = nn;

   if (nn->next != NULL)
   {
      nn->next->prev = nn;
   }

   if (list->last == NULL)
   {
      list->last = nn;
   }
}

ll_data_t list_shift(struct list *list)
{
   struct list_node *c = list->first;

   if (c == NULL)
   {
      return 0;
   }

   ll_data_t data = c->data;

   list->first = c->next;

   // in case of single element list
   if (c->next != NULL)
   {
      c->next->prev = NULL;
   }
   else
   {
      list->last = NULL;
   }

   free(c);

   return data;
}

void list_delete(struct list *list, ll_data_t data)
{
   struct list_node *c = list->first;

   while (c != NULL && c->data != data)
   {
      c = c->next;
   }

   if (c != NULL && c->prev != NULL)
   {
      c->prev->next = c->next;
   }

   if (c != NULL && c->next != NULL)
   {
      c->next->prev = c->prev;
   }

   if (c != NULL && c == list->first)
   {
      list->first = c->next;
   }

   if (c != NULL && c == list->last)
   {
      list->last = c->prev;
   }

   free(c);
}

size_t list_count(const struct list *list)
{
   struct list_node *n = list->first;

   int count = 0;

   while (n != NULL)
   {
      n = n->next;
      count++;
   }

   return count;
}