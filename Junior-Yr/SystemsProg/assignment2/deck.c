#include "deck.h"
#include "card.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Variable: deck_instance
 * -----------------------
 *
 * Go Fish uses a single deck
 */
struct deck deck_instance;

int shuffle() {
  deck_instance.top_card = 51; // make full deck

  char suit[4] = {'H', 'D', 'C', 'S'};
  char rank[13][2] = {
      "2", "3", "4", "5", "6", "7", "8",
      "9", "1", "J", "Q", "K", "A"}; // fill deck with cards,
                                     // 10 = 1 to save memory space

  int index = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 13; j++) {
      deck_instance.list[index].suit = suit[i];
      strcpy(deck_instance.list[index].rank, rank[j]);

      index++;
    }
  }
  // fisher and yates alg
  for (int i = deck_instance.top_card; i > 0; i--) {
    int j = rand() % (1 + i); // generate number between 0 and i

    struct card temp = deck_instance.list[i]; // swap card's places
    deck_instance.list[i] = deck_instance.list[j];
    deck_instance.list[j] = temp;
  }
  return 0; // return 0 on success
}

int deal_player_cards(struct player *target) {
  if (deck_instance.top_card < 7) {
    return -1; // Error if not enough cards to deal
  }

  // Ensure target->card_list is initialized
  if (target->card_list == NULL) {
    target->card_list = (struct hand *)malloc(
        sizeof(struct hand));       // Allocate memory for the first hand
    target->card_list->next = NULL; // Initialize next pointer to NULL
  }

  // Deal the first card
  target->card_list->top = *next_card();

  // Set the current hand to the first card
  struct hand *current = target->card_list; // Use a pointer for the linked list
  for (int i = 1; i < 7; i++) { // Already dealt 1 card, so start from 1
    // Create a new hand for the next card if not already created
    if (current->next == NULL) {
      current->next = (struct hand *)malloc(
          sizeof(struct hand));   // Allocate memory for the new hand
      current->next->next = NULL; // Initialize the next pointer to NULL
    }

    // Deal the next card
    current = current->next;     // Move to the next hand
    current->top = *next_card(); // Set the top card
  }
  target->hand_size = 7; // Set the hand size
  return 0;              // Success return
}

struct card *next_card() {
  if (deck_instance.top_card < 0) {
    return NULL; // no card next
  }
  return &deck_instance.list[deck_instance.top_card--]; // return and point to
                                                        // next top card
}

size_t deck_size() { return deck_instance.top_card + 1; }

void print_card(struct card card) {
  // Check if the rank is '1' and print '10' instead
  if (strcmp(card.rank, "1") == 0) {
    printf("10%c ", card.suit);
  } else {
    printf("%s%c ", card.rank, card.suit);
  }
}

void print_hand(struct hand *hand) {
  struct hand *current = hand;

  while (current != NULL) {
    print_card(current->top);

    current = current->next;
  }
  printf("\n");
}

void print_book(struct player *target) {
  for (int i = 0; i < 7; i++) {
    if (target->book[i] != '0') { // Print only valid ranks
      printf("%c ", target->book[i]);
    }
  }
  printf("\n");
}


int draw_card(struct player *target) {
  if (deck_instance.top_card < 1) {
    return 1; // error: no cards in deck
  } // insert card into list and link
  add_card(target, next_card());
  return 0;
}



