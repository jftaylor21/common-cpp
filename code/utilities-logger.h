#ifndef UTILITIES_LOGGER_H
#define UTILITIES_LOGGER_H

#include <cstdarg>
#include <string>

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

    enum FormattingOptions
    {
      FORMAT_LOGLEVEL=1,
      FORMAT_TIME=2,
      FORMAT_THREADID=4,
      FORMAT_COLOR=8
    };

    static Logger& get();
    ~Logger();

    //bitwise or of options
    void setFormattingOptions(int options);
    int formattingOptions() const;

    void setMaxLogLevel(LogLevel level);
    LogLevel maxLogLevel() const;
    static std::string logLevel2str(LogLevel level);

    void setScreenEnable(bool enable);
    bool screenEnabled() const;

    void setFilename(const std::string& filename);
    void setFileEnable(bool enable);
    bool fileEnabled() const;

    void output(LogLevel level, const char* msg, va_list args);
    void output(LogLevel level, const char* msg, ...);
    void fatal(const char* msg, ...);
    void error(const char* msg, ...);
    void warning(const char* msg, ...);
    void info(const char* msg, ...);

  private:
    Logger();
    Logger(const Logger&);
    Logger& operator=(const Logger&);

    std::string generatePrefix(LogLevel level);

    int mFormattingOptions;
    LogLevel mMaxLogLevel;
    bool mScreenEnabled;
    bool mFileEnabled;
  };
}

#endif
