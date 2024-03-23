/* 
6. Имеется дерево, корень которого соответствует основателю
рода.  Сыновья  каждой  вершины  задают  сыновей   и   дочерей
соответствующего    человека.   Указывается   имя   некоторого
человека.  Требуется выдать имена его детей,  внуков, сестер и
братьев, одного из родителей, дедушки или бабушки (9).
Черепов Даниил ПС-21
*/

#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <fstream>
using namespace std;

const int DL = 20;//Максимальная длина имени 
struct Tree {
	char name[DL];//имя
	Tree* fath;//отец
	int urov;//уровень исходного дерева
	vector <Tree*> sons;//указатели на сыновей
};

//Функция внесения данных
void Add(ifstream &F, Tree*&r)
{
	char buf[DL];
	int i, j, k, m, len;
	Tree* p, * q, * t;//top = NULL
	m = -1;//уровень предыдущей вершины
	t = 0;//указатель на предыдущую вершину
	while (!F.eof())
	{
		F >> buf;
		len = strlen(buf);
		if (len == 0) continue;
		//если конец файла в следующей строке или пустая строка
		k = 0;
		while (buf[k] == '.') k++;
		p = new Tree;
		i = 0;
		j = k;
		while (p->name[i++] = buf[j++]);
		//копирование вместе с '\0э
		p->urov = k;
		if (k == 0)                    // корень
		{
			r = p;
			t = r;
			m = 0;
			continue;
		}
		if (k > m)       // переход на следующий уровень
		{
			t->sons.push_back(p);
			p->fath = t;
		}
		else if (k == m)            // тот же уровень
		{
			q = t->fath;
			q->sons.push_back(p);
			p->fath = q;
		}
		else        // подъем по дереву на m-k+1 уровней
		{
			q = t;
			for (i = 0; i <= m - k; i++) q = q->fath;
			// q - отец вводимой вершины p
			q->sons.push_back(p);
			p->fath = q;
		}
		m = k;      // текущий уровень
		t = p;      // текущая вершина
	}
}

void print_down(Tree* p, int level, string name)
{
	if (strcmp(p->name, name.c_str()) == 0) {
		if (!p->sons.empty()) {
			cout << "Дети: ";
			for (int i = 0; i < p->sons.size(); i++) {
				cout << p->sons[i]->name << " ";
			}
			cout << endl;
		} else {
			cout << "Детей нет" << endl;
		}
		if (p->urov != 0) {
			vector<Tree*> siblings = p->fath->sons;
			if (siblings.size() == 1)
			{
				cout << "Братьев и сестёр нет";
			} else {
				cout << "Братья, сёстры: ";
				for (int i = 0; i < siblings.size(); i++) {
				if (strcmp(siblings[i]->name, p->name) != 0) {
					cout << siblings[i]->name << " ";
					}
				}
				
			}	
			cout << endl;
			cout << "Родитель: " << p->fath->name << endl;
			if (p->fath->urov != 0) {
				cout << "Дедушка: " << p->fath->fath->name << endl;
			} else {
				cout << "Дедушки нет" << endl;
			}
		} else {
			cout << "Братьев и сестёр нет. Родитель неизвестен. Дедушка неизвестен. Мы у основателя дерева" << endl;
		}
		if (!p->sons.empty()) {
			cout << "Внуки: ";
			int z = 0, r = 0;
			for (int i = 0; i < p->sons.size(); i++) {
				if (p->sons[i]->sons.size() != 0) {
					for (int j = 0; j < p->sons[i]->sons.size(); j++) {
						cout << p->sons[i]->sons[j]->name << " ";
						r += 1;
					}
				} else {
					if (r == 0) {
						z += 1;
					}
				}

			} if (z != 0) {
				cout << "их нет";
			}
		} else {
			cout << "Внуков нет";
		}
		cout << endl;
	}
	if (p->sons.size()) {
		for (int i = 0; i < p->sons.size(); i++)
			print_down(p->sons[i], level + 1, name);
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream file("Tree.txt");
	Tree* top = nullptr;
	int answer = 0;
	while (answer != 3)
	{
		cout << "Введите желаемое действие:" << endl;
		cout << "Введите 1 -> запись дерева" << endl;
		cout << "Введите 2 -> вывести потомков" << endl;
		cout << "Введите 3 -> остановить программуы" << endl;
		cin >> answer;
		switch (answer)
		{
		case 1:
			Add(file, top);
			break;
		case 2:
			char names[DL];
			cout << "Введите имя человека ";
			cin >> names;
			print_down(top, 0, names);
			break;
		case 3:
			break;
		}
	}
	return 0;
}