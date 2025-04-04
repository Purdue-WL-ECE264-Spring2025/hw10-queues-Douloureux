#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
  size_t value = serialize(state);
  insert_at_head(&q->data, value);
}

struct game_state dequeue(struct queue *q) {
  size_t value = remove_from_tail(&q->data);
  return deserialize(value);
}

int number_of_moves(struct game_state start) { return 0; }
