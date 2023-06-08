#ifndef MY_STRTOK
#define MY_STRTOK

#include <iostream>
#include <cstring>

char* myStrtok(char* str, const char* delimiter) {
    static char* buffer = nullptr;
    if (str != nullptr)
        buffer = str;
    else if (buffer == nullptr)
        return nullptr;

    char* token = buffer;
    char* delimiterPtr = std::strpbrk(buffer, delimiter);

    // Buscar comillas dobles
    char* doubleQuotesPtr = std::strchr(buffer, '\"');
    if (doubleQuotesPtr != nullptr && (delimiterPtr == nullptr || doubleQuotesPtr < delimiterPtr)) {
        // Buscar la siguiente comilla doble
        char* closingQuotesPtr = std::strchr(doubleQuotesPtr + 1, '\"');
        if (closingQuotesPtr != nullptr) {
            // Encontrar el próximo delimitador después de las comillas dobles
            delimiterPtr = std::strpbrk(closingQuotesPtr + 1, delimiter);

            // Si se encuentra un delimitador, reemplazarlo por un carácter nulo
            if (delimiterPtr != nullptr) {
                *delimiterPtr = '\0';
                buffer = delimiterPtr + 1;
            } else {
                buffer = nullptr;
            }

            return token;
        }
    }

    if (delimiterPtr != nullptr) {
        *delimiterPtr = '\0';
        buffer = delimiterPtr + 1;
    } else {
        buffer = nullptr;
    }

    return token;
}


#endif