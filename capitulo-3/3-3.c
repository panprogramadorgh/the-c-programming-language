#include <stdio.h>

/* Determines the maximum length for literal strings throughout the programm. */
#define MAX 1024 // 1 KiB

/* Allows to expand brief notation of character sequences like a-b or 0-9 found in `s1` while copies the new literal string into `s2`. */
void expand(const char s1[], char s2[]);

/* Returns the position of `v` inside `str` starting from `offset` or -1 in case of not found. */
int indexOf(const char str[], const char v[], unsigned offset);

/* Compares the literal string `s1` with `s2` and returns 0 in case those are different. */
int compare(const char s1[], const char s2[]);

/* Takes a slice from `s` starting from `p` and fills the character array `r` with size of `size`. */
void slice(const char s[], char r[], unsigned start, unsigned end);

int main()
{
  const char from[] =
      "Brief notation a-z (0-9 & A-Z) of a character sequence.";
  char to[MAX];

  expand(from, to);

  printf("%s\n", to);

  return 0;
}

void expand(const char s1[], char s2[])
{
  int s1lgth, seqlgth;
  /* Sequence positions. */
  int lower_alpha, upper_alpha, digits;
  int i, j, k;

  seqlgth = 3;
  lower_alpha = indexOf(s1, "a-z", 0);
  upper_alpha = indexOf(s1, "A-Z", 0);
  digits = indexOf(s1, "0-9", 0);

  for (s1lgth = 0; s1[s1lgth] != '\0'; s1lgth++)
    ;
  for (
      i = j = 0;
      (j < MAX - 1) &&
      (i < s1lgth);
      i++, j++)
  {
    if (i == lower_alpha)
    {
      for (k = 'a'; (j < MAX - 1) && (k <= 'z'); k++, j++)
        s2[j] = k;
      j--; // Exceso de incremento
      i += 2;
      lower_alpha = indexOf(s1, "a-z", lower_alpha + seqlgth);
    }
    else if (i == upper_alpha)
    {
      for (k = 'A'; (j < MAX - 1) && (k <= 'Z'); k++, j++)
        s2[j] = k;
      j--; // Exceso de incremento
      i += 2;
      upper_alpha = indexOf(s1, "A-Z", upper_alpha + seqlgth);
    }
    if (i == digits)
    {
      for (k = '0'; (j < MAX - 1) && (k <= '9'); k++, j++)
        s2[j] = k;
      j--; // Exceso de incremento
      i += 2;
      digits = indexOf(s1, "a-z", digits + seqlgth);
    }
    else
      s2[j] = s1[i];
  }
  s2[j] = '\0';
}

int indexOf(const char str[], const char v[], unsigned offset)
{
  int strlgth, vlgth;
  int comparation_start_pos, final_comparation_pos;
  int pos;

  pos = -1;

  for (strlgth = 0; str[strlgth] != '\0'; strlgth++)
    ;
  for (vlgth = 0; v[vlgth] != '\0'; vlgth++)
    ;
  final_comparation_pos = strlgth - vlgth;
  if (final_comparation_pos < 0)
    return pos;

  char comparation_slice[MAX]; // +1 for the null character

  for (comparation_start_pos = offset; pos == -1 && comparation_start_pos <= final_comparation_pos; comparation_start_pos++)
  {
    slice(str, comparation_slice, comparation_start_pos, comparation_start_pos + vlgth - 1);
    if (compare(v, comparation_slice))
      pos = comparation_start_pos;
  }

  return pos;
}

int compare(const char s1[], const char s2[])
{
  int i, eq;

  eq = 1;

  for (i = 0; eq == 1 && s1[i] != '\0'; i++)
    eq = s1[i] == s2[i];

  return eq;
}

void slice(const char s[], char r[], unsigned start, unsigned end)
{
  int i;

  for (i = start; (s[i] != '\0') && i <= end; i++)
    r[i - start] = s[i];
  r[i] = '\0';
}