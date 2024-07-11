#pragma once

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandler.h"

#include "Appstate.h"

using namespace Poco::Net;

HTTPRequestHandler* actionArranger(const HTTPServerRequest& request, Appstate& state);
