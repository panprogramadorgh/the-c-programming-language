#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/* Determines the maximum length for the stack values. */
#define MAXSTACK (1U << 6)

/* Determines the maximum length in characters of the number to input. If the maximum is reached, the excess is divested. */
#define MAXD (1U << 5)

/* Debugging symbolic constants. */

/* ANSI scape codes for colors. */
#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

/* ------------------------------ */

/* Defines the input signals for `getinput`. */
enum inptypes
{
  UNINIT_INPTYPE, // Input type signal for uninitialized value.
  NUMBER,
  OPERATOR,
  EXIT // Input type signal for program exit.
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

/* Allows to get the user input for calculator. Different input types defined in `inptypes` enum. */
int getinput();

/* Pushes a new value to the stack. */
void push(double value);

/* Removes and returns the last value in the stack. */
double pop(void);

/* Prints the current values for stack. */
void prtstack();

/* Stores number input. */
double n = 0.0;
/* Stores operation input (or number sign). */
char op = UNINIT_INPTYPE;

/* #### Inverse Polish notation calculator with upgrades:
  - Module operator (%).
  - Signed numbers input support.
*/
int main()
{
  /* Stack operating vars.*/
  double n1, n2;
  /* User data entrance. */
  int input;

  while ((input = getinput()) != EXIT)
  {
    if (input == NUMBER)
      push(n);
    else // input is an operator
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
  }

  prtstack();

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

void prtstack()
{
  int i;
  for (i = 0; i < next; i++)
  {
    printf("%f", stack[i]);
    if (i < next - 1)
      printf(", \n");
    else
      putchar('\n');
  }
}

int getinput()
{
  /* Digit characters. */
  char digit[MAXD];
  int sign, c, i;

  /* The number is positive by default (if corresponding). */
  sign = 1;

  /* Ignore initial spaces or tabs. */
  while (isspace((c = getchar())))
    ;

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

  i = 0;
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

  n = atof(digit) * sign;

  return NUMBER;
}