#pragma once
#include <mutex>
#include <vector>
#include "Client.h"

class ClassicCashRegister
{
	private:
		std::mutex _mutex;
		int counter;
		int productsToScan;
		std::vector<Client*> clientsQueue;

	public:
		ClassicCashRegister();
		int getCounter();
		int getProductsToScan();
		void setProductsToScan(int productsToScan);
		void Scan(Client* client);
		void Pay();
		std::vector<Client*> getQueue();
};

