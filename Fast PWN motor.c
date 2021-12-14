#include <avr/io.h>
#include <avr/interrupt.h>

void main(void)
{
	PORTB = 0x20; // 0x?0 --> ? X, enable(0: enable, 1: disable), dir(0: 역방향 ,1: 정방향), pwm2
	DDRB  = 0xFF; //output 0C0(PB4)

	PORTF = 0x00;
	DDRF = 0x00; // 속도 조절

	TCNT0 = 0x00; 
	OCR0 = 0x00; //값 증가시 duty cycle 증가, 값 감소시 duty cycle 감소
	TCCR0 = 0x6C; //0110, 1100 --> Fast PWM, non-inverting mode, presacler:64 

	sei(); // global interrupt 허용
	
	while(1)
	{
		//OCR0 값 증가시 duty cycle 커져서 속도가 빨라짐
		//OCR0 값 감소시 duty cycle 작아져서 속도가 느려짐
		if(PINF & 0x01) // 0번 버튼 누르면
		{
			OCR0 = 0; // 모터에 low만 인가돼서 모터 회전 안함
		}
		else if(PINF & 0x02) // 1번 버튼 
		{
			OCR0 = 150;
		}
		else if(PINF & 0x04)  // 2번 버튼
		{
			OCR0 = 180;
		}
		else if(PINF & 0x08) // 3번 버튼
		{
			OCR0 = 210;
		}
		else if(PINF & 0x10) // 4번
		{
			OCR0 = 250;
		}
		else if(PINF & 0x20) // 5번
			{	
				if(PORTB & 0x20) //정방향(1) -> 역방향(0)
				{
					PORTB = PORTB & 0xDF; // 1101, 1111
				}
				else // 역방향(0) -> 정방향(1)
				{
					PORTB = PORTB | 0x20; 
				}
			}		
	}	
} 
