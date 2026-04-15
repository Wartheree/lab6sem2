//
// Created by danil on 14.04.2026.
//
#include<string>
#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>
class Student {
private:
    std::string name;
    std::string group;
    int record_book_number;
    int *grades;
public:
    Student(){grades=new int[4];}
    Student(std::string name, std::string group, int record_book_number, int grades[4]) : name(name), group(group), record_book_number(record_book_number), grades(grades) {}
    ~Student(){delete[] grades;}
    Student(const Student &oth) {
        name=oth.name;
        group=oth.group;
        record_book_number=oth.record_book_number;
        grades=new int[4];
        for(int i=0;i<4;i++){grades[i]=oth.grades[i];}
    }
    Student& operator=(const Student &oth) {
        if (this == &oth) return *this;
        delete[] grades;
        name=oth.name;
        group=oth.group;
        record_book_number=oth.record_book_number;
        grades=new int[4];
        for(int i=0;i<4;i++){grades[i]=oth.grades[i];}
        return *this;
    }
    Student(Student&& oth) {
        name=oth.name;
        group=oth.group;
        record_book_number=oth.record_book_number;
        grades=oth.grades;
        oth.grades=nullptr;
    }
    Student& operator=(Student&& oth) {
        if (this == &oth) return *this;
        delete[] grades;
        name=oth.name;
        group=oth.group;
        record_book_number=oth.record_book_number;
        grades=oth.grades;
        oth.grades=nullptr;
        return *this;
    }
    float get_average() const{
        return (grades[0]+grades[1]+grades[2]+grades[3])/4.0;
    }
    friend std::ostream& operator<<(std::ostream& os, const Student& st) {
        os<<"Name: "<<st.name<<"; Group: "<<st.group<<"; Record Book Number: "<<st.record_book_number<<"; Grades: "<<st.grades[0]<<", "<<st.grades[1]<<", "<<st.grades[2]<<", "<<st.grades[3];
        return os;
    }
    bool operator<(const Student& oth) const {
        return this->get_average()<oth.get_average();
    }
    bool operator>(const Student& oth) const {
        return this->get_average()>oth.get_average();
    }
};

int main() {
    int* grade1=new int[4]{4,5,5,4};
    int* grade2=new int[4]{5,5,5,5};
    int* grade3=new int[4]{3,3,3,3};
    Student s1("John", "RK1", 1234,grade1);
    Student s2("Ann", "RK2", 2314,grade2);
    Student s3("Peter", "RK3", 6751,grade3);
    std::vector<Student> students_vec={s1,s2,s3};
    std::sort(students_vec.begin(),students_vec.end());
    for (auto pos: students_vec) {std::cout<<pos<<std::endl;}
    std::cout<<std::endl;

    std::deque<Student> students_deq;
    std::copy(students_vec.begin(),students_vec.end(),std::back_inserter(students_deq));
    std::sort(students_deq.begin(),students_deq.end(),std::greater<Student>());
    for (auto pos: students_deq) {std::cout<<pos<<std::endl;}

    return 0;
}