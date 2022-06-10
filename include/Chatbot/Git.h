#pragma once
#include <git2.h>
#include <cpprest/json.h>

class Git
{
protected:
	std::wstring errMessage;
public:
	Git();
	Git(const Git&) = delete;
	Git& operator=(const Git&) = delete;
	virtual ~Git();

	std::wstring ErrorMessage() const noexcept;
};