#include "serial.h"

#include <stdio.h>
#include <stdlib.h>

#include <string>

Serial::Serial(FILE* in, FILE* out) : in(in), out(out) {}

void Serial::write(std::string data) {
    // gets the data's size
    unsigned int size = data.size();

    // converts the size into bytes that can be easily sent over the connection
    char sizeData[4] = {(char)size, (char)(size >> 8), (char)(size >> 16), (char)(size >> 24)};

    // sends the bytes
    fputc(sizeData[0], this->out);
    fputc(sizeData[1], this->out);
    fputc(sizeData[2], this->out);
    fputc(sizeData[3], this->out);

    // write the ddata
    for (int i = 0; i < size; i++) {
        fputc(data[i], this->out);
    }
}

void Serial::write(char data[], unsigned int size) {
    // converts the size into bytes that can be easily sent over the connection
    char sizeData[4] = {(char)size, (char)(size >> 8), (char)(size >> 16), (char)(size >> 24)};

    // sends the bytes
    fputc(sizeData[0], this->out);
    fputc(sizeData[1], this->out);
    fputc(sizeData[2], this->out);
    fputc(sizeData[3], this->out);

    // write the data
    for (int i = 0; i < size; i++) {
        fputc(data[i], this->out);
    }
}

std::string Serial::read_string() {
    unsigned int size = get_size();

    char str[size];

    for (int i = 0; i < size; i++) {
        str[i] = fgetc(this->in);
    }

    return std::string(str);
}

void Serial::read_bytes(char buf[], int size) {
    for (int i = 0; i < size; i++) {
        buf[i] = fgetc(this->in);
    }
}

unsigned int Serial::get_size() {
    unsigned int size = (fgetc(this->in) << 24) | (fgetc(this->in) << 16) | (fgetc(this->in) << 8) | fgetc(this->in);
    size = __builtin_bswap32(size);

    return size;
}