#include "json.h"

#include <string>

using namespace json;

const char* json::from_bool(bool value) { return value ? "true" : "false"; }

std::string Json_encoder::get_fstring() {
    return this->fstring;
}

void Json_encoder::add_key(types type, std::string name) {
    switch (type) {
        case string:
            this->fstring.append("\"" + name + "\": \"%s\", ");
            break;

        case decimal:
            this->fstring.append("\"" + name + "\": %g, ");
            break;

        case integer:
            this->fstring.append("\"" + name + "\": %i, ");
            break;

        case boolean:
            this->fstring.append("\"" + name + "\": %s, ");  // same as string but without quotes
            break;
        
        case json:
            this->fstring.append("\"" + name + "\": \"%s\", "); // nested json is just another string
            break;
    }
}

void Json_encoder::add_key(types type, char* name) {
    add_key(type, std::string(name));
}

void Json_encoder::finalize_keys() {
    // get the index of the last ","
    int index = this->fstring.find_last_of(',');
    
    // replace the charicter at that index with "}"
    this->fstring[index] = '}';

    // there is still a space left behined so this removes it
    this->fstring[index+1] = '\n';
}
