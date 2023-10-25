#define TEST_H

/**********************************
List struct
**********************************/
typedef struct date {
	unsigned int day;
	unsigned int month;
	unsigned int year;
} date_t;

typedef struct client {
    char clientName;
    char file;
    int age;
    int gender;
    date_t bithday;
} client_t;
