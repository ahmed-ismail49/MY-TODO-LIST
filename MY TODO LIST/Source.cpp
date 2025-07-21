#include <iostream>
#include <string>
#include <ctime>

#define max_users 100

using namespace std;

struct date {
	int day, month, year;
};

struct task {
	string title;
	string details;
	date end_date = {};
	int priority=0;
	bool is_done = false;
};

struct user {
	string user_name;
	string password;
	task tasks[100];
	int task_counter = 0;
}users[max_users];

int user_counter = 0;

void display_menu(int user_index);
void add_task(int user_index);
void mark_as_done(int user_index);
void edit(int user_index);
void delete_task(int user_index);
void display_tasks(int user_index);
void display_done(int user_index);
void display_overdue(int user_index);
void display_today(int user_index);
void search(int user_index);
void intailize_data();

int main() {
	intailize_data();
	int choice;
	cout << "press [1] to sign up." << endl;
	cout << "press [2] to login." << endl;
	cout << "enter your choice : ";
	cin >> choice;
	if (1 == choice) {
		cout << "username : ";
		cin >> users[user_counter].user_name;
		cout << "password : ";
		cin >> users[user_counter].password;
		cout << "wellcome " << users[user_counter].user_name << endl;
		display_menu(user_counter);
		user_counter++;
	}
	else if (2 == choice) {
		string user_name, password;
		bool user_notfound = true;
		cout << "enter your username : ";
		cin >> user_name;
		cout << "enter your password : ";
		cin >> password;
		for (int i = 0; i <= user_counter; i++) {
			if (user_name == users[i].user_name && password == users[i].password) {
				user_notfound = false;
				cout << "welcome  " << user_name << endl;
				display_menu(i);
			}
		}
		if (user_notfound)
			cout << "** incorrect username or password. **" << endl;
	}
	else
		cout << "** please enter 1 or 2 **";
	return 0;
}

void display_menu(int user_index) {
	int choice;
	char answer;
	do {
		cout << "[1]add a new task." << endl;
		cout << "[2]mark task as done." << endl;
		cout << "[3]edit specific task." << endl;
		cout << "[4]delete specific task." << endl;
		cout << "[5]dispaly all tasks." << endl;
		cout << "[6]display all done tasks." << endl;
		cout << "[7]display all overdue tasks." << endl;
		cout << "[8]display the tasks need to be done today." << endl;
		cout << "[9]search for specific task." << endl;
		cout << "[10]exist." << endl;
		cout << "enter your choice : ";
		cin >> choice;
		switch (choice) {
		case 1:
			add_task(user_index); // call add fn
			break;
		case 2:
			mark_as_done(user_index); // call mark task as done fn
			break;
		case 3:
			edit(user_index); // call edit fn
			break;
		case 4:
			delete_task(user_index); // call delete fn
			break;
		case 5:
			display_tasks(user_index); // call display all tasks fn
			break;
		case 6:
			display_done(user_index); // call display done fn
			break;
		case 7:
			display_overdue(user_index); // call display overdue  fn
			break;
		case 8:
			display_today(user_index); // call display today fn
			break;
		case 9:
			search(user_index); // call search fn
			break;
		case 10:
			main(); // to return from first again
			break;
		default:
			cout << "** please enter number between 1:10 **";
		}
		cout << "do you want to do something else ? (y/n) ";
		cin >> answer;
	} while (answer == 'y' || answer == 'Y');
}

void add_task(int user_index) {
	cout << "task title : ";
	cin.ignore(1, '\n');     getline(cin, users[user_index].tasks[users[user_index].task_counter].title);
	cout << "task details : ";
	getline(cin, users[user_index].tasks[users[user_index].task_counter].details);
	cout << "enter due date " << endl;
	cout << "day : ";        cin >> users[user_index].tasks[users[user_index].task_counter].end_date.day;
	cout << "month : ";      cin >> users[user_index].tasks[users[user_index].task_counter].end_date.month;
	cout << "year : ";       cin >> users[user_index].tasks[users[user_index].task_counter].end_date.year;
	cout << "priority (1:10) : ";
	cin >> users[user_index].tasks[users[user_index].task_counter].priority;
	users[user_index].task_counter++;
}

void mark_as_done(int user_index) {
	int task_number;
	cout << "enter task number you want to mark as done : ";
	cin >> task_number;
	if (task_number > 0 && task_number <= users[user_index].task_counter) {
		users[user_index].tasks[task_number - 1].is_done = true;
		cout << task_number << '.' << users[user_index].tasks[task_number - 1].title << "[done]." << endl;
	}
	else
		cout << "you have " << users[user_index].task_counter << " tasks only." << endl;
}

void edit(int user_index) {
	int task_number;
	cout << "enter task number you want to edit : ";
	cin >> task_number;
	if (task_number > 0 && task_number <= users[user_index].task_counter) {
		cout << task_number << '.' << users[user_index].tasks[task_number - 1].title << endl;
		cout << "\t details : " << users[user_index].tasks[task_number - 1].details << endl;
		cout << "\t date : " << users[user_index].tasks[task_number - 1].end_date.day << '/' << users[user_index].tasks[task_number - 1].end_date.month << '/' << users[user_index].tasks[task_number - 1].end_date.year << endl;
		cout << "\t priority : " << users[user_index].tasks[task_number - 1].priority << endl;
		(users[user_index].tasks[task_number - 1].is_done == 1) ? cout << "\t status : done.\n" : cout << "\t status : uncompleted.\n";
		int choice;
		cout << "[1]modify title." << endl;
		cout << "[2]modify details." << endl;
		cout << "[3]modify date." << endl;
		cout << "[4]modify priority." << endl;
		cout << "enter your choice : ";    cin >> choice;
		switch (choice) {
		case 1:
			cout << "enter the new title : ";
			getline(cin, users[user_index].tasks[task_number - 1].title);
			break;
		case 2:
			cout << "enter the new details : ";
			getline(cin, users[user_index].tasks[task_number - 1].details);
			break;
		case 3:
			cout << "enter the new date " << endl;
			cout << "day : ";             cin >> users[user_index].tasks[task_number - 1].end_date.day;
			cout << "month : ";           cin >> users[user_index].tasks[task_number - 1].end_date.month;
			cout << "year : ";            cin >> users[user_index].tasks[task_number - 1].end_date.year;
			break;
		case 4:
			cout << "enter new priority : ";
			cin >> users[user_index].tasks[task_number - 1].priority;
			break;
		default:
			cout << "** please enter number between 1:4 **";
		}
	}
	else
		cout << "you have " << users[user_index].task_counter << " tasks only." << endl;
}

void delete_task(int user_index) {
	int task_number;
	cout << "enter task number you want to delete : ";
	cin >> task_number;
	if (task_number > 0 && task_number <= users[user_index].task_counter) {
		cout << task_number << '.' << users[user_index].tasks[task_number - 1].title << "[deleted]." << endl;
		for (int i = task_number - 1; i < users[user_index].task_counter - 1; i++) {
			users[user_index].tasks[i] = users[user_index].tasks[i + 1];
		}
		users[user_index].task_counter--;
	}
	else
		cout << "you have " << users[user_index].task_counter << " tasks only." << endl;
}

void display_tasks(int user_index) {
	if (users[user_index].task_counter == 0) {
		cout << "you don't have any task, go and add some." << endl;
	}
	else {
		for (int i = 0; i < users[user_index].task_counter; i++) {
			cout << i + 1 << '.' << users[user_index].tasks[i].title << endl;
			cout << "\t details : " << users[user_index].tasks[i].details << endl;
			cout << "\t date : " << users[user_index].tasks[i].end_date.day << '/' << users[user_index].tasks[i].end_date.month << '/' << users[user_index].tasks[i].end_date.year << endl;
			cout << "\t priority : " << users[user_index].tasks[i].priority << endl;
			(users[user_index].tasks[i].is_done == 1) ? cout << "\t status : done.\n" : cout << "\t status : uncompleted.\n";
		}
	}
}

void display_done(int user_index) {
	bool found = false;
	for (int i = 0; i < users[user_index].task_counter; i++) {
		if (users[user_index].tasks[i].is_done) {
			cout << i + 1 << '.' << users[user_index].tasks[i].title << endl;
			cout << "\t details : " << users[user_index].tasks[i].details << endl;
			cout << "\t date : " << users[user_index].tasks[i].end_date.day << '/' << users[user_index].tasks[i].end_date.month << '/' << users[user_index].tasks[i].end_date.year << endl;
			cout << "\t priority : " << users[user_index].tasks[i].priority << endl;
			(users[user_index].tasks[i].is_done == 1) ? cout << "\t status : done.\n" : cout << "\t status : uncompleted.\n";
			found = true;
		}
	}
	if (false == found)
		cout << "you don't have any completed tasks, go and do some." << endl;
}

void display_overdue(int user_index) {
	// today time with ctime
	time_t curr_time = time(nullptr);
	tm local_time;
	localtime_s(&local_time, &curr_time);
	int year = 1900 + local_time.tm_year;
	int month = 1 + local_time.tm_mon;
	int day = local_time.tm_mday;

	bool found = false;
	for (int i = 0; i < users[user_index].task_counter; i++) {
		if (users[user_index].tasks[i].end_date.year < year || (users[user_index].tasks[i].end_date.year == year && users[user_index].tasks[i].end_date.month < month) || (users[user_index].tasks[i].end_date.year == year && users[user_index].tasks[i].end_date.month == month && users[user_index].tasks[i].end_date.day < day) && false == users[user_index].tasks[i].is_done) {
			cout << i + 1 << '.' << users[user_index].tasks[i].title << endl;
			cout << "\t details : " << users[user_index].tasks[i].details << endl;
			cout << "\t date : " << users[user_index].tasks[i].end_date.day << '/' << users[user_index].tasks[i].end_date.month << '/' << users[user_index].tasks[i].end_date.year << endl;
			cout << "\t priority : " << users[user_index].tasks[i].priority << endl;
			cout << "\t status : uncompleted." << endl;
			found = true;
		}
	}
	if (false == found)
		cout << "great you don't have overdue tasks." << endl;
}

void display_today(int user_index) {
	// today time with ctime
	time_t curr_time = time(nullptr);
	tm local_time;
	localtime_s(&local_time, &curr_time);
	int year = 1900 + local_time.tm_year;
	int month = 1 + local_time.tm_mon;
	int day = local_time.tm_mday;

	bool found = false;
	for (int i = 0; i < users[user_index].task_counter; i++) {
		if (users[user_index].tasks[i].end_date.year == year && users[user_index].tasks[i].end_date.month == month && users[user_index].tasks[i].end_date.day == day) {
			cout << i + 1 << users[user_index].tasks[i].title << endl;
			cout << "\t details : " << users[user_index].tasks[i].details << endl;
			cout << "\t date : " << users[user_index].tasks[i].end_date.day << '/' << users[user_index].tasks[i].end_date.month << '/' << users[user_index].tasks[i].end_date.year << endl;
			cout << "\t priority : " << users[user_index].tasks[i].priority << endl;
			(users[user_index].tasks[i].is_done == 1) ? cout << "\t status : done.\n" : cout << "\t status : uncompleted.\n";
			found = true;
		}
	}
	if (false == found)
		cout << "enjoy you don't have tasks today." << endl;
}

void search(int user_index) {
	int choice;
	int task_number;
	int day, month, year;
	bool found = false;
	string title;
	cout << "[1]search by task number." << endl;
	cout << "[2]search by task title." << endl;
	cout << "[3]search by date." << endl;
	cout << "eneter your choice : ";
	cin >> choice;
	switch (choice) {
	case 1:
		cout << "enter task number : ";
		cin >> task_number;
		if (task_number > 0 && task_number <= users[user_index].task_counter) {
			cout << task_number << '.' << users[user_index].tasks[task_number - 1].title << endl;
			cout << "\t details : " << users[user_index].tasks[task_number - 1].details << endl;
			cout << "\t date : " << users[user_index].tasks[task_number - 1].end_date.day << '/' << users[user_index].tasks[task_number - 1].end_date.month << '/' << users[user_index].tasks[task_number - 1].end_date.year << endl;
			cout << "\t priority : " << users[user_index].tasks[task_number - 1].priority << endl;
			(users[user_index].tasks[task_number - 1].is_done == 1) ? cout << "\t stasus : done\n" : cout << "\t status : uncompleted\n";
			found = true;
		}
		else
			cout << "you have " << users[user_index].task_counter << " tasks only." << endl;
		break;
	case 2:
		cout << "enter task title : ";
		cin >> title;
		for (int i = 0; i < users[user_index].task_counter; i++) {
			if (users[user_index].tasks[i].title == title) {
				cout << i + 1 << '.' << users[user_index].tasks[i].title << endl;
				cout << "\t details : " << users[user_index].tasks[i].details << endl;
				cout << "\t date : " << users[user_index].tasks[i].end_date.day << '/' << users[user_index].tasks[i].end_date.month << '/' << users[user_index].tasks[i].end_date.year << endl;
				cout << "\t priority : " << users[user_index].tasks[i].priority << endl;
				(users[user_index].tasks[i].is_done == 1) ? cout << "\t stasus : done\n" : cout << "\t status : uncompleted\n";
				found = true;
			}
		}
		if (false == found)
			cout << "there are no task with this title, try to search by anothor way." << endl;
		break;
	case 3:
		cout << "enter the date :" << endl;
		cout << "day : ";          cin >> day;
		cout << "month : ";        cin >> month;
		cout << "year : ";         cin >> year;
		for (int i = 0; i < users[user_index].task_counter; i++) {
			if (users[user_index].tasks[i].end_date.day == day && users[user_index].tasks[i].end_date.month == month && users[user_index].tasks[i].end_date.year == year) {
				cout << i + 1 << '.' << users[user_index].tasks[i].title << endl;
				cout << "\t details : " << users[user_index].tasks[i].details << endl;
				cout << "\t date : " << users[user_index].tasks[i].end_date.day << '/' << users[user_index].tasks[i].end_date.month << '/' << users[user_index].tasks[i].end_date.year << endl;
				cout << "\t priority : " << users[user_index].tasks[i].priority << endl;
				(users[user_index].tasks[i].is_done == 1) ? cout << "\t stasus : done\n" : cout << "\t status : uncompleted\n";
				found = true;
			}
		}
		if (false == found)
			cout << "there are no task, try to search by anothor way." << endl;
		break;
	default:
		cout << "** please enter number between 1:3 **" << endl;
	}
}

void intailize_data() {
	/* first user */
	users[user_counter].user_name = "ramez";
	users[user_counter].password = "ramez123";
	// first task
	users[0].tasks[0].title = "clean";
	users[0].tasks[0].details = "clean my room";
	users[0].tasks[0].end_date.day = 1;
	users[0].tasks[0].end_date.month = 5;
	users[0].tasks[0].end_date.year = 2024;
	users[0].tasks[0].priority = 3;
	// second task
	users[0].tasks[1].title = "study";
	users[0].tasks[1].details = "study math lessons";
	users[0].tasks[1].end_date.day = 1;
	users[0].tasks[1].end_date.month = 5;
	users[0].tasks[1].end_date.year = 2024;
	users[0].tasks[1].priority = 9;
	// third task
	users[0].tasks[2].title = "gym";
	users[0].tasks[2].details = "do exercises (push)";
	users[0].tasks[2].end_date.day = 6;
	users[0].tasks[2].end_date.month = 5;
	users[0].tasks[2].end_date.year = 2024;
	users[0].tasks[2].priority = 10;
	// fourth task
	users[0].tasks[3].title = "play";
	users[0].tasks[3].details = "play football with friends";
	users[0].tasks[3].end_date.day = 10;
	users[0].tasks[3].end_date.month = 4;
	users[0].tasks[3].end_date.year = 2024;
	users[0].tasks[3].priority = 7;
	// fifth task
	users[0].tasks[4].title = "work";
	users[0].tasks[4].details = "go to work";
	users[0].tasks[4].end_date.day = 11;
	users[0].tasks[4].end_date.month = 4;
	users[0].tasks[4].end_date.year = 2024;
	users[0].tasks[4].priority = 8;
	// intailize tasks counter
	users[0].task_counter = 5;

	user_counter++;
}