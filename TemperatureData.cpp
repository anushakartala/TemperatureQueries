#include "TemperatureData.h"
using namespace std;
#include <string>

TemperatureData::TemperatureData() : id(""), year(0), month(0), temperature(0.0) {}

TemperatureData::TemperatureData(std::string id, int year, int month, double temperature) : id(id), year(year), month(month), temperature(temperature) {}


TemperatureData::~TemperatureData() {} // You should not need to implement this

bool TemperatureData::operator<(const TemperatureData& b)
{
	if(this -> id < b.id)
	{
		return true;
	}
	if(this -> id > b.id)
	{
		return false;
	}
	if (this -> year < b.year)
	{
		return true;
	}
	if (this -> year > b.year)
	{
		return false;
	}
	if (this -> month < b.month)
	{
		return true;
	}
	if (this -> month > b.month)
	{
		return false;
	}
	if (this -> temperature < b.temperature)
	{
		return true;
	}
		return true;
}
