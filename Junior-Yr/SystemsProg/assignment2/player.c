#include "player.h"
#include <stdio.h>
#include <string.h>

/*
 * Instance Variables: user, computer
 * ----------------------------------
 *
 *  We only support 2 users: a human and a computer
 */
struct player user;
struct player computer;

int add_card(struct player *target, struct card *new_card) {
  // Allocate memory for the new hand node
  struct hand *new_node = (struct hand *)malloc(sizeof(struct hand));
  if (new_node == NULL) {
    return -1; // Memory allocation failed
  }

  // Assign the new card to the new node
  new_node->top = *new_card;

  // Link the new node to the current list
  new_node->next = target->card_list;

  // Update the player's hand to point to the new node
  target->card_list = new_node;

  // Increase the hand size
  target->hand_size++;

  return 0; // Success
}

int remove_card(struct player *target, struct card *old_card) {
  struct hand *previous = NULL;
  struct hand *current = target->card_list;

  // Traverse the list until we find the card or reach the end
  while (current != NULL) {
    if ((current->top.suit == old_card->suit) &&
        (strcmp(current->top.rank, old_card->rank) == 0)) {
      // Found the card to remove
      if (previous == NULL) {
        // Removing the first card in the list
        target->card_list = current->next;
      } else {
        // Bypass the current card
        previous->next = current->next;
      }
      free(current);       // Free the memory allocated for the removed card
      target->hand_size--; // Decrease hand size
      return 1;            // Card removed successfully
    }
    // Move to the next card in the list
    previous = current;
    current = current->next;
  }

  return 0; // Card not found
}
char check_add_book(struct player *target) {
  struct hand *current;
  struct hand *to_remove[4];
  char rank_to_remove;
  int found = 0;
  char rank_index[13] = {'2', '3', '4', '5', '6', '7', '8',
                         '9', '1', 'J', 'Q', 'K', 'A'};

  for (int i = 0; i < 13; i++) {
    int count = 0;
    current = target->card_list;
    while (current != NULL) {
      if (current->top.rank[0] == rank_index[i]) { // Compare ranks directly
        to_remove[count++] = current;
        if (count == 4) {
          rank_to_remove = rank_index[i]; // Store the rank to remove
          found = 1;
          break;
        }
      }
      current = current->next;
    }
    if (found) {
      break;
    }
  }

  if (!found) {
    return 0; // No book found
  }

  // Remove the cards from the player's hand
  for (int i = 0; i < 4; i++) {
    remove_card(target, &to_remove[i]->top);
  }

  // Add the rank to the player's book
  for (int i = 0; i < 7; i++) { // Max 7 books in deck
    if (target->book[i] == '0') {
      target->book[i] = rank_to_remove; // Store the rank directly
      break;
    }
  }

  printf("    - Player made a book of: %c\n", rank_to_remove);
  return rank_to_remove; // Return the rank of the book added
}

int search(struct player *target, char rank) {
  if (target->hand_size == 0) {
    return 0; // Hand size 0, can't match anything
  }

  struct hand *current = target->card_list;
  // Traverse the player's hand
  while (current != NULL) {
    if (current->top.rank[0] == rank) { // Compare characters directly
      return 1;                         // Rank found
    }
    current = current->next;
  }

  return 0; // Rank not found
}

int transfer_cards(struct player* source, struct player* target, char rank) {
  struct hand *current = source->card_list;
  struct hand *previous = NULL;
  int transferred = 0;

  while (current != NULL) {
    struct hand *next_card = current->next; // Save the next card before potentially removing current
    if (current->top.rank[0] == rank) {

      // Transfer card to target
      struct hand *new_card = malloc(sizeof(struct hand));
      new_card->top = current->top;
      new_card->next = target->card_list;
      target->card_list = new_card;
      target->hand_size++;
      
      // Remove card from source
      if (previous == NULL) {
        source->card_list = next_card;
      } else {
        previous->next = next_card;
      }
      free(current);
      source->hand_size--;
      transferred++;
    } else {
      previous = current;
    }
    current = next_card;
  }

  return transferred; // Return the number of transferred cards
}


int game_over(struct player *target) {
  if (target->book[6] == '0') {
    return 0;
  }
  return 1;
}

int reset_player(struct player *target) {
  // Step 1: Free memory allocated for cards in the player's hand
  struct hand *current = target->card_list;
  struct hand *temp;

  while (current != NULL) {
    temp = current;
    current = current->next;
    free(temp);

    // Reset the player's card list and hand size
    target->card_list = NULL;
    target->hand_size = 0;

    // Clear the player's book (max 7 books)
    for (int i = 0; i < 7; i++) {
      target->book[i] = '0';
    }

    return 0; // Return 0 to indicate success
  }
  return 1; // something bad happened
}
char computer_play(struct player *target) {
  char ranks[13][3] = {0}; // Array to store the ranks in player's hand
  int rank_count = 0;
  struct hand *current = target->card_list;

  // Collect ranks in the player's hand
  while (current != NULL) {
    int already_added = 0;
    for (int i = 0; i < rank_count; i++) {
      if (strcmp(ranks[i], current->top.rank) == 0) {
        already_added = 1;
        break;
      }
    }
    if (!already_added) {
      strcpy(ranks[rank_count++], current->top.rank);
    }
    current = current->next;
  }

  // Select a random rank from the collected ranks
  if (rank_count > 0) {
    int index = rand() % rank_count;
    return ranks[index][0]; // Return the selected rank
  }

  return '\0'; // Return null character if no ranks found
}

char user_play(struct player *target) {
  char rank[3]; // Buffer to store up to 2 characters and a null terminator
  while (1) {
    printf("Player 1's turn, enter a rank: ");

    // Read the input as a string, including possible multi-character ranks
    scanf("%2s", rank); // This limits input to 2 characters (e.g., "10")

    // Clear any leftover characters in the input buffer
    while (getchar() != '\n')
      ; // Discard until a newline is found

    // Only return if the player has a card of the entered rank
    if (search(target, rank[0]) == 1) {
      return rank[0]; // Return just the first character
    }

    printf("Error - must have at least one card from that rank to play\n");
  }
}
