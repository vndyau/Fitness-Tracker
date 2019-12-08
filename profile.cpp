#include <iostream>
#include <string>
#include <gtkmm.h>
#include "profile.h"
#include "login.h"




Bronze::Bronze(){}
Silver::Silver(){}
Person::Person(){}



Bronze::Bronze(string name,int ID,string bday,int age,int weight,int height){
  this->name = name;
  this->ID = ID;
  this->birthday = bday;
  this->age = age;
  this->weight = weight;
  this->height = height;
}

void Bronze::show_info(){
  Gtk::Window tempWind;
  Gtk::Dialog * dialog = new Gtk::Dialog();
  dialog->set_transient_for(tempWind);
  dialog->set_title("Information");

  Gtk::Label nameLabel("Name: "+this->name);
  dialog->get_content_area()->pack_start(nameLabel);
  nameLabel.show();


  Gtk::Label idLabel("ID: "+to_string(this->ID));
  dialog->get_content_area()->pack_start(idLabel);
  idLabel.show();

  Gtk::Label birthdayLabel("Birthday: "+this->birthday);
  dialog->get_content_area()->pack_start(birthdayLabel);
  birthdayLabel.show();

  Gtk::Label ageLabel("Age: "+to_string(this->age));
  dialog->get_content_area()->pack_start(ageLabel);
  ageLabel.show();

  Gtk::Label weightLabel("Weight: "+to_string(this->weight));
  dialog->get_content_area()->pack_start(weightLabel);
  weightLabel.show();

  Gtk::Label heightLabel("Height: "+to_string(this->height));
  dialog->get_content_area()->pack_start(heightLabel);
  heightLabel.show();

  dialog->add_button("Exit",1);

  dialog->run();
  delete(dialog);
}


Bronze::Bronze(string name,int ID,string bday,int age,int weight,int height,vector<string> schedule){
  this->name = name;
  this->ID = ID;
  this->birthday = bday;
  this->age = age;
  this->weight = weight;
  this->height = height;
  this->schedule = schedule;
}




Silver::Silver(string name,int ID,string bday,int age,int weight,int height,int diet,int goals){
  this->name = name;
  this->ID = ID;
  this->birthday = bday;
  this->age = age;
  this->weight = weight;
  this->height = height;
  this->diet = diet;
  this->goals = goals;
}

void Silver::show_info(){
  Gtk::Window tempWind;
  Gtk::Dialog * dialog = new Gtk::Dialog();
  dialog->set_transient_for(tempWind);
  dialog->set_title("Information");

  Gtk::Label nameLabel("Name: "+this->name);
  dialog->get_content_area()->pack_start(nameLabel);
  nameLabel.show();


  Gtk::Label idLabel("ID: "+to_string(this->ID));
  dialog->get_content_area()->pack_start(idLabel);
  idLabel.show();

  Gtk::Label birthdayLabel("Birthday: "+this->birthday);
  dialog->get_content_area()->pack_start(birthdayLabel);
  birthdayLabel.show();

  Gtk::Label ageLabel("Age: "+to_string(this->age));
  dialog->get_content_area()->pack_start(ageLabel);
  ageLabel.show();

  Gtk::Label weightLabel("Weight: "+to_string(this->weight));
  dialog->get_content_area()->pack_start(weightLabel);
  weightLabel.show();

  Gtk::Label heightLabel("Height: "+to_string(this->height));
  dialog->get_content_area()->pack_start(heightLabel);
  heightLabel.show();

  Gtk::Label dietLabel("Diet Goals (calories): "+to_string(this->diet));
  dialog->get_content_area()->pack_start(dietLabel);
  dietLabel.show();

  Gtk::Label goalsLabel("Hours to work out this week: "+to_string(this->goals));
  dialog->get_content_area()->pack_start(goalsLabel);
  goalsLabel.show();

dialog->add_button("Exit",1);

  dialog->run();
  delete(dialog);
}


Silver::Silver(string name,int ID,string bday,int age,int weight,int height,vector<string> schedule,int diet,int goals):Bronze(){
  this->name = name;
  this->ID = ID;
  this->birthday = bday;
  this->age = age;
  this->weight = weight;
  this->height = height;
  this->schedule = schedule;
  this->diet = diet;
  this->goals = goals;
}


Gold::Gold(string name,int ID,string bday,int age,int weight,int height,int diet,int goals,string reminder){
  this->name = name;
  this->ID = ID;
  this->birthday = bday;
  this->age = age;
  this->weight = weight;
  this->height = height;
  this->diet = diet;
  this->goals = goals;
  this->reminder = (reminder == "Y" || reminder == "y");
  this->sleeptime = 0;
}

void Gold::show_info(){
  Gtk::Window tempWind;
  Gtk::Dialog * dialog = new Gtk::Dialog();
  dialog->set_transient_for(tempWind);
  dialog->set_title("Information");

  Gtk::Label nameLabel("Name: "+this->name);
  dialog->get_content_area()->pack_start(nameLabel);
  nameLabel.show();


  Gtk::Label idLabel("ID: "+to_string(this->ID));
  dialog->get_content_area()->pack_start(idLabel);
  idLabel.show();

  Gtk::Label birthdayLabel("Birthday: "+this->birthday);
  dialog->get_content_area()->pack_start(birthdayLabel);
  birthdayLabel.show();

  Gtk::Label ageLabel("Age: "+to_string(this->age));
  dialog->get_content_area()->pack_start(ageLabel);
  ageLabel.show();

  Gtk::Label weightLabel("Weight: "+to_string(this->weight));
  dialog->get_content_area()->pack_start(weightLabel);
  weightLabel.show();

  Gtk::Label heightLabel("Height: "+to_string(this->height));
  dialog->get_content_area()->pack_start(heightLabel);
  heightLabel.show();

  Gtk::Label dietLabel("Diet Goals (calories): "+to_string(this->diet));
  dialog->get_content_area()->pack_start(dietLabel);
  dietLabel.show();

  Gtk::Label goalsLabel("Hours to work out this week: "+to_string(this->goals));
  dialog->get_content_area()->pack_start(goalsLabel);
  goalsLabel.show();

  Gtk::Label sleepLabel("Hours Slept This Week: "+to_string(this->sleeptime));
  dialog->get_content_area()->pack_start(sleepLabel);
  sleepLabel.show();

  string rem = this->reminder ? "Yes":"No";
  Gtk::Label remLabel("Have Reminders?: "+rem);
  dialog->get_content_area()->pack_start(remLabel);
  remLabel.show();

  dialog->add_button("Exit",1);

  dialog->run();
  delete(dialog);
}


Gold::Gold(string name,int ID,string bday,int age,int weight,int height,vector<string> schedule,int diet,int goals,int sleep,string reminder):Silver(){
  this->name = name;
  this->ID = ID;
  this->birthday = bday;
  this->age = age;
  this->weight = weight;
  this->height = height;
  this->schedule = schedule;
  this->diet = diet;
  this->goals = goals;
  this->reminder = (reminder == "Y" || reminder == "y");
  this->sleeptime = sleep;
}
