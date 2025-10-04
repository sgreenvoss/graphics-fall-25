#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;
string FILE_PATH = "";

struct Pixel {
	unsigned char r, g, b;

public:
	Pixel(unsigned char red = '\0', unsigned char green = '\0', unsigned char blue = '\0') {
		r = red;
		g = green;
		b = blue;
	}

	void color(int red, int green, int blue) {
		r = (unsigned char)red;
		g = (unsigned char)green;
		b = (unsigned char)blue;
	}

};

struct Image {
	string file_name;
	int WIDTH;
	int HEIGHT;
	int size;
	Pixel* pixels;

public:
	Image(string name, int w, int h) {
		file_name = name;
		WIDTH = w;
		HEIGHT = h;
		size = WIDTH * HEIGHT;
		pixels = new Pixel[size];
	}

	string pnmHeader() {
		string width = std::to_string(WIDTH);
		string height = std::to_string(HEIGHT);
		string out = "P6\n" + width + " " + height + "\n255\n";

		return out;
	}

	void writePlainImage(int color) {
		// this is for testing purposes and should produce a plain color.
		ofstream file_out;
		file_out.open(file_name);
		file_out << pnmHeader();
		char ccolor = static_cast<char>(color);

		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				file_out << ccolor;
				file_out << ccolor;
				file_out << ccolor;
			}
		}
		file_out.close();
	}

	void assignPixels(int colMin, int colMax, int rowMin, int rowMax,
		unsigned char R, unsigned char G, unsigned char B) {
		for (int i = rowMin; i < rowMax; i++) {
			for (int j = colMin; j < colMax; j++) {
				int index = (i * WIDTH) + j;
				pixels[index].r = R;
				pixels[index].g = G;
				pixels[index].b = B;
			}
		}
	}

	void writeFromVector() {
		cout << "Attempting to open the file at " << file_name.c_str() << endl;
		FILE* f = fopen(file_name.c_str(), "wb");

		// handle the case if the file was not found or opened.
		if (f == nullptr) {
			cerr << "File path invalid, exiting." << endl;
			exit(1);
		}

		// write the default header to the pnm file
		string data = pnmHeader();
		fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);

		// write all of the pixels to the file
		fwrite(pixels, sizeof(Pixel), size, f);
		fclose(f);

	}

};


int main() {
	cout << "Creating image object." << endl;
	Image image(FILE_PATH + "proj1A_out.pnm", 300, 300);

	// Top three
	image.assignPixels(0, 100, 0, 100, 0, 0, 0);
	image.assignPixels(100, 200, 0, 100, 128, 128, 128);
	image.assignPixels(200, 300, 0, 100, 255, 255, 255);

	// middle three
	image.assignPixels(0, 100, 100, 200, 255, 0, 0);
	image.assignPixels(100, 200, 100, 200, 0, 255, 0);
	image.assignPixels(200, 300, 100, 200, 0, 0, 255);

	// bottom three
	image.assignPixels(0, 100, 200, 300, 255, 0, 255);
	image.assignPixels(100, 200, 200, 300, 0, 255, 255);
	image.assignPixels(200, 300, 200, 300, 255, 255, 0);

	cout << "All pixels assigned." << endl;

	image.writeFromVector();

	cout << "All pixels written." << endl;

	return 0;
}
