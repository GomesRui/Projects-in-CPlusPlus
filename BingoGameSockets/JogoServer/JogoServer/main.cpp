#include "Main.h"

#define MAX_CARD 10
#define PORT 54000

int GetData(SOCKET clientSocket, char *buf, int size)
{
	int bytesReceived = 0;

	while (true)
	{
		bytesReceived = recv(clientSocket, buf, size, 0);
		
		if (bytesReceived <= 0) //Input data will be stored in the buffer coming from the Client
		{
			std::cerr << "Waiting for data...";
			return -1;
		}

		if (bytesReceived == SOCKET_ERROR) //Error handling
		{
			std::cerr << "Error in recv()!" << std::endl;
			return -1;
		}
		else
		{
			return bytesReceived;
		}

	}
}

int SendData(SOCKET clientSocket, char *message, int size)
{
	int bytesSent = 0;

	bytesSent = send(clientSocket, message, size, 0);
	if (bytesSent <= 0)
	{
		std::cerr << "Error sending data to client!";
		return -1;
	}

	if (bytesSent == SOCKET_ERROR) //Error handling
	{
		std::cerr << "Error in send()!" << std::endl;
			return -1;
	}
	else
	{
			return bytesSent;
	}

}

void DrawNumber(char *numberCharArr, int size, Card *card)
{	
	int number = (rand() % 50 + 1);	
	std::string numberString = std::to_string(number);
	
	numberString.copy(numberCharArr, numberString.length() + 1);
	numberCharArr[size - 1] = '\0';

	card->setCard(number);

}

bool Jogo(SOCKET clientSocket, Card *mappedCard)
{
	char inputData[BUF_SIZE_SENT] = { '\0' };
	char outputData[BUF_SIZE_RECEIVE] = { '\0' };
	
	std::string message;
	char numberDraw [3] = { '\0' };

	//Populate card
	if (mappedCard->isCardNULL()) //Check if the card is new / has numbers
		mappedCard->BuildCard();

	int* card = mappedCard->getCard(); // geting int array from the mappedCard object

	// Convert int to char[]
	for (int i = 0; i < mappedCard->getSizeCard(); i++)
	{
		message += std::to_string(card[i]);
		message += ",";
	}
	message.copy(inputData, message.length() + 1);

	//Send array to user
	SendData(clientSocket, inputData, strlen(inputData));

	//Get confirmation from client
	GetData(clientSocket, outputData, sizeof(outputData));

	if (strstr(outputData, "Received"))
	{

		//Create 1 random number every second until receives message from client with "Won"
		std::cout << "Numbers draw: ";
		do
		{
			//clearing buffer variables.
			ZeroMemory(outputData, sizeof(outputData));
			ZeroMemory(numberDraw, sizeof(numberDraw));

			//Get the draw number and ask the client to check if it has in its card
			DrawNumber(numberDraw, sizeof(numberDraw), mappedCard);
			std::cout << numberDraw << " > ";
			if (SendData(clientSocket, numberDraw, sizeof(numberDraw)) <= 0)
			{
				return false;
			}

			if (GetData(clientSocket, outputData, sizeof(outputData)) <= 0)
			{
				return false;
			}

			Sleep(1000); //every 1 second

		} while (strstr(outputData, "Next"));

		return true;
	}
}

int main()
{
	std::map<std::string, Card> mapOfCards; //Map container to link cards with usernames

	// Create winsock
	
	srand(time(0));
	WSADATA data_ws;
	WORD version = MAKEWORD(2, 2);

	int OK_ws = WSAStartup(version, &data_ws);

	if (OK_ws != 0)
	{
		std::cerr << "Error initializing winsock!" << std::endl;
		WSACleanup();
		return -1;
	}

	std::cout << "Server Online..." << std::endl;

	// Create socket

	restartCS:
	SOCKET listener = socket(AF_INET, SOCK_STREAM, 0); //IPv4, TCP, IP

	if (listener == INVALID_SOCKET) //Error handling
	{
		std::cerr << "Error creating the socket!" << std::endl;
		WSACleanup();
		return -1;
	}

	// Binding the IP:port to socket listerner

	sockaddr_in hint;
	hint.sin_family = AF_INET; //IPv4
	hint.sin_port = htons(PORT); //port: 54000
	hint.sin_addr.S_un.S_addr = INADDR_ANY; //localhost

	bind(listener, (sockaddr*)& hint, sizeof(hint)); //bind the ip address and port 
													//to the listener socket

	// Listener in listening

	if (listen(listener, 1) == ECONNREFUSED){ 	//passive mode with socket waiting on a client 
												//to make a connection. It only allows 1 connection at a time
		std::cerr << "Maximum connections allowed reached" << std::endl;
	}
		
	// Wait the connection

	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listener, (sockaddr*)&client, &clientSize); //extracts the connection
																			// request for the listening socket
																			// client-server connection estabilished with clientSocket.

	if (clientSocket == INVALID_SOCKET) //Error handling
	{
		std::cerr << "Invalid client socket!" << std::endl;
		closesocket(clientSocket);
		WSACleanup();
		return -1; //repeat process 3 times.
	}

	// Verifying connectivity

	char host[NI_MAXHOST]; //client's hostname
	char service[NI_MAXSERV]; //client's service 

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) != 0)
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
	}

	//Checking username and linking with card

	char buf[BUF_SIZE_RECEIVE];
	int bytesReceived = 0;

	GetData(clientSocket, buf, sizeof(buf));

	std::string username = std::string(buf);
	
	if (mapOfCards.count(username) == 0)
	{
		const Card myCard(host, service); //create a new card for the new username
		mapOfCards.insert(std::pair<std::string, Card>(username, myCard));
		std::cout << "A new player with username \""<< username << "\" has connected!" << std::endl;
	}
	else
	{
		std::cout << "The player " << username << " has connected!" << std::endl;
	}
	   
	// One connection at a time!

	closesocket(listener);

	//accept and echo messages back to client

	while (true)
	{

		bytesReceived = GetData(clientSocket, buf, sizeof(buf));
		if (bytesReceived > 0)
		{

			if (strstr(buf, "Quit"))
			{
				closesocket(clientSocket);
				mapOfCards[username].~Card();
				mapOfCards.erase(username);

				std::cout << "Player quited! Opening the connection to a new player...";
				goto restartCS;
			}
			else if (strstr(buf, "End"))
			{
				std::cout << std::endl;
				std::cout << " - - - END GAME - - - ";
				break;
			}
			else if (strstr(buf, "Jogo"))
			{
				std::cout << std::endl;
				if (Jogo(clientSocket, &mapOfCards[username]))
				{
					std::cout << "Player Won!" << std::endl;
				}
				else
				{
					std::cout << std::endl;
					std::cout << "Player has exited! Saving content..." << std::endl;
					std::cout << std::endl;
					closesocket(clientSocket);
					goto restartCS;
				}
			}
		}

		
		//Echo the result

		//send(clientSocket, buf, bytesReceived + 1, 0);
				
	}

	//Clear Map of Cards
	std::map<std::string, Card>::iterator it; 

	for (it = mapOfCards.begin(); it != mapOfCards.end(); )
	{
		mapOfCards.erase(it++);
	}

	// Close socket
	
	closesocket(clientSocket);

	//Shutdown and cleanup Winsock

	WSACleanup();

	//std::cout << "Server Offline..." << std::endl;

	return 0;

}