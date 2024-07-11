#pragma once

#include <string>
#include <vector>

#include "Poco/Data/Binding.h"
#include "Appstate.h"

#include "Poco/JSON/Object.h"

#include "Taskstruct.h"

Poco::JSON::Object asJSON(Task task);

class homeService {
public:
	homeService(Appstate& state);

	std::vector<Task> displayTasks();
private:
	Appstate& internalstate;
};


