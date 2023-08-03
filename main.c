/*
 * simple_project.c
 *
 * Created: 6/30/2023 4:52:49 PM
 * Author : Abderrahmane Lahouasna
 */
#define  F_CPU   8000000UL
 
#define  ADCLH  *((volatile unsigned int*)0x24) 
#include <avr/io.h>
void ADC_int(void);
void ADC_Start_Conversion(void);
unsigned int ADC_Get_Result(void);

int main(void)
{
	float value_adc,voltage,value;
	unsigned char temp []={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
		                  0x08,0x09,0x10,0x11,0x12,0x13,0x14,0x15,
						  0x16,0x17,0x18,0x19,0x20,0x21,0x22,0x23,
						  0x24,0x25,0x26,0x27,0x28,0x29,0x30,0x31,
						  0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,
						  0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,
						  0x48,0x49,0x50,0x51,0x52,0x53,0x54,0x55,
						  0x56,0x57,0x58,0x59,0x60,0x61,0x62,0x63,
						  0x64,0x65,0x66,0x67,0x68,0x69,0x70,0x71,
						  0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,
						  0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,
						  0x88,0x89,0x90,0x91,0x92,0x93,0x94,0x95,
						  0x96,0x97,0x98,0x99};
	// selections 
    /* Replace with your application code */
	DDRA =0x00;
	DDRC =0xFF;
	PORTC=0x00;
	DDRD=0xFF;
	PORTD=0x00;
	ADC_int();
	
    while (1) 
    {
			ADC_Start_Conversion();
		value_adc=ADC_Get_Result();
		voltage=(1.5*value_adc)/1023;
		value=voltage*100;
		PORTC=temp[(int)value];
		if(value>30){
			PORTD=0x03;
			
		}
		else if(value<=25&&value>=24){
			PORTD=0x04;
		}
		else if(value<20) 
		{
			PORTD=0X18;
		}
		
		
}
	}
void ADC_int(void)
{
	/************* voltage reference selection********************/
	         
	ADMUX |=(1<<REFS0);// REFS0 =0
	ADMUX &=~(1<<REFS1);// REFS1 =0
	/*************************************************************/
	/**************Seletion ADC Mode******************************/
	       ADCSRA |=(1<<ADATE);// Auto trigger enable
		 /*********Free Running*********************/
			SFIOR &=~(1<<ADTS0);// ADTS0 =0
			SFIOR &=~(1<<ADTS1);// ADTS1 =0
			SFIOR &=~(1<<ADTS2);// ADTS2 =0
	/*************************************************************/
	/********************clock ADC********************************/
	    /****************division by 128**********************/
		ADCSRA |=(1<<ADPS0);
		ADCSRA |=(1<<ADPS1);
		ADCSRA |=(1<<ADPS2);
		
	/*********************Selection Adjustement*******************/
	          /***************Right Adjustement*******************/
	             ADMUX &=~(1<<ADLAR);
	/*************************************************************/
	/*********************Clearing interrupt flag*****************/
	           ADCSRA |=(1<<ADIF);
	/*************************************************************/
	/********************Enabling ADC*****************************/
	             ADCSRA |=(1<<ADEN);
	/*************************************************************/
	
	
}
void ADC_Start_Conversion(void)
{
	/***************************seletion channels*********************/
	     /********************channel_0*******************************/
	ADMUX &=~(1<<MUX0);//MUX0=0
	ADMUX &=~(1<<MUX1);//MUX1=0
	ADMUX &=~(1<<MUX2);//MUX2=0
	ADMUX &=~(1<<MUX3);//MUX3=0
	ADMUX &=~(1<<MUX4);//MUX4=0
	/**********************************Start conversion***************/
	    ADCSRA |=(1<<ADSC);
}
volatile unsigned int ADC_Get_Result(void)
{
	return (ADCL |(ADCH<<8));
}