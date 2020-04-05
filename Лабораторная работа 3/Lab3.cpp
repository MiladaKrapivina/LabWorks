#include <iostream>
#include "libbmp.h"

using namespace std;

bool getCharR(BmpImg* img, int x, int y, int& count, int& toByte) {
	toByte = toByte + (img->red_at(x, y) % 2) * pow(2, count);
	return true;
}

bool getCharG(BmpImg* img, int x, int y, int& count, int& toByte) {
	toByte = toByte + (img->green_at(x, y) % 2) * pow(2, count);
	return true;
}

bool getCharB(BmpImg* img, int x, int y, int& count, int& toByte) {
	toByte = toByte + (img->blue_at(x, y) % 2) * pow(2, count);
	return true;
}

bool check(int& count, int& toByte) {

	if (count == 0)
	{
		if (char(toByte) == '\0') return false;

		std::cout << char(toByte);

		count = 8;
		toByte = 0;
	}
	return true;
}

int main()
{
	BmpImg img;
	img.read("pic4.bmp");
	int count = 7;
	int toByte = 0;

	for (int i = img.get_width() - 1; i >= 0; i--)         // KEY   11r 11g 11b 10r 10g 10b 01r 01g
		for (int j = img.get_height() - 1; j >= 0; j--)
		{
			if (!(getCharR(&img, i, j, count, toByte)&& check(count, toByte))) return 0;
			count--;

			if (!(getCharG(&img, i, j, count, toByte) && check(count, toByte))) return 0;
			count--;

			if (!(getCharB(&img, i, j, count, toByte) && check(count, toByte))) return 0;
			count--;
		}
}
