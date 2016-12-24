/*
 * user_main.h
 *
 *  Created on: 2016年5月10日
 *      Author: Administrator
 */

#ifndef APP_INCLUDE_USER_MAIN_H_
#define APP_INCLUDE_USER_MAIN_H_

#include "osapi.h"
#include "user_interface.h"
#include "clien.h"
#include "gpio.h"
#include "smartconfig.h"
#include "driver/uart.h"
#include "ets_sys.h"
#include "c_types.h"
#include "eagle_soc.h"
#include "sntp.h"
#include "mem.h"
ETSTimer connect_timer;
//ETSTimer station_check;
//ETSTimer smartconfig_timer;
ETSTimer heartbeat_timer;

static uint8 count = 0;
static uint32 count_down = 0;
uint8 status;
struct station_config *sta_conf;
bool wifi_discon_flag;
//uint8 *my_mac_addr;
uint8 my_sta_mac[6];
char macaddr1[24];
struct espconn *pespconn;
uint32 current_stamp;
uint32_t time;
bool switch_on;//插座开关状态标志位，默认关闭，为0.开启为1

//static uint8 *TMdata;
//static uint8 TMdata[24][24] = {0};//用数组来接收从服务器发过来的数据有着妙不可言的好处，叼叼叼，师胸就是牛逼
//static uint8 **TMdata;
static uint8 TM_ID = 0;
static uint8 restart_flag = 0;
//static uint8 hardware_flag = 0;
//uint8 count_down = 0;
uint8 DMdata[24];

//定时功能结构体
struct TIMER{
	uint8 TMdata[24];
	uint8 TM_ID;
};

struct TIMER timer[8];


#endif /* APP_INCLUDE_USER_MAIN_H_ */
