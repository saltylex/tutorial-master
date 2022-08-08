#pragma once

#include "repo.h"
#include "handlers.h"
#include "tutorial.h"
#include <string>

class Service {

public:
    Handler* h = nullptr;
    Repo &r;
    Repo &wl;
    Repo &queue;
    Service(Repo &rep, Repo &watch, Repo &kiueue);

    void
    add_to_repo(const std::string &title, const std::string &presenter, Duration duration, int likes, const std::string &link);

    void remove_from_repo(const std::string &link);

    void update_in_repo(const std::string &title, const std::string &presenter, Duration duration, int likes,
                        const std::string &link, const std::string &linky);

    Repo search_in_repo(const std::string &pres);

    void add_to_watch_list(const Tutorial tut);

    void remove_from_watch_list(int pos);

    unsigned int get_size() const { return this->r.get_size(); }

    Repo &get_repo() { return this->r; }

    Repo &get_watch_list() { return this->wl; }

    Repo &get_queue() { return this->queue; }

    Handler *get_handler() { return this->h; };

    void save(std::vector<Tutorial> v) { this->h->save(v); }

    ~Service() { delete this->h; }
};

