#include "utilities-logger.h"
#include <cstdio>
#include <cstdarg>

Utilities::Logger& Utilities::Logger::get()
{
  static Logger log;
  return log;
}

Utilities::Logger::Logger()
  : mMaxLogLevel(LOGLEVEL_FATAL)
{
}

Utilities::Logger::~Logger()
{
}

void Utilities::Logger::setMaxLogLevel(LogLevel level)
{
  mMaxLogLevel = level;
}

Utilities::Logger::LogLevel Utilities::Logger::maxLogLevel()
{
  return mMaxLogLevel;
}

void Utilities::Logger::output(LogLevel level, const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  vfprintf(stderr, msg, args);
  fflush(stderr);
  va_end(args);
}
