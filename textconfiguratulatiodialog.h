#ifndef TEXTCONGRATULATIONDIALOG_H
#define TEXTCONGRATULATIONDIALOG_H

#include <QDialog>
#include <dbmanager.h>
namespace Ui {
class TextCongratulationDialog;
}

class TextCongratulationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextCongratulationDialog(QWidget *parent = 0);
    ~TextCongratulationDialog();

private slots:
    void okSaveTextCongratulation();

    void cancelCloseTextCongratulation();

    void getCongratulationText(int arg1);

    void on_openTextCongratulationDialog();

protected:
    void changeEvent(QEvent *apcEvt);

private:
    Ui::TextCongratulationDialog *ui;

};

#endif // TEXTCONGRATULATIONDIALOG_H
