#include "dialog2.h"
#include "ui_dialog2.h"
#include "globals.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::on_pushButton_clicked()
{
    if(ui->queen->isChecked()) g_pawn_choice=-5;
    if(ui->rook->isChecked()) g_pawn_choice=-2;
    if(ui->knight->isChecked()) g_pawn_choice=-3;
    if(ui->bishop->isChecked()) g_pawn_choice=-4;
    this->hide();
}

