#pragma once
#include <iostream>
#include <map>
#include <string>
#include "Synonims.h"
#include <algorithm>
#include <memory>
#include <fstream>
#include <vector>

class Synonims
{
public:
	
	Synonims(std::string filename) {
		dictionary = new (std::nothrow) std::map<std::string, std::string>();
		this->filename = filename;
		std::ifstream in_file(filename);
		if (in_file) {
			std::string f, s;
			while (!in_file.eof()) {
				in_file >> f >> s;
				dictionary->insert(make_pair(f, s));
			}
		}
		else { std::cout << "File was not read" << std::endl; }
	}

	~Synonims() {
		dictionary->clear();
		delete dictionary;
	}

	void add(std::string &a, std::string &b) {
		try {
			enter(a, b);
			if (nullptr == dictionary) throw std::string("Dictionary doesn't exist");
			dictionary->insert(make_pair(pair[0], pair[1]));
			if (!store(*dictionary)) throw std::string("PAIR WAS ADD SUCCESFULLY");
			std::cout << "PAIR WAS ADD SUCCESFULLY" << std::endl;
		}
		catch (std::string &str) {
			std::cout << str << std::endl;
		}
		catch (std::bad_alloc &e) {
			std::cout << "Memory allocation error: " << e.what() << std::endl;
		}
	}

	void check(std::string &a, std::string &b) {
		try {
			enter(a, b);
			auto key = dictionary->find(pair[0]);
			if (dictionary->end() == key) throw std::string("Pair was not found");
			if (pair[1] == key->second) std::cout << "WORDS ARE SYNONIMS" << std::endl;
			else std::cout << "WORDS ARE NOT SYNONIMS" << std::endl;
		}
		catch (std::string str){
			std::cout << str << std::endl;
		}
	}

	

	void remove(std::string &a, std::string &b) {
		enter(a, b);
		auto tmp = dictionary->find(pair[0]);
		if (tmp != dictionary->end()) {
			if (pair[1] == tmp->second) { dictionary->erase(tmp); }
			else{std::cout << "PAIR WAS NOT FOUND" << std::endl;}
		}
		else {std::cout << "PAIR WAS NOT FOUND" << std::endl;}
	}

	void setFilename(std::string filename) {
		this->filename = filename;
	}

private:
	
	void enter(std::string &a, std::string &b) {
		std::vector<std::string> tmp;
		tmp.push_back(a);
		tmp.push_back(b);
		std::sort(tmp.begin(), tmp.end());
		pair[0] = tmp.front();
		pair[1] = tmp.back();
	}

	bool store(std::map<std::string, std::string>  dictionary) {
		std::ofstream out_file(filename);
		if (!out_file) std::cout << "Creating new file" << std::endl;
		for (auto pair : dictionary) {
			out_file << pair.first << ' ' << pair.second << '\n';
		}
		return true;
	}

protected:
    std::map<std::string, std::string>* dictionary;
	std::string pair[2];
	std::string filename;
};

