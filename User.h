

#ifndef USER_H_
#define USER_H_

#include "functions.h"


class User {
private:
	int userID;
	string userName;
	string password;
	string name;
	string email;
	int allowAnonymousQuestions;

	vector<int> questionsIDsfromMe;
	map<int, vector<int>> questionIDQuestionsIDsThread;

public:
	User();
	User(const string &line);
	virtual ~User();

	string toString() const;
	void ReadUser(const string &user_name, int id);
	void resetToQuestions(const vector<int>& toQuestions);
	void resetFromQuestions(const vector<pair<int, int>>& toQuestions);
	void print()const;

	int getIsAllowAnonymousQuestions() const;
	void setIsAllowAnonymousQuestions(int allowAnonymousQuestions);
	const string& getEmail() const;
	void setEmail(const string &email);
	const string& getName() const;
	void setName(const string &name);
	const string& getPassword() const;
	void setPassword(const string &password);
	const map<int, vector<int> >& getQuestionIdQuestionsIDsThread() const;
	void setQuestionIdQuestionsIDsThread(
			const map<int, vector<int> > &questionIdQuestionsIDsThread);
	const vector<int>& getQuestionsIDsfromMe() const;
	void setQuestionsIDsfromMe(const vector<int> &questionsIDsfromMe);
	int getUserId() const;
	void setUserId(int userId);
	const string& getUserName() const;
	void setUserName(const string &userName);
};

#endif /* USER_H_ */
