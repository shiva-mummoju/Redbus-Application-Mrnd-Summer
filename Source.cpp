#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include "serverUtils.h"
#include "clientUtil.h"
#include "dbUtils.h"


void test_bus_cache();
void test_ticket_cache();
void test_seat_booking();


int main(){

	importData();
	load_all_the_cache();
	int k = 0;

	main_screen();

	close();

	scanf("%d", &k);

	return 0;
}



void test_bus_cache(){
	int k = 0;
	

	Bus_response* printing;


	printing = getAvailableBuses("vijayawada", "hyderabad", "25/05/2018");

	for (k = 0; k < printing->length; k++){
		printf("%s\n", printing->bus_details[k]->destination);
	}

	printing = get_buses("vijayawada", "hyderabad", "25/05/2018");
	for (k = 0; k < printing->length; k++){
		printf("%s\n", printing->bus_details[k]->destination);
	}

	printf("Printing cache\n");
	for (k = 0; k < busCacheLen; k++){
		printf("%d\n", bus_cache[k]->bid);
	}

	printf("get buses hyderabd to vizag");
	printing = get_buses("hyderabad", "vizag", "25/05/2018");

	printf("Printing cache\n");
	for (k = 0; k < busCacheLen; k++){
		printf("%d\n", bus_cache[k]->bid);
	}

	printf("get buses hyderabd to vizag");
	printing = get_buses("hyderabad", "vizag", "25/05/2018");

	printf("Printing cache\n");
	for (k = 0; k < busCacheLen; k++){
		printf("%d\n", bus_cache[k]->bid);
	}

	printf("get buses vizag to kakinada\n");
	printing = get_buses("vizag", "kakinada", "28/05/2018");
	
	printf("Printing cache\n");
	for (k = 0; k < busCacheLen; k++){
		printf("%d\n", bus_cache[k]->bid);
	}

}



void test_ticket_cache(){
	int k = 0;

	Ticket_response* response = get_tickets_db(4);
	printf("\n getting ticket 4\n");
	for (k = 0; k < response->length; k++){
		printf("%s\n", response->ticket_details[k]->uname);
	}


	response = get_tickets(4);
	printf("printing ticket cache 4\n");
	for (k = 0; k < ticketCacheLen; k++){
		printf("%s\n", ticket_cache[k]->uname);
	}


	 response = get_tickets_db(10);
	printf("\n getting ticket from db 10\n");
	for (k = 0; k < response->length; k++){
		printf("%s\n", response->ticket_details[k]->uname);
	}


	response = get_tickets(10);

	printf("printing ticket cache\n");
	for (k = 0; k < ticketCacheLen; k++){
		printf("%s\n", ticket_cache[k]->uname);
	}


	response = get_tickets_db(10);
	printf("\n getting ticket from db 10\n");
	for (k = 0; k < response->length; k++){
		printf("%s\n", response->ticket_details[k]->uname);
	}


	response = get_tickets(10);

	printf("printing ticket cache\n");
	for (k = 0; k < ticketCacheLen; k++){
		printf("%s\n", ticket_cache[k]->uname);
	}

	 response = get_tickets_db(4);
	printf("\n getting ticket 4\n");
	for (k = 0; k < response->length; k++){
		printf("%s\n", response->ticket_details[k]->uname);
	}


	response = get_tickets(4);
	printf("printing ticket cache 4\n");
	for (k = 0; k < ticketCacheLen; k++){
		printf("%s\n", ticket_cache[k]->uname);
	}
}



void test_seat_booking(){

	int k = 0;

	printf("\nbefore\n");
	for (k = 0; k < ticketCacheLen; k++){
		printf("%d", ticket_cache[k]->tid);
	}

	int a[1] = { 3 };
	book_ticket(1, 5, "24/05/2018", a, 1);

	printf("\nafter\n");
	for (k = 0; k < ticketCacheLen; k++){
		printf("%d", ticket_cache[k]->tid);
	}

	int b[1] = { 2 };
	book_ticket(1, 3, "25/05/2018", b, 1);

	printf("\nafter\n");
	for (k = 0; k < ticketCacheLen; k++){
		printf("%d", ticket_cache[k]->tid);
	}


}