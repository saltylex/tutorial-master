#pragma once
#include "tutorial.h"
#include <vector>

class Handler {
public:
    virtual void save(std::vector<Tutorial> v) = 0;
};

class CSVHandler : public Handler {
public:
    void save(std::vector<Tutorial> v) override;
};

class HTMLHandler : public Handler {
public:
    void save(std::vector<Tutorial> v) override;
};