#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#if defined(BL_FORT_USE_UNDERSCORE)
#define GET_PRESENT_DIR get_present_dir_
#elif defined(BL_FORT_USE_DBL_UNDERSCORE)
#define GET_PRESENT_DIR get_present_dir__
#elif defined(BL_FORT_USE_LOWERCASE)
#define GET_PRESENT_DIR get_present_dir
#endif


#if defined(BL_FORT_USE_UNDERSCORE)
#define SEND_FAIL_RETURN_CODE send_fail_return_code_
#elif defined(BL_FORT_USE_DBL_UNDERSCORE)
#define SEND_FAIL_RETURN_CODE send_fail_return_code__
#elif defined(BL_FORT_USE_LOWERCASE)
#define SEND_FAIL_RETURN_CODE send_fail_return_code
#endif


#if defined(BL_FORT_USE_UNDERSCORE)
#define SEND_SUCCESS_RETURN_CODE send_success_return_code_
#elif defined(BL_FORT_USE_DBL_UNDERSCORE)
#define SEND_SUCCESS_RETURN_CODE send_success_return_code__
#elif defined(BL_FORT_USE_LOWERCASE)
#define SEND_SUCCESS_RETURN_CODE send_success_return_code
#endif


/* icwd is a Fortran integer array of length size.  This will be
   converted into a Fortran string using the boxlib bl_string_module
   routines */

void GET_PRESENT_DIR (int* icwd, const int *size) {
  int i;
  char *cwd;

  cwd = (char *) malloc( (*size)*sizeof(char));
  
  if (getcwd(cwd, *size) == 0)
    {
      fprintf(stderr, "GET_PRESENT_DIR: getcwd() returned NULL\n");
      exit(1);
    }

  /* fill the remainder of the string with ' ', so the boxlib int2str 
     routines result in a nice string */
  for (i = strlen(cwd); i < *size; i++)
    cwd[i] = ' ';


  /* convert the char string to an integer */
  for (i=0; i < *size; i++) {
    icwd[i] = (int) cwd[i];
  }

  free (cwd);
}


void SEND_FAIL_RETURN_CODE () {
  /* this function would not be needed if all Fortran compilers
     supported 'error stop' */
 
  exit(EXIT_FAILURE);

}

void SEND_SUCCESS_RETURN_CODE () {
  /* this function would not be needed if all Fortran compilers
     supported 'error stop' */
 
  exit(EXIT_SUCCESS);

}
