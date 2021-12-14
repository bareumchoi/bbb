#include <avr/io.h>
#include <avr/interrupt.h>

void main(void)
{
	PORTB = 0x20; // 0x?0 --> ? X, enable(0: enable, 1: disable), dir(0: ������ ,1: ������), pwm2
	DDRB  = 0xFF; //output 0C0(PB4)

	PORTF = 0x00;
	DDRF = 0x00; // �ӵ� ����

	TCNT0 = 0x00; 
	OCR0 = 0x00; //�� ������ duty cycle ����, �� ���ҽ� duty cycle ����
	TCCR0 = 0x6C; //0110, 1100 --> Fast PWM, non-inverting mode, presacler:64 

	sei(); // global interrupt ���
	
	while(1)
	{
		//OCR0 �� ������ duty cycle Ŀ���� �ӵ��� ������
		//OCR0 �� ���ҽ� duty cycle �۾����� �ӵ��� ������
		if(PINF & 0x01) // 0�� ��ư ������
		{
			OCR0 = 0; // ���Ϳ� low�� �ΰ��ż� ���� ȸ�� ����
		}
		else if(PINF & 0x02) // 1�� ��ư 
		{
			OCR0 = 150;
		}
		else if(PINF & 0x04)  // 2�� ��ư
		{
			OCR0 = 180;
		}
		else if(PINF & 0x08) // 3�� ��ư
		{
			OCR0 = 210;
		}
		else if(PINF & 0x10) // 4��
		{
			OCR0 = 250;
		}
		else if(PINF & 0x20) // 5��
			{	
				if(PORTB & 0x20) //������(1) -> ������(0)
				{
					PORTB = PORTB & 0xDF; // 1101, 1111
				}
				else // ������(0) -> ������(1)
				{
					PORTB = PORTB | 0x20; 
				}
			}		
	}	
} 
