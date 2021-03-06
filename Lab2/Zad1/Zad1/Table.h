#pragma once
#include <string>


class Table
{
private:
	std::string name;
	int size;
	int* array;
public:
	// constructors
	Table(std::string& name, int array_size);
	Table();
	Table(const Table& other);
	// destructor
	~Table();
	// methods
	void print_info();
	void set_name(std::string& new_name);
	bool set_size(int new_size);
	Table* clone();
};