#include "exit_codes.h"

// Citation:
// https://stackoverflow.com/questions/6286874/c-naming-suggestion-for-error-code-enums

struct exit_message
{
    int code;
    const char *message;
}

exit_message[] =
    {
        {E_SUCCESS, "No errors.\n"}, // Success is first error
        {E_DEFAULT_ERROR, "Success state never achieved.\n"},

        // Other errors are listed by type

        // IO
        {E_FILE_DOES_NOT_EXIST, "File does not exist.\n"},
        {E_FILE_NOT_READABLE, "File cannot be read.\n"},
        {E_FILE_NOT_WRITEABLE, "File cannot be written to.\n"},
        {E_FILE_CREATION_FAILURE, "File cannot be created.\n"},
        {E_DIRECTORY_DOES_NOT_EXIST, "Directory does not exist.\n"},
        {E_DIRECTORY_EXISTS, "Directory exists.\n"},
        {E_DIRECTORY_NOT_EMPTY, "Directory is not empty.\n"},
        {E_DIRECTORY_EMPTY, "Directory is empty.\n"},
        {E_MKDIR_FAILURE, "Failed to create directory.\n"},
        {E_INVALID_INPUT, "Invalid input.\n"},
        {E_OUT_OF_BOUNDS, "Out of bounds.\n"},
        {E_OUT_OF_ORDER, "Out of order\n"},
        // OS
        {E_FORK_ERROR, "Error trying to fork.\n"},

        // Network
        {E_HANGUP, "Server hangup.\n"},
        {E_PORT_RESTRICTED, "Restricted port.\n"},
        {E_PORT_ERROR, "Unknown port error.\n"},
        {E_SOCKET_ERROR, "Unknown socket error.\n"},
        {E_HOST_ADDRESS_ERROR, "Unknown host address error.\n"},
        {E_BIND_ERROR, "Unable to bind socket.\n"},
        {E_LISTEN_ERROR, "Unknown listen error.\n"},
        {E_RECEIVE_ERROR, "Unable to receive.\n"},

        // Memory Management
        {E_CMR_FAILURE, "Calloc / malloc / realloc failure.\n"},
        {E_NULL_POINTER, "Unexpected NULL pointer detected.\n"},

        // General Data Structures
        {E_CONTAINER_DOES_NOT_EXIST, "Container does not exist.\n"},
        {E_CONTAINER_EMPTY, "Container empty when expected to be occupied.\n"},
        {E_CONTAINER_NOT_EMPTY, "Container occupied when expected to be empty.\n"},

        // Tree
        {E_KEY_ALREADY_EXISTS, "Key already exists in tree.\n"},
        {E_KEY_NOT_FOUND, "Search key not found in tree.\n"},

        // Linked List
        {E_TOO_BIG, "Position is greater than size of list.\n"},
        {E_TOO_SMALL, "Position is less than size of list.\n"},
};

void print_exit_message(exit_code_t exit_code)
{
    if (E_SUCCESS == exit_code)
    {
        return;
    }

    if ((sizeof exit_message / sizeof exit_message[0]) > exit_code)
    {
        fprintf(stderr, "%s", exit_message[exit_code].message);
    }
    else
    {
        fprintf(stderr, "Unknown error detected.\n");
    }

    return;
}
