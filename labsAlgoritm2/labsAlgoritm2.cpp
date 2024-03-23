/*7. Перед открытием двух железнодорожных касс сформировались
2 очереди пассажиров,  причем некоторые из них находятся сразу
в  обеих очередях.  Для каждого пассажира известны его места в
очередях и необходимое время обслуживания.  Если у какого-либо
пассажира очереди подходят одновременно, то он обслуживается в
первой   кассе.   Промоделировать   работу    касс,    выдавая
последовательно информацию об обслуживании пассажиров (7).*/
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

struct Passenger {	//пассажир структура
	char Name;
	int service_time;
	Passenger* next;
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream file("passengers.txt"); //файл с которого читаем

	vector<Passenger> cash_register_1;	//касса 1
	vector<Passenger> cash_register_2;	//касса 2

	Passenger* top = 0; //список пуст
	string str;
	char k, name = ' ';
	int time = 0, pos = 0, i = 0;
	while (!file.eof())	//запись пассажиров в кассы
	{
		file >> k;
		while (pos == 0)
		{
			file >> k;
			if ((k >= 'A') && (k <= 'Z'))
			{
				while (k != ')')
				{
					if ((k >= 'A') && (k <= 'Z'))
					{
						name = k;
					}
					if ((k >= '1') && (k <= '9'))
					{
						time = k - '0';
					}
					file >> k;
				}
					Passenger* c = new Passenger;
					c->Name = name;
					c->service_time = time;
					c->next = top;
					top = c;	
					cash_register_1.push_back({ name, time });
			}
			if (k == ';')
			{
				pos = 1;
			}
		}
		while (pos == 1)
		{
			file >> k;
			if ((k >= 'A') && (k <= 'Z'))
			{
				while (k != ')')
				{
					if ((k >= 'A') && (k <= 'Z'))
					{
						name = k;
					}
					if ((k >= '1') && (k <= '9'))
					{
						time = k - '0';
					}
					file >> k;
				}
				Passenger* c = new Passenger;
				c->Name = name;
				c->service_time = time;
				c->next = top;
				top = c;
				cash_register_2.push_back({ name, time });
			}
			if (k == ';')
			{
				pos = 2;
			}
		}
	}
	if ((cash_register_1.empty()) && (cash_register_2.empty()))	//свободны ли кассы
	{
		cout << "Ошибка: Обе кассы свободные" << endl;
	}
	else//заполнены
	{
		int reg1 = 0, reg2 = 0;
		cout << "Пассажиры 1 кассы: ";
		for (int i = 0; i < cash_register_1.size(); i++)
		{
			printf("%c", cash_register_1[reg1].Name);
			reg1 += 1;
			cout << " ";
		}
		cout << endl;
		cout << "Пассажиры 2 кассы: ";
		for (int i = 0; i < cash_register_2.size(); i++)
		{
			printf("%c", cash_register_2[reg2].Name);
			reg2 += 1;
			cout << " ";
		}
		cout << endl;
		reg1 = 0, reg2 = 0;
		int total1 = 0, total2 = 0;
		int i = 0, m = 1;
		total1 = total1 + cash_register_1[reg1].service_time;
		total2 = total2 + cash_register_2[reg2].service_time;
		while ((reg1 != cash_register_1.size()) || (reg2 != cash_register_2.size()))
		{
			if ((reg1 == cash_register_1.size()) || (reg2 == cash_register_2.size())) //проверка, если остались какие-либо пустые вектора
			{
				break;
			}
			if (cash_register_1[reg1].Name == cash_register_2[reg2].Name)
			{
				vector<Passenger> ::iterator it = cash_register_2.begin(); //удаляем из 2 кассы
				auto& iter = *it;
				i = 0, m = 1;
				char id_passenger = cash_register_1[reg1].Name;
				while (i < cash_register_2.size())
				{
					if (it->Name == id_passenger)
					{
						cash_register_2.erase(it);
						i = cash_register_2.size();
					}
					else
					{
						if (m != cash_register_2.size())
						{
							it += 1;
							m += 1;
						}
						else
						{
							i = cash_register_2.size();
						}
					}
				}
			}
			else
			{
			    vector<Passenger> ::iterator it = cash_register_2.begin(); //удаляем из 2 кассы
				auto& iter = *it;
				i = 0, m = 1;
				char id_passenger = cash_register_1[reg1].Name;
				while (i < cash_register_2.size())
				{
					if (it->Name == id_passenger)
					{
						cash_register_2.erase(it);
						i = cash_register_2.size();
					}
					else
					{
						if (m != cash_register_2.size())
						{
							it += 1;
							m += 1;
						}
						else
						{
							i = cash_register_2.size();
						}
					}
				}
				vector<Passenger> ::iterator itt = cash_register_1.begin(); //удаляем из 1 кассы
				auto& ites = *itt;
				i = 0, m = 1;
				id_passenger = cash_register_2[reg2].Name;
				while (i < cash_register_1.size())
				{
					if (itt->Name == id_passenger)
					{
						cash_register_1.erase(itt);
						i = cash_register_1.size();
					}
					else
					{
						if (m != cash_register_1.size())
						{
							itt += 1;
							m += 1;
						}
						else
						{
							i = cash_register_1.size();
						}
					}
				}
				if (total1 > total2)
				{	
					if (reg2 == cash_register_2.size())
					{
						break;
					}
					else
					{
						reg2 += 1;
						total2 = total2 + cash_register_2[reg2].service_time;
					}
				}
				else
				{
					if (total1 < total2)
					{	
						if (reg1 == cash_register_1.size())
						{
							break;
						}
						else
						{
							reg1 += 1;
							total1 = total1 + cash_register_1[reg1].service_time;
						}
					}
					else
					{
						if (reg1 != cash_register_1.size())
						{
							reg2 += 1;
						}
						if (reg2 != cash_register_2.size())
						{
							reg1 += 1;
						}
					}
				}	
				
			}
		}
		reg1 = 0, reg2 = 0, total1 = 0, total2 = 0;
		cout << "Пассажиры 1 кассы, которые были обслужены: ";
		for (int i = 0; i < cash_register_1.size(); i++)
		{
			printf("%c", cash_register_1[reg1].Name);
			cout << '[' << total1 << ',';
			total1 = total1 + cash_register_1[reg1].service_time;
			cout << total1 << ']';
			reg1 += 1;
			cout << " ";
		}
		cout << endl;
		cout << "Пассажиры 2 кассы, которые были обслужены: ";
		for (int i = 0; i < cash_register_2.size(); i++)
		{
			printf("%c", cash_register_2[reg2].Name);
			cout << '[' << total2 << ',';
			total2 = total2 + cash_register_2[reg2].service_time;
			cout << total2 << ']';
			reg2 += 1;
			cout << " ";
		}
		cout << endl;
	}
	cout << "Все пассажиры обслужены в кассах" << endl;
	return 0;
}