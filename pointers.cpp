#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <cmath>

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
    double  average;
    Student student;
    char*   input_line = (char*) malloc(10 * sizeof(char));;
    
// Sequence of user input -> store in fields of `student`
    for(int flag = 1;flag;) //student id input
    {
        flag = 0;  //assume loop will succeed, unless later statements undo this

        printf("Please enter the student's id number: ");
        std::cin >> input_line;

        for(int i = 0; input_line[i] != '\x00';i++)
        {
            if(!isdigit(input_line[i])) //catches non-digit chars, ~including negative signs~
            {
                printf("Sorry, I cannot understand your answer\n");
                flag = 1;  //loop will reiterate

                break;  //breaks inner loop
            }
        }
    }

    student.id = std::stoi(input_line);

    input_line = (char*) realloc(input_line,129 * sizeof(char));

    for(int flag = 1;flag;)
    {
        flag = 0;

        printf("Please enter the student's first name: ");
        std::cin >> input_line;

        for(int i = 0;input_line[i] != '\x00';i++)
            if(!isalpha(input_line[i]))
            {
                printf("Sorry, I cannot understand your answer\n");
                flag = 1;
            }
    }
    student.f_name = (char*) malloc(sizeof(input_line));
    strcpy(student.f_name,input_line);

    for(int flag = 1;flag;)
    {
        flag = 0;

        printf("Please enter the student's last name: ");
        std::cin >> input_line;

        for(int i = 0;input_line[i] != '\x00';i++)
            if(!isalpha(input_line[i]))
            {
                printf("Sorry, I cannot understand your answer\n");
                ++flag;
            }
    }
    student.l_name = (char*) malloc(sizeof(strlen(input_line) + 1));
    strcpy(student.l_name,input_line);

    for(int flag = 1;flag;) //assignment count input
    {
        flag = 0;  //assume loop will succeed, unless later statements undo this

        printf("Please enter how many assignments were graded: ");
        std::cin >> input_line;

        for(int i = 0; input_line[i] != '\x00';i++)
        {
            if(!isdigit(input_line[i])) //catches non-digit chars, ~including negative signs~
            {
                printf("Sorry, I cannot understand your answer\n");
                ++flag;  //loop will reiterate

                break;  //breaks inner loop
            }
        }

        if(!flag)
        {
            student.n_assignments = std::stoi(input_line);

            if(student.n_assignments < 1)   //zeroes pass earlier check
            {
                printf("Sorry, I cannot understand your answer\n");
                ++flag;
            }
        }
    }

    student.grades = (double*) malloc(student.n_assignments * sizeof(double));
    printf("\n");

    for(int i = 0;i < student.n_assignments;i++)
    {   
        while(1)    //assignment count input
        {
            printf("Please enter grade for assignment %d: ",i);

            std::cin >> input_line;

            try
            {
                int decimal_counter = 0;

                for(int i = 0; input_line[i] != '\x00';i++)
                {

                    if(!isdigit(input_line[i])) //catches non-digit chars, ~including negative signs~
                    {
                        if(input_line[i] == '.')    //non-digit is a decimal point
                        {
                            if(decimal_counter++ > 0)   //if there's more than one decimal point
                                throw std::invalid_argument("Too many decimal points");
                        }

                        else    //non-digit isn't a decimal point
                            throw std::invalid_argument("Illegal character");
                    }

                }

                student.grades[i] = strtod(input_line,NULL);

                break;  //breaks infinite while loop
            }//try

            catch(std::invalid_argument)
            {
                printf("Sorry, I cannot understand your answer\n");
            }
        }
    }

    calculateStudentAverage(&student,&average);

//round to the nearest tenth, convert to string

    average *= 10.0;
    average = round(average);
    average /= 10.0;

    std::string avstring = std::to_string(average);

    avstring = avstring.substr(0,avstring.find(".") + 2);

// Output `average`
    printf("\nStudent: %s %s [%d]\n",student.f_name,student.l_name,student.id);
    std::cout << "  Average grade: " << avstring << std::endl;

//free malloced memory
    free(input_line);
    free(student.f_name);
    free(student.l_name);
    free(student.grades);

    return 0;
}//main

void calculateStudentAverage(void *object, double *avg)
{
//sum grades
    Student* student = (Student*) object;
    double  sum = 0;

    for(int i = 0;i < student->n_assignments;i++)
        sum += student->grades[i];

    *avg = sum / (double) student->n_assignments;
}//calculateStudentAverage
