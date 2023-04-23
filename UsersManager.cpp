

#include "UsersManager.h"

UsersManager::UsersManager() :
		lastID(0) {
}
UsersManager::~UsersManager() {

}

void UsersManager::loadDataBase() {
	lastID = 0;

	userNameToUserObject.clear();
	vector<string> lines = ReadFileLines("users.txt");

	for (const auto &line : lines) {
		User user(line);
		userNameToUserObject[user.getUserName()] = user;
		lastID = max(lastID, user.getUserId());
	}

}

void UsersManager::accessSystem() {
	int choice = showReadMenu( { "Login", "SignUp" });
	if (choice == 1) {
		doLogin();
	} else {
		doSignUp();
	}
}

void UsersManager::doLogin() {
	loadDataBase();
	while (true) {
		string name, password;
		cout << "Enter User Name: ";
		cin >> name;
		cout << "\nEnter Password: ";
		cin >> password;
		currentUser.setUserName(name);
		currentUser.setPassword(password);

		if (!userNameToUserObject.count(currentUser.getUserName())) {
			cout << "\nInvalid User Name or Password!!! Try again...\n\n";
			continue;
		}
		const User& user_exist = userNameToUserObject[currentUser.getUserName()];
		if (currentUser.getPassword() != user_exist.getPassword() ) {
			cout << "\nInvalid User Name or Password!!! Try again...\n\n";
			continue;
		}
		currentUser = user_exist;
		break;
	}
}

void UsersManager::doSignUp() {
	string userName;
	while(true){
		cout << "Enter UserName (no spaces): ";
		cin >> userName;
		if(userNameToUserObject.count(userName)){
			cout << "This UserName Already used!!! Try another one...\n";
		}else{
			break;
		}
	}
	currentUser.ReadUser(userName, ++lastID);
	userNameToUserObject[currentUser.getUserName()] = currentUser;

	updateDataBase(currentUser);
}

void UsersManager::resetToQuestions(const vector<int> toQuestions){
	currentUser.resetToQuestions(toQuestions);
}

void UsersManager::resetFromQuestions(const vector<pair<int, int> >& toQuestions){
	currentUser.resetFromQuestions(toQuestions);
}

void UsersManager::listUserNamesIDs() {
	for(const auto& [name, user] : userNameToUserObject){
		cout <<"ID: " << user.getUserId() << "\t\tName: " << user.getName() <<"\n";
	}
}

pair<int, int> UsersManager::readUserID() {
	int userID;
	cout << "Enter User ID \"or -1 to cancel\": ";
	cin >> userID;
	if(userID == -1){
		return {-1, -1};
	}
	for(const auto &[name, user] : userNameToUserObject){
		if(userID == user.getUserId()){
			return {user.getUserId(), user.getIsAllowAnonymousQuestions()};
		}
	}
	cout << "Invalid ID!!! Try again...\n";
	return readUserID();
}

void UsersManager::updateDataBase(const User& user) {
	string line = user.toString();
	vector<string>lines(1, line);
	writeFileLines("users.txt", lines);
}

const User& UsersManager::getCurrentUser() const {
	return currentUser;
}

int UsersManager::getLastId() const {
	return lastID;
}


void UsersManager::setLastId(int lastId) {
	lastID = lastId;
}

