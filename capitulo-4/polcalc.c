#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/* Determines the maximum length for the stack values. */
#define MAXSTACK (1U << 6)

/* Defines the input for `getinput`. */
enum inptypes
{
  NUMBER,
  OPERATOR,
  EXIT
};

/* Defines the available operators to be choosen in `getinput`. */
enum operators
{
  ADD = '+',
  SUB = '-',
  MUL = '*',
  DIV = '/'
};

/* Allows to get the user input for calculator. Different input types defined in `inptypes` enum. */
int getinput();

/* Pushes a new value to the stack. */
void push(double value);

/* Removes and returns the last value in the stack. */
double pop(void);

/* Prints the current values for stack. */
void prtstack();

/* Next stack next. */
int next = 0;
/* Stack values. */
double stack[MAXSTACK];
/* Stores number input. */
double n;
/* Stores operation input.*/
char op;

int main()
{
  /* Stack operating vars.*/
  double n1, n2;
  /* User data entrance. */
  int input;

  while (1)
  {
    input = getinput();
    if (input == EXIT)
      break; // If the next pos in stack is the first (operation is deemed as complete) exit the loop.
    else if (input == NUMBER)
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
      }
    }
  }

  // printf("%f\n", stack[0]); // Prints first position of stack.

  prtstack();

  return 0;
}

/* Determines the maximum length in characters of the number to input. If the maximum is reached, the excess is divested. */
#define MAX_DIGIT_LEN (1U << 5)

/* Generic Utilities. */

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
  for (fpart = 0.0, divisor = 1; isdigit(s[i]); i++, divisor *= 10)
    fpart = fpart * 10 + (s[i] - '0');
  fpart /= divisor;

  return (ipart + fpart) * sign;
}

/* Allows to simplify operator character checking. */
int isoperator(char op)
{
  return (op == ADD || op == SUB || op == MUL || op == DIV);
}

/* --- --- --- --- */

void push(double value)
{
  if (next >= MAXSTACK)
  {
    fprintf(stderr, "Max stack length exceded.\ns");
    exit(1); // Program exit for error cause
  }
  stack[next++] = value;
}

double pop(void)
{
  if (next < 1)
  {
    fprintf(stderr, "Min stack length reached.\n");
    exit(1); // Program exit for error cause
  };
  return stack[--next];
}

void prtstack()
{
  int i;
  for (i = 0; i < next; i++)
  {
    printf("%f, ", stack[i]);
    if (i % 10 == 0)
      putchar('\n');
  }
  putchar('\n');
}

int getinput()
{
  /* Digit characters. */
  char digit[MAX_DIGIT_LEN];
  /* Is an operator. */
  int isop;
  /* Has entry a digit or an operator. */
  int ent;

  int c, i;

  i = isop = ent = 0;

  /* Entering the integer part of the number or just an operator. */
  while (
      (!isop) &&
      (i < MAX_DIGIT_LEN - 1) &&
      (isdigit((c = getchar())) || (ent == 0 && (isspace(c) || isoperator(c)))))
  {
    if (!isspace(c) && ent == 0)
      ent = 1;
    if (isoperator(c))
    {
      op = c;
      isop = 1;
    }
    else if (isdigit(c))
    {
      if (ent == 0)
        ent = 1;
      digit[i++] = c;
    }
  }

  if (c == EOF)
    return EXIT;
  else if (isop)
    return OPERATOR;

  /* The input prompt stoped coused for integer part ending. */
  if (c == '.')
  {
    digit[i++] = c;
    for (; (i < MAX_DIGIT_LEN - 1) && (isdigit((c = getchar()))); i++)
      digit[i] = c;
  }

  digit[i] = '\0';
  n = atof(digit);

  return NUMBER;
}