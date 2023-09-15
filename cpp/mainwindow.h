#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include "board.h"
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void setupChessBoard();

    void showCurrentBoardPosition();

private:

    Ui::MainWindow *ui;

    QWidget *centralWidget;

    QGridLayout *chessBoard;

    QList<QPushButton*> squares;

    Board *board;

    QPixmap *darkCheckerMan;
    QPixmap *whiteCheckerMan;
    QPixmap *whiteCheckerKing;
    QPixmap *darkCheckerKing;

    bool isPieceSelected;
    QPushButton* squareToMoveFrom;
    QLabel* resultLabel;
    QDialog* resultDialog;
    QPushButton* newGameButton;
    QVBoxLayout* dialogLayout;

public slots:
    void handleSquareClicked();
    void handleNewGameButtonClicked();

};
#endif // MAINWINDOW_H
