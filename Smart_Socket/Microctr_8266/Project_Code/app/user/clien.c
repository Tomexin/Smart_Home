/*
 * clien.c
 *
 *  Created on: 2016年5月14日
 *      Author: Administrator
 */
#include "clien.h"
unsigned int i =0;//计数标志位
unsigned int j=0, k=0;//计数标志位
unsigned int l=0, n =0;//计数标志位
bool Mon[8]={0}, Tue[8]={0}, Wed[8]={0}, Thu[8]={0}, Fri[8]={0}, Sat[8]={0}, Sun[8]={0}; //
char *real_time;//北京时间
bool count_down_flag = 0;//倒计时标志位
bool daojishi = 0;
bool timer_flag[8] = {0};//用户定时开关标志位
bool timer_repeat[8] = {1};//定时单次或是多次标志位

void ICACHE_FLASH_ATTR dingshi_fun(void)
{
	int a =0;
	int p = 0;
	time = sntp_get_current_timestamp();//获取服务器时间
	real_time = sntp_get_real_time(time);//将服务器时间转换成北京时间
	os_printf("%s",real_time);//串口打印北京时间
	//real_time = strchr(real_time, 'T');
	for(p=0; p<8; p++)
	{
		if(Mon[p] == 1)
		{
			if(timer_flag[p] == 1)
			{
				if(real_time[0]=='M' && real_time[1]=='o' && real_time[2]== 'n')
				{
					if(real_time[11]==timer[p].TMdata[10] && real_time[12]==timer[p].TMdata[11]&&\
					   real_time[13]==timer[p].TMdata[12] && real_time[14]==timer[p].TMdata[13]&&\
					   real_time[15]==timer[p].TMdata[14])
					{
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//打开开关
						switch_on = 1;//开关状态标识位置1
						espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
						if(timer_repeat[p] == 0)
						{
							if(timer[p].TMdata[16]>='0' && timer[p].TMdata[16]<='9')
							{}
							else
							{
								//spi_flash必须先擦除旧数据才能写入新数据,so先擦除扇区数据
								spi_flash_erase_sector(0x3C);
								//写入更新数据
								spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
								//将未更新的数据重新写入
								for(a=0; a<8; a++)
								{
									if(a!= p)
									{
										os_memcpy(DMdata, timer[a].TMdata, 24);
										spi_flash_write(0x3C*4096+24*a, (uint32 *)(DMdata), 24);
									}
									os_delay_us(70);
								}
								timer_repeat[p] = 1;
							}
						}

					}

					if(real_time[11]==timer[p].TMdata[16] && real_time[12]==timer[p].TMdata[17]&&\
					   real_time[13]==timer[p].TMdata[18] && real_time[14]==timer[p].TMdata[19]&&\
					   real_time[15]==timer[p].TMdata[20])
					{
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//关掉开关
						switch_on = 0;//开关状态标志位清零
						espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
						if(timer_repeat[p] == 0)
						{
							//spi_flash必须先擦除旧数据才能写入新数据,so先擦除扇区数据
							spi_flash_erase_sector(0x3C);
							//写入更新数据
							spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
							//将未更新的数据重新写入
							for(a=0; a<8; a++)
							{
								if(a != p)
								{
									os_memcpy(DMdata, timer[a].TMdata, 24);
									spi_flash_write(0x3C*4096+24*a, (uint32 *)(DMdata), 24);
								}
								os_delay_us(70);
							}
						}
					}

				}
			}
		}
		if(Tue[p] == 1)
		{
			if(timer_flag[p] == 1)
			{
			//real_time = strchr(real_time, 'T');
				if(real_time[0]=='T' && real_time[1]=='u' && real_time[2]== 'e')
				{
					//os_printf("%c\r\n", real_time[15]);
					//os_printf("%c\r\n", TMdata[p][14]);
					if(real_time[11]==timer[p].TMdata[10] && real_time[12]==timer[p].TMdata[11]&&\
					   real_time[13]==timer[p].TMdata[12] && real_time[14]==timer[p].TMdata[13]&&\
					   real_time[15]==timer[p].TMdata[14])
					{
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//打开开关
						switch_on = 1;//插座开关状态标识位置1
						espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
						if(timer_repeat[p] == 0)
						{
							if(timer[p].TMdata[16]>='0' && timer[p].TMdata[16]<='9')
							{}
							else
							{
								//spi_flash必须先擦除旧数据才能写入新数据,so先擦除扇区数据
								spi_flash_erase_sector(0x3C);
								//写入更新数据
								spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
								//将未更新的数据重新写入
								for(a=0; a<8; a++)
								{
									if(a!= p)
									{
										os_memcpy(DMdata, timer[a].TMdata, 24);
										spi_flash_write(0x3C*4096+24*a, (uint32 *)(DMdata), 24);
									}
									os_delay_us(70);
								}
								timer_repeat[p] = 1;
							}
						}
					}

					if(real_time[11]==timer[p].TMdata[16] && real_time[12]==timer[p].TMdata[17]&&\
					   real_time[13]==timer[p].TMdata[18] && real_time[14]==timer[p].TMdata[19]&&\
					   real_time[15]==timer[p].TMdata[20])
					{
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//关掉开关
						switch_on = 0;//插座开关状态标志位清零
						espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
						if(timer_repeat[p] == 0)
						{
							//spi_flash必须先擦除旧数据才能写入新数据,so先擦除扇区数据
							spi_flash_erase_sector(0x3C);
							//写入更新数据
							spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
							//将未更新的数据重新写入
							for(a=0; a<8; a++)
							{
								if(a != p)
								{
									os_memcpy(DMdata, timer[a].TMdata, 24);
									spi_flash_write(0x3C*4096+24*a, (uint32 *)(DMdata), 24);
								}
								os_delay_us(70);
							}
						}
					}
				}
			}
		}
		if(Wed[p] == 1)
		{
			if(timer_flag[p] == 1)
			{
				if(real_time[0]=='W' && real_time[1]=='e' && real_time[2]== 'd')
				{
					os_printf("Wed[%d],%c\r\n", p, real_time[15]);
					os_printf("Wed[%d],%c\r\n", p, timer[p].TMdata[14]);
					if(real_time[11]==timer[p].TMdata[10] && real_time[12]==timer[p].TMdata[11]&&\
					   real_time[13]==timer[p].TMdata[12] && real_time[14]==timer[p].TMdata[13]&&\
					   real_time[15]==timer[p].TMdata[14])
					{
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//打开开关
						switch_on = 1;//插座开关状态标识位置1
						espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
						if(timer_repeat[p] == 0)
						{
							if(timer[p].TMdata[16]>='0' && timer[p].TMdata[16]<='9')
							{}
							else
							{
								//spi_flash必须先擦除旧数据才能写入新数据,so先擦除扇区数据
								spi_flash_erase_sector(0x3C);
								//写入更新数据
								spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
								//将未更新的数据重新写入
								for(a=0; a<8; a++)
								{
									if(a!= p)
									{
										os_memcpy(DMdata, timer[a].TMdata, 24);
										spi_flash_write(0x3C*4096+24*a, (uint32 *)(DMdata), 24);
									}
									os_delay_us(70);
								}
								timer_repeat[p] = 1;
							}
						}
					}

					if(real_time[11]==timer[p].TMdata[16] && real_time[12]==timer[p].TMdata[17]&&\
					   real_time[13]==timer[p].TMdata[18] && real_time[14]==timer[p].TMdata[19]&&\
					   real_time[15]==timer[p].TMdata[20])
					{
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//关掉开关
						switch_on = 0;//插座开关状态标识位清零
						espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
						if(timer_repeat[p] == 0)
						{
							//spi_flash必须先擦除旧数据才能写入新数据,so先擦除扇区数据
							spi_flash_erase_sector(0x3C);
							//写入更新数据
							spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
							//将未更新的数据重新写入
							for(a=0; a<8; a++)
							{
								if(a!= p)
								{
									os_memcpy(DMdata, timer[a].TMdata, 24);
									spi_flash_write(0x3C*4096+24*a, (uint32 *)(DMdata), 24);
								}
								os_delay_us(70);
							}
						}
					}
				}
			}
		}
		if(Thu[p] == 1)
		{
			if(timer_flag[p] == 1)
			{
				if(real_time[0]=='T' && real_time[1]=='h' && real_time[2]== 'u')
				{
					//os_printf("%c\r\n", real_time[11]);
					//os_printf("%c\r\n", TMdata[p][16]);
					if(real_time[11]==timer[p].TMdata[10] && real_time[12]==timer[p].TMdata[11]&&\
					   real_time[13]==timer[p].TMdata[12] && real_time[14]==timer[p].TMdata[13]&&\
					   real_time[15]==timer[p].TMdata[14])
					{
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//打开开关
						switch_on = 1;//开关状态标识位置1
						espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
						if(timer_repeat[p] == 0)
						{
							if(timer[p].TMdata[16]>='0' && timer[p].TMdata[16]<='9')
							{}
							else
							{
								//spi_flash必须先擦除旧数据才能写入新数据,so先擦除扇区数据
								spi_flash_erase_sector(0x3C);
								//写入更新数据
								spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
								//将未更新的数据重新写入
								for(a=0; a<8; a++)
								{
									if(a!= p)
									{
										os_memcpy(DMdata, timer[a].TMdata, 24);
										spi_flash_write(0x3C*4096+24*a, (uint32 *)(DMdata), 24);
									}
									os_delay_us(70);
								}
								timer_repeat[p] = 1;
							}
						}
					}

					if(real_time[11]==timer[p].TMdata[16] && real_time[12]==timer[p].TMdata[17]&&\
					   real_time[13]==timer[p].TMdata[18] && real_time[14]==timer[p].TMdata[19]&&\
					   real_time[15]==timer[p].TMdata[20])
					{
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//关掉开关
						switch_on = 0;//插座开关状态标志位清零
						espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
						if(timer_repeat[p] == 0)
						{
							//spi_flash必须先擦除旧数据才能写入新数据,so先擦除扇区数据
							spi_flash_erase_sector(0x3C);
							//写入更新数据
							spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
							//将未更新的数据重新写入
							for(a=0; a<8; a++)
							{
								if(a!= p)
								{
									os_memcpy(DMdata, timer[a].TMdata, 24);
									spi_flash_write(0x3C*4096+24*a, (uint32 *)(DMdata), 24);
								}
								os_delay_us(70);
							}
						}
					}
				}
			}
		}
		if(Fri[p] == 1)
		{
			if(timer_flag[p] == 1)
			{
				if(real_time[0]=='F' && real_time[1]=='r' && real_time[2]== 'i')
				{
					os_printf("%c\r\n", real_time[15]);
					os_printf("%c\r\n", timer[p].TMdata[14]);
					if(real_time[11]==timer[p].TMdata[10] && real_time[12]==timer[p].TMdata[11]&&\
					   real_time[13]==timer[p].TMdata[12] && real_time[14]==timer[p].TMdata[13]&&\
					   real_time[15]==timer[p].TMdata[14])
					{
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//打开开关
						switch_on = 1; //插座开关状态标识位置1
						espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
						if(timer_repeat[p] == 0)
						{
							if(timer[p].TMdata[16]>='0' && timer[p].TMdata[16]<='9')
							{}
							else
							{
								//spi_flash必须先擦除旧数据才能写入新数据,so先擦除扇区数据
								spi_flash_erase_sector(0x3C);
								//写入更新数据
								spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
								//将未更新的数据重新写入
								for(a=0; a<8; a++)
								{
									if(a!= p)
									{
										os_memcpy(DMdata, timer[a].TMdata, 24);
										spi_flash_write(0x3C*4096+24*a, (uint32 *)(DMdata), 24);
									}
									os_delay_us(70);
								}
								timer_repeat[p] = 1;
							}
						}
					}

					if(real_time[11]==timer[p].TMdata[16] && real_time[12]==timer[p].TMdata[17]&&\
					   real_time[13]==timer[p].TMdata[18] && real_time[14]==timer[p].TMdata[19]&&\
					   real_time[15]==timer[p].TMdata[20])
					{
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//关掉开关
						switch_on = 0;//插座开关状态标识位清零
						espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
						if(timer_repeat[p] == 0)
						{
							//spi_flash必须先擦除旧数据才能写入新数据,so先擦除扇区数据
							spi_flash_erase_sector(0x3C);
							//写入更新数据
							spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
							//将未更新的数据重新写入
							for(a=0; a<8; a++)
							{
								if(a!= p)
								{
									os_memcpy(DMdata, timer[a].TMdata, 24);
									spi_flash_write(0x3C*4096+24*a, (uint32 *)(DMdata), 24);
								}
								os_delay_us(70);
							}
						}
					}
				}
			}
		}
		if(Sat[p] == 1)
		{
			if(timer_flag[p] == 1)
			{
				if(real_time[0]=='S' && real_time[1]=='a' && real_time[2]== 't')
				{
					if(real_time[11]==timer[p].TMdata[10] && real_time[12]==timer[p].TMdata[11]&&\
					   real_time[13]==timer[p].TMdata[12] && real_time[14]==timer[p].TMdata[13]&&\
					   real_time[15]==timer[p].TMdata[14])
					{
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//打开开关
						switch_on = 1;//插座开关状态标识位置1
						espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
						if(timer_repeat[p] == 0)
						{
							if(timer[p].TMdata[16]>='0' && timer[p].TMdata[16]<='9')
							{}
							else
							{
								//spi_flash必须先擦除旧数据才能写入新数据,so先擦除扇区数据
								spi_flash_erase_sector(0x3C);
								//写入更新数据
								spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
								//将未更新的数据重新写入
								for(a=0; a<8; a++)
								{
									if(a!= p)
									{
										os_memcpy(DMdata, timer[a].TMdata, 24);
										spi_flash_write(0x3C*4096+24*a, (uint32 *)(DMdata), 24);
									}
									os_delay_us(70);
								}
								timer_repeat[p] = 1;
							}
						}
					}

					if(real_time[11]==timer[p].TMdata[16] && real_time[12]==timer[p].TMdata[17]&&\
					   real_time[13]==timer[p].TMdata[18] && real_time[14]==timer[p].TMdata[19]&&\
					   real_time[15]==timer[p].TMdata[20])
					{
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//关掉开关
						switch_on = 0;//开关状态标识位清零
						espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
						if(timer_repeat[p] == 0)
						{
							//spi_flash必须先擦除旧数据才能写入新数据,so先擦除扇区数据
							spi_flash_erase_sector(0x3C);
							//写入更新数据
							spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
							//将未更新的数据重新写入
							for(a=0; a<8; a++)
							{
								if(a!= p)
								{
									os_memcpy(DMdata, timer[a].TMdata, 24);
									spi_flash_write(0x3C*4096+24*a, (uint32 *)(DMdata), 24);
								}
								os_delay_us(70);
							}
						}
					}
				}
			}
		}
		if(Sun[p] == 1)
		{
			if(timer_flag[p] == 1)
			{
				if(real_time[0]=='S' && real_time[1]=='u' && real_time[2]== 'n')
				{
					if(real_time[11]==timer[p].TMdata[10] && real_time[12]==timer[p].TMdata[11]&&\
					   real_time[13]==timer[p].TMdata[12] && real_time[14]==timer[p].TMdata[13]&&\
					   real_time[15]==timer[p].TMdata[14])
					{
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//打开开关
						switch_on = 1;//开关状态标识位置1
						espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
						if(timer_repeat[p] == 0)
						{
							if(timer[p].TMdata[16]>='0' && timer[p].TMdata[16]<='9')
							{}
							else
							{
								//spi_flash必须先擦除旧数据才能写入新数据,so先擦除扇区数据
								spi_flash_erase_sector(0x3C);
								//写入更新数据
								spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
								//将未更新的数据重新写入
								for(a=0; a<8; a++)
								{
									if(a!= p)
									{
										os_memcpy(DMdata, timer[a].TMdata, 24);
										spi_flash_write(0x3C*4096+24*a, (uint32 *)(DMdata), 24);
									}
									os_delay_us(70);
								}
								timer_repeat[p] = 1;
							}
						}
					}

					if(real_time[11]==timer[p].TMdata[16] && real_time[12]==timer[p].TMdata[17]&&\
					   real_time[13]==timer[p].TMdata[18] && real_time[14]==timer[p].TMdata[19]&&\
					   real_time[15]==timer[p].TMdata[20])
					{
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//关掉开关
						switch_on = 0;//开关状态标识位清零
						espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
						if(timer_repeat[p] == 0)
						{
							//spi_flash必须先擦除旧数据才能写入新数据,so先擦除扇区数据
							spi_flash_erase_sector(0x3C);
							//写入更新数据
							spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
							//将未更新的数据重新写入
							for(a=0; a<8; a++)
							{
								if(a!= p)
								{
									os_memcpy(DMdata, timer[a].TMdata, 24);
									spi_flash_write(0x3C*4096+24*a, (uint32 *)(DMdata), 24);
								}
								os_delay_us(70);
							}
						}
					}
				}
			}
		}
	}
}

//软件定时器回调函数，用作心跳包，智能插座定时功能，智能插座倒计时功能
void ICACHE_FLASH_ATTR heatbeat_cb(void)
{
	i++;
	if(i == 30)//每隔60秒循环一次
	{

		dingshi_fun();//智能插座实现定时功能函数

		//智能插座倒计时功能
		if(daojishi == 1)
		{
			l++;
			if(l == count_down)
			{
				l=0;
				daojishi = 0;
				count_down  = 0;
				if(count_down_flag == 1)
				{
					GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//打开开关
					switch_on = 1;//插座开关状态标识位置1
					espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
				}
				else
				{
					GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//关掉开关
					switch_on = 0;//插座开关状态标识位清零
					espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
				}
			}
		}

		espconn_sent(pespconn, "wo\r\n",strlen("wo\r\n"));//心跳包
		i = 0;
	}
	os_timer_arm(&heartbeat_timer,2000,NULL);//重新使能软件定时器
}

//网络数据接收成功的回调函数
void  ICACHE_FLASH_ATTR user_tcp_recv_cb(void*arg, char *pdata, unsigned short len)
{
	int i = 0;
	//TMdata = pdata;
	os_printf("\r\n收到数据%s\r\n", pdata);
	pdata = strchr(pdata, '{');
	os_delay_us(300);//延时300ms
	if(pdata != NULL)
	{
		//插座开关控制
		if(pdata[0] == '{' && pdata[1] == 'Z' && pdata[2] == 'Z' \
				&& pdata[3] == 'Z' && pdata[4] == '0' && pdata[5] == '1'\
				&& pdata[6] == '}')
		{
			GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//打开开关
			switch_on = 1;//插座开关状态标识位置1
			espconn_sent(pespconn, "[ZZZ01]\r\n", strlen("[ZZZ01]\r\n"));//反馈服务器
		}

		if(pdata[0] == '{' && pdata[1] == 'Z' && pdata[2] == 'Z' \
				&& pdata[3] == 'Z' && pdata[4] == '0' && pdata[5] == '2'\
				&& pdata[6] == '}')
		{
			GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//关掉开关
			switch_on = 0;//插座开关状态标识位清零
			espconn_sent(pespconn, "[ZZZ02]\r\n", strlen("[ZZZ02]\r\n"));//反馈服务器
		}

		//8266给服务器反馈插座开关状态
		if(pdata[0]=='{' && pdata[1]=='W' && pdata[2]=='}')
		{
			if(switch_on == 1)//插座状态为开
			{
				espconn_sent(pespconn, "[ZZZ01]\r\n", strlen("[ZZZ01]\r\n"));//反馈服务器
			}
			if(switch_on == 0)//插座状态为关
			{
				espconn_sent(pespconn, "[ZZZ02]\r\n", strlen("[ZZZ02]\r\n"));//反馈服务器
			}
		}

		//8266给服务器反馈定时数据
		if(pdata[0]=='{' && pdata[1]=='T' && pdata[2]=='M' && pdata[3]=='}')
		{
			int k=0;
			for(k=0; k<8; k++)
			{
				spi_flash_read(0x3C*4096+24*k, (uint32 *)(DMdata), 24);
				os_memcpy(timer[k].TMdata, DMdata, 24);
				timer[k].TMdata[0] = '[';//给服务器发送数据以'['开头,']'结尾
				timer[k].TMdata[23] = ']';
				espconn_sent(pespconn, timer[k].TMdata, 24);
				espconn_sent(pespconn, "\r\n", strlen("\r\n"));
				timer[k].TMdata[0] = '{';//重新恢复数据
				timer[k].TMdata[23] = '}';
				os_delay_us(1000);//延时1ms
			}
		}

		//智能插座定时功能接收数据
		if(pdata[1] == 'S' || pdata[1] == 'R')
		{
			int a;
			TM_ID = (uint8)((pdata[21]-'0')*10+(pdata[22]-'0'));//获取定时用户ID
			os_printf("%d\n", TM_ID);
			//写入是否重复定时标志位
			if(pdata[1] == 'R')
				timer_repeat[TM_ID] = 1;
			else if(pdata[1] == 'S')
				timer_repeat[TM_ID] = 0;
			else
				timer_repeat[TM_ID] = 0;

			//写入定时开关标志位
			if(pdata[2] == 'K')
			{
				timer_flag[TM_ID] = 1;
			}
			else if(pdata[2] == 'G')
			{
				timer_flag[TM_ID] = 0;
			}
			else
			{
				timer_flag[TM_ID] = 0;
			}

			os_memcpy(timer[TM_ID].TMdata, pdata, 24);//将收到的数据存入TMdata中
			os_memcpy(DMdata, timer[TM_ID].TMdata, 24);
			//spi_flash必须先擦除旧数据才能写入新数据,so先擦除扇区数据
			spi_flash_erase_sector(0x3C);
			//写入更新数据
			spi_flash_write(0x3C*4096+24*TM_ID, (uint32 *)(DMdata), 24);
			//将未更新的数据重新写入
			for(a=0; a<8; a++)
			{
				if(a!= TM_ID)
				{
					os_memcpy(DMdata, timer[a].TMdata, 24);
					spi_flash_write(0x3C*4096+24*a, (uint32 *)(DMdata), 24);
				}
				os_delay_us(70);
			}

			if(pdata[3] == '1')
				Mon[TM_ID] = 1;
			if(pdata[4] == '1')
				Tue[TM_ID] = 1;
			if(pdata[5] == '1')
				Wed[TM_ID] = 1;
			if(pdata[6] == '1')
				Thu[TM_ID] = 1;
			if(pdata[7] == '1')
				Fri[TM_ID] = 1;
			if(pdata[8] == '1')
				Sat[TM_ID] = 1;
			if(pdata[9] == '1')
				Sun[TM_ID] = 1;
		}

		//智能插座倒计时功能接收数据
		if(pdata[1]=='C' && pdata[2]=='D')
		{
			l = 0;
			n = 0;
			if(pdata[3] == 'Q')
			{
				daojishi = 0;
			}
			else
			{
				daojishi = 1;
				count_down = (uint32)(((pdata[3]-'0')*10+(pdata[4]-'0'))*60+((pdata[5]-'0')*10+(pdata[6]-'0')));
				//os_printf("%d\n", count_down);
				if(pdata[7] == 'K')
				{
					count_down_flag = 1;
				}
				if(pdata[7] == 'G')
				{
					count_down_flag = 0;
				}
			}
		}
	}
}

//发送数据成功后的回调函数
void ICACHE_FLASH_ATTR user_tcp_sent_cb(void *arg)
{
	//os_printf("send_data_ok");
//	hw_timer_init(FRC1_SOURCE, 0);//硬件定时器初始化，适用于需要高精度定时场合使用，普通场合使用软件定时器
//	hw_timer_set_func(hw_test_timer_cb);//设置硬件定时器回调函数
//	hw_timer_arm(1000000);//定时时间1S，单位时间是1us
}

//断开TCP连接的回调函数
void ICACHE_FLASH_ATTR user_tcp_discon_cb(void *arg)
{
	if(restart_flag == 0)
	{
		status = wifi_station_get_connect_status();

		//服务器断，WiFi未断
		if(status == STATION_GOT_IP)
		{
			os_delay_us(1000000);
			//重新连接TCPserver
			espconn_connect((struct espconn *)arg);
		}
		//服务器和WiFi均断
		else
		{
			GPIO_OUTPUT_SET(GPIO_ID_PIN(4), 1);//指示灯灭
		}
	}
}

//TCP连接成功后的回调函数
void ICACHE_FLASH_ATTR user_tcp_connect_cb(void *arg)
{
	uint8 g=0;
	//读取flash中的数据存入TMdata中
	for(g=0; g<8; g++)
	{
		spi_flash_read(0x3C*4096+24*g, (uint32 *)(DMdata), 24);
		os_memcpy(timer[g].TMdata, DMdata, 24);
		os_printf("%s ",timer[g].TMdata);

		//读取是否重复定时标志位
		if(timer[g].TMdata[1] == 'R')
			timer_repeat[g] = 1;
		else if(timer[g].TMdata[1] == 'S')
			timer_repeat[g] = 0;
		else
			timer_repeat[g] = 0;
		//读取定时开关标志位
		if(timer[g].TMdata[2] == 'K')
			timer_flag[g] = 1;
		else if(timer[g].TMdata[2] == 'G')
			timer_flag[g] = 0;
		else
			timer_flag[g] = 0;
		//判断一周定时频度
		if(timer[g].TMdata[3] == '1')
			Mon[g] = 1;
		if(timer[g].TMdata[4] == '1')
			Tue[g] = 1;
		if(timer[g].TMdata[5] == '1')
			Wed[g] = 1;
		if(timer[g].TMdata[6] == '1')
			Thu[g] = 1;
		if(timer[g].TMdata[7] == '1')
			Fri[g] = 1;
		if(timer[g].TMdata[8] == '1')
			Sat[g] = 1;
		if(timer[g].TMdata[9] == '1')
			Sun[g] = 1;
		os_delay_us(100);
	}
	for(g=0; g<24; g++)
	{
		DMdata[i] = 0;
	}
	GPIO_OUTPUT_SET(GPIO_ID_PIN(4), 1);//指示灯亮
	pespconn = arg;
	//注册接收数据的回调函数
	espconn_regist_recvcb(pespconn, user_tcp_recv_cb);
	//注册发送数据成功的回调函数
	espconn_regist_sentcb(pespconn, user_tcp_sent_cb);
	//注册断开连接的回调函数
	espconn_regist_disconcb(pespconn, user_tcp_discon_cb);

	//发送WiFi模块MAC地址
	os_delay_us(300);//延时300us
	espconn_sent(pespconn, macaddr1, strlen(macaddr1));
	os_printf("%s\n",macaddr1);

	//注册软件定时器，用作心跳包、智能插座定时功能、智能插座倒计时功能
	os_timer_disarm(&heartbeat_timer);//关闭定时器
	os_timer_setfn(&heartbeat_timer,heatbeat_cb,NULL);//设置定时器回调函数Wifi_connect
	os_timer_arm(&heartbeat_timer,2000,NULL);//软件定时延时2s，不自动重装
}

//TCP连接失败后重连的回调函数
//wifi连接和服务器连接均失败指示灯灭
//服务器连接失败指示灯闪烁
void ICACHE_FLASH_ATTR user_tcp_recon_cb(void *arg, sint8 err)
{
	if(restart_flag == 0)
	{
			status = wifi_station_get_connect_status();
			//服务器断，WiFi未断
			if(status == STATION_GOT_IP)
			{
				os_printf("服务器断了，路由器没断");
				//指示灯闪烁
				if(GPIO_INPUT_GET(4) == 0)
					GPIO_OUTPUT_SET(GPIO_ID_PIN(4), 1);
				else
					GPIO_OUTPUT_SET(GPIO_ID_PIN(4), 0);
				//os_printf("连接错误，错误代码为%d\r\n",err);
				os_delay_us(10000);
				//重新连接TCPserver
				espconn_connect((struct espconn *)arg);
				os_delay_us(10000);
			}
			//服务器和WiFi均断
			else
			{
				os_printf("服务器和路由器都断了\r\n");
				GPIO_OUTPUT_SET(GPIO_ID_PIN(4), 0);//指示灯灭
				wifi_discon_flag = 1;
				os_timer_disarm(&connect_timer);//关闭定时器
				os_timer_arm(&connect_timer,1000,NULL);//使能WiFi连接定时器
			}
			os_delay_us(500000);
	}
}

//TCP连接函数
void ICACHE_FLASH_ATTR my_station_init(struct ip_addr *remote_ip, struct ip_addr *local_ip, int remote_port)
{
	// espconn参数配置
	user_tcp_conn.type = ESPCONN_TCP;
	user_tcp_conn.state = ESPCONN_NONE;
	user_tcp_conn.proto.tcp = (esp_tcp *)os_zalloc(sizeof(esp_tcp));
	os_memcpy(user_tcp_conn.proto.tcp->local_ip, local_ip, 4);
	os_memcpy(user_tcp_conn.proto.tcp->remote_ip, remote_ip,4);
	user_tcp_conn.proto.tcp->local_port = espconn_port();
	user_tcp_conn.proto.tcp->remote_port = remote_port;

	//注册TCP连接成功后的回调函数
	espconn_regist_connectcb(&user_tcp_conn, user_tcp_connect_cb);
	//注册TCP连接发生异常断开时的回调函数，一般设置重连
	espconn_regist_reconcb(&user_tcp_conn, user_tcp_recon_cb);

	//启用连接TCPserver
	espconn_connect(&user_tcp_conn);//连接TCPserver
}

