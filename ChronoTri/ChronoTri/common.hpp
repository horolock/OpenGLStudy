#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

std::string getVertName(const std::string& basename) {
	return basename + ".vert";
}

std::string getFragName(const std::string& basename) {
	return basename + ".frag";
}

std::string loadFile(const std::string& filename) {
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Error: Cannot Open\"" << filename << "\"\n";
		return "";
	}

	std::stringstream buffer;

	buffer << file.rdbuf();

	return buffer.str();
}