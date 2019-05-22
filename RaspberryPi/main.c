// ATmega32a

#define F_CPU 1000000
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define FOSC F_CPU // Clock Speed
#define BAUD 4800
#define MYUBRR FOSC / 16 / BAUD - 1

//GIZMOSNACK DEFINES STARTS //
#define BIT(x) (1 << (x))
#define SETBITS(x, y) ((x) |= (y))
#define CLEARBITS(x, y) ((x) &= (~(y)))
#define SETBIT(x, y) SETBITS((x), (BIT((y))))
#define CLEARBIT(x, y) CLEARBITS((x), (BIT((y))))
//GIZMOSNACK DEFINES ENDS //

void blink(void)
{
    SETBIT(PORTD, 5);
    _delay_ms(100);
    CLEARBIT(PORTD, 5);
}
void USART_Init(unsigned int ubrr)
{
    /*Set baud rate */
    UBRRH = (unsigned char)(ubrr >> 8);
    UBRRL = (unsigned char)ubrr;
    UCSRB = (1 << RXEN) | (1 << TXEN);
    /* Set frame format: 8data, 2stop bit */
    UCSRC = (1 << URSEL) | (1 << USBS) | (3 << UCSZ0);
}
unsigned char USART_Receive(void)
{
    /* Wait for data to be received */
    while (!(UCSRA & (1 << RXC)))
        ;
    /* Get and return received data from buffer */
    return UDR;
}
void USART_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSRA & (1 << UDRE)))
        ;
    /* Put data into buffer, sends the data */
    UDR = data;
}
void ADC_Init(void)
{
    DDRC = 0x00;
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}
int ADC_Read(uint8_t ch)
{
    ch &= 0b00000111;
    ADMUX = (ADMUX & 0xF8) | ch;
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC))
        ;
    return ADC;
}
void SPI_SlaveInit(void)
{

    /* Set MISO output, all others input */
    DDRB = (0 << PB4) | (1 << PB6);
    /* Enable SPI */
    SPCR = (1 << SPE);
}
char SPI_SlaveReceive(void)
{
    /* Wait for reception complete */
    while (!(SPSR & (1 << SPIF)))
        ;
    /* Return data register */
    return SPDR;
}
void SPI_Transmit(char cData)
{
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while (!(SPSR & (1 << SPIF)))
        ;
}
int main(void)
{
    DDRD = (1 << 5);
    blink();
    USART_Init(MYUBRR);
    //SPI_SlaveInit();
    ADC_Init();
    while (1)
    {
        char input[2];
        input[0] = USART_Receive();
        //input[0] = SPI_SlaveReceive();
        input[1] = '\0';
        int channel = atoi(input);
        //USART_Transmit(channel);
        uint16_t adc_value = ADC_Read(channel);
        //USART_Transmit(adc_value);
        //USART_Transmit(adc_value);
        //char buffer[5];
        //itoa(adc_value, buffer, 5);

        // int i = 0;
        // for (i = 0; i < 5; i++)
        // {
        //     USART_Transmit(buffer[i]);
        // }
        USART_Transmit((uint8_t)((adc_value >> 8) & 0xff));
        USART_Transmit((uint8_t)((adc_value)&0xff));
        //SPI_Transmit((char)((adc_value >> 8) & 0xff));
        //SPI_Transmit((char)((adc_value)&0xff));
        blink();
    }
}
