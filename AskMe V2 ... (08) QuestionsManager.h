

#ifndef QUESTIONSMANAGER_H_
#define QUESTIONSMANAGER_H_

#include "Question.h"
#include "User.h"

class QuestionsManager {
private:
	map<int, vector<int>> questionIDQuestionsIDsThread;

	map<int, Question> questionIDQuestinosObject;

	int lastID;

public:
	QuestionsManager();
	virtual ~QuestionsManager();
	QuestionsManager(const QuestionsManager &other) = delete;
	QuestionsManager& operator=(const QuestionsManager &other) = delete;

	void loadDataBase();
	vector<int> getUserToQuestions(const User &user) const;
	vector<pair<int, int>> getUserFromQuestions(const User &user) const;
	void printUserToQuestions(const User &user) const;
	void printUserFromQuestions(const User &user) const;
	int readQuestionIDAny(const User &user) const;
	int readQuestionIDThread(const User &user) const;
	void answerQuestion(const User &user);
	void deleteQuestion(const User &user);
	void askQuestion(const User &user,
			const pair<int, int> &toUserIDandAnonymousPair);
	void listFeed() const;
	void updateDataBase();


	int getLastId() const;
	void setLastId(int lastId);
	const map<int, vector<int> >& getquestionIDQuestionsIDsThread() const;
	void setquestionIDQuestionsIDsThread(
			const map<int, vector<int> > &questionIDQuestionsIDsThread);
	const map<int, Question>& getQuestionIdQuestinosObjectPointer() const;
	void setQuestionIdQuestinosObjectPointer(
			const map<int, Question> &questionIdQuestinosObject);
};

#endif /* QUESTIONSMANAGER_H_ */
