/*
 * clien.c
 *
 *  Created on: 2016��5��14��
 *      Author: Administrator
 */
#include "clien.h"
unsigned int i =0;//������־λ
unsigned int j=0, k=0;//������־λ
unsigned int l=0, n =0;//������־λ
bool Mon[8]={0}, Tue[8]={0}, Wed[8]={0}, Thu[8]={0}, Fri[8]={0}, Sat[8]={0}, Sun[8]={0}; //
char *real_time;//����ʱ��
bool count_down_flag = 0;//����ʱ��־λ
bool daojishi = 0;
bool timer_flag[8] = {0};//�û���ʱ���ر�־λ
bool timer_repeat[8] = {1};//��ʱ���λ��Ƕ�α�־λ

void ICACHE_FLASH_ATTR dingshi_fun(void)
{
	int a =0;
	int p = 0;
	time = sntp_get_current_timestamp();//��ȡ������ʱ��
	real_time = sntp_get_real_time(time);//��������ʱ��ת���ɱ���ʱ��
	os_printf("%s",real_time);//���ڴ�ӡ����ʱ��
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
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//�򿪿���
						switch_on = 1;//����״̬��ʶλ��1
						espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
						if(timer_repeat[p] == 0)
						{
							if(timer[p].TMdata[16]>='0' && timer[p].TMdata[16]<='9')
							{}
							else
							{
								//spi_flash�����Ȳ��������ݲ���д��������,so�Ȳ�����������
								spi_flash_erase_sector(0x3C);
								//д���������
								spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
								//��δ���µ���������д��
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
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//�ص�����
						switch_on = 0;//����״̬��־λ����
						espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
						if(timer_repeat[p] == 0)
						{
							//spi_flash�����Ȳ��������ݲ���д��������,so�Ȳ�����������
							spi_flash_erase_sector(0x3C);
							//д���������
							spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
							//��δ���µ���������д��
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
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//�򿪿���
						switch_on = 1;//��������״̬��ʶλ��1
						espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
						if(timer_repeat[p] == 0)
						{
							if(timer[p].TMdata[16]>='0' && timer[p].TMdata[16]<='9')
							{}
							else
							{
								//spi_flash�����Ȳ��������ݲ���д��������,so�Ȳ�����������
								spi_flash_erase_sector(0x3C);
								//д���������
								spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
								//��δ���µ���������д��
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
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//�ص�����
						switch_on = 0;//��������״̬��־λ����
						espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
						if(timer_repeat[p] == 0)
						{
							//spi_flash�����Ȳ��������ݲ���д��������,so�Ȳ�����������
							spi_flash_erase_sector(0x3C);
							//д���������
							spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
							//��δ���µ���������д��
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
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//�򿪿���
						switch_on = 1;//��������״̬��ʶλ��1
						espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
						if(timer_repeat[p] == 0)
						{
							if(timer[p].TMdata[16]>='0' && timer[p].TMdata[16]<='9')
							{}
							else
							{
								//spi_flash�����Ȳ��������ݲ���д��������,so�Ȳ�����������
								spi_flash_erase_sector(0x3C);
								//д���������
								spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
								//��δ���µ���������д��
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
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//�ص�����
						switch_on = 0;//��������״̬��ʶλ����
						espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
						if(timer_repeat[p] == 0)
						{
							//spi_flash�����Ȳ��������ݲ���д��������,so�Ȳ�����������
							spi_flash_erase_sector(0x3C);
							//д���������
							spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
							//��δ���µ���������д��
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
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//�򿪿���
						switch_on = 1;//����״̬��ʶλ��1
						espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
						if(timer_repeat[p] == 0)
						{
							if(timer[p].TMdata[16]>='0' && timer[p].TMdata[16]<='9')
							{}
							else
							{
								//spi_flash�����Ȳ��������ݲ���д��������,so�Ȳ�����������
								spi_flash_erase_sector(0x3C);
								//д���������
								spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
								//��δ���µ���������д��
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
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//�ص�����
						switch_on = 0;//��������״̬��־λ����
						espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
						if(timer_repeat[p] == 0)
						{
							//spi_flash�����Ȳ��������ݲ���д��������,so�Ȳ�����������
							spi_flash_erase_sector(0x3C);
							//д���������
							spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
							//��δ���µ���������д��
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
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//�򿪿���
						switch_on = 1; //��������״̬��ʶλ��1
						espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
						if(timer_repeat[p] == 0)
						{
							if(timer[p].TMdata[16]>='0' && timer[p].TMdata[16]<='9')
							{}
							else
							{
								//spi_flash�����Ȳ��������ݲ���д��������,so�Ȳ�����������
								spi_flash_erase_sector(0x3C);
								//д���������
								spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
								//��δ���µ���������д��
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
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//�ص�����
						switch_on = 0;//��������״̬��ʶλ����
						espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
						if(timer_repeat[p] == 0)
						{
							//spi_flash�����Ȳ��������ݲ���д��������,so�Ȳ�����������
							spi_flash_erase_sector(0x3C);
							//д���������
							spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
							//��δ���µ���������д��
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
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//�򿪿���
						switch_on = 1;//��������״̬��ʶλ��1
						espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
						if(timer_repeat[p] == 0)
						{
							if(timer[p].TMdata[16]>='0' && timer[p].TMdata[16]<='9')
							{}
							else
							{
								//spi_flash�����Ȳ��������ݲ���д��������,so�Ȳ�����������
								spi_flash_erase_sector(0x3C);
								//д���������
								spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
								//��δ���µ���������д��
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
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//�ص�����
						switch_on = 0;//����״̬��ʶλ����
						espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
						if(timer_repeat[p] == 0)
						{
							//spi_flash�����Ȳ��������ݲ���д��������,so�Ȳ�����������
							spi_flash_erase_sector(0x3C);
							//д���������
							spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
							//��δ���µ���������д��
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
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//�򿪿���
						switch_on = 1;//����״̬��ʶλ��1
						espconn_sent(pespconn, "[ZZZ01]\r\n",strlen("[ZZZ01]\r\n"));
						if(timer_repeat[p] == 0)
						{
							if(timer[p].TMdata[16]>='0' && timer[p].TMdata[16]<='9')
							{}
							else
							{
								//spi_flash�����Ȳ��������ݲ���д��������,so�Ȳ�����������
								spi_flash_erase_sector(0x3C);
								//д���������
								spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
								//��δ���µ���������д��
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
						GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//�ص�����
						switch_on = 0;//����״̬��ʶλ����
						espconn_sent(pespconn, "[ZZZ02]\r\n",strlen("[ZZZ02]\r\n"));
						if(timer_repeat[p] == 0)
						{
							//spi_flash�����Ȳ��������ݲ���д��������,so�Ȳ�����������
							spi_flash_erase_sector(0x3C);
							//д���������
							spi_flash_write(0x3C*4096+24*p, (uint32 *)("{RG0000000AAAAAAAAAAAAA}"), 24);
							//��δ���µ���������д��
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

//�����ʱ���ص����������������������ܲ�����ʱ���ܣ����ܲ�������ʱ����
void ICACHE_FLASH_ATTR heatbeat_cb(void)
{
	i++;
	if(i == 30)//ÿ��60��ѭ��һ��
	{

		dingshi_fun();//���ܲ���ʵ�ֶ�ʱ���ܺ���

		//���ܲ�������ʱ����
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
		}

		espconn_sent(pespconn, "wo\r\n",strlen("wo\r\n"));//������
		i = 0;
	}
	os_timer_arm(&heartbeat_timer,2000,NULL);//����ʹ�������ʱ��
}

//�������ݽ��ճɹ��Ļص�����
void  ICACHE_FLASH_ATTR user_tcp_recv_cb(void*arg, char *pdata, unsigned short len)
{
	int i = 0;
	//TMdata = pdata;
	os_printf("\r\n�յ�����%s\r\n", pdata);
	pdata = strchr(pdata, '{');
	os_delay_us(300);//��ʱ300ms
	if(pdata != NULL)
	{
		//�������ؿ���
		if(pdata[0] == '{' && pdata[1] == 'Z' && pdata[2] == 'Z' \
				&& pdata[3] == 'Z' && pdata[4] == '0' && pdata[5] == '1'\
				&& pdata[6] == '}')
		{
			GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 1);//�򿪿���
			switch_on = 1;//��������״̬��ʶλ��1
			espconn_sent(pespconn, "[ZZZ01]\r\n", strlen("[ZZZ01]\r\n"));//����������
		}

		if(pdata[0] == '{' && pdata[1] == 'Z' && pdata[2] == 'Z' \
				&& pdata[3] == 'Z' && pdata[4] == '0' && pdata[5] == '2'\
				&& pdata[6] == '}')
		{
			GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);//�ص�����
			switch_on = 0;//��������״̬��ʶλ����
			espconn_sent(pespconn, "[ZZZ02]\r\n", strlen("[ZZZ02]\r\n"));//����������
		}

		//8266��������������������״̬
		if(pdata[0]=='{' && pdata[1]=='W' && pdata[2]=='}')
		{
			if(switch_on == 1)//����״̬Ϊ��
			{
				espconn_sent(pespconn, "[ZZZ01]\r\n", strlen("[ZZZ01]\r\n"));//����������
			}
			if(switch_on == 0)//����״̬Ϊ��
			{
				espconn_sent(pespconn, "[ZZZ02]\r\n", strlen("[ZZZ02]\r\n"));//����������
			}
		}

		//8266��������������ʱ����
		if(pdata[0]=='{' && pdata[1]=='T' && pdata[2]=='M' && pdata[3]=='}')
		{
			int k=0;
			for(k=0; k<8; k++)
			{
				spi_flash_read(0x3C*4096+24*k, (uint32 *)(DMdata), 24);
				os_memcpy(timer[k].TMdata, DMdata, 24);
				timer[k].TMdata[0] = '[';//������������������'['��ͷ,']'��β
				timer[k].TMdata[23] = ']';
				espconn_sent(pespconn, timer[k].TMdata, 24);
				espconn_sent(pespconn, "\r\n", strlen("\r\n"));
				timer[k].TMdata[0] = '{';//���»ָ�����
				timer[k].TMdata[23] = '}';
				os_delay_us(1000);//��ʱ1ms
			}
		}

		//���ܲ�����ʱ���ܽ�������
		if(pdata[1] == 'S' || pdata[1] == 'R')
		{
			int a;
			TM_ID = (uint8)((pdata[21]-'0')*10+(pdata[22]-'0'));//��ȡ��ʱ�û�ID
			os_printf("%d\n", TM_ID);
			//д���Ƿ��ظ���ʱ��־λ
			if(pdata[1] == 'R')
				timer_repeat[TM_ID] = 1;
			else if(pdata[1] == 'S')
				timer_repeat[TM_ID] = 0;
			else
				timer_repeat[TM_ID] = 0;

			//д�붨ʱ���ر�־λ
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

			os_memcpy(timer[TM_ID].TMdata, pdata, 24);//���յ������ݴ���TMdata��
			os_memcpy(DMdata, timer[TM_ID].TMdata, 24);
			//spi_flash�����Ȳ��������ݲ���д��������,so�Ȳ�����������
			spi_flash_erase_sector(0x3C);
			//д���������
			spi_flash_write(0x3C*4096+24*TM_ID, (uint32 *)(DMdata), 24);
			//��δ���µ���������д��
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

		//���ܲ�������ʱ���ܽ�������
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

//�������ݳɹ���Ļص�����
void ICACHE_FLASH_ATTR user_tcp_sent_cb(void *arg)
{
	//os_printf("send_data_ok");
//	hw_timer_init(FRC1_SOURCE, 0);//Ӳ����ʱ����ʼ������������Ҫ�߾��ȶ�ʱ����ʹ�ã���ͨ����ʹ�������ʱ��
//	hw_timer_set_func(hw_test_timer_cb);//����Ӳ����ʱ���ص�����
//	hw_timer_arm(1000000);//��ʱʱ��1S����λʱ����1us
}

//�Ͽ�TCP���ӵĻص�����
void ICACHE_FLASH_ATTR user_tcp_discon_cb(void *arg)
{
	if(restart_flag == 0)
	{
		status = wifi_station_get_connect_status();

		//�������ϣ�WiFiδ��
		if(status == STATION_GOT_IP)
		{
			os_delay_us(1000000);
			//��������TCPserver
			espconn_connect((struct espconn *)arg);
		}
		//��������WiFi����
		else
		{
			GPIO_OUTPUT_SET(GPIO_ID_PIN(4), 1);//ָʾ����
		}
	}
}

//TCP���ӳɹ���Ļص�����
void ICACHE_FLASH_ATTR user_tcp_connect_cb(void *arg)
{
	uint8 g=0;
	//��ȡflash�е����ݴ���TMdata��
	for(g=0; g<8; g++)
	{
		spi_flash_read(0x3C*4096+24*g, (uint32 *)(DMdata), 24);
		os_memcpy(timer[g].TMdata, DMdata, 24);
		os_printf("%s ",timer[g].TMdata);

		//��ȡ�Ƿ��ظ���ʱ��־λ
		if(timer[g].TMdata[1] == 'R')
			timer_repeat[g] = 1;
		else if(timer[g].TMdata[1] == 'S')
			timer_repeat[g] = 0;
		else
			timer_repeat[g] = 0;
		//��ȡ��ʱ���ر�־λ
		if(timer[g].TMdata[2] == 'K')
			timer_flag[g] = 1;
		else if(timer[g].TMdata[2] == 'G')
			timer_flag[g] = 0;
		else
			timer_flag[g] = 0;
		//�ж�һ�ܶ�ʱƵ��
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
	GPIO_OUTPUT_SET(GPIO_ID_PIN(4), 1);//ָʾ����
	pespconn = arg;
	//ע��������ݵĻص�����
	espconn_regist_recvcb(pespconn, user_tcp_recv_cb);
	//ע�ᷢ�����ݳɹ��Ļص�����
	espconn_regist_sentcb(pespconn, user_tcp_sent_cb);
	//ע��Ͽ����ӵĻص�����
	espconn_regist_disconcb(pespconn, user_tcp_discon_cb);

	//����WiFiģ��MAC��ַ
	os_delay_us(300);//��ʱ300us
	espconn_sent(pespconn, macaddr1, strlen(macaddr1));
	os_printf("%s\n",macaddr1);

	//ע�������ʱ�������������������ܲ�����ʱ���ܡ����ܲ�������ʱ����
	os_timer_disarm(&heartbeat_timer);//�رն�ʱ��
	os_timer_setfn(&heartbeat_timer,heatbeat_cb,NULL);//���ö�ʱ���ص�����Wifi_connect
	os_timer_arm(&heartbeat_timer,2000,NULL);//�����ʱ��ʱ2s�����Զ���װ
}

//TCP����ʧ�ܺ������Ļص�����
//wifi���Ӻͷ��������Ӿ�ʧ��ָʾ����
//����������ʧ��ָʾ����˸
void ICACHE_FLASH_ATTR user_tcp_recon_cb(void *arg, sint8 err)
{
	if(restart_flag == 0)
	{
			status = wifi_station_get_connect_status();
			//�������ϣ�WiFiδ��
			if(status == STATION_GOT_IP)
			{
				os_printf("���������ˣ�·����û��");
				//ָʾ����˸
				if(GPIO_INPUT_GET(4) == 0)
					GPIO_OUTPUT_SET(GPIO_ID_PIN(4), 1);
				else
					GPIO_OUTPUT_SET(GPIO_ID_PIN(4), 0);
				//os_printf("���Ӵ��󣬴������Ϊ%d\r\n",err);
				os_delay_us(10000);
				//��������TCPserver
				espconn_connect((struct espconn *)arg);
				os_delay_us(10000);
			}
			//��������WiFi����
			else
			{
				os_printf("��������·����������\r\n");
				GPIO_OUTPUT_SET(GPIO_ID_PIN(4), 0);//ָʾ����
				wifi_discon_flag = 1;
				os_timer_disarm(&connect_timer);//�رն�ʱ��
				os_timer_arm(&connect_timer,1000,NULL);//ʹ��WiFi���Ӷ�ʱ��
			}
			os_delay_us(500000);
	}
}

//TCP���Ӻ���
void ICACHE_FLASH_ATTR my_station_init(struct ip_addr *remote_ip, struct ip_addr *local_ip, int remote_port)
{
	// espconn��������
	user_tcp_conn.type = ESPCONN_TCP;
	user_tcp_conn.state = ESPCONN_NONE;
	user_tcp_conn.proto.tcp = (esp_tcp *)os_zalloc(sizeof(esp_tcp));
	os_memcpy(user_tcp_conn.proto.tcp->local_ip, local_ip, 4);
	os_memcpy(user_tcp_conn.proto.tcp->remote_ip, remote_ip,4);
	user_tcp_conn.proto.tcp->local_port = espconn_port();
	user_tcp_conn.proto.tcp->remote_port = remote_port;

	//ע��TCP���ӳɹ���Ļص�����
	espconn_regist_connectcb(&user_tcp_conn, user_tcp_connect_cb);
	//ע��TCP���ӷ����쳣�Ͽ�ʱ�Ļص�������һ����������
	espconn_regist_reconcb(&user_tcp_conn, user_tcp_recon_cb);

	//��������TCPserver
	espconn_connect(&user_tcp_conn);//����TCPserver
}

