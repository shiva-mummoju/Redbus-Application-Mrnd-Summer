#pragma once
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include<stdlib.h>
#include "dbUtils.h"



//
//struct tickets{
//	int tid;
//	int uid;
//	int bid;
//	char* date;
//	char* uname;
//	char* time;
//}**ticket_cache=NULL;

tickets** ticket_cache;

/*truct user{
	char* uid;
	char* password;
	char* name;
};*/
//
//struct bus{
//	int bid;
//	int price;
//	char* time;
//	char* service_name;
//	char* src;
//	char* dest;
//}**bus_cache=NULL;

bus** bus_cache ;

//struct seats{
//	int bid;
//	char* date;
//	char* seat_string;
//	char* availability;
//};


//struct Bus_response{
//	int length;
//	bus** bus_details;
//}*bus_response_server;

Bus_response* bus_response_server;

//struct Ticket_response{
//	int length;
//	tickets** ticket_details;
//};

int ticketCacheLen=0, busCacheLen=0;


// server API
int login_request(char *uname, char *password);
int register_request(char *name, char *uname, char *pass);
Bus_response* getBusesFromDatabase(char* src, char*  dest, char* date, int seats);
void load_all_the_cache();
Bus_response* get_buses(char* src, char* dest, char* date, int seats);
int book_ticket(int uid, int bid, char* date, int seats, int* seats_nos);
Ticket_response* get_tickets(int uid);
char* get_seats_server(int bid, char* date);
void close();
 




char* get_seats_server(int bid, char* date){
	return get_seats(bid, date);
}

int login_request(char *uname, char *password){
	return authenticate(uname, password);
}

int register_request(char *uname, char *pass){
	return registerUser( uname, pass);
}


void load_all_the_cache(){

	int i = 0;
	printf("\nloading ticket cache\n");
	ticket_cache = (tickets**)malloc(sizeof(tickets*)*255);
		for (i = 0; i < 255; i++){
			ticket_cache[i] = (tickets*)malloc(sizeof(tickets));
		}
		ticketCacheLen = 0;
		
		
	
		printf("\nloading bus cache\n");
		bus_cache = (bus**)malloc(sizeof(bus*) * 255);
		for (i = 0; i < 255; i++){
			bus_cache[i] = (bus*)malloc(sizeof(bus));
		}

		ticketCacheLen = 0;
		

}



void close(){
	flush();
}

Bus_response* get_buses(char* src, char* dest, char* date){
	
	int k;
	Bus_response* buses_response_to_be_send_to_frontend = (Bus_response*)malloc(sizeof(Bus_response));
	buses_response_to_be_send_to_frontend->bus_details = (bus**)malloc(sizeof(bus*) * 255);
	for (k = 0; k < 255; k++){
		buses_response_to_be_send_to_frontend->bus_details[k] = (bus*)malloc(sizeof(bus));
	}

	buses_response_to_be_send_to_frontend->length = 0;

	int hit = 0;
	int i;

	if (busCacheLen == 0){
		//loadbuscache
		bus_response_server = getAvailableBuses(src, dest, date);
		//loading the immediately got buses into cache

		for (i = 0; i < bus_response_server->length; i++){
			bus_cache[busCacheLen]->bid = bus_response_server->bus_details[i]->bid;
			bus_cache[busCacheLen]->date = bus_response_server->bus_details[i]->date;
			bus_cache[busCacheLen]->destination = bus_response_server->bus_details[i]->destination;
			bus_cache[busCacheLen]->price = bus_response_server->bus_details[i]->price;
			bus_cache[busCacheLen]->source = bus_response_server->bus_details[i]->source;
			bus_cache[busCacheLen]->time = bus_response_server->bus_details[i]->time;
			bus_cache[busCacheLen]->type = bus_response_server->bus_details[i]->type;
			busCacheLen++;
			
		}

		return bus_response_server;
	}
	else{
		//parse the bus cache for hit

		hit = 0;

		for (i = 0; i < busCacheLen; i++){
			if (!strcmp(bus_cache[i]->source , src) && !strcmp(bus_cache[i]->destination , dest)){
				hit = 1;
				buses_response_to_be_send_to_frontend->bus_details[(buses_response_to_be_send_to_frontend->length)]->bid = bus_cache[i]->bid;
				buses_response_to_be_send_to_frontend->bus_details[(buses_response_to_be_send_to_frontend->length)]->date = bus_cache[i]->date;
				buses_response_to_be_send_to_frontend->bus_details[(buses_response_to_be_send_to_frontend->length)]->destination = bus_cache[i]->destination;
				buses_response_to_be_send_to_frontend->bus_details[(buses_response_to_be_send_to_frontend->length)]->price = bus_cache[i]->price;
				buses_response_to_be_send_to_frontend->bus_details[(buses_response_to_be_send_to_frontend->length)]->source = bus_cache[i]->source;
				buses_response_to_be_send_to_frontend->bus_details[(buses_response_to_be_send_to_frontend->length)]->time = bus_cache[i]->time;
				buses_response_to_be_send_to_frontend->bus_details[(buses_response_to_be_send_to_frontend->length)]->type = bus_cache[i]->type;
				buses_response_to_be_send_to_frontend->length++;
			}
		}

		if (hit == 0){
			//cache miss

			bus_response_server = getAvailableBuses(src, dest, date);

			if (busCacheLen + bus_response_server->length > 255){
				busCacheLen = 0;
			}

			for (i = 0; i < bus_response_server->length && busCacheLen< 255; i++){
				bus_cache[busCacheLen]->bid = bus_response_server->bus_details[i]->bid;
				bus_cache[busCacheLen]->date = bus_response_server->bus_details[i]->date;
				bus_cache[busCacheLen]->destination = bus_response_server->bus_details[i]->destination;
				bus_cache[busCacheLen]->price = bus_response_server->bus_details[i]->price;
				bus_cache[busCacheLen]->source = bus_response_server->bus_details[i]->source;
				bus_cache[busCacheLen]->time = bus_response_server->bus_details[i]->time;
				bus_cache[busCacheLen]->type = bus_response_server->bus_details[i]->type;
				busCacheLen++;

			}

			return bus_response_server;

		}
		else{
			//cache hit
			return buses_response_to_be_send_to_frontend;
		}
		
	}
}



int book_ticket(int uid, int bid, char* date, int* seats, int seats_booked){
	int result_code_book_ticket = update_seats(uid,bid, date, seats, seats_booked);
	//printf("Result code: %d\n", result_code_book_ticket);
	//printf("cache len %d\n", ticketCacheLen);
	if (result_code_book_ticket > 0){
		if (ticketCacheLen >= 255){
			ticketCacheLen = 0;
		}
		printf("After printing recieved the code: %d\n",result_code_book_ticket);
		ticket_cache[ticketCacheLen]->bid = bid;
		ticket_cache[ticketCacheLen]->date = date;
		ticket_cache[ticketCacheLen]->tid = result_code_book_ticket;
		ticket_cache[ticketCacheLen]->uid = uid;
		ticket_cache[ticketCacheLen]->time = "time";
		ticket_cache[ticketCacheLen]->uname = "username";
		ticketCacheLen++;
		return 1;
	}
	else {
		return -1;
	}

}



Ticket_response* get_tickets(int uid){

	int i = 0;
	int count = 0;
	int hit = 0;
	Ticket_response* response = (Ticket_response*)malloc(sizeof(Ticket_response));

	if(ticketCacheLen == 0){
		printf("debug: ticket cache len fount to be 0\n");
		response = get_tickets_db(uid);
		for (i = 0; i < response->length && ticketCacheLen<255; i++){
			ticket_cache[ticketCacheLen]->bid = response->ticket_details[i]->bid;
			ticket_cache[ticketCacheLen]->date = response->ticket_details[i]->date;
			ticket_cache[ticketCacheLen]->tid = response->ticket_details[i]->tid;
			ticket_cache[ticketCacheLen]->time = response->ticket_details[i]->time;
			ticket_cache[ticketCacheLen]->uid = response->ticket_details[i]->uid;
			ticket_cache[ticketCacheLen]->uname = response->ticket_details[i]->uname;
			ticketCacheLen++;
			
		}
		
		
		return response;
	}

	tickets** tickets_to_be_sent = (tickets**)malloc(sizeof(tickets*) * 255);
	for (i = 0; i < 255; i++){
		tickets_to_be_sent[i] = (tickets*)malloc(sizeof(tickets));
	}

	for (i = 0; i < ticketCacheLen; i++){
		if (ticket_cache[i]->uid ==  uid){
			hit = 1;
			tickets_to_be_sent[count]->bid = ticket_cache[i]->bid;
			tickets_to_be_sent[count]->date = ticket_cache[i]->date;
			tickets_to_be_sent[count]->tid = ticket_cache[i]->tid;
			tickets_to_be_sent[count]->time = ticket_cache[i]->time;
			tickets_to_be_sent[count]->uid = ticket_cache[i]->uid;
			tickets_to_be_sent[count]->uname = ticket_cache[i]->uname;
			count = count + 1;
		}
	}


	if (hit == 1){
		printf("\nticket cache hit\n");
		response->length = count;
		response->ticket_details = tickets_to_be_sent;

	}
	else{
		printf("\nticket cache miss\n");
		response = get_tickets_db(uid);
		if (ticketCacheLen + response->length >= 255){
			ticketCacheLen == 0;
		}
		for (i = 0; i < response->length; i++){
			ticket_cache[ticketCacheLen]->bid = response->ticket_details[i]->bid;
			ticket_cache[ticketCacheLen]->date = response->ticket_details[i]->date;
			ticket_cache[ticketCacheLen]->tid = response->ticket_details[i]->tid;
			ticket_cache[ticketCacheLen]->time = response->ticket_details[i]->time;
			ticket_cache[ticketCacheLen]->uid = response->ticket_details[i]->uid;
			ticket_cache[ticketCacheLen]->uname = response->ticket_details[i]->uname;
			ticketCacheLen++;
		}	
	}
	return response;

	
}







