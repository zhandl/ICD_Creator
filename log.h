
#ifndef QXMLEDIT_FRAMEWORK_LOG_H
#define QXMLEDIT_FRAMEWORK_LOG_H

// this code inspired by KLabeler
class LogInfo
{

public:
    QString source;     // module
    QString method;     //
    QString type;       // enter function, exit, etc

};

class FrwLogger
{

public:
    enum ELogLevel { DEBUG, INFO, WARNING, ERROR };


    virtual bool isEnabled() = 0;
    virtual void setEnabled(const bool how) = 0;
    virtual ELogLevel getLevel() = 0;
    virtual void setLevel(const ELogLevel newLevel) = 0;
    virtual bool isLoggable(const ELogLevel level) = 0;

    virtual void debug(const QString &message, const LogInfo *source = NULL) = 0;
    virtual void info(const QString &message, const LogInfo *source = NULL) = 0;
    virtual void warning(const QString &message, const LogInfo *source = NULL) = 0;
    virtual void error(const QString &message, const LogInfo *source = NULL) = 0;

};


#endif // QXMLEDIT_FRAMEWORK_LOG_H
