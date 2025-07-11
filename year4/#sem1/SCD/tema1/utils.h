#include <sstream>
#include <string>
#include <vector>

#include "oauth.h"

std::vector<std::string> SplitString(std::string str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

std::string ReturnCodeToString(enum return_code code) {
    switch (code) {
        case return_code::OK:
            return "OK";
        case return_code::USER_NOT_FOUND:
            return "USER_NOT_FOUND";
        case return_code::NOT_SIGNED:
            return "NOT_SIGNED";
        case return_code::SIGNED:
            return "SIGNED";
        case return_code::OPERATION_NOT_PERMITTED:
            return "OPERATION_NOT_PERMITTED";
        case return_code::PERMISSION_DENIED:
            return "PERMISSION_DENIED";
        case return_code::TOKEN_EXPIRED:
            return "TOKEN_EXPIRED";
        case return_code::RESOURCE_NOT_FOUND:
            return "RESOURCE_NOT_FOUND";
        case return_code::REQUEST_DENIED:
            return "REQUEST_DENIED";
        case return_code::PERMISSION_GRANTED:
            return "PERMISSION_GRANTED";
        default:
            return "UNKNOWN";
    }
}

enum action StringToAction(std::string action) {
    if (action == "READ") {
        return action::READ;
    } else if (action == "INSERT") {
        return action::INSERT;
    } else if (action == "MODIFY") {
        return action::MODIFY;
    } else if (action == "DELETE") {
        return action::DELETE;
    } else if (action == "EXECUTE") {
        return action::EXECUTE;
    } else {
        return action::ERROR;
    }
}
