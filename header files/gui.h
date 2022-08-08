#pragma once
#include <qwidget.h>
#include "tutorial.h"
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include "service.h"
#include "repo.h"

class GUI: public QWidget
{
Q_OBJECT

public:
    GUI(Service& serv, QWidget *parent = nullptr);

    ~GUI() override;

private:
    Service& service;

    HTMLHandler html_handler = HTMLHandler();
    CSVHandler csv_handler = CSVHandler();

    std::vector<Tutorial> playlist_list;

    int playlistIndex = 0;
    int tutorialsIndex = 0;


    QListWidget* tutorialsList;
    QListWidget* playList;

    QLineEdit* titleEdit;
    QLineEdit* presenterEdit;
    QLineEdit* minutesEdit;
    QLineEdit* secondsEdit;
    QLineEdit* numberOfLikesEdit;
    QLineEdit* linkEdit;

    QPushButton* addTutorialButton;
    QPushButton* deleteTutorialButton;
    QPushButton* updateTutorialButton;
    //QPushButton* filterTutorialButton;

    QPushButton* playlistButton;
    QPushButton* playButton;
    QPushButton* nextButton;

    QPushButton* html;
    QPushButton* csv;

    QLineEdit* filter_bar;

    void initGUI();
    void populateTutorials();
    void populatePlaylist();

    void read_data();
    void write_data();

    void currentTextChanged(const QString &currentText);
    void textEdited(const QString &new_text);
    void addToPlaylist();

    void add();
    void update_rename();
    void remove();

    void open_tutorial();
    void next();

    Tutorial get_tutorial_from_string(std::string selection);
    void close_app();

    void save_html();
    void save_csv();

};
