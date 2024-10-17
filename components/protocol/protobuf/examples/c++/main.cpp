#include <google/protobuf/message.h>  // for protobuf

#include <fstream>
#include <iostream>
#include <vector>

#include "student.pb.h"  // for protobuf source file
int main() {
    // 可以看到，protobuf文件中的信息都被封装在namespace
    // student中，这是之前protobuf中的`package`语法所规定的。
    // 1. 如何实例化一个proto文件中定义的类
    student::StudentInfo student1;
    // 2. 如何设置类的各个属性
    // a. 添加单一字段：使用set_<xxx>()语句
    student1.set_age(18);
    student1.set_name("Alice");
    student1.set_sex(student::Sex::FEMALE);
    // b. 添加repeated字段：使用add_<xxx>()语句
    student::Course *course1 = student1.add_courses();
    course1->set_name("calculus");
    course1->set_credit(5);
    student::Course *course2 = student1.add_courses();
    course2->set_name("Fundamentals of Electronic Circuits and System");
    course2->set_credit(2);
    // 3. 如何使用类的各个属性：使用<xxx>()语句
    std::cout << "----------------student info----------------" << std::endl
              << "age: " << student1.age() << std::endl
              << "name: " << student1.name() << std::endl
              << "sex (0:male, 1:female): " << (int)student1.sex() << std::endl
              << "courses: " << std::endl;
    for (int i = 0; i < student1.courses_size(); i++) {
        std::cout << " " << i << ". "
                  << "name: " << student1.courses(i).name() << " "
                  << "credit: " << student1.courses(i).credit() << std::endl;
    }
    std::cout << "--------------------------------------------" << std::endl;
    // 4. 序列化
    std::cout << "serialize to file." << std::endl;
    std::fstream output("./output", std::ios::out | std::ios::binary);
    student1.SerializeToOstream(&output);  // 序列化为流
    output.close();
    std::cout << "serialize to array." << std::endl;
    size_t size = student1.ByteSizeLong();
    unsigned char *data = new unsigned char[size];
    student1.SerializeToArray(data, student1.ByteSizeLong());  // 序列化为数组
    // 5. 反序列化和debug
    std::cout << "deserialize from array." << std::endl;
    student::StudentInfo studentInfoFromArray;
    std::cout << std::endl;
    studentInfoFromArray.ParseFromArray(data, size);
    std::cout << studentInfoFromArray.DebugString()
              << std::endl;  // 输出字符串化的信息
    // 此处有大坑：需要开着 -pthread，否则会报错
}