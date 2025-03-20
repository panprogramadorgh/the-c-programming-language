#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFFER_SIZE 1024 // 1KiB size

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
  str->pos = 0;
  free(str->mem);
}

/// @brief Writes buffer data of `buffer_size` length on internal string memory block
/// @param str 
/// @param buffer 
/// @param buffer_size 
/// @return The number of bytes written
size_t write_string(String *str, const char *buffer, const size_t buffer_size)
{
  int i = str->pos;
  while (i < str->size && (i - str->pos) < buffer_size)
  {
    str->mem[i] = buffer[i];
    i++;
  }
  str->pos = i;
  return str->pos;
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

  // Finaly we copy the internal memory block into dest
  int i = 0;
  while (dest->mem[i] = orig->mem[i])
    i++;
  
  // Once both internal memory blocks contains the same, size and pos fields are set
  dest->size = orig->size;
  dest->pos = i;

  return 0;
}


// TODO: Create print string function which reads internal heap memory block starting at pos and goes up until size is reached

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
  write_string(&str, str_init, str_init_len);

  print_line(str.mem);
  free_string(&str);

  return EXIT_SUCCESS;
}