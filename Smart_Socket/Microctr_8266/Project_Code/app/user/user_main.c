/*
 * user_main.c
 *
 *  Created on: 2016年5月10日
 *      Author: Administrator
 *
 *  作者：徐欣
 *  日期：2016年6月25日
 *  简述：该固件为单孔智能插座固件，支持硬件和软件同时控制，支持服务器异常断开，重连；支持路由器异常断开，
 *  重连，gpio4口为状态指示灯，gpio5口为开关控制口，gpio12口为按键中断口。
 *  单孔智能插座控制固件3代，无心跳包，断开服务器连接后自动重连
 *  date:2016年7月1日
 *  单插孔智能插座固件成熟版第一代
 *
 */

#include "user_main.h"

//smartconfig功能的回调函数
void ICACHE_FLASH_ATTR smartconfig_done(sc_status status, void *pdata)
{
	//os_printf("\r\nplease smartconfig\r\n");
	os_timer_disarm(&connect_timer);//关闭定时器
    switch(status) {
        case SC_STATUS_WAIT:
            os_printf("SC_STATUS_WAIT\n");
            break;
        case SC_STATUS_FIND_CHANNEL:
            os_printf("SC_STATUS_FIND_CHANNEL\n");
            break;
        case SC_STATUS_GETTING_SSID_PSWD:
            os_printf("SC_STATUS_GETTING_SSID_PSWD\n");
			sc_type *type = pdata;
            if (*type == SC_TYPE_ESPTOUCH) {
                os_printf("SC_TYPE:SC_TYPE_ESPTOUCH\n");
            } else {
                os_printf("SC_TYPE:SC_TYPE_AIRKISS\n");
            }
            break;
        case SC_STATUS_LINK:
            os_printf("SC_STATUS_LINK\n");
            sta_conf = pdata;

	        wifi_station_set_config(sta_conf);
	        wifi_station_disconnect();
	        wifi_station_connect();
            break;
        case SC_STATUS_LINK_OVER:
            os_printf("SC_STATUS_LINK_OVER\n");
            if (pdata != NULL) {
                uint8 phone_ip[4] = {0};

                os_memcpy(phone_ip, (uint8*)pdata, 4);
                os_printf("Phone ip: %d.%d.%d.%d\n",phone_ip[0],phone_ip[1],phone_ip[2],phone_ip[3]);
            }
            smartconfig_stop();
            os_timer_arm(&connect_timer,1000,NULL);//重新使能定时器
            break;
    }

}

//定时器回调函数，定时完成之后检测是否连上AP
void ICACHE_FLASH_ATTR Wifi_connect(void *arg){
	os_timer_disarm(&connect_timer);//关闭定时器
	//count++;
	os_delay_us(1000);
	status = wifi_station_get_connect_status();
	if(status == STATION_GOT_IP)
	{
		wifi_discon_flag = 0;
		//client
		os_printf("\r\nWiFi connect success\r\n");
		GPIO_OUTPUT_SET(GPIO_ID_PIN(4), 1);//led灯亮，模块正常工作
		restart_flag = 0;
		//hardware_flag = 0;

		//SNTP服务器
		sntp_setservername(0,"0.cn.pool.ntp.org");
		sntp_setservername(1,"1.cn.pool.ntp.org");
		sntp_setservername(2,"2.cn.pool.ntp.org");
		sntp_init();

		struct ip_info info;
		//const char remote_ip[4] = {211,149,174,125};
		//const char remote_ip[4] = {192,168,0,120};
		const char remote_ip[4] = {192,168,1,105};
		wifi_get_ip_info(STATION_IF, &info);
		//my_station_init((struct ip_addr *)remote_ip, &info.ip, 23455);
		my_station_init((struct ip_addr *)remote_ip, &info.ip, 23455);
		return;
	}
	else
	{
		if(wifi_discon_flag == 0)
		{
			count ++;
			if(count > 8)//自动连接10次，不成功表明没有连上AP。
						//注意：重连次数不能太少，不然会产生误判，无法成功连上ap,特别是smartconfig之后
			{
				GPIO_OUTPUT_SET(GPIO_ID_PIN(4), 0);//led灯灭，模块进入smartconfig状态
				//os_printf("\r\nwifi connect fail,please smartconfig\r\n");

				//smartconfig_stop();
				smartconfig_start(smartconfig_done, 0);//开启WiFi模块的smartconfig功能,串口仅打印连接结果

				return;//一定要加return，不然一定会出错，
						//不加，一定不能正常进入smartconfig模式，感谢8266群主的指导
			}
			os_delay_us(500);
		}
	}
	os_timer_arm(&connect_timer,1000,NULL);//重新使能定时器
}

//定义GPIO12中断触发回调函数；不可以加ICACHE_FLASH_ATTR宏，否则会出错
//中断功能为通过外部按键方式实现控制开关的目的
//按键长按5秒模块重新进入smartconfig模式
LOCAL void key_init_handle(void *arg)
{

	uint16 gpio_status=0;
	gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);//判断IO口状态
	gpio_pin_intr_state_set(GPIO_ID_PIN(12),GPIO_PIN_INTR_DISABLE);//关闭GPIO12中断
	GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status);//清除中断标志

	os_delay_us(5000); //延时消抖
	if(GPIO_INPUT_GET(12) == 0)
	{
		if(GPIO_INPUT_GET(5) == 0)
		{
			GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//打开开关
			switch_on = 1;//插座开光状态标识位置1
			espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
		}
		else
		{
			GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//关掉开关
			switch_on = 0;//插座开关状态标识位清零
			espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
		}
	}

	//设备重置功能
	os_delay_us(200000);
	if(GPIO_INPUT_GET(12) == 0)
	{
		os_delay_us(500000);
		if(GPIO_INPUT_GET(12) == 0)
		{
		os_delay_us(500000);
		if(GPIO_INPUT_GET(12) == 0)
		{
		os_delay_us(500000);
		if(GPIO_INPUT_GET(12) == 0)
		{
		os_delay_us(500000);
		if(GPIO_INPUT_GET(12) == 0)
		{
		os_delay_us(500000);
		if(GPIO_INPUT_GET(12) == 0)
		{
		os_delay_us(500000);
		if(GPIO_INPUT_GET(12) == 0)
		{
		os_delay_us(500000);
		if(GPIO_INPUT_GET(12) == 0)
		{
		os_delay_us(500000);
		if(GPIO_INPUT_GET(12) == 0)
		{
		os_delay_us(500000);
		if(GPIO_INPUT_GET(12) == 0)
		{
		os_delay_us(500000);
		if(GPIO_INPUT_GET(12) == 0)
		{
			os_timer_disarm(&heartbeat_timer);//关闭心跳包定时器
			restart_flag = 1;//重置restart_flag
			wifi_station_disconnect();//断开wifi连接
			smartconfig_start(smartconfig_done, 0);//进入smartconfig模式
		}
		}
		}
		}
		}
		}
		}
		}
		}
		}

	}
	//重新设置中断类型并使能中断
	gpio_pin_intr_state_set(GPIO_ID_PIN(12),GPIO_PIN_INTR_NEGEDGE);
	ETS_GPIO_INTR_ENABLE();
}

//GPIO中断初始化函数
void ICACHE_FLASH_ATTR GPIO_intr_init(void)
{
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U,FUNC_GPIO12);//配置IO12为GPIO12
	ETS_GPIO_INTR_ATTACH(key_init_handle,NULL);//注册GPIO中断触发回调函数
	ETS_GPIO_INTR_DISABLE();//禁止所有GPIO中断
	GPIO_DIS_OUTPUT(GPIO_ID_PIN(12));//将GPIO12设置为输入模式
	//设置GPIO12的寄存器
	gpio_register_set(GPIO_PIN_ADDR(12), \
			GPIO_PIN_INT_TYPE_SET(GPIO_PIN_INTR_DISABLE) \
			| GPIO_PIN_PAD_DRIVER_GET(GPIO_PAD_DRIVER_DISABLE)\
			| GPIO_PIN_SOURCE_SET(GPIO_AS_PIN_SOURCE));
	//设置中断触发方式为下降沿触发
	gpio_pin_intr_state_set(GPIO_ID_PIN(12),GPIO_PIN_INTR_NEGEDGE);
	//使能中断
	ETS_GPIO_INTR_ENABLE();
}

//系统初始化完成之后的回调函数，回调函数中执行扫描环境AP的任务
void system_done(void)
{
	//获取WiFi模块的mac地址
	wifi_get_macaddr(STATION_IF, my_sta_mac);
	//os_printf(MACSTR);
	os_sprintf(macaddr1, ""MACSTR"\r\n", MAC2STR(my_sta_mac));
	//os_printf(macaddr1);

	os_timer_disarm(&connect_timer);//关闭定时器
	os_timer_setfn(&connect_timer,Wifi_connect,NULL);//设置定时器回调函数Wifi_connect
	os_timer_arm(&connect_timer,1000,NULL);//软件定时延时1s，不自动重装
}

//程序入口函数
void user_init(){
	int i=0, j=0;
	uart_init(115200,115200);
	wifi_discon_flag = 0;
	switch_on = 0;//插座上电默认关闭

	//gpio4口控制状态指示灯，gpio5口为开关控制口
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U,FUNC_GPIO4);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U,FUNC_GPIO5);
	GPIO_OUTPUT_SET(GPIO_ID_PIN(4), 1);//led灯亮，模块进入工作状态
	GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//插座开关上电默认关闭

	GPIO_intr_init();//调用GPIO中断初始化函数
	//设置WiFi工作模式为station模式
	wifi_set_opmode(0x01);

	//将结构体的数组的元素清零
	for(i=0; i<8; i++)
	{
		for(j=0; j<24; j++)
		{
			timer[i].TMdata[j]=0;
		}
	}

//	TMdata = (uint8 **)os_malloc(sizeof(uint8 *)*24);//为二维数组分配24行
//
//	for(i=0; i<24; i++)
//	{
//		TMdata[i] = (uint8 *)os_malloc(sizeof(uint8 *)*24);
//	}

	system_init_done_cb(system_done);//注册系统初始化完成之后回调函数
}


void user_rf_pre_init(){

}



