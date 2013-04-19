#include "utilities-logger.h"
#include "utilities-thread.h"
#include "utilities-screen.h"
#include "utilities-string.h"
#include "utilities-time.h"
#include <cstdio>

Utilities::Logger& Utilities::Logger::get()
{
  static Logger log;
  return log;
}

Utilities::Logger::Logger()
  : mFormattingOptions(FORMAT_LOGLEVEL|FORMAT_TIME|FORMAT_THREADID|FORMAT_COLOR),
    mMaxLogLevel(LOGLEVEL_FATAL)
{
}

Utilities::Logger::~Logger()
{
}

void Utilities::Logger::setFormattingOptions(int options)
{
  mFormattingOptions = options;
}

int Utilities::Logger::formattingOptions() const
{
  return mFormattingOptions;
}

void Utilities::Logger::setMaxLogLevel(LogLevel level)
{
  mMaxLogLevel = level;
}

Utilities::Logger::LogLevel Utilities::Logger::maxLogLevel() const
{
  return mMaxLogLevel;
}

std::string Utilities::Logger::logLevel2str(LogLevel level)
{
  std::string ret;
  switch(level)
  {
  case LOGLEVEL_FATAL:
    ret = "FATAL";
    break;
  case LOGLEVEL_ERROR:
    ret = "ERROR";
    break;
  case LOGLEVEL_WARNING:
    ret = "WARNING";
    break;
  case LOGLEVEL_INFO:
    ret = "INFO";
    break;
  }
  return ret;
}

void Utilities::Logger::setScreenEnable(bool enable)
{
  mScreenEnabled = enable;
}

bool Utilities::Logger::screenEnabled() const
{
  return mScreenEnabled;
}

void Utilities::Logger::output(LogLevel level, const char *msg, va_list args)
{
  if (level <= mMaxLogLevel && mScreenEnabled)
  {
    //according to spec, this is thread safe
    vfprintf(stderr, (generatePrefix(level)+msg).c_str(), args);
    fflush(stderr);
    setTextColor(COLOR_RESET);
  }
  if (level == LOGLEVEL_FATAL)
  {
    exit(1);
  }
}

void Utilities::Logger::output(LogLevel level, const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  output(level, msg, args);
  va_end(args);
}

void Utilities::Logger::fatal(const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  output(LOGLEVEL_FATAL, msg, args);
  va_end(args);
}

void Utilities::Logger::error(const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  output(LOGLEVEL_ERROR, msg, args);
  va_end(args);
}

void Utilities::Logger::warning(const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  output(LOGLEVEL_WARNING, msg, args);
  va_end(args);
}

void Utilities::Logger::info(const char *msg, ...)
{
  va_list args;
  va_start(args, msg);
  output(LOGLEVEL_INFO, msg, args);
  va_end(args);
}

std::string Utilities::Logger::generatePrefix(LogLevel level)
{
  std::string ret;
  if (mFormattingOptions & FORMAT_COLOR)
  {
    switch(level)
    {
    case LOGLEVEL_FATAL:
    case LOGLEVEL_ERROR:
      setTextColor(COLOR_RED);
      break;
    case LOGLEVEL_WARNING:
      setTextColor(COLOR_YELLOW);
      break;
    case LOGLEVEL_INFO:
      setTextColor(COLOR_GREEN);
      break;
    }
  }
  else if (mFormattingOptions & FORMAT_LOGLEVEL)
  {
    ret += "[" + logLevel2str(level) + "] ";
  }
  else if (mFormattingOptions & FORMAT_TIME)
  {
    ret += "[" + timeString() + "] ";
  }
  else if (mFormattingOptions & FORMAT_THREADID)
  {
    ret += "[" + toString(Thread::currentThreadID())+"] ";
  }
  return ret;
}
