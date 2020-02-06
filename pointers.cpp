// compile: g++ -std=c++11 -o pointers pointers.cpp
#include <iostream>
#include <string.h>
#include <stdlib.h>

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
	while(1)	//student id input
	{
		printf("Please enter the student's id number: ");
		std::cin >> input_line;

		try
		{
			student.id = std::stoi(input_line);

			if(student.id < 0)
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

	input_line = (char*) realloc(input_line,129 * sizeof(char));

	printf("Please enter the student's first name: ");
	std::cin >> input_line;
	student.f_name = (char*) malloc(sizeof(input_line));
	strcpy(student.f_name,input_line);

	printf("Please enter the student's last name: ");
	std::cin >> input_line;
	student.l_name = (char*) malloc(sizeof(strlen(input_line) + 1));
	strcpy(student.l_name,input_line);
	
	while(1)	//assignment count input
	{
		printf("Please enter how many assignments were graded: ");

		std::cin >> input_line;

		try
		{
			student.n_assignments = std::stoi(input_line);
			
			if(student.n_assignments <= 0)
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

	student.grades = (double*) malloc(student.n_assignments * sizeof(double));

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

/*
	printf("ID= %d\n",student.id);
	printf("Name= %s %s\n",student.f_name,student.l_name);
	printf("Assignments: %d\n",student.n_assignments);
	for(int i = 0;i < student.n_assignments;i++)
		printf("Assignment %d: %f\n",i,student.grades[i]);
*/

	calculateStudentAverage(&student,&average);

//	printf("average= %f\n",average);
// Output `average`
	printf("Student: %s %s [%d]\n",student.f_name,student.l_name,student.id);
	printf("\tAverage grade: %f",average);

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
