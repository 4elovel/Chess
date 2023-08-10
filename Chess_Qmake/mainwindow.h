#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include "ui_mainwindow.h"
#include <QMainWindow>
#include <vector>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <QAudioOutput>
#include <QMediaPlayer>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void refresh_board();
    void make_turn(int x,int y);
    void fromCordsToBtn(int x,int y,QPushButton*& btn);
    int isColorSame(int num1,int num2);
    bool isCheck(QPair<int,int> pos);
    bool isInDanger(QPair<int,int> pos);
    std::vector<QPair<int,int>> isCheckPosition(QPair<int,int> pos);
private slots:

    void on_A8_clicked(){make_turn(0,0);}
    void on_A7_clicked(){make_turn(1,0);}
    void on_A6_clicked(){make_turn(2,0);}
    void on_A5_clicked(){make_turn(3,0);}
    void on_A4_clicked(){make_turn(4,0);}
    void on_A3_clicked(){make_turn(5,0);}
    void on_A2_clicked(){make_turn(6,0);}
    void on_A1_clicked(){make_turn(7,0);}

    void on_B8_clicked(){make_turn(0,1);}
    void on_B7_clicked(){make_turn(1,1);}
    void on_B6_clicked(){make_turn(2,1);}
    void on_B5_clicked(){make_turn(3,1);}
    void on_B4_clicked(){make_turn(4,1);}
    void on_B3_clicked(){make_turn(5,1);}
    void on_B2_clicked(){make_turn(6,1);}
    void on_B1_clicked(){make_turn(7,1);}

    void on_C8_clicked(){make_turn(0,2);}
    void on_C7_clicked(){make_turn(1,2);}
    void on_C6_clicked(){make_turn(2,2);}
    void on_C5_clicked(){make_turn(3,2);}
    void on_C4_clicked(){make_turn(4,2);}
    void on_C3_clicked(){make_turn(5,2);}
    void on_C2_clicked(){make_turn(6,2);}
    void on_C1_clicked(){make_turn(7,2);}

    void on_D8_clicked(){make_turn(0,3);}
    void on_D7_clicked(){make_turn(1,3);}
    void on_D6_clicked(){make_turn(2,3);}
    void on_D5_clicked(){make_turn(3,3);}
    void on_D4_clicked(){make_turn(4,3);}
    void on_D3_clicked(){make_turn(5,3);}
    void on_D2_clicked(){make_turn(6,3);}
    void on_D1_clicked(){make_turn(7,3);}

    void on_E8_clicked(){make_turn(0,4);}
    void on_E7_clicked(){make_turn(1,4);}
    void on_E6_clicked(){make_turn(2,4);}
    void on_E5_clicked(){make_turn(3,4);}
    void on_E4_clicked(){make_turn(4,4);}
    void on_E3_clicked(){make_turn(5,4);}
    void on_E2_clicked(){make_turn(6,4);}
    void on_E1_clicked(){make_turn(7,4);}

    void on_F8_clicked(){make_turn(0,5);}
    void on_F7_clicked(){make_turn(1,5);}
    void on_F6_clicked(){make_turn(2,5);}
    void on_F5_clicked(){make_turn(3,5);}
    void on_F4_clicked(){make_turn(4,5);}
    void on_F3_clicked(){make_turn(5,5);}
    void on_F2_clicked(){make_turn(6,5);}
    void on_F1_clicked(){make_turn(7,5);}

    void on_G8_clicked(){make_turn(0,6);}
    void on_G7_clicked(){make_turn(1,6);}
    void on_G6_clicked(){make_turn(2,6);}
    void on_G5_clicked(){make_turn(3,6);}
    void on_G4_clicked(){make_turn(4,6);}
    void on_G3_clicked(){make_turn(5,6);}
    void on_G2_clicked(){make_turn(6,6);}
    void on_G1_clicked(){make_turn(7,6);}

    void on_H8_clicked(){make_turn(0,7);}
    void on_H7_clicked(){make_turn(1,7);}
    void on_H6_clicked(){make_turn(2,7);}
    void on_H5_clicked(){make_turn(3,7);}
    void on_H4_clicked(){make_turn(4,7);}
    void on_H3_clicked(){make_turn(5,7);}
    void on_H2_clicked(){make_turn(6,7);}
    void on_H1_clicked(){make_turn(7,7);}


    void on_reset_triggered();

private:
    QPushButton *btn_ptr;
    Ui::MainWindow *ui;
    QPair<int,int> choice1;
    int fig_ch1;
    QPair<int,int> w_king_pos;
    QPair<int,int> b_king_pos;
    bool color_ch1=false;
    bool white_turn=true;
    bool leaver= false;
    bool rook70HasTurn=false,rook77HasTurn=false,rook00HasTurn=false,rook07HasTurn=false;
    bool wKingHasTurn=false, bKingHasTurn=false;
    QMediaPlayer player;
    QAudioOutput audioOutput;
    QPair<int,int> last_turn;
    QMessageBox msg;

    int board[8][8]={
        {-2,-3,-4,-5,-6,-4,-3,-2},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1},
        {2,3,4,5,6,4,3,2}
    };;
};
#endif // MAINWINDOW_H
