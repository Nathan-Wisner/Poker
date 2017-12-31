#include "Header.h"

/* shuffle cards in deck */
void shuffle(int wDeck[][13])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}
}

/* deal cards in deck */
void deal(const int wDeck[][13], const char *wFace[], const char *wSuit[], Hand *player)
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

					/* deal each of the 52 cards */
	for (card = 1; card <= 5; card++)
	{
		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++)
			{
				/* if slot contains current card, display card */
				if (wDeck[row][column] == card)
				{
					player->Hand[column]++;
					printf("%5s of %-8s%c", wFace[column], wSuit[row], card % 2 == 0 ? '\n' : '\t');
				}

			}
		}
	}
}

void SetHands(const int wDeck[][13], const char *wFace[], const char *wSuit[], Hand *player, int hand) // Sets the hand to a specific value not determined by the user
{
	for (int Column = 0; Column < 13; Column++)
	{
		for (int Row = 0; Row < 4; Row++)
		{
			if (wDeck[Row][Column] == hand)
			{
				player->Hand[Column]++;
				player->suit[Row]++;
				hand++;
			}
		}
	}
}

int CheckCards(const int wDeck[][13], const char *wFace[], const char *wSuit[], Hand *player) //Checks the cards for the best commbination
{
	int highest = 0;

	for (int i = 0; i < 13; i++)
	{
		if (player->Hand[i] == 5)
		{
			printf(" You have a straight of %s's ", wFace[i]);
			highest += 5;
		}

		else if(player->suit[i] == 5)
		{
			printf(" You have a flush of %s's ", wFace[i]);
			highest += 5;
		}

		else if (wSuit[i] == 5)
		{
			printf(" You have a flush of %s's! ", wSuit[i]);
			highest += 5;
		}

		else if (player->Hand[i] == 4)
		{
			printf(" You have a four of a kind of %s 's \n", wFace[i]);
			highest += 4;
		}
		else if (player->Hand[i] == 3)
		{
			printf(" You have a three of a kind of %s's \n", wFace[i]);
			highest += 3;
		}

		else if (player->Hand[i] == 2)
		{
			printf(" You have a pair of %s's \n", wFace[i]);
			highest += 2;
		}

	}
	return highest;
}

void ClearDeck(Hand *player) //Resets the deck back to 0
{
	for (int i = 0; i < 13; i++)
	{
		player->Hand[i] = 0;
	}

	for (int j = 0; j < 4; j++)
	{
		player->suit[j] = 0;
	}
}

void setDeck(Hand *source, Hand *destination) // Sets the deck for the suit and hand
{
	for (int i = 0; i < 13; i++)
	{
		destination->Hand[i] = source->Hand[i];
	}

	for (int j = 0; j < 4; j++)
	{
		destination->suit[j] = source->suit[j];
	}
}

void determineDecks(const int wDeck[][13], const char *wFace[], const char *wSuit[], Hand *firstDeck, Hand *secondDeck) //Determines the better of two decks
{
	if (CheckCards(wDeck, wFace, wSuit, firstDeck) < CheckCards(wDeck, wFace, wSuit, secondDeck))
	{
		setDeck(secondDeck, firstDeck);
		ClearDeck(firstDeck);
		printf(" Switched \n");
	}

	else
	{
		printf("Not swapped \n");
		ClearDeck(secondDeck);
	}

}

int SetCard(const int wDeck[][13], const char *wFace[], const char *wSuit[], Hand *player, int hand) //Sets cards for a deck
{
	for (int Column = 0; Column < 13; Column++)
	{
		for (int Row = 0; Row < 4; Row++)
		{
			if (wDeck[Row][Column] == hand)
			{
				player->Hand[Column]++;
				player->suit[Row]++;
			}
		}
	}
}

void GetChoice(const int deck[][13], const char *face[], const char *suit[], Hand *user, Hand *otherDeck, Hand *Dealer)	//Retreives the choice from the player about changing cards
{
	int choice,many;

	printf(" How many cards would you like to exchange for a new one? \n");
	scanf("%d", &many);

	if (many > 3)
	{
		printf("You cannot choose more than 3 cards! \n");
		GetChoice(deck, face, suit, user, otherDeck, Dealer);
	}

	else
		{
			for (int i = 0; i < many; i++)
			{
				printf(" What card would you like to exchange for a new one? (Aces are 1, Jacks are 11, Queens are 12 and Kings are 13) \n");
				scanf("%d", &choice);
				if (user->Hand[choice - 1] == 0)
				{
					printf("You do not have a card there! \n");
					GetChoice(deck, face, suit, user, otherDeck, Dealer);
				}

				user->Hand[choice - 1]--;
				SetCard(deck, face, suit, user, 31 + rand() % 20);

			}
		}
}

void Turn(const int deck[][13], const char *face[], const char *suit[], Hand *user, Hand *otherDeck, Hand *Dealer) // Executes the part of the turn the player doesnt see
{
	ResetDeck(deck);
	shuffle(deck);
	ClearDeck(user);
	deal(deck, face, suit, user);
	SetHands(deck, face, suit, Dealer, 6);

	for (int i = 2; i < 7; i++)
	{
		SetHands(deck, face, suit, otherDeck, i*5);
		determineDecks(deck, face, suit, Dealer, otherDeck);
		for (int i = 0; i < 13; i++)
		{
			if (Dealer->Hand[i] != 0)
			{
				Dealer->Hand[i]--;
				SetCard(deck, face, suit, Dealer, 31 + rand() % 20);
			}
		}
		system("cls");
	}
}

void PlayerTurn(const int deck[][13], const char *face[], const char *suit[], Hand *user, Hand *otherDeck, Hand *Dealer)	//Executes the part of the turn the player will see
{
	printf(" Aces :  %d \n", user->Hand[0]);

	for (int i = 1; i < 10; i++)
	{
		printf(" %d ' s : %d \n", i + 1, user->Hand[i]);
	}

	printf(" Jacks:  %d \n", user->Hand[10]);
	printf(" Queens: %d \n", user->Hand[11]);
	printf(" Kings:  %d \n", user->Hand[12]);

	GetChoice(deck, face, suit, user, otherDeck, Dealer);

		if (CheckCards(deck, face, suit, user) > CheckCards(deck, face, suit, Dealer))
		{
			printf("The user has won! \n");
			ClearDeck(Dealer);
			ClearDeck(user);
			ClearDeck(otherDeck);
			_sleep(1500);
		}

		else if (CheckCards(deck, face, suit, user) < CheckCards(deck, face, suit, Dealer))
		{
			printf("The Dealer has won! \n");
			ClearDeck(Dealer);
			ClearDeck(user);
			ClearDeck(otherDeck);
			_sleep(1500);
		}

		else if (CheckCards(deck, face, suit, user) == CheckCards(deck, face, suit, Dealer))
		{
			printf("Its a tie! \n");
			ClearDeck(Dealer);
			ClearDeck(user);
			ClearDeck(otherDeck);
			_sleep(1500);
		}
	
}

void ResetDeck(int deck[][13])		//Resets the deck
{
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			deck[j][i] = 0;
		}
	}
}