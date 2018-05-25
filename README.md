RED BUS APPLICATION DOCX

Overview:
	Specifications:
	•	User can register himself with the application.
	•	User can login and book/ view the tickets.
	•	User can view various buses available on a date and specified route.
	•	User can choose the seats and book them.

Layers of Operation:
	•	Client or UI Layer: The client or the user interacts through a user interface where he can choose options from a menu 		for various use cases like booking ticket, viewing booking history, etc.
	•	Server Layer: The client passes his request to the server where the request is processed via a communication with the 		database in DB layer. Responses for the requests after processing are again sent back to the client through this layer.
	•	DB Layer: The database layer consists of entire data that is essential for the working of application, like buses, 		availability, tickets booked, users, etc.

Calls in various layers:
	
	Client Layer:
	•	void login(): Used for logging into the application.
	•	void signup(): Used for registering a new user.
	•	bool validate_username(char *username): Used for validating the username before it is sent to the server.
	•	bool validate_password(char *password): Used for validating the password before it is sent to the server.
	•	void user_screen(int userid): Used for displaying the user menu.
	•	void view_history(int userid): Used for displaying the list of booked tickets of a user.
	•	void book_tickets(int userid): Used for booking ticket.
	•	void show_availability(int bid, char*date, char*available_seats, int userid, int no_of_seats): Used for getting the 		availability of seats in a bus.
	•	void payment_screen(int userid): Used to display the payment screen.

	Server Layer:
	•	int login_request(char* uname, char* password):  Takes the request from the client to login and authenticates the 		username and password.
	•	int register_request(char* name, char* uname,char* pass): Takes the username and password from the user and registers 		him as a new user..
	•	Bus_response* get_buses(char* src, char* dest, char* date, int seats): Returns the number of buses as well the bus 		details of the buses of a particular source, destination, date and number of seats.
	•	int book_ticket(int uid, int bid, char* date, int seats, int* seats_nos): Accepts the request from the user to book a 		particular seat of a particular bus and particular date.
	•	void load_all_the_cache(): Loads the cache in the server into the main memory.
	•	Ticket_response* get_tickets(int uid):  Returns the list of tickets the user has booked before.
	•	Char* get_seats_server(int bid, char* date): Returns the details regarding the seats availability and non availability 		of a particular bus at a particular date.
	DB Layer:
	•	void importData(): Used for importing the data from files, into the memory.
	•	void flush(): Used for exporting the data in the memory back to the files.
	•	struct Bus_response *getAvailableBuses(char *src, char *dest, char *date): Used for getting the details of the buses 		available for the given route on the given date.
	•	char *get_seats(int bid, char *date): Used for getting the seats that are available in a bus on the specified date.
	•	int authenticate(char *uname, char *pass): Used for authenticating the user details.
	•	int registerUser(char *username, char *password): Used for registering the user.
	•	int update_seats(int uid, int bid, char *date, int *seats, int numberofseatsbooked): Update the state of seats in the 		database after a booking request is processed.


TEAM DETAILS:
	TEAM NO.: 1
	
	UI LAYER:  
	1.	 Anand (BVRIT-N)
	2.	Priyatham (GVPE)
	3.	Saradhi (SRKR)
	
	SERVER LAYER:
	1.	Shiva (VCE)
	2.	Satya Sarika (BVRIT-N)
	3.	Aditya (GMRIT)

	DB LAYER:
	1.	Ujwal (SMEC)
	2.	Pallavi (CVR)
	3.	Supriya (SVECW)
	4.	Samudrudu (PEC)
