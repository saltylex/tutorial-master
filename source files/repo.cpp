#include "../header files/repo.h"

bool Repo::find(const std::string &linky) {
    return std::any_of(this->data.begin(), this->data.end(),
                       [&linky](const Tutorial &i) { return linky == i.get_link(); });
}

void Repo::add(const Tutorial &c) {
    if(find(c.get_link()))
        throw RepoException("\nTutorial already exists!\n\n");
    this->data.push_back(c);
}

void Repo::remove(const Tutorial &t) {
    auto it = std::find(this->data.begin(), this->data.end(), t);
    if(it == data.end())
        throw RepoException("\nTutorial does not exist, therefore it can't be removed!\n\n");
    this->data.erase(it);
}

Tutorial &Repo::get_at(int index) {
    return this->data[index];
}

int Repo::get_index(const std::string &link) {
    auto x = 0;
    for (const Tutorial &i: this->data) {
        if (link == i.get_link()) {
            return x;
        }
        x++;
    }
    return -1;
}
