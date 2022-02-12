#include <stdio.h>
#include <stdint.h>

typedef union mem {
	uint8_t buf[7];

	struct {
		uint8_t sec;
		uint8_t min;
		uint8_t hour;
		uint8_t day;
		uint8_t date;
		uint8_t month;
		uint8_t year;
	};
}mem_t;

mem_t mem;

int getSec(uint8_t value);
int getMin(uint8_t value);
int getHour(uint8_t value);
char* getDay(uint8_t value);
int getMonth(uint8_t value);
int getDate(uint8_t value);
int getYear(uint8_t value);

int main(void)
{
	FILE *fp = fopen("christmas23", "rb");
	fread(mem.buf, 8, 1, fp);

	printf("Input :");
	for (int i = 0; i < 7; ++i)
	{
		printf("0x%02X ", mem.buf[i]);
	}
	printf("\n");

	printf("%d H : ", getHour(mem.hour));
	printf("%d M : ", getMin(mem.min));
	printf("%d S\n", getMin(mem.sec));

	printf("%d Y : ", getYear(mem.year));
	printf("%d M : ", getMonth(mem.month));
	printf("%d D\n", getDate(mem.date));

	printf("Day  : %s\n", getDay(mem.day));


	fclose(fp);
}

int getSec(uint8_t value)
{
	return ((value >> 4) & 0x7) * 10 + ((value) & 0xf);
}

int getMin(uint8_t value)
{
	return  ((value >> 4) & 0x7) * 10 + ((value) & 0xf);
}

int getHour(uint8_t value)
{
	// am/pm mode
	if (value & 0x40)
	{
		if (((value >> 4) & 0x2) == 2)
		{
			printf("PM ");
		}
		else {
			printf("AM ");
		}
		return ((value) & 0x10) * 10 + ((value) & 0xf);
	}
	if (!(value & 0x40))
	{
		return ((value >> 4) & 0x3) * 10 + ((value) & 0xf);
	}
}

char* getDay(uint8_t value)
{
	int day = (value & 0x3);
	if (day == 3) { return "Sunday"; }
	else if (day == 4) { return "Monday"; }
	else if (day == 5) { return "Thusday"; }
	else if (day == 6) { return "Wednsday"; }
	else if (day == 0) { return "Thursday"; }
	else if (day == 1) { return "Friday"; }
	else if (day == 2) { return "Saturday"; }
}

int getMonth(uint8_t value)
{
	return ((value >> 4) & 0x1) * 10 + ((value) & 0xF);
}

int getDate(uint8_t value)
{
	return ((value >> 4) & 0x3) * 10 + ((value) & 0xF);
}

int getYear(uint8_t value)
{
	return ((value >> 4) & 0xF) * 10 + ((value) & 0xF);
}
