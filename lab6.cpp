//
// Created by danil on 14.04.2026.
//
#include<string>
#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>
#include<fstream>
#include<sstream>
class Student {
private:
    std::string name;
    std::string group;
    int record_book_number;
    int *grades;
public:
    Student(){grades=new int[4];}
    Student(std::string name, std::string group, int record_book_number, int new_grades[4]) : name(name), group(group), record_book_number(record_book_number) {
        grades=new int[4];
        for (int i = 0; i < 4; i++) grades[i] = new_grades[i];
    }
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
        os<<st.name<<" "<<st.group<<" "<<st.record_book_number<<" "<<st.grades[0]<<" "<<st.grades[1]<<" "<<st.grades[2]<<" "<<st.grades[3];
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
    std::ifstream input("input.txt");
    if (!input.is_open()) {std::cerr<<"file not found"; return 1;}
    std::string line;
    std::string name;
    std::string group;
    int record_book_number;
    int *grades=new int[4];
    std::vector<Student> students_vec;
    while (std::getline(input,line)) {
        std::stringstream read_line(line);
        read_line >> name >> group >> record_book_number>>grades[0]>>grades[1]>>grades[2]>>grades[3];
        students_vec.push_back(Student(name,group,record_book_number,grades));
    }
    delete[] grades;
    input.close();

    std::ofstream output("output.txt");
    output<<"given vector: "<<std::endl;
    for (auto pos: students_vec) {output<<pos<<std::endl;}

    output<<std::endl<<"sorted vector: "<<std::endl;
    std::sort(students_vec.begin(),students_vec.end());
    for (auto pos: students_vec) {output<<pos<<std::endl;}

    output<<std::endl<<"copied deque: "<<std::endl;
    std::deque<Student> students_deq;
    std::copy(students_vec.begin(),students_vec.end(),std::back_inserter(students_deq));
    for (auto pos: students_deq) {output<<pos<<std::endl;}

    output.close();
    return 0;
}