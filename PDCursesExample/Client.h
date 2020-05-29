#pragma once
#include <string>
#include <random>
class Client
{
private:
	int numberOfProductsInBag;
	int shoppingTime;
	std::string name;;
	std::random_device generator;
	std::mt19937 mt;
	std::uniform_int_distribution<int> dist;
public:
	int getNumberOfProductsInBag();
	int getShoppingTime();
	std::string getName();
	void setNumberOfProductsInBag(int number);
	void setShoppingTime();
	void setShoppingTime(int time);
	void collectProduct();
	Client(int shoppingTime, int numberOfProductsInBag, std::string name);
};

