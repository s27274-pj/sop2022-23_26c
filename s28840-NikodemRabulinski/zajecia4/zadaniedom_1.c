#include <stddef.h>
#include <stdio.h>

struct node {
  struct node *next;
  int value;
};

#define NODE(n, nxt, val)                                                      \
  do {                                                                         \
    n.next = nxt;                                                              \
    n.value = val;                                                             \
  } while (0)

#define foreach(curr, head) for (curr = head; curr; curr = curr->next)

size_t list_len(struct node *head) {
  size_t res;
  for (res = 0; head; res += 1, head = head->next)
    ;
  return res;
}

void list_insert(struct node **head, size_t idx, struct node *n) {
  if (!idx) {
    n->next = *head;
    *head = n;
  } else if ((*head)->next)
    list_insert(&(*head)->next, idx - 1, n);
  else
    (*head)->next = n;
}

void list_remove(struct node **head, size_t idx) {
  struct node *tmp;
  if (!idx) {
    tmp = (*head)->next;
    (*head)->next = NULL;
    *head = tmp;
  } else if (idx && (*head)->next)
    list_remove(&(*head)->next, idx - 1);
}

void list_print(struct node *head) {
  struct node *curr;

  printf("%d", head->value);
  foreach (curr, head->next)
    printf(" -> %d", curr->value);
  printf("\n");
}

int main() {
  struct node last, snd, fst, tmp, *head;

  NODE(last, NULL, 3);
  NODE(snd, &last, 2);
  NODE(fst, &snd, 1);

  head = &fst;

  printf("Length = %zu\n", list_len(head));

  list_print(head);

  NODE(tmp, NULL, 5);

  list_insert(&head, 0, &tmp);
  list_print(head);

  list_remove(&head, 0);
  list_print(head);

  list_insert(&head, 1, &tmp);
  list_print(head);

  list_remove(&head, 1);
  list_print(head);

  list_insert(&head, -1, &tmp);
  list_print(head);

  list_remove(&head, 3);
  list_print(head);

  list_insert(&head, 2, &tmp);
  list_print(head);

  return 0;
}
