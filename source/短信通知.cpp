
/******************说明***********************/ 
//         P3^4---//打电话                 
//         P3^5---//接电话
//		   P3^6---//挂电话
//		   P3^3---//发英文短信

         
/*****************************************/
#include <stc12c5a.h>
#include <string.h>
#include "hardware.h"
#include "sms.h"
#include "sms.c"

sbit led1 = P1^0;
sbit led2 = P1^1;
sbit led3 = P1^2;
sbit led4 = P1^3;
sbit led5 = P1^4;
sbit led6 = P1^5;
sbit led7 = P1^6;
sbit led8 = P1^7;
uchar 	idata rbuff[110];						//串口接收数据缓存区
uchar   numbuff[]="18392567656";  				//此处修改为需要接收短信的手机号码,注意要定义为字符串（\0）
uchar  	databuff[]="000000"; 					//数据缓存区,注意要定义为字符串（\0）
uchar	rcount;									//串口接收数据指针
				 
bit		tc35_init_ok;							//注册成功初始化完成标志
bit		receive_ok;								//收到模块“ok”标志
bit     send_error;
bit     send_ok;

void initUart(void)					  			   
{	 //	RXD=1;
	//TXD=1;

 	TMOD=0x20;									//T1工作方式2,8位自动重装
 	SCON=0x40;									//串行口工作方式1，8位UTRA
 	TH1=0xfd;
 	TL1=0xfd;									//波特率发生器，波特率为4800
 	REN=1;	  									//允许串行接收
 	TR1=1;										//开波特率发生器T1
 	ES=1;										//开串行口中断
 	EA=1;										//开总中断
//	R=1;
//	T=1;
}



void RECEIVE_DATA(void) interrupt 4	  			//接收tC35发送的数据并缓存
{ 
	ES=0;
	if(RI)
   	{
		rbuff[rcount++]=SBUF;
    	RI=0;
	}
  	//判断是否接收完毕
  	if((rbuff[rcount-1]==0x0a)&&(rbuff[rcount-2]==0x0d)&&(rbuff[rcount-3]==0x4b)&&(rbuff[rcount-4]==0x4f))
	{					//换行					 //回车						
		receive_ok=1;
	}
	//判断是否为新短消息指示	  
  	if((rbuff[rcount-14]=='C')&&(rbuff[rcount-13]=='M')&&(rbuff[rcount-12]=='T')&&(rbuff[rcount-11]=='I'))
    {							                                                           							 	     //换行
		new_sms=1;
	}
	else  new_sms=0;

  	if(((rbuff[rcount-17]=='C')&&(rbuff[rcount-16]=='M')&&(rbuff[rcount-15]=='G')&&(rbuff[rcount-14]=='S')&&(rbuff[rcount-4]==0x4f)&&(rbuff[rcount-3]==0x4b)&&(rbuff[rcount-2]==0x0d)&&(rbuff[rcount-1]==0x0a))|((rbuff[rcount-16]=='C')&&(rbuff[rcount-15]=='M')&&(rbuff[rcount-14]=='G')&&(rbuff[rcount-13]=='S')&&(rbuff[rcount-4]==0x4f)&&(rbuff[rcount-3]==0x4b)&&(rbuff[rcount-2]==0x0d)&&(rbuff[rcount-1]==0x0a)))
    {							                                                           							 	     //换行
		send_ok=1;

	}
	else  send_ok=0;
  	if((rbuff[rcount-7]=='E')&&(rbuff[rcount-6]=='R')&&(rbuff[rcount-5]=='R')&&(rbuff[rcount-4]=='O')&&(rbuff[rcount-3]=='R'))
    {							                                                           							 	     //换行
		send_error=1;
	}
	else  send_error=0;

	if(rcount>109)rcount=0;
	ES=1; 
}




uchar KeyScan()	//带返回值的子函数
{
	uchar cord_l,cord_h;//声明列线和行线的值的储存变量
	P0 = 0x0f;//0000 1111
	if( (P0 & 0x0f) != 0x0f)//判断是否有按键按下
	{
		delay(5);//软件消抖
		if( (P0 & 0x0f) != 0x0f)//判断是否有按键按下
		{
			  cord_h = P0 & 0x0f;// 储存行线值
			  P0 =  0xf0;
			  cord_l = P0 & 0xf0;// 储存列线值
			  while( (P0 & 0xf0) != 0xf0 );//松手检测
			  return (cord_l + cord_h);//返回键值码
		}	
	}
	return (cord_l + cord_h);//返回键值码	
}

void KeyPro()
{	  
	switch( KeyScan() )
	{
	 	//第四行键值码
		
		case 0xee: led1=0;Sendsms("need maintenance\r\n");		break;
		case 0xde: 		Sendsms("loushui\r\n");	break;	//发送英文短信;		
		case 0xbe: led3=0;		break;
		case 0x7e: led4=0;		break;
		
		//第三行键值码
		case 0xed: led5=0;		break;
		case 0xdd: led6=0;		break;
		case 0xbd: led7=0;		break;
		case 0x7d: led8=0;		break;

		//第二行键值码
		case 0xeb: led1=0;		break;
		case 0xdb: led1=0;		break;
		case 0xbb: led1=0;	break;
		case 0x7b: led1=0;	break;

		//第一行键值码
		case 0xe7:	 P1 = 0xff ;break;	   //
		case 0xd7: ;	break;
		case 0xb7: ;	break;
		case 0x77: ;	break;

	}	
}
void main(void)		
{
	uchar  times=0;				 
	uchar m=0;
	tc35_init_ok=0;

	initUart();	  								//初始化串口
	Init_tc35();								//初始化模块
	delay(5000);
	delay(5000);
	delay(5000);
	delay(5000);
 	while(tc35_init_ok==0)  					//初始化
 	{		
		Init_tc35();
		delay(4000);
		times++;
		if(times>15)
		{	
			times=0;
			delay(1000);					
			delay(500);
			delay(1000);
			delay(4000);delay(4000);delay(4000);
		}
	}
	if(tc35_init_ok)
	{		  
		LED=0;									   //初始化成功鸣叫一声
		delay(2000);
		LED=1;
		delay(2000);
		LED=0;
	}	
			   						
 	while(1)	   					
 	{
	
		KeyPro();

	

  	}		    			
 
}

