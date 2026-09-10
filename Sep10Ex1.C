//THIS DOESNT WORK AT ALL LMAO
#include <stdio.h>

struct Student{
    char name[20];
    float marks;
};
typedef struct{
    char name[20];
    int id;
    float price;
}book;

void raisePrice(book *p) {
    p ->price = p ->price + 10.0;
}
struct Student student_arr[5];

book raisePriceWithoutPointer(book var){
    
}

struct Student studentbuilder(void){
struct Student newstudent;
    scanf("Please enter student's name: %s", newstudent.name);
    scanf("Please enter student's marks: %d", newstudent.marks);
    return newstudent;
}

int main(void){
    int students;
    printf("How many students are in this class? (0-5): ");
    scanf("%d", students);

    for(int i=0; i<students; i++){
        studentbuilder();
    }
    for(int i=0; i<sizeof(student_arr); i++){
        printf("Student name:  %c", student_arr[i].name);
        printf("Average grade: %d", student_arr[i].marks);
    }
}