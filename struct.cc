#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    cout<<"---------------------------"<<endl;
    typedef struct student_s{
        string name;
        int age;
        int score;
    }student_t;

    //赋值1
    student_t stu1 = {"张三", 29, 94};
    
    cout << stu1.name << "  " << stu1.score << "  " << stu1.age << endl;

    //赋值2
    student_t stu2;
    stu2.name = "李四";
    stu2.age = 23;
    stu2.score = 90;    

    cout << stu1.name << "  " << stu1.score << "  " << stu1.age << endl;

    cout<<"---------------------------"<<endl;

    //结构体数组
    
    student_t stuArr[3] = {
        {"wangwu", 24, 59},
        {"zhaoliu", 40, 100},
        {"songqi", 19, 30}
    };

    for(int i = 0; i < 3; i ++){
        cout<<"name:"<<stuArr[i].name<<" "<<"age:"<<stuArr[i].age<<" "<<"score:"<<stuArr[i].score<<endl;
    }
    
    cout<<"---------------------"<<endl;

    stuArr[1].name = "change";

    for(int i = 0; i < 3; i ++){
        cout<<"name:"<<stuArr[i].name<<" "<<"age:"<<stuArr[i].age<<" "<<"score:"<<stuArr[i].score<<endl;
    }
    cout<<"------------------------------------------------"<<endl;

    student_t pStu = {"point", 12, 99};
    student_t *p = &pStu;

    cout<<"name:"<<p->name<<" "<<"age:"<<p->score<<" "<<"score:"<<p->score<<endl;

    return 0;
}

