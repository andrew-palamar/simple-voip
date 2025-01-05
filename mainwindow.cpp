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

void MainWindow::registerSip()
{
    metaVoIP = new MetaVoIP(ui->sipProtoBox->currentText(), ui->sipPortText->text().toInt());
    sipUser = ui->sipUser->text().simplified();
    sipServer = ui->sipServer->text().simplified();
    sipPass = ui->sipPass->text().simplified();
    sipState = "init";

    connect(metaVoIP, SIGNAL(callStateChanged(int, int, int, int, QString)), this, SLOT(on_callState_changed(int, int, int, int, QString)));

    if(metaVoIP != nullptr && metaVoIP->isLoaded())
        metaVoIP->createAccount("sip:"+sipUser+"@"+sipServer, "sip:"+sipServer, sipUser, sipPass);
    else
        error("Loading SIP library failed!");
}

void MainWindow::on_b1_clicked()
{
    ui->number->setText(ui->number->text()+"1");
    if(sipState == "calling")
        metaVoIP->sendDtmf("1");
}

void MainWindow::on_b2_clicked()
{
    ui->number->setText(ui->number->text()+"2");
    if(sipState == "calling")
        metaVoIP->sendDtmf("2");
}

void MainWindow::on_b3_clicked()
{
    ui->number->setText(ui->number->text()+"3");
    if(sipState == "calling")
        metaVoIP->sendDtmf("3");
}

void MainWindow::on_b4_clicked()
{
    ui->number->setText(ui->number->text()+"4");
    if(sipState == "calling")
        metaVoIP->sendDtmf("4");
}

void MainWindow::on_b5_clicked()
{
    ui->number->setText(ui->number->text()+"5");
    if(sipState == "calling")
        metaVoIP->sendDtmf("5");
}

void MainWindow::on_b6_clicked()
{
    ui->number->setText(ui->number->text()+"6");
    if(sipState == "calling")
        metaVoIP->sendDtmf("6");
}

void MainWindow::on_b7_clicked()
{
    ui->number->setText(ui->number->text()+"7");
    if(sipState == "calling")
        metaVoIP->sendDtmf("7");
}

void MainWindow::on_b8_clicked()
{
    ui->number->setText(ui->number->text()+"8");
    if(sipState == "calling")
        metaVoIP->sendDtmf("8");
}

void MainWindow::on_b9_clicked()
{
    ui->number->setText(ui->number->text()+"9");
    if(sipState == "calling")
        metaVoIP->sendDtmf("9");
}

void MainWindow::on_b0_clicked()
{
    ui->number->setText(ui->number->text()+"0");
    if(sipState == "calling")
        metaVoIP->sendDtmf("0");
}

void MainWindow::on_hangButton_clicked()
{
    ui->number->clear();
    metaVoIP->hangupCall(callId);
    sipState = "";
    ui->info->clear();
}

void MainWindow::on_phoneButton_clicked()
{
    if(sipState=="calling")
    {
        metaVoIP->holdCall(callId);
        sipState = "calling";
    }
    else if(sipState=="localRing")
    {
        metaVoIP->acceptCall(callId);
        sipState = "calling";
        ringtone.stop();
    }
    else if(sipState!="localRing" && ui->number->text()!="")
    {
        metaVoIP->makeCall("sip:"+ui->number->text()+"@"+sipServer);
        ui->info->setText("Calling "+ui->number->text()+"...");
        ui->number->clear();
    }
}

void MainWindow::on_callState_changed(int role, int callId, int state, int status, QString remoteUri)
{
    if(state == PJSIP_INV_STATE_EARLY && status == 180)
    {
        if(role == 1)
        {
            int j = 0;
            QList<int> namePos;
            QList<int> numPos;

            while ((j = remoteUri.indexOf("\"", j)) != -1) {
                namePos.append(j);
                ++j;
            }

            numPos.append(remoteUri.indexOf("sip:"));
            numPos.append(remoteUri.indexOf("@"));

            QString name = remoteUri.mid(namePos[0]+1, namePos[1]-1);
            QString num = remoteUri.mid(numPos[0]+4, numPos[1]-(numPos[0]+4));
            QString caller = name;

            if(name.size()<=1)
                caller = num;

            ui->info->setText(caller + " is calling...");
            sipState = "localRing";
            ringtone.play();
        }
        else
        {
            sipState = "remoteRing";
            outgoingRing.play();
        }

        this->callId = callId;
    }
    else if(state == PJSIP_INV_STATE_CONFIRMED && status == 200)
    {
        sipState = "calling";
        ringtone.stop();
        outgoingRing.stop();
    }
    else if(state == PJSIP_INV_STATE_DISCONNECTED)
    {
        ui->info->clear();
        sipState = "";
        ringtone.stop();
        outgoingRing.stop();
    }
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
    ui->bRaute->setFont(font);
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

    outgoingRing.setSource(QUrl::fromLocalFile(":/sounds/ring.wav"));
    outgoingRing.setLoopCount(QSoundEffect::Infinite);
    ringtone.setSource(QUrl::fromLocalFile(":/sounds/ring.wav"));
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
    QMessageBox::about(this, "MetaVoIP 1.0.0", "Copyright:\nMetaSEC 2015\n\nDeveloper:\n- Dominik Fehr <df@metasec.de>");
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
