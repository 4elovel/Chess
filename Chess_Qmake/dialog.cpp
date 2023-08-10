#include "dialog.h"
#include "ui_dialog.h"
#include "globals.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    if(ui->queen->isChecked()) g_pawn_choice=5;
    if(ui->rook->isChecked()) g_pawn_choice=2;
    if(ui->knight->isChecked()) g_pawn_choice=3;
    if(ui->bishop->isChecked()) g_pawn_choice=4;
    this->hide();
}

