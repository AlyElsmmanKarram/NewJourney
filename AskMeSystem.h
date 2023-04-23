

#ifndef ASKMESYSTEM_H_
#define ASKMESYSTEM_H_

#include "QuestionsManager.h"
#include "UsersManager.h"

class AskMeSystem {
private:
	UsersManager usersManager;
	QuestionsManager questionManager;

	void loadDataBase(bool fillUserQuestions = false);
	void resetCurrentUserQuestions();
public:
	AskMeSystem();
	virtual ~AskMeSystem();
	AskMeSystem(const AskMeSystem &other) = delete;
	AskMeSystem& operator=(const AskMeSystem &other) = delete;
	void RUN();

};

#endif /* ASKMESYSTEM_H_ */
