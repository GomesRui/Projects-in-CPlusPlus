#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <set>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

#define BUF_SIZE_SENT 31
#define BUF_SIZE_RECEIVE 31
#define PORT 54000
#define MAX_CARD 10
#define IPADDRESS "127.0.0.1"


int GetData(SOCKET clientSocket, char *buf, int size)
{
	int bytesReceived = 0;

	while (true)
	{
		bytesReceived = recv(clientSocket, buf, size, 0);

		if (bytesReceived <= 0) //Input data will be stored in the buffer coming from the Client
		{
			std::cerr << "Failed reading data from the client Socket";
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

void GetUser(SOCKET sock)
{
	std::string inputDataS;

	do
	{
		std::cout << "Please provide your username: ";
		std::cin >> inputDataS;

		if (inputDataS.size() > 0)
		{
			char inputData[sizeof(inputDataS)] = { '\0' };

			inputDataS.copy(inputData, inputDataS.size());
			SendData(sock, inputData, sizeof(inputData));

			break;
		}

	} while (true);
}

bool Jogo(SOCKET sock, int result)
{
	char inputData[BUF_SIZE_SENT] = { '\0' }; //to send
	char outputData[BUF_SIZE_RECEIVE] = { '\0' };  //to receive

	std::set<int> currentCard;
	std::set<int>::iterator it;

	//converted std::strings between char[] and std::string for send and recv.
	std::string stringInput;
	std::string stringOutput; 

	int numberDraw;

	bool found = false; //to check when a number was found
		
		if (result != SOCKET_ERROR)
		{
			//Wait for response
			int bytesReceived = GetData(sock, outputData, sizeof(outputData));


			//Populating the set collection with the numbers
			int count = 0, lastValue = 0, countCardNumbers = 0;
			for (int i = 0; i < strlen(outputData); i++)
			{
				if (outputData[i] == ',') //using ',' to separate numbers
				{
					countCardNumbers++;
					stringInput = std::string(outputData, i - count , count);

					if (stringInput.front() == ',') //taking out extra ','s
						stringInput.erase(stringInput.begin());

					currentCard.insert(stoi(stringInput));
					count = 0;
					lastValue = i;
				}

				count++;

			}
			


			//Send the ACK to Server
			if (bytesReceived > 0 && countCardNumbers == 10)
			{
				std::cout << "Server> ";
				std::cout << "CARD OUT: " << std::string(outputData, 0, lastValue) << std::endl; // Echo response to console
				stringInput = "Received";
				stringInput.copy(inputData, sizeof(inputData));
				SendData(sock, inputData, strlen(inputData));

				//Wait for the draw numbers
				do
				{
					//clearing buffer variables.
					ZeroMemory(outputData, sizeof(outputData));
					ZeroMemory(inputData, sizeof(inputData));

					GetData(sock, outputData, sizeof(outputData));
					numberDraw = atoi(outputData); //Converting from char[] to int

					std::cout << std::endl;
					std::cout << "Draw: " << numberDraw << " | ";
					std::cout << "Current Card: ";
					
					//Check for number in the card
					for (it = currentCard.begin(); it != currentCard.end(); )
					{
						if (*it == numberDraw)
						{
							found = true;
							currentCard.erase(it++);
						}
						else if (*it == 0)
						{
							currentCard.erase(it++);
						}
						else
						{
							std::cout << *it << " ";
							++it;
						}												
					}

					std::cout << " | Missing Numbers: " << currentCard.size() << " | ";

					if (found)
					{
						std::cout << "Number found!";
						found = false;
					}
					

					//Check final result in card
					if (currentCard.size() == 0)
					{
						stringInput = "Won";
						stringInput.copy(inputData, stringInput.size());
						SendData(sock, inputData, strlen(inputData));
						break;
					}
					else
					{
						stringInput = "Next";
						stringInput.copy(inputData, stringInput.size());
						SendData(sock, inputData, strlen(inputData));						
					}			


				} while (true);

			}

			else
			{
				std::cout << "Failed to get the card!" << std::endl;
				std::cout << "Going back to the menu..." << std::endl;
				return false;
			}
					   
		}
		else 
		{
			std::cout << "Failed to start the game!" << std::endl;
			std::cout << "Going back to the menu..." << std::endl;
			return false;
		}

	//cleaning arrays
	ZeroMemory(inputData, sizeof(inputData));
	ZeroMemory(outputData, sizeof(outputData));

	std::cout << std::endl;
	std::cout << "Player Won!" << std::endl;
	std::cout << std::endl;

	return true;
}

int main()
{

	//Server's connection input
	std::string ipAddr = IPADDRESS;
	int port = PORT;

	//Initialize WinSock
	WSAData data;
	WORD version = MAKEWORD(2, 2);
	int wsResult = WSAStartup(version, &data);

	if (wsResult != 0)
	{
		std::cerr << "Error starting winsock. Err: " << wsResult << std::endl;
		return -1;
	}

	//Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Error creating socket! Err: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}

	//Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddr.c_str(), &hint.sin_addr);

	//Connect to server
	int connRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connRes == SOCKET_ERROR)
	{
		std::cerr << "ERROR connecting to server! Err: " << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return -1;
	}

	GetUser(sock); //get the client's username

	char command[5] = { '\0' }; //to send
	std::string inputDataS;

	//Loop to start the game
	do
	{
		//Displaying Menu
		std::cout << std::endl;
		std::cout << " ============ MENU ============ " << std::endl;
		std::cout << " = 'Jogo' - To start game " << std::endl;
		std::cout << " = 'Quit' - To quit the user " << std::endl;
		std::cout << " = 'End' - To end the game " << std::endl;
		std::cout << " ============================== " << std::endl;
		//Prompt user for input
		std::cout << "Send data: ";
		std::cin >> inputDataS;
		std::cout << std::endl;

		if (inputDataS.size() > 0 && inputDataS == "Jogo" || inputDataS == "Quit" || inputDataS == "End")
		{
			//Send text
			inputDataS.copy(command, sizeof(command));
			int result = SendData(sock, command, strlen(command));

			if (inputDataS == "Jogo")
			{
				if (Jogo(sock, result))
				{
					std::cout << "GAME HAS FINISHED! Going back to the menu..." << std::endl;
					std::cout << std::endl;
				}
				else
				{
					std::cout << "Player Lost!" << std::endl;
					break;
				}
			}
			else if (inputDataS == "Quit")
			{
				std::cout << "Program is going to close..." << std::endl;
				break;
			}
			else if (inputDataS == "End")
			{
				std::cout << "Ending game..." << std::endl;
				break;
			}
		}
		else
		{
			std::cout << "Wrong input. To start the game, write 'Jogo', 'Quit' or 'End'" << std::endl;
		}

	} while (true);

	//Close down
	closesocket(sock);
	WSACleanup();
	return 0;

}