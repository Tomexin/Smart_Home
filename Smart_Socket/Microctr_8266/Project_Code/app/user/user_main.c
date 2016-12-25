/*
 * user_main.c
 *
 *  Created on: 2016��5��10��
 *      Author: Administrator
 *
 *  ���ߣ�����
 *  ���ڣ�2016��6��25��
 *  �������ù̼�Ϊ�������ܲ����̼���֧��Ӳ�������ͬʱ���ƣ�֧�ַ������쳣�Ͽ���������֧��·�����쳣�Ͽ���
 *  ������gpio4��Ϊ״ָ̬ʾ�ƣ�gpio5��Ϊ���ؿ��ƿڣ�gpio12��Ϊ�����жϿڡ�
 *  �������ܲ������ƹ̼�3���������������Ͽ����������Ӻ��Զ�����
 *  date:2016��7��1��
 *  ��������ܲ����̼�������һ��
 *
 */

#include "user_main.h"

//smartconfig���ܵĻص�����
void ICACHE_FLASH_ATTR smartconfig_done(sc_status status, void *pdata)
{
	//os_printf("\r\nplease smartconfig\r\n");
	os_timer_disarm(&connect_timer);//�رն�ʱ��
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
            os_timer_arm(&connect_timer,1000,NULL);//����ʹ�ܶ�ʱ��
            break;
    }

}

//��ʱ���ص���������ʱ���֮�����Ƿ�����AP
void ICACHE_FLASH_ATTR Wifi_connect(void *arg){
	os_timer_disarm(&connect_timer);//�رն�ʱ��
	//count++;
	os_delay_us(1000);
	status = wifi_station_get_connect_status();
	if(status == STATION_GOT_IP)
	{
		wifi_discon_flag = 0;
		//client
		os_printf("\r\nWiFi connect success\r\n");
		GPIO_OUTPUT_SET(GPIO_ID_PIN(4), 1);//led������ģ����������
		restart_flag = 0;
		//hardware_flag = 0;

		//SNTP������
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
			if(count > 8)//�Զ�����10�Σ����ɹ�����û������AP��
						//ע�⣺������������̫�٣���Ȼ��������У��޷��ɹ�����ap,�ر���smartconfig֮��
			{
				GPIO_OUTPUT_SET(GPIO_ID_PIN(4), 0);//led����ģ�����smartconfig״̬
				//os_printf("\r\nwifi connect fail,please smartconfig\r\n");

				//smartconfig_stop();
				smartconfig_start(smartconfig_done, 0);//����WiFiģ���smartconfig����,���ڽ���ӡ���ӽ��

				return;//һ��Ҫ��return����Ȼһ�������
						//���ӣ�һ��������������smartconfigģʽ����л8266Ⱥ����ָ��
			}
			os_delay_us(500);
		}
	}
	os_timer_arm(&connect_timer,1000,NULL);//����ʹ�ܶ�ʱ��
}

//����GPIO12�жϴ����ص������������Լ�ICACHE_FLASH_ATTR�꣬��������
//�жϹ���Ϊͨ���ⲿ������ʽʵ�ֿ��ƿ��ص�Ŀ��
//��������5��ģ�����½���smartconfigģʽ
LOCAL void key_init_handle(void *arg)
{

	uint16 gpio_status=0;
	gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);//�ж�IO��״̬
	gpio_pin_intr_state_set(GPIO_ID_PIN(12),GPIO_PIN_INTR_DISABLE);//�ر�GPIO12�ж�
	GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status);//����жϱ�־

	os_delay_us(5000); //��ʱ����
	if(GPIO_INPUT_GET(12) == 0)
	{
		if(GPIO_INPUT_GET(5) == 0)
		{
			GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//�򿪿���
			switch_on = 1;//��������״̬��ʶλ��1
			espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
		}
		else
		{
			GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//�ص�����
			switch_on = 0;//��������״̬��ʶλ����
			espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
		}
	}

	//�豸���ù���
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
			os_timer_disarm(&heartbeat_timer);//�ر���������ʱ��
			restart_flag = 1;//����restart_flag
			wifi_station_disconnect();//�Ͽ�wifi����
			smartconfig_start(smartconfig_done, 0);//����smartconfigģʽ
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
	//���������ж����Ͳ�ʹ���ж�
	gpio_pin_intr_state_set(GPIO_ID_PIN(12),GPIO_PIN_INTR_NEGEDGE);
	ETS_GPIO_INTR_ENABLE();
}

//GPIO�жϳ�ʼ������
void ICACHE_FLASH_ATTR GPIO_intr_init(void)
{
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U,FUNC_GPIO12);//����IO12ΪGPIO12
	ETS_GPIO_INTR_ATTACH(key_init_handle,NULL);//ע��GPIO�жϴ����ص�����
	ETS_GPIO_INTR_DISABLE();//��ֹ����GPIO�ж�
	GPIO_DIS_OUTPUT(GPIO_ID_PIN(12));//��GPIO12����Ϊ����ģʽ
	//����GPIO12�ļĴ���
	gpio_register_set(GPIO_PIN_ADDR(12), \
			GPIO_PIN_INT_TYPE_SET(GPIO_PIN_INTR_DISABLE) \
			| GPIO_PIN_PAD_DRIVER_GET(GPIO_PAD_DRIVER_DISABLE)\
			| GPIO_PIN_SOURCE_SET(GPIO_AS_PIN_SOURCE));
	//�����жϴ�����ʽΪ�½��ش���
	gpio_pin_intr_state_set(GPIO_ID_PIN(12),GPIO_PIN_INTR_NEGEDGE);
	//ʹ���ж�
	ETS_GPIO_INTR_ENABLE();
}

//ϵͳ��ʼ�����֮��Ļص��������ص�������ִ��ɨ�軷��AP������
void system_done(void)
{
	//��ȡWiFiģ���mac��ַ
	wifi_get_macaddr(STATION_IF, my_sta_mac);
	//os_printf(MACSTR);
	os_sprintf(macaddr1, ""MACSTR"\r\n", MAC2STR(my_sta_mac));
	//os_printf(macaddr1);

	os_timer_disarm(&connect_timer);//�رն�ʱ��
	os_timer_setfn(&connect_timer,Wifi_connect,NULL);//���ö�ʱ���ص�����Wifi_connect
	os_timer_arm(&connect_timer,1000,NULL);//�����ʱ��ʱ1s�����Զ���װ
}

//������ں���
void user_init(){
	int i=0, j=0;
	uart_init(115200,115200);
	wifi_discon_flag = 0;
	switch_on = 0;//�����ϵ�Ĭ�Ϲر�

	//gpio4�ڿ���״ָ̬ʾ�ƣ�gpio5��Ϊ���ؿ��ƿ�
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U,FUNC_GPIO4);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U,FUNC_GPIO5);
	GPIO_OUTPUT_SET(GPIO_ID_PIN(4), 1);//led������ģ����빤��״̬
	GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//���������ϵ�Ĭ�Ϲر�

	GPIO_intr_init();//����GPIO�жϳ�ʼ������
	//����WiFi����ģʽΪstationģʽ
	wifi_set_opmode(0x01);

	//���ṹ��������Ԫ������
	for(i=0; i<8; i++)
	{
		for(j=0; j<24; j++)
		{
			timer[i].TMdata[j]=0;
		}
	}

//	TMdata = (uint8 **)os_malloc(sizeof(uint8 *)*24);//Ϊ��ά�������24��
//
//	for(i=0; i<24; i++)
//	{
//		TMdata[i] = (uint8 *)os_malloc(sizeof(uint8 *)*24);
//	}

	system_init_done_cb(system_done);//ע��ϵͳ��ʼ�����֮��ص�����
}


void user_rf_pre_init(){

}



