#ifndef PROFILE_H
#define PROFILE_STUFF

#include <gtkmm.h>
#include <vector>

using namespace std;



class Person
{
public:
		string name;
		int ID;
    string birthday;
    int age;//
    int weight;
	int height;
    vector<string> schedule;

	Person();

    virtual void show_info() = 0;
};


class Bronze:virtual public Person
{
// to get rid of abstractness add functionality later.
public:
	void show_info();
	Bronze();
	Bronze(string name,int ID,string bday,int age,int weight,int height,vector<string> schedule);
	Bronze(string name,int ID,string bday,int age,int weight,int height);
};

class Silver: virtual public Bronze
{

	public:
		void show_info();
		Silver();
		Silver(string name,int ID,string bday,int age,int weight,int height,vector<string> schedule,int diet,int goals);
		Silver(string name,int ID,string bday,int age,int weight,int height,int diet,int goals);
		int diet; //calories
		int goals; //time left to workout


};

class Gold: public Silver
{
	public:
		void show_info();
		Gold(string name,int ID,string bday,int age,int weight,int height,vector<string> schedule,int diet,int goals,int sleep,string reminder);
		Gold(string name,int ID,string bday,int age,int weight,int height,int diet,int goals,string reminder);
		static void sleepFunction();
		bool reminder; //Do you get reminders? Y/N
		int sleeptime; //How much sleep did you get per day?
};
#endif
