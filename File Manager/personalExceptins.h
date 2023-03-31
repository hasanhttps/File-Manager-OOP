#pragma once


class BadDirCreate :public exception {
private:
	string _message;
public:
	BadDirCreate() : _message("This directory couldn't be created. Make sure the path is correct.") {};
	explicit BadDirCreate(string message) : _message(message) {};
	char const* what() const override { return _message.data(); }
};
class BadDirOpen :public exception {
private:
	string _message;
public:
	BadDirOpen() : _message("This directory couldn't be opened. Make sure that this directory exists.") {};
	explicit BadDirOpen(string message) : _message(message) {};
	char const* what() const override { return _message.data(); }
};
class BadDirRemove :public exception {
private:
	string _message;
public:
	BadDirRemove() : _message("This directory couldn't be removed. Make sure that this directory exists.") {};
	explicit BadDirRemove(string message) : _message(message) {};
	char const* what() const override { return _message.data(); }
};
class BadDirMove :public exception {
private:
	string _message;
public:
	BadDirMove() : _message("This directory couldn't be moved. Make sure that each of this directories exist.") {};
	explicit BadDirMove(string message) : _message(message) {};
	char const* what() const override { return _message.data(); }
};
class BadDirRename :public exception {
private:
	string _message;
public:
	BadDirRename() : _message("This directory couldn't be renamed. Make sure that each of this directories exist.") {};
	explicit BadDirRename(string message) : _message(message) {};
	char const* what() const override { return _message.data(); }
};

