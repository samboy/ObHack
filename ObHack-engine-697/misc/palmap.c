
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SKIP  0x88

static int slime_to_nukage_pairs[] =
{
  0x01,127, 0x4f,126, 0x4e,125, 0xee,124, 0x0f,123,
  0x4d,123, 0xed,122, 0x97,122, 0x4c,121, 0x4b,121,
  0x4a,120,

  -1,-1  // end marker
};

static int slime_to_blood_pairs[] =
{
  0x01,190, 0x4f,189, 0x4e,188, 0xee, 40, 0x0f,187,
  0x4d, 38, 0xed,186, 0x97, 36, 0x4c,185, 0x4b, 33,
  0x4a,184,

  -1,-1  // end marker
};

static int FindPair(int *pairs, int index)
{
  int j;
  for (j=0; pairs[j] >= 0; j += 2)
  {
    if (pairs[j] == index)
      return pairs[j+1];
  }

  return index;
}

int main(void)
{
  int k;
  for (k=0; k < SKIP; k++)
    putchar(getchar());

  for (;;)
  {
    int ch = getchar();
    if (ch == EOF)
      break;
    
    putchar(FindPair(slime_to_blood_pairs, ch));
  }
  
  return 0;
}
