

#ifndef USERSMANAGER_H_
#define USERSMANAGER_H_
#include "User.h"

class UsersManager {
private:
	map<string, User> userNameToUserObject;
	User currentUser;
	int lastID;
public:
	UsersManager();
	virtual ~UsersManager();
	UsersManager(const UsersManager &other);
	UsersManager& operator=(const UsersManager &other);
	void loadDataBase();
	void accessSystem();
	void doLogin();
	void doSignUp();
	void listUserNamesIDs();
	pair<int, int> readUserID();
	void updateDataBase(const User &user);
	void resetToQuestions(const vector<int> toQuestions);
	void resetFromQuestions(const vector<pair<int, int>>& toQuestions);

	const User& getCurrentUser() const;
	void setCurrentUser(const User &currentUser);
	int getLastId() const;
	void setLastId(int lastId);

};

#endif /* USERSMANAGER_H_ */
