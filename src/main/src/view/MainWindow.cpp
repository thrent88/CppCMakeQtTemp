#include "view/MainWindow.h"
#include "ui_MainWindow.h"

#include "store/ObjectStore.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) ,ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->mWindowTitle_ = windowTitle();

    REGISTER_OBJECT("main-windows", this);
}

MainWindow::~MainWindow() {
    delete ui;
}
