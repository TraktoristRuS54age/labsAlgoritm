/*26. В текстовом  файле  имеется  некоторое   информационнное
письмо. Требуется сформировать ответ на письмо. Если  последнее
предложение письма является  вопросом,  начинающимся  со  слова 
"кто", то слово "кто"  заменяется  словами  "конь в пальто",  а 
знак вопроса заменяется на знак восклицания. В противном случае
нужно дать ответ: "Спасибо за информацию" (8).
Черепов Даниил ПС-21
*/
#include <iostream>
#include <string>
#include <fstream>

#include <windows.h>
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string in,ou, word,coutword;
	cout << "Введите входной файл" << endl;
	getline(cin, in);
	cout << "Введите выходной файл" << endl;
	getline(cin, ou);
	ifstream file;
	fstream out;
	file.open(in);
	out.open(ou);
	int n = 0;
	char ch = ' ';
	bool M = TRUE;

	if (!file.is_open())
	{
		cout << "Файл не найден! 1" << endl;
	}
	else
	{	
		while (!file.eof())
		{
			file.get(ch);
			if ((ch == '.') || (ch == '!') || (ch == '?'))
			{
				out << ch;
				file.get(ch);
				if (ch == ' ')
				{
					out << endl;
				}
			}
			else
			{
				if (ch == '\n')
				{
					out << ' ';
				}
				else
				{
					out << ch;
				}
				
			}
		}
		out.close();
	}
	file.close();

	ch = ' ';
	out.open(ou);
	if (!out.is_open())
	{
		cout << "Файл не найден! 2" << endl;
	}
	else
	{
		word, coutword = "";
		getline(out, word);
		while (M)
		{		
			if (word.size() == 0)
			{
				if (coutword[coutword.size() - 1] == '?')
				{
					ch = coutword.c_str()[n];
					if ((ch == 'К') || (ch == 'к'))
					{
						n = n + 1;
						ch = coutword.c_str()[n];
						if (ch == 'т')
						{
							n = n + 1;
							ch = coutword.c_str()[n];
							if (ch == 'о')
							{
								n = n + 1;
								ch = coutword.c_str()[n];
								if (ch == '-')
								{
									cout << "Спасибо за информацию! 5" << endl;
									M = FALSE;
								}
								else
								{
									cout << "Конь в пальто,";
									while (M)
									{
										cout << ch;
										n = n + 1;
										ch = coutword.c_str()[n];
										if (ch == '?')
										{
											M = FALSE;
										}
									}
									cout << "!" << endl;
								}
							}
							else
							{
								cout << "Спасибо за информацию! 4" << endl;
								M = FALSE;
							}
						}
						else
						{
							cout << "Спасибо за информацию! 3" << endl;
							M = FALSE;
						}
					}
					else
					{
						cout << "Спасибо за информацию! 2" << endl;
						M = FALSE;
					}
				}
				else
				{
					cout << "Спасибо за информацию! 1" << endl;
					M = FALSE;
				}
			}
			else
			{
				coutword = "";
				coutword = word;
			}
			getline(out, word);
		}
	}
	return 0;
}