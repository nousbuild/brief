#include <stc12c5a.h>
#include <intrins.h>
#include <zhuan.h>
#include <shengbo.h>
#define uchar unsigned char
#define uint unsigned int
uchar shuaxin ;

void Conut(uchar i)
	{
	 if (i == 1)
	 {
	 time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;
	 S1=(time*1.7)/100;}
//	 if (i == 2)
//	 {
//	 time=TH0*256+TL0;
//	 TH0=0;
//	 TL0=0;
//	 S2=(time*1.7)/100;}
//	 if (i == 3)
//	 {
//	 time=TH0*256+TL0;
//	 TH0=0;
//	 TL0=0;
//	 S3=(time*1.7)/100;}     
	}

	void txbo (uchar i)
 {	
 	  if (i == 1)
 	  {TX1=1;			               
	  _nop_();_nop_(); _nop_(); _nop_();
	  _nop_();_nop_(); _nop_(); _nop_();
	  _nop_();_nop_(); _nop_(); _nop_();
	  _nop_();_nop_(); _nop_(); _nop_();
	  _nop_();_nop_(); _nop_();_nop_();_nop_();
	  TX1=0;
	  }
//	  if (i == 2)
// 	  {TX2=1;			                
//	  _nop_();_nop_(); _nop_(); _nop_();
//	  _nop_();_nop_(); _nop_(); _nop_();
//	  _nop_();_nop_(); _nop_(); _nop_();
//	  _nop_();_nop_(); _nop_(); _nop_();
//	  _nop_();_nop_(); _nop_();_nop_();_nop_();
//	  TX2=0;
//	  }
//	  if (i == 3)
// 	  {TX3=1;			               
//	  _nop_();_nop_(); _nop_(); _nop_();
//	  _nop_();_nop_(); _nop_(); _nop_();
//	  _nop_();_nop_(); _nop_(); _nop_();
//	  _nop_();_nop_(); _nop_(); _nop_();
//	  _nop_();_nop_(); _nop_();_nop_();_nop_();
//	  TX3=0;
//	  }
 } 

 void cebo ()
 {
 	while(!RX1);		//当RX为零时等待
	 TR0=1;			    //开启计数
	 while(RX1);			//当RX为1计数并等待
	 TR0=0;				//关闭计数
	 Conut(1);


//	 while(!RX2);		//当RX为零时等待
//	 TR0=1;			    //开启计数
//	 while(RX2);			//当RX为1计数并等待
//	 TR0=0;				//关闭计数
//	 Conut(2);
//
//	 
//	 while(!RX3);		//当RX为零时等待
//	 TR0=1;			    //开启计数
//	 while(RX3);			//当RX为1计数并等待
//	 TR0=0;					//关闭计数
//	 Conut(3);				//计算
 } 

 void zhongduan()
 {		  
 		 timer++; 
		 if(timer>=6)
		 { 
		  timer=0;
		  
		   
		 }
	 if(timer == 5)
	 {
	 	txbo (1);
	 }
//	 if(timer == 10)
//	 {
////	 	txbo (2);
//	 }
//	 if(timer == 15)
//	 {
////	 	txbo (3);
//	 }
	
 }
