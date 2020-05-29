#include "SelfCashRegister.h"

SelfCashRegister::SelfCashRegister() {
	this->counter = 0;
	this->productsToScan = 0;
}

int SelfCashRegister::getCounter()
{
	return counter;
}

int SelfCashRegister::getProductsToScan()
{
	return this->productsToScan;
}

void SelfCashRegister::setProductsToScan(int productsToScan)
{
	this->productsToScan = productsToScan;
}

void SelfCashRegister::Scan() {
	counter++;
	_mutex.lock();
}

void SelfCashRegister::Pay() {
	counter--;
	_mutex.unlock();
}