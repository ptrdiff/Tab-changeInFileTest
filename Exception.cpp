#include <iostream>
#include <fstream>

void exception(std::ifstream &in, std::ofstream &out, int Ncount)
{
	char *s = new char[Ncount + 1];
	int gcount;
	int i = 0;
	int tospice = 0;
	bool flag;
	while (in.peek() != EOF) {
		in.read(s, Ncount);
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
}