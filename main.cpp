#include "profile.h"
#include "login.h"
#include <gtkmm.h>
using namespace std;



int main(int argc, char ** argv){
  Gtk::Main res(argc,argv);
  loginWindow log(argv[1]);
  Gtk::Main::run(log);
}
