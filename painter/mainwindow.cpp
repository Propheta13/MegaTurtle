#include <QImage>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mgscene.h"
#include "mtailgenerator.h"
#include "mdefault.h"
#include "matrixer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_map_scene(new MGScene(QString("Launch generate"), this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(m_map_scene);

    m_settings.tail_resolution = MapGenerator::DefaultTailResolution; //default value
    m_map_scene->setSceneRect(QRectF(0,0,m_settings.tail_resolution*Matrixer::SIZEX+1,m_settings.tail_resolution*Matrixer::SIZEY+1));
    m_tailgen = new MTailGenerator(m_map_scene, this);

    QObject::connect(ui->actionGenerate_tail_map, SIGNAL(triggered()), this, SLOT(slotGenerateTailMap()));
    QObject::connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(slotChangeSettings()));
    QObject::connect(ui->actionSave_tail_map, SIGNAL(triggered()), this, SLOT(slotSaveTailMap()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    ui->graphicsView->fitInView(0, 0, m_map_scene->width(), m_map_scene->height(), Qt::KeepAspectRatio);
    QMainWindow::resizeEvent(event);
}

void MainWindow::showEvent(QShowEvent* event)
{
    ui->graphicsView->fitInView(0, 0, m_map_scene->width(), m_map_scene->height(), Qt::KeepAspectRatio);
    QMainWindow::showEvent(event);
}

void MainWindow::slotGenerateTailMap()
{
    m_tailgen->setTailResolution(m_settings.tail_resolution);
    m_tailgen->generate();
    m_tailgen->draw();
    ui->actionSave_tail_map->setEnabled(true);
}

void MainWindow::slotChangeSettings()
{
    MSettingsDialog sd(&m_settings, this);
    sd.exec();
}

void MainWindow::slotSaveTailMap()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save tail map",QDir::currentPath(),
                                                            QString("Tail height map (*.thm)"),
                                                        new QString("Tail height map (*.thm)"));

    if(fileName.isNull())
    {
        return;
    }

    m_tailgen->save(fileName);
}
