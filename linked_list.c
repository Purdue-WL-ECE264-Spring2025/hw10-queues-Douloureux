#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) {
  struct list_node *new = malloc(sizeof(struct list_node));
  new->value = value;
  new->next = NULL;

  return new;
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node *old_head = list->head;

  if (old_head == NULL) {
    list->head = new_node(value);
  } else {
    struct list_node *new_head = new_node(value);
    new_head->next = old_head;
    list->head = new_head;
  }
}

void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node *old_head = list->head;

  if (old_head == NULL) {
    old_head = new_node(value);
  } else {
    struct list_node *new_head = new_node(value);
    struct list_node *pos = old_head;

    while (pos->next != NULL) {
      pos = pos->next;
    }

    pos->next = new_head;
  }
}

size_t remove_from_head(struct linked_list *list) {
  struct list_node *old_head = list->head;
  size_t value = 0;

  if (old_head == NULL) {
    return value;
  } else {
    if (old_head->next == NULL) {
      value = old_head->value;
      free(old_head);
      list->head = NULL;
      return value;
    } else {
      struct list_node *new_head = list->head->next;
      value = old_head->value;
      free(old_head);
      list->head = new_head;
      return value;
    }
  }
}

size_t remove_from_tail(struct linked_list *list) {
  struct list_node *old_pos = list->head;
  size_t value = 0;

  if (old_pos == NULL)
    return value;
  else {
    if (old_pos->next == NULL) {
      value = old_pos->value;
      free(old_pos);
      list->head = NULL;
      return value;
    } else {
      old_pos = list->head;
      while (old_pos->next->next != NULL) {
        old_pos = old_pos->next;
      }

      struct list_node *new_tail = old_pos;
      value = new_tail->next->value;
      free(new_tail->next);
      new_tail->next = NULL;
      return value;
    }
  }
}

void free_list(struct linked_list list) {
  struct list_node *pos = list.head;
  struct list_node *temp;

  if (pos == NULL) {
    free(list.head);
  } else {
    while (pos->next != NULL) {
      temp = pos;
      pos = pos->next;
      free(temp);
    }
    free(pos);
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
