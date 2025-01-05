#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSound>

void MainWindow::on_b1_clicked()
{
    ui->number->setText(ui->number->text()+"1");
    QSound::play(":/sounds/Dtmf-1.wav");
    if(sipState == "calling")
        metaVoIP->sendDtmf("1");
}

void MainWindow::on_b2_clicked()
{
    ui->number->setText(ui->number->text()+"2");
    QSound::play(":/sounds/Dtmf-2.wav");
    if(sipState == "calling")
        metaVoIP->sendDtmf("2");
}

void MainWindow::on_b3_clicked()
{
    ui->number->setText(ui->number->text()+"3");
    QSound::play(":/sounds/Dtmf-3.wav");
    if(sipState == "calling")
        metaVoIP->sendDtmf("3");
}

void MainWindow::on_b4_clicked()
{
    ui->number->setText(ui->number->text()+"4");
    QSound::play(":/sounds/Dtmf-4.wav");
    if(sipState == "calling")
        metaVoIP->sendDtmf("4");
}

void MainWindow::on_b5_clicked()
{
    ui->number->setText(ui->number->text()+"5");
    QSound::play(":/sounds/Dtmf-5.wav");
    if(sipState == "calling")
        metaVoIP->sendDtmf("5");
}

void MainWindow::on_b6_clicked()
{
    ui->number->setText(ui->number->text()+"6");
    QSound::play(":/sounds/Dtmf-6.wav");
    if(sipState == "calling")
        metaVoIP->sendDtmf("6");
}

void MainWindow::on_b7_clicked()
{
    ui->number->setText(ui->number->text()+"7");
    QSound::play(":/sounds/Dtmf-7.wav");
    if(sipState == "calling")
        metaVoIP->sendDtmf("7");
}

void MainWindow::on_b8_clicked()
{
    ui->number->setText(ui->number->text()+"8");
    QSound::play(":/sounds/Dtmf-8.wav");
    if(sipState == "calling")
        metaVoIP->sendDtmf("8");
}

void MainWindow::on_b9_clicked()
{
    ui->number->setText(ui->number->text()+"9");
    QSound::play(":/sounds/Dtmf-9.wav");
    if(sipState == "calling")
        metaVoIP->sendDtmf("9");
}

void MainWindow::on_b0_clicked()
{
    ui->number->setText(ui->number->text()+"0");
    QSound::play(":/sounds/Dtmf-0.wav");
    if(sipState == "calling")
        metaVoIP->sendDtmf("0");
}

void MainWindow::on_bPound_clicked()
{
    ui->number->setText(ui->number->text()+"#");
    QSound::play(":/sounds/Dtmf-pound.wav");
}

void MainWindow::on_bStar_clicked()
{
    ui->number->setText(ui->number->text()+"*");
    QSound::play(":/sounds/Dtmf-star.wav");
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
