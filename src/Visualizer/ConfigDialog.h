#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedWidget>

class QListWidget;
class QListWidgetItem;
class QStackedWidget;

class ConfigDialog : public QDialog
{
    Q_OBJECT

    public:
        ConfigDialog(QWidget* parent = 0);

    public slots:
        void changePage(QListWidgetItem *current, QListWidgetItem *previous);

    private:
        void createIcons();

        QListWidget *pContentsWidget;
        QStackedWidget *pPagesWidget;
};

#endif
