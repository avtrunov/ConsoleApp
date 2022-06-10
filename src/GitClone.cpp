#include "Chatbot/GitClone.h"

GitClone::~GitClone()
{
	git_repository_free(repo);
}

bool GitClone::Execute(const std::wstring& url,const std::wstring& path) noexcept
{
	const auto url8 = utility::conversions::utf16_to_utf8(url);
	const auto path8 = utility::conversions::utf16_to_utf8(L"git\\" + path);// добавить GIT_PATH

	if (git_clone(&repo, url8.c_str(), path8.c_str(), nullptr))
	{
		const git_error* err = git_error_last();
		errMessage += utility::conversions::to_string_t(std::string(err->message));
		return false;
	}
	return true;
}

//добавить возвращение  git_repository_path()