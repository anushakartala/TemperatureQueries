#include "TemperatureDatabase.h"

#include <fstream>
using namespace std;
#include <string>
#include <sstream>
#include <cmath>

// Default constructor/destructor. Modify them if you need to.
TemperatureDatabase::TemperatureDatabase() {}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename)
{
ifstream inData(filename);
if(!inData.is_open())
{
	cout << "Error: Unable to open " << filename;
}
else
{
	while (!inData.eof())
	{
		string inputLine;
		getline(inData, inputLine);
		stringstream inputStringStream;
		string id;
		int year;
		int month;
		double temperature;
		if (!inputLine.empty())
		{
			inputStringStream << inputLine;
			inputStringStream >> id >> year >> month >> temperature;
		}
		if (inputStringStream.bad() || inputStringStream.fail())
		{
			cout << "Error: Other invalid input" << endl;
		}
		else if (year < 1800 || year > 2018)
		{
			cout << "Error: Invalid year " << year << endl;
		}
		else if (month < 1 || month > 12)
		{
			cout << "Error: Invalid month " << month << endl;
		}
		else if (temperature == -99.99)
		{

		}
		else if (temperature > 50.0 || temperature < -50.0)
		{
			cout << "Error: Invalid temperature " << temperature << endl;
		}
		else
		{
			records.insert(id, year, month, temperature);

		}
	}
}
records.print();
}

void TemperatureDatabase::performQuery(const string& filename)
{
	// Implement this function for part 2
	//  Leave it blank for part 1
	ifstream inData(filename);
	 ofstream txtOut;
	  //txtOut.open ("Example.txt");
	  txtOut.open ("result.dat");



	if(!inData.is_open())
	{
		cout << "Error: Unable to open " << filename;
	}
	else
	{
		while (!inData.eof())
		{
			string inputLine;
			getline(inData, inputLine);
			stringstream inputStringStream;
			string id;
			int year1;
			int year2;
			string query;
			bool valid=true;
			if (!inputLine.empty())
			{
				inputStringStream << inputLine;
				inputStringStream >> id >> query >> year1 >> year2;
			}
			if (inputStringStream.bad() || inputStringStream.fail())
			{
				cout << "Error: Other invalid query" << endl;
				valid=false;
			}
			else if (year1 < 1800 || year1 > 2018 || year2 < 1800 || year2 > 2018)
			{
				cout << "Error: Invalid range " << year1 << "-" << year2 << endl;
				valid=false;
			}
			else if(year2<year1)
			{
				cout << "Error: Invalid range " << year1 << "-" << year2 << endl;
			}
			else if ((query!="AVG") && (query!="MODE"))
			{
				cout << "Error: Unsupported query " << query <<endl;
				valid = false;
			}
			else if (query=="AVG")
			{
				Node * temp = new Node();
				double sum = 0;
				int count = 0;
				temp = records.getHead();
				while(temp != nullptr)
				{
					if(temp->data.id==id)
					{
						if(temp->data.year<=year2 && temp->data.year>=year1)
						{
							sum = sum + temp->data.temperature;
							count ++;
						}
					}
					temp = temp->next;

				}
				if (count>0)
					//cout << id<<"   "<<year1<<"    "<<year2<<"   "<<query<< "  " <<  sum/count<< endl;
					txtOut << id<<" "<<year1<<" "<<year2<<" "<<query<< " " <<  sum/count<< endl;
				else

					txtOut << id<<" "<<year1<<" "<<year2<<" "<<query<< " " <<  "unknown" << endl;

			}
			/*else if (query=="MODE")
						{
							Node * temp = new Node();
							double sum = 0;
							int count = 0;
							temp = records.getHead();
							double ValueArray[1000];
							int CountArray[1000];
							bool found;
							while(temp != nullptr)
							{
								if(temp->data.year<=year2 && temp->data.year>=year1)
								{
									found = false;
									for(int i=0; i<count; i++)
									{
										if(ValueArray[i] == temp->data.temperature)
										{
											CountArray[i] = CountArray[i] + 1;
											found = true;
										}
									}
									if (found==false)
									{
										ValueArray[count] = temp->data.temperature;
										CountArray[count] = 1;
										count ++;
									}

								}
								temp = temp->next;

							}
							if (count>0)
							{
								int max = CountArray[0];
								int position = 0;
								for(int i=1;i<count;i++)
								{
									if (CountArray[i]>=max)
									{
										max = CountArray[i];
										position =i;
									}

								}
								txtOut << id<<"   "<<year1<<"    "<<year2<<"   "<<query<< "  " <<  round(ValueArray[position])<< endl;

							}

							else

								txtOut << id<<"   "<<year1<<"    "<<year2<<"   "<<query<< "  " <<  "Unknown" << endl;

						}*/
			else if(query=="MODE")
			{
				int ValueArray[100] = {0};
				int max;
				int roundedValue;
				int position;
				Node * temp = new Node();
				temp = records.getHead();
				while(temp != nullptr)
				{
					if(temp->data.id == id)
					{
						if(temp->data.year<=year2 && temp->data.year>=year1)
						{

							roundedValue = round(temp->data.temperature);
							ValueArray[roundedValue] =ValueArray[roundedValue] + 1;


						}
					}
					temp = temp->next;

				}

				max=ValueArray[0];
				for(int i=1;i<100;i++)
				{
					if (ValueArray[i]>=max)
					{

						max = ValueArray[i];
						position = i;
					}
				}

				if(max>0)
					txtOut << id<<" "<<year1<<" "<<year2<<" "<<query<< " " <<  position<< endl;
				else
					txtOut << id<<" "<<year1<<" "<<year2<<" "<<query<< " " <<  "unknown" << endl;



			}

		}
	}
	inData.close();
	txtOut.close();

}
