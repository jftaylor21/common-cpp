#ifndef UTILITIES_LOGGER_H
#define UTILITIES_LOGGER_H

namespace Utilities
{
  class Logger
  {
  public:
    enum LogLevel
    {
      LOGLEVEL_FATAL,
      LOGLEVEL_ERROR,
      LOGLEVEL_WARNING,
      LOGLEVEL_INFO
    };

    static Logger& get();
    ~Logger();

    void setMaxLogLevel(LogLevel level);
    LogLevel maxLogLevel();

    void output(LogLevel level, const char* msg, ...);
    void fatal(const char* msg, ...);
    void error(const char* msg, ...);
    void warning(const char* msg, ...);
    void info(const char* msg, ...);

  private:
    Logger();
    Logger(const Logger&);
    Logger& operator=(const Logger&);

    LogLevel mMaxLogLevel;
  };
}

#endif
