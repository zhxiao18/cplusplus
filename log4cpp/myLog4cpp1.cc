//普通布局，写入到cout
#include <iostream>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Priority.hh>

using std::cin;
using std::cout;
using std::endl;
using namespace log4cpp;

void test01(){
    //1、日志布局
    SimpleLayout *pSmpl = new SimpleLayout();

    //2、日志目的地
   OstreamAppender *pOsa = new OstreamAppender("ostream", &cout);
   pOsa->setLayout(pSmpl);
    
    //3、category种类
    Category &root = Category::getRoot();
    root.addAppender(pOsa);

    //4、过滤器
    root.setPriority(Priority::DEBUG);
    /* cout << root.getPriority() << endl; */

    //5、记录日志
    root.alert("this is a alert message.");

    Category::shutdown();
}

int main()
{   
    test01();
    return 0;
}

