

#include "AskMeSystem.h"

AskMeSystem::AskMeSystem(){
// TODO Auto-generated constructor stub
}

void AskMeSystem::loadDataBase(bool fillUserQuestions){


	usersManager.loadDataBase();
	questionManager.loadDataBase();

	if(fillUserQuestions){
		resetCurrentUserQuestions();
	}
}

void AskMeSystem::resetCurrentUserQuestions(){
	const User& user = usersManager.getCurrentUser();

	const auto& toQuestions = questionManager.getUserToQuestions(user);

	usersManager.resetToQuestions(toQuestions);

	const auto& fromQuestions = questionManager.getUserFromQuestions(user);
	usersManager.resetFromQuestions(fromQuestions);

}

AskMeSystem::~AskMeSystem(){
// TODO Auto-generated destructor stub
}

void AskMeSystem::RUN(){
	loadDataBase(false);
	usersManager.accessSystem();
	resetCurrentUserQuestions();
	vector<string> menu;
	menu.push_back("Print Questions To Me");
	menu.push_back("Print Questions From Me");
	menu.push_back("Answer Question");
	menu.push_back("Delete Question");
	menu.push_back("Ask Question");
	menu.push_back("List System Users");
	menu.push_back("Feed");
	menu.push_back("Logout");

	while(true){
		int choice = showReadMenu(menu);
		loadDataBase(true);

		if(choice == 1)
			questionManager.printUserToQuestions(usersManager.getCurrentUser());
		else if(choice == 2)
			questionManager.printUserFromQuestions(usersManager.getCurrentUser());
		else if(choice == 3){
			questionManager.answerQuestion(usersManager.getCurrentUser());
			questionManager.updateDataBase();
		}else if(choice == 4){
			questionManager.deleteQuestion(usersManager.getCurrentUser());
			resetCurrentUserQuestions();
			questionManager.updateDataBase();
		}else if(choice == 5){// if i remove brackets a cross initialization error will appear
			auto [id, isAnonymous] = usersManager.readUserID();
			if(id != -1){
				questionManager.askQuestion(usersManager.getCurrentUser(), {id, isAnonymous});
				questionManager.updateDataBase();
			}
		}else if(choice == 6)
			usersManager.listUserNamesIDs();
		else if(choice == 7)
			questionManager.listFeed();
		else
			break;
	}

	RUN();
}
