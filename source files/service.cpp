#include "../header files/service.h"
#include <cstring>

Service::Service(Repo &rep, Repo &watch, Repo &kiueue) : r{rep}, wl{watch}, queue{kiueue} {}

void Service::add_to_repo(const std::string &title, const std::string &presenter, Duration duration, int likes,
                          const std::string &link) {
    Tutorial t{title, presenter, duration, likes, link};
    this->r.add(t);
}

void Service::update_in_repo(const std::string &title, const std::string &presenter, Duration duration, int likes,
                             const std::string &link, const std::string &linky) {
    this->get_repo().get_at(this->get_repo().get_index(link)).update(title, presenter, duration, likes, linky);
}

void Service::remove_from_repo(const std::string &link) {
    Tutorial t = this->r.get_at(this->r.get_index(link));
    this->r.remove(t);
}

Repo Service::search_in_repo(const std::string &pres) {
    Repo thing;
    for (const Tutorial &i: this->get_repo().get_data()) {
        if (i.get_presenter().find(pres) != std::string::npos)
            thing.add(i);
    }
    return thing;
}

void Service::add_to_watch_list(const Tutorial tut) {
    this->wl.add(tut);
}

void Service::remove_from_watch_list(int pos) {
    this->wl.remove(this->wl.get_at(pos));
}