#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//defining structure for student:
struct Student{
	char firstname[20];
	char surname[20];
	double lab;
	double assignment;
	double midterm;
	double final;
	double total;
};
//To avoid using struct again and again, we are defining our own datatype:
typedef struct Student student;

//Protoypes of functions
int linecount(FILE *,char *);
student *Load_StudentTable(int,char *,FILE *,student *); 
void Display_StudentTable(int,student *);
int search(char *,student*,int);
void sort(student *,char,int);



/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
//Taking the file name from the user:
	char filename[20];
	printf("Please enter the filename: ");
	scanf("%s",filename);
	while(strcmp(argv[1],filename)!=0){
		printf("This file does not exist, please enter again: ");
		scanf("%s",filename);
	}
	//Declaring FILE and storing number of lines:
	FILE *inFile;
	int numoflines;
	numoflines = linecount(inFile,filename);
	printf("Number of lines in %s are %d\n\n",filename,numoflines);
	
	//Dynamic memory allocation:
	student *info;
	info = (student *)malloc(sizeof(student)*(numoflines));
	if(info==NULL){
		printf("Failed to allocate memory");
		exit(1);
	}
	//Loading the file data to the array:
	info = Load_StudentTable(numoflines,filename,inFile,info);
	//Displaying the student table:
	Display_StudentTable(numoflines,info);
	//Going to ask user what to do:
	//Going to exit the program when end=1:
	int end=0,choice,found;
	do{
		char search_name[50],search_surname[20],ask;
		//Asking user what to do:
		printf("Press 1 for search, 2 for sort and 3 for exit: ");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				printf("Enter the name of the student: ");
				//scanf("%s %s",search_name,search_surname);
				fflush(stdin);
				gets(search_name);
				//Passing the values to search function:
				found = search(search_name,info,numoflines);
				if(found>=1)
				{
					//When found is greater and equals to one its means that name is available in table:
					printf("%s %s has %.2lf from Lab, %.2lf from Assignment, %.2lf from Midterm and %.2lf from Final, with the total of %.2lf.\n\n",info[found].firstname,info[found].surname,info[found].lab,info[found].assignment,info[found].midterm,info[found].final,info[found].total);
				}
				//When found=-1 then we are going to ask user again for student name:
				while(found==-1){
					printf("That student is unknow! Please try again: ");
					gets(search_name);
					found = search(search_name,info,numoflines);
					if(found>=1)
					{
						//When found is greater and equals to one its means that name is available in table:
						printf("%s %s has %.2lf from Lab, %.2lf from Assignment, %.2lf from Midterm and %.2lf from Final, with the total of %.2lf.\n\n",info[found].firstname,info[found].surname,info[found].lab,info[found].assignment,info[found].midterm,info[found].final,info[found].total);
					}					
				}
				break;
			case 2:
				//Asking user how to sort student table
				printf("Sort by (F:Final , T:Total): ");
				scanf(" %c",&ask);
				//In case, user entered the wrong option then we are going to ask again:
				while(ask!='T' && ask!='F'){
				printf("Sort by (F:Final , T:Total): ");
				scanf(" %c",&ask);
				}
				//Passing the user answer to sort
				sort(info,ask,numoflines);
				//Going to display the table after sorting is completed:
				Display_StudentTable(numoflines,info);

				break;
				
			case 3:
				//Going to end the program:
				end=1;
				break;
		}
	}while(end!=1);
	
	
	
	
	
	return 0;
}
//Line count funtion
//Going to read and return number of lines, in cng140.txt
int linecount(FILE *inFile,char *filename){
	
	int c,count=0;
	//Opening the file:
	inFile = fopen(filename,"r");
	if(inFile==NULL){
		printf("Unable to open the file\n");
		printf("or File does not exist");
		exit(1);
	}
	//This while loop will read each character until End of File:
	while((c=fgetc(inFile))!=EOF){
		
		if(c=='\n')//c=='\n' means end of line
		{
			//so we are going to increament value of count:
			count++;
		}
	}
	//We are increament again out of while because last line is equal to end of file not '\n':
	count++;
	fclose(inFile);
	return count;
	
}

//Load Student Data fucntion
//Fuction is going to read each line the file and going to store it to the array
student *Load_StudentTable(int count,char *filename,FILE *inFile,student *info){
	int i;
	inFile = fopen(filename,"r");
	if(inFile==NULL){
		printf("Unable to open the file\n");
		printf("or File does not exist");
		exit(1);
	}
	double temp; //This temp will record total marks for students:
	//Storing the values to the info array:
	for(i=0;i<count;i++){
		if(i==0){
			fscanf(inFile,"%*[^\n]");
		}
		else{
			fscanf(inFile,"%s %s %lf %lf %lf %lf %lf",info[i].firstname,info[i].surname,&info[i].lab,&info[i].assignment,&info[i].midterm,&info[i].final);
			temp = info[i].lab + info[i].assignment + (0.3*info[i].midterm) + (0.35*info[i].final);
			info[i].total = temp;
		}
	}
	fclose(inFile);
	return info;	
}
//Function will display the table:
void Display_StudentTable(int count, student *info){
	int i;
	if(info==NULL){
		printf("File not loaded");
		exit(1);
	}
	//Defining an array which is going to record only the first line of cng140.txt:
	char detail[7][50]={"Name","Surname","Lab","Assignment","Midterm","Final","Total"};
	for(i=0;i<=7;i++){
		if(strcmp(detail[i],"Name")==0)
		{
			printf("%s ",detail[i]);
		}
		else if(strcmp(detail[i],"Surname")==0){
			printf("%s",detail[i]);
		}
		else{
			printf("\t%s",detail[i]);
		}
	}
	printf("\n");
	//Displaying Table:
	for(i=1;i<count;i++){
		printf("%s %s %5.2lf\t%.2lf\t\t%.2lf\t%.2lf\t%.2lf\t\n",info[i].firstname,info[i].surname,info[i].lab,info[i].assignment,info[i].midterm,info[i].final,info[i].total);
	}
}

//This function is going to search for student name and surname:
int search(char *search_name,student *info,int count){
	int i,found;
	//Combine is the combination of firstname and surname of student:
	char combined[50];
	//Putting a space in first name and storing it to putspace:
	char putspace[20];
	//In temp_firstname we are storing firstname so that orignal firstname will remain same:
	char temp_firstname[20];
	
	//For loop will go through every data until and unless name is found:
	for(i=1;i<count;i++){
		
		
		if(strcmp(search_name,info[i].firstname)==0){
		found = i;
		return found;
		
	}
	
		//Combining first name and surname so that i can compare it:
		strcpy(temp_firstname,info[i].firstname);
		strcpy(putspace,strcat(temp_firstname," "));
		strcpy(combined,strcat(putspace,info[i].surname));
		
	if(strcmp(search_name,combined)==0)
	{
		found=i;
		return found;
	}
	
	//Going to compare surnames when user only entered the student surname
	else if(strcmp(search_name,info[i].surname)==0){
		found = i;
		return found;
	}
	
	}
	
	//If name and surname are not found then it's going to return -1:
	return -1;
}

//This function is going to sort the data
void sort(student *info, char ask, int count){
	//How I sorted the student table
	//Declaring variables to store values for temporary time:
	int i,k;
	char temp_firstname[20],temp_surname[20];
	double temp_lab,temp_assignment,temp_midterm,temp_final,temp_total;
	//If user want to sort total grades then:
	if(ask=='T'){
		//This nested loop will loop until all values are not sorted out:
		for(k=1;k<count;k++){
		
			//Going to loop from first student to second last student:
			for(i=1;i<count-1;i++){
				
				if(info[i].total < info[i+1].total){
					//i is first student[i] and i+1 is the student after first[i+1] one.
					//if first student grades[i] are greater than the student after first[i+1] student then it's not going to enter this if statement.
					//if if statement is true than:
					//I will copy the first student[i] data to temporary values.
					strcpy(temp_firstname,info[i].firstname);
					strcpy(temp_surname,info[i].surname);					 
					temp_lab = info[i].lab;
					temp_assignment = info[i].assignment;
					temp_midterm = info[i].midterm;
					temp_final = info[i].final;
					temp_total = info[i].total;
					//When first student[i] are copied then:
					//we going to replace second student[i+1] data to first[i]:
					strcpy(info[i].firstname,info[i+1].firstname);
					strcpy(info[i].surname,info[i+1].surname);
					info[i].lab = info[i+1].lab;
					info[i].assignment = info[i+1].assignment;
					info[i].midterm = info[i+1].midterm;
					info[i].final = info[i+1].final;
					info[i].total = info[i+1].total;
					//Finally, we are going copy values stored in temporary variables back to second student[i+1] place:
					strcpy(info[i+1].firstname, temp_firstname);
					strcpy(info[i+1].surname, temp_surname);
					info[i+1].lab = temp_lab;
					info[i+1].assignment = temp_assignment;
					info[i+1].midterm = temp_midterm;
					info[i+1].final = temp_final;
					info[i+1].total = temp_total;					
					
					
					
					
				}
			
			}
		}
	}
	//When user want sort the student table by final grades:
	//We are going to do the same thing as we did above but this time we going to compare final grades with each other untill and unless all values are sorted:
	else{
		for(k=1;k<count;k++){
		
			for(i=1;i<count-1;i++){
				if(info[i].final < info[i+1].final){
					strcpy(temp_firstname,info[i].firstname);
					strcpy(temp_surname,info[i].surname);					 
					temp_lab = info[i].lab;
					temp_assignment = info[i].assignment;
					temp_midterm = info[i].midterm;
					temp_final = info[i].final;
					temp_total = info[i].total;
					
					strcpy(info[i].firstname,info[i+1].firstname);
					strcpy(info[i].surname,info[i+1].surname);
					info[i].lab = info[i+1].lab;
					info[i].assignment = info[i+1].assignment;
					info[i].midterm = info[i+1].midterm;
					info[i].final = info[i+1].final;
					info[i].total = info[i+1].total;
					
					strcpy(info[i+1].firstname, temp_firstname);
					strcpy(info[i+1].surname, temp_surname);
					info[i+1].lab = temp_lab;
					info[i+1].assignment = temp_assignment;
					info[i+1].midterm = temp_midterm;
					info[i+1].final = temp_final;
					info[i+1].total = temp_total;					
					
					
					
					
				}
			
			}
		}
		
	}
}


