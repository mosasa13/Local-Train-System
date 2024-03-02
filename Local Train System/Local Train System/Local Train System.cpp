#include <iostream>
#include <fstream>

using namespace std;

void view_des();

void customer_menu(string username) {
	cout << endl << "Welcome " << username << endl << endl;
	cout << "Start Booking" << endl << endl;
	view_des();
	cout << endl << "Each station costs 100 EGP || Return 200 EGP " << endl;
	cout << endl << endl << "Enter the name of the Start Station: ";
	string start;
	cin >> start;
	//check if the input is correct
	bool found = false;
	while (!found) {
		ifstream des("des.txt");
		while (!des.eof()) {
			string t_name;
			des >> t_name;
			if (t_name == start) {
				found = true;
				break;
			}
		}
		des.close();
		if (found)
			break;
		else {
			cout << "error in valid choice .. enter again :";
			cin >> start;
		}
	}
	cout << endl << endl << "Enter the name of the End Station: ";
	string end;
	cin >> end;

	//check if the input is correct and after start
	found = false;
	bool b3d_start = false;
	while (!found) {
		ifstream des("des.txt");
		while (!des.eof()) {
			string t_name;
			des >> t_name;
			if (t_name == start)
				b3d_start = true;
			if (t_name == end && b3d_start) {
				found = true;
				break;
			}
		}
		des.close();
		if (found)
			break;
		else {
			cout << "error in valid choice .. enter again :";
			cin >> end;
		}
	}
	cout << endl << "Pick time:" << endl;
	cout << "[1] 6 Am" << endl << "[2] 12 Pm" << endl << "[3] 6 Pm" << endl << "[4] 12 Am" << endl;
	int time;
	cin >> time;
	while (time < 0 || time > 4) {
		cout << "Invalid choice - Choose again:";
		cin >> time;
	}
	cout << "Enter the day:";
	int day;
	cin >> day;
	while (day < 0 || day > 31) {
		cout << "Invalid choice - Choose again:";
		cin >> day;
	}
	cout << "Enter the month:";
	int month;
	cin >> month;
	while (month < 0 || month > 12) {
		cout << "invalid choice - choose again:";
		cin >> month;
	}
	cout << "1. One way   2. Return  ";
	int x;
	cin >> x;
	while (x < 0 || x > 2) {
		cout << "invalid choice - choose again:";
		cin >> x;
	}
	cout << endl << "---------------------------------" << endl;

	cout << " Thank You " << username << " For choosing us !!" << endl;
	cout << "Your stations are : " << endl;
	ifstream file("des.txt");



	int sum = 100;
	bool startPrint = false;
	while (!file.eof()) {
		string t_name;
		file >> t_name;
		if (t_name == start)
			startPrint = true;
		if (t_name == end)
			startPrint = false;

		if (startPrint) {
			cout << t_name << " -> ";
			sum += 100;
		}
	}
	cout << end;

	cout << endl << endl << "Cost : " << sum * x;
	cout << endl << "---------------------------------";

	file.close();



}

void add_des() {
	cout << "Enter the name of the new destination: ";
	string name;
	cin >> name;
	fstream file("des.txt", ios::app);
	file << endl << name;
	file.close();
}

void view_des() {
	ifstream file("des.txt");
	string name;
	if (file.is_open()) {
		while (!file.eof()) {
			file >> name;
			cout << " ->  " << name;
		}
	}
	else {
		cout << "No Stations";
	}
}

void rem_des() {
	view_des();
	bool found = false;
	cout << endl << endl << "Enter the name of the destination you want to remove :";
	string name;
	cin >> name;

	ifstream file("des.txt");
	fstream file2("x.txt", ios::app);
	if (file.is_open()) {
		while (!file.eof()) {
			string t_name;
			file >> t_name;
			if (t_name != name)
				file2 << endl << t_name;
			else
				found = true;
		}
	}

	if (found)
		cout << name << " removed";
	else
		cout << name << " not found";

	file.close();
	file2.close();
	remove("des.txt");
	rename("x.txt", "des.txt");
}

void admin_menu() {
	cout << "1. View destinations" << endl;
	cout << "2. Add destination" << endl;
	cout << "3. Remove destinations" << endl;
	int c;
	cin >> c;
	if (c == 1) {
		view_des();
	}
	else if (c == 2) {
		add_des();
	}
	else if (c == 3) {
		rem_des();
	}
	else {
		exit(0);
	}
}

void login() {
	string username, password;
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	if (username == "admin" && password == "admin") {
		admin_menu();
	}
	else {

		bool found = false;
		ifstream file("user.txt");
		if (file.is_open()) {
			while (!file.eof()) {
				string t_username, t_pass;
				file >> t_username >> t_pass;
				if (t_username == username && t_pass == password) {
					found = true;
					file.close();
					customer_menu(username);
				}
			}
		}
		if (!found)
			cout << "Wrong username/password";
	}
}

void signup() {
	string username, password;
	cout << "Enter username :";
	cin >> username;
	cout << "Enter password :";
	cin >> password;

	bool found = true;
	while (found) {
		found = false;
		ifstream file2("user.txt");
		if (file2.is_open()) {
			while (!file2.eof()) {
				string t_username, t_pass;
				file2 >> t_username >> t_pass;
				if (t_username == username) {
					cout << "Username is Taken " << endl << "Enter again : ";
					cin >> username;
					found = true;
					file2.close();
					break;
				}
			}
		}
		else {
			break;
		}
	}

	fstream file("user.txt", ios::app);
	file << endl << username << " " << password;
	file.close();

}

int main() {
	cout << "1.Login" << endl;
	cout << "2.Sign up" << endl;
	int c;
	cin >> c;
	if (c == 1)
		login();
	else if (c == 2)
		signup();
	else
		exit(0);
}