#include "homeService.h"

#include "Poco/Tuple.h"
#include "Taskstruct.h"

homeService::homeService(Appstate& state) : internalstate(state) {}
std::vector<Task> homeService::displayTasks() {
	std::cout << "Inside handlerequest\n";
	typedef Poco::Tuple<std::string, std::string, int> Taskem;
	typedef std::vector<Taskem> Taskems;
	Taskems ts;

	std::vector<Task> tasks;

	Poco::Data::Statement select(internalstate.session);

	select << "SELECT name, description, id FROM task", Poco::Data::Keywords::into(ts), Poco::Data::Keywords::now;
	
	for (auto t : ts) {
		Task task;

		task.name = t.get<0>();
		task.description = t.get<1>();
		task.id = t.get<2>();

		tasks.push_back(task);
	}


	return tasks;
}

Poco::JSON::Object asJSON(Task task) {
	Poco::JSON::Object json;
	
	json.set("id", task.id);
	json.set("name", task.name);
	json.set("description", task.description);

	return json;
}