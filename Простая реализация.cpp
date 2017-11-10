#include <iostream>
#include <fstream>

inline void tablo(std::ofstream  &out,int gcount, int Ncount, char tab) {
	int rcount;
	if (tab == 'L') rcount = 0;
	if (tab == 'R') rcount = Ncount - gcount ;
	if (tab == 'C') rcount = (Ncount - gcount)/2;
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
	char *s = new char[Ncount+1];
	int gcount;
	int i = 0;

	while(in.peek() != EOF){
	in.getline(s, Ncount, '\n'); 
	gcount = in.gcount();
	while ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n')) { ++i; }
	tablo(out, gcount-i, Ncount, tab);
	out.write(s+i, gcount-i);
	out << '\n';
	i = 0;
}


	delete[] s;
	in.close();
	out.close();
	system("pause");
	return 0;
}