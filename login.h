
#ifndef LOGIN_H
#define LOGINWINDOW

#include <gtkmm.h>
#include <map>
#include <vector>
#include <string>

using namespace std;


class loginWindow: public Gtk::Window{
public:
  loginWindow(string fileName);
  virtual ~loginWindow();
protected:
  Gtk::Button loginButton,signUp,exit;
  Gtk::Entry userName,numID;
  Gtk::Box box;
  Gtk::Grid grid;
  void login();
  void signUpPage();
  void close();
};

void readIn(string fileName);
void readOut();
void sign();

#endif
