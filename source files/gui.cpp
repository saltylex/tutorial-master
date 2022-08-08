#include "../header files/gui.h"
#include <fstream>
#include <QDesktopServices>

GUI::GUI(Service &service, QWidget *parent) : service(service) {
    this->read_data();
    this->initGUI();
    this->populateTutorials();
}

GUI::~GUI() {
    this->close_app();
}


void GUI::initGUI() {
    //General layout of the window
    auto *layout = new QHBoxLayout{this};
    /// ------------------------------- LEFT SIDE
    /// -----------------------LIST
    this->filter_bar = new QLineEdit{};
    QFont filter{"Verdana", 10};
    this->filter_bar->setFont(filter);


    this->tutorialsList = new QListWidget{};
    this->tutorialsList->setSelectionMode(QAbstractItemView::SingleSelection);
    QLinearGradient grad(0,0,0, this->tutorialsList->height());
    grad.setColorAt(0, Qt::white);
    grad.setColorAt(1, Qt::magenta);
    QPalette pal = this->tutorialsList->palette();
    pal.setBrush(QPalette::ColorRole::Base, QBrush(grad));
    this->tutorialsList->setPalette(pal);
    auto *allCoatsLabel = new QLabel{"All Tutorials"};

    auto *leftSide = new QWidget{};
    auto *leftLayout = new QVBoxLayout{leftSide};

    QObject::connect(this->filter_bar, &QLineEdit::textChanged, this, &GUI::textEdited);

    leftLayout->addWidget(allCoatsLabel);
    leftLayout->addWidget(this->filter_bar);
    leftLayout->addWidget(this->tutorialsList);

    /// -----------------------TUTORIAL DATA
    auto *formLayout = new QWidget{};
    auto *movieLayout = new QFormLayout{formLayout};

    this->titleEdit = new QLineEdit{};
    this->presenterEdit = new QLineEdit{};
    this->minutesEdit = new QLineEdit{};
    this->secondsEdit = new QLineEdit{};
    this->numberOfLikesEdit = new QLineEdit{};
    this->linkEdit = new QLineEdit{};
    QFont f{"Verdana", 10};
    auto *titleLabel = new QLabel{"&Title:"};
    titleLabel->setBuddy(this->titleEdit);
    auto *presenterLabel = new QLabel{"&Presenter:"};
    presenterLabel->setBuddy(this->presenterEdit);
    auto *minutesLabel = new QLabel{"&Minutes:"};
    minutesLabel->setBuddy(this->minutesEdit);
    auto *secondsLabel = new QLabel{"&Seconds:"};
    secondsLabel->setBuddy(this->secondsEdit);
    auto *numberOfLikesLabel = new QLabel{"&Number of likes:"};
    numberOfLikesLabel->setBuddy(this->numberOfLikesEdit);
    auto *linkLabel = new QLabel{"&Link:"};
    linkLabel->setBuddy(this->linkEdit);
    titleLabel->setFont(f);
    presenterLabel->setFont(f);
    minutesLabel->setFont(f);
    secondsLabel->setFont(f);
    numberOfLikesLabel->setFont(f);
    linkLabel->setFont(f);
    this->titleEdit->setFont(f);
    this->presenterEdit->setFont(f);
    this->minutesEdit->setFont(f);
    this->secondsEdit->setFont(f);
    this->numberOfLikesEdit->setFont(f);
    this->linkEdit->setFont(f);
    movieLayout->addRow(titleLabel, this->titleEdit);
    movieLayout->addRow(presenterLabel, this->presenterEdit);
    movieLayout->addRow(minutesLabel, this->minutesEdit);
    movieLayout->addRow(secondsLabel, this->secondsEdit);
    movieLayout->addRow(numberOfLikesLabel, this->numberOfLikesEdit);
    movieLayout->addRow(linkLabel, this->linkEdit);

    leftLayout->addWidget(formLayout);
    ///----------------------- BUTTONS

    auto *buttonsWidget = new QWidget{};
    auto *gridLayout = new QGridLayout{buttonsWidget};

    this->addTutorialButton = new QPushButton("Add");
    this->addTutorialButton->setFont(f);
    this->deleteTutorialButton = new QPushButton("Remove");
    this->deleteTutorialButton->setFont(f);
    this->updateTutorialButton = new QPushButton("Update");
    this->updateTutorialButton->setFont(f);


    gridLayout->addWidget(this->addTutorialButton, 0, 0);
    gridLayout->addWidget(this->deleteTutorialButton, 0, 1);
    gridLayout->addWidget(this->updateTutorialButton, 0, 2);


    leftLayout->addWidget(buttonsWidget);

    ///------------------------------- MID SIDE

    auto *middleSide = new QWidget{};
    auto *middleLayout = new QVBoxLayout{middleSide};

    this->playlistButton = new QPushButton(">");
    this->playlistButton->setFont(f);

    middleLayout->addWidget(this->playlistButton);


    ///------------------------------- RIGHT SIDE

    auto *rightSide = new QWidget{};
    auto *rightLayout = new QVBoxLayout{rightSide};

    this->playList = new QListWidget{};
    this->playList->setSelectionMode(QAbstractItemView::SingleSelection);
    auto *playlistLabel = new QLabel{"Playlist"};

    rightLayout->addWidget(playlistLabel);
    rightLayout->addWidget(this->playList);

    auto *buttonsPlaylist = new QWidget{};
    auto *gridPlaylist = new QGridLayout{buttonsPlaylist};

    this->playButton = new QPushButton("Play");
    this->playButton->setFont(f);
    this->nextButton = new QPushButton("Next");
    this->nextButton->setFont(f);
    this->html = new QPushButton("Save HTML");
    this->html->setFont(f);
    this->csv = new QPushButton("Save CSV");
    this->csv->setFont(f);

    gridPlaylist->addWidget(this->playButton, 0, 0);
    gridPlaylist->addWidget(this->nextButton, 0, 1);
    gridPlaylist->addWidget(this->html, 1, 0);
    gridPlaylist->addWidget(this->csv, 1, 1);


    rightLayout->addWidget(buttonsPlaylist);





    /// ------------------------------- ADD ALL
    layout->addWidget(leftSide);
    layout->addWidget(middleSide);
    layout->addWidget(rightSide);

    QObject::connect(this->tutorialsList, &QListWidget::currentTextChanged, this, &GUI::currentTextChanged);
    QObject::connect(this->playlistButton, &QPushButton::released, this, &GUI::addToPlaylist);
    QObject::connect(this->addTutorialButton, &QPushButton::released, this, &GUI::add);
    QObject::connect(this->deleteTutorialButton, &QPushButton::released, this, &GUI::remove);
    QObject::connect(this->updateTutorialButton, &QPushButton::released, this, &GUI::update_rename);
    QObject::connect(this->playButton, &QPushButton::released, this, &GUI::open_tutorial);
    QObject::connect(this->nextButton, &QPushButton::released, this, &GUI::next);
    QObject::connect(this->html, &QPushButton::released, this, &GUI::save_html);
    QObject::connect(this->csv, &QPushButton::released, this, &GUI::save_csv);

}

void GUI::populateTutorials() {
    this->tutorialsList->clear();
    std::vector<Tutorial> allTutorials = this->service.get_repo().get_data();

    for (auto &m: allTutorials)
        this->tutorialsList->addItem(QString::fromStdString(m.to_string()));
    this->tutorialsList->setCurrentRow(this->tutorialsIndex);

}

void GUI::read_data() {
    std::ifstream f(
            R"(C:\Users\lexig\OneDrive\Documente\GitHub\a5-6-913-Goia-Alexia\cmake-build-debug-coverage\data.txt)");
    while (!f.eof()) {
        Tutorial temp;
        f >> temp;
        this->service.r.add(temp);
    }
    f.close();

}

void GUI::write_data() {
    std::ofstream ot(
            R"(C:\Users\lexig\OneDrive\Documente\GitHub\a5-6-913-Goia-Alexia\cmake-build-debug-coverage\data.txt)");
    int x = 0;
    for (Tutorial i: this->service.get_repo().get_data()) {
        ot << i;
        x++;
        if (x != this->service.get_repo().get_data().size()) {
            ot << "\n";
        }
    }
}

void GUI::currentTextChanged(const QString &currentText) {
    std::cout << "Current Text: " << currentText.toStdString() << std::endl;

    if (!this->tutorialsList->currentItem())
        return;

    std::string selection = this->tutorialsList->currentItem()->text().toStdString();
    Tutorial c = this->get_tutorial_from_string(selection);

    this->titleEdit->setText(QString::fromStdString(c.get_title()));
    this->presenterEdit->setText(QString::fromStdString(c.get_presenter()));
    this->minutesEdit->setText(QString::fromStdString(std::to_string(c.get_duration().minutes)));
    this->secondsEdit->setText(QString::fromStdString(std::to_string(c.get_duration().seconds)));
    this->numberOfLikesEdit->setText(QString::fromStdString(std::to_string(c.get_likes())));
    this->linkEdit->setText(QString::fromStdString(c.get_link()));
}

void GUI::textEdited(const QString &new_text) {
    this->tutorialsList->clear();
    this->titleEdit->clear();
    this->presenterEdit->clear();
    this->minutesEdit->clear();
    this->secondsEdit->clear();
    this->numberOfLikesEdit->clear();
    this->linkEdit->clear();

    int count = 0;
    for (auto m: this->service.get_repo().get_data())
        if (m.to_string().find(new_text.toStdString()) != std::variant_npos) {
            this->tutorialsList->addItem(QString::fromStdString(m.to_string()));
            count++;
        }
    if (this->tutorialsIndex == count) {
        this->tutorialsIndex = 0;
    }
    this->tutorialsList->setCurrentRow(this->tutorialsIndex);
}

void GUI::addToPlaylist() {
    if (!this->tutorialsList->currentItem())
        return;

    std::string selection_link;
    selection_link = this->linkEdit->text().toStdString();
    Tutorial selection = this->service.get_repo().get_at(this->service.get_repo().get_index(selection_link));
    std::cout << selection.to_string() << std::endl;
    this->playlist_list.push_back(selection);

    this->tutorialsIndex++;
    if (this->tutorialsIndex == this->service.get_size()) {
        this->tutorialsIndex = 0;
    }
    this->tutorialsList->setCurrentRow(this->tutorialsIndex);
    this->populatePlaylist();
}

void GUI::populatePlaylist() {
    this->playList->clear();

    for (auto m: this->playlist_list)
        this->playList->addItem(QString::fromStdString(m.to_string()));
    this->playList->setCurrentRow(this->playlistIndex);
}

void GUI::add() {
    std::cout << "To add:";
    if (this->titleEdit->text().isEmpty() || this->presenterEdit->text().isEmpty() ||
        this->minutesEdit->text().isEmpty() || this->linkEdit->text().isEmpty() ||
        this->secondsEdit->text().isEmpty() || this->numberOfLikesEdit->text().isEmpty())
        return;

    std::string title;
    std::string presenter;
    Duration duration;
    int likes;
    std::string link;

    try {
        likes = stoi(this->numberOfLikesEdit->text().toStdString());
        title = this->titleEdit->text().toStdString();
        presenter = this->presenterEdit->text().toStdString();
        duration = {stoi(this->minutesEdit->text().toStdString()), stoi(this->secondsEdit->text().toStdString())};
        link = this->linkEdit->text().toStdString();
    } catch (...) {
        std::cout << "Invalid Arguments\n";
        return;
    }

    if (!this->service.get_repo().find(link)) {
        try {
            this->service.add_to_repo(title, presenter, duration, likes, link);
        } catch (...) {
            std::cout << "Already exists\n";
        }
    }
    this->populateTutorials();
}

void GUI::update_rename() {
    if (this->titleEdit->text().isEmpty() || this->presenterEdit->text().isEmpty() ||
        this->minutesEdit->text().isEmpty() || this->linkEdit->text().isEmpty() ||
        this->secondsEdit->text().isEmpty() || this->numberOfLikesEdit->text().isEmpty())
        return;

    std::string title;
    std::string presenter;
    Duration duration;
    int likes;
    std::string link;

    try {
        likes = stoi(this->numberOfLikesEdit->text().toStdString());
        title = this->titleEdit->text().toStdString();
        presenter = this->presenterEdit->text().toStdString();
        duration = {stoi(this->minutesEdit->text().toStdString()), stoi(this->secondsEdit->text().toStdString())};
        link = this->linkEdit->text().toStdString();
    } catch (...) {
        std::cout << "Invalid Arguments\n";
        return;
    }

    if (!this->service.get_repo().find(link)) {
        return;
    }

    if (this->service.get_repo().find(link))
        this->service.update_in_repo(title, presenter, duration, likes, link, link);


    this->populateTutorials();
}

void GUI::remove() {
    if (this->linkEdit->text().isEmpty())
        return;

    std::string link;
    try {
        link = this->linkEdit->text().toStdString();
    } catch (...) {
        std::cout << "Invalid Arguments\n";
        return;
    }

    if (!this->service.get_repo().find(link)) {
        return;
    }
    this->service.remove_from_repo(link);
    this->populateTutorials();
}

void GUI::open_tutorial() {
    if (!this->playList->currentItem())
        return;
    std::string selection = this->playList->currentItem()->text().toStdString();
    Tutorial c = this->get_tutorial_from_string(selection);
    QDesktopServices::openUrl(QUrl(c.get_link().c_str(), QUrl::TolerantMode));
}

void GUI::next() {
    this->tutorialsIndex++;
    if (this->tutorialsIndex == this->service.get_size()) {
        this->tutorialsIndex = 0;
    }
    this->tutorialsList->setCurrentRow(this->tutorialsIndex);
}

Tutorial GUI::get_tutorial_from_string(std::string selection) {
    selection += "|";
    std::vector<std::string> tokens;

    size_t pos = 0;
    while ((pos = selection.find('|')) != std::string::npos) {
        tokens.push_back(selection.substr(0, pos));
        selection.erase(0, pos + 1);
    }

    int mins, sec;

    pos = tokens[2].find(':');
    mins = std::stoi(tokens[2].substr(0, pos));
    tokens[2].erase(0, pos + 1);
    sec = std::stoi(tokens[2]);

    int likes;

    pos = tokens[3].find(':');
    tokens[3].erase(0, pos + 1);
    likes = std::stoi(tokens[3]);

    auto c = Tutorial(tokens[0], tokens[1], {mins, sec}, likes, tokens[4]);
    std::cout << std::endl << c.to_string() << std::endl;
    return c;
}

void GUI::close_app() {
    this->write_data();
}

void GUI::save_html() {
    this->html_handler.save(this->playlist_list);
    QDesktopServices::openUrl(
            QUrl("C:/Users/lexig/OneDrive/Documente/GitHub/a5-6-913-Goia-Alexia/cmake-build-debug/watchlist.html",
                 QUrl::TolerantMode));
}

void GUI::save_csv() {
    this->csv_handler.save(this->playlist_list);
    QDesktopServices::openUrl(
            QUrl("C:/Users/lexig/OneDrive/Documente/GitHub/a5-6-913-Goia-Alexia/cmake-build-debug/watchlist.csv",
                 QUrl::TolerantMode));
}




