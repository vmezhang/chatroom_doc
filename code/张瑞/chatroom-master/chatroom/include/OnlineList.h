#ifndef ONLINELIST_H_
#define ONLINELIST_H_

#include <QTableWidget>

class OnlineList : public QTableWidget
{
    Q_OBJECT
public:
    OnlineList();
    ~OnlineList();

    void createViewTitle();
    void insertUserInfo(QString nickname, QString hostname, QString ipaddr);
    void removeUserInfo(QString hostname);
};

#endif // ONLINELIST_H_
