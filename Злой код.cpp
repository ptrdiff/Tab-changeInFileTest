#include <iostream>
#include <fstream>

//функция для расстановки пробелов в начале каждой строки. Так выполняется табуляция.
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
		std::cout << "По какому краю выровнить?(L,R,C) ";
		std::cin >> tab;
		std::cout << "Ширина поля ввода: ";
		std::cin >> Ncount;
	}
	char *s = new char[Ncount];///строка для считывания
	char *s1 = new char[Ncount];///строка для буфера
	int gcount;
	int i;
	int back;

	while (in.peek() != EOF) {

		///в случае, если нам подали размер поля не такой же как в файле, то мы закрываем всё и заканчиваем программу.
		if (!(in.getline(s, Ncount))) {
			std::cout << "Неверная ширина поля ввода!" << std::endl;
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

		///в считанной строке перемещаемся к первому символу не являющемуся знаком табуляции.
		while ((i < gcount) && ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n') || (s[i] == '\0'))) { ++i; }

		///в этом цикле мы рассматриваем каждый элемент и если он равен знакам табуляции, то просто идём дальше.
		///если же он равен символу слова, то мы его пишем в буферную строку s1;
		///чтобы между словами остались пробелы я использую if; 
		for (; i < gcount;) {
			while ((s[i] != ' ') && (s[i] != '\t') && (s[i] != '\n') && (i < gcount) && (s[i] != '\0')) { s1[back] = s[i]; ++i; ++back; }
			while ((i < gcount) && ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n') || (s[i] == '\0'))) { ++i; }
			if ((s[i] != ' ') && (s[i] != '\t') && (s[i] != '\n') && (i < gcount) && (s[i] != '\0')) { s1[back] = ' ';  ++back; }
		}

		gcount = back;/// back - итератор s1, по нему мы узнаем сколько символов записалось в буфер.
		tablo(out, gcount, Ncount, tab);
		out.write(s1, gcount);///записываем буфер в файл.
		out << '\n';
	}


	delete[] s;
	delete[] s1;
	in.close();
	out.close();
	system("pause");
	return 0;
}