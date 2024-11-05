#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>

// Determina si es un año bisiesto
#define IS_LEAP_YEAR 1 // 1 | 0

#define MAXLN 64

// Meses del año por cada variante de tabulacion de dias
#define MONTHS 12

// Variantes de tabulacion de dias
#define VARIANTS 2

// Retorna el dia del año
int day_of_year(int day, int month);

// Permite obtene el dia del mes de un dia de un año
void day_of_month(int year, int year_day, int *month, int *day_month);

// Retorna != 0 si year es bisiesto
int is_leap_year(int year);

// Permite obtener lineas de texto
int getln(char *line, int max);

// Conversion de cadena de texto en un numero
int strtoi(char *digit);

static unsigned char daytab[VARIANTS][MONTHS] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int main()
{
  char line[MAXLN];
  int year;
  int year_day;
  int month, month_day;

  // Introducir año
  printf("Enter year: ");
  if (getln(line, MAXLN) < 0)
  {
    perror("text line excedes maximum length");
    return EXIT_FAILURE;
  }
  year = strtoi(line);

  // Introducir dia del año
  printf("Enter year day: ");
  if (getln(line, MAXLN) < 0)
  {
    perror("text line excedes maximum length");
    return EXIT_FAILURE;
  }
  year_day = strtoi(line);

  // Conversion a dia y mes.
  day_of_month(year, year_day, &month, &month_day);
  printf("%d/%d/%d\n", month_day, month, year);

  return EXIT_SUCCESS;
}

int day_of_year(int day, int month)
{
  int days_counter = day < 1 ? 1 : day;
  int curmonth = month - 2; // Obtener indice del mes anterior

  if (curmonth < 0)
    return day;

  for (; curmonth >= 0; curmonth--)
    days_counter += daytab[IS_LEAP_YEAR][curmonth];

  return days_counter;
}

void day_of_month(int year, int year_day, int *month, int *day_month)
{
  int lyear = is_leap_year(year); // Es bisiesto
  int curmonth = 0;               // Indice de mes
  int days_count = 0;             // Contador de dias

  for (; days_count < year_day; curmonth++)
    days_count += daytab[lyear][curmonth];

  *month = curmonth;
  *day_month = daytab[lyear][--curmonth] + year_day - days_count;
}

int is_leap_year(int year)
{
  return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

int getln(char *line, int max)
{
  int c;
  char *ch = line;

  while ((c = getchar()) != EOF && c != '\n')
  {
    if (ch - line >= max)
    {
      errno = ENOMEM;
      perror("text line is too much long");
      return -1;
    }
    *ch++ = c;
  }
  *ch = '\0';
  return ch - line;
}

int strtoi(char *digit)
{
  int sign;
  int result = 0;

  while (*digit++ == ' ')
    ;
  sign = *--digit == '-' ? -1 : 1;
  if (*digit == '+' || *digit == '-')
    digit++;
  if (isdigit(*digit))
  {
    do
    {
      result = result * 10 + (*digit - '0');
    } while (isdigit(*++digit));
  }

  return result * sign;
}