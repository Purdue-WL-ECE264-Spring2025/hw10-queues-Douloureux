#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
  size_t value = serialize(state);
  struct list_node *pos = q->data.head;

  while (pos != NULL) {
    if (value == pos->value) {
      return;
    }
    pos = pos->next;
  }

  insert_at_head(&q->data, value);
}

struct game_state dequeue(struct queue *q) {
  size_t value = remove_from_tail(&q->data);
  return deserialize(value);
}

int is_solved(struct game_state status) {
  int check = 1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (status.tiles[i][j] == check)
        check++;
    }
  }

  return (check == 16);
}

int number_of_moves(struct game_state start) {
  struct queue q;
  q.data.head = NULL;
  enqueue(&q, start);

  while (q.data.head != NULL) {
    struct game_state curr = dequeue(&q);

    if (curr.empty_col != 3) {
      struct game_state move1 = curr;
      move_left(&move1);
      enqueue(&q, move1);
    }
    if (curr.empty_row != 3) {
      struct game_state move2 = curr;
      move_up(&move2);
      enqueue(&q, move2);
    }
    if (curr.empty_col != 0) {
      struct game_state move3 = curr;
      move_right(&move3);
      enqueue(&q, move3);
    }
    if (curr.empty_row != 0) {
      struct game_state move4 = curr;
      move_down(&move4);
      enqueue(&q, move4);
    }
    if (is_solved(curr)) {
      free_list(q.data);
      return curr.num_steps;
    }
  }

  free_list(q.data);
  return 37;
}
