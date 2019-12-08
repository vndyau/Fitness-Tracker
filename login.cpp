
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <sstream>
#include "login.h"
#include <gtkmm.h>
#include<bits/stdc++.h>
#include <iterator>
#include "project.cpp"



using namespace std;


loginWindow::loginWindow(string fileName):box(Gtk::ORIENTATION_VERTICAL),loginButton("Login"),signUp("Sign Up"),exit("Exit"){


  readIn(fileName);

  set_size_request(400,400);
  set_title("Fitness Tracker!");
  add(box);

  userName.set_max_length(100);
  userName.set_text("Enter user name");
  userName.select_region(0, userName.get_text_length());
  box.pack_start(userName);

  numID.set_max_length(100);
  numID.set_text("Enter ID");
  numID.select_region(0,numID.get_text_length());
  numID.set_visibility(false);
  box.pack_start(numID);

  loginButton.signal_clicked().connect(sigc::mem_fun(*this,&loginWindow::login));
  box.pack_start(loginButton);


  signUp.signal_clicked().connect(sigc::mem_fun(*this,&loginWindow::signUpPage));
  box.pack_start(signUp);


  exit.signal_clicked().connect(sigc::mem_fun(*this,&loginWindow::close));
  box.pack_start(exit);


  show_all_children();
}

void loginWindow::close(){
  hide();
  readOut();
}
void loginWindow::login(){
  string user = userName.get_text();
  string password = numID.get_text();
  if (loginInfo.find(user) == loginInfo.end()){
    // Dialog box that asks whether or not they want to sign up
    Gtk::Window w;
    Gtk::Dialog dialog;
    dialog.set_transient_for(w);

    dialog.add_button("Sign up",1);
    dialog.add_button("Exit",0);

    int res = dialog.run();
    if(res == 1){
      sign();
    }

  }
  else if(loginInfo[user] != password){
    //Dialog box that says wrong password and to input in new password
    Gtk::MessageDialog dialog(*this,"Wrong password, please enter new password",false,Gtk::MESSAGE_INFO);
    dialog.run();
  }
  else{
    int num = stoi(password);
    Person * user = peopleMap[num];
    if(dynamic_cast<Gold *>(peopleMap[num]) != NULL){
      hide();
      goldWindow goldWind(user);
      Gtk::Main::run(goldWind);
    }
    else if(dynamic_cast<Silver *>(user) != NULL){
      hide();
      silverWindow silvWind(user);
      Gtk::Main::run(silvWind);
    }

    else{
      hide();
      bronzeWindow bWind(user);
      Gtk::Main::run(bWind);
    }


  }

}

void loginWindow::signUpPage(){
  sign();
}

loginWindow::~loginWindow(){}

void readIn(string fileName){
  ifstream input;
  input.open(fileName);
  if(!input.is_open()) exit(1);

  while(!input.eof()){
    string line;
    getline(input,line);
    if(line == "") break;
    stringstream ss(line);
    string name;
    getline(ss,name,',');
    string id;
    getline(ss,id,',');
    string bday;
    getline(ss,bday,',');
    string age;
    getline(ss,age,',');
    string weight;
    getline(ss,weight,',');
    string height;
    getline(ss,height,',');
    vector<string> schedule;
    for(int i = 0 ; i < 7;i++){
      string time;
      getline(ss,time,',');
      schedule.push_back(time);
    }


    string tier;
    getline(ss,tier,',');

    cout << name << endl;
    cout << id << endl;
    cout << bday << endl;
    cout << age << endl;
    cout << weight << endl;
    cout << height << endl;
    for(int i = 0 ;i < 7;i++) cout << schedule[i] << endl;
    cout << tier << endl;


    Person * p;


    if(tier == "S"){
      // continue parsing silver information here
      string dietNum;
      getline(ss,dietNum,',');
      string goalsNum;
      getline(ss,goalsNum);
      p = new Silver(name,stoi(id),bday,stoi(age),stoi(weight),stoi(height),schedule,stoi(dietNum),stoi(goalsNum));
    }
    else if(tier == "G"){
      // continue parsing silver/gold information here
      string dietNum;
      getline(ss,dietNum,',');
      string goalsNum;
      getline(ss,goalsNum,',');
      string sleepNum;
      getline(ss,sleepNum,',');
      string reminderYN;
      getline(ss,reminderYN,',');

      p = new Gold(name,stoi(id),bday,stoi(age),stoi(weight),stoi(height),schedule,stoi(dietNum),stoi(goalsNum),stoi(sleepNum),reminderYN);
    }
    else p = new Bronze(name,stoi(id),bday,stoi(age),stoi(weight),stoi(height),schedule);

    loginInfo[name] = id;
    peopleMap[stoi(id)] = p;
    }
  }
void readOut(){
  ofstream output;
  output.open("testfile.txt");
  for(map<int,Person*>::iterator it = peopleMap.begin() ; it != peopleMap.end();it++){
    Person * p = it->second;
    string tier;
    if(dynamic_cast<Gold *>(p) != NULL) tier = "G";
    else if(dynamic_cast<Silver *>(p) != NULL) tier = "S";
    else tier = "B";
    output << p->name << "," << p->ID << "," << p->birthday << "," << p->age << "," << p->weight << "," << p->height << ",";
    if(p->schedule.size() != 7) output << "x,x,x,x,x,x,x,";
    else for(int i = 0 ; i < 7 ;i++) output << p->schedule[i] <<",";


    if(tier == "G"){
      // output << gold/silver stuff;
      Gold * gPerson = dynamic_cast<Gold *>(p);
      output << tier <<",";
      cout << gPerson->diet;
      string reminder = gPerson->reminder ? "Y" : "N";
      output << gPerson->diet << "," << gPerson->goals << "," << gPerson->sleeptime << "," << reminder;
    }
    else if(tier == "S"){
      // output << silver stuff;
      Silver * sPerson = dynamic_cast<Silver *>(p);
      output << tier <<",";
      output << sPerson->diet << "," << sPerson->goals;
    }
    else output << tier;
    output<<endl;
  }
}


void sign(){
  int ret; //ret holds the value of the Done button when pushed; temp is used to transfer entries to variables.
  string temp;

  Gtk::Window profile;
  Gtk::Dialog *dialog = new Gtk::Dialog();
  dialog->set_transient_for(profile);
  dialog->set_title("Enter your info for your profile");

  //Name
  Gtk::Label *labelN = new Gtk::Label("Enter your full name:");
  dialog -> get_content_area() -> pack_start(*labelN);
  labelN -> show();
  Gtk::Entry entry_name;
  entry_name.set_text("Firstname Lastname");
  entry_name.set_max_length(30);
  entry_name.show();
  dialog -> get_vbox() -> pack_start(entry_name);

  //ID
  Gtk::Label *labelId = new Gtk::Label("Enter your ID number (max 10 digits):");
  dialog -> get_content_area() -> pack_start(*labelId);
  labelId -> show();
  Gtk::Entry entry_id;
  entry_id.set_text("1234567890");
  entry_id.set_max_length(10);
  entry_id.show();
  dialog -> get_vbox() -> pack_start(entry_id);

  //Birthday
  Gtk::Label *labelBd = new Gtk::Label("Enter your birthday (month/day):");
  dialog -> get_content_area() -> pack_start(*labelBd);
  labelBd -> show();
  Gtk::Entry entry_bd;
  entry_bd.set_text("12/31");
  entry_bd.set_max_length(5);
  entry_bd.show();
  dialog -> get_vbox() -> pack_start(entry_bd);


  //Age
  Gtk::Label *labelA = new Gtk::Label("Enter your age:");
  dialog -> get_content_area() -> pack_start(*labelA);
  labelA -> show();
  Gtk::Entry entry_age;
  entry_age.set_text("99");
  entry_age.set_max_length(2);
  entry_age.show();
  dialog -> get_vbox() -> pack_start(entry_age);

  //Weight
  Gtk::Label *labelW = new Gtk::Label("Enter your weight:");
  dialog -> get_content_area() -> pack_start(*labelW);
  labelW -> show();
  Gtk::Entry entry_weight;
  entry_weight.set_text("999");
  entry_weight.set_max_length(3);
  entry_weight.show();
  dialog -> get_vbox() -> pack_start(entry_weight);

  //Height
  Gtk::Label *labelH = new Gtk::Label("Enter your height (in inches):");
  dialog -> get_content_area() -> pack_start(*labelH);
  labelH -> show();
  Gtk::Entry entry_height;
  entry_height.set_text("99");
  entry_height.set_max_length(2);
  entry_height.show();
  dialog -> get_vbox() -> pack_start(entry_height);

  //Tier
  Gtk::Label *labelT1 = new Gtk::Label("Enter the tier you would like");
  dialog -> get_content_area() -> pack_start(*labelT1);
  labelT1 -> show();
  Gtk::Label *labelT2 = new Gtk::Label("(B = bronze, S = silver, G = gold):");
  dialog -> get_content_area() -> pack_start(*labelT2);
  labelT2 -> show();
  Gtk::Entry entry_tier;
  entry_tier.set_text("B");
  entry_tier.set_max_length(1);
  entry_tier.show();
  dialog -> get_vbox() -> pack_start(entry_tier);

  //Done Button
  dialog -> add_button("Done", 1); //Button Done will send a 1 when pushed
  dialog->add_button("Exit",0);
  ret = dialog -> run();

  if (ret == 1) //sets the variables with the values from entries. If a variable is an int, temp will help transforming the value into an int.
  {
      string name = entry_name.get_text();

      string temp = entry_id.get_text();
      int ID = stoi(temp, nullptr);

      string birthday = entry_bd.get_text();

      temp = entry_age.get_text();
      int age = stoi(temp, nullptr);

      temp = entry_weight.get_text();
      int weight = stoi(temp, nullptr);

      temp = entry_height.get_text();
      int height = stoi(temp, nullptr);

      string tier = entry_tier.get_text();
      Person * p;

      if(loginInfo.find(name) != loginInfo.end()){
        Gtk::MessageDialog d("Username already exists! Choose another!", false, Gtk::MESSAGE_INFO);
        d.run();
        delete(dialog);

      }
      else{
        if(tier == "G" || tier == "g"){
          Gtk::Dialog gDialog;
          gDialog.set_transient_for(profile);
          gDialog.set_title("Additional Info");


          Gtk::Label dietLabel("How many calories to eat this week?");
          dietLabel.show();
          Gtk::Entry dietEntry;
          dietEntry.set_text("");
          dietEntry.show();
          gDialog.get_content_area()->pack_start(dietLabel);
          gDialog.get_vbox()->pack_start(dietEntry);

          Gtk::Label goalsLabel("How much time to workout this week?");
          goalsLabel.show();
          Gtk::Entry goalsEntry;
          goalsEntry.set_text("");
          goalsEntry.show();
          gDialog.get_content_area()->pack_start(goalsLabel);
          gDialog.get_vbox()->pack_start(goalsEntry);


          Gtk::Label reminderLabel("Would you like reminders for work outs? (Y/N)");
          reminderLabel.show();
          Gtk::Entry reminderEntry;
          reminderEntry.set_text("");
          reminderEntry.show();
          gDialog.get_content_area()->pack_start(reminderLabel);
          gDialog.get_vbox()->pack_start(reminderEntry);

          gDialog.add_button("Submit",1);
          int ans = gDialog.run();

          p = new Gold(name,ID,birthday,age,weight,height,stoi(dietEntry.get_text()),stoi(goalsEntry.get_text()),reminderEntry.get_text());
        }
        else if(tier == "S" || tier == "s"){
          Gtk::Dialog gDialog;
          gDialog.set_transient_for(profile);
          gDialog.set_title("Additional Info");


          Gtk::Label dietLabel("How many calories to eat this week?");
          dietLabel.show();
          Gtk::Entry dietEntry;
          dietEntry.set_text("");
          dietEntry.show();
          gDialog.get_content_area()->pack_start(dietLabel);
          gDialog.get_vbox()->pack_start(dietEntry);

          Gtk::Label goalsLabel("How much time to workout this week?");
          goalsLabel.show();
          Gtk::Entry goalsEntry;
          goalsEntry.set_text("");
          goalsEntry.show();
          gDialog.get_content_area()->pack_start(goalsLabel);
          gDialog.get_vbox()->pack_start(goalsEntry);

          gDialog.add_button("Submit",1);
          int ans = gDialog.run();

          p = new Silver(name,ID,birthday,age,weight,height,stoi(dietEntry.get_text()),stoi(goalsEntry.get_text()));
        }
        else p = new Bronze(name,ID,birthday,age,weight,height);

            loginInfo[name] = to_string(ID);
            peopleMap[ID] = p;
            delete(dialog);
          }
      }
}
