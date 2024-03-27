#include <pthread.h>
#include <getopt.h>

#include "../../include/sniffer/sniffer.h"


int main( int argc, char *argv[] )
{
  pthread_t sniffing_thread;
  pthread_t sending_thread;
  pthread_cond_t info_dspl_signal;

  sniff_args_t args = { 
    .req_ip_dest = NULL,
    .req_ip_source = NULL,
    .req_port_dest = NULL,
    .req_port_source = NULL 
  };

  struct option {
	  const char *name;
	  int has_arg;
	  int *flag;
	  int val;
  };

  const struct option options[5] = {
    { .name = "ipsrc", .has_arg = required_argument, .flag = 0, .val = '1' },
    { .name = "ipdest", .has_arg = required_argument, .flag = 0, .val = '2' },
    { .name = "portsrc", .has_arg = required_argument, .flag = 0, .val = '3' },
    { .name = "portdest", .has_arg = required_argument, .flag = 0, .val = '4' },
    { .name = 0, .has_arg = 0, .flag = 0, .val = 0 }
  };

  int opt;
  while ( ( opt = getopt_long(argc, argv, "1:2:3:4:", options, NULL ) ) != -1 )
  {
    switch (opt)
    {
      case '1':
        if ( check_ip(optarg) != -1 ) {
          strcpy(args.req_ip_source, optarg );
          break;
        }
        else
          ERROR_EXIT("Wrong value of reqired ip source address!\n");
      case '2':
        if ( check_ip(optarg) != -1 ) {
          strcpy(args.req_ip_source, optarg );
          break;
        }
        else
          ERROR_EXIT("Wrong value of reqired ip dest address!\n");
      case '3':
        if ( check_port(optarg) != -1 ) {
          strcpy(args.req_ip_source, optarg );
          break;
        }
        else
          ERROR_EXIT("Wrong value of reqired source port value!\n");
      case '4':
        if ( check_port(optarg) != -1 ) {
          strcpy(args.req_ip_source, optarg );
          break;
        }
        else
          ERROR_EXIT("Wrong value of reqired dest port value!\n");
    }
  }

  if ( pthread_create( &sniffing_thread, NULL, &sniff, &args ) != 0 )
    ERROR_EXIT("Thread creation error!\n");
  if ( pthread_create( &sending_thread, NULL, &send_data_to_representer, NULL ) != 0 )
    ERROR_EXIT("Thread creation error!\n");

  if ( pthread_join( sniffing_thread, NULL ) != 0 )
    ERROR_EXIT("Thread join error\n");
  if ( pthread_join( sending_thread, NULL ) != 0 )
    ERROR_EXIT("Thread join error\n");    

  return 0;
}