#include "../header files/tutorial.h"

Tutorial::Tutorial(const std::string &title, const std::string &presenter, Duration duration, int likes, const std::string &link){
    if(!(Validator::validate_duration(duration)))
        throw TutorialException("\nNot a valid duration!\n\n");
    if(!(Validator::validate_likes(likes)))
        throw TutorialException("\nNot a valid number of likes!\n\n");
    this->title = title;
    this->presenter = presenter;
    this->duration = duration;
    this->likes = likes;
    this->link = link;
}
void Tutorial::update(const std::string &new_title, const std::string &new_presenter, Duration new_duration, int new_likes,
                      const std::string &new_link) {
    this->title = new_title;
    this->presenter = new_presenter;
    this->duration = new_duration;
    this->likes = new_likes;
    this->link = new_link;
}

std::string Tutorial::to_string() {
    std::string s;
    s += this->title + "|";
    s += this->presenter + "|";
    if(this->duration.seconds >= 10)
        s += std::to_string(this->duration.minutes) + ":" + std::to_string(this->duration.seconds) + "|Likes:";
    else
        s += std::to_string(this->duration.minutes) +  ":0" + std::to_string(this->duration.seconds) + "|Likes:";

    s += std::to_string(this->likes) + "|";
    s += this->link;
    return s;
}


// example of line in file:
// Title,Presenter,Duration,Likes,Link

std::istream & operator>>(std::istream & is, Tutorial & t)
{
    if (is.eof())
        is.setstate(std::ios_base::failbit); // operator bool returns true for eof => enforce false to terminate the loop
    else
    {
        getline(is, t.title, ',');
        getline(is, t.presenter, ',');
        std::string min, sec;
        getline(is, min, ':');
        getline(is, sec, ',');
        Duration d{std::stoi(min), std::stoi(sec)};
        t.duration = d;
        std::string lik;
        getline(is, lik, ',');
        t.likes = std::stoi(lik);
        getline(is, t.link, '\n');
    }
    return is;
}

// example of line in file:
// Title,Presenter,Duration,Likes,Link

std::ostream & operator<<(std::ostream & os, const Tutorial & t)
{
    os << t.title << "," << t.presenter << "," << t.duration.minutes << ":" << t.duration.seconds << "," << t.likes <<
    ',' << t.link;
    return os;
}
