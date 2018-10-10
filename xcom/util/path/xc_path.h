#ifndef TXCPATH_H
#define TXCPATH_H

#include <string>
#include <vector>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

class TXCPath {
public:
	enum path_type {
		windows_path = 0,
		posix_path = 1,
#if defined(_WIN32)
		native_path = windows_path
#else
		native_path = posix_path
#endif
	};

	TXCPath();

	TXCPath(const TXCPath &path);

	TXCPath(TXCPath &&path);

	TXCPath(const char *string);

	TXCPath(const std::string &string);

	~TXCPath();

	size_t length() const;

	bool empty() const;

	bool is_absolute() const;

	TXCPath make_absolute() const;

	bool exists() const;

	size_t file_size() const;

	bool is_directory() const;

	bool is_file() const;

	std::string extension() const;

	std::string filename() const;

	TXCPath parent() const;
    
    std::vector<TXCPath> childs() const;

	time_t creation_time() const;

	time_t last_access_time() const;

	time_t last_modified_time() const;

	time_t last_status_change_time() const;

	std::string str(path_type type = native_path) const;

	void set(const std::string &str, path_type type = native_path);

	TXCPath operator/(const TXCPath &other) const;

	TXCPath &operator=(const TXCPath &path);

	TXCPath &operator=(TXCPath &&path);

	friend std::ostream &operator<<(std::ostream &os, const TXCPath &path);

	bool operator==(const TXCPath &p) const;

	bool operator!=(const TXCPath &p) const;

	bool remove_file() const;

	bool resize_file(size_t target_length) const;

	bool create_directory() const;

	bool is_wide();

#if defined(_WIN32)
	TXCPath(const std::wstring &wstring);

	TXCPath(const wchar_t *wstring);

	std::wstring wstr(path_type type = native_path) const;

	void set(const std::wstring &wstring, path_type type = native_path);

	TXCPath &operator=(const std::wstring &str);
#endif

	static TXCPath getcwd();

protected:
	static std::vector<std::string> tokenize(const std::string &string, const std::string &delim);

protected:
	path_type _type;
	bool _wide;
	bool _absolute;
	std::vector<std::string> _path;
};

#endif //TXCPATH_H