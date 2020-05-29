#pragma once
#include <mutex>
class SelfCashRegister
{
private:
	std::mutex _mutex;
	int counter;
	int productsToScan;
public:
	SelfCashRegister();
	int getCounter();
	int getProductsToScan();
	void setProductsToScan(int productsToScan);
	void Scan();
	void Pay();
};

