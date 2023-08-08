#include <string>
#include <fstream>
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
using std::ofstream;
using std::string;

int main(int argc, char** argv) {
    //创建目的地
    //创建来源
    //根据来源设置优先级，绑定目的地
    //写入日志

    //采用指针的形式创建目的地对象
    //第一个参数代表目的地名字，第二参数代表想要输出到终端
    //之前常见的new语句创建对象，前后类名保持一致
    //这里涉及到继承的知识，是用基类指针指向了一个派生类对象
    //
    string filename("test1.txt");
    ofstream ofs(filename);

	/* log4cpp::OstreamAppender *appender1 = new log4cpp::OstreamAppender("console", &std::cout); */
	log4cpp::OstreamAppender *appender1 = new log4cpp::OstreamAppender("console", &ofs);
    //目的地对象通过setLayout函数设置布局，参数是布局对象
	appender1->setLayout(new log4cpp::BasicLayout());

    //第二个参数是保存日志的文件名
	log4cpp::FileAppender *appender2 = new log4cpp::FileAppender("default", "program.log");
	appender2->setLayout(new log4cpp::BasicLayout());

    //创建了Category类型的根对象，用root作为引用名进行了绑定
	log4cpp::Category& root = log4cpp::Category::getRoot();
    //设置Category根对象的优先级（日志系统的优先级）
	root.setPriority(log4cpp::Priority::WARN);
    //设置root的目的地，传入的目的地对象的地址
	root.addAppender(appender1);

    //创建category类型的叶对象,同样用引用进行绑定
    //引用名确实不与对象名重名，后面的sub1与配置文件相关，不代表对象名
    //这种方式是叶对象和根对象分离地去创建
	log4cpp::Category& sub1 = log4cpp::Category::getInstance(std::string("sub1"));
    //Category的叶对象重新设置了目的地，但是没有重新设置优先级
    //所以sub1的（系统）优先级会继承root的优先级
    //优先级改写了
	sub1.setPriority(log4cpp::Priority::CRIT);
    //目的地增加了
	sub1.addAppender(appender2);
    //禁用根对象的目的地
    sub1.setAdditivity(false);

    //用category对象去写入的日志（来源）
	// use of functions for logging messages
    // 这些函数的名字代表写入的日志信息的优先级
	root.error("root error");//会记录
	root.info("root info");//不会
	sub1.error("sub1 error");//不会
	sub1.warn("sub1 warn");//不会
    sub1.alert("sub1 alert");//会记录到文件，也会输出到终端

	// printf-style for logging variables
	root.warn("%d + %d == %s ?", 1, 1, "two");//会

	// use of streams for logging messages
	root << log4cpp::Priority::ERROR << "Streamed root error";//会
	root << log4cpp::Priority::INFO << "Streamed root info";//不会
	sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";//不会
	sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";//不会

	// or this way:
	root.errorStream() << "Another streamed error";//会

	return 0;
}

