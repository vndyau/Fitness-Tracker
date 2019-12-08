#ifndef CHOICE_H
#define CHOICE_H


#include <gtkmm.h>
#include <vector>
#include <string>
#include "profile.h"

using namespace std;




class bronzeWindow : public Gtk::Window
{
public:
    bronzeWindow(Person * p);
    virtual ~bronzeWindow();

protected:
    Person * currUser;
    void close_button();
    void information_clicked();
    void upgrade_clicked();
    void schedule_clicked();

    Gtk::VBox Main_box;
    Gtk::HBox Horizontal_box;
    Gtk::Grid Main_grid;
    Gtk::Image Bronze_image;
    Gtk::Label label;
    Gtk::Entry entry;
    Gtk::Button Information, Upgrade, Schedule_change, Quit;
};

class silverWindow : public Gtk::Window
{
public:
    silverWindow(Person * p);
    virtual ~silverWindow();

protected:
    Person * currUser;
    void close_button();
    void information_clicked();
    void upgrade_clicked();
    void degrade_clicked();
    void schedule_clicked();
    void diet_clicked();
    void goalsFunction();

    Gtk::VBox Main_box, Second_box;
    Gtk::HBox Horizontal_box;
    Gtk::Grid Main_grid;
    Gtk::Image Silver_image;
    Gtk::Label label;
    Gtk::Entry entry;
    Gtk::Button Information, Upgrade, Degrade, Schedule_change, Diet, Goals, Quit;
};

class goldWindow : public Gtk::Window
{
public:
    goldWindow(Person * p);
    virtual ~goldWindow();

protected:
    Person * currUser;
    void close_button();
    void information_clicked();
    void degrade_clicked();
    void schedule_clicked();
    void diet_clicked();
    void reminder_clicked();
    void sleepFunction();
    void goalsFunction();
    Gtk::VBox Main_box, Second_box;
    Gtk::HBox Horizontal_box;
    Gtk::Grid Main_grid;
    Gtk::Image Gold_image;
    Gtk::Label label;
    Gtk::Entry entry;
    Gtk::Button Information, Upgrade, Degrade, Schedule_change, Diet, Goals, Reminder, Sleep, Quit;
};


class information
{
public:
    string Name, ID, Birthday, WeightString, AgeString, HeightString;
    float Weight;
    int Age, Height;
    int Schedule[7];

    information(Person * p);
};

#endif
