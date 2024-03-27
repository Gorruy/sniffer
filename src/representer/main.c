#include <fcntl.h>
#include <mqueue.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_EXIT(message) do {\
  fprintf(stderr, message ); \
  perror(strerror(errno)); \
  exit(EXIT_FAILURE); \
} while(0)

#define QUEUE_NAME "/SniffingQueue"


int main(void)
{
  mqd_t queue_to_sniffer = mq_open(QUEUE_NAME, O_RDWR );
  if ( queue_to_sniffer == (mqd_t) -1 )
  {
    perror(strerror(errno));
    exit(EXIT_FAILURE);
  }

  size_t stats[2];

  if ( mq_send( queue_to_sniffer, (char*)stats, 0, 0 ) == -1 ) // Message of zero size to notify sniffer
    ERROR_EXIT("Error in sendind\n");

  if ( mq_receive( queue_to_sniffer, (char*)stats, sizeof(size_t)*2, 0 ) == -1 ){
    ERROR_EXIT("Error in recieveing\n");
  }

  printf( "Number of packets:%ld, size of all packets in bytes:%ld", stats[0], stats[1] );

  mq_unlink(QUEUE_NAME); 
}