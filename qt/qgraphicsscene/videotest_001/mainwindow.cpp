#include "mainwindow.h"
#include "mydrawitem.h"
#include "mygraphicsitemgroup.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QGraphicsVideoItem>
#include <QMediaPlaylist>
#include <QMediaGaplessPlaybackControl>
#include <QMediaService>
#include <QtMultimedia>
#include <QtMultimediaWidgets>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose);

    m_scene = new QGraphicsScene(this);
    m_scene->setBackgroundBrush(Qt::green);
    ui->graphicsView->setScene(m_scene);

    m_player_1 = new QMediaPlayer(this);
    m_player_2 = new QMediaPlayer(this);

    QMediaPlaylist *playlist_1 = new QMediaPlaylist(this);
    playlist_1->addMedia(QUrl::fromLocalFile(QDir::homePath() + "/temp/video/water.mp4"));
    playlist_1->addMedia(QUrl::fromLocalFile(QDir::homePath() + "/temp/video/water2.mp4"));
    playlist_1->setPlaybackMode(QMediaPlaylist::Loop);
    m_player_1->setPlaylist(playlist_1);

    QMediaPlaylist *playlist_2 = new QMediaPlaylist(this);
    playlist_2->addMedia(QUrl::fromLocalFile(QDir::homePath() + "/temp/video/some1.mp4"));
    playlist_2->setPlaybackMode(QMediaPlaylist::Loop);
    m_player_2->setPlaylist(playlist_2);


    m_video_item_1 = new QGraphicsVideoItem;
    m_video_item_1->setPos(QPointF(0, 0));
    m_video_item_1->setSize(QSizeF(600, 400));
    m_video_item_1->setAspectRatioMode(Qt::IgnoreAspectRatio);
    m_scene->addItem(m_video_item_1);

    QGraphicsPixmapItem *pixmap_item = new QGraphicsPixmapItem;
    pixmap_item->setPixmap(QPixmap(QDir::homePath() + "/temp/video/1.jpg"));
    pixmap_item->setPos(0, 0);
    pixmap_item->setScale(0.04);
    pixmap_item->setShapeMode(QGraphicsPixmapItem::MaskShape);
    m_scene->addItem(pixmap_item);


    m_video_item_2 = new MyGraphicsVideoItem;
    m_video_item_2->setPos(QPointF(200, 200));
    m_video_item_2->setSize(QSizeF(300, 150));
    m_video_item_2->setOpacity(0.8);
    //m_video_item_2->setAspectRatioMode(Qt::IgnoreAspectRatio);
    m_scene->addItem(m_video_item_2);


    m_player_1->setVideoOutput(m_video_item_1);
    m_player_2->setVideoOutput(m_video_item_2);

    m_player_1->play();
    m_player_2->play();


    MyDrawItem *rect1 = new MyDrawItem(0);
    rect1->setBrush(QBrush(Qt::red));
    rect1->setRect(100, 100, 300, 200);
    //rect1->setRotation(30);
    m_scene->addItem(rect1);

    QGraphicsSimpleTextItem *text_item = new QGraphicsSimpleTextItem;
    text_item->setText("This is example text");
    text_item->setFont(QFont("arial", 30));
    text_item->setPos(300, 100);
    text_item->setBrush(QBrush(Qt::red));
    text_item->setFlag(QGraphicsItem::ItemIsMovable, true);
    text_item->setFlag(QGraphicsItem::ItemIsSelectable, true);
    text_item->setSelected(true);
    m_scene->addItem(text_item);

//    QGraphicsView *view1 = new QGraphicsView;
//    view1->setScene(m_scene);
//    //view1->setSceneRect(100, 100, 200, 200);
//    view1->resize(1000, 1000);
//    view1->fitInView(QRect(0, 0, 200, 200));
//    view1->show();

//    QGraphicsView *view2 = new QGraphicsView;
//    view2->setScene(m_scene);
//    view2->setSceneRect(300, 100, 200, 200);
//    view2->resize(220, 220);
//    view2->show();

//    QGraphicsRectItem *rect1 = new QGraphicsRectItem(0);
//    rect1->setBrush(QBrush(Qt::red));
//    rect1->setRect(100, 100, 400, 400);
//    m_scene->addItem(rect1);

//    QGraphicsRectItem *rect2 = new QGraphicsRectItem(0);
//    rect2->setBrush(QBrush(Qt::green));
//    rect2->setRect(20, 20, 100, 100);
//    QGraphicsRectItem *rect3 = new QGraphicsRectItem(0);
//    rect3->setBrush(QBrush(Qt::blue));
//    rect3->setRect(80, 80, 80, 80);
//    //m_scene->addItem(rect2);
//    //m_scene->addItem(rect3);
//    MyGraphicsItemGroup *group = new MyGraphicsItemGroup(0);
//    group->addToGroup(rect2);
//    group->addToGroup(rect3);
//    m_scene->addItem(group);
    //qDebug() << group->boundingRect();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_imgRotate_valueChanged(int value)
{
    m_video_item_2->setRotation(-value);
}

void MainWindow::on_pushButton_clicked()
{
    if (m_video_item_2->graphicsEffect()) {
        m_video_item_2->graphicsEffect()->deleteLater();
    }
    else {
        m_video_item_2->setGraphicsEffect(new QGraphicsDropShadowEffect(this));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    m_video_item_2->setShowMask(!m_video_item_2->hasShowMask());
}
