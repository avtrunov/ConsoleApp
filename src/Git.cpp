#include "Chatbot/Git.h"

Git::Git() : errMessage(L"")
{
	git_libgit2_init();
}

Git::~Git()
{
	git_libgit2_shutdown();
}

std::wstring Git::ErrorMessage() const noexcept
{
	return errMessage;
}