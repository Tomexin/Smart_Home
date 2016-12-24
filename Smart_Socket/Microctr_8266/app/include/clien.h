/*
 * clien.h
 *
 *  Created on: 2016Äê5ÔÂ14ÈÕ
 *      Author: Administrator
 */

#ifndef APP_INCLUDE_CLIEN_H_
#define APP_INCLUDE_CLIEN_H_
#include "user_main.h"
#include "espconn.h"
#include "mem.h"
#include "hw_timer.h"
#include "spi_flash.h"
struct espconn user_tcp_conn;
void my_station_init(struct ip_addr *remote_ip, struct ip_addr *local_ip, int remote_port);



#endif /* APP_INCLUDE_CLIEN_H_ */
