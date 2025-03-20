#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFFER_SIZE 20

// String related macros
#define STRING_ERROR_ALLOC "string memory error: could not create internal memory block"

// ---------------------

typedef struct String
{
  // Represents the heap memory block pointer
  char *mem;
  // Represents the current size of `mem`
  size_t size;
  // Represents the current position at the heap
  size_t pos;
} String;

/// @brief Allocates a `initial_size`-length String in the heap.
/// @param str String pointer where to allocate the string
/// @param initial_size Initial size for the string
/// @return
// 0 -- Any error ocurred allocating new string internal memory block
// 1 -- Internal system call memomory allocation failure
unsigned char alloc_string(String *str, const size_t initial_size)
{
  char *line = (char *)malloc(sizeof(char) * initial_size);
  if (!line)
    return 1;

  size_t line_pos = 0;
  //              mem, size, pos
  *str = (String){line, initial_size, line_pos};
  return 0;
}

// Frees resource from `str` string pointer
void free_string(String *str)
{
  free(str->mem);
  str->pos = 0;
  str->size = 0;
}

/// @brief Moves internal string memory block ptr
/// @param str
/// @param pos
/// @return
// -1 -- Position is out of the size of the string
// Any other integer value -- Distance from current ptr position to previous one
size_t move_string(String *str, size_t pos)
{
  if (pos >= str->size)
    return -1;
  size_t prev_pos = str->pos;
  str->pos = pos;
  return abs(str->pos - prev_pos);
}

/// @brief Resizes the internal string memory block. After memory resizing it's important to update the string pointer position.
/// @param str
/// @param size
/// @return
// -1 -- Internal memory reallocation error
// Any other integer number -- Size difference between current and previous size
size_t resize_string(String *str, size_t size)
{
  str->mem = realloc(str->mem, size);
  if (!str->mem)
    return -1;

  size_t prev_size = str->size;
  str->size = size;

  return abs(str->size - prev_size);
}

/// @brief Reads internal string memory block starting from string pos into `buffer`
/// @param buffer
/// @param max_buffer_size
/// @param str
/// @return Readen bytes
size_t read_string(char *buffer, size_t max_buffer_size, String *str)
{
  size_t prev_pos = str->pos;
  while (str->pos < str->size && str->pos < max_buffer_size && (buffer[str->pos] = str->mem[str->pos]))
    str->pos++;
  return str->pos - prev_pos;
}

/// @brief Writes buffer data of `buffer_size` length on internal string memory block
/// @param str
/// @param buffer
/// @param buffer_size
/// @return
// -1 -- Internal memory reallocation error
// Any integer number -- The number of bytes written
size_t write_string_from_buffer(String *str, const char *buffer, const size_t buffer_size)
{
  // Internal memory resizement so then we can write data comming from buffer
  if (str->pos + buffer_size - str->size > 0) // Incrementing the memory block size
  {
    size_t new_size = (str->pos + buffer_size) * 2;
    if (resize_string(str, new_size) < 0)
      return -1;
  }
  // TODO: Check and ensure correct memory resizing
  else if (str->size / (str->pos + buffer_size) > 1) // Decreases the memory block size
  {
    size_t greater_multiple = str->size / (str->pos + buffer_size);
    size_t new_size = greater_multiple * (str->pos + buffer_size);

    if (resize_string(str, new_size) < 0)
      return -1;
  }

  size_t prev_pos = str->pos;
  while (prev_pos < str->size && (str->pos - prev_pos) < buffer_size)
  {
    str->mem[str->pos] = buffer[str->pos];
    str->pos++;
  }
  return str->pos - prev_pos;
}

/// @brief Copies `dest` to `orig`
/// @param dest Destiny
/// @param orig Origin
/// @return
// 0 -- No errors have happend
// 1 -- Internal system call memory block allocation failure
unsigned char copy_string(String *dest, const String *orig)
{
  // Frees the internal destiny string memory block (if size is greater than 0)
  if (dest->size)
    free_string(dest);

  // New memory block is allocated
  dest->mem = (char *)malloc(sizeof(char) * orig->size);
  if (!dest->mem)
    return 1;
  dest->size = orig->size;

  // Finaly we copy the internal memory block into dest
  size_t current_pos = 0;
  while (dest->mem[current_pos] = orig->mem[current_pos])
    current_pos++;

  return 0;
}

// Low level functions and utilities

/// @brief Same use as with strlen standard library utility
/// @param line
/// @return Line length as an integer
size_t chcount_line(const char *line)
{
  int i = 0;
  while (line[i++])
    ;
  return i;
}

// Prints an array of characters
void print_line(const char *line)
{
  for (int i = 0; line[i]; i++)
  {
    putchar(line[i]);
  }
}

// ------------------------

int main()
{
  String str;
  const char *str_init = "hello world\n";
  size_t str_init_len = chcount_line(str_init);

  if (alloc_string(&str, BUFFER_SIZE))
  {
    errno = EXIT_FAILURE;
    perror(STRING_ERROR_ALLOC);
    exit(errno);
  }
  printf("%ld\n", str.size);
  write_string_from_buffer(&str, str_init, str_init_len);
  move_string(&str, 0);
  printf("%ld\n", str.size);

  free_string(&str);
  return EXIT_SUCCESS;
}