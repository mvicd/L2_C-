#pragma once
#include <iostream>

template <class T>
class Set {
	int* arr;
	size_t size;
public:
	Set() : arr(nullptr), size(0) {}
	Set(size_t count);
	Set(int* new_arr, size_t count) : arr(new_arr), size(count) {}
	Set(const Set<T>& set);
	~Set();
	size_t get_size();
	Set<T> operator + (const Set<T>& set);
	Set<T> operator - (const Set<T>& set);

	void operator + (const T add_num);
	Set<T>& operator += (const T add_num);
	void operator - (const T del_num);
	Set<T>& operator -= (const T del_num);

	int& operator [] (const size_t index);
	int operator [] (const size_t index) const;
	bool operator == (const Set<T>& set);
	bool operator != (const Set<T>& set);
	Set<T>& operator = (const Set<T>& set);

	Set intersection(const Set<T>& set);
	bool contain_num(const T number);
	template <typename T> friend std::ostream& operator<< (std::ostream& out, const Set<T>& set);
};



template <>
class Set<std::pair<int, double>> {

	int* arr;
	size_t size;
public:
	Set() : arr(nullptr), size(0) {}
	Set(size_t count);
	Set(int* new_arr, size_t count) : arr(new_arr), size(count) {}
	Set(const Set<std::pair<int, double>>& set);
	~Set();
	size_t get_size();
	Set<std::pair<int, double>> operator + (const Set<std::pair<int, double>>& set);
	Set<std::pair<int, double>> operator - (const Set<std::pair<int, double>>& set);

	void operator + (const std::pair<int, double> add_num);
	Set<std::pair<int, double>>& operator += (const std::pair<int, double> add_num);
	void operator - (const std::pair<int, double> del_num);
	Set<std::pair<int, double>>& operator -= (const std::pair<int, double> del_num);

	int& operator [] (const std::pair<int, double> index);
	int operator [] (const std::pair<int, double> index) const;
	bool operator == (const Set<std::pair<int, double>>& set);
	bool operator != (const Set<std::pair<int, double>>& set);
	Set<std::pair<int, double>>& operator = (const Set<std::pair<int, double>>& set);

	Set<std::pair<int, double>> intersection(const Set<std::pair<int, double>>& set);
	bool contain_num(const int number);
	template <> friend std::ostream& operator<< (std::ostream& out, const Set<std::pair<int, double>>& set);


};


template <>
class Set<std::string> {

	int* arr;
	size_t size;
public:
	Set() : arr(nullptr), size(0) {}
	Set(size_t count);
	Set(int* new_arr, size_t count) : arr(new_arr), size(count) {}
	Set(const Set<std::string>& set);
	~Set();
	size_t get_size();
	Set<std::string> operator + (const Set<std::string>& set);
	Set<std::string> operator - (const Set<std::string>& set);

	void operator + (const std::string add_num);
	Set<std::string>& operator += (const std::string add_num);
	void operator - (const std::string del_num);
	Set<std::string>& operator -= (const std::string del_num);

	int& operator [] (const size_t index);
	int operator [] (const size_t index) const;
	bool operator == (const Set<std::string>& set);
	bool operator != (const Set<std::string>& set);
	Set<std::string>& operator = (const Set<std::string>& set);

	Set<std::string> intersection(const Set<std::string>& set);
	bool contain_num(const std::string number);
	template <> friend std::ostream& operator<< (std::ostream& out, const Set<std::string>& set);


};

