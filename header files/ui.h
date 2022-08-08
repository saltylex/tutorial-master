#include "service.h"
#pragma once
class UI {
public:
    UI(const Service& service);

    void start_ui();

private:
    void generate();
    void read_data();
    void write_data();
    Service service;
};