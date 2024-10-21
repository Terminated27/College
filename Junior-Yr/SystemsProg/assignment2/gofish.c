#include "gofish.h"
#include "deck.h"
#include "player.h"
#include <ctype.h>
#include <stdio.h>

void print_gamestate() {
  fprintf(stdout, "\nPlayer 1's Hand - ");
  print_hand(user.card_list);
  print_hand(computer.card_list);
  printf("Player 1's book - ");
  print_book(&user);
  printf("Player 2's book - ");
  print_book(&computer);
}

void computers_turn() {
  char rank;
  int transferred = 0;
  print_gamestate();

  while (1) {
    rank = computer_play(&computer);
    transferred = transfer_cards(&user, &computer, rank);
    printf("Player 2's turn, computer entered : %c\n", rank);
    if (transferred != 0) {
      if (rank == '1') {
        printf("    - Player 1 has %d 10's\n", transferred);
      } else {
        printf("    - Player 1 has %d %c's\n", transferred, rank);
      }
      check_add_book(&computer); // Check if the user can form a book
      printf("    - Player 2 gets another turn\n\n");
    } else {
      if (rank == '1') {
        printf("    - Player 1 has no 10's\n");
      } else {
        printf("    - Player 1 has no %c's\n", rank);
      }
      draw_card(&computer); // User draws a card when no match
      check_add_book(&computer);
      return;
    }
  }
}

void players_turn() {
  char rank;
  int transferred = 0;
  print_gamestate();

  while (1) {
    rank = user_play(&user);
    transferred = transfer_cards(&computer, &user, rank);

    if (transferred != 0) {
      if (rank == '1') {
        printf("    - Player 2 has %d 10's\n", transferred);
      } else {
        printf("    - Player 2 has %d %c's\n", transferred, rank);
      }
      check_add_book(&user); // Check if the user can form a book
      printf("    - Player 1 gets another turn\n\n");
    } else {
      if (rank == '1') {
        printf("    - Player 2 has no 10's\n");
      } else {
        printf("    - Player 2 has no %c's\n", rank);
      }
      draw_card(&user); // User draws a card when no match
      check_add_book(&user);
      return;
    }
  }
}

int main(int args, char *argv[]) {
  int game = 0;
  char play_again = 'Y';
  while (toupper(play_again) == 'Y') {
    // Initialize everything
    fprintf(stdout, "\nShuffling deck...\n");
    shuffle();
    deal_player_cards(&user);
    deal_player_cards(&computer);
    for (int i = 0; i < 7; i++) {
      user.book[i] = '0';
    }
    for (int i = 0; i < 7; i++) {
      computer.book[i] = '0';
    }

    game = 0;
    while (game == 0) { // Run game logic
      players_turn();
      if ((game = game_over(&user)) == 1) {
        printf("Player 1 wins! yay you won :)\n");
        break;
      }
      computers_turn();
      if ((game = game_over(&computer)) == 1) {
        printf("Player 2 wins! sorry you lose :(\n");
        break;
      }
    }
    do {
      printf("Do you want to play again? [Y/N]: ");
      scanf(" %c", &play_again);
      play_again = toupper(play_again); // Convert to uppercase
    } while (play_again != 'Y' && play_again != 'N'); // Ensure valid input
  }

  return 0;
}
