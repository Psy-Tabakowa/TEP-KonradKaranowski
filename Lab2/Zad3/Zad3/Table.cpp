#include <iostream>
#include "Table.h"
#include "constans.h"


Table::Table(std::string& name, int array_size) :
	name(name),
	size(array_size <= 0 ? 0 : array_size)
{
	if (size == 0)
	{
		array = NULL;
	}
	else
	{
		array = new int[size];
	}
	std::cout << "Created with specified parameters: " << name << std::endl;
}

Table::Table() :
	name(DEFAULT_NAME),
	size(DEFAULT_LENGTH)
{
	if (size == 0)
	{
		array = NULL;
	}
	else
	{
		array = new int[size];
	}
	std::cout << "Created with default parameters: " << name << std::endl;
}

Table::Table(const Table& other) :
	name(other.name + "_copy"),
	size(other.size)
{
	if (size == 0)
	{
		array = NULL;
	}
	else
	{
		array = new int[size];
		for (int i = 0; i < size; i++)
		{
			array[i] = other.array[i];
		}
	}
	std::cout << "Created copy: " << name << std::endl;
}

Table::Table(std::string& name, int array_size, int* array) :
	name(name + "_concated"),
	size(array_size),
	array(array)
{
	std::cout << "Created using concatenation" << std::endl;
}

Table::~Table()
{
	if (array != NULL)
	{
		delete[] array;
	}
	std::cout << "Deleted object with name: " << name << std::endl;
}

void Table::print_info()
{
	std::cout << name << " " << size << " " << this << std::endl;
}

void Table::set_name(std::string& new_name)
{
	name = new_name;
}

bool Table::set_size(int new_size)
{
	if (new_size < 0)
	{
		std::cout << "Array size has to be positive." << std::endl;
		return false;
	}
	int* new_array = new int[new_size];
	if (array != NULL)
	{	
		for (int i = 0; i < std::min(size, new_size); i++)
		{
			new_array[i] = array[i];
		}
		delete[] array;
	}
	size = new_size;
	array = new_array;
	return true;
}

void Table::set_value_at(int offset, int new_value)
{
	if ((offset >= size) || (offset < 0))
	{
		std::cout << "Offset has to be lesser than array size and greater than -1" << std::endl;
		return;
	}
	array[offset] = new_value;
}

void Table::print()
{
	std::cout << "Array with pointer: " << array << " and size: " << size << std::endl;
	std::cout << '[';
	if (array == NULL)
	{
		std::cout << "NULL";
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << array[i] << ' ';
		}
	}
	std::cout << ']' << std::endl;
}


Table* Table::clone()
{
	return new Table(*this);
}



Table Table::operator+(const Table& other)
{
	int new_size = size + other.size;
	int* new_array;
	if (new_size == 0)
	{
		new_array = NULL;
	}
	else
	{
		new_array = new int[new_size];
		for (int i = 0; i < size; i++)
		{
			new_array[i] = array[i];
		}
		for (int i = 0; i < other.size; i++)
		{
			new_array[i + size] = other.array[i];
		}
	}
	return Table(name, new_size, new_array);
}


Table operator+(int element, const Table& table)
{
	int new_size = table.size + 1;
	int* new_array = new int[new_size];
	new_array[0] = element;
	for (int i = 0; i < table.size; i++)
	{
		new_array[i + 1] = table.array[i];
	}
	std::string new_name = "Created with friend";
	return Table(new_name, new_size, new_array);
}

std::ostream& operator<<(std::ostream& os, const Table& table)
{
	os << '[';
	for (int i = 0; i < table.size; i++)
	{
		 os << table.array[i] << " ";
	}
	os << ']';
	return os;
}
