#include <map>
#include <string>
#include "variant.hpp"
namespace json {

enum types {
    string,
    decimal,
    integer,
    Boolean,
};

/// @brief Needed because a bool gets converted to an int-like when formated
/// @return a string of either "true" or "false"
const char* form_bool(bool value);

class Json_encoder {
   private:
    std::string fstring = "{";

   public:
    std::string get_fstring();

    void add_key(types type, std::string name);
    void add_key(types type, char* name);

    void finalize_keys();

    template <class... T>  // these have to be in a header file for some reason
    std::string encode(T... values) {
        int size = snprintf(NULL, 0, this->fstring.c_str(), values...) + 1;
        char out[size];

        sprintf(out, this->fstring.c_str(), values...);
        return std::string(out);
    }
};


}  // namespace json