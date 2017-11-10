#include <iostream>
#include <fstream>

inline void tablo(std::ofstream  &out,int &tospice, int Ncount, char tab) {
	out << '\n';
	int rcount;
	if (tab == 'L') rcount = 0;
	if (tab == 'R') rcount = Ncount - tospice;
	if (tab == 'C') rcount = (Ncount - tospice)/2;
	for (int i = 0; i < rcount; ++i) out << "1";
	tospice = 0;
}

int main()
{
	setlocale(0, "Russian");

	std::ifstream  in("text.txt");
	std::ofstream  out("textout.txt");
	char tab = ' ';
	int Ncount = -1;
	while ((tab != 'L') && (tab != 'C') && (tab != 'R') || (Ncount < 0)) {
		std::cout << "L,C,R?";
		std::cin >> tab;
		std::cout << "N?";
		std::cin >> Ncount;
	}
	char *s = new char[Ncount+1];
	int gcount;
	int i = 0;
	int tospice = 0;
	bool flag;

	while(in.peek() != EOF){
	in.read(s,Ncount);
	gcount = in.gcount();
	flag = 0;
		for (; i < gcount;) {
			while ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n')) { ++i; }
			while ((s[i] != ' ') && (s[i] != '\t') && (i < gcount) && (s[i] != '\n')) { 
				++tospice;
				if (tospice == Ncount) { out << '\n'; tospice = 0; }
				out.write(s + i, 1); 
				++i;
				if (flag == 0)flag = 1;
			}
			if ((flag == 1) && (i < gcount) && (s[i + 1] != '\n') && (s[i - 1] != '\n')) { 
				++tospice;
				if (tospice == Ncount) { out << '\n'; tospice = 0; break; }
				out << " ";
				flag = 0;  
			}
		}
		i = 0;
}


	delete[] s;
	in.close();
	out.close();
	system("pause");
	return 0;
}