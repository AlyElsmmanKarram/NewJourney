

#include "User.h"

User::User() :
		userID(-1), allowAnonymousQuestions(-1) {
}
User::User(const string &line) {

	vector<string> subStrings = splitString(line);
	assert((int)subStrings.size() == 6 && "whoops,,, The input data is invalid\n\n");
	userID = toInt(subStrings[0]);
	userName = subStrings[1];
	password = subStrings[2];
	name = subStrings[3];
	email = subStrings[4];
	allowAnonymousQuestions = toInt(subStrings[5]);
}

User::~User() {
	//cout << "Bye User destructor :( \n";
}

string User::toString() const {
	ostringstream oss;
	oss << userID << "," << userName << "," << password << "," << name << ","
			<< email << "," << allowAnonymousQuestions;
	return oss.str();
}

void User::print() const {
	cout << "User: " << userID << ", " << userName << " " << password << ", "
			<< email << "\n";
}
void User::resetToQuestions(const vector<int> &toQuestions) {
	questionsIDsfromMe.clear();

	for (const auto &questionID : toQuestions) {
		questionsIDsfromMe.push_back(questionID);
	}
}

void User::resetFromQuestions(const vector<pair<int, int> > &toQuestions) {
	questionIDQuestionsIDsThread.clear();

	for (const auto &pairID : toQuestions) {
		questionIDQuestionsIDsThread[pairID.first].push_back(pairID.second);
	}
}
void User::ReadUser(const string &user_name, int id) {
	setUserName(user_name);
	setUserId(id);

	string str;
	cout << "Enter password: ";
	cin >> str;
	setPassword(str);

	cout << "Enter name: ";
	cin >> str;
	setName(str);

	cout << "Enter email: ";
	cin >> str;
	setEmail(str);

	cout << "Allow anonymous questions? (0 or 1): ";
	int st;
	cin >> st;
	setIsAllowAnonymousQuestions(st);
}



int User::getIsAllowAnonymousQuestions() const {
	return allowAnonymousQuestions;
}

void User::setIsAllowAnonymousQuestions(int allowAnonymousQuestions) {
	this->allowAnonymousQuestions = allowAnonymousQuestions;
}

const string& User::getEmail() const {
	return email;
}

void User::setEmail(const string &email) {
	this->email = email;
}

const string& User::getName() const {
	return name;
}

void User::setName(const string &name) {
	this->name = name;
}

const string& User::getPassword() const {
	return password;
}

void User::setPassword(const string &password) {
	this->password = password;
}

const map<int, vector<int> >& User::getQuestionIdQuestionsIDsThread() const {
	return questionIDQuestionsIDsThread;
}

void User::setQuestionIdQuestionsIDsThread(
		const map<int, vector<int> > &questionIdQuestionsIDsThread) {
	questionIDQuestionsIDsThread = questionIdQuestionsIDsThread;
}

const vector<int>& User::getQuestionsIDsfromMe() const {
	return questionsIDsfromMe;
}

void User::setQuestionsIDsfromMe(const vector<int> &questionsIDsfromMe) {
	this->questionsIDsfromMe = questionsIDsfromMe;
}

int User::getUserId() const {
	return userID;
}

void User::setUserId(int userId) {
	userID = userId;
}

const string& User::getUserName() const {
	return userName;
}

void User::setUserName(const string &userName) {
	this->userName = userName;
}

