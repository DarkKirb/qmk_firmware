#include "compose.h"
#include <stdint.h>
#include "action.h"
#include "keycode.h"
#include "neo2.h"
#include "print.h"
#include "quantum_keycodes.h"
#include "unicode/unicode.h"

static int charsWritten, currentState;

static void resetState(void) {
  print("resetState()\n");
  charsWritten = 0;
  currentState = 0;
}

static void finishCompose(const char* result) {
  uprintf("Finishing compose with result: %s (%d chars written)\n", result, charsWritten);
  while(charsWritten) {
    tap_code(KC_BACKSPACE);
    charsWritten--;
  }
  send_unicode_string(result);
  resetState();
}

typedef struct {
  uint16_t first_edge_idx;
  uint16_t edge_count;
} compose_node_t;

typedef struct {
  const char * value;
  uint16_t c;
  uint16_t next_node;
} compose_edge_t;

#include "composeTable.h"

static void checkComposeState(void) {
  print("checkComposeState()\n");
  if(currentState * sizeof(compose_node_t) > sizeof(nodes)) {
    finishCompose("[error in compose]");
  }
}

static const compose_edge_t *findEdge(uint16_t keycode) {
  checkComposeState();
  uint32_t uc = keystroke_to_unicode(keycode);
  uprintf("Resolved keycode %d: %ld\n", keycode, uc);

  uint16_t match1 = (uint16_t)uc; // yes only bmp support, keyboard doesn’t have any astral keycodes anyways
  uint16_t match2 = 0;
  if(keycode < 256) {
    match2 = 0xD800 + keycode;
    print("(low keycode)\n");
  } else if(keycode == KC_LEAD) {
    match2 = 0xD800;
    print("(leader key)\n");
  }
  
  for(int i = nodes[currentState].first_edge_idx; i < nodes[currentState].first_edge_idx + nodes[currentState].edge_count; i++) {
    if(compose_edges[i].c == match1 || compose_edges[i].c == match2) {
      uprintf("found matching node: %d -> %d\n", currentState, i);
      return &compose_edges[i];
    }
  }
  print("no matching edge found.\n");
  return NULL;
}

// yes this breaks with emoji
static size_t charcount_utf8(const char * s) {
  size_t n = 0;
  while(*s)
    if((*(s++) & 0xC0) != 0x80)
      n++; // only count non-continuation characters
  return n;
}

static void transEdge(const compose_edge_t *edge) {
  uprintf("Transitioning to node %d\n", edge->next_node);
  if(edge->value) {
    uprintf("new node has value %s\n", edge->value);
    finishCompose(edge->value);
    if(edge->next_node != 0) // not necessarily the final product
      charsWritten = charcount_utf8(edge->value);
  }
  currentState = edge->next_node;
  checkComposeState();
}

static bool isCombining(uint32_t uc) {
  // yes it is not all of them, but all of them that matter for us
  if(uc >= 0x300 && uc < 0x370)
    return true;
  if(uc == 0x20d7)
    return true;
  return false;
}

void process_compose(uint16_t keycode, keyrecord_t *record) {
  if(!record->event.pressed)
    return;
  uint32_t uc = keystroke_to_unicode(keycode);
  const compose_edge_t * edge = findEdge(keycode);
  if(edge == NULL && uc != 0) { // no matching edge found, reset and try again
    print("No matching edge found, reset.\n");
    resetState();
    edge = findEdge(keycode);
  }
  if(edge == NULL) {
    print("No compose edge found.\n");
    return; // nothing found
  }
  // before we can advance the compose state, we need to prepare certain keys (dead keys, the leader key) because otherwise our deletion will delete too much (which of course is something we do not want)
  if(isCombining(uc)) {
    print("keycode refers to deadkey, writing space\n");
    tap_code(KC_SPACE);
  } else if(keycode == KC_LEAD) {
    print("keycode refers to leader key, writing compose symbol\n");
    send_unicode_string("♫");
  }
  charsWritten++;
  transEdge(edge);
}