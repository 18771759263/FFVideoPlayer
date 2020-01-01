#pragma once

#include <iostream>
#include <string>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h> 
#include <log4cplus/layout.h> 
#include <log4cplus/loggingmacros.h> 
#include <log4cplus/helpers/stringhelper.h> 

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;


class MyLog
{
public:
	static MyLog* getInstance();
	Logger logger;

	~MyLog();

private:
	MyLog();

private:
	//���ڲ������ٵ���
	class GC
	{
	public:
		~GC()
		{
			if (m_Log != NULL)
			{
				delete m_Log;
				m_Log = NULL;
			}
		}
	};

private:
	static MyLog *m_Log;
	static GC gc;
};

