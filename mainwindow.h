#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>
#include <QDesktopWidget>
#include <QSoundEffect>

#include "MetaVoIP.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSoundEffect ringtone, outgoingRing;
    QScreen *screen;
    MetaVoIP *metaVoIP;
    int screenX, screenY, callId;
    QString sipState, sipUser, sipServer, sipPass;

    void registerSip();
    void getSettings();
    void error(QString error);
    void sipCommand(QString cmd, QString value);

private slots:
    void getScreen();
    void on_regState_started(bool status);
    void on_regState_changed(bool status);
    void on_callState_changed(int role, int callId, int state, int status, QString remoteUri);
    void on_saveButton_clicked();
    void on_phoneButton_clicked();
    void on_b0_clicked();
    void on_b1_clicked();
    void on_b2_clicked();
    void on_b3_clicked();
    void on_b4_clicked();
    void on_b5_clicked();
    void on_b6_clicked();
    void on_b7_clicked();
    void on_b8_clicked();
    void on_b9_clicked();
    void on_bPound_clicked();
    void on_bStar_clicked();
    void on_hangButton_clicked();
    void on_actionAbout_Qt_triggered();
    void on_actionAbout_triggered();
};

#endif // MAINWINDOW_H
