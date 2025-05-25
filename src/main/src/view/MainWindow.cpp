#include "view/MainWindow.h"
#include "ui_MainWindow.h"

#include <QHBoxLayout>

#include "store/ObjectStore.h"
#include "view/component/JsonEditorWidget.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) ,ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->mWindowTitle_ = windowTitle();

    QHBoxLayout *horizontalLayout = new QHBoxLayout(ui->centralwidget);
    ui->centralwidget->setLayout(horizontalLayout);

    JsonEditorWidget *jsonEditorWidget = new JsonEditorWidget(this);
    horizontalLayout->addWidget(jsonEditorWidget);

    jsonEditorWidget->loadJaon(R"({"name": "thrent", "age": 18})");

    REGISTER_OBJECT("main-windows", this);
}

MainWindow::~MainWindow() {
    delete ui;
}
