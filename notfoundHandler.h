#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

using namespace Poco::Net;

class notfoundHandler : public HTTPRequestHandler {
public:
	notfoundHandler();

	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
};