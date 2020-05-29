#include "ClassicCashRegister.h"

ClassicCashRegister::ClassicCashRegister() {
	this->counter = 0;
	this->productsToScan = 0;
}

int ClassicCashRegister::getCounter()
{
	return counter;
}

int ClassicCashRegister::getProductsToScan()
{
	return this->productsToScan;
}

void ClassicCashRegister::setProductsToScan(int productsToScan)
{
	this->productsToScan = productsToScan;
}

void ClassicCashRegister::Scan(Client* client) {
	this->clientsQueue.push_back(client);
	_mutex.lock();
	this->clientsQueue.erase(std::find(clientsQueue.begin(), clientsQueue.end(), client));
	counter++;
}

void ClassicCashRegister::Pay() {
	_mutex.unlock();
	counter--;
}

std::vector<Client*> ClassicCashRegister::getQueue()
{
	return this->clientsQueue;
}
