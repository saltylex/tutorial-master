#pragma once

#include <algorithm>
#include <vector>
#include "dynamicArray.h"
#include "tutorial.h"
class RepoException : public std::exception {

public:

    explicit RepoException(const std::string& msg) : msg_(msg) {}
    ~RepoException() override = default;

    std::string getMessage() const {return(msg_);}
private:
    std::string msg_;
};


class Repo {
private:
    std::vector<Tutorial> data;
public:
    void add(const Tutorial &t);
    void remove(const Tutorial &t);
    bool find(const std::string &linky);

    std::vector<Tutorial> get_data() const { return this->data; };
    unsigned int get_size() { return this->data.size(); }
    int get_index(const std::string &link);
    Tutorial &get_at(int index);

};