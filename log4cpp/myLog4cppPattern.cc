//patternLayout   FileAppender
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>

using std::cin;
using std::cout;
using std::endl;
using namespace log4cpp;

void test01(){
    //1、日志布局
    PatternLayout * pattLay = new PatternLayout();
    pattLay->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout * pattLay2 = new PatternLayout();
    pattLay2->setConversionPattern("%d %c [%p] %m%n");

    //2、日志目的地
    //打印到终端
    OstreamAppender * osAppender = new OstreamAppender("ostream", &cout);
    osAppender->setLayout(pattLay);
    //打印到文件中
    FileAppender *pfa = new FileAppender("file", "test.txt");
    pfa->setLayout(pattLay2);

    //3、日志种类,日志记录器
    Category & root = Category::getRoot();
    root.addAppender(osAppender);
    root.addAppender(pfa);

    //4、过滤器
    root.setPriority(Priority::DEBUG);

    //5、记录日志
    root.warn("Warning!");
    root.fatal("Fatal!");
    root.error("Error!");

    Category::shutdown();
}

int main()
{   
    test01();
    return 0;
}

