#include "Card.h"

Card::Card(char host[], char service[])
{
	strcpy_s(this->host, host);
	strcpy_s(this->service, service);
}

Card::~Card()
{
}

Card::Card()
{
}

int* Card::getCard()
{
	return this->card;
}

//Update internal card with draw number
void Card::setCard(int number)
{
	for (int i = 0; i < MAX_CARD; i++)
	{
		if (this->card[i] == number)
		{
			this->card[i] = 0;
			break;
		}

	}
}

int Card::getSizeCard()
{
	return MAX_CARD;
}

void Card::BuildCard()
{
	int randomNr = 0;
	int* it;

	// Populate card with random numbers

	std::cout << "CARD OUT: ";

	for (int i = 0; i < MAX_CARD; i++)
	{
		randomNr = (rand() % 50 + 1);
		it = std::find(std::begin(this->card), std::end(this->card), randomNr);

		if (it == std::end(this->card))
		{
			this->card[i] = randomNr;
			std::cout << "[" << this->card[i] << "]";
		}
		else
		{
			i--;
		}

	}
	std::cout << std::endl;
}

//Check if the card is new / has numbers
bool Card::isCardNULL()
{
	for (int i = 0; i < MAX_CARD; i++)
	{
		if (this->card[i] != 0)
			return false;
	}

	return true;
}
