#include "notfoundHandler.h"

notfoundHandler::notfoundHandler() {}
void notfoundHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
	response.setChunkedTransferEncoding(true);
	response.setContentType("text/plain");
	response.setStatus(HTTPResponse::HTTP_NOT_FOUND);

	std::ostream& ost = response.send();
	ost << "NOT FOUND";
}