#include <iostream>
#include <fstream>
#include "../header files/ui.h"
#include "../header files/handlers.h"
#include <cstdlib>

UI::UI(const Service &service) : service{service} {

}


void print_admin_menu() {
    std::cout << "ADMINISTRATOR MODE\n";
    std::cout << "1 - Add Tutorial\n";
    std::cout << "2 - Delete Tutorial\n";
    std::cout << "3 - Update Tutorial\n";
    std::cout << "4 - List Tutorials\n";
    std::cout << "0 - Exit\n";
}

void print_user_menu() {
    std::cout << "\nOPTIONS\n";
    std::cout << "1 - Change presenter\n";
    std::cout << "2 - Add Tutorial to Watchlist\n";
    std::cout << "3 - Next Tutorial\n";
    std::cout << "4 - Delete Tutorial from Watchlist\n";
    std::cout << "5 - See Your Watchlist\n";
    std::cout << "6 - See your Watchlist (with program)\n";
    std::cout << "0 - Exit\n";
}

int get_command() {
    int t;
    std::cout << "Enter command: ";
    std::cin >> t;
    return t;
}

void UI::generate() {
    std::string links[15] = {"https://www.youtube.com/watch?v=4qn7ep6ZpRY",
                             "https://www.youtube.com/watch?v=98jFaB305Pw",
                             "https://www.youtube.com/watch?v=lifrsyc3oM8",
                             "https://www.youtube.com/watch?v=w28BLCybd_0",
                             "https://www.youtube.com/watch?v=Kpm8rEywBDQ",
                             "https://www.youtube.com/watch?v=VoF-Qk_tWgU",
                             "https://www.youtube.com/watch?v=GiPUkGrZgkQ",
                             "https://www.youtube.com/watch?v=S1ryMTJ1KJg",
                             "https://www.youtube.com/watch?v=zuegQmMdy8M",
                             "https://www.youtube.com/watch?v=CC5ZnrE-Ok0",
                             "https://www.youtube.com/watch?v=vRLcRiEB1tc",
                             "https://www.youtube.com/watch?v=QW_S3z27c_c",
                             "https://www.youtube.com/watch?v=SKqCNqWc8nM",
                             "https://www.youtube.com/watch?v=Ubi0Flp2om0",
                             "https://www.youtube.com/watch?v=ErSmRD67pzo"};
    for (int i = 1; i <= 15; i++) {
        this->service.add_to_repo(std::to_string(i), std::to_string(i), Duration{i, i}, i, links[15 - i]);

    }
}

std::string get_mode() {
    std::string mode;
    std::cout << "~~~~~~~~~~ WELCOME TO MASTER C++! ~~~~~~~~~~\n";
    while (mode != "user" && mode != "admin") {
        std::cout << "Who are you? (user/admin): ";
        std::cin >> mode;
    }
    return mode;
}

void UI::read_data(){
    std::ifstream f("data.txt");
    while (!f.eof()) {
        Tutorial temp;
        f >> temp;
        this->service.r.add(temp);
    }
    f.close();
}

void UI::write_data(){
    std::ofstream out("data.txt");
    for (const Tutorial &t: this->service.get_repo().get_data()) {
        out << t;
        if (!(t == this->service.get_repo().get_data().back()))
            out << std::endl;
    }
    out.close();
}

void UI::start_ui() {
    read_data();
    int position = 0;
    //generate();
    std::string mode = get_mode();
    bool running = true;
    if (mode == "admin") {
        while (running) {
            print_admin_menu();
            int cmd = get_command();
            int likes, minutes, seconds;
            std::string title, presenter, link;
            Duration duration;
            switch (cmd) {
                case 0:
                    running = false;
                    std::cout << "Goodbye!";
                    break;
                case 1: {
                    std::cout << "Input the tutorial's link:";
                    std::cin >> link;
                    std::cout << "Introduce new tutorial title:";
                    std::cin >> title;
                    std::cout << "Introduce new tutorial presenter:";
                    std::cin >> presenter;
                    std::cout << "Introduce new tutorial duration:\nMinutes:";
                    std::cin >> minutes;
                    std::cout << "Seconds:";
                    std::cin >> seconds;
                    std::cout << "Introduce the number of likes:";
                    std::cin >> likes;
                    duration = Duration{minutes, seconds};

                    try {
                        this->service.add_to_repo(title, presenter, duration, likes, link);
                    }
                    catch (RepoException &a) {
                        std::cout << a.getMessage();
                    }
                    catch (TutorialException &a) {
                        std::cout << a.getMessage();
                    }
                }
                    break;
                case 2:
                    std::cout << "Introduce the tutorial's link: ";
                    std::cin >> link;
                    try {
                        this->service.remove_from_repo(link);
                    }
                    catch (RepoException &a) {
                        std::cout << a.getMessage();
                    }
                    break;
                case 3: {
                    std::cout << "Introduce the old tutorial link: ";
                    std::cin >> link;
                    std::cout << "Introduce the updated tutorial link: ";
                    std::string linky;
                    std::cin >> linky;
                    std::cout << "Introduce the updated title: ";
                    std::cin >> title;
                    std::cout << "Introduce the updated presenter: ";
                    std::cin >> presenter;
                    std::cout << "Introduce the updated minute duration: ";
                    std::cin >> minutes;
                    std::cout << "Introduce the updated seconds duration: ";
                    std::cin >> seconds;
                    std::cout << "Introduce the updated like number: ";
                    std::cin >> likes;
                    duration = Duration{minutes, seconds};
                    try {
                        this->service.update_in_repo(title, presenter, duration, likes, link, linky);
                    }
                    catch (RepoException &a) {
                        std::cout << a.getMessage();
                    }
                    catch (TutorialException &a) {
                        std::cout << a.getMessage();
                    }
                    break;
                }
                case 4: {
                    std::string s;
                    for (Tutorial &i: this->service.get_repo().get_data()) {
                        s += i.to_string();
                        s += "\n";
                    }
                    std::cout << s;
                }
                    break;
                default:
                    std::cout << "\nInvalid command!\n\n";
                    break;
            }
        }
    } else {
        std::string extension;
        while (this->service.get_handler() == nullptr) {
            std::cout << "Enter 1 for CSV or 0 for HTML: ";
            std::string input;
            std::cin >> input;
            if (input == "1") {
                extension = "csv";
                this->service.h = new CSVHandler;
            } else if (input == "0") {
                extension = "html";
                this->service.h = new HTMLHandler;
            } else {
                std::cout << "INVALID";
            }
        }
        std::cout << "Welcome, amazing person! Ready to learn?\n";
        while (running) {
            std::string pres;
            std::cout
                    << "To start browsing, please introduce the presenter's name (or 'all' for all of the tutorials):";
            std::cin >> pres;
            if (pres == "all") {
                this->service.queue = this->service.get_repo();
                running = false;
            } else {
                this->service.queue = this->service.search_in_repo(pres);
                if (this->service.queue.get_size() == 0) {
                    std::cout << "No tutorials found! Please try different search terms.\n";
                    continue;
                }
                running = false;
            }
        }
        running = true;
        while (running) {
            std::cout << "CURRENTLY WATCHING: " + this->service.get_queue().get_at(position).get_title() + " (" +
                         std::to_string(this->service.get_queue().get_size()) + " results found)";
            std::string link_opener = "xdg-open " + this->service.get_queue().get_at(position).get_link();
            system(link_opener.data());
            print_user_menu();
            int cmd = get_command();
            std::string search_string;
            switch (cmd) {
                case 0:
                    running = false;
                    std::cout << "Goodbye!";
                    break;
                case 1:
                    std::cout << "Introduce the new presenter's name (or 'all' for all of the tutorials): ";
                    std::cin >> search_string;
                    if (search_string == "all") {
                        this->service.queue = this->service.get_repo();
                    } else {
                        Repo copy_yes = this->service.queue;
                        this->service.queue = this->service.search_in_repo(search_string);
                        if (this->service.queue.get_size() == 0) {
                            std::cout << "No tutorials found! Please try different search terms.\n";
                            this->service.queue = copy_yes;
                        }
                        position = 0;
                    }
                    break;
                case 2:
                    try {
                        this->service.add_to_watch_list(this->service.queue.get_at(position));
                    }
                    catch (RepoException &a) {
                        std::cout << a.getMessage();
                    }
                    catch (TutorialException &a) {
                        std::cout << a.getMessage();
                    }
                    this->service.save(this->service.get_watch_list().get_data());
                    break;
                case 3:
                    position++;
                    if (position >= this->service.get_queue().get_size())
                        position = 0;
                    break;
                case 4: {
                    int pos;
                    std::string option, link_copy;
                    std::cout << "Which tutorial do you want to remove from the watch list? (list index): ";
                    std::cin >> pos;
                    if (pos < 0 || pos >= this->service.get_watch_list().get_size()) {
                        std::cout << "Invalid entry! (try entering a list index next time)\n\n";
                        break;
                    }
                    link_copy = this->service.get_watch_list().get_at(pos).get_link();
                    this->service.remove_from_watch_list(pos);
                    this->service.save(this->service.get_watch_list().get_data());
                    std::cout << "Tutorial removed! Would you like to leave a like? (y/n): ";
                    while (option != "y" && option != "n") {
                        std::cin >> option;
                        if (option != "y" && option != "n")
                            std::cout << "Invalid option, try again!\n";
                    }
                    if (option == "y") {
                        this->service.r.get_at(this->service.r.get_index(link_copy)).likes++;
                        this->service.queue.get_at(this->service.queue.get_index(link_copy)).likes++;
                    }
                    std::cout << "Alright, thank you for the feedback!\n\n";
                    break;
                }
                case 5: {
                    std::cout << "CURRENT WATCH LIST:\n\n";
                    std::string s;
                    for (int i = 0; i < this->service.get_watch_list().get_size(); i++) {
                        s += std::to_string(i);
                        s += ". ";
                        s += this->service.get_watch_list().get_at(i).to_string();
                        s += "\n";
                    }
                    s += "\n";
                    if (s == "\n") {
                        s = "None! Try adding some tutorials to your watch list!\n\n";
                    }
                    std::cout << s;
                }
                    break;
                case 6: {
                    std::string command =
                            "xdg-open C://Users/lexig/OneDrive/Documente/GitHub/a5-6-913-Goia-Alexia/cmake-build-debug-coverage/watchlist." +
                            extension;
                    std::system(command.c_str());
                }
                    break;
                default:
                    std::cout << "\nInvalid command!\n\n";
                    break;
            }

        }

    }
write_data();
}
