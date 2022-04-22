#include <iostream>
#include <string>
#include <iomanip>
#include <locale>
#include <Windows.h> 

using namespace std;


//1. ��� ������� �������� ��������� ������� ���.

//2. ��������� ������� ��������, �� �������� � ������ ������ �5� ��� �4

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
	cout << "������ N: "; cin >> N;

	Student* s = new Student[N];

	int menuItem;
	string lastname = "";
	string cours = "";
	int informatic = 0;
	int found;


	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [5] - ����������" << endl;
		cout << " [6] - �������� ������������� �� ���� �����" << endl;
		cout << " [7] - ������� ����� �������� �� �������� , ������ �� ������� � �����������" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
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
			cout << "������ ����� ������:" << endl;
			cout << " �������: "; cin >> lastname;
			cout << " ���� "; cin >> cours;
			cout << " ������ � ����������� "; cin >> informatic;
			cin.get(); 
			cin.sync(); 

			cout << endl;
			if ((found = BinSearch(s, N, lastname, cours, informatic)) != -1)
				cout << "�������� ���������� � ������� " << found + 1 << endl;
			else
				cout << "�������� ���������� �� ��������" << endl;
			break;

			BinSearch(s, N, lastname, cours, informatic);
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
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
		cout << "������� � " << i + 1 << ":" << endl;
		cout << " �������: "; cin >> s[i].lastname;
		cout << " ����: "; cin >> s[i].cours;
		cout << " ������������: "; cin >> s[i].spec;
		cout << " ������ � ������: "; cin >> s[i].physic;
		cout << " ������ � ����������: "; cin >> s[i].math;
		cout << " ������ � �����������: "; cin >> s[i].informatic;
		cout << endl;
	}
}
void Print(Student* s, const int N)
{
	cout << "========================================================================="
		<< endl;
	cout << "| � | ������� | ���� | ������������ | Գ���� | ���������� | ����������� | "
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
	for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
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
	int* I = new int[N]; // �������� ��������� �����
	for (int i = 0; i < N; i++)
		I[i] = i; // ��������� ���� ����������� ������
	int i, j, value; // �������� ��������� ����� �������
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
{ // ��������� ������� Print(), ��� ������ ��������� p[i]... 
 // ������������� ������ �� ��������� ���������� ������ �: p[I[i]]...
	cout << "========================================================================="
		<< endl;
	cout << "| � | ������� | ���� | ������������ | Գ���� | ���������� | ����������� | "
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
	// ������� ������ ���������� �������� ��� -1, ���� ������� ������� �������
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

