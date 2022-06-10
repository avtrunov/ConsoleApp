#pragma once
#include "Chatbot/Git.h"

class GitClone : public Git
{
private:
	git_repository* repo;
public:
	GitClone() noexcept : Git(), repo(nullptr) {}
	GitClone(const Git&) = delete;
	GitClone& operator=(const GitClone&) = delete;
	~GitClone();

	bool Execute(const std::wstring& url, const std::wstring& path) noexcept;
};