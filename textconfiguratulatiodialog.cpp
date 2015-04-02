#include "textconfiguratulatiodialog.h"
#include "ui_textconfiguratulatiodialog.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>


///В данном классе реализуется окно «поздравление»


TextCongratulationDialog::TextCongratulationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextCongratulationDialog)
{
    ui->setupUi(this);
    connect(this->ui->okSaveCongratulationButton, SIGNAL(clicked()), this, SLOT(okSaveTextCongratulation()));
    connect(this->ui->cancelButton ,SIGNAL(clicked()), this, SLOT(cancelCloseTextCongratulation()));
    connect(this->ui->choiceListPattern, SIGNAL(currentIndexChanged(int)), this, SLOT(getCongratulationText(int)));
    on_openTextCongratulationDialog();
}



void TextCongratulationDialog::changeEvent(QEvent *apcEvt)
{
    if(apcEvt->type()== QEvent::LanguageChange)
    {
        ui->congratulationGroup->setTitle(tr("Шаблон текста поздравления"));
        ui->txtChoosePattern->setText(tr("Выберете шаблон:"));
        ui->txtPattern->setText(tr("Текст выбранного шаблона:"));
        ui->cancelButton->setText(tr("Отмена"));
    }
}

TextCongratulationDialog::~TextCongratulationDialog()
{
    delete ui;
}

void TextCongratulationDialog::okSaveTextCongratulation()
{
    close();
}

void TextCongratulationDialog::cancelCloseTextCongratulation()
{
    close();

}

void TextCongratulationDialog::getCongratulationText(const int arg1)
{
    /// get congratulation text for differnt group of people
    QString q = DBManager::getInstance()->getTextFor(arg1);
    ui->displayPattern->setText(q);
}

void TextCongratulationDialog::on_openTextCongratulationDialog()
{
/*    // получить модель для combobox
    ui->choiceListPattern->setModel(DBManager::getInstance()->listTextCongr());
    // получить тексты
    on_choiceListPattern_activated(0);
    */
}
