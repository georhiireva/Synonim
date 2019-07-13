#include <iostream>
#include <map>
#include <string>
#include "Synonims.h"
#include <cctype>

struct CommandProcess {
	Synonims* syn;
	CommandProcess(Synonims* syn) {
		this->syn = syn;
	}
	virtual bool process(std::string &a, std::string &b) = 0;
};

struct Exit : CommandProcess {
	Exit(Synonims* syn) : CommandProcess(syn){}
	bool process(std::string &a, std::string &b) override { return false; }
};

struct Add : CommandProcess {
	Add(Synonims* syn) : CommandProcess(syn){}
	bool process(std::string &a, std::string &b) override {
		syn->add(a, b);
		return true;
	}
};

struct Check : CommandProcess {
	Check(Synonims* syn) : CommandProcess(syn){}
	bool process(std::string &a, std::string &b) override {
		syn->check(a, b);
		return true;
	}
};

struct Delete : CommandProcess {
	Delete(Synonims* syn) : CommandProcess(syn){}
	bool process(std::string &a, std::string &b) override {
		syn->remove(a, b);
		return true;
	}
};

void run(std::string filename) {
	Synonims syn(filename);
	std::map<std::string, CommandProcess*> menu;
	Exit _exit(&syn);
	Add _add(&syn);
	Check _check(&syn);
	Delete _delete(&syn);
	menu["exit"] = &_exit;
	menu["add"] = &_add;
	menu["check"] = &_check;
	menu["delete"] = &_delete;

	bool proceed = true;
	while (proceed) {
		std::string command, a, b;
		std::cout << "Enter command (EXIT, ADD, CHECK OR DELETE)(Введите команду и пару синонимов)" << std::endl;
		std::cin >> command >> a >> b;
		std::transform(command.begin(), command.end(), command.begin(), tolower);
		auto process_it = menu.find(command);
		if (menu.end() == process_it) {std::cout << "Unknown command. Try again" << std::endl; continue; }

		proceed = process_it->second->process(a, b);
	}
}

int main(int argc, char** argv) {
	setlocale(LC_ALL, "Russian");
	try {
		if (argc< 1) throw std::string("Не указан путь к файлу");
	}
	catch (std::string str) {
		std::cout << str << std::endl;
		return 0;
	}
	
	std::string filename = argv[1];
	if (filename.empty()) std::cout << "empty" << std::endl;
	std::cout << filename << std::endl;
	run(filename);
	return 0;
}