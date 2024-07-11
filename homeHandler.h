#pragma once

#include "homeService.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

using namespace Poco::Net;

class homeHandler : public HTTPRequestHandler {
public:
	homeHandler(homeService service);

	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
private:
	homeService internalservice;
};