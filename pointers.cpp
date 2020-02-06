// compile: g++ -std=c++11 -o pointers pointers.cpp
#include <iostream>
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
	char*	input_line;
	
// Sequence of user input -> store in fields of `student`
	printf("Please enter the student's id number: ");
	input_line = (char*) malloc(10 * sizeof(char));
	std::cin >> input_line;
	//TODO insert error check and store

	printf("%s\n",input_line);	//test id #

	printf("Please enter the student's first name: ");
	input_line = (char*) realloc(input_line,129 * sizeof(char));
	std::cin >> input_line;
	//TODO insert error check and store

	printf("%s\n",input_line);	//test first name

	printf("Please enter the student's last name: ");
	std::cin >> input_line;
	//TODO insert error check and store

	printf("%s\n",input_line);	//test last name
// Call `CalculateStudentAverage(???, ???)`
// Output `average`

    return 0;
}

void calculateStudentAverage(void *object, double *avg)
{
    // Code to calculate and store average grade
}
