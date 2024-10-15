#include <stdio.h>
#include <stdlib.h>
#include "glk.h"
#include "minglk.h"
#include "glkstart.h"

int main(int argc, char *argv[])
{
  if (sizeof(glui32) != 4)
  {
    printf("Compile-time error: glui32 is not a 32-bit value.\n");
    return EXIT_FAILURE;
  }

  if ((glui32)(-1) < 0)
  {
    printf("Compile-time error: glui32 is not unsigned.\n");
    return EXIT_FAILURE;
  }

  if (sizeof(glsi32) != 4)
  {
    printf("Compile-time error: glsi32 is not a 32-bit value.\n");
    return EXIT_FAILURE;
  }

  if ((glsi32)(-1) > 0)
  {
    printf("Compile-time error: glsi32 is not signed.\n");
    return EXIT_FAILURE;
  }

  glk_startup_t startdata;

  printf("MinGlk - Minimal Glk Library (v%s)\n\n", LIBRARY_VERSION);

  glk_main();
  glk_exit();

  if (!glk_startup_code(&startdata))
  {
    glk_exit();
  }

  return EXIT_SUCCESS;
}
