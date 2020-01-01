#include "MyLog.h"
#include <iostream>
#include <string>

using namespace std;

MyLog* MyLog::m_Log = NULL;
MyLog::GC MyLog::gc;

#define PROPERT "D:\\VS_WorkSpace\\FFVideoPlayer\\x64\\Debug\\config\\logconfig.properties"

MyLog::MyLog()
{
	log4cplus::initialize();

	PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(PROPERT));
	logger = Logger::getRoot();
}

MyLog::~MyLog()
{
	
}

MyLog *MyLog::getInstance()
{
	if (m_Log == NULL)
	{
		m_Log = new MyLog();
	}

	return m_Log;
}