#pragma once
#include <exception>
#include <string>

class Validation_exception : public std::exception {
private:
	std::string message;
public:
	Validation_exception(std::string message) : message{ message } {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};

class Repository_entity_not_found_exception : public std::exception {
private:
	std::string message;
public:
	Repository_entity_not_found_exception(std::string message) : message{ message } {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};

class Repository_duplicate_exception : public std::exception {
private:
	std::string message;
public:
	Repository_duplicate_exception(std::string message) : message{ message } {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};
