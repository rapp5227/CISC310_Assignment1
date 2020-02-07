// compile: g++ -std=c++11 -o pointers pointers.cpp
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    double	average;
    Student	student;
	char*	input_line = (char*) malloc(10 * sizeof(char));;
	
// Sequence of user input -> store in fields of `student`
	for(int loop_flag = 1; loop_flag == 1;)	//student id input
	{
		loop_flag = 0;	//assume loop will succeed, unless later statements undo this

		printf("Please enter the student's id number: ");
		std::cin >> input_line;

		for(int i = 0; input_line[i] != '\x00';i++)
		{
			if(!isdigit(input_line[i]))	//catches non-digit chars, ~including negative signs~
			{
				printf("Sorry, I cannot understand your answer\n");
				loop_flag = 1;	//loop will reiterate

				break;	//breaks inner loop
			}
		}
	}

	student.id = std::stoi(input_line);

	input_line = (char*) realloc(input_line,129 * sizeof(char));

	printf("Please enter the student's first name: ");
	std::cin >> input_line;
	student.f_name = (char*) malloc(sizeof(input_line));
	strcpy(student.f_name,input_line);

	printf("Please enter the student's last name: ");
	std::cin >> input_line;
	student.l_name = (char*) malloc(sizeof(strlen(input_line) + 1));
	strcpy(student.l_name,input_line);

	for(int loop_flag = 1; loop_flag == 1;)	//assignment count input
	{
		loop_flag = 0;	//assume loop will succeed, unless later statements undo this

		printf("Please enter how many assignments were graded: ");
		std::cin >> input_line;

		for(int i = 0; input_line[i] != '\x00';i++)
		{
			if(!isdigit(input_line[i]))	//catches non-digit chars, ~including negative signs~
			{
				printf("Sorry, I cannot understand your answer\n");
				loop_flag = 1;	//loop will reiterate

				break;	//breaks inner loop
			}
		}

		if(!loop_flag)
		{
			student.n_assignments = std::stoi(input_line);

			if(student.n_assignments < 1)	//zeroes pass earlier check
			{
				printf("Sorry, I cannot understand your answer\n");
				++loop_flag;
			}
		}
	}

	student.grades = (double*) malloc(student.n_assignments * sizeof(double));
	printf("\n");

	for(int i = 0;i < student.n_assignments;i++)
	{	
		while(1)	//assignment count input
		{
			printf("Please enter grade for assignment %d: ",i);

			std::cin >> input_line;

			try
			{
				student.grades[i] = strtod(input_line,NULL);
				
				if(student.grades[i] < 0.0)
				{
					throw std::invalid_argument("Negative number");
				}

				break;
			}
			catch(std::invalid_argument)
			{
				printf("Sorry, I cannot understand your answer\n");
			}
		}
	}

	calculateStudentAverage(&student,&average);

//trim trailing zeroes from average
	char* avstring = (char*) malloc(11 * sizeof(char));	//score must be less than 1000, has up to 6 decimals
	sprintf(avstring,"%f",average);

//TODO avstring is initalized correctly, need to trim the zeroes

// Output `average`
	printf("\nStudent: %s %s [%d]\n",student.f_name,student.l_name,student.id);
	printf("  Average grade: %s",avstring);

	free(input_line);
	free(student.grades);

    return 0;
}

void calculateStudentAverage(void *object, double *avg)
{
//sum grades
	Student* student = (Student*) object;
	double	sum = 0;

	for(int i = 0;i < student->n_assignments;i++)
		sum += student->grades[i];

	*avg = sum / (double) student->n_assignments;
}
