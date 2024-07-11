#pragma once

#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/Statement.h"


#include "Appstate.h"

struct Status {
	bool status;
	std::string message;
};
class actionShared {
public:
	typedef struct {
		std::string name;
		std::string description;
	} taskstr;

	actionShared(Appstate& state);

	Status delete_task(int id);
	Status create_task(taskstr task);
private:
	Appstate& internalstate;
};
