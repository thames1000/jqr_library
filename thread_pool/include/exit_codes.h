#ifndef EXIT_CODES_H
#define EXIT_CODES_H

#include <stdio.h>
#include <stdlib.h>

// ENUM for custom error codes
typedef enum exit_code
{
    E_SUCCESS,       // Success code (must be first code)
    E_DEFAULT_ERROR, // Default error code (must be second code)

    // Other errors are listed by type

    // IO
    E_FILE_DOES_NOT_EXIST,
    E_FILE_NOT_READABLE,
    E_FILE_NOT_WRITEABLE,
    E_FILE_CREATION_FAILURE,
    E_DIRECTORY_DOES_NOT_EXIST,
    E_DIRECTORY_EXISTS,
    E_DIRECTORY_NOT_EMPTY,
    E_DIRECTORY_EMPTY,
    E_MKDIR_FAILURE,
    E_INVALID_INPUT,
    E_OUT_OF_BOUNDS,
    E_OUT_OF_ORDER,

    // OS
    E_FORK_ERROR,

    // Network
    E_HANGUP,
    E_PORT_RESTRICTED,
    E_PORT_ERROR,
    E_SOCKET_ERROR,
    E_HOST_ADDRESS_ERROR,
    E_BIND_ERROR,
    E_LISTEN_ERROR,
    E_RECEIVE_ERROR,

    // Memory Management
    E_CMR_FAILURE,  // Calloc, Malloc, Realloc failure
    E_NULL_POINTER, // Pointer is NULL

    // General Data Structures
    E_CONTAINER_DOES_NOT_EXIST, // Container does not exist
    E_CONTAINER_EMPTY,          // Container is empty
    E_CONTAINER_NOT_EMPTY,      // Container is not empty

    // Tree
    E_KEY_ALREADY_EXISTS, // Key already exists
    E_KEY_NOT_FOUND,      // Search key not found

    // Linked List
    E_TOO_SMALL, // Position is less than size of list
    E_TOO_BIG,   // Position is greater than size of list
} exit_code_t;

// struct using custom err_codes_t to print related error messages
typedef struct exit_message exit_message_t;

/**
 * @brief function to print custom exit messages.
 *
 * @param exit_code exit code by which to find the message string.
 */
void print_exit_message(exit_code_t exit_code);

#endif
