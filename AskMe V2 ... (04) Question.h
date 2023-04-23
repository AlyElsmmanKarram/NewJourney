

#ifndef QUESTION_H_
#define QUESTION_H_

#include "functions.h"


class Question {
private:
	int questionID;
	int parentQuestionID;
	int fromUserID;
	int toUserID;
	int isAnonymous;
	string question_text;
	string answer_text;

public:
	Question();
	virtual ~Question();
	Question(const string &line);
	string toString() const;
	void printFromQuestion() const;
	void printToQuestion() const;
	void printFeedQuestion() const;


	const string& getAnswerText() const;
	void setAnswerText(const string &answerText);
	int getFromUserId() const;
	void setFromUserId(int fromUserId);
	int getIsAnonymous() const;
	void setIsAnonymous(int isAnonymous);
	int getParentQuestionId() const;
	void setParentQuestionId(int parentQuestionId);
	const string& getQuestionText() const;
	void setQuestionText(const string &questionText);
	int getQuestionId() const;
	void setQuestionId(int questionId);
	int getToUserId() const;
	void setToUserId(int toUserId);
};


#endif /* QUESTION_H_ */
