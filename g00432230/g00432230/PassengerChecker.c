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



int main()
{

	//Checking if login file exists
	if (!FileExists("login.txt")) 
	{
		LoginFile();
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
	