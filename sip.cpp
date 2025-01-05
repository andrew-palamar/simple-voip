#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::registerSip()
{
    // Check if already registering
	if (isRegistering) {
		if (metaVoIP) {
			delete metaVoIP; // Clean up the existing MetaVoIP instance
			metaVoIP = nullptr; // Reset pointer
		}
	}

    metaVoIP = new MetaVoIP(ui->sipProtoBox->currentText(), ui->sipPortText->text().toInt());
    sipUser = ui->sipUser->text().simplified();
    sipServer = ui->sipServer->text().simplified();
    sipPass = ui->sipPass->text().simplified();
    sipState = "init";

    connect(metaVoIP, SIGNAL(callStateChanged(int, int, int, int, QString)), this, SLOT(on_callState_changed(int, int, int, int, QString)));
    connect(metaVoIP, SIGNAL(regStateStarted(bool)), this, SLOT(on_regState_started(bool)));
    connect(metaVoIP, SIGNAL(regStateChanged(bool)), this, SLOT(on_regState_changed(bool)));

    if(metaVoIP != Q_NULLPTR && metaVoIP->isLoaded()){
        // Set the flag to indicate we are starting registration
		isRegistering = true;
        metaVoIP->createAccount("sip:"+sipUser+"@"+sipServer, "sip:"+sipServer, sipUser, sipPass);
    }
    else
    {
        error("Loading SIP library failed!");
        isRegistering = false; // Reset the flag since registration failed
    }
}

void MainWindow::on_callState_changed(int role, int callId, int state, int status, QString remoteUri)
{
    this->callId = callId;

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

void MainWindow::on_regState_started(bool status)
{
    if(status)
    {
        ui->phoneButton->setEnabled(true);
        ui->hangButton->setEnabled(true);
    }
    else
    {
        ui->phoneButton->setEnabled(false);
        ui->hangButton->setEnabled(false);
    }
}

void MainWindow::on_regState_changed(bool status)
{
    if(status)
    {
        ui->phoneButton->setEnabled(true);
        ui->hangButton->setEnabled(true);
    }
    else
    {
        ui->phoneButton->setEnabled(false);
        ui->hangButton->setEnabled(false);
    }
}
