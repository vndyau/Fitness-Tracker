//Brian Truong ID:1001549574
#include "project.h"
#include <iostream>
#include <string>

using namespace std;

map<string, string> loginInfo; // name to password
map<int, Person *> peopleMap;  // ID# to person object

bronzeWindow::bronzeWindow(Person *p) : Main_box(Gtk::ORIENTATION_VERTICAL), Information("Fitness Information"), Upgrade("Upgrade to Silver"),
                                        Schedule_change("Change your Schedule"), Quit("Exit")
{
  this->currUser = p;
  set_title("Bronze Member Account");

  Bronze_image.set("bronzepicture.png");
  Main_box.pack_start(Bronze_image);
  set_size_request(600, 250);

  Information.signal_clicked().connect(sigc::mem_fun(*this, &bronzeWindow::information_clicked));
  Main_box.pack_start(Information);

  Upgrade.signal_clicked().connect(sigc::mem_fun(*this, &bronzeWindow::upgrade_clicked));
  Main_box.pack_start(Upgrade);

  Schedule_change.signal_clicked().connect(sigc::mem_fun(*this, &bronzeWindow::schedule_clicked));
  Main_box.pack_start(Schedule_change);

  Quit.signal_clicked().connect(sigc::mem_fun(*this, &bronzeWindow::close_button));
  Main_box.pack_start(Quit);

  add(Main_box);
  show_all_children();
}
bronzeWindow::~bronzeWindow() {}

void bronzeWindow::close_button()
{
  Gtk::MessageDialog dialog(*this, "Are you sure you want to exit?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
  int res = dialog.run();

  if (res == Gtk::RESPONSE_YES)
  {
    readOut();
    hide();
  }
}
void bronzeWindow::information_clicked()
{
  information member(this->currUser);
}
void bronzeWindow::upgrade_clicked()
{
  Gtk::MessageDialog dialog(*this, "Are you sure you want to upgrade to a Silver Membership?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
  int Answer = dialog.run();
  dialog.close();
  switch (Answer)
  {
  case (Gtk::RESPONSE_YES):
    if (Gtk::RESPONSE_YES)
    {
      hide();
      Gtk::Window profile;
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

      gDialog.add_button("Submit", 1);
      int ans = gDialog.run();
      gDialog.close();
      peopleMap.erase(this->currUser->ID);
      Person *newP = new Silver(this->currUser->name, this->currUser->ID, this->currUser->birthday, this->currUser->age, this->currUser->weight, this->currUser->height, this->currUser->schedule, stoi(dietEntry.get_text()), stoi(goalsEntry.get_text()));
      peopleMap[this->currUser->ID] = newP;
      silverWindow window1(newP);
      Gtk::Main::run(window1);
    }
  case (Gtk::RESPONSE_NO):
    std::cout << "Back to Bronze Membership" << std::endl;
    break;

  default:
    std::cout << "Corner button clicked." << std::endl;
    break;
  }
  // dialog.destroy();
}
void bronzeWindow::schedule_clicked()
{
}

//SILVER

//goals event handler
void workOut(Person *&p)
{

  Gtk::Window w;
  Gtk::Dialog *dialog = new Gtk::Dialog();
  Gtk::Label label("What day is it?");
  dialog->get_content_area()->pack_start(label);
  label.show();
  Gtk::Entry ent;
  dialog->get_content_area()->pack_start(ent);
  ent.show();
  dialog->add_button("Enter", 1);
  string day;
  if (dialog->run() == 1)
    day = ent.get_text();
  delete (dialog);
  int index = -1;
  if (day == "Sunday" || day == "sunday")
    index = 0;
  else if (day == "Monday" || day == "monday")
    index = 1;
  else if (day == "Tuesday" || day == "tuesday")
    index = 2;
  else if (day == "Wednesday" || day == "wednesday")
    index = 3;
  else if (day == "Thursday" || day == "thursday")
    index = 4;
  else if (day == "Friday" || day == "friday")
    index = 5;
  else if (day == "Saturday" || day == "saturday")
    index = 6;

  if (index == -1)
  {
    Gtk::MessageDialog d("Invalid input", false, Gtk::MESSAGE_INFO);
    d.run();
    return;
  }

  if (p->schedule[index] == "x")
  {
    Gtk::Window w;
    Gtk::Dialog *dialog = new Gtk::Dialog();

    dialog->set_transient_for(w);
    dialog->set_title("Workout Hours");
    Gtk::Label label("How many hours have you worked out today?");
    dialog->get_content_area()->pack_start(label);
    label.show();

    Gtk::SpinButton userIn;
    userIn.set_range(0, 12);
    userIn.set_value(1);
    userIn.set_increments(1, -1);
    dialog->get_vbox()->pack_start(userIn);
    userIn.show();

    dialog->add_button("Send", 1);
    dialog->add_button("Exit", 0);

    int res = dialog->run();

    if (res == 1)
    {
      Silver *newSilver = dynamic_cast<Silver *>(p);
      newSilver->goals -= userIn.get_value_as_int();
      Gtk::MessageDialog d("Total left to workout this week: " + to_string(newSilver->goals) + " hours");
      d.run();
    }
    delete (dialog);
  }
  else
  {

    // calculate time based on scheduled workout then set day to x in schedule
  }
}

void setGoals(Silver *p)
{
  Gtk::Window w;
  Gtk::Dialog *dialog = new Gtk::Dialog();
  dialog->set_transient_for(w);

  Gtk::Label lab("Update your goals?");
  dialog->get_content_area()->pack_start(lab);
  lab.show();
  Gtk::SpinButton userIn;
  userIn.set_range(0, 12);
  userIn.set_value(1);
  userIn.set_increments(1, -1);
  dialog->get_vbox()->pack_start(userIn);
  userIn.show();

  dialog->add_button("Submit", 1);
  dialog->add_button("Exit", 0);
  int res = dialog->run();

  if (res == 1)
  {
    int newGoal = userIn.get_value_as_int();
    p->goals = newGoal;
    Gtk::MessageDialog md("Your new goal to workout is now: " + to_string(p->goals) + " hours");
    md.run();
  }

  delete (dialog);
};

void silverWindow::goalsFunction()
{
  Gtk::Window w;
  Gtk::Dialog *dialog = new Gtk::Dialog();
  dialog->set_title("Goals Menu");
  dialog->set_transient_for(w);
  dialog->add_button("Record Workout", 1);
  dialog->add_button("Set Goals", 2);
  dialog->add_button("See Current Goals", 3);
  dialog->add_button("Exit", 0);

  int res = dialog->run();

  if (res == 1)
    workOut(this->currUser);
  else if (res == 2)
    setGoals(dynamic_cast<Silver *>(this->currUser));
  else if (res == 3)
  {
    Gtk::MessageDialog md("Amount of hours to workout this week " + to_string(dynamic_cast<Silver *>(this->currUser)->goals));
    md.run();
  }
  delete (dialog);
}

silverWindow::silverWindow(Person *p) : Main_box(Gtk::ORIENTATION_VERTICAL)
// , Information("Fitness Information"), Upgrade("Upgrade to Gold"),
//                    Degrade("Degrade to Bronze"), Schedule_change("Change your Schedule"), Quit("Exit")
{

  set_size_request(550, 350);

  this->currUser = p;
  set_title("Silver Member Account");

  Silver_image.set("silverpicture.png");

  Main_box.pack_start(Horizontal_box);
  Horizontal_box.pack_start(Silver_image);
  Horizontal_box.pack_start(Second_box);

  Information.add_label("Fitness Information");
  Information.signal_clicked().connect(sigc::mem_fun(*this, &silverWindow::information_clicked));
  Second_box.pack_start(Information);

  Upgrade.add_label("Upgrade to Gold");
  Upgrade.signal_clicked().connect(sigc::mem_fun(*this, &silverWindow::upgrade_clicked));
  Second_box.pack_start(Upgrade);

  Degrade.add_label("Degrade to Bronze");
  Degrade.signal_clicked().connect(sigc::mem_fun(*this, &silverWindow::degrade_clicked));
  Second_box.pack_start(Degrade);

  Schedule_change.add_label("Change your Schedule");
  Schedule_change.signal_clicked().connect(sigc::mem_fun(*this, &silverWindow::schedule_clicked));
  Second_box.pack_start(Schedule_change);

  Diet.add_label("Check Diet");
  Diet.signal_clicked().connect(sigc::mem_fun(*this, &silverWindow::diet_clicked));
  Second_box.pack_start(Diet);

  Goals.add_label("Check Goals");
  Goals.signal_clicked().connect(sigc::mem_fun(*this, &silverWindow::goalsFunction));
  Second_box.pack_start(Goals);

  Quit.add_label("Exit");
  Quit.signal_clicked().connect(sigc::mem_fun(*this, &silverWindow::close_button));
  Second_box.pack_start(Quit);

  add(Main_box);
  show_all_children();
}
silverWindow::~silverWindow() {}

void silverWindow::close_button()
{
  Gtk::MessageDialog dialog(*this, "Are you sure you want to exit?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
  int res = dialog.run();

  if (res == Gtk::RESPONSE_YES)
  {
    readOut();
    hide();
  }
}
void silverWindow::information_clicked()
{
  information member(this->currUser);
}
void silverWindow::upgrade_clicked()
{
  Gtk::MessageDialog dialog(*this, "Are you sure you want to upgrade to a Gold Membership?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
  int Answer = dialog.run();

  switch (Answer)
  {
  case (Gtk::RESPONSE_YES):
    if (Gtk::RESPONSE_YES)
    {
      hide();
      dialog.close();
      Gtk::Window profile;
      Gtk::Dialog gDialog;
      gDialog.set_transient_for(profile);
      gDialog.set_title("Additional Info");

      Gtk::Label reminderLabel("Would you like reminders for work outs? (Y/N)");
      reminderLabel.show();
      Gtk::Entry reminderEntry;
      reminderEntry.set_text("");
      reminderEntry.show();
      gDialog.get_content_area()->pack_start(reminderLabel);
      gDialog.get_vbox()->pack_start(reminderEntry);

      gDialog.add_button("Submit", 1);
      int ans = gDialog.run();
      gDialog.close();

      Silver *curr = dynamic_cast<Silver *>(this->currUser);
      peopleMap.erase(this->currUser->ID);
      Person *newP = new Gold(this->currUser->name, this->currUser->ID, this->currUser->birthday, this->currUser->age, this->currUser->weight, this->currUser->height, this->currUser->schedule, curr->diet, curr->goals, 0, reminderEntry.get_text());
      peopleMap[this->currUser->ID] = newP;
      goldWindow window1(newP);
      Gtk::Main::run(window1);
    }
  case (Gtk::RESPONSE_NO):
    std::cout << "Back to Silver Membership" << std::endl;
    break;

  default:
    std::cout << "Corner button clicked." << std::endl;
    break;
  }
}
void silverWindow::degrade_clicked()
{
  Gtk::MessageDialog dialog(*this, "Are you sure you want to degrade to a Bronze Membership?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
  int Answer = dialog.run();

  switch (Answer)
  {
  case (Gtk::RESPONSE_YES):
    if (Gtk::RESPONSE_YES)
    {
      hide();
      dialog.close();
      cout << "asdf" << endl;
      Person *currP = this->currUser;
      Person *newBronze = new Bronze(currP->name, currP->ID, currP->birthday, currP->age, currP->weight, currP->height, currP->schedule);

      peopleMap.erase(newBronze->ID);
      peopleMap[newBronze->ID] = newBronze;
      bronzeWindow window1(newBronze);
      Gtk::Main::run(window1);
    }
  case (Gtk::RESPONSE_NO):
    std::cout << "Back to Silver Membership" << std::endl;
    break;

  default:
    std::cout << "Corner button clicked." << std::endl;
    break;
  }
}
void silverWindow::schedule_clicked()
{
}

void silverWindow::diet_clicked()
{
  Gtk::Window w;
  Gtk::Dialog *dialog = new Gtk::Dialog();
  dialog->set_title("Diet Menu");
  dialog->set_transient_for(w);

  Gtk::Label Calorie("Record the amount of calories you ate today");
  Calorie.show();
  Gtk::Entry Line;
  Line.show();

  dialog->get_content_area()->pack_start(Calorie);
  dialog->get_content_area()->pack_start(Line);

  dialog->add_button("Confirm Calorie amount", 1);

  dialog->add_button("Exit", 0);

  int res = dialog->run();

  if (res == 1)
  {
    Silver * temp = dynamic_cast<Silver*>(this->currUser);
    temp->diet -=  stoi(Line.get_text());
    Gtk::MessageDialog d("Need to eat "+to_string(temp->diet)+" calories to reach goal!");
    d.run();
  }


  delete (dialog);
}

//GOLD

void goldWindow::diet_clicked()
{
  Gtk::Window w;
  Gtk::Dialog *dialog = new Gtk::Dialog();
  dialog->set_title("Diet Menu");
  dialog->set_transient_for(w);

  Gtk::Label Calorie("Record the amount of calories you ate today (calories):");
  Calorie.show();
  Gtk::Entry Line;
  Line.show();

  Gtk::Label Water("Record the amount of water you drank today (ounces):");
  Water.show();
  Gtk::Entry Line1;
  Line1.show();

  dialog->get_content_area()->pack_start(Calorie);
  dialog->get_content_area()->pack_start(Line);

  dialog->get_content_area()->pack_start(Water);
  dialog->get_content_area()->pack_start(Line1);

  dialog->add_button("Confirm Calorie and Water amount", 1);

  dialog->add_button("Exit", 0);

  int res = dialog->run();

  if (res == 1){
      Silver * temp = dynamic_cast<Silver*>(this->currUser);
      temp->diet -=  stoi(Line.get_text());
      Gtk::MessageDialog d("Need to eat "+to_string(temp->diet)+" calories to reach goal!");
      d.run();
  }


  delete (dialog);
}

void goldWindow::goalsFunction()
{
  Gtk::Window w;
  Gtk::Dialog *dialog = new Gtk::Dialog();
  dialog->set_title("Goals Menu");
  dialog->set_transient_for(w);
  dialog->add_button("Record Workout", 1);
  dialog->add_button("Set Goals", 2);
  dialog->add_button("See Current Goals", 3);
  dialog->add_button("Exit", 0);

  int res = dialog->run();

  if (res == 1)
    workOut(this->currUser);
  else if (res == 2)
    setGoals(dynamic_cast<Silver *>(this->currUser));
  else if (res == 3)
  {
    Gtk::MessageDialog md("Amount of hours to workout this week " + to_string(dynamic_cast<Silver *>(this->currUser)->goals));
    md.run();
  }
  delete (dialog);
}

void goldWindow::reminder_clicked()
{
  Gold *goldPerson = dynamic_cast<Gold *>(this->currUser);
  if (goldPerson->reminder)
  {
    Gtk::MessageDialog md("You have a workout scheduled today!", false, Gtk::MESSAGE_INFO);
    md.run();
  }
  else
  {
    Gtk::MessageDialog md(*this, "You don't have reminders set up. Would you like to turn it on?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
    int res = md.run();
    if (res == Gtk::RESPONSE_YES)
    {
      goldPerson->reminder = true;
      Gtk::MessageDialog newDialog("You will now be reminded for workouts!", false, Gtk::MESSAGE_INFO);
      newDialog.run();
    }
  }
}

goldWindow::goldWindow(Person *p) : Main_box(Gtk::ORIENTATION_VERTICAL)
// , Information("Fitness Information"),
//                                     Degrade("Degrade to Silver"), Schedule_change("Change your Schedule"), Diet("Check Diet"), Quit("Exit")
{
  this->currUser = p;
  set_title("Gold Member Account");
  set_size_request(670, 400);

  Gold_image.set("goldpicture.png");
  Main_box.pack_start(Horizontal_box);

  //
  Horizontal_box.pack_start(Gold_image);
  Horizontal_box.pack_start(Second_box);

  Information.add_label("Fitness Information");
  Information.signal_clicked().connect(sigc::mem_fun(*this, &goldWindow::information_clicked));
  Second_box.pack_start(Information);

  Degrade.add_label("Degrade to Silver");
  Degrade.signal_clicked().connect(sigc::mem_fun(*this, &goldWindow::degrade_clicked));
  Second_box.pack_start(Degrade);

  Schedule_change.add_label("Change your Schedule");
  Schedule_change.signal_clicked().connect(sigc::mem_fun(*this, &goldWindow::schedule_clicked));
  Second_box.pack_start(Schedule_change);

  Diet.add_label("Check Diet");
  Diet.signal_clicked().connect(sigc::mem_fun(*this, &goldWindow::diet_clicked));
  Second_box.pack_start(Diet);

  Goals.add_label("Check Goals");
  Goals.signal_clicked().connect(sigc::mem_fun(*this, &goldWindow::goalsFunction));
  Second_box.pack_start(Goals);

  Reminder.add_label("Examine Reminder");
  Reminder.signal_clicked().connect(sigc::mem_fun(*this, &goldWindow::reminder_clicked));
  Second_box.pack_start(Reminder);

  Sleep.add_label("Explore Sleep");
  Sleep.signal_clicked().connect(sigc::mem_fun(*this, &goldWindow::sleepFunction));
  Second_box.pack_start(Sleep);

  Quit.add_label("Exit");
  Quit.signal_clicked().connect(sigc::mem_fun(*this, &goldWindow::close_button));
  Second_box.pack_start(Quit);

  add(Main_box);
  show_all_children();
}
goldWindow::~goldWindow() {}

void goldWindow::close_button()
{
  Gtk::MessageDialog dialog(*this, "Are you sure you want to exit?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
  int res = dialog.run();

  if (res == Gtk::RESPONSE_YES)
  {
    readOut();
    hide();
  }
}

void goldWindow::information_clicked()
{
  information update(this->currUser);
}

void goldWindow::degrade_clicked()
{
  Gtk::MessageDialog dialog(*this, "Are you sure you want to degrade to a Silver Membership?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
  int Answer = dialog.run();

  switch (Answer)
  {
  case (Gtk::RESPONSE_YES):
    if (Gtk::RESPONSE_YES)
    {
      hide();
      dialog.close();
      Silver *currP = dynamic_cast<Silver *>(this->currUser);
      Person *newSilver = new Silver(currP->name, currP->ID, currP->birthday, currP->age, currP->weight, currP->height, currP->schedule, currP->diet, currP->goals);

      peopleMap.erase(newSilver->ID);
      peopleMap[newSilver->ID] = newSilver;
      silverWindow window1(newSilver);
      Gtk::Main::run(window1);
    }
  case (Gtk::RESPONSE_NO):
    std::cout << "Back to Gold Membership" << std::endl;
    break;

  default:
    std::cout << "Corner button clicked." << std::endl;
    break;
  }
}
void goldWindow::schedule_clicked()
{
}

void goldWindow::sleepFunction()
{

  Gtk::Window w;
  Gtk::Dialog *dialog = new Gtk::Dialog();
  dialog->set_transient_for(w);
  cout << "Reached here" << endl;

  Gtk::Label lab("How much sleep did you get?");
  dialog->get_content_area()->pack_start(lab);
  lab.show();
  Gtk::SpinButton userIn;
  userIn.set_range(0, 12);
  userIn.set_value(1);
  userIn.set_increments(1, -1);
  dialog->get_vbox()->pack_start(userIn);
  userIn.show();

  dialog->add_button("Submit", 1);

  int res = dialog->run();

  if (res == 1)
  {

    Gold *person = dynamic_cast<Gold *>(this->currUser);
    person->sleeptime += userIn.get_value_as_int();

    Gtk::MessageDialog d("You have now slept for " + to_string(person->sleeptime) + " hours total!", false, Gtk::MESSAGE_INFO);
    d.run();

    delete (dialog);
  }
}

//////////////////////////////////////////////////////////////
information::information(Person *p)
{

  Gtk::Window tempWind;
  Gtk::Dialog * dialog = new Gtk::Dialog();
  dialog->set_transient_for(tempWind);
  dialog->set_title("Information");
  Gtk::Label lab("Change info or view info?");
  dialog->get_content_area()->pack_start(lab);
  lab.show();
  dialog->add_button("Change",1);
  dialog->add_button("View",0);

  int res = dialog->run();
  if(res == 1){
    delete(dialog);
    Gtk::Window w;
    Gtk::Dialog *dialog_box = new Gtk::Dialog();
    dialog_box->set_default_size(500, 400);
    dialog_box->set_transient_for(w);
    dialog_box->set_title("Fitness Information");
    Gtk::Label *label = new Gtk::Label("Change Current Fitness Information:\n");
    dialog_box->get_content_area()->pack_start(*label);
    label->show();

    Gtk::Label *label1 = new Gtk::Label("Full Name\n");
    dialog_box->get_content_area()->pack_start(*label1);
    label1->show();

    dialog_box->add_button("Confirm", 1);
    dialog_box->set_default_response(1);

    Gtk::Entry *first_entry = new Gtk::Entry();
    first_entry->set_text("Enter your Full Name: ");
    first_entry->set_max_length(60);
    first_entry->show();
    dialog_box->get_vbox()->pack_start(*first_entry);

    Gtk::Label *label2 = new Gtk::Label("\nID Number\n");
    dialog_box->get_content_area()->pack_start(*label2);
    label2->show();

    Gtk::Entry *second_entry = new Gtk::Entry();
    second_entry->set_text("Enter your ID Number: ");
    second_entry->set_max_length(60);
    second_entry->show();
    dialog_box->get_vbox()->pack_start(*second_entry);

    Gtk::Label *label3 = new Gtk::Label("\nBirthday\n");
    dialog_box->get_content_area()->pack_start(*label3);
    label3->show();

    Gtk::Entry *third_entry = new Gtk::Entry();
    third_entry->set_text("Enter your Birthday: ");
    third_entry->set_max_length(60);
    third_entry->show();
    dialog_box->get_vbox()->pack_start(*third_entry);

    Gtk::Label *label4 = new Gtk::Label("\nWeight\n");
    dialog_box->get_content_area()->pack_start(*label4);
    label4->show();

    Gtk::Entry *fourth_entry = new Gtk::Entry();
    fourth_entry->set_text("Enter your Weight: ");
    fourth_entry->set_max_length(60);
    fourth_entry->show();
    dialog_box->get_vbox()->pack_start(*fourth_entry);

    Gtk::Label *label5 = new Gtk::Label("\nAge\n");
    dialog_box->get_content_area()->pack_start(*label5);
    label5->show();

    Gtk::Entry *fifth_entry = new Gtk::Entry();
    fifth_entry->set_text("Enter your Age: ");
    fifth_entry->set_max_length(60);
    fifth_entry->show();
    dialog_box->get_vbox()->pack_start(*fifth_entry);

    Gtk::Label *label6 = new Gtk::Label("\nHeight\n");
    dialog_box->get_content_area()->pack_start(*label6);
    label6->show();

    Gtk::Entry *sixth_entry = new Gtk::Entry();
    sixth_entry->set_text("Enter your Height: ");
    sixth_entry->set_max_length(60);
    sixth_entry->show();
    dialog_box->get_vbox()->pack_start(*sixth_entry);

    int result = dialog_box->run();
    Name = first_entry->get_text();
    ID = second_entry->get_text();
    Birthday = third_entry->get_text();
    WeightString = fourth_entry->get_text();
    AgeString = fifth_entry->get_text();
    HeightString = sixth_entry->get_text();

    Weight = stof(WeightString);
    Age = stoi(AgeString);
    Height = stoi(HeightString);

    cout << "Name is: " << Name << "\nID is: " << ID << "\nBirthday is: " << Birthday << "\nWeight is: " << Weight << "\nAge is: " << Age << "\nHeight is: " << Height << endl;

    if (loginInfo.find(Name) != loginInfo.end())
    {
      Gtk::MessageDialog d("Name already exist choose another name!", false, Gtk::MESSAGE_INFO);
      d.run();
      dialog_box->close();
      return;
    }

    p->name = Name;
    p->ID = stoi(ID);
    p->birthday = Birthday;
    p->weight = Weight;
    p->age = Age;
    p->height = Height;

    Gtk::MessageDialog d("Updated information!", false, Gtk::MESSAGE_INFO);
    d.run();

    dialog_box->close();

    delete dialog_box;
  }
  else if(res == 0){
    delete(dialog);
    p->show_info();
  }
}
