
#include <stdarg.h>

#define UTRSTAT2	*((volatile unsigned int *) 0xE2900810)
#define UTXH2		*((volatile unsigned int *) 0xE2900820)
#define URXH2		*((volatile unsigned int *) 0xE2900824)

typedef enum
{
	SMALL = 0,
	BIG
}ENUM_SB;

void send_byte(unsigned char byte)
{
	while (!(UTRSTAT2 & (0x1 << 2)));
	
	UTXH2 = byte;
}

unsigned char recv_byte(void)
{
	while (!(UTRSTAT2 & 0x1));
	
	return URXH2 & 0xFF;
}

void putchar(unsigned char c)
{
	send_byte(c);
	
	if (c == '\n')
	{
		send_byte('\r');
	}
}

unsigned char getchar(void)
{
	return recv_byte();
}


void puts(char * str)
{
	char * p = str;
	while (*p)
		putchar(*p++);
	putchar('\n');
}

void putint(int num)
{
	char a[20] = {0};
	int cnt = 0;
	char * intc = "0123456789";
	
	while (num > 0)
	{
		a[cnt++] = intc[num % 10];
		num /= 10;
	}
	
	while (cnt >= 0)
	{
		putchar(a[cnt--]);
	}
}

void puthex(int num, ENUM_SB sb)
{
	char a[20] = {0};
	int cnt = 0;
	char * hexs = "0123456789abcdef";
	char * hexb = "0123456789ABCDEF";
	
	while (num > 0)
	{
		if (sb == SMALL)
			a[cnt++] = hexs[num % 16];
		else
			a[cnt++] = hexb[num % 16];
		num /= 16;
	}
	
	while (cnt >= 0)
	{
		putchar(a[cnt--]);
	}
}

void printf(const char * fmt, ...)
{
	va_list ap;
	char c;
	int num;
	char * str;
	
	va_start(ap, fmt);
	
	while (*fmt)
	{
		c = *fmt++;
		
		if (c == '%')
		{
			switch (*fmt++)
			{
			case 'c':
				c = (char)va_arg(ap, char);
				putchar(c);
				break;
			case 'd':
			case 'u':
				num = (int)va_arg(ap, int);
				putint(num);
				break;
			case 'x':
				num = (int)va_arg(ap, int);
				puthex(num, SMALL);
				break;
			case 'X':
				num = (int)va_arg(ap, int);
				puthex(num, BIG);
				break;
			case 's':
				str = (char *)va_arg(ap, char *);
				puts(str);
				break;
			default:
				break;
			}
		}
		else
		{
			putchar(c);
		}		
	}
}

void delay(unsigned int t)
{
	unsigned int t2 = 0xFFFF;
	while (t--)
		for (; t2; t2--);
}

int main(void)
{
	int i = 0;
	
	puts("Hello UART2");
	
	while (i++ < 100)
	{
		printf("%d    %X\n", i, i);
		delay(500000);
	}
		
	return 0;
}
