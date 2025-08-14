#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

typedef struct Login//Used for finding password and username
{
	char username[20];
	char password[20];
}Login;

typedef struct Passenger//Declaring everything that will be used and saved for Passengers for if they need to be called up
{
	int pps;
	char firstName[20];
	char surname[20];
	int birthYear;
	char email[50];
	int area;
	int travelClass;
	int tripNum;
}Passenger;

bool FileExists(const char* filename);//Checking if the file exists

int Logging_In(Login user);//Making login file with all the passwords/username

void LoginFile();//File used 
void PassengerFile();//Setting up passenger file if needed


Passenger GetPassengerInfo();//Inputting user info by user
Passenger ShowAllPassenger();//Showing all passengers to user
Passenger ShowOnePassengerInfo(const char* username);//Making it to show a specific passenger
Passenger ChangeStats(const char* username);
Passenger Delete();




int main()
{

	//Checking if login file exists
	if (!FileExists("login.txt")) 
	{
		LoginFile();
	}
	if (!FileExists("passenger.txt"))
	{ 
		PassengerFile(); 
	}

	int count = 0;
	bool checker = true;//Used to make sure user doesn't make a incorrect decision
	Login user;//This is how user will input new data

	while (checker)
	{


		printf("Login \n\n\n ----------------- \n USERNAME\n ");
		scanf("%s", &user.username);
		printf(" ----------------- \n PASSWORD\n ");
		scanf("%s", &user.password);

		if (Logging_In(user)) //Making sure user put in right loggin
		{
			printf("Login successful!\n");
			checker = false;//If correct loop will end
		}
		else 
		{
			printf("Login failed \nIncorrect username or password.\n");//Will keep user in loop until correct username/password
		}
	}

	printf("Hello %s\n\n", user.username);
	printf("welcome to travelers mangement\n\n\n");


	int choice = 0;
	while (choice != -1)//Ends when choice is -1
	{
		printf("\n--------------------------------------\n");
		printf("would you like to \n");
		printf("1. Add a passenger to list\n");
		printf("2. Display all passengers\n");
		printf("3. Display passenger details\n");
		printf("4. Update passenger statistics\n");
		printf("5. Delete passenger\n");
		printf("6. Show statistics\n");
		printf("7. Print to reports file\n");
		printf("8. Display all passengers by date of birth\n");
		printf("-1. End protocol\n");
		scanf_s("%d", &choice);

		switch (choice)//Asking all questions for user this will be main thing utilised by them
		{

		case 1:
			GetPassengerInfo();
			break;
		case 2:
			ShowAllPassenger();
			break;
		case 3:
			ShowOnePassengerInfo(user.username);
			break;
		case 4:
			ChangeStats(user.username);
			break;
		case 5:
			Delete();
			break;
		case -1:
			printf("\n\nEnding protocol\n");
			break;

		default:

			printf("\n\n Invalid input try again \n");
			break;//Making sure if user inputs incorrect input it will continue
		}
	}
}


//Ensuring the file is here if needed
bool FileExists(const char* filename) {
	struct stat buffer;
	return (stat(filename, &buffer) == 0);
}


//setting up my login file if needed
void LoginFile()
{
	FILE* fp = fopen("login.txt", "w");//Writing into the login file to add stuff

	if (fp == NULL) {
		printf("Error opening file!\n");//Closing if error occurs

		return 0;
	}
	else
	{
		//Usernames and passwords
		fprintf(fp, "Owner OwnerP\n");
		fprintf(fp, "Manager ManagerP\n");
		fprintf(fp, "Employee EmployeeP\n");
	}
	fclose(fp);
	return;

}

void PassengerFile()
{
	FILE* fp = fopen("passenger.txt", "w");//Writing into the login file to add stuff

	if (fp == NULL) {
		printf("Error opening file!\n");//Closing if error occurs

		return 0;
	}
	fclose(fp);
	return;

}

//Checking if user is logged in correctly
int Logging_In(Login user)
{
	FILE* fp = fopen("login.txt", "r");//Reading login file to check


	if (fp == NULL)
	{
		printf("Error opening file!\n");

		return 0;
	}
	else
	{
		char storedUsername[20], storedPassword[20];

		//Checking if both username and password are correct
		while (fscanf(fp, "%s %s", storedUsername, storedPassword) != EOF)
		{
			if (strcmp(user.username, storedUsername) == 0 && strcmp(user.password, storedPassword) == 0)
			{
				fclose(fp);//file must be closed
				return true; //If username and password are correct it will close file and return true to let user pass
			}
		}

		fclose(fp);
		return false; //If not it will return false
	}
	fclose(fp);//Closing file in the end
	
}
	

Passenger GetPassengerInfo() 
{
	Passenger user;//This is to save user input

	printf("\n\nNow adding a passenger\n ");
	
	

		bool checker = true;//This is to make sure it resets if false answer is input


		int tempPPS = 0;

		do {
			checker = false;  

			char checkingPPS[250];
			int ppsCheck;

			//Finding users pps and making sure it is valid
			printf("What is their PPS number: ");
			scanf("%d", &tempPPS);

			//reading file to make sure pps is not already in use
			FILE* fp = fopen("Passenger.txt", "r");
			if (fp == NULL)
			{
				perror("Error opening file");
				return;
			}


			if (fp != NULL) 
			{
				//Making sure user must input a valid pps
				while (fgets(checkingPPS, sizeof(checkingPPS), fp)) 
				{
					sscanf(checkingPPS, "%d,", &ppsCheck);
					if (tempPPS == ppsCheck) {
						printf("PPS already in use. Please try again.\n");
						checker = true; 
						break;
					}
				}
				fclose(fp);
			}

		} while (checker == true);

		user.pps = tempPPS;//if pps is valid input it as a proper pps

		//appending so file doesn't erase other ones
		FILE* fp = fopen("Passenger.txt", "a");

		//Asking user name and surname
		printf("What is their first name: ");
		scanf("%s", user.firstName);

		printf("What is their surname: ");
		scanf("%s", user.surname);


		//Asking their birthyear
		printf("What year were they born: ");
		scanf_s("%d", &user.birthYear);


		//This sequence is to ensure user input a valid email with @ and .com
		do
		{
			checker = true;
			printf("Users Email address: ");
			scanf("%s", user.email);
			if (!strstr(user.email, ".com") || !strstr(user.email, "@"))
			{
				printf("Email must contain .com and a @\n");
				checker = false;
			}

		} while (checker == false);

		//Inputting as integer to ensure all answers are valid
		do
		{
			checker = true;
			printf("Where did user travel from \n");
			printf("1.Dublin \n");
			printf("2.Leinster \n");
			printf("3.Connaght \n");
			printf("4.Ulster \n");
			printf("5.Munster \n");
			scanf_s("%d", &user.area);
			if (user.area < 1 || user.area > 5)
			{
				printf("Invalid input must be between 1 and 5\n");
				checker = false;
			}


		} while (checker == false);

		//checking class with int since only 2 choices so for ease of use
		do
		{
			checker = true;
			printf("What class \n");
			printf("1.Economy \n");
			printf("2.First Class \n");
			scanf_s("%d", &user.travelClass);
			if (user.travelClass != 1 && user.travelClass != 2)
			{
				printf("Invalid input must be between 1 Economy and 2 first class\n");
				checker = false;
			}


		} while (checker == false);

		//Checking how many times they travelled
		do
		{
			checker = true;
			printf("How many times a year do they go?\n");
			printf("1.Less than three times a year \n");
			printf("2.Less than five times a year \n");
			printf("3.More than five times a year \n");
			scanf_s("%d", &user.tripNum);
			if (user.tripNum < 1 || user.tripNum >3)
			{
				printf("Invalid input must be between 1 and 3\n");
				checker = false;
			}


		}while (checker == false);

	//Once finished it reads passenger to file to be saved
	fprintf(fp, "%d %s %s %d %s %d %d %d\n", user.pps, user.firstName, user.surname, user.birthYear, user.email,user.area, user.travelClass, user.tripNum);
	printf("Process complete\n\n");

	fclose(fp);//closed
	

	return user;
}

//If user wishes to see all passengers this can easily read them all
Passenger ShowAllPassenger()
{
	printf("\n\nNow Displaying all passengers\n\n\n");

	FILE* fp = fopen("Passenger.txt", "r");
	if (fp == NULL)
	{
		perror("Error opening Passenger.txt");
		return;
	}

	//This is to make sure they are all called to filed
	int pps;
	char firstName[50];
	char surname[50];
	int birthYear;
	char email[50];
	int area;
	int travelClass;
	int tripNum;

	//This is to show name of their answer to questions
	char className[20];
	char location[20];
	char timesTravelled[40];

	printf("PASSENGER INFO\n");
	printf("______________\n\n");
	//loop to show all passengers
	while (fscanf(fp, "%d %s %s %d %s %d %d %d", &pps, firstName, surname, &birthYear, email, &area, &travelClass, &tripNum) == 8)
	{
		//Inputting the area travelClass and tripNum name to be shown based on their integer then to be read
		switch (area)
		{
		case 1:
			strcpy(location, "Dublin");
			break;

		case 2:
			strcpy(location, "Leinster");
			break;

		case 3:
			strcpy(location, "Connacht");
			break;

		case 4:
			strcpy(location, "Ulster");
			break;

		case 5:
			strcpy(location, "Munster");
			break;
		}



		if (travelClass == 1)
		{
			strcpy(className, "Economy");
		}
		else
		{
			strcpy(className, "First class");
		}

		switch (tripNum)
		{
		case 1:
			strcpy(timesTravelled, "Less than three times per year");
			break;

		case 2:
			strcpy(timesTravelled, "Less than five times per year");
			break;

		case 3:
			strcpy(timesTravelled, "More than five times per year");
			break;
		}



		//Reading all out to user in a easily read format
		printf("PPS: %d \n", pps);
		printf("Name: %s %s \n", firstName, surname);
		printf("Date of Birth : %d \n", birthYear);
		printf("Email : % s \n", email);
		printf("Coming from : %s \n", location);
		printf("Class: %s \n", className);
		printf("Number of trips : %s\n\n\n", timesTravelled);
	}

	printf("______________\n");
	printf("All Passenger info shown\n\n");
	fclose(fp);
	return;
}


//Ready one passenger of users request
Passenger ShowOnePassengerInfo(const char* username)
{


	//Making sure only Admins can access this
	if (strcmp(username, "Employee") == 0)
	{
		printf("Invalid function only Admins allowed \n");
		return;
	}

	printf("\n\nNow Displaying passenger details\n");

	//Searching for passenger of users interest
	int ppsSearch;
	printf("Which passenger pps would you like to display: ");
	scanf_s("%d", &ppsSearch);

	FILE* fp = fopen("Passenger.txt", "r");
	if (fp == NULL)
	{
		perror("Error opening file");
		return;
	}

	//To be read by computers must all be in file and valid to computers perameters
	int pps;
	char firstName[20];
	char surname[20];
	int birthYear;
	char email[50];
	int area;
	int travelClass;
	int tripNum;

	//To show the names of the integers to user
	char className[20];
	char location[20];
	char timesTravelled[40];

	bool found = false;//Checking if passenger found

	//Will remain false so as to keep looking until end of file or passenger found where will end early
	while (found == false)
	{


		fscanf(fp, "%d %s %s %d %s %d %d %d", &pps, firstName, surname, &birthYear, email, &area, &travelClass, &tripNum);

		if (pps == ppsSearch) //Checking if the pps and ppsSearch match
		{
			found = true;
			//Displaying passenger of their request info
			printf("\n------------------------\n");
			printf("PPS: %d\n", pps);
			printf("First Name: %s\n", firstName);
			printf("Surname: %s\n", surname);
			printf("Birth Year: %d\n", birthYear);
			printf("Email: %s\n", email);

			switch (area)
			{
			case 1:
				strcpy(location, "Dublin");
				break;

			case 2:
				strcpy(location, "Leinster");
				break;

			case 3:
				strcpy(location, "Connacht");
				break;

			case 4:
				strcpy(location, "Ulster");
				break;

			case 5:
				strcpy(location, "Munster");
				break;
			}



			if (travelClass == 1)
			{
				strcpy(className, "Economy");
			}
			else
			{
				strcpy(className, "First class");
			}

			switch (tripNum)
			{
			case 1:
				strcpy(timesTravelled, "Less than three times per year");
				break;

			case 2:
				strcpy(timesTravelled, "Less than five times per year");
				break;

			case 3:
				strcpy(timesTravelled, "More than five times per year");
				break;
			}


			printf("Coming from: %s\n", location);
			printf("Travel Class: %s\n", className);
			printf("Trip Number: %s\n", timesTravelled);
			printf("\n------------------------\n\n");

		}
		else if (!found)
		{
			//If not found it will end 
			printf("No user for pps %d has been located in file\n\n", ppsSearch);
			return;
		}


	}
	fclose(fp);
	return;
}


//For altering the inputs of the passengers only done my admin
Passenger ChangeStats(const char* username)
{
	//Reading the first passenger to check if they are real
	FILE* file1 = fopen("Passenger.txt", "r");

	//Then this is where new changes will be put into
	FILE* file2 = fopen("NewPassenger.txt", "w");

	//Making sure both files are working
	if (file1 == NULL || file2 == NULL)
	{
		perror("Error opening file");
		return;
	}

	//This makes sure only Admins i.e manager and owner can use it
	if (strcmp(username, "Employee") == 0)
	{
		printf("Invalid function only Admins allowed \n");
		return;
	}

	printf("\n\nNow updating passenger statistics\n");

	int pps;
	char firstName[20];
	char surname[20];
	int birthYear;
	char email[50];
	int area;
	int travelClass;
	int tripNum;
	int ppsSearch;

	bool found = false;

	//This is giving user pps for it to search for
	printf("Enter PPS of the passenger to update: ");
	scanf("%d", &ppsSearch);

	while (fscanf(file1, "%d %s %s %d %s %d %d %d", &pps, firstName, surname, &birthYear, email, &area, &travelClass, &tripNum) == 8)
	{


		//writing the inputs into the functions to check them and print them if ok
		fscanf(file1, "%d %s %s %d %s %d %d %d", &pps, firstName, surname, &birthYear, email, &area, &travelClass, &tripNum);

		//This is the users search for pps if it = the results this is one they change
		if (pps == ppsSearch)
		{
			found = true;
			printf("\n\nuser %d has been found input new info", ppsSearch);

			printf("\n\n----------------------------------------\n\n");

			//New inputs for the changeds stats
			printf("What is their first name: ");
			scanf("%s", firstName);

			printf("What is their surname: ");
			scanf("%s", surname);


			printf("What year were they born: ");
			scanf_s("%d", &birthYear);

			bool checker = true;
			do
			{
				checker = true;
				printf("Users Email address: ");
				scanf("%s", email);
				if (!strstr(email, ".com") || !strstr(email, "@"))
				{
					printf("Email must contain .com and a @\n");
					checker = false;
				}

			} while (checker == false);

			do
			{
				checker = true;
				printf("Where did user travel from \n");
				printf("1.Dublin \n");
				printf("2.Leinster \n");
				printf("3.Connaght \n");
				printf("4.Ulster \n");
				printf("5.Munster \n");
				scanf_s("%d", &area);
				if (area < 1 || area > 5)
				{
					printf("Invalid input must be between 1 and 5\n");
					checker = false;
				}


			} while (checker == false);

			do
			{
				checker = true;
				printf("What class \n");
				printf("1.Economy \n");
				printf("2.First Class \n");
				scanf_s("%d", &travelClass);
				if (travelClass != 1 && travelClass != 2)
				{
					printf("Invalid input must be between 1 Economy and 2 first class\n");
					checker = false;
				}


			} while (checker == false);

			do
			{
				checker = true;
				printf("What class \n");
				printf("1.Less than three times a year \n");
				printf("2.Less than five times a year \n");
				printf("3.More than five times a year \n");
				scanf_s("%d", &tripNum);
				if (tripNum < 1 || tripNum >3)
				{
					printf("Invalid input must be between 1 and 3\n");
					checker = false;
				}


			} while (checker == false);

			//Writes the results iunto file 2 whether normal or altered
			fprintf(file2, "%d %s %s %d %s %d %d %d\n", pps, firstName, surname, birthYear, email, area, travelClass, tripNum);

			printf("\n\n----------------------------------------\n\n");
		}
		else
		{
			fprintf(file2, "%d %s %s %d %s %d %d %d\n", pps, firstName, surname, birthYear, email, area, travelClass, tripNum);
		}

		//When finished writing/reading closing both files
		fclose(file1);
		fclose(file2);

		//This checks if passenger has been found or not if it has been found NewPassenger replaces the original and if it is not found then NewPassenger is removed
		if (!found)
		{
			remove("NewPassenger.txt");
			printf("No user for pps %d has been located in file\n\n", ppsSearch);
			return;
		}
		else if (found)
		{
			remove("Passenger.txt");
			rename("NewPassenger.txt", "Passenger.txt");

		}

	}

}

//This is to delete a passenger from list based on pps
Passenger Delete()
{
	printf("\n\nNow deleting a passenger\n");
	//Reads passenger so as to check if passenger is in it
	FILE* file1 = fopen("Passenger.txt", "r");

	//This will replace the original if it is used
	FILE* file2 = fopen("NewPassenger.txt", "w");

	//Make sure both files are ok
	if (file1 == NULL || file2 == NULL)
	{
		perror("Error opening file");
		return;
	}

	int ppsSearch;

	//Searching for user pps for if needed//
	printf("Input pps of user you wish to delete: ");
	scanf("%d", &ppsSearch);

	int pps;
	char firstName[20];
	char surname[20];
	int birthYear;
	char email[50];
	int area;
	int travelClass;
	int tripNum;

	//Making it so we know if user is found or not to know if passenger has been found
	bool found = false;

	while (fscanf(file1, "%d %s %s %d %s %d %d %d", &pps, firstName, surname, &birthYear, email, &area, &travelClass, &tripNum) == 8)
	{

		//This says if passenger is equal to the searched pps it will delete passenger by skipping them in file 2
		if (pps == ppsSearch)
		{
			printf("\nUser %d has been deleted\n\n", ppsSearch);
			found = true;
			continue;
		}

		// If passenger is not found it will print it to new file
		fprintf(file2, "%d %s %s %d %s %d %d %d\n", pps, firstName, surname, birthYear, email, area, travelClass, tripNum);
	}

	fclose(file1);
	fclose(file2);

	//Erase new passenge if passenger is not found
	if (!found)
	{
		remove("NewPassenger.txt");
		printf("No user for PPS %d found in file.\n\n", ppsSearch);
	}
	//Replace Passenger with new Passenger if found
	else
	{
		remove("Passenger.txt");
		rename("NewPassenger.txt", "Passenger.txt");
	}
}