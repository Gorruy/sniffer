/*
* Sniffer is prrogramm that can collect data about incoming udp packages
* Copyright (C) 2024  Vladimir Mimikin <vladimirmimikin@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SNFR
#define SNFR

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>


// This struct will be used to pass requriments from programm arguments and values to increment
typedef struct sniff_args {
    unsigned interface;
    uint8_t *req_ip_dest;
    uint8_t *req_ip_source;
    uint16_t req_port_dest;
    uint16_t req_port_source;
    volatile size_t *pkt_len_ptr;
    volatile size_t *pkt_num_ptr;
    pthread_mutex_t *pkt_mtx;
} sniff_args_t;

void* sniff(void*);

extern volatile int break_signal;

#endif 