#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <atomic>
#include "Client.h"
#include <thread>
#include <chrono>
#include <string>
#include <windows.h>
#include "ClassicCashRegister.h"
#include <random>
#include <windows.h>
#include "SelfCashRegister.h"

const int THREAD_NUMBER = 30;
const int SELF_CASH_REGISTER_SIZE = 4;
const int CLASSIC_CASH_REGISTER_SIZE = 2;
std::vector<Client*> clients;
ClassicCashRegister* cashLong1;
ClassicCashRegister* cashLong2;
SelfCashRegister* cashShort1;
SelfCashRegister* cashShort2;
SelfCashRegister* cashShort3;
SelfCashRegister* cashShort4;
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(20, 60);

int bestSelf()
{
	std::vector<int> countery{ cashShort1->getCounter(),cashShort2->getCounter(),cashShort3->getCounter(),cashShort4->getCounter() };
	int index = std::distance(countery.begin(), std::min_element(std::begin(countery), std::end(countery)));
	return index;
}


void clientLifeCycle(Client* client)
{
	while (true)
	{
		while (client->getShoppingTime() > 0)
		{
			client->collectProduct();
			client->setShoppingTime();
		}

		if (client->getNumberOfProductsInBag() >= 35)
		{
			if (cashLong1 -> getQueue().size() <= cashLong2 ->getQueue().size())
			{
				cashLong1 ->Scan(client);
				for (int i = client->getNumberOfProductsInBag(); i > 0; i--)
				{
					client->setNumberOfProductsInBag(client->getNumberOfProductsInBag() - 1);
					cashLong1->setProductsToScan(client->getNumberOfProductsInBag());
					Sleep(500);
				}

				cashLong1 ->Pay();
				client->setShoppingTime(distribution(generator));
			}
			else
			{
				
				cashLong2 ->Scan(client);
				for (int i = client->getNumberOfProductsInBag(); i > 0; i--)
				{
					client->setNumberOfProductsInBag(client->getNumberOfProductsInBag() - 1);
					cashLong2->setProductsToScan(client->getNumberOfProductsInBag());
					Sleep(500);
				}

				cashLong2 ->Pay();
				client->setShoppingTime(distribution(generator));
			}
			Sleep(20000);
		}
		else
		{
			int selectCash = bestSelf();
			switch (selectCash)
			{
				case 0:
				default:
					cashShort1->Scan();
					for (int i = client->getNumberOfProductsInBag(); i > 0; i--)
					{
						client->setNumberOfProductsInBag(client->getNumberOfProductsInBag() - 1);
						cashShort1->setProductsToScan(client->getNumberOfProductsInBag());
						Sleep(1500);
					}
					cashShort1->Pay();
					client->setShoppingTime(distribution(generator));
					break;
				case 1:
					cashShort2->Scan();
					for (int i = client->getNumberOfProductsInBag(); i > 0; i--)
					{
						client->setNumberOfProductsInBag(client->getNumberOfProductsInBag() - 1);
						cashShort2->setProductsToScan(client->getNumberOfProductsInBag());
						Sleep(1500);
					}
					cashShort2->Pay();
					client->setShoppingTime(distribution(generator));
					break;
				case 2:
					cashShort3->Scan();
					for (int i = client->getNumberOfProductsInBag(); i > 0; i--)
					{
						client->setNumberOfProductsInBag(client->getNumberOfProductsInBag() - 1);
						cashShort3->setProductsToScan(client->getNumberOfProductsInBag());
						Sleep(1500);
					}
					cashShort3->Pay();
					client->setShoppingTime(distribution(generator));
					break;
				case 3:
					cashShort4->Scan();
					for (int i = client->getNumberOfProductsInBag(); i > 0; i--)
					{
						client->setNumberOfProductsInBag(client->getNumberOfProductsInBag() - 1);
						cashShort4->setProductsToScan(client->getNumberOfProductsInBag());
						Sleep(1500);
					}
					cashShort4->Pay();
					client->setShoppingTime(distribution(generator));
					break;
			}
			Sleep(20000);
		}
	}
}

void Display(std::atomic<bool>& displaying)
{

	while (displaying)
	{
		clear();

		// title
		mvprintw(1, 1, " ##########################");
		mvprintw(2, 1, " # Symulator supermarketu #");
		mvprintw(3, 1, " ##########################");

		// classic cash registers and queues to them
		attron(COLOR_PAIR(2));
		mvprintw(5, 1, "-----------------");
		mvprintw(6, 1, "| Kasy klasyczne |");
		mvprintw(7, 1, "-----------------");
		std::vector<ClassicCashRegister*> classicCashRegistersVect{ cashLong1, cashLong2 };
		for (int i = 0; i < CLASSIC_CASH_REGISTER_SIZE; i++)
		{
			attron(COLOR_PAIR(2));
			std::string s = "[ " + std::to_string(classicCashRegistersVect[i]->getProductsToScan()) + " ]";
			mvprintw(8 + i * 3, 1, "^^^^^");
			mvprintw(9 + i*3, 1, s.c_str());
			mvprintw(10 + i * 3, 1, "^^^^^");
		}

		// first classic cash register queue
		std::vector<Client*> queueFirst = cashLong1->getQueue();
		std::string queueFirstClassicText = "";
		for (int i = 0; i < queueFirst.size(); i++)
		{
			queueFirstClassicText += std::to_string(queueFirst[i]->getNumberOfProductsInBag()) + " | ";
		}
		mvprintw(8, 8, "같같같같같같같같같같같같같같같같같같같같같같같같같");
		mvprintw(9, 8, queueFirstClassicText.c_str());
		mvprintw(10, 8, "같같같같같같같같같같같같같같같같같같같같같같같같같");

		// second classic cash register queue
		std::vector<Client*> queueSecond = cashLong2->getQueue();
		std::string queueSecondClassicText = "";
		for (int i = 0; i < queueSecond.size(); i++)
		{
			queueSecondClassicText += std::to_string(queueSecond[i]->getNumberOfProductsInBag()) + " | ";
		}
		mvprintw(11, 8, "같같같같같같같같같같같같같같같같같같같같같같같같같");
		mvprintw(12, 8, queueSecondClassicText.c_str());
		mvprintw(13, 8, "같같같같같같같같같같같같같같같같같같같같같같같같같");


		// self cash registers
		attron(COLOR_PAIR(3));
		mvprintw(15, 1, "---------------------");
		mvprintw(16, 1, "| Kasy samoobslugowe |");
		mvprintw(17, 1, "---------------------");
		std::vector<SelfCashRegister*> selfCashRegistersVect{ cashShort1, cashShort2, cashShort3, cashShort4 };
		for (int i = 0; i < SELF_CASH_REGISTER_SIZE; i++)
		{
			std::string s = "[ " + std::to_string(selfCashRegistersVect[i]->getProductsToScan()) + " ]";
			mvprintw(18, 1 + i*6, s.c_str());
		}

		attron(COLOR_PAIR(1));
		mvprintw(1, 80, "Klienci w sklepie: ");
		for (int i = 0; i < clients.size(); i++)
		{
			std::string s = "Klient " + clients[i]->getName() + ", liczba produktow: " + std::to_string(clients[i]->getNumberOfProductsInBag());
			mvprintw(2 +1*i, 80, s.c_str());
		}
		refresh();
	}		
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	initscr();
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

	cashLong1 = new ClassicCashRegister();
	cashLong2 = new ClassicCashRegister();
	cashShort1 = new SelfCashRegister();
	cashShort2 = new SelfCashRegister();
	cashShort3 = new SelfCashRegister();
	cashShort4 = new SelfCashRegister();
	
	std::vector<std::thread> threads;

	for (int i = 0; i < THREAD_NUMBER; i++)
	{
		clients.push_back(new Client(rand() % 40 + 20, 0, std::to_string(i)));
	}

	for (int i = 0; i < clients.size(); i++)
	{
		threads.push_back(std::thread(clientLifeCycle, clients[i]));
	}

	std::atomic<bool> displaying{ true };
	std::thread displayThread(Display, std::ref(displaying));

	int esc = 0;
	do {
		noecho();
		esc = getch();
	} while (esc != 27);

	displaying = false;

	for (int i = 0; i < clients.size(); i++) {
		threads[i].join();
	}

	displayThread.join();
	endwin();
	return 0;
}