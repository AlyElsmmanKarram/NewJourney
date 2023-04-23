

#include "QuestionsManager.h"

QuestionsManager::QuestionsManager() : lastID(0){
//cout << "Hello QuestionManager constructor :D \n";
}

QuestionsManager::~QuestionsManager(){
//cout << "Bye QuesionManager destructor :( \n";
}

void QuestionsManager::loadDataBase(){
	lastID = 0;
	questionIDQuestionsIDsThread.clear();
	questionIDQuestinosObject.clear();

	vector<string> lines = ReadFileLines("questions.txt");
	for(const auto& line : lines){
		Question question(line);
		lastID = max(lastID, question.getQuestionId());

		questionIDQuestinosObject[question.getQuestionId()] = question;

		if(question.getParentQuestionId() == -1){
			questionIDQuestionsIDsThread[question.getQuestionId()].push_back(question.getQuestionId());
		}else{
			questionIDQuestionsIDsThread[question.getParentQuestionId()].push_back(question.getQuestionId());
		}
	}
}

vector<int> QuestionsManager::getUserToQuestions(const User& user) const{
	vector<int> questionIDs;
	for(const auto& pair : questionIDQuestionsIDsThread){
		for(const int& questionID : pair.second){
			const Question& question = questionIDQuestinosObject.find(questionID)->second;// [() because of const
			if(question.getFromUserId() == user.getUserId()){
				questionIDs.push_back(question.getQuestionId());
			}
		}
	}
	return questionIDs;
}

vector<pair<int, int> > QuestionsManager::getUserFromQuestions(const User& user) const{
	vector<pair<int, int>> questionIDs;
	for(const auto& pair : questionIDQuestionsIDsThread){
		for(const auto& questionID : pair.second){
			const Question& question = questionIDQuestinosObject.find(questionID)->second;// [() because of const

			if(question.getToUserId() == user.getUserId()){
				if(question.getParentQuestionId() == -1){
					questionIDs.push_back( {question.getQuestionId(), question.getQuestionId()});
				}else{
					questionIDs.push_back( {question.getParentQuestionId(), question.getQuestionId()});
				}
			}
		}
	}
	return questionIDs;
}

void QuestionsManager::printUserToQuestions(const User& user) const{
	cout << "\n";
	if(user.getQuestionIdQuestionsIDsThread().size() == 0){
		cout << "There are No Questions...\n";
	}
	for(const auto& pair : user.getQuestionIdQuestionsIDsThread()){
		for(const auto& questionID : pair.second){
			const Question& question = questionIDQuestinosObject.find(questionID)->second;
			question.printToQuestion();
		}
	}
	cout << "\n";
}

void QuestionsManager::printUserFromQuestions(const User& user) const{
	cout << "\n";
	if(user.getQuestionsIDsfromMe().size() == 0){
		cout << "There are No Questions...\n";
	}

	for(const auto& questionID : user.getQuestionsIDsfromMe()){
		const Question& question = questionIDQuestinosObject.find(questionID)->second;
		question.printFromQuestion();
	}
	cout << "\n";
}

int QuestionsManager::readQuestionIDAny(const User& user) const{
	int questionID;
	cout << "Enter question ID or -1 to cancel: ";
	cin >> questionID;

	if(questionID == -1){
		return -1;
	}
	if(!questionIDQuestinosObject.count(questionID)){
		cout << "Error: Invalid question ID!!! Try again...\n\n";
		return readQuestionIDAny(user);
	}
	const Question& question = questionIDQuestinosObject.find(questionID)->second;
	if(question.getToUserId() != user.getUserId()){
		cout << "Error: Invalid question ID!!! Try again...\n\n";
		return readQuestionIDAny(user);
	}
	return questionID;
}

int QuestionsManager::readQuestionIDThread(const User& user) const{
	int questionID;
	cout << "For thread question. Enter question ID or -1 for new question: ";
	cin >> questionID;

	if(questionID == -1){
		return -1;
	}

	if(!questionIDQuestionsIDsThread.count(questionID)){
		cout << "Error: Invalid question ID!!! Try again...\n\n";
		return readQuestionIDThread(user);
	}
	return questionID;
}

void QuestionsManager::answerQuestion(const User& user){
	int questionID = readQuestionIDAny(user);
	if(questionID == -1){
		return;
	}
	Question& question = questionIDQuestinosObject[questionID];
	question.printToQuestion();
	if(question.getAnswerText() != ""){
		cout << "\nWarning: This question is Already Answered. Your answer will be updated.\n";
	}
	cout << "Enter Answer: ";// don't enter comma','

	string ans;
	getline(cin, ans);
	getline(cin, ans);
	question.setAnswerText(ans);
	question.printFeedQuestion();
}

void QuestionsManager::deleteQuestion(const User& user){
	int questionID = readQuestionIDAny(user);

	if(questionID == -1){
		return;
	}

	vector<int> idsToRemove;

	if(questionIDQuestionsIDsThread.count(questionID)){
		idsToRemove = questionIDQuestionsIDsThread[questionID];
		questionIDQuestionsIDsThread.erase(questionID);
	}else{
		idsToRemove.push_back(questionID);

		for(auto& [id, vec] : questionIDQuestionsIDsThread){
			for(int pos = 0; pos < (int) vec.size(); pos++){
				if(questionID == vec[pos]){
					vec.erase(vec.begin() + pos);
					break;
				}
			}
		}
	}
}

void QuestionsManager::askQuestion(const User& user, const pair<int, int>& toUserIDandAnonymousPair){
	Question question;
	if(!toUserIDandAnonymousPair.second){// not allowing anonymous
		cout << "Note: Anonymous questions are not allowed for this user.\n";
		question.setIsAnonymous(0);
	}else{
		cout << "Is anonymous question?:(0 or 1) : ";
		int st;
		cin >> st;
		question.setIsAnonymous(st);
	}
	question.setParentQuestionId(readQuestionIDThread(user));
	cout << "Enter question: ";
	string quest;
	getline(cin, quest);
	getline(cin, quest);
	question.setQuestionText(quest);
	question.setFromUserId(user.getUserId());
	question.setToUserId(toUserIDandAnonymousPair.first);
	question.setQuestionId(++lastID);// wrong handling for parallel sessions
	questionIDQuestinosObject[question.getQuestionId()] = question;

	if(question.getParentQuestionId() == -1){
		questionIDQuestionsIDsThread[question.getQuestionId()].push_back(question.getQuestionId());
	}else{
		questionIDQuestionsIDsThread[question.getParentQuestionId()].push_back(question.getQuestionId());
	}
}

void QuestionsManager::listFeed() const{
	for(const auto& pair : questionIDQuestinosObject){
		const Question& question = pair.second;

		if(question.getAnswerText() == "")
			continue;

		question.printFeedQuestion();
	}
}

void QuestionsManager::updateDataBase(){
	vector<string> lines;
	for(const auto& pair : questionIDQuestinosObject){
		lines.push_back(pair.second.toString());
	}
	writeFileLines("questions.txt", lines, false);
}

int QuestionsManager::getLastId() const{
	return lastID;
}

void QuestionsManager::setLastId(int lastId){
	lastID = lastId;
}

const map<int, vector<int> >& QuestionsManager::getquestionIDQuestionsIDsThread() const{
	return questionIDQuestionsIDsThread;
}

void QuestionsManager::setquestionIDQuestionsIDsThread(const map<int, vector<int> >& questionIdQuestionsIDsThread){
	questionIDQuestionsIDsThread = questionIdQuestionsIDsThread;
}
