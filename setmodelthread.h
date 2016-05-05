#ifndef SETMODELTHREAD_H
#define SETMODELTHREAD_H

#include <QThread>

#include <QDomDocument>
#include <QString>

class DomModel;

class SetModelThread : public QThread
{
    Q_OBJECT
public:
    explicit SetModelThread(QObject *parent = 0);
    ~SetModelThread();

    DomModel *getModel() {
        return model;
    }

    void setTarget(QDomDocument&, const QString&);

private:
    DomModel *model;

    QDomDocument *document;
    QString filePath;

protected:
    virtual void run();

signals:
    void setModelOvered();

public slots:

};

#endif // SETMODELTHREAD_H
