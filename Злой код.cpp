#include <iostream>
#include <fstream>

//������� ��� ����������� �������� � ������ ������ ������. ��� ����������� ���������.
inline void tablo(std::ofstream  &out, int gcount, int Ncount, char tab) {
	int rcount;
	if (tab == 'L') rcount = 0;
	if (tab == 'R') rcount = Ncount - gcount;
	if (tab == 'C') rcount = (Ncount - gcount) / 2;
	for (int i = 0; i < rcount; ++i) out << " ";
}

int main()
{
	setlocale(0, "Russian");

	std::ifstream  in("text.txt");
	std::ofstream  out("textout.txt");
	char tab = ' ';
	int Ncount = -1;
	while ((tab != 'L') && (tab != 'C') && (tab != 'R') || (Ncount < 0)) {
		std::cout << "�� ������ ���� ���������?(L,R,C) ";
		std::cin >> tab;
		std::cout << "������ ���� �����: ";
		std::cin >> Ncount;
	}
	char *s = new char[Ncount];///������ ��� ����������
	char *s1 = new char[Ncount];///������ ��� ������
	int gcount;
	int i;
	int back;

	while (in.peek() != EOF) {

		///� ������, ���� ��� ������ ������ ���� �� ����� �� ��� � �����, �� �� ��������� �� � ����������� ���������.
		if (!(in.getline(s, Ncount))) {
			std::cout << "�������� ������ ���� �����!" << std::endl;
			delete[] s;
			delete[] s1;
			in.close();
			out.close();
			system("pause");
			return -1;
		}

		gcount = in.gcount();
		back = 0;
		i = 0;

		///� ��������� ������ ������������ � ������� ������� �� ����������� ������ ���������.
		while ((i < gcount) && ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n') || (s[i] == '\0'))) { ++i; }

		///� ���� ����� �� ������������� ������ ������� � ���� �� ����� ������ ���������, �� ������ ��� ������.
		///���� �� �� ����� ������� �����, �� �� ��� ����� � �������� ������ s1;
		///����� ����� ������� �������� ������� � ��������� if; 
		for (; i < gcount;) {
			while ((s[i] != ' ') && (s[i] != '\t') && (s[i] != '\n') && (i < gcount) && (s[i] != '\0')) { s1[back] = s[i]; ++i; ++back; }
			while ((i < gcount) && ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n') || (s[i] == '\0'))) { ++i; }
			if ((s[i] != ' ') && (s[i] != '\t') && (s[i] != '\n') && (i < gcount) && (s[i] != '\0')) { s1[back] = ' ';  ++back; }
		}

		gcount = back;/// back - �������� s1, �� ���� �� ������ ������� �������� ���������� � �����.
		tablo(out, gcount, Ncount, tab);
		out.write(s1, gcount);///���������� ����� � ����.
		out << '\n';
	}


	delete[] s;
	delete[] s1;
	in.close();
	out.close();
	system("pause");
	return 0;
}