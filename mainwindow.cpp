#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtDebug>
#include <QPoint>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model= new Chip(this);

    ui->listView->setModel(model);
    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showContextMenu(const QPoint& pos)
{
    // Handle global position
       QPoint globalPos = ui->listView->mapToGlobal(pos);

       // Create menu and insert some actions
       QMenu myMenu;
       myMenu.addAction(QIcon(":/i/i/add-icon.png"), "Insert", this, SLOT(addItem()));
       myMenu.addAction(QIcon(":/i/i/delete-icon.png"), "Erase",  this, SLOT(eraseItem()));
       myMenu.addAction(QIcon(":/i/i/Pencil-icon.png"), "Update", this, SLOT(updateItem()));

       // Show context menu at handling position
       myMenu.exec(globalPos);
}

void MainWindow::addItem()
{
    qDebug() << "addItem";
    model->addSome();
}

void MainWindow::eraseItem()
{
    qDebug() << "eraseItem";
    QModelIndex index = ui->listView->currentIndex();
    auto ind = index.row();
    qDebug() << ind;
    model->removeAt(ind);
}

void MainWindow::updateItem()
{
    model->updateAt(ui->listView->currentIndex());
}

void MainWindow::on_pushButton_clicked()
{
    QList<Annotation>::const_iterator i;
    for (i = model->getBeginAnnotations(); i != model->getEndAnnotations(); ++i)
    {
            qDebug() << "c: " << *i;
            //(*i).l="22";
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    model->addSome();
}

void MainWindow::on_pushButton_3_clicked()
{
    model->clearModel();
}

void MainWindow::on_pushButton_4_clicked()
{
     qDebug() << "c: ";
     setCursor(QPixmap(":/i/i/point-dirty.png").scaledToWidth(32));
}
