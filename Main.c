#include "Header.h"

/*
Name: Nathan Wisner
PA: 7 Poker
Class: CPTS 121
TA: Edgar Parez
Professor: Andy O' Fallon
Date: 11/16/2017 (Finished date)
*/
int main(void)
{
	Hand user;
	Hand Dealer;
	Hand otherDeck;

	/* initialize suit array */
	const char *suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char *face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };

	/* initalize deck array */
	int deck[4][13] = { 0 };

	srand((unsigned)time(NULL)); /* seed random-number generator */

	for (int i = 0; i < 11; i++)
	{
		Turn(deck, face, suit, &user, &otherDeck, &Dealer);
		PlayerTurn(deck, face, suit, &user, &otherDeck, &Dealer);
		system("cls");
	}

	return 0;
}