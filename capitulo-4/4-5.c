#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

/* Determines the maximum length for literal strings (ex: `funcname` literal string which stores the function name introduced by the user). */
#define MAXS (1U << 10)

/* Determines the maximum length for the stack values. */
#define MAXSTACK (1U << 6)

/* Determines the maximum length in characters of the number to input. If the maximum is reached, the excess is divested. */
#define MAXD (1U << 5)

/* Max length for the variables array. */
#define MAXVAR (1U << 10)

/* Determines the maximum length for function arguments. */
#define MAXARGS (1U << 6)

/* ANSI scape codes for colors. */
#define RED "\x1b[31m"
#define BLUE "\x1b[34m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"
/* ------------------------------ */

/* Defines the input signals for `getinput`. */
enum inptypes
{
  INPT_UNINIT, // Input type signal for uninitialized value.
  INPT_NUMBER,
  INPT_OPERATOR,
  INPT_VARIABLE,
  INPT_COMMAND,  // Input type signal for commands (ex: \q equivalent to EXIT signal)
  INPT_FUNCTION, // Input type signal for functions (ex: f:sin arg).
  INPT_EXIT      // Input type signal for program exit.
};

/* Defines the available operators to be choosen in `getinput`. */
enum operators
{
  OP_UNINIT, // Operator signal for uninitialized value.
  OP_ADD = '+',
  OP_SUB = '-',
  OP_MUL = '*',
  OP_DIV = '/',
  OP_MOD = '%'
};

enum commands
{
  CMD_QUIT = 'q',  // Ends all calc stacks.
  CMD_NEXT = 'n',  // Steps over the next calc stack.
  CMD_STACK = 's', // Prints the stack.
  CMD_CLRSCR = 'c' // Clears the screen
};

enum constants
{
  CONST_LASTSTACK = 'l'
};

/* Utilities. */

/* Allows to get a character from the stdin. */
int getch(void);

/* Allows to unget characters. */
void ungetch(int c);

/* Allows to get the user input for calculator. Different input types defined in `inptypes` enum. */
int getinput(void);

/* Clears and prints the initial text. */
void resetscr(void);

/* Allows to compare two different literal strings. */
int comparestr(const char a[], const char b[]);

/* --------------- */

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

/* Prints the current values for stack. */
void prtstack();
/* --------------- */

/* Stores number input. */
double n = 0.0;

/* Stores operation input (or number sign). */
char op = INPT_UNINIT;

/* Stores the last stack result value. */
double lstack = 0.0;

/* Stores the variables. */
double variables[MAXVAR];

/* Stores the function names. */
char funcname[MAXS];
/* Stores the funcion arguments. */
char funcargs[MAXARGS][MAXS];
int funcargscount;

/*
  ### Mejoras a realizar:
*/
int main()
{
  /* Stack operating vars.*/
  double n1, n2;
  /* User data entrance. */
  int input, ex, next;

  resetscr();

  ex = 0;
  while (!ex)
  {
    next = 0; // Reset next.
    clean();  // Clean stack.
    while (!ex && !next)
    {
      input = getinput();

      if (input == INPT_NUMBER)
        push(n);
      else if (input == INPT_OPERATOR)
      {
        n2 = pop(), n1 = pop();

        switch (op)
        {
        case OP_ADD:
          push(n1 + n2);
          break;
        case OP_SUB:
          push(n1 - n2);
          break;
        case OP_MUL:
          push(n1 * n2);
          break;
        case OP_DIV:
          push(n1 / n2);
          break;
        case OP_MOD:
          push((int)n1 % (int)n2);
          break;
        default:
          break;
        }
      }
      else if (input == INPT_VARIABLE)
        ;
      else if (input == INPT_COMMAND)
      {
        switch (getch())
        {
        case CMD_QUIT:
          ex = 1;
          break;
        case CMD_NEXT:
          next = 1;
          break;
        case CMD_STACK:
          prtstack();
          break;
        case CMD_CLRSCR:
          resetscr();
          break;
        default:
          fprintf(stderr, RED "main error: command error: Unkown command.\n" RESET);
          exit(1);
        }
      }
      else if (input == INPT_FUNCTION)
      {
        int i; // Iterates over function arguments.

        if (comparestr(funcname, "prt")) // Funcion para imprimir variables
        {
          double arg;

          if (funcargscount < 1)
          {
            fprintf(stderr, RED "main error: prt error: At least one argument is required.\n" RESET);
            exit(1);
          }

          if (funcargs[0][0] == '$')
          {
            char varnlit[MAXD];
            for (i = 1; ((i - 1) < (MAXD - 1)) && isdigit(funcargs[0][i]); i++)
              varnlit[i - 1] = funcargs[0][i];
            varnlit[i - 1] = '\0';

            arg = atof(varnlit);
          }
          else
          {
            arg = atof(funcargs[0]);
          }
          printf("%f\n", arg);
        }
        else if (comparestr(funcname, "head"))
        {
          if (funcargscount > 0)
          {
            fprintf(stderr, RED "main error: head error: No arguments are required.\n" RESET);
            exit(1);
          }
          printf("%f\n", head());
        }
        else if (comparestr(funcname, "duplast"))
        {
          if (funcargscount > 0)
          {
            fprintf(stderr, RED "main error: duplast error: No arguments are required.\n" RESET);
            exit(1);
          }
          duplast();
        }
        else if (comparestr(funcname, "swap"))
        {
          if (funcargscount > 0)
          {
            fprintf(stderr, RED "main error: swap error: No arguments are required.\n" RESET);
            exit(1);
          }
          swap();
        }
        else if (comparestr(funcname, "clean"))
        {
          if (funcargscount > 0)
          {
            fprintf(stderr, RED "main error: clean error: No arguments are required.\n" RESET);
            exit(1);
          }
          clean();
        }
        else if (comparestr(funcname, "sin"))
        {
          if (funcargscount != 1)
          {
            fprintf(stderr, RED "main error: sin error: Just one argument is required.\n" RESET);
            exit(1);
          }
          printf("%f\n", sin(atof(funcargs[0])));
        }
        else if (comparestr(funcname, "cos"))
        {
          if (funcargscount != 1)
          {
            fprintf(stderr, RED "main error: cos error: Just one argument is required.\n" RESET);
            exit(1);
          }
          printf("%f\n", cos(atof(funcargs[0])));
        }
        else if (comparestr(funcname, "tan"))
        {
          if (funcargscount != 1)
          {
            fprintf(stderr, RED "main error: tan error: Just one argument is required.\n" RESET);
            exit(1);
          }
          printf("%f\n", tan(atof(funcargs[0])));
        }
        else
        {
          fprintf(stderr, RED "main error: Unknown funcion name.\n" RESET);
          exit(1);
        }
      }
      else if (input == INPT_EXIT)
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

/* Generic utilities. */

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
  return (op == OP_ADD || op == OP_SUB || op == OP_MUL || op == OP_DIV || op == OP_MOD);
}

/* Allows to compare two different literal strings. */
int comparestr(const char a[], const char b[])
{
  int alen, blen;
  int i;

  for (alen = 0; a[alen] != '\0'; alen++)
    ;
  for (blen = 0; (blen <= alen + 1) && (b[blen] != '\0'); blen++)
    ;
  if (blen != alen)
    return 0;

  for (i = 0; i < alen && a[i] == b[i]; i++)
    ;
  return i >= alen;
}

/* Modularization utilities. */

/* Determines whether the value returned by the `getvarn` function is a variable or a constant. */
int isconstant = 0;

/* In charge of getting and settings the function name. The function returns the next character to the name. */
char getfuncname()
{
  int i, c;

  for (i = 0; (i < MAXS - 1) && !isspace((c = getch())); i++)
    funcname[i] = c;
  funcname[i] = '\0';

  return c;
}

/* In charge of getting and setting the function parameters. */
void getfuncargs()
{
  int i, j, c;

  while ((c = getch()) == ' ')
    ;

  j = 0;
  do
  {
    for (i = 0; (i < MAXS - 1) && !isspace(c); i++, (c = getch()))
    {
      funcargs[j][i] = c;
    }
    funcargs[j][i] = '\0';
    j++;
  } while (j < MAXARGS && c == ' ');
  funcargscount = j;
}

/* Allows to get variable names from stdin. */
int getvarn()
{
  char varnamelit[MAXD];
  int varname, c, i;

  for (i = 0; (i < MAXD - 1) && isdigit((c = getch())); i++)
    varnamelit[i] = c;
  varnamelit[i] = '\0';

  /* Handling constants. */
  if (i == 0 && c == 'l')
  {
    isconstant = 1;
    return c;
  }

  if (i == MAXD - 1 || i == 0)
  {
    fprintf(stderr, RED "getinput error: Invalid variable name.\n" RESET);
    exit(1); // Program exit.
  }

  isconstant = 0;
  ungetch(c); // Reserves the exit character for next fn call.
  varname = atof(varnamelit);
  return varname;
}

/* In charge of reading digits. TODO: Comprobar que funcione. TODO: Crear funcion para numeros enteros. */
double getdigit()
{
  char digitlit[MAXD];
  int c, i;
  double result;

  i = 0;

  while ((c = getch()) == ' ')
    ;
  if (c == '+' || c == '-')
  {
    digitlit[i++] = c;
    c = getch();
  }
  for (; (i < MAXD - 1) && isdigit(c); i++, (c = getch()))
    digitlit[i] = c;
  if (c == '.')
  {
    digitlit[i++] = '.';
    for (; (i < MAXD - 1) && isdigit((c = getch())); i++)
      digitlit[i] = c;
  }
  digitlit[i] = '\0';

  result = atof(digitlit);
  return result;
}

/* External variables for push & pop. */

/* Next stack next. */
int next = 0;
/* Stack values. */
double stack[MAXSTACK];

/* Utilities for stack. */

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
      printf("%f,\n", stack[i]);
    else
      printf(BLUE "%f\n" RESET, stack[i]);
  }
}

/* Input utilities */

int lastchar = '\0';

int getch()
{
  int c;

  if (lastchar == '\0')
    return getchar();
  c = lastchar;
  lastchar = '\0';

  return c;
}

void ungetch(int c)
{
  lastchar = c;
}

int getinput()
{
  /* Variables. */
  int varn1, varn2;
  double varv; // It can be a floating point digit, or failing that, the value of other variable.

  int c;

  /* Loop variables. */
  int i, j;

  i = 0;

  /* Ignore initial spaces or tabs. */
  while (isspace((c = getch())))
    ;

  if (isdigit(c) || c == '+' || c == '-')
  {
    char temp = c;
    ungetch(c);
    n = getdigit();
    if (n > 0)
      return INPT_NUMBER;
    c = temp;
  }

  /* Handling command. */
  if (c == '\\')
    return INPT_COMMAND;

  /* Handling function calls. */
  if (c == 'f')
  {
    /* Checking separator */
    if ((c = getch()) != ':')
    {
      fprintf(stderr, RED "getinput error: Invalid function name separator.\n" RESET);
      exit(1); // Program exit.
    }
    /* Setting function name. */
    c = getfuncname();

    /* Obtaining funcion arguments. */
    if (c == ' ')
      getfuncargs();

    return INPT_FUNCTION;
  }

  /* Handling variables. */
  if (c == '$')
  {
    varn1 = getvarn();

    /* Handling constants.

      FIXME: Arreglar sistema de constantes

     */
    if (varn1 == 'l')
    {
      n = lstack;
      return INPT_NUMBER;
    }

    /* In case the user is setting the variable. */
    if ((c = getch()) == ' ')
    {
      /* Means the var value is other variable. */
      if ((c = getch()) == '$')
      {
        varn2 = getvarn();
        variables[varn1] = variables[varn2];
      }
      else
      {
        ungetch(c);
        varv = getdigit();
        variables[varn1] = varv;
      }
      return INPT_VARIABLE;
    }
    /* Or just returning the value of the variable. */
    n = variables[varn1];
    return INPT_NUMBER;
  }

  /* Checking if the first non-space character is an operator. */
  if (isoperator(c))
  {
    op = c;
    return INPT_OPERATOR; // Returns the signal
  }

  if (c == EOF)
    return INPT_EXIT;
  else if (c != '\n')
  {
    fprintf(stderr, RED "getinput error: Invalid character input: %c\n" RESET, c);
    exit(1);
  }
}

void resetscr(void)
{
  printf("\e[1;1H\e[2J"); // Clears the screen.
  printf(BLUE "RPC - Reverse Polish notation based calculator (v1.0).\n" RESET);
  printf(
      "Enter a line break to move to the next argument.\n\
Type \\n to calculate and step over the next calc\n\
stack or \\q to calculate and finish.\n");
}