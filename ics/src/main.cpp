#include <stdio.h>

#include "list.h"

struct Student
{
    int Age;
    int Grade;
};

void DisplayList(List<Student>& list)
{
    auto* n = list.First;
    while (n != list.Last)
    {
        Student& s = n->Val;
        printf("Age: %i, Grade: %i\n", s.Age, s.Grade);
        n = n->Next;
    }
}

int main()
{
    List<Student> list;
    list.Init(20);

    Student s{ 0, 0 };
    list.Add(s);

    s = Student{ 4, 8 };

    list.Add(s);

    DisplayList(list);

    int a = -1 % 8;
    printf("-1 % 8 = %i\n", a);
}
