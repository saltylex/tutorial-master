#include <string>
#include <iostream>

#pragma once

class TutorialException : public std::exception {

public:

    explicit TutorialException(const std::string &msg) : msg_(msg) {}

    ~TutorialException() override = default;

    std::string getMessage() const { return (msg_); }

private:
    std::string msg_;
};

struct Duration {
    int minutes;
    int seconds;
};
typedef struct Duration Duration;


class Validator {
public:
    static bool validate_duration(Duration d) {
        return d.minutes >= 0 && d.minutes <= 59 && d.seconds >= 0 && d.seconds <= 59;
    }

    static bool validate_likes(int lick) { return lick >= 0; }

};

class Tutorial {
private:
    std::string title;
    std::string presenter;
    Duration duration;

    std::string link;

public:
    bool operator==(const Tutorial &tut) const {
        return (title == tut.title)
               && (presenter == tut.presenter)
               && (duration.minutes == tut.duration.minutes) && (duration.seconds == tut.duration.seconds) &&
               (link == tut.link);
    }

    int likes;

    Tutorial() : title{""}, presenter{""}, duration{0, 0}, likes{0}, link{""} {};

    Tutorial(const std::string &title, const std::string &presenter, Duration duration, int likes,
             const std::string &link);


    std::string get_title() const { return this->title; }

    std::string get_presenter() const { return this->presenter; }

    Duration get_duration() const { return this->duration; }

    int get_likes() const { return this->likes; }

    std::string get_link() const { return this->link; }

    void update(const std::string &new_title, const std::string &new_presenter, Duration new_duration, int new_likes,
                const std::string &new_link);


    std::string to_string();

    friend std::istream &operator>>(std::istream &is, Tutorial &t);

    friend std::ostream &operator<<(std::ostream &os, const Tutorial &t);

};