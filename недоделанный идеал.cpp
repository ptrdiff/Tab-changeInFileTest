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
		std::cout << "L,C,R?";
		std::cin >> tab;
		std::cout << "N?";
		std::cin >> Ncount;
	}
	char *s = new char[Ncount+1];
	int gcount;
	int i = 0;
	int tospice = 0;
	bool flag, flag2 = 1;

	while(in.peek() != EOF){
	in.getline(s,Ncount,'\n');
	gcount = in.gcount();
	flag = 0;
	if (flag2 == 1) { tablo(out, gcount, Ncount, tab); flag2 = 0; }
		for (; i < gcount;) {
			while ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n')) { ++i; }
			while ((s[i] != ' ') && (s[i] != '\t') && (i < gcount) && (s[i] != '\n')) { 
				out.write(s + i, 1); 
				++tospice;
				if (tospice == Ncount) { out << '\n'; tospice = 0; flag2 = 1; tablo(out, tospice, Ncount, tab); }
				++i;
				if (flag == 0)flag = 1;
			}
			if ((flag == 1) && (i < gcount) && (s[i + 1] != '\n') && (s[i - 1] != '\n')) { 
				out << " ";
				++tospice;
				if (tospice == Ncount) { out << '\n'; tospice = 0; flag2 = 1; tablo(out, tospice, Ncount, tab); }
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