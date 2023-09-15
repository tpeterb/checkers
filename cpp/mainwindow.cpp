#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "board.h"
#include "piece.h"
#include <QLabel>
#include "position.h"
#include "moveHelper.h"
#include <string>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //this->setWindowState(Qt::WindowMaximized);
    //this->showFullScreen();
    //this->showMaximized();
    this->setContentsMargins(this->size().width() / 2,
                             this->size().height() / 2,
                             this->size().width() / 2,
                             this->size().height() / 2);
    this->setWindowTitle("Dámajáték");
    this->centralWidget = new QWidget();
    this->chessBoard = new QGridLayout();
    setupChessBoard();
    centralWidget->setLayout(chessBoard);
    this->setCentralWidget(centralWidget);
    centralWidget->move(centralWidget->parentWidget()->geometry().center());

    board = new Board();
    isPieceSelected = false;

    whiteCheckerMan = new QPixmap(":/images/white_checker_man-removebg.png");
    darkCheckerMan = new QPixmap(":/images/dark_checker_man-removebg.png");
    darkCheckerKing = new QPixmap(":/images/dark_checker_king-removebg.png");
    whiteCheckerKing = new QPixmap(":/images/white_checker_king-removebg.png");

    showCurrentBoardPosition();

    resultDialog = new QDialog(this);
    resultDialog->setModal(true);
    resultDialog->setFixedSize(QSize(150, 150));
    dialogLayout = new QVBoxLayout();
    resultDialog->setLayout(dialogLayout);
    resultLabel = new QLabel();
    newGameButton = new QPushButton();
    newGameButton->setText("New Game");
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(handleNewGameButtonClicked()));
    dialogLayout->addWidget(resultLabel);
    dialogLayout->addWidget(newGameButton);
    //qDebug() << this->size().width();
    //qDebug() << this->size().height();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete centralWidget;
    delete chessBoard;
    delete board;
    delete whiteCheckerMan;
    delete darkCheckerMan;
    delete darkCheckerKing;
    delete whiteCheckerKing;
    qDeleteAll(squares);
    squares.clear();
    delete resultLabel;
    delete resultDialog;
    delete newGameButton;
    delete dialogLayout;
}

void MainWindow::setupChessBoard() {
    chessBoard = new QGridLayout;
    for (int i = 0; i < Board::board_size; i++) {
        for (int j = 0; j < Board::board_size; j++) {
            QPushButton* square = new QPushButton();
            if ((i + j) % 2) {
                square->setStyleSheet("background-color: black; margin: 0;");
            } else {
                square->setStyleSheet("background-color: antiquewhite; margin: 0;");
            }
            square->setMinimumSize(QSize(30, 30));
            square->setMaximumSize(QSize(55, 55));
            connect(square, SIGNAL(clicked()), this, SLOT(handleSquareClicked()));
            squares.append(square);
            chessBoard->addWidget(square, i, j, 1, 1);

        }
    }
    auto horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    chessBoard->addItem(horizontalSpacer, 0, Board::board_size+1, 1, 1);
    auto verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    chessBoard->addItem(verticalSpacer, Board::board_size+1, 0, 1, 1);
    chessBoard->setSpacing(0);
    chessBoard->setContentsMargins(0, 0, 0, 0);
    this->setLayout(chessBoard);
}

void MainWindow::showCurrentBoardPosition() {
    QIcon whiteManIcon(*whiteCheckerMan);
    QIcon darkManIcon(*darkCheckerMan);
    QIcon darkKingIcon(*darkCheckerKing);
    QIcon whiteKingIcon(*whiteCheckerKing);
    for (auto square : squares) {
        square->setIcon(QIcon());
    }
    for (auto& piece : board->getPieces()) {
        PieceColor pieceColor = piece.getPieceColor();
        PieceType pieceType = piece.getPieceType();
        Position piecePosition = piece.getPosition();
        QLayoutItem* gridItem = chessBoard->itemAtPosition(piecePosition.getRow(), piecePosition.getCol());
        QWidget* widget = gridItem->widget();
        QPushButton* button = dynamic_cast<QPushButton*>(widget);
        if (button == nullptr) {

        }
        switch (pieceColor) {
            case PieceColor::white:
                if (pieceType == PieceType::man) {
                    button->setIcon(whiteManIcon);
                } else {
                    button->setIcon(whiteKingIcon);
                }
                break;
            case PieceColor::black:
                if (pieceType == PieceType::man) {
                    button->setIcon(darkManIcon);
                } else {
                    button->setIcon(darkKingIcon);
                }
                break;
        }
    }
}

void MainWindow::handleSquareClicked() {

    QPushButton* clickSourceSquare = qobject_cast<QPushButton*>(sender());
    int index = chessBoard->indexOf(clickSourceSquare);
    int row, col, rowSpan, colSpan;
    chessBoard->getItemPosition(index, &row, &col, &rowSpan, &colSpan);
    if (clickSourceSquare != nullptr) {
        if (!isPieceSelected) {
            if (!board->isSquareEmpty(Position(row, col))) { // Selecting the piece to move
                //qDebug() << "Piece selected!";
                isPieceSelected = true;
                squareToMoveFrom = clickSourceSquare;
            }
        } else { // A piece has already been selected previously
            if (!board->isSquareEmpty(Position(row, col))) {
                squareToMoveFrom = clickSourceSquare;
                return;
            }
            int squareToMoveFromRow, squareToMoveFromCol, squareToMoveFromRowSpan, squareToMoveFromColSpan;
            int squareToMoveFromIndex = chessBoard->indexOf(squareToMoveFrom);
            chessBoard->getItemPosition(squareToMoveFromIndex,
                                        &squareToMoveFromRow,
                                        &squareToMoveFromCol,
                                        &squareToMoveFromRowSpan,
                                        &squareToMoveFromColSpan);
            Piece* pieceToMove = &board->getPiece(board->getPieceIndexByPosition(Position(squareToMoveFromRow, squareToMoveFromCol)));
            std::optional<Move> moveToMake = MoveHelper::getMoveFromCoordinateChanges(Position(squareToMoveFromRow, squareToMoveFromCol),
                                                                       Position(row, col), pieceToMove->getPieceColor());
            if (moveToMake.has_value()) { // The move exists in the game
                board->makeMove(pieceToMove->getPosition(), moveToMake.value(), pieceToMove->getPieceColor());
                this->showCurrentBoardPosition();
                squareToMoveFrom = nullptr;
                isPieceSelected = false;
                if (board->whiteWins()) {
                    resultLabel->setText("White wins!");
                    resultDialog->exec();
                } else if (board->blackWins()) {
                    resultLabel->setText("Black wins!");
                    resultDialog->exec();
                }
            }
        }
    }
}

void MainWindow::handleNewGameButtonClicked() {
    delete board;
    board = new Board();
    showCurrentBoardPosition();
    resultDialog->close();
}
