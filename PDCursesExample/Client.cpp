#include "Client.h"
#include <Windows.h>

void Client::setNumberOfProductsInBag(int number)
{
	this->numberOfProductsInBag = number;
}

void Client::setShoppingTime()
{
	this->shoppingTime -= 1;
	Sleep(dist(mt));
}

void Client::setShoppingTime(int time)
{
	this->shoppingTime = time;
}

void Client::collectProduct()
{
	this->numberOfProductsInBag += 1;
}

int Client::getNumberOfProductsInBag()
{
	return this->numberOfProductsInBag;
}

int Client::getShoppingTime()
{
	return this->shoppingTime;
}

std::string Client::getName()
{
	return this->name;
}


Client::Client(int shoppingTime, int numberOfProductsInBag, std::string name)
{
	this->mt = std::mt19937(generator());
	this->dist = std::uniform_int_distribution<int>(1000, 6000);
	this->shoppingTime = shoppingTime;
	this->numberOfProductsInBag = numberOfProductsInBag;
	this->name = name;
}

