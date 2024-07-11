#include "homeHandler.h"

homeHandler::homeHandler(homeService service) : internalservice(service) {}
void homeHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
	std::cout << "Inside Handlerequest!\n";
	std::vector<Task> tasks = internalservice.displayTasks();

	response.setChunkedTransferEncoding(true);
	response.setContentType("application/json");

	Poco::JSON::Array jsontasks;
	for (int index = 0; index < tasks.size(); index++) {
		Poco::JSON::Object jsontask = asJSON(tasks[index]);
		jsontasks.set(index, jsontask);
	}

	std::ostringstream ostr;

	Poco::JSON::Stringifier::stringify(jsontasks, ostr);

	std::ostream& ost = response.send();

	ost << ostr.str();
}
