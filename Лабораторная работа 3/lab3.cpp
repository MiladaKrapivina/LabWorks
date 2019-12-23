#include <iostream>
#include <ostream>
#include <cmath>
#include <vector>
#include "libbmp.h"


using namespace std;


enum canal {
	RED,
	GREEN,
	BLUE
};

char to_char(bool arr[8]) {
	int sum = 0;
	for (int i = 0; i < 8; i++) {
		sum += pow(2, i) * arr[i];
	}

	char res = sum;
	return res;
}

bool get_bit(int x, int y, BmpImg img) {
	static int len = 0;
	int color_num;
	static canal color = RED;
	static bool temp[8] = {};

	switch (color) {
	case RED:
		color_num = int(img.red_at(x, y)) % 2;
		break;
	case GREEN:
		color_num = int(img.green_at(x, y)) % 2;
		break;
	case BLUE:
		color_num = int(img.blue_at(x, y)) % 2;
		break;
	}
	
	temp[7 - len] = color_num;
	len++;

	if (len == 8) {
		char temp_char = to_char(temp);
		if (temp_char == char(0)) {
			cout << endl;
			len = 0;
			color = static_cast<canal> ((color + 1) % 3);
			return false;
		}
		else {
			cout << temp_char;
			len = 0;
			color = static_cast<canal> ((color + 1) % 3);
			return true;
		}
	}
	color = static_cast<canal> ((color + 1) % 3);
	return true;
}

int main() {
	BmpImg img;
	img.read("pic4.bmp");

	const int x_max = 608, y_max = 507;
	for (int x_pos = x_max - 1; x_pos > -1; x_pos --) {
		for (int y_pos = y_max - 1; y_pos > -1; y_pos --) {
			if (!get_bit(x_pos, y_pos, img)) return 0;
			if (!get_bit(x_pos, y_pos, img)) return 0;
			if (!get_bit(x_pos, y_pos, img)) return 0;
		}
	}
	return 0;
}