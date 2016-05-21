#include "ace/OS.h"

#include "ace/Get_Opt.h"
int
main (int argc, char *argv[]) 
{
   
//Specify option string so that switches b, d, f and h all expect
//arguments. Switches a, c, e and g expect no arguments.
      ACE_Get_Opt get_opt (argc, argv, "ab:cd:ef:gh:");
  int c;
  
//Process the scanned options with the help of the overloaded ()
//operator.
      while ((c = get_opt ()) != EOF)
    switch (c)
      
    {
        case 'a':
          ACE_DEBUG ((LM_DEBUG, "got a\n"));
          break;
        case 'b':
          ACE_DEBUG ((LM_DEBUG, "got b with arg %s\n", get_opt.optarg));
          break;
        case 'c':
          ACE_DEBUG ((LM_DEBUG, "got c\n"));
          break;
        case 'd':
          ACE_DEBUG ((LM_DEBUG, "got d with arg %s\n", get_opt.optarg));
          break;
        case 'e':
          ACE_DEBUG ((LM_DEBUG, "got e\n"));
          break;
        case 'f':
          ACE_DEBUG ((LM_DEBUG, "got f with arg %s\n", get_opt.optarg));
          break;
        case 'g':
          ACE_DEBUG ((LM_DEBUG, "got g\n"));
          break;
        case 'h':
          ACE_DEBUG ((LM_DEBUG, "got h with arg %s\n", get_opt.optarg));
           break;
        default:
          ACE_DEBUG ((LM_DEBUG, "got %c, which is unrecognized!\n", c));
          break;
    }
  
//optind indicates how much of argv has been scanned so far, while
//get_opt hasn't returned EOF. In this case it indicates the index in
//argv from where the option switches have been fully recognized and the
//remaining elements must be scanned by the called himself.
      for (int i = get_opt.optind; i < argc; i++)
    ACE_DEBUG ((LM_DEBUG, "optind = %d, argv[optind] = %s\n", i, argv[i]));
  return 0;
}

 
