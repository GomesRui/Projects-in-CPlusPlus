#pragma once

#include "Main.h"

#define MAX_CARD 10

class Card
{

private:

	char host[NI_MAXHOST];
	char service[NI_MAXSERV];
	int card[MAX_CARD] = {};

public:

	Card(char host[], char service[]);
	Card();
	~Card();
	bool isCardNULL();
	void BuildCard();
	int* getCard();
	void setCard(int number);
	int getSizeCard();
};

