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
  CMD_QUIT = 'q',      // Ends all calc stacks.
  CMD_NEXT = 'n',      // Steps over the next calc stack.
  CMD_STACK = 's',     // Prints the stack.
  CMD_LASTSTACK = 'l', // Prins the last stack.
  CMD_CLRSCR = 'c'     // Clears the screen
};

enum constants
{
  CONST_LASTSTACK = 'l'
};

/* Allows to get the user input for calculator. Different input types defined in `inptypes` enum. */
int getinput(void);

/* Clears and prints the initial text. */
void resetscr(void);

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
char op = INPT_UNINIT;
/* Stores the last stack result value. */
double lstack = 0.0;
/* Stores the variables. */
double variables[MAXVAR];

/*
  ### Mejoras a realizar:

  TODO:

  1. Sistema de llamada a funciones (ejemplo funciones trigonometricas) (ejemplo: f:<func name> arg1 arg2 ...)

  1.1 Funcion para imprimir valores o variables (quita por lo tanto comando para imprimir ultimo resultado de pila, por ejecutar funcion de imprimir variables con la constante que almacena el resultado de la ultima pila de calculo)

  2. Settear variables con el valor de otra variable.

  3. Implementar funcion de C para obtener mas facilmente el valor de las variables (en general implementar alguna funcion para simplificar la logica).
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
        switch (getchar())
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
        case CMD_LASTSTACK:
          printf("%f\n", lstack);
          break;
        case CMD_CLRSCR:
          resetscr();
          break;
        default:
          fprintf(stderr, RED "command error: Unkown command.\n" RESET);
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
  return (op == OP_ADD || op == OP_SUB || op == OP_MUL || op == OP_DIV || op == OP_MOD);
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
      printf("%f,\n", stack[i]);
    else
      printf(BLUE "%f\n" RESET, stack[i]);
  }
}

int getinput()
{
  /* Variables. */
  char varlit[MAXD];
  int varn, varvsign;
  double varv;
  /* --------- */

  /* Digit characters. */
  char digit[MAXD];

  int sign, c, i;

  /* The number is positive by default (if corresponding). */
  sign = varvsign = 1;
  i = 0;

  /* Ignore initial spaces or tabs. */
  while (isspace((c = getchar())))
    ;

  if (c == '\\')
    return INPT_COMMAND;

  if (c == '$')
  {
    for (; i < MAXD - 1 && (isdigit((c = getchar()))); i++)
      varlit[i] = c;
    varlit[i] = '\0';
    /* Constants.  */
    if (i == 0 && c == 'l')
    {
      n = lstack;
      return INPT_NUMBER;
    }
    /* Checking variable name length. */
    if (i == 0 || i >= MAXD - 1)
    {
      fprintf(stderr, RED "getinput error: Invalid variable name.\n" RESET);
      exit(1); // Program exit.
    }

    /* Handling variable name. */
    varn = atof(varlit);
    if (varn >= MAXVAR)
    {
      fprintf(stderr, RED "getinput error: Invalid variable name.\n" RESET);
      exit(1); // Program exit.
    }

    /* In case the user is setting the variable. */
    if (c == ' ')
    {
      for (i = 0; i < MAXD - 1 && isdigit((c = getchar())); i++)
        varlit[i] = c;

      /* In case the new value is other variable. */
      if (i == 0 && c == '$')
      {
        int rvarn;

        /* Checking variable name length. */
        for (; i < MAXD - 1 && isdigit((c = getchar())); i++)
          varlit[i] = c;
        varlit[i] = '\0';

        if (i == 0 || i >= MAXD)
        {
          fprintf(stderr, RED "getinput error: Invalid variable name.\n" RESET);
          exit(1); // Program exit.
        }

        rvarn = atof(varlit);
        if (rvarn >= MAXVAR)
        {
          fprintf(stderr, RED "getinput error: Invalid variable name.\n" RESET);
          exit(1); // Program exit.
        }
        varv = variables[rvarn];
        printf(YELLOW "%f\n" RESET, varv);

        variables[varn] = varv;
        return INPT_VARIABLE;
      }
      /* Or just a new value. */

      // TODO: Terminar de implementar sistema de signos para valores nuevos de variables.

      if (i == 0 && (c == '+' || c == '-'))
        varvsign = (c == '+') ? 1 : -1;

      /* Checking variable value length. */
      if (i == 0 || i >= MAXD)
      {
        fprintf(stderr, RED "getinput error: Invalid variable value.\n" RESET);
        exit(1); // Program exit.
      }
      /* In case the new value has decimals. */
      else if (c == '.')
      {
        varlit[i++] = c;
        for (; isdigit((c = getchar())); i++)
          varlit[i] = c;
      }
      varlit[i] = '\0';
      variables[varn] = atof(varlit);
      return INPT_VARIABLE;
    }
    /* Or just returning the value of the variable. */
    n = variables[varn];
    return INPT_NUMBER;
  }

  /* Checking if the first non-space character is an operator. */
  if (isoperator(c))
  {
    int tempop = c;
    if ((tempop == '+' || tempop == '-') && isdigit((c = getchar())))
      sign = (tempop == '+') ? 1 : -1;
    else
    {
      op = tempop;          // Sets the operator
      return INPT_OPERATOR; // Returns the signal
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
    return INPT_EXIT;
  else if (!isdigit(c) && c != '\n')
  {
    fprintf(stderr, RED "getinput error: Invalid character input.\n" RESET);
    exit(1);
  }

  n = atof(digit) * sign;
  return INPT_NUMBER;
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