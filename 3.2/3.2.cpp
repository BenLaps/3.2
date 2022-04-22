#include <iostream>
#include <string>
#include <iomanip>
#include <locale>
#include <Windows.h> 

using namespace std;


//1. Для кожного предмету обчислити середній бал.

//2. Обчислити кількість студентів, які отримали з фізики оцінки “5” або “4

//enum Cours{l,ll,lll,lV,V};

struct Student
{
	string lastname;
	//Cours cours;
	string cours;
	string spec;
	int physic;
	int math;
	int informatic;
};


void Create(Student* s, const int N);
void Print(Student* s, const int N);

void Sort(Student* s, const int N);

int* IndexSort(Student* s, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);

int BinSearch(Student* s, const int N, const string lastname, const string cours, const int informatic);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "Введіть N: "; cin >> N;

	Student* s = new Student[N];

	int menuItem;
	string lastname = "";
	string cours = "";
	int informatic = 0;
	int found;


	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [5] - сортування" << endl;
		cout << " [6] - індексне впорядкування та вивід даних" << endl;
		cout << " [7] - бінарний пошук студента за прізвищем , курсом та оцінкою з інформатики" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;


		switch (menuItem)
		{
		case 1:
			Create(s, N);
			break;
		case 2:
			Print(s, N);
			break;
		case 5:
			Sort(s, N);
			break;
		case 6:
			PrintIndexSorted(s, IndexSort(s, N), N);
			break;
		case 7:
			cout << "Введіть ключі пошуку:" << endl;
			cout << " Прізвище: "; cin >> lastname;
			cout << " Куср "; cin >> cours;
			cout << " Оцінку з інформатики "; cin >> informatic;
			cin.get(); 
			cin.sync(); 

			cout << endl;
			if ((found = BinSearch(s, N, lastname, cours, informatic)) != -1)
				cout << "Знайдено працівника в позиції " << found + 1 << endl;
			else
				cout << "Шуканого працівника не знайдено" << endl;
			break;

			BinSearch(s, N, lastname, cours, informatic);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}

void Create(Student* s, const int N)
{
	for (int i = 0; i < N; i++)
	{
		cin.get();
		cin.sync();
		cout << "Студент № " << i + 1 << ":" << endl;
		cout << " Прізвище: "; cin >> s[i].lastname;
		cout << " Курс: "; cin >> s[i].cours;
		cout << " Спеціальність: "; cin >> s[i].spec;
		cout << " Оцінка з фізики: "; cin >> s[i].physic;
		cout << " Оцінка з математики: "; cin >> s[i].math;
		cout << " Оцінка з інформатики: "; cin >> s[i].informatic;
		cout << endl;
	}
}
void Print(Student* s, const int N)
{
	cout << "========================================================================="
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Інформатика | "
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << s[i].lastname
			<< "| " << setw(4) << right << s[i].cours << " "
			<< "| " << setw(11) << left << s[i].spec << " "
			<< "| " << setw(6) << right << s[i].physic << " "
			<< "| " << setw(6) << left << s[i].math << " "
			<< "| " << setw(7) << right << s[i].informatic << endl;
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}
void Sort(Student* s, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((s[i1].cours > s[i1 + 1].cours)
				||
				(s[i1].cours == s[i1 + 1].cours &&
					s[i1].informatic > s[i1 + 1].informatic)
				||
				(s[i1].cours == s[i1 + 1].cours &&
					s[i1].informatic == s[i1 + 1].informatic &&
					s[i1].lastname < s[i1 + 1].lastname))
			{
				tmp = s[i1];
				s[i1] = s[i1 + 1];
				s[i1 + 1] = tmp;
			}
}

int* IndexSort(Student* s, const int N)
{
	int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; // починаємо сортувати масив індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((s[I[j]].cours > s[value].cours) ||
				(s[I[j]].cours == s[value].cours &&
					s[I[j]].informatic > s[value].informatic) ||
				(s[I[j]].cours == s[value].cours &&
					s[I[j]].informatic == s[value].informatic &&
					s[I[j]].lastname < s[value].lastname));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* s, int* I, const int N)
{ // аналогічно функції Print(), але замість звертання p[i]... 
 // використовуємо доступ за допомогою індексного масиву І: p[I[i]]...
	cout << "========================================================================="
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Інформатика | "
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << s[I[i]].lastname
			<< "| " << setw(4) << right << s[I[i]].cours << " "
			<< "| " << setw(11) << left << s[I[i]].spec << " "
			<< "| " << setw(6) << right << s[I[i]].physic << " "
			<< "| " << setw(6) << left << s[I[i]].math << " "
			<< "| " << setw(7) << right << s[I[i]].informatic << endl;
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}

int BinSearch(Student* s, const int N, const string lastname, const string cours, const int informatic)
{
	// повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (s[m].lastname == lastname && s[m].cours == cours && s[m].informatic == informatic)
			return m;
		if ((s[m].lastname < lastname)
			||
			(s[m].cours == cours &&
				s[m].lastname < lastname)
			||
			(s[m].informatic == informatic &&
				s[m].cours == cours &&
				s[m].lastname < lastname))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}

