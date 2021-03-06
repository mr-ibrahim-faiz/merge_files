#include<iostream>
using std::cout;
using std::endl;

#include<string>
using std::string;

#include<fstream>
using std::ios;
using std::fstream;

#include<windows.h>

#include<filesystem>
using namespace std::experimental::filesystem::v1;

// creates file if it doesn't exist
inline void create_file_if(const string& filename) {
	fstream file(filename, ios::in);
	if (file.is_open());
	else file.open(filename, ios::out);
	file.close();
}

// displays help
inline void display_help() {
	cout << "This program merges the text files of the current directory into an output file.\n";
}

int main(int argc, char* argv[]) {
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	const string output { "output.txt" };
	create_file_if(output);

	if (argc == 1) {
		fstream dst(output, ios::app);

		if (dst.is_open()) {

			for (directory_iterator it(current_path()), end; it != end; ++it) {
				path current = it->path();
				string input = current.filename().string();

				if (current.has_extension() && current.extension() == ".txt" && input != output) {
					fstream src(input, ios::in);
					if (src.is_open()) {
						dst << "[ " << input << " ]\n\n";
						if(src.rdbuf() != nullptr)
							dst << src.rdbuf() << "\n\n" << std::flush;
						if (!dst) dst.clear();
						src.close();
					}
					else cout << "Error: unable to open " << input << '\n';
				}
			}
			dst.close();
		}
		else cout << "Error: unable to open " << output << '\n';
	}
	else display_help();

	return 0;
}