#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <iostream>
#include <QPair>
#include "dialog.h"
#include "dialog2.h"
#include "globals.h"
#include <QAudioOutput>
#include <QMediaPlayer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    const QSize s(928,950); //928,950
    QWidget::setFixedSize(s);
    w_king_pos.first=7;
    w_king_pos.second=4;
    b_king_pos.first=0;
    b_king_pos.second=4;
    msg.setText("Check!");
    refresh_board();
    player.setAudioOutput(&audioOutput);
    player.setSource(QUrl("qrc:/sounds/game-start.mp3"));
    player.play();

}

void MainWindow::refresh_board(){

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::isColorSame(int num1,int num2){
    if((num1>0 && num2>0) || (num1<0 && num2<0) ) return 1;
    if((num1>0 && num2<0) || (num1<0 && num2>0) ) return -1;
    return 0;
}

void MainWindow::fromCordsToBtn(int x,int y,QPushButton*& btn){
    if(x==0 && y==0) btn = ui->A8;
    else if(x==0 && y==1) btn = ui->B8;
    else if(x==0 && y==2) btn = ui->C8;
    else if(x==0 && y==3) btn = ui->D8;
    else if(x==0 && y==4) btn = ui->E8;
    else if(x==0 && y==5) btn = ui->F8;
    else if(x==0 && y==6) btn = ui->G8;
    else if(x==0 && y==7) btn = ui->H8;

    else if(x==1 && y==0) btn = ui->A7;
    else if(x==1 && y==1) btn = ui->B7;
    else if(x==1 && y==2) btn = ui->C7;
    else if(x==1 && y==3) btn = ui->D7;
    else if(x==1 && y==4) btn = ui->E7;
    else if(x==1 && y==5) btn = ui->F7;
    else if(x==1 && y==6) btn = ui->G7;
    else if(x==1 && y==7) btn = ui->H7;

    else if(x==2 && y==0) btn = ui->A6;
    else if(x==2 && y==1) btn = ui->B6;
    else if(x==2 && y==2) btn = ui->C6;
    else if(x==2 && y==3) btn = ui->D6;
    else if(x==2 && y==4) btn = ui->E6;
    else if(x==2 && y==5) btn = ui->F6;
    else if(x==2 && y==6) btn = ui->G6;
    else if(x==2 && y==7) btn = ui->H6;

    else if(x==3 && y==0) btn = ui->A5;
    else if(x==3 && y==1) btn = ui->B5;
    else if(x==3 && y==2) btn = ui->C5;
    else if(x==3 && y==3) btn = ui->D5;
    else if(x==3 && y==4) btn = ui->E5;
    else if(x==3 && y==5) btn = ui->F5;
    else if(x==3 && y==6) btn = ui->G5;
    else if(x==3 && y==7) btn = ui->H5;

    else if(x==4 && y==0) btn = ui->A4;
    else if(x==4 && y==1) btn = ui->B4;
    else if(x==4 && y==2) btn = ui->C4;
    else if(x==4 && y==3) btn = ui->D4;
    else if(x==4 && y==4) btn = ui->E4;
    else if(x==4 && y==5) btn = ui->F4;
    else if(x==4 && y==6) btn = ui->G4;
    else if(x==4 && y==7) btn = ui->H4;

    else if(x==5 && y==0) btn = ui->A3;
    else if(x==5 && y==1) btn = ui->B3;
    else if(x==5 && y==2) btn = ui->C3;
    else if(x==5 && y==3) btn = ui->D3;
    else if(x==5 && y==4) btn = ui->E3;
    else if(x==5 && y==5) btn = ui->F3;
    else if(x==5 && y==6) btn = ui->G3;
    else if(x==5 && y==7) btn = ui->H3;

    else if(x==6 && y==0) btn = ui->A2;
    else if(x==6 && y==1) btn = ui->B2;
    else if(x==6 && y==2) btn = ui->C2;
    else if(x==6 && y==3) btn = ui->D2;
    else if(x==6 && y==4) btn = ui->E2;
    else if(x==6 && y==5) btn = ui->F2;
    else if(x==6 && y==6) btn = ui->G2;
    else if(x==6 && y==7) btn = ui->H2;

    else if(x==7 && y==0) btn = ui->A1;
    else if(x==7 && y==1) btn = ui->B1;
    else if(x==7 && y==2) btn = ui->C1;
    else if(x==7 && y==3) btn = ui->D1;
    else if(x==7 && y==4) btn = ui->E1;
    else if(x==7 && y==5) btn = ui->F1;
    else if(x==7 && y==6) btn = ui->G1;
    else if(x==7 && y==7) btn = ui->H1;
}



void MainWindow::make_turn(int x,int y){


    int fig = board[x][y];
    std::vector<QPair<int,int>> posible;

    bool color = false;
    if(fig>0)color = true;
    if(!leaver){
        if(fig==0) {
            ui->statusbar->showMessage("");
            return;
        }
        if(color!=white_turn){
            ui->statusbar->showMessage("Not your turn!");
            if(ui->statusbar->currentMessage()=="Not your turn!"){
                if(player.source() != QUrl("qrc:/sounds/illegal.mp3"))
                    player.setSource(QUrl("qrc:/sounds/illegal.mp3"));
                player.play();
            }
            return;
        }
        color_ch1=color;
        choice1.first=x;
        choice1.second=y;
        fig_ch1=fig;
        leaver =true;
        return;
    }
    if(leaver){
        leaver = false;
        QPair<int,int> choice2;
        choice2.first=x;
        choice2.second=y;
        switch (abs(board[choice1.first][choice1.second])) {
        case 1://pawn
            ui->statusbar->showMessage("Turn is wrong!");
            if(true){

                if(color_ch1){

                    if(choice1.first==3 && board[last_turn.first][last_turn.second]==-1){
                        if(last_turn.second==choice1.second-1 && choice2.first==choice1.first-1 && choice2.second==choice1.second-1){

                            board[last_turn.first][last_turn.second]=0;
                            fromCordsToBtn(last_turn.first,last_turn.second,btn_ptr);
                            btn_ptr->setIcon(QIcon());
                            board[choice1.first][choice1.second]=0;
                            fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                            btn_ptr->setIcon(QIcon());
                            board[choice2.first][choice2.second]=1;
                            fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                            btn_ptr->setIcon(QIcon(":/images/wpawn.png"));
                            refresh_board();
                            ui->statusbar->showMessage("Turn is successful!");
                            if(player.source() != QUrl("qrc:/sounds/capture.mp3"))
                                player.setSource(QUrl("qrc:/sounds/capture.mp3"));
                            player.play();
                            last_turn = choice2;
                            white_turn = !white_turn;
                        }

                        if(last_turn.second==choice1.second+1 && choice2.first==choice1.first-1 && choice2.second==choice1.second+1){

                            board[last_turn.first][last_turn.second]=0;
                            fromCordsToBtn(last_turn.first,last_turn.second,btn_ptr);
                            btn_ptr->setIcon(QIcon());
                            board[choice1.first][choice1.second]=0;
                            fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                            btn_ptr->setIcon(QIcon());
                            board[choice2.first][choice2.second]=1;
                            fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                            btn_ptr->setIcon(QIcon(":/images/wpawn.png"));
                            refresh_board();
                            ui->statusbar->showMessage("Turn is successful!");
                            if(player.source() != QUrl("qrc:/sounds/capture.mp3"))
                                player.setSource(QUrl("qrc:/sounds/capture.mp3"));
                            player.play();
                            last_turn = choice2;
                            white_turn = !white_turn;
                        }

                    }


                    if(choice1.first-1==choice2.first && choice1.second==choice2.second) posible.push_back(choice2);
                    else if(choice1.first==6 && choice2.first ==4 && choice1.second==choice2.second) posible.push_back(choice2);
                    if(board[choice1.first-1][choice1.second-1]<0) posible.push_back(QPair<int,int>(choice1.first-1,choice1.second-1));
                    if(board[choice1.first-1][choice1.second+1]<0) posible.push_back(QPair<int,int>(choice1.first-1,choice1.second+1));
                }
                if(!color_ch1){

                    if(choice1.first==4 && board[last_turn.first][last_turn.second]==1){
                        if(last_turn.second==choice1.second-1 && choice2.first==choice1.first+1 && choice2.second==choice1.second-1){

                            board[last_turn.first][last_turn.second]=0;
                            fromCordsToBtn(last_turn.first,last_turn.second,btn_ptr);
                            btn_ptr->setIcon(QIcon());
                            board[choice1.first][choice1.second]=0;
                            fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                            btn_ptr->setIcon(QIcon());
                            board[choice2.first][choice2.second]=-1;
                            fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                            btn_ptr->setIcon(QIcon(":/images/bpawn.png"));
                            refresh_board();
                            ui->statusbar->showMessage("Turn is successful!");
                            if(player.source() != QUrl("qrc:/sounds/capture.mp3"))
                                player.setSource(QUrl("qrc:/sounds/capture.mp3"));
                            player.play();
                            last_turn = choice2;
                            white_turn = !white_turn;
                        }

                        if(last_turn.second==choice1.second+1 && choice2.first==choice1.first+1 && choice2.second==choice1.second+1){

                            board[last_turn.first][last_turn.second]=0;
                            fromCordsToBtn(last_turn.first,last_turn.second,btn_ptr);
                            btn_ptr->setIcon(QIcon());
                            board[choice1.first][choice1.second]=0;
                            fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                            btn_ptr->setIcon(QIcon());
                            board[choice2.first][choice2.second]=-1;
                            fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                            btn_ptr->setIcon(QIcon(":/images/bpawn.png"));
                            refresh_board();
                            ui->statusbar->showMessage("Turn is successful!");
                            if(player.source() != QUrl("qrc:/sounds/capture.mp3"))
                                player.setSource(QUrl("qrc:/sounds/capture.mp3"));
                            player.play();
                            last_turn = choice2;
                            white_turn = !white_turn;
                        }

                    }

                    if(choice1.first+1==choice2.first && choice1.second==choice2.second) posible.push_back(choice2);
                    else if(choice1.first==1 && choice2.first ==3 && choice1.second==choice2.second) posible.push_back(choice2);
                    if(board[choice1.first+1][choice1.second-1]>0) posible.push_back(QPair<int,int>(choice1.first+1,choice1.second-1));
                    if(board[choice1.first+1][choice1.second+1]>0) posible.push_back(QPair<int,int>(choice1.first+1,choice1.second+1));
                }
            }
            for (int i = 0; i < posible.size(); ++i) { //res

                if(posible[i]==choice2){

                    if(fig==0 || isColorSame(fig,fig_ch1)){ //res
                        int save = board[choice2.first][choice2.second];
                        fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                        board[choice2.first][choice2.second]= board[choice1.first][choice1.second];
                        board[choice1.first][choice1.second]=0;
                        if(color_ch1 && isCheck(w_king_pos)){
                            board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                            board[choice2.first][choice2.second] = save;

                                if(player.source() != QUrl("qrc:/sounds/illegal.mp3"))
                                    player.setSource(QUrl("qrc:/sounds/illegal.mp3"));
                                player.play();

                            ui->statusbar->showMessage("Turn is wrong!");
                            return;
                        }else if(!color_ch1 && isCheck(b_king_pos)){
                            board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                            board[choice2.first][choice2.second] = save;

                                if(player.source() != QUrl("qrc:/sounds/illegal.mp3"))
                                    player.setSource(QUrl("qrc:/sounds/illegal.mp3"));
                                player.play();

                            ui->statusbar->showMessage("Turn is wrong!");
                            return;
                        }
                        if(color_ch1){
                            if(choice2.first==0){
                                Dialog d;
                                d.exec();

                                board[choice2.first][choice2.second]=g_pawn_choice;
                                switch (g_pawn_choice) {
                                case 2:
                                    btn_ptr->setIcon(QIcon(":/images/wrook.png"));
                                    break;
                                case 3:
                                    btn_ptr->setIcon(QIcon(":/images/whose.png"));
                                    break;
                                case 4:
                                    btn_ptr->setIcon(QIcon(":/images/wbishop.png"));
                                    break;
                                case 5:
                                    btn_ptr->setIcon(QIcon(":/images/wqeen.png"));
                                    break;
                                }
                            }else{
                            btn_ptr->setIcon(QIcon(":/images/wpawn.png"));
                            }
                        }
                        else if(!color_ch1){
                            if(choice2.first==7){

                            Dialog2 d;
                            d.exec();

                            board[choice2.first][choice2.second]=g_pawn_choice;
                            switch (g_pawn_choice) {
                            case -2:
                                    btn_ptr->setIcon(QIcon(":/images/brook.png"));
                                    break;
                            case -3:
                                    btn_ptr->setIcon(QIcon(":/images/bhorse.png"));
                                    break;
                            case -4:
                                    btn_ptr->setIcon(QIcon(":/images/bbishop.png"));
                                    break;
                            case -5:
                                    btn_ptr->setIcon(QIcon(":/images/bqeen.png"));
                                    break;
                            }

                            }else{
                            btn_ptr->setIcon(QIcon(":/images/bpawn.png"));
                            }
                        }
                        fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                        btn_ptr->setIcon(QIcon());
                        refresh_board();
                        if(player.source() != QUrl("qrc:/sounds/move.mp3"))
                            player.setSource(QUrl("qrc:/sounds/move.mp3"));
                        player.play();
                        ui->statusbar->showMessage("Turn is successful!");
                        last_turn = choice2;
                        white_turn = !white_turn;
                        break;
                    }

                }

            }
            break;
        case 2: //rook

            for (int i = choice1.first+1; i < 8; ++i) { //down
                if(board[i][choice1.second] == 0 ){
                    posible.push_back(QPair<int,int>(i,choice1.second));
                }
                else if(isColorSame(board[i][choice1.second],fig_ch1) == 1){
                    break;
                }
                else if(isColorSame(board[i][choice1.second],fig_ch1) == -1){
                    posible.push_back(QPair<int,int>(i,choice1.second));

                    break;
                }
            }

            for (int i = choice1.first-1; i > -1; --i) { //up
                if(board[i][choice1.second] == 0 ){
                    posible.push_back(QPair<int,int>(i,choice1.second));
                }
                else if(isColorSame(board[i][choice1.second],fig_ch1) == 1){
                    break;
                }
                else if(isColorSame(board[i][choice1.second],fig_ch1) == -1){
                    posible.push_back(QPair<int,int>(i,choice1.second));
                    break;
                }
            }

            for (int i = choice1.second+1; i < 8; ++i) { // right
                if(board[choice1.first][i] == 0 ){
                    posible.push_back(QPair<int,int>(choice1.first,i));
                }
                else if(isColorSame(board[choice1.first][i],fig_ch1) == 1){
                    break;
                }
                else if(isColorSame(board[choice1.first][i],fig_ch1) == -1){
                    posible.push_back(QPair<int,int>(choice1.first,i));
                    break;
                }
            }

            for (int i = choice1.second-1; i > -1; --i) { // left
                if(board[choice1.first][i] == 0 ){
                    posible.push_back(QPair<int,int>(choice1.first,i));
                }
                else if(isColorSame(board[choice1.first][i],fig_ch1) == 1){
                    break;
                }
                else if(isColorSame(board[choice1.first][i],fig_ch1) == -1){
                    posible.push_back(QPair<int,int>(choice1.first,i));
                    break;
                }

            }
            for (int i = 0; i < posible.size(); ++i) { //res
                if(posible[i]==choice2){
                    int save = board[choice2.first][choice2.second];
                    fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                    board[choice2.first][choice2.second]= board[choice1.first][choice1.second];
                    board[choice1.first][choice1.second]=0;
                    if(color_ch1 && isCheck(w_king_pos)){
                        board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                        board[choice2.first][choice2.second] = save;
                        ui->statusbar->showMessage("Turn is wrong!");
                        return;
                    }else if(!color_ch1 && isCheck(b_king_pos)){
                        board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                        board[choice2.first][choice2.second] = save;
                        ui->statusbar->showMessage("Turn is wrong!");
                        return;
                    }
                    if(color_ch1){
                        btn_ptr->setIcon(QIcon(":/images/wrook.png"));
                    }
                    else    btn_ptr->setIcon(QIcon(":/images/brook.png"));
                    fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                    btn_ptr->setIcon(QIcon());
                    refresh_board();
                    ui->statusbar->showMessage("Turn is successful!");
                    if(player.source() != QUrl("qrc:/sounds/move.mp3"))
                        player.setSource(QUrl("qrc:/sounds/move.mp3"));
                    player.play();
                    white_turn = !white_turn;
                    if(choice1.first==7 && choice1.second==0) rook70HasTurn=true;
                    if(choice1.first==7 && choice1.second==7) rook77HasTurn=true;
                    if(choice1.first==0 && choice1.second==0) rook00HasTurn=true;
                    if(choice1.first==0 && choice1.second==7) rook07HasTurn=true;
                    break;
                }
                ui->statusbar->showMessage("Turn is wrong!");
            }

            break;
        case 3://knight

            if(choice2.first== choice1.first+2 && choice2.second==choice1.second+1){
                if(fig==0 || isColorSame(fig,fig_ch1)){
                    int save = board[choice2.first][choice2.second];
                    fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                    board[choice2.first][choice2.second]= board[choice1.first][choice1.second];
                    board[choice1.first][choice1.second]=0;

                    if(color_ch1 && isCheck(w_king_pos)){
                        board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                        board[choice2.first][choice2.second] = save;
                        ui->statusbar->showMessage("Turn is wrong!");
                        return;
                    }else if(!color_ch1 && isCheck(b_king_pos)){
                        board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                        board[choice2.first][choice2.second] = save;
                        ui->statusbar->showMessage("Turn is wrong!");
                        return;
                    }

                    if(color_ch1){
                        btn_ptr->setIcon(QIcon(":/images/whose.png"));
                    }
                    else    btn_ptr->setIcon(QIcon(":/images/bhorse.png"));
                    fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                    btn_ptr->setIcon(QIcon());
                    refresh_board();
                    ui->statusbar->showMessage("Turn is successful!");
                    if(player.source() != QUrl("qrc:/sounds/move.mp3"))
                        player.setSource(QUrl("qrc:/sounds/move.mp3"));
                    player.play();
                    white_turn = !white_turn;
                    break;
                }
            }
            else if(choice2.first== choice1.first+1 && choice2.second==choice1.second-2){
                if(fig==0 || isColorSame(fig,fig_ch1)){
                    fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                    board[choice2.first][choice2.second]= board[choice1.first][choice1.second];
                    board[choice1.first][choice1.second]=0;
                    if(color_ch1){
                        btn_ptr->setIcon(QIcon(":/images/whose.png"));
                    }
                    else    btn_ptr->setIcon(QIcon(":/images/bhorse.png"));
                    fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                    btn_ptr->setIcon(QIcon());
                    refresh_board();
                    ui->statusbar->showMessage("Turn is successful!");
                    if(player.source() != QUrl("qrc:/sounds/move.mp3"))
                        player.setSource(QUrl("qrc:/sounds/move.mp3"));
                    player.play();
                    white_turn = !white_turn;
                    break;
                }
            }
            else if(choice2.first== choice1.first-1 && choice2.second==choice1.second-2){
                if(fig==0 || isColorSame(fig,fig_ch1)){
                    int save = board[choice2.first][choice2.second];
                    fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                    board[choice2.first][choice2.second]= board[choice1.first][choice1.second];
                    board[choice1.first][choice1.second]=0;
                    if(color_ch1 && isCheck(w_king_pos)){
                        board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                        board[choice2.first][choice2.second] = save;
                        ui->statusbar->showMessage("Turn is wrong!");
                        return;
                    }else if(!color_ch1 && isCheck(b_king_pos)){
                        board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                        board[choice2.first][choice2.second] = save;
                        ui->statusbar->showMessage("Turn is wrong!");
                        return;
                    }
                    if(color_ch1){
                        btn_ptr->setIcon(QIcon(":/images/whose.png"));
                    }
                    else    btn_ptr->setIcon(QIcon(":/images/bhorse.png"));
                    fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                    btn_ptr->setIcon(QIcon());
                    refresh_board();
                    ui->statusbar->showMessage("Turn is successful!");
                    if(player.source() != QUrl("qrc:/sounds/move.mp3"))
                        player.setSource(QUrl("qrc:/sounds/move.mp3"));
                    player.play();
                    white_turn = !white_turn;
                    break;
                }
            }
            else if(choice2.first== choice1.first-2 && choice2.second==choice1.second-1){
                if(fig==0 || isColorSame(fig,fig_ch1)){
                    int save = board[choice2.first][choice2.second];
                    fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                    board[choice2.first][choice2.second]= board[choice1.first][choice1.second];
                    board[choice1.first][choice1.second]=0;
                    if(color_ch1 && isCheck(w_king_pos)){
                        board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                        board[choice2.first][choice2.second] = save;
                        ui->statusbar->showMessage("Turn is wrong!");
                        return;
                    }else if(!color_ch1 && isCheck(b_king_pos)){
                        board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                        board[choice2.first][choice2.second] = save;
                        ui->statusbar->showMessage("Turn is wrong!");
                        return;
                    }
                    if(color_ch1){
                        btn_ptr->setIcon(QIcon(":/images/whose.png"));
                    }
                    else    btn_ptr->setIcon(QIcon(":/images/bhorse.png"));
                    fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                    btn_ptr->setIcon(QIcon());
                    refresh_board();
                    ui->statusbar->showMessage("Turn is successful!");
                    if(player.source() != QUrl("qrc:/sounds/move.mp3"))
                        player.setSource(QUrl("qrc:/sounds/move.mp3"));
                    player.play();
                    white_turn = !white_turn;
                    break;
                }
            }
            else if(choice2.first== choice1.first+1 && choice2.second==choice1.second+2){
                if(fig==0 || isColorSame(fig,fig_ch1)){
                    int save = board[choice2.first][choice2.second];
                    fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                    board[choice2.first][choice2.second]= board[choice1.first][choice1.second];
                    board[choice1.first][choice1.second]=0;
                    if(color_ch1 && isCheck(w_king_pos)){
                        board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                        board[choice2.first][choice2.second] = save;
                        ui->statusbar->showMessage("Turn is wrong!");
                        return;
                    }else if(!color_ch1 && isCheck(b_king_pos)){
                        board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                        board[choice2.first][choice2.second] = save;
                        ui->statusbar->showMessage("Turn is wrong!");
                        return;
                    }
                    if(color_ch1){
                        btn_ptr->setIcon(QIcon(":/images/whose.png"));
                    }
                    else    btn_ptr->setIcon(QIcon(":/images/bhorse.png"));
                    fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                    btn_ptr->setIcon(QIcon());
                    refresh_board();
                    ui->statusbar->showMessage("Turn is successful!");
                    if(player.source() != QUrl("qrc:/sounds/move.mp3"))
                        player.setSource(QUrl("qrc:/sounds/move.mp3"));
                    player.play();
                    white_turn = !white_turn;
                    break;
                }
            }
            else if(choice2.first== choice1.first-2 && choice2.second==choice1.second+1){
                if(fig==0 || isColorSame(fig,fig_ch1)){
                    int save = board[choice2.first][choice2.second];
                    fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                    board[choice2.first][choice2.second]= board[choice1.first][choice1.second];
                    board[choice1.first][choice1.second]=0;
                    if(color_ch1 && isCheck(w_king_pos)){
                        board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                        board[choice2.first][choice2.second] = save;
                        ui->statusbar->showMessage("Turn is wrong!");
                        return;
                    }else if(!color_ch1 && isCheck(b_king_pos)){
                        board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                        board[choice2.first][choice2.second] = save;
                        ui->statusbar->showMessage("Turn is wrong!");
                        return;
                    }
                    if(color_ch1){
                        btn_ptr->setIcon(QIcon(":/images/whose.png"));
                    }
                    else    btn_ptr->setIcon(QIcon(":/images/bhorse.png"));
                    fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                    btn_ptr->setIcon(QIcon());
                    refresh_board();
                    ui->statusbar->showMessage("Turn is successful!");
                    if(player.source() != QUrl("qrc:/sounds/move.mp3"))
                        player.setSource(QUrl("qrc:/sounds/move.mp3"));
                    player.play();
                    white_turn = !white_turn;
                    break;
                }
            }
            else if(choice2.first== choice1.first-1 && choice2.second==choice1.second+2){
                if(fig==0 || isColorSame(fig,fig_ch1)){
                    int save = board[choice2.first][choice2.second];
                    fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                    board[choice2.first][choice2.second]= board[choice1.first][choice1.second];
                    board[choice1.first][choice1.second]=0;
                    if(color_ch1 && isCheck(w_king_pos)){
                        board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                        board[choice2.first][choice2.second] = save;
                        ui->statusbar->showMessage("Turn is wrong!");
                        return;
                    }else if(!color_ch1 && isCheck(b_king_pos)){
                        board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                        board[choice2.first][choice2.second] = save;
                        ui->statusbar->showMessage("Turn is wrong!");
                        return;
                    }
                    if(color_ch1){
                        btn_ptr->setIcon(QIcon(":/images/whose.png"));
                    }
                    else    btn_ptr->setIcon(QIcon(":/images/bhorse.png"));
                    fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                    btn_ptr->setIcon(QIcon());
                    refresh_board();
                    ui->statusbar->showMessage("Turn is successful!");
                    if(player.source() != QUrl("qrc:/sounds/move.mp3"))
                        player.setSource(QUrl("qrc:/sounds/move.mp3"));
                    player.play();
                    white_turn = !white_turn;
                    break;
                }
            }
            else if(choice2.first== choice1.first+2 && choice2.second==choice1.second-1){
                if(fig==0 || isColorSame(fig,fig_ch1)){//res
                    int save = board[choice2.first][choice2.second];
                    fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                    board[choice2.first][choice2.second]= board[choice1.first][choice1.second];
                    board[choice1.first][choice1.second]=0;
                    if(color_ch1 && isCheck(w_king_pos)){
                        board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                        board[choice2.first][choice2.second] = save;
                        ui->statusbar->showMessage("Turn is wrong!");
                        return;
                    }else if(!color_ch1 && isCheck(b_king_pos)){
                        board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                        board[choice2.first][choice2.second] = save;
                        ui->statusbar->showMessage("Turn is wrong!");
                        return;
                    }
                    if(color_ch1){
                        btn_ptr->setIcon(QIcon(":/images/whose.png"));
                    }
                    else    btn_ptr->setIcon(QIcon(":/images/bhorse.png"));
                    fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                    btn_ptr->setIcon(QIcon());
                    refresh_board();
                    ui->statusbar->showMessage("Turn is successful!");
                    if(player.source() != QUrl("qrc:/sounds/move.mp3"))
                        player.setSource(QUrl("qrc:/sounds/move.mp3"));
                    player.play();
                    white_turn = !white_turn;
                    break;
                }
            }
            ui->statusbar->showMessage("Turn is wrong!");
            break;
        case 4://bishop
            for (int i = choice1.first+1,j = choice1.second-1; i < 8; ++i,j--) {//Left-down
                if(j==-1) break;
                    if(board[i][j]==0) posible.push_back(QPair<int,int>(i,j));
                    else if(isColorSame(board[i][j],fig_ch1)==-1){
                        posible.push_back(QPair<int,int>(i,j));
                        break;
                    }
                    else if(isColorSame(board[i][j],fig_ch1)==1){
                        break;

                }
            }
            for (int i = choice1.first-1, j = choice1.second+1; i > -1; --i,j++) {//right-up
                if(j==8) break;
                    if(board[i][j]==0) posible.push_back(QPair<int,int>(i,j));
                    else if(isColorSame(board[i][j],fig_ch1)==-1){
                        posible.push_back(QPair<int,int>(i,j));
                        break;
                    }
                    else if(isColorSame(board[i][j],fig_ch1)==1){
                        break;
                    }
                }
            for (int i = choice1.first-1,j = choice1.second-1; i > -1; --i,--j) {//left-up
                    if(j == -1) break;
                    if(board[i][j]==0) posible.push_back(QPair<int,int>(i,j));
                    else if(isColorSame(board[i][j],fig_ch1)==-1){
                        posible.push_back(QPair<int,int>(i,j));
                        break;
                    }
                    else if(isColorSame(board[i][j],fig_ch1)==1){
                        break;
                    }
                }
            for (int i = choice1.first+1,j = choice1.second+1; i < 8; ++i,++j) {//right-down
                    if(j == 8) break;
                    if(board[i][j]==0) posible.push_back(QPair<int,int>(i,j));
                    else if(isColorSame(board[i][j],fig_ch1)==-1){
                        posible.push_back(QPair<int,int>(i,j));
                        break;
                    }
                    else if(isColorSame(board[i][j],fig_ch1)==1){
                        break;
                    }
            }
            for (int i = 0; i < posible.size(); ++i) { //res
                if(posible[i]==choice2){

                    if(fig==0 || isColorSame(fig,fig_ch1)){ //res
                        int save = board[choice2.first][choice2.second];
                        fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                        board[choice2.first][choice2.second]= board[choice1.first][choice1.second];
                        board[choice1.first][choice1.second]=0;
                        if(color_ch1 && isCheck(w_king_pos)){
                            board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                            board[choice2.first][choice2.second] = save;
                            ui->statusbar->showMessage("Turn is wrong!");
                            return;
                        }else if(!color_ch1 && isCheck(b_king_pos)){
                            board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                            board[choice2.first][choice2.second] = save;
                            ui->statusbar->showMessage("Turn is wrong!");
                            return;
                        }
                        if(color_ch1){
                            btn_ptr->setIcon(QIcon(":/images/wbishop.png"));
                        }
                        else    btn_ptr->setIcon(QIcon(":/images/bbishop.png"));
                        fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                        btn_ptr->setIcon(QIcon());
                        refresh_board();
                        ui->statusbar->showMessage("Turn is successful!");
                        if(player.source() != QUrl("qrc:/sounds/move.mp3"))
                            player.setSource(QUrl("qrc:/sounds/move.mp3"));
                        player.play();
                        white_turn = !white_turn;
                        break;
                    }
                }
                ui->statusbar->showMessage("Turn is wrong!");
            }
            break;
        case 5://queen
            for (int i = choice1.first+1,j = choice1.second-1; i < 8; ++i,j--) {//Left-down
                if(j==-1) break;
                if(board[i][j]==0) posible.push_back(QPair<int,int>(i,j));
                else if(isColorSame(board[i][j],fig_ch1)==-1){
                    posible.push_back(QPair<int,int>(i,j));
                    break;
                }
                else if(isColorSame(board[i][j],fig_ch1)==1){
                    break;

                }
            }
            for (int i = choice1.first-1, j = choice1.second+1; i > -1; --i,j++) {//right-up
                if(j==8) break;
                if(board[i][j]==0) posible.push_back(QPair<int,int>(i,j));
                else if(isColorSame(board[i][j],fig_ch1)==-1){
                    posible.push_back(QPair<int,int>(i,j));
                    break;
                }
                else if(isColorSame(board[i][j],fig_ch1)==1){
                    break;
                }
            }
            for (int i = choice1.first-1,j = choice1.second-1; i > -1; --i,--j) {//left-up
                if(j == -1) break;
                if(board[i][j]==0) posible.push_back(QPair<int,int>(i,j));
                else if(isColorSame(board[i][j],fig_ch1)==-1){
                    posible.push_back(QPair<int,int>(i,j));
                    break;
                }
                else if(isColorSame(board[i][j],fig_ch1)==1){
                    break;
                }
            }
            for (int i = choice1.first+1,j = choice1.second+1; i < 8; ++i,++j) {//right-down
                if(j == 8) break;
                if(board[i][j]==0) posible.push_back(QPair<int,int>(i,j));
                else if(isColorSame(board[i][j],fig_ch1)==-1){
                    posible.push_back(QPair<int,int>(i,j));
                    break;
                }
                else if(isColorSame(board[i][j],fig_ch1)==1){
                    break;
                }
            }

            for (int i = choice1.first+1; i < 8; ++i) { //down
                if(board[i][choice1.second] == 0 ){
                    posible.push_back(QPair<int,int>(i,choice1.second));
                }
                else if(isColorSame(board[i][choice1.second],fig_ch1) == 1){
                    break;
                }
                else if(isColorSame(board[i][choice1.second],fig_ch1) == -1){
                    posible.push_back(QPair<int,int>(i,choice1.second));

                    break;
                }
            }

            for (int i = choice1.first-1; i > -1; --i) { //up
                if(board[i][choice1.second] == 0 ){
                    posible.push_back(QPair<int,int>(i,choice1.second));
                }
                else if(isColorSame(board[i][choice1.second],fig_ch1) == 1){
                    break;
                }
                else if(isColorSame(board[i][choice1.second],fig_ch1) == -1){
                    posible.push_back(QPair<int,int>(i,choice1.second));
                    break;
                }
            }

            for (int i = choice1.second+1; i < 8; ++i) { // right
                if(board[choice1.first][i] == 0 ){
                    posible.push_back(QPair<int,int>(choice1.first,i));
                }
                else if(isColorSame(board[choice1.first][i],fig_ch1) == 1){
                    break;
                }
                else if(isColorSame(board[choice1.first][i],fig_ch1) == -1){
                    posible.push_back(QPair<int,int>(choice1.first,i));
                    break;
                }
            }

            for (int i = choice1.second-1; i > -1; --i) { // left
                if(board[choice1.first][i] == 0 ){
                    posible.push_back(QPair<int,int>(choice1.first,i));
                }
                else if(isColorSame(board[choice1.first][i],fig_ch1) == 1){
                    break;
                }
                else if(isColorSame(board[choice1.first][i],fig_ch1) == -1){
                    posible.push_back(QPair<int,int>(choice1.first,i));
                    break;
                }

            }

            for (int i = 0; i < posible.size(); ++i) { //res
                if(posible[i]==choice2){

                    if(fig==0 || isColorSame(fig,fig_ch1)){ //res
                        int save = board[choice2.first][choice2.second];
                        fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                        board[choice2.first][choice2.second]= board[choice1.first][choice1.second];
                        board[choice1.first][choice1.second]=0;
                        if(color_ch1 && isCheck(w_king_pos)){
                            board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                            board[choice2.first][choice2.second] = save;
                            ui->statusbar->showMessage("Turn is wrong!");
                            return;
                        }else if(!color_ch1 && isCheck(b_king_pos)){
                            board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                            board[choice2.first][choice2.second] = save;
                            ui->statusbar->showMessage("Turn is wrong!");
                            return;
                        }
                        if(color_ch1){
                            btn_ptr->setIcon(QIcon(":/images/wqeen.png"));
                        }
                        else    btn_ptr->setIcon(QIcon(":/images/bqeen.png"));
                        fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                        btn_ptr->setIcon(QIcon());
                        refresh_board();
                        ui->statusbar->showMessage("Turn is successful!");
                        if(player.source() != QUrl("qrc:/sounds/move.mp3"))
                            player.setSource(QUrl("qrc:/sounds/move.mp3"));
                        player.play();
                        last_turn = choice2;
                        white_turn = !white_turn;
                        break;
                    }
                }
                ui->statusbar->showMessage("Turn is wrong!");
            }
            break;
        case 6://king
            //castling
            if(color_ch1 && !wKingHasTurn && !rook77HasTurn && board[7][5]==0 && board[7][6]==0 && board[7][7]==2 && choice2==QPair<int,int>(7,6) && !isCheck(w_king_pos)){
                board[7][4]=0;
                board[7][5]=6;
                if(!isCheck(QPair<int,int>(7,5))){
                    board[7][5]=0;
                    board[7][6]=6;
                    if(!isCheck(QPair<int,int>(7,6))){
                        board[7][5]=2;
                        board[7][7]=0;
                        fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                        btn_ptr->setIcon(QIcon(":/images/wking.png"));
                        fromCordsToBtn(7,5,btn_ptr);
                        btn_ptr->setIcon(QIcon(":/images/wrook.png"));
                        fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                        btn_ptr->setIcon(QIcon());
                        fromCordsToBtn(7,7,btn_ptr);
                        btn_ptr->setIcon(QIcon());
                        refresh_board();
                        white_turn = !white_turn;
                        ui->statusbar->showMessage("Turn is successful!");
                        if(player.source() != QUrl("qrc:/sounds/castle.mp3"))
                            player.setSource(QUrl("qrc:/sounds/castle.mp3"));
                        player.play();
                        break;

                    }else{
                        board[7][4]=6;
                        board[7][6]=0;
                    }
                }else{
                    board[7][4]=6;
                    board[7][5]=0;
                }
            }

            if(!color_ch1 && !bKingHasTurn && !rook07HasTurn && board[0][5]==0 && board[0][6]==0 && board[0][7]==2 && choice2==QPair<int,int>(0,6) && !isCheck(b_king_pos)){
                board[0][4]=0;
                board[0][5]=-6;
                if(!isCheck(QPair<int,int>(0,5))){
                    board[0][5]=0;
                    board[0][6]=-6;
                    if(!isCheck(QPair<int,int>(0,6))){
                        board[0][5]=-2;
                        board[0][7]=0;
                        fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                        btn_ptr->setIcon(QIcon(":/images/bking.png"));
                        fromCordsToBtn(0,5,btn_ptr);
                        btn_ptr->setIcon(QIcon(":/images/brook.png"));
                        fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                        btn_ptr->setIcon(QIcon());
                        fromCordsToBtn(0,7,btn_ptr);
                        btn_ptr->setIcon(QIcon());
                        refresh_board();
                        white_turn = !white_turn;
                        ui->statusbar->showMessage("Turn is successful!");
                        if(player.source() != QUrl("qrc:/sounds/castle.mp3"))
                            player.setSource(QUrl("qrc:/sounds/castle.mp3"));
                        player.play();
                        break;

                    }else{
                        board[0][4]=-6;
                        board[0][6]=0;
                    }
                }else{
                    board[0][4]=-6;
                    board[0][5]=0;
                }
            }

            if(color_ch1 && !wKingHasTurn && !rook70HasTurn && board[7][1]==0 && board[7][2]==0 && board[7][3]==0 && board[7][0]==2 && choice2==QPair<int,int>(7,2) && !isCheck(w_king_pos)){
                board[7][4]=0;
                board[7][3]=6;
                if(!isCheck(QPair<int,int>(7,3))){
                    board[7][3]=0;
                    board[7][2]=6;
                    if(!isCheck(QPair<int,int>(7,2))){
                        board[7][3]=2;
                        board[7][0]=0;
                        fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                        btn_ptr->setIcon(QIcon(":/images/wking.png"));
                        fromCordsToBtn(7,3,btn_ptr);
                        btn_ptr->setIcon(QIcon(":/images/wrook.png"));
                        fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                        btn_ptr->setIcon(QIcon());
                        fromCordsToBtn(7,0,btn_ptr);
                        btn_ptr->setIcon(QIcon());
                        refresh_board();
                        white_turn = !white_turn;
                        ui->statusbar->showMessage("Turn is successful!");
                        if(player.source() != QUrl("qrc:/sounds/castle.mp3"))
                            player.setSource(QUrl("qrc:/sounds/castle.mp3"));
                        player.play();
                        break;

                    }else{
                        board[7][4]=6;
                        board[7][2]=0;
                    }
                }else{
                    board[7][4]=6;
                    board[7][3]=0;
                }
            }

            if(!color_ch1 && !bKingHasTurn && !rook00HasTurn && board[0][1]==0 && board[0][2]==0 && board[0][3]==0 && board[0][0]==-2 && choice2==QPair<int,int>(0,2) && !isCheck(b_king_pos)){
                board[0][4]=0;
                board[0][3]=-6;
                if(!isCheck(QPair<int,int>(0,3))){
                    board[0][3]=0;
                    board[0][2]=-6;
                    if(!isCheck(QPair<int,int>(0,2))){
                        board[0][3]=-2;
                        board[0][0]=0;
                        fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                        btn_ptr->setIcon(QIcon(":/images/bking.png"));
                        fromCordsToBtn(0,3,btn_ptr);
                        btn_ptr->setIcon(QIcon(":/images/brook.png"));
                        fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                        btn_ptr->setIcon(QIcon());
                        fromCordsToBtn(0,0,btn_ptr);
                        btn_ptr->setIcon(QIcon());
                        refresh_board();
                        white_turn = !white_turn;
                        ui->statusbar->showMessage("Turn is successful!");
                        if(player.source() != QUrl("qrc:/sounds/castle.mp3"))
                            player.setSource(QUrl("qrc:/sounds/castle.mp3"));
                        player.play();
                        break;

                    }else{
                        board[0][4]=-6;
                        board[0][2]=0;
                    }
                }else{
                    board[0][4]=-6;
                    board[0][3]=0;
                }
            }

            //turn
            if(isColorSame(board[choice1.first-1][choice1.second-1],board[choice1.first][choice1.second]) != 1 ) posible.push_back(QPair<int,int>(choice1.first-1,choice1.second-1));
            if(isColorSame(board[choice1.first-1][choice1.second],board[choice1.first][choice1.second]) != 1 ) posible.push_back(QPair<int,int>(choice1.first-1,choice1.second));
            if(isColorSame(board[choice1.first-1][choice1.second+1],board[choice1.first][choice1.second]) != 1 ) posible.push_back(QPair<int,int>(choice1.first-1,choice1.second+1));
            if(isColorSame(board[choice1.first][choice1.second-1],board[choice1.first][choice1.second]) != 1 ) posible.push_back(QPair<int,int>(choice1.first,choice1.second-1));
            if(isColorSame(board[choice1.first][choice1.second+1],board[choice1.first][choice1.second]) != 1 ) posible.push_back(QPair<int,int>(choice1.first,choice1.second+1));
            if(isColorSame(board[choice1.first+1][choice1.second-1],board[choice1.first][choice1.second]) != 1 ) posible.push_back(QPair<int,int>(choice1.first+1,choice1.second-1));
            if(isColorSame(board[choice1.first+1][choice1.second],board[choice1.first][choice1.second]) != 1 ) posible.push_back(QPair<int,int>(choice1.first+1,choice1.second));
            if(isColorSame(board[choice1.first+1][choice1.second+1],board[choice1.first][choice1.second]) != 1 ) posible.push_back(QPair<int,int>(choice1.first+1,choice1.second+1));

            ui->statusbar->showMessage("Turn is wrong!");
            for (int i = 0; i < posible.size(); ++i) { //res
                if(posible[i]==choice2){
                    if(fig==0 || isColorSame(fig,fig_ch1)){ //res
                        int buf = board[choice2.first][choice2.second];
                        fromCordsToBtn(choice2.first,choice2.second,btn_ptr);
                        board[choice2.first][choice2.second]= board[choice1.first][choice1.second];
                        board[choice1.first][choice1.second]=0;


                        if(isCheck(choice2)){
                            board[choice1.first][choice1.second] = board[choice2.first][choice2.second];
                            board[choice2.first][choice2.second] = buf;
                            return;
                        }

                        if(color_ch1){
                            btn_ptr->setIcon(QIcon(":/images/wking.png"));
                            w_king_pos=choice2;
                            wKingHasTurn=true;
                        }
                        else    {
                            btn_ptr->setIcon(QIcon(":/images/bking.png"));
                            b_king_pos=choice2;
                            bKingHasTurn=true;
                        }
                        fromCordsToBtn(choice1.first,choice1.second,btn_ptr);
                        btn_ptr->setIcon(QIcon());
                        refresh_board();
                        ui->statusbar->showMessage("Turn is successful!");
                        if(player.source() != QUrl("qrc:/sounds/move.mp3"))
                            player.setSource(QUrl("qrc:/sounds/move.mp3"));
                        player.play();
                        white_turn = !white_turn;
                        break;
                    }
                }
            }

        }
        if(ui->statusbar->currentMessage()=="Turn is successful!"){

            last_turn=choice2;
        }
        if(ui->statusbar->currentMessage()=="Turn is wrong!"){
            if(player.source() != QUrl("qrc:/sounds/illegal.mp3"))
            player.setSource(QUrl("qrc:/sounds/illegal.mp3"));
            player.play();
        }

    }


    if(isCheck(w_king_pos)) {
        if(player.source() != QUrl("qrc:/sounds/move-check.mp3"))
            player.setSource(QUrl("qrc:/sounds/move-check.mp3"));
        bool checker=false;
        std::vector<QPair<int,int>> buf = isCheckPosition(w_king_pos);

        if(!isInDanger(buf[0]) || buf.size()>1){
            choice1= w_king_pos;
            posible.clear();
            //can king run?
            if(isColorSame(board[choice1.first-1][choice1.second-1],board[choice1.first][choice1.second]) != 1 ) posible.push_back(QPair<int,int>(choice1.first-1,choice1.second-1));
            if(isColorSame(board[choice1.first-1][choice1.second],board[choice1.first][choice1.second]) != 1 ) posible.push_back(QPair<int,int>(choice1.first-1,choice1.second));
            if(isColorSame(board[choice1.first-1][choice1.second+1],board[choice1.first][choice1.second]) != 1 ) posible.push_back(QPair<int,int>(choice1.first-1,choice1.second+1));
            if(isColorSame(board[choice1.first][choice1.second-1],board[choice1.first][choice1.second]) != 1 ) posible.push_back(QPair<int,int>(choice1.first,choice1.second-1));
            if(isColorSame(board[choice1.first][choice1.second+1],board[choice1.first][choice1.second]) != 1 ) posible.push_back(QPair<int,int>(choice1.first,choice1.second+1));
            if(isColorSame(board[choice1.first+1][choice1.second-1],board[choice1.first][choice1.second]) != 1 ) posible.push_back(QPair<int,int>(choice1.first+1,choice1.second-1));
            if(isColorSame(board[choice1.first+1][choice1.second],board[choice1.first][choice1.second]) != 1 ) posible.push_back(QPair<int,int>(choice1.first+1,choice1.second));
            if(isColorSame(board[choice1.first+1][choice1.second+1],board[choice1.first][choice1.second]) != 1 ) posible.push_back(QPair<int,int>(choice1.first+1,choice1.second+1));
            for (int i = 0; i < posible.size(); ++i) {
                int buff = board[posible[i].first][posible[i].second];
                board[posible[i].first][posible[i].second] = 6;
                board[choice1.first][choice1.second] = 0;
                if(!isCheck(QPair<int,int>(posible[i].first,posible[i].second))){
                    checker=true;
                    board[posible[i].first][posible[i].second] = buff;
                    board[choice1.first][choice1.second] = 6;
                    break;
                }
                board[posible[i].first][posible[i].second] = buff;
                board[choice1.first][choice1.second] = 6;
            }
            if(!checker){
                //he cant run
                msg.setText("CHECKMATE, WHITE LOSES!");

                if(player.source() != QUrl("qrc:/sounds/game-end.mp3"))
                    player.setSource(QUrl("qrc:/sounds/game-end.mp3"));


                if(buf.size() ==1){

                    for (int i = 0; i < 8; ++i) {
                        for (int j = 0; j < 8; ++j) {
                            int save = board[i][j];
                            board[i][j]=-7;
                            if(isInDanger( QPair<int,int>(i,j) ) && !isCheck(w_king_pos)){
                                msg.setText("White check!");
                            if(player.source() != QUrl("qrc:/sounds/move-check.mp3"))
                                    player.setSource(QUrl("qrc:/sounds/move-check.mp3"));
                                board[i][j]= save;
                                break;
                            }
                            board[i][j]= save;
                        }
                    }
                }
                player.play();
                msg.exec();
                msg.setText("Check!");

            }else{
                //he can
                player.play();
                msg.setText("White check!");
                msg.exec();
                msg.setText("Check!");
            }
            //can king run?
        }else{
        //he also can
            player.play();
        msg.setText("White check!");
        msg.exec();
        msg.setText("Check!");
        }
    }

    if(isCheck(b_king_pos)) {
        player.setSource(QUrl("qrc:/sounds/move-check.mp3"));
        bool checker=false;
        std::vector<QPair<int,int>> buf = isCheckPosition(b_king_pos);

        if(!isInDanger(buf[0]) || buf.size()>1){
        choice1= b_king_pos;
        posible.clear();
        //can king run?
        if(isColorSame(board[choice1.first-1][choice1.second-1],board[choice1.first][choice1.second]) != 1 ){ posible.push_back(QPair<int,int>(choice1.first-1,choice1.second-1));
                if(choice1.first-1==-1 || choice1.first-1 == 8 || choice1.second-1 == -1 || choice1.second-1 == 8) posible.pop_back();}
        if(isColorSame(board[choice1.first-1][choice1.second],board[choice1.first][choice1.second]) != 1 ){ posible.push_back(QPair<int,int>(choice1.first-1,choice1.second));
                if(choice1.first-1==-1 || choice1.first-1 == 8) posible.pop_back();}
        if(isColorSame(board[choice1.first-1][choice1.second+1],board[choice1.first][choice1.second]) != 1 ){ posible.push_back(QPair<int,int>(choice1.first-1,choice1.second+1));
        if(choice1.first-1==-1 || choice1.first-1 == 8 || choice1.second+1 == -1 || choice1.second+1 == 8) posible.pop_back();}
        if(isColorSame(board[choice1.first][choice1.second-1],board[choice1.first][choice1.second]) != 1 ){ posible.push_back(QPair<int,int>(choice1.first,choice1.second-1));
        if(choice1.second-1 == -1 || choice1.second-1 == 8) posible.pop_back();}
        if(isColorSame(board[choice1.first][choice1.second+1],board[choice1.first][choice1.second]) != 1 ){ posible.push_back(QPair<int,int>(choice1.first,choice1.second+1));
        if(choice1.second+1 == -1 || choice1.second+1 == 8) posible.pop_back();}
        if(isColorSame(board[choice1.first+1][choice1.second-1],board[choice1.first][choice1.second]) != 1 ){ posible.push_back(QPair<int,int>(choice1.first+1,choice1.second-1));
        if(choice1.first+1==-1 || choice1.first+1 == 8 || choice1.second-1 == -1 || choice1.second-1 == 8) posible.pop_back();}
        if(isColorSame(board[choice1.first+1][choice1.second],board[choice1.first][choice1.second]) != 1 ){ posible.push_back(QPair<int,int>(choice1.first+1,choice1.second));
        if(choice1.first+1==-1 || choice1.first+1 == 8) posible.pop_back();}
        if(isColorSame(board[choice1.first+1][choice1.second+1],board[choice1.first][choice1.second]) != 1 ){ posible.push_back(QPair<int,int>(choice1.first+1,choice1.second+1));
        if(choice1.first+1==-1 || choice1.first+1 == 8 || choice1.second+1 == -1 || choice1.second+1 == 8) posible.pop_back();}
        for (int i = 0; i < posible.size(); ++i) {
                int buff = board[posible[i].first][posible[i].second];
                board[posible[i].first][posible[i].second] = -6;
                board[choice1.first][choice1.second] = 0;
                if(!isCheck(QPair<int,int>(posible[i].first,posible[i].second))){
                    checker=true;
                    board[posible[i].first][posible[i].second] = buff;
                    board[choice1.first][choice1.second] = -6;
                    break;
                }
                board[posible[i].first][posible[i].second] = buff;
                board[choice1.first][choice1.second] = -6;
        }
        if(!checker){
                //he cant run
                msg.setText("CHECKMATE, BLACK LOSES!");

                if(player.source() != QUrl("qrc:/sounds/game-end.mp3"))
                    player.setSource(QUrl("qrc:/sounds/game-end.mp3"));


                if(buf.size() ==1){

                    for (int i = 0; i < 8; ++i) {
                        for (int j = 0; j < 8; ++j) {
                            int save = board[i][j];
                            board[i][j]=7;
                            if(isInDanger( QPair<int,int>(i,j) ) && !isCheck(b_king_pos)){
                                msg.setText("Black check!");
                                if(player.source() != QUrl("qrc:/sounds/move-check.mp3"))
                                    player.setSource(QUrl("qrc:/sounds/move-check.mp3"));
                                board[i][j]= save;
                                break;
                            }
                            board[i][j]= save;
                        }
                    }
                }
                player.play();
                msg.exec();
                msg.setText("Check!");

        }else{
                //he can
                player.play();
                msg.setText("Black check!");
                msg.exec();
                msg.setText("Check!");
        }
        //can king run?
        }else{
        //he also can
        player.play();
        msg.setText("Black check!");
        msg.exec();
        msg.setText("Check!");
        }

    }
}




void MainWindow::on_reset_triggered()
{
    if(player.source() != QUrl("qrc:/sounds/game-end.mp3"))
        player.setSource(QUrl("qrc:/sounds/game-end.mp3"));
    player.play();
    color_ch1=false;
    white_turn=true;
    leaver= false;
    rook70HasTurn=false,rook77HasTurn=false,rook00HasTurn=false,rook07HasTurn=false;
    wKingHasTurn=false, bKingHasTurn=false;
    w_king_pos.first=7;
    w_king_pos.second=4;
    b_king_pos.first=0;
    b_king_pos.second=4;
    msg.setText("Check!");

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
        board[i][j]=0;
        fromCordsToBtn(i,j,btn_ptr);
        btn_ptr->setIcon(QIcon(""));
        }
    }

    board[0][0]=-2;
    fromCordsToBtn(0,0,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/brook.png"));

    board[0][1]=-3;
    fromCordsToBtn(0,1,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/bhorse.png"));

    board[0][2]=-4;
    fromCordsToBtn(0,2,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/bbishop.png"));

    board[0][3]=-5;
    fromCordsToBtn(0,3,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/bqeen.png"));

    board[0][4]=-6;
    fromCordsToBtn(0,4,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/bking.png"));

    board[0][5]=-4;
    fromCordsToBtn(0,5,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/bbishop.png"));

    board[0][6]=-3;
    fromCordsToBtn(0,6,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/bhorse.png"));

    board[0][7]=-2;
    fromCordsToBtn(0,7,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/brook.png"));



    board[7][0]=2;
    fromCordsToBtn(7,0,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/wrook.png"));

    board[7][1]=3;
    fromCordsToBtn(7,1,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/whose.png"));

    board[7][2]=4;
    fromCordsToBtn(7,2,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/wbishop.png"));

    board[7][3]=5;
    fromCordsToBtn(7,3,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/wqeen.png"));

    board[7][4]=6;
    fromCordsToBtn(7,4,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/wking.png"));

    board[7][5]=4;
    fromCordsToBtn(7,5,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/wbishop.png"));

    board[7][6]=3;
    fromCordsToBtn(7,6,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/whose.png"));

    board[7][7]=2;
    fromCordsToBtn(7,7,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/wrook.png"));



    board[1][0]=-1;
    fromCordsToBtn(1,0,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/bpawn.png"));

    board[1][1]=-1;
    fromCordsToBtn(1,1,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/bpawn.png"));

    board[1][2]=-1;
    fromCordsToBtn(1,2,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/bpawn.png"));

    board[1][3]=-1;
    fromCordsToBtn(1,3,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/bpawn.png"));

    board[1][4]=-1;
    fromCordsToBtn(1,4,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/bpawn.png"));

    board[1][5]=-1;
    fromCordsToBtn(1,5,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/bpawn.png"));

    board[1][6]=-1;
    fromCordsToBtn(1,6,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/bpawn.png"));

    board[1][7]=-1;
    fromCordsToBtn(1,7,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/bpawn.png"));


    board[6][0]=1;
    fromCordsToBtn(6,0,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/wpawn.png"));

    board[6][1]=1;
    fromCordsToBtn(6,1,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/wpawn.png"));

    board[6][2]=1;
    fromCordsToBtn(6,2,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/wpawn.png"));

    board[6][3]=1;
    fromCordsToBtn(6,3,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/wpawn.png"));

    board[6][4]=1;
    fromCordsToBtn(6,4,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/wpawn.png"));

    board[6][5]=1;
    fromCordsToBtn(6,5,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/wpawn.png"));

    board[6][6]=1;
    fromCordsToBtn(6,6,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/wpawn.png"));

    board[6][7]=1;
    fromCordsToBtn(6,7,btn_ptr);
    btn_ptr->setIcon(QIcon(":/images/wpawn.png"));

    if(player.source() != QUrl("qrc:/sounds/game-start.mp3"))
        player.setSource(QUrl("qrc:/sounds/game-start.mp3"));
    player.play();
}

