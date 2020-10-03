#include "Parameter.h"

Parameter::Parameter(string command) {
    parameters = explode(command, ' ');
}

vector<string> Parameter::getParameters() {
    return parameters;
}

vector<string> Parameter::explode(string const& command, char separator) {
    vector<string> result;
    istringstream iss(command);

    for (std::string token; getline(iss, token, separator); ) {
        result.push_back(std::move(token));
    }

    return result;
}
