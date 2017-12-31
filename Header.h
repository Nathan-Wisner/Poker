#ifndef HEADER_H
#define HEADER_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Hand {
	int Hand[13];
	int suit[4];
} Hand;

void shuffle(int wDeck[][13]);
void deal(const int wDeck[][13], const char *wFace[], const char *wSuit[], Hand *player);
void SetHands(const int wDeck[][13], const char *wFace[], const char *wSuit[], Hand *player, int hand);
void ClearDeck(Hand *player);
int CheckCards(const int wDeck[][13], const char *wFace[], const char *wSuit[], Hand *player);
void setDeck(Hand *source, Hand *destination);
void determineDecks(const int wDeck[][13], const char *wFace[], const char *wSuit[], Hand *firstDeck, Hand *secondDeck);
void Turn(const int deck[][13], const char *face[], const char *suit[], Hand *user, Hand *otherDeck, Hand *Dealer);
int SetCard(const int wDeck[][13], const char *wFace[], const char *wSuit[], Hand *player, int hand);
void PlayerTurn(const int deck[][13], const char *face[], const char *suit[], Hand *user, Hand *otherDeck, Hand *Dealer);
void ResetDeck(int deck[][13]);

#endif HEADER_H