#include "GraphColoringheader.h"
#include <filesystem>
#include <fstream>
namespace  fs = std::filesystem;


vector<string> filesindir(const fs::path& dir) {
	vector<string> files;
	for (auto& p : fs::recursive_directory_iterator(dir)) {
		if (fs::is_regular_file(p)) {
			files.push_back(p.path().string());
		}
	}
	return files;
}

void fill_result(int& min_color_numb, ofstream& out, string& file_name) {
	out << file_name << " ";
	out << min_color_numb << '\n';
}