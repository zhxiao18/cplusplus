#include <iostream>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Category.hh>
using std::cout;
using namespace log4cpp;

void test0(){
    //1.设置日志布局
    PatternLayout * ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%p] %m%n");
    //2.创建日志目的地对象
    OstreamAppender * pos = new OstreamAppender("console",&cout);
    //3.用目的地对象去绑定布局
    pos->setLayout(ptn1);
    //4.创建日志记录器对象（来源）
    Category & root = Category::getRoot();
    //传入C风格字符串也可以，会发生隐式转换
    Category & salesDepart = Category::getInstance("salesDepart");
    //如果没有需要继承的属性，
    //可以采用这种方式一步到位地去创建一个Category类型的叶对象
    /* Category & salesDepart = Category::getRoot().getInstance("salesDepart"); */

    //5.设置优先级
    salesDepart.setPriority(Priority::ERROR);
    //6.设置目的地
    salesDepart.addAppender(pos);

    //7.记录日志
    salesDepart.emerg("this is an emerg msg");
    salesDepart.fatal("this is a fatal msg");
    salesDepart.alert("this is an alert msg");
    salesDepart.crit("this is a crit msg");
    salesDepart.error("this is an error msg");
    salesDepart.warn("this is a warn msg");
    salesDepart.notice("this is a notice msg");
    salesDepart.info("this is an info msg");
    salesDepart.debug("this is a debug msg");


    //8.日志系统要退出时，回收资源
    //Category对象内部会管理好资源
    Category::shutdown();
}

int main(void){
    test0();
    return 0;
}

