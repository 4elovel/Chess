#pragma once
#include "mainwindow.cpp"

bool MainWindow::isCheck(QPair<int,int> pos){
    bool col = false;
    int posx = pos.first;
    int posy = pos.second;
    if(board[pos.first][pos.second] > 0) col=true;
    //bishop + queen
    for (int i = pos.first+1,j = pos.second-1; i < 8; ++i,j--) {//Left-down
        if(j==-1) break;
        if(board[i][j]==0) continue;
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==-1){
            if(abs(board[i][j]) == 4 || abs(board[i][j]) == 5) return true;
            break;
        }
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==1){
            break;
        }
    }
    for (int i = pos.first-1, j = pos.second+1; i > -1; --i,j++) {//right-up
        if(j==8) break;
        if(board[i][j]==0) continue;
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==-1){
            if(abs(board[i][j]) == 4 || abs(board[i][j]) == 5) return true;
            break;
        }
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==1){
            break;
        }
    }
    for (int i = pos.first-1,j = pos.second-1; i > -1; --i,--j) {//left-up
        if(j == -1) break;
        if(board[i][j]==0) continue;
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==-1){
            if(abs(board[i][j]) == 4 || abs(board[i][j]) == 5) return true;
            break;
        }
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==1){
            break;
        }
    }
    for (int i = pos.first+1,j = pos.second+1; i < 8; ++i,++j) {//right-down
        if(j == 8) break;
        if(board[i][j]==0) continue;
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==-1){
            if(abs(board[i][j]) == 4 || abs(board[i][j]) == 5) return true;
            break;
        }
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==1){
            break;
        }
    }
    //rook + queen
    for (int i = pos.first+1; i < 8; ++i) { //down
        if(board[i][pos.second] == 0 ){
            continue;
        }
        else if(isColorSame(board[i][pos.second],board[pos.first][pos.second]) == 1){
            break;
        }
        else if(isColorSame(board[i][pos.second],board[pos.first][pos.second]) == -1){
            if(abs(board[i][pos.second]) == 2 || abs(board[i][pos.second]) == 5)
                return true;
            break;
        }
    }
    for (int i = pos.first-1; i > -1; --i) { //up
        if(board[i][pos.second] == 0 ){
            continue;
        }
        else if(isColorSame(board[i][pos.second],board[pos.first][pos.second]) == 1){
            break;
        }
        else if(isColorSame(board[i][pos.second],board[pos.first][pos.second]) == -1){
            if(abs(board[i][pos.second]) == 2 || abs(board[i][pos.second]) == 5)
                return true;
            break;
        }
    }
    for (int i = pos.second+1; i < 8; ++i) { // right
        if(board[pos.first][i] == 0 ){
            continue;
        }
        else if(isColorSame(board[pos.first][i],board[pos.first][pos.second]) == 1){
            break;
        }
        else if(isColorSame(board[pos.first][i],board[pos.first][pos.second]) == -1){
            if(abs(board[pos.first][i]) == 2 || abs(board[pos.first][i]) == 5)
                return true;
            break;
        }
    }
    for (int i = pos.second-1; i > -1; --i) { // left
        if(board[pos.first][i] == 0 ){
            continue;
        }
        else if(isColorSame(board[pos.first][i],board[pos.first][pos.second]) == 1){
            break;
        }
        else if(isColorSame(board[pos.first][i],board[pos.first][pos.second]) == -1){
            if(abs(board[pos.first][i]) == 2 || abs(board[pos.first][i]) == 5)
                return true;
            break;

        }

    }
    //pawn
    if(col){
        if(board[pos.first-1][pos.second-1]==-1) return true;
        if(board[pos.first-1][pos.second+1]==-1) return true;
    }
    if(!col){
        if(board[pos.first+1][pos.second-1]==1) return true;
        if(board[pos.first+1][pos.second+1]==1) return true;
    }
    //knight
    if( pos.first-2 < 8 && pos.first-2 > 0 && pos.second-1 < 8 && pos.second-1 > 0)
    if(abs(board[pos.first-2][pos.second-1])==3 && isColorSame(board[pos.first][pos.second],board[pos.first-2][pos.second-1])== -1) return true;
    if( pos.first-2 < 8 && pos.first-2 > 0 && pos.second+1 < 8 && pos.second+1 > 0)
    if(abs(board[pos.first-2][pos.second+1])==3 && isColorSame(board[pos.first][pos.second],board[pos.first-2][pos.second+1])== -1) return true;
    if( pos.first-1 < 8 && pos.first-1 > 0 && pos.second+2 < 8 && pos.second+2 > 0)
    if(abs(board[pos.first-1][pos.second+2])==3 && isColorSame(board[pos.first][pos.second],board[pos.first-1][pos.second+2])== -1) return true;
    if( pos.first+1 < 8 && pos.first+1 > 0 && pos.second+2 < 8 && pos.second+2 > 0)
    if(abs(board[pos.first+1][pos.second+2])==3 && isColorSame(board[pos.first][pos.second],board[pos.first+1][pos.second+2])== -1) return true;
    if( pos.first+2 < 8 && pos.first+2 > 0 && pos.second-1 < 8 && pos.second-1 > 0)
    if(abs(board[pos.first+2][pos.second-1])==3 && isColorSame(board[pos.first][pos.second],board[pos.first+2][pos.second-1])== -1) return true;
    if( pos.first+2 < 8 && pos.first+2 > 0 && pos.second+1 < 8 && pos.second+1 > 0)
    if(abs(board[pos.first+2][pos.second+1])==3 && isColorSame(board[pos.first][pos.second],board[pos.first+2][pos.second+1])== -1) return true;
    if( pos.first+1 < 8 && pos.first+1 > 0 && pos.second-2 < 8 && pos.second-2 > 0)
    if(abs(board[pos.first+1][pos.second-2])==3 && isColorSame(board[pos.first][pos.second],board[pos.first+1][pos.second-2])== -1) return true;
    if( pos.first-1 < 8 && pos.first-1 > 0 && pos.second-2 < 8 && pos.second-2 > 0)
    if(abs(board[pos.first-1][pos.second-2])==3 && isColorSame(board[pos.first][pos.second],board[pos.first-1][pos.second-2])== -1) return true;
    //king + queen
    if(abs(board[pos.first-1][pos.second-1])==6) return true;
    if(abs(board[pos.first-1][pos.second-1]) == 5 && isColorSame(board[pos.first-1][pos.second-1],board[pos.first][pos.second])==-1) return true;
    if(abs(board[pos.first-1][pos.second])==6) return true;
    if(abs(board[pos.first-1][pos.second]) == 5 && isColorSame(board[pos.first-1][pos.second],board[pos.first][pos.second])==-1) return true;
    if(abs(board[pos.first-1][pos.second+1])==6) return true;
    if(abs(board[pos.first-1][pos.second+1]) == 5 && isColorSame(board[pos.first-1][pos.second+1],board[pos.first][pos.second])==-1) return true;

    if(abs(board[pos.first][pos.second-1])==6) return true;
    if(abs(board[pos.first][pos.second-1]) == 5 && isColorSame(board[pos.first][pos.second-1],board[pos.first][pos.second])==-1) return true;
    if(abs(board[pos.first][pos.second+1])==6) return true;
    if(abs(board[pos.first][pos.second+1]) == 5 && isColorSame(board[pos.first][pos.second+1],board[pos.first][pos.second])==-1) return true;

    if(abs(board[pos.first+1][pos.second-1])==6) return true;
    if(abs(board[pos.first+1][pos.second-1]) == 5 && isColorSame(board[pos.first+1][pos.second-1],board[pos.first][pos.second])==-1) return true;
    if(abs(board[pos.first+1][pos.second])==6) return true;
    if(abs(board[pos.first+1][pos.second]) == 5 && isColorSame(board[pos.first+1][pos.second],board[pos.first][pos.second])==-1) return true;
    if(abs(board[pos.first+1][pos.second+1])==6) return true;
    if(abs(board[pos.first+1][pos.second+1]) == 5 && isColorSame(board[pos.first+1][pos.second+1],board[pos.first][pos.second])==-1) return true;

    return false;
}

bool MainWindow::isInDanger(QPair<int,int> pos)
{
    bool col = false;
    if(board[pos.first][pos.second] > 0) col=true;
    //bishop + queen
    for (int i = pos.first+1,j = pos.second-1; i < 8; ++i,j--) {//Left-down
        if(j==-1) break;
        if(board[i][j]==0) continue;
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==-1){
            if(abs(board[i][j]) == 4 || abs(board[i][j]) == 5) return true;
            break;
        }
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==1){
            break;
        }
    }
    for (int i = pos.first-1, j = pos.second+1; i > -1; --i,j++) {//right-up
        if(j==8) break;
        if(board[i][j]==0) continue;
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==-1){
            if(abs(board[i][j]) == 4 || abs(board[i][j]) == 5) return true;
            break;
        }
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==1){
            break;
        }
    }
    for (int i = pos.first-1,j = pos.second-1; i > -1; --i,--j) {//left-up
        if(j == -1) break;
        if(board[i][j]==0) continue;
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==-1){
            if(abs(board[i][j]) == 4 || abs(board[i][j]) == 5) return true;
            break;
        }
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==1){
            break;
        }
    }
    for (int i = pos.first+1,j = pos.second+1; i < 8; ++i,++j) {//right-down
        if(j == 8) break;
        if(board[i][j]==0) continue;
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==-1){
            if(abs(board[i][j]) == 4 || abs(board[i][j]) == 5) return true;
            break;
        }
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==1){
            break;
        }
    }
    //rook + queen
    for (int i = pos.first+1; i < 8; ++i) { //down
        if(board[i][pos.second] == 0 ){
            continue;
        }
        else if(isColorSame(board[i][pos.second],board[pos.first][pos.second]) == 1){
            break;
        }
        else if(isColorSame(board[i][pos.second],board[pos.first][pos.second]) == -1){
            if(abs(board[i][pos.second]) == 2 || abs(board[i][pos.second]) == 5)
                return true;
            break;
        }
    }
    for (int i = pos.first-1; i > -1; --i) { //up
        if(board[i][pos.second] == 0 ){
            continue;
        }
        else if(isColorSame(board[i][pos.second],board[pos.first][pos.second]) == 1){
            break;
        }
        else if(isColorSame(board[i][pos.second],board[pos.first][pos.second]) == -1){
            if(abs(board[i][pos.second]) == 2 || abs(board[i][pos.second]) == 5)
                return true;
            break;
        }
    }
    for (int i = pos.second+1; i < 8; ++i) { // right
        if(board[pos.first][i] == 0 ){
            continue;
        }
        else if(isColorSame(board[pos.first][i],board[pos.first][pos.second]) == 1){
            break;
        }
        else if(isColorSame(board[pos.first][i],board[pos.first][pos.second]) == -1){
            if(abs(board[pos.first][i]) == 2 || abs(board[pos.first][i]) == 5)
                return true;
            break;
        }
    }
    for (int i = pos.second-1; i > -1; --i) { // left
        if(board[pos.first][i] == 0 ){
            continue;
        }
        else if(isColorSame(board[pos.first][i],board[pos.first][pos.second]) == 1){
            break;
        }
        else if(isColorSame(board[pos.first][i],board[pos.first][pos.second]) == -1){
            if(abs(board[pos.first][i]) == 2 || abs(board[pos.first][i]) == 5)
                return true;
            break;

        }

    }
    //pawn
    if(col){
        if(pos.first-1 != -1 && pos.first-1!=8 && pos.second-1 != -1 && pos.second-1 != 8)
        if(board[pos.first-1][pos.second-1]==-1) return true;
        if(pos.first-1 != -1 && pos.first-1!=8 && pos.second-1 != +1 && pos.second+1 != 8)
        if(board[pos.first-1][pos.second+1]==-1) return true;
    }
    if(!col){
        if(pos.first+1 != -1 && pos.first+1!=8 && pos.second-1 != -1 && pos.second-1 != 8)
        if(board[pos.first+1][pos.second-1]==1) return true;
        if(pos.first+1 != -1 && pos.first+1!=8 && pos.second+1 != -1 && pos.second+1 != 8)
        if(board[pos.first+1][pos.second+1]==1) return true;
    }
    //knight
    if(abs(board[pos.first-2][pos.second-1])==3 && isColorSame(board[pos.first][pos.second],board[pos.first-2][pos.second-1])== -1) return true;
    if(abs(board[pos.first-2][pos.second+1])==3 && isColorSame(board[pos.first][pos.second],board[pos.first-2][pos.second+1])== -1) return true;
    if(abs(board[pos.first-1][pos.second+2])==3 && isColorSame(board[pos.first][pos.second],board[pos.first-1][pos.second+2])== -1) return true;
    if(abs(board[pos.first+1][pos.second+2])==3 && isColorSame(board[pos.first][pos.second],board[pos.first+1][pos.second+2])== -1) return true;
    if(abs(board[pos.first+2][pos.second-1])==3 && isColorSame(board[pos.first][pos.second],board[pos.first+2][pos.second-1])== -1) return true;
    if(abs(board[pos.first+2][pos.second+1])==3 && isColorSame(board[pos.first][pos.second],board[pos.first+2][pos.second+1])== -1) return true;
    if(abs(board[pos.first+1][pos.second-2])==3 && isColorSame(board[pos.first][pos.second],board[pos.first+1][pos.second-2])== -1) return true;
    if(abs(board[pos.first-1][pos.second-2])==3 && isColorSame(board[pos.first][pos.second],board[pos.first-1][pos.second-2])== -1) return true;
    //king + queen

    if(abs(board[pos.first-1][pos.second-1]) == 5 && isColorSame(board[pos.first-1][pos.second-1],board[pos.first][pos.second])==-1) return true;

    if(abs(board[pos.first-1][pos.second]) == 5 && isColorSame(board[pos.first-1][pos.second],board[pos.first][pos.second])==-1) return true;

    if(abs(board[pos.first-1][pos.second+1]) == 5 && isColorSame(board[pos.first-1][pos.second+1],board[pos.first][pos.second])==-1) return true;


    if(abs(board[pos.first][pos.second-1]) == 5 && isColorSame(board[pos.first][pos.second-1],board[pos.first][pos.second])==-1) return true;

    if(abs(board[pos.first][pos.second+1]) == 5 && isColorSame(board[pos.first][pos.second+1],board[pos.first][pos.second])==-1) return true;


    if(abs(board[pos.first+1][pos.second-1]) == 5 && isColorSame(board[pos.first+1][pos.second-1],board[pos.first][pos.second])==-1) return true;

    if(abs(board[pos.first+1][pos.second]) == 5 && isColorSame(board[pos.first+1][pos.second],board[pos.first][pos.second])==-1) return true;

    if(abs(board[pos.first+1][pos.second+1]) == 5 && isColorSame(board[pos.first+1][pos.second+1],board[pos.first][pos.second])==-1) return true;

    return false;
}

std::vector<QPair<int,int>> MainWindow::isCheckPosition(QPair<int,int> pos){
    std::vector<QPair<int,int>> res;

    bool col = false;
    if(board[pos.first][pos.second] > 0) col=true;
    //bishop + queen
    for (int i = pos.first+1,j = pos.second-1; i < 8; ++i,j--) {//Left-down
        if(j==-1) break;
        if(board[i][j]==0) continue;
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==-1){
            if(abs(board[i][j]) == 4 || abs(board[i][j]) == 5) res.push_back(QPair<int,int>(i,j));
            break;
        }
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==1){
            break;
        }
    }
    for (int i = pos.first-1, j = pos.second+1; i > -1; --i,j++) {//right-up
        if(j==8) break;
        if(board[i][j]==0) continue;
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==-1){
            if(abs(board[i][j]) == 4 || abs(board[i][j]) == 5) res.push_back(QPair<int,int>(i,j));
            break;
        }
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==1){
            break;
        }
    }
    for (int i = pos.first-1,j = pos.second-1; i > -1; --i,--j) {//left-up
        if(j == -1) break;
        if(board[i][j]==0) continue;
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==-1){
            if(abs(board[i][j]) == 4 || abs(board[i][j]) == 5) res.push_back(QPair<int,int>(i,j));
            break;
        }
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==1){
            break;
        }
    }
    for (int i = pos.first+1,j = pos.second+1; i < 8; ++i,++j) {//right-down
        if(j == 8) break;
        if(board[i][j]==0) continue;
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==-1){
            if(abs(board[i][j]) == 4 || abs(board[i][j]) == 5) res.push_back(QPair<int,int>(i,j));
            break;
        }
        else if(isColorSame(board[i][j],board[pos.first][pos.second])==1){
            break;
        }
    }
    //rook + queen
    for (int i = pos.first+1; i < 8; ++i) { //down
        if(board[i][pos.second] == 0 ){
            continue;
        }
        else if(isColorSame(board[i][pos.second],board[pos.first][pos.second]) == 1){
            break;
        }
        else if(isColorSame(board[i][pos.second],board[pos.first][pos.second]) == -1){
            if(abs(board[i][pos.second]) == 2 || abs(board[i][pos.second]) == 5)
                res.push_back(QPair<int,int>(i,pos.second));
            break;
        }
    }
    for (int i = pos.first-1; i > -1; --i) { //up
        if(board[i][pos.second] == 0 ){
            continue;
        }
        else if(isColorSame(board[i][pos.second],board[pos.first][pos.second]) == 1){
            break;
        }
        else if(isColorSame(board[i][pos.second],board[pos.first][pos.second]) == -1){
            if(abs(board[i][pos.second]) == 2 || abs(board[i][pos.second]) == 5)
                res.push_back(QPair<int,int>(i,pos.second));;
            break;
        }
    }
    for (int i = pos.second+1; i < 8; ++i) { // right
        if(board[pos.first][i] == 0 ){
            continue;
        }
        else if(isColorSame(board[pos.first][i],board[pos.first][pos.second]) == 1){
            break;
        }
        else if(isColorSame(board[pos.first][i],board[pos.first][pos.second]) == -1){
            if(abs(board[pos.first][i]) == 2 || abs(board[pos.first][i]) == 5)
                res.push_back(QPair<int,int>(pos.first,i));;
            break;
        }
    }
    for (int i = pos.second-1; i > -1; --i) { // left
        if(board[pos.first][i] == 0 ){
            continue;
        }
        else if(isColorSame(board[pos.first][i],board[pos.first][pos.second]) == 1){
            break;
        }
        else if(isColorSame(board[pos.first][i],board[pos.first][pos.second]) == -1){
            if(abs(board[pos.first][i]) == 2 || abs(board[pos.first][i]) == 5)
                res.push_back(QPair<int,int>(pos.first,i));;
            break;

        }

    }
    //pawn
    if(col){
        if(board[pos.first-1][pos.second-1]==-1) res.push_back(QPair<int,int>(pos.first-1,pos.second-1));
        if(board[pos.first-1][pos.second+1]==-1) res.push_back(QPair<int,int>(pos.first-1,pos.second+1));
    }
    if(!col){
        if(board[pos.first+1][pos.second-1]==1) res.push_back(QPair<int,int>(pos.first+1,pos.second-1));
        if(board[pos.first+1][pos.second+1]==1) res.push_back(QPair<int,int>(pos.first+1,pos.second+1));
    }
    //knight
    if(abs(board[pos.first-2][pos.second-1])==3 && isColorSame(board[pos.first][pos.second],board[pos.first-2][pos.second-1])== -1) res.push_back(QPair<int,int>(pos.first-2,pos.second-1));
    if(abs(board[pos.first-2][pos.second+1])==3 && isColorSame(board[pos.first][pos.second],board[pos.first-2][pos.second+1])== -1) res.push_back(QPair<int,int>(pos.first-2,pos.second+1));
    if(abs(board[pos.first-1][pos.second+2])==3 && isColorSame(board[pos.first][pos.second],board[pos.first-1][pos.second+2])== -1) res.push_back(QPair<int,int>(pos.first-1,pos.second+2));
    if(abs(board[pos.first+1][pos.second+2])==3 && isColorSame(board[pos.first][pos.second],board[pos.first+1][pos.second+2])== -1) res.push_back(QPair<int,int>(pos.first+1,pos.second+2));
    if(abs(board[pos.first+2][pos.second-1])==3 && isColorSame(board[pos.first][pos.second],board[pos.first+2][pos.second-1])== -1) res.push_back(QPair<int,int>(pos.first+2,pos.second-1));
    if(abs(board[pos.first+2][pos.second+1])==3 && isColorSame(board[pos.first][pos.second],board[pos.first+2][pos.second+1])== -1) res.push_back(QPair<int,int>(pos.first+2,pos.second+1));
    if(abs(board[pos.first+1][pos.second-2])==3 && isColorSame(board[pos.first][pos.second],board[pos.first+1][pos.second-2])== -1) res.push_back(QPair<int,int>(pos.first+1,pos.second-2));
    if(abs(board[pos.first-1][pos.second-2])==3 && isColorSame(board[pos.first][pos.second],board[pos.first-1][pos.second-2])== -1) res.push_back(QPair<int,int>(pos.first-1,pos.second-2));
    //king + queen

    if(abs(board[pos.first-1][pos.second-1]) == 5 && isColorSame(board[pos.first-1][pos.second-1],board[pos.first][pos.second])==-1) res.push_back(QPair<int,int>(pos.first-1,pos.second-1));

    if(abs(board[pos.first-1][pos.second]) == 5 && isColorSame(board[pos.first-1][pos.second],board[pos.first][pos.second])==-1) res.push_back(QPair<int,int>(pos.first-1,pos.second));

    if(abs(board[pos.first-1][pos.second+1]) == 5 && isColorSame(board[pos.first-1][pos.second+1],board[pos.first][pos.second])==-1) res.push_back(QPair<int,int>(pos.first-1,pos.second+1));

    if(abs(board[pos.first][pos.second-1]) == 5 && isColorSame(board[pos.first][pos.second-1],board[pos.first][pos.second])==-1) res.push_back(QPair<int,int>(pos.first,pos.second-1));

    if(abs(board[pos.first][pos.second+1]) == 5 && isColorSame(board[pos.first][pos.second+1],board[pos.first][pos.second])==-1) res.push_back(QPair<int,int>(pos.first,pos.second+1));

    if(abs(board[pos.first+1][pos.second-1]) == 5 && isColorSame(board[pos.first+1][pos.second-1],board[pos.first][pos.second])==-1) res.push_back(QPair<int,int>(pos.first+1,pos.second-1));

    if(abs(board[pos.first+1][pos.second]) == 5 && isColorSame(board[pos.first+1][pos.second],board[pos.first][pos.second])==-1) res.push_back(QPair<int,int>(pos.first+1,pos.second));

    if(abs(board[pos.first+1][pos.second+1]) == 5 && isColorSame(board[pos.first+1][pos.second+1],board[pos.first][pos.second])==-1) res.push_back(QPair<int,int>(pos.first+1,pos.second+1));

    return res;
}
