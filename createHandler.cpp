#include "createHandler.h"

createHandler::createHandler(actionShared service) : internalservice(service) {}
void createHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
	std::string method = request.getMethod();

	if (method == HTTPRequest::HTTP_POST) {
		std::cout << "posting it\n";

		std::istream& ist = request.stream();
		std::string empty((std::istreambuf_iterator<char>(ist)),
			std::istreambuf_iterator<char>());

		std::cout << empty << std::endl;
		Poco::JSON::Parser parser;
		Poco::Dynamic::Var result = parser.parse(empty);

		Poco::JSON::Object::Ptr obj = result.extract<Poco::JSON::Object::Ptr>();

		Status s = internalservice.create_task({
			obj->getValue<std::string>("name"),
			obj->getValue<std::string>("description")
		});

		Poco::JSON::Object o;
		o.set("status", s.status);
		o.set("message", s.message);

		std::ostringstream resp;
		Poco::JSON::Stringifier::stringify(o, resp);

		// Configurate Response

		response.setChunkedTransferEncoding(true);
		response.setContentType("application/json");
		response.setStatus(HTTPResponse::HTTP_OK);

		std::ostream& ost = response.send();
		ost << resp.str();
	}
	else {
		response.setChunkedTransferEncoding(true);
		response.setContentType("text/plain");
		response.setStatus(HTTPResponse::HTTP_METHOD_NOT_ALLOWED);

		std::ostream& ost = response.send();
		ost << "method is not allowed";
	}
}