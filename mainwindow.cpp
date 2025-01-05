#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    screen = QGuiApplication::screens().first();
    connect(screen, SIGNAL(virtualGeometryChanged(QRect)), this, SLOT(getScreen()));
    connect(ui->sipUser, SIGNAL(editingFinished()), QGuiApplication::inputMethod(), SLOT(hide()));
    connect(ui->sipPass, SIGNAL(editingFinished()), QGuiApplication::inputMethod(), SLOT(hide()));
    connect(ui->sipServer, SIGNAL(editingFinished()), QGuiApplication::inputMethod(), SLOT(hide()));
    connect(ui->sipPort, SIGNAL(editingFinished()), QGuiApplication::inputMethod(), SLOT(hide()));

    getScreen();
    getSettings();

    if(ui->sipUser->text()!="" && ui->sipPass->text()!="" && ui->sipServer->text()!="" && ui->sipPort->text()!="")
        registerSip();
}

void MainWindow::getScreen()
{
    QRect rec = QApplication::desktop()->screenGeometry();
    screenY = rec.height();
    screenX = rec.width();

    ui->hangButton->setIcon(QPixmap(":/images/phone_hang.png"));
    ui->phoneButton->setIcon(QPixmap(":/images/phone.png"));
    ui->phoneButton->setIconSize(QSize(screenX/15,screenY/15));
    ui->hangButton->setIconSize(QSize(screenX/15,screenY/15));
    QFont font = ui->b0->font();
    font.setPointSize(20);
    ui->b0->setFont(font);
    ui->b1->setFont(font);
    ui->b2->setFont(font);
    ui->b3->setFont(font);
    ui->b4->setFont(font);
    ui->b5->setFont(font);
    ui->b6->setFont(font);
    ui->b7->setFont(font);
    ui->b8->setFont(font);
    ui->b9->setFont(font);
    ui->bPound->setFont(font);
    ui->bStar->setFont(font);
    ui->number->setFont(font);
    ui->info->setFont(font);
    ui->sipUserText->setFont(font);
    ui->sipUser->setFont(font);
    ui->sipPassText->setFont(font);
    ui->sipPass->setFont(font);
    ui->sipServerText->setFont(font);
    ui->sipServer->setFont(font);
    ui->saveButton->setFont(font);
    ui->sipProtoText->setFont(font);
    ui->sipProtoBox->setFont(font);
    ui->sipPortText->setFont(font);
    ui->sipPort->setFont(font);

    ui->phoneButton->setEnabled(false);
    ui->hangButton->setEnabled(false);
}

void MainWindow::getSettings()
{
    QFile settings("settings.dat");
    if(settings.exists())
    {
        if(settings.open(QIODevice::ReadOnly))
        {
            ui->sipServer->setText(settings.readLine().simplified());
            ui->sipUser->setText(settings.readLine().simplified());
            ui->sipPass->setText(settings.readLine().simplified());
            ui->sipProtoBox->setCurrentIndex(settings.readLine().toInt());
            ui->sipPort->setText(settings.readLine().simplified());
            settings.close();
        }
        else
            error("No read permission available");
    }

    outgoingRing.setSource(QUrl::fromLocalFile(":/sounds/outgoing.wav"));
    outgoingRing.setLoopCount(QSoundEffect::Infinite);
    ringtone.setSource(QUrl::fromLocalFile(":/sounds/incoming.wav"));
    ringtone.setLoopCount(QSoundEffect::Infinite);
}

void MainWindow::on_saveButton_clicked()
{
    if(ui->sipUser->text()!="" && ui->sipPass->text()!="" && ui->sipServer->text()!="" && ui->sipPort->text()!="")
    {
        QFile settings("settings.dat");
        settings.remove();
        if (settings.open(QIODevice::WriteOnly))
        {
            QTextStream out(&settings);
            out << ui->sipServer->text().simplified();
            out << "\n";
            out << ui->sipUser->text().simplified();
            out << "\n";
            out << ui->sipPass->text().simplified();
            out << "\n";
            out << QString::number(ui->sipProtoBox->currentIndex());
            out << "\n";
            out << ui->sipPort->text().simplified();
            settings.close();

            registerSip();
        }
        else
            error("No write permission available");
    }
    else
        error("Please insert necessary values");
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "MetaVoIP 1.1.0", "Copyright:\nmetaSEC 2015-2016\n\nAuthor:\n- Dominik Fehr <df@metasec.de>");
}

void MainWindow::error(QString error)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText(error);
    msgBox.setWindowTitle("Error");
    msgBox.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
