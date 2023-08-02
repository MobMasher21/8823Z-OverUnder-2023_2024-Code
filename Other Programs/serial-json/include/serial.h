#include <stdio.h>

#include <string>

class Serial {
   private:
    FILE* in;
    FILE* out;

   public:
    Serial(FILE* in, FILE* out);
    ~Serial();

    void write(std::string data);
    void write(char data[], unsigned int size);

    std::string read_string();
    void read_bytes(char buf[], int size);

    unsigned int get_size();
};