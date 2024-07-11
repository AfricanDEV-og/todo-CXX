#include "actionShared.h"

actionShared::actionShared(Appstate& state) : internalstate(state) {}
Status actionShared::create_task(taskstr task) {
	Poco::Data::Statement insert(internalstate.session);

	insert << "INSERT INTO task (name, description) VALUES (?, ?)",
		Poco::Data::Keywords::use(task.name),
		Poco::Data::Keywords::use(task.description),
		Poco::Data::Keywords::now;

	if (insert.parseError() == "") {
		bool stat = true;
		std::string msg = "Task was created";

		return { stat, msg };
	}
	else {
		bool stat = false;
		std::string msg = "Action failed";

		return { stat, msg };
	}
}
Status actionShared::delete_task(int id) {
	Poco::Data::Statement deletekey(internalstate.session);

	deletekey << "DELETE FROM task WHERE id=?",
		Poco::Data::Keywords::use(id),
		Poco::Data::Keywords::now;

	if (deletekey.parseError() == "") {
		bool stat = true;
		std::string msg = "Task was deleted";

		return { stat, msg };
	}
	else {
		bool stat = false;
		std::string msg = "Action failed";

		return { stat, msg };
	}
}