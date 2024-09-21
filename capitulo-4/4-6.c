#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/* Determines the maximum length for the stack values. */
#define MAXSTACK (1U << 6)

/* Determines the maximum length in characters of the number to input. If the maximum is reached, the excess is divested. */
#define MAXD (1U << 5)

/* Max length for the variables array. */
#define MAXVAR (1U << 10)

/* ANSI scape codes for colors. */
#define RED "\x1b[31m"
#define BLUE "\x1b[34m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"
/* ------------------------------ */

/* Defines the input signals for `getinput`. */
enum inptypes
{
  UNINIT_INPTYPE, // Input type signal for uninitialized value.
  NUMBER,
  OPERATOR,
  VARIABLE,
  COMMAND, // Input type signal for commands (ex: \q equivalent to EXIT signal)
  EXIT     // Input type signal for program exit.
};

/* Defines the available operators to be choosen in `getinput`. */
enum operators
{
  UNINIT_OP, // Operator signal for uninitialized value.
  ADD = '+',
  SUB = '-',
  MUL = '*',
  DIV = '/',
  MOD = '%'
};

enum commands
{
  QUIT = 'q',     // Ends all calc stacks.
  NEXT = 'n',     // Steps over the next calc stack.
  STACK = 's',    // Prints the stack.
  LASTSTACK = 'l' // Prins the last stack.
};

/* Allows to get the user input for calculator. Different input types defined in `inptypes` enum. */
int getinput();

/* Allows to copy literal strings. */
void copystr(const char from[], char to[]);

/* Stack utilities. */
/* Pushes a new value to the stack. */
void push(double value);

/* Removes and returns the last value in the stack. */
double pop(void);

/* Returns the last value in the stack. */
double head(void);

/* Duplicates the last element in the stack. */
void duplast(void);

/* Swaps the last two elements in the stack. */
void swap(void);

/* Cleans the stack. */
void clean(void);

/* --------------- */

/* Prints the current values for stack. */
void prtstack();

/* Stores number input. */
double n = 0.0;
/* Stores operation input (or number sign). */
char op = UNINIT_INPTYPE;
/* Stores the last stack result value. */
double lstack = 0.0;
/* Stores the variables. */
double variables[MAXVAR];

int main()
{
  /* Stack operating vars.*/
  double n1, n2;
  /* User data entrance. */
  int input, ex, next;

  printf(BLUE "Reverse Polish notation based calculator (v1.0).\n" RESET);
  printf(
      "Enter a line break to move to the next argument.\n\
Type \\n to calculate and step over the next calc\n\
stack or \\q to calculate and finish.\n");

  ex = 0;
  while (!ex)
  {
    next = 0; // Reset next.
    clean();  // Clean stack.
    while (!ex && !next)
    {
      input = getinput();

      if (input == NUMBER)
        push(n);
      else if (input == OPERATOR)
      {
        n2 = pop(), n1 = pop();

        switch (op)
        {
        case ADD:
          push(n1 + n2);
          break;
        case SUB:
          push(n1 - n2);
          break;
        case MUL:
          push(n1 * n2);
          break;
        case DIV:
          push(n1 / n2);
          break;
        case MOD:
          push((int)n1 % (int)n2);
          break;
        default:
          break;
        }
      }
      else if (input == VARIABLE)
        ;
      else if (input == COMMAND)
      {
        switch (getchar())
        {
        case QUIT:
          ex = 1;
          break;
        case NEXT:
          next = 1;
          break;
        case STACK:
          prtstack();
          break;
        case LASTSTACK:
          printf("%f\n", lstack);
          break;
        default:
          fprintf(stderr, RED "command error: Unkown command.\n" RESET);
          exit(1);
        }
      }
      else if (input == EXIT)
        ex = 1;
      else
      {
        fprintf(stderr, RED "main error: Unknown input type.\n" RESET);
        exit(1);
      }
    }
    if (next > 0)
      lstack = head();
    prtstack();
  }

  return 0;
}

/* External variables for push & pop. */
/* Next stack next. */
int next = 0;
/* Stack values. */
double stack[MAXSTACK];
/* --------------------------------- */

/* Allows to convert a literal string to a real double number. */
double atof(const char s[])
{
  long int ipart;
  double fpart, divisor;
  int i, sign;

  for (i = 0; isspace(s[i]); i++)
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;
  for (ipart = 0L; isdigit(s[i]); i++)
    ipart = ipart * 10 + (s[i] - '0');
  if (s[i] == '.')
    i++;
  for (fpart = 0.0, divisor = 1.0; isdigit(s[i]); i++, divisor *= 10)
    fpart = fpart * 10 + (s[i] - '0');
  fpart /= divisor;

  return (ipart + fpart) * sign;
}

/* Allows to simplify operator character checking. */
int isoperator(char op)
{
  return (op == ADD || op == SUB || op == MUL || op == DIV || op == MOD);
}

/* Allows to copy literal strings. */
void copystr(const char from[], char to[])
{
  int i, c;
  for (i = 0; (to[i] = from[i]) != '\0'; i++)
    ;
}

/* --- --- --- --- */

void push(double value)
{
  if (next >= MAXSTACK)
  {
    fprintf(stderr, RED "push error: Max stack length exceded.\ns" RESET);
    exit(1); // Program exit for error cause
  }
  stack[next++] = value;
}

double pop(void)
{
  if (next < 1)
  {
    fprintf(stderr, RED "pop error: Min stack length reached.\n" RESET);
    exit(1); // Program exit for error cause
  };
  return stack[--next];
}

double head(void)
{
  if (next < 1)
  {
    fprintf(stderr, RED "head error: Empty stack.\n" RESET);
    return 0.0;
  }
  else
    return stack[next - 1];
}

void duplast(void)
{
  push(head()); // Just pushes the last element in the stack.
}

void swap(void)
{
  double n1, n2;
  n2 = pop(), n1 = pop();
  push(n2), push(n1);
}

void clean(void)
{
  next = 0;
}

void prtstack()
{
  int i;

  if (next <= 0)
  {
    printf("Empty stack.\n");
    return;
  }

  for (i = 0; i < next; i++)
  {
    if (i < next - 1)
      printf("%f ,\n", stack[i]);
    else
      printf(BLUE "%f\n" RESET, stack[i]);
  }
}

int getinput()
{
  /* Variables. */
  char varnlit[MAXD];
  char varvlit[MAXD];
  int varn, varv, varvsign;
  /* --------- */

  /* Digit characters. */
  char digit[MAXD];

  int sign, c, i;

  /* The number is positive by default (if corresponding). */
  sign = 1;
  i = 0;

  /* Ignore initial spaces or tabs. */
  while (isspace((c = getchar())))
    ;

  if (c == '\\')
    return COMMAND;

  if (c == '$')
  {
    for (; i < MAXD - 1 && isdigit((c = getchar())); i++)
      varnlit[i] = c;
    if (i == 0 || i >= MAXD - 1)
    {
      fprintf(stderr, RED "getinput error: Invalid variable name.\n" RESET);
      exit(1); // Program exit.
    }
    varnlit[i] = '\0';

    varn = atof(varnlit);
    if (varn >= MAXVAR)
    {
      fprintf(stderr, RED "getinput error: Invalid variable name.\n" RESET);
      exit(1); // Program exit.
    }

    if (c == ' ')
    {
      for (i = 0; isdigit((c = getchar())); i++)
        varvlit[i] = c;
      if (c == '.')
      {
        varvlit[i++] = c;
        for (; isdigit((c = getchar())); i++)
          varvlit[i] = c;
      }
      varvlit[i] = '\0';
      variables[varn] = atof(varvlit);
      return VARIABLE;
    }
    n = variables[varn];
    return NUMBER;
  }

  /* Checking if the first non-space character is an operator. */
  if (isoperator(c))
  {
    int tempop = c;
    if ((tempop == '+' || tempop == '-') && isdigit((c = getchar())))
      sign = (tempop == '+') ? 1 : -1;
    else
    {
      op = tempop;     // Sets the operator
      return OPERATOR; // Returns the signal
    }
  }

  /* If it is a number, then enter digits inside `digit` array. */
  if (isdigit(c))
  {
    /* Entering the integer part. */
    do
    {
      digit[i++] = c;
    } while ((i < MAXD - 1) && isdigit((c = getchar())));

    /* The input prompt stoped coused for integer part ending. */
    if ((i < MAXD - 1) && c == '.')
    {
      digit[i++] = c;

      /* Entering the floating part. */
      while ((i < MAXD - 1) && isdigit((c = getchar())))
        digit[i++] = c;
    }
  }
  digit[i] = '\0';

  if (c == EOF)
    return EXIT;
  else if (!isdigit(c) && c != '\n')
  {
    fprintf(stderr, RED "getinput error: Invalid character input.\n" RESET);
    exit(1);
  }

  n = atof(digit) * sign;
  return NUMBER;
}