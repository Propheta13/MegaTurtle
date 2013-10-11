#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "msettingsdialog.h"

namespace Ui {
class MainWindow;
}

class MGScene;
class MTailGenerator;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    MGScene *m_map_scene;
    QPixmap *m_map;

    MTailGenerator *m_tailgen;
    MSettings::settings_t m_settings;

protected:
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);

private slots:
    void slotGenerateTailMap();
    void slotChangeSettings();
    void slotSaveTailMap();
};

#endif // MAINWINDOW_H
