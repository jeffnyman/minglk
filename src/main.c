#include <stdio.h>
#include <stdlib.h>
#include "glk.h"
#include "minglk.h"

int main(int argc, char *argv[])
{
  printf("MinGlk - Minimal Glk Library (v%s)\n\n", LIBRARY_VERSION);

  glk_main();
  glk_exit();

  return EXIT_SUCCESS;
}
