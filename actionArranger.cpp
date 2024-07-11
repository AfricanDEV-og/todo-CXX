#include "actionArranger.h"
#include "actionShared.h"

#include "createHandler.h"
#include "deleteHandler.h"
#include "notfoundHandler.h"

#include <regex>
#include <string>

HTTPRequestHandler* actionArranger(const HTTPServerRequest& request, Appstate& state) {
	std::smatch m;
	std::string uri = request.getURI();

	actionShared shared(state);
	if (uri  == "/api/task/create") {
		std::cout << "Inside create part\n";
		return new createHandler(shared);
	}
	else if (uri == "/api/task/delete") {
		std::cout << "Inside delete part\n";
		return new deleteHandler(shared);
	}
	else {
		return new notfoundHandler();
	}
}