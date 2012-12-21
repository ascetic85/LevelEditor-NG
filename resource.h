#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>

class Resource : public QObject
{
    Q_OBJECT
public:
    explicit Resource(QObject *parent = 0);

    void setResource(QString& dir);

    QString directory();

    /**
     * @brief file
     * @param id    : "res:file" | "file"
     * @return res/file or file or ...
     *
     * - lower case, please
     */
    QString file(QString id);

protected:
    QString m_resDir;
};

#endif // RESOURCE_H
