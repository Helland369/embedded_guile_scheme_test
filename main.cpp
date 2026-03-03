#include <cstddef>
#include <cstdlib>
#include <libguile.h>

static SCM my_addition(SCM a, SCM b)
{
  int x = scm_to_int(a);
  int y = scm_to_int(b);
  return scm_from_int(x + y);
}

static SCM my_division(SCM a, SCM b)
{
  double x = scm_to_double(a);
  double y = scm_to_double(b);
  return scm_from_double(x / y);
}    

static SCM my_user(void)
{
  char *str = getenv("USER");
  if (str == NULL)
    return SCM_BOOL_F;
  else
    return scm_from_locale_string(str);
  
}

static void inneer_main(void *data, int argc, char *argv[])
{
  scm_c_define_gsubr("my-user", 0, 0, 0, reinterpret_cast<scm_t_subr>(my_user));
  scm_c_define_gsubr("my-addition", 2, 0, 0, reinterpret_cast<scm_t_subr>(my_addition));
  scm_c_define_gsubr("my-division", 2, 0, 0, reinterpret_cast<scm_t_subr>(my_division));
  scm_shell(argc, argv);
}    

int main(int argc, char *argv[])
{
  scm_boot_guile(argc, argv, inneer_main, 0);
  return 0;  
}
