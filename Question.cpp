

#include "Question.h"

Question::Question() : questionID(-1), parentQuestionID(-1), fromUserID(-1), toUserID(-1), isAnonymous(1), question_text(""), answer_text(""){
}

Question::~Question(){
}

Question::Question(const string& line){
	vector<string> subStrings = splitString(line);
	assert((int )subStrings.size() == 7 && "whoops,,, The input data is invalid\n\n");
	questionID = toInt(subStrings[0]);
	parentQuestionID = toInt(subStrings[1]);
	fromUserID = toInt(subStrings[2]);
	toUserID = toInt(subStrings[3]);
	isAnonymous = toInt(subStrings[4]);
	question_text = subStrings[5];
	answer_text = subStrings[6];
}

const string& Question::getAnswerText() const{
	return answer_text;
}

void Question::setAnswerText(const string& answerText){
	answer_text = answerText;
}

int Question::getFromUserId() const{
	return fromUserID;
}

void Question::setFromUserId(int fromUserId){
	fromUserID = fromUserId;
}

int Question::getIsAnonymous() const{
	return isAnonymous;
}

void Question::setIsAnonymous(int isAnonymous){
	this->isAnonymous = isAnonymous;
}

int Question::getParentQuestionId() const{
	return parentQuestionID;
}

void Question::setParentQuestionId(int parentQuestionId){
	parentQuestionID = parentQuestionId;
}

const string& Question::getQuestionText() const{
	return question_text;
}

void Question::setQuestionText(const string& questionText){
	question_text = questionText;
}

int Question::getQuestionId() const{
	return questionID;
}

void Question::setQuestionId(int questionId){
	questionID = questionId;
}

int Question::getToUserId() const{
	return toUserID;
}

void Question::setToUserId(int toUserId){
	toUserID = toUserId;
}

string Question::toString() const{
	ostringstream oss;
	oss << questionID << "," << parentQuestionID << "," << fromUserID << "," << toUserID << "," << isAnonymous << "," << question_text << ","
			<< answer_text;
	return oss.str();
}

void Question::printToQuestion() const{
	string prefix = "";
	if(parentQuestionID != -1){
		prefix = "\tThread: ";
	}
	cout << prefix << "Question ID (" << questionID << ")";
	if(!isAnonymous){
		cout << "from user ID (" << fromUserID << ")";
	}
	cout << "Question: " << question_text << "\n";
	if(answer_text != ""){
		cout << prefix << answer_text << "\n";
	}
	cout << "\n";
}

void Question::printFromQuestion() const{
	cout << "Question ID (" << questionID << ")";
	if(!isAnonymous){
		cout << " !AQ";
	}
	cout << " to user ID (" << toUserID << ")";
	cout << "\tQuestion: " << question_text;

	if(answer_text != ""){
		cout << "\tAnswer: " << answer_text << "\n";
	}else{
		cout << "\tNOT Answered YET\n";
	}
}

void Question::printFeedQuestion() const{
	if(parentQuestionID != -1){
		cout << "\tThread parent question ID (" << parentQuestionID << ") ";
	}
	cout << "Question ID (" << questionID << ") ";
	if(!isAnonymous){
		cout << "from user ID (" << fromUserID << ") ";
	}
	cout << "to user ID (" << toUserID << ") ";
	cout << "\n\tQuestion: " << question_text << "\n";
	if(answer_text != ""){
		cout << "\t Answer: " << answer_text << "\n";
	}
}
