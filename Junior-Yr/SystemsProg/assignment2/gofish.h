#ifndef GOFISH_H
#define GOFISH_H

#include "card.h"
#include "deck.h"

/*
function: print_gamestate
-----------
prints the board at a gamestate

returns: nothing
*/
void print_gamestate();

/*
function: players_turn
-----------
runs the logic for a whole players turn

returns: nothing
*/
void players_turn();


/*
function: computers_turn
----------
runs the logic for a whole computer turn

returns: nothing
*/
void computers_turn();

#endif
