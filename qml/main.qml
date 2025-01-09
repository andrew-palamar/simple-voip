import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

// Rectangle {
ApplicationWindow {
    id: mainWindow
    visible: true
    // Hide window frame
    // flags: Qt.FramelessWindowHint
    width: 720
    height: 720
    title: "simple-voip"

    menuBar: MenuBar {
        enabled: false
        visible: false
        Menu {
            title: "&Help"
            Action {
                text: "&About"
                icon.source: "/images/logo_transparent.png"
            }
            Action {
                text: "About &Qt"
                icon.source: "/images/about.png"
            }
        }
    }

    TabBar {
        id: tabBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        TabButton {
            text: "Phone"
            font.pixelSize: 24
        }
        TabButton {
            text: "Settings"
            font.pixelSize: 24
        }
    }

    StackLayout {
        id: stackLayout
        width: mainWindow.width - 40
        height: mainWindow.height - menuBar.height - 2 * tabBar.height
        x: parent.x + 20
        y: tabBar.height + 20
        anchors.left: mainWindow.left
        currentIndex: tabBar.currentIndex

        // Phone Tab
        GridLayout {
            columns: 1
            rows: 7
            // Status string
            TextField {
                id: info
                Layout.fillWidth: true
                placeholderText: "Status"
                readOnly: true
                enabled: false
                horizontalAlignment: TextInput.AlignHCenter
                text: backend.statusStr
                font.pixelSize: 24
            }

            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    RoundButton {
                        radius: height / 4
                        anchors.fill: parent
                        text: "1"
                        font.pixelSize: 48
                        onClicked: backend.on_b1_clicked()
                    }
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    RoundButton {
                        radius: height / 4
                        anchors.fill: parent
                        text: "2"
                        font.pixelSize: 48
                        onClicked: backend.on_b2_clicked()
                    }
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    RoundButton {
                        radius: height / 4
                        anchors.fill: parent
                        text: "3"
                        font.pixelSize: 48
                        onClicked: backend.on_b3_clicked()
                    }
                }
            }

            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    RoundButton {
                        radius: height / 4
                        anchors.fill: parent
                        text: "4"
                        font.pixelSize: 48
                        onClicked: backend.on_b4_clicked()
                    }
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    RoundButton {
                        radius: height / 4
                        anchors.fill: parent
                        text: "5"
                        font.pixelSize: 48
                        onClicked: backend.on_b5_clicked()
                    }
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    RoundButton {
                        radius: height / 4
                        anchors.fill: parent
                        text: "6"
                        font.pixelSize: 48
                        onClicked: backend.on_b6_clicked()
                    }
                }
            }

            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    RoundButton {
                        radius: height / 4
                        anchors.fill: parent
                        text: "7"
                        font.pixelSize: 48
                        onClicked: backend.on_b7_clicked()
                    }
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    RoundButton {
                        radius: height / 4
                        anchors.fill: parent
                        text: "8"
                        font.pixelSize: 48
                        onClicked: backend.on_b8_clicked()
                    }
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    RoundButton {
                        radius: height / 4
                        anchors.fill: parent
                        text: "9"
                        font.pixelSize: 48
                        onClicked: backend.on_b9_clicked()
                    }
                }
            }

            RowLayout {
                spacing: 5
                Layout.alignment: Qt.AlignHCenter
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    RoundButton {
                        radius: height / 4
                        anchors.fill: parent
                        text: "*"
                        font.pixelSize: 48
                        onClicked: backend.on_bStar_clicked()
                    }
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    RoundButton {
                        radius: height / 4
                        anchors.fill: parent
                        text: "0"
                        font.pixelSize: 48
                        onClicked: backend.on_b0_clicked()
                    }
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    RoundButton {
                        radius: height / 4
                        anchors.fill: parent
                        text: "#"
                        font.pixelSize: 48
                        onClicked: backend.on_bPound_clicked()
                    }
                }
            }

            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    RoundButton {
                        radius: height / 4
                        anchors.fill: parent
                        icon.source: "/images/phone.png"
                        icon.height: 80
                        icon.width: 80
                        onClicked: backend.on_phoneButton_clicked()
                        enabled: backend.buttonPhoneEnabled
                        // text: "Call/Answer"
                        // font.pixelSize: 48
                    }
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    RoundButton {
                        radius: height / 4
                        anchors.fill: parent
                        icon.source: "/images/phone_hang.png"
                        icon.height: 80
                        icon.width: 80
                        onClicked: backend.on_hangButton_clicked()
                        enabled: backend.buttonHangupEnabled
                        // text: "Hangup"
                        // font.pixelSize: 48
                    }
                }
            }

            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                TextField {
                    id: txtNumber
                    text: backend.numberStr
                    readOnly: false
                    width: 360
                    font.pixelSize: 24
                }

                Rectangle {
                    y: txtNumber.y
                    Layout.leftMargin: 5
                    height: txtNumber.height
                    width: height
                    color: "transparent"
                    RoundButton {
                        radius: height / 4
                        anchors.fill: parent
                        text: "[X]"
                        font.pixelSize: 24
                        onClicked: backend.setNumberStr("")
                    }
                }
            }
        }// GridLayout

        // Settings Tab
        GridLayout {

            columns: 1
            RowLayout {
                Label {
                    text: "SIP Username:"
                    font.pixelSize: 24
                }
                TextField {
                    id: sipUser
                    placeholderText: "1234"
                    horizontalAlignment: TextInput.AlignHCenter
                    text: backend.sipUserStr
                    font.pixelSize: 24
                    Layout.fillWidth: true
                    onTextChanged: {
                        backend.sipUserStr = text;
                    }
                }
            }

            RowLayout {
                Label {
                    text: "SIP Password:"
                    font.pixelSize: 24
                }
                TextField {
                    id: sipPass
                    echoMode: TextInput.Password
                    horizontalAlignment: TextInput.AlignHCenter
                    font.pixelSize: 24
                    Layout.fillWidth: true
                    text: backend.sipPassStr
                    onTextChanged: {
                        backend.sipPassStr = text;
                    }
                }
            }

            RowLayout {
                Label {
                    text: "SIP Server:"
                    font.pixelSize: 24
                }
                TextField {
                    id: sipServer
                    placeholderText: "192.168.31.222"
                    horizontalAlignment: TextInput.AlignHCenter
                    font.pixelSize: 24
                    Layout.fillWidth: true
                    text: backend.sipServerStr
                    onTextChanged: {
                        backend.sipServerStr = text;
                    }
                }
            }

            RowLayout {
                Label {
                    text: "SIP Port:"
                    font.pixelSize: 24
                }
                TextField {
                    id: sipPort
                    placeholderText: "5060"
                    horizontalAlignment: TextInput.AlignHCenter
                    Layout.fillWidth: true
                    font.pixelSize: 24
                    text: backend.sipPortStr
                    onTextChanged: {
                        backend.sipPortStr = text;
                    }
                }
            }

            RowLayout {
                Label {
                    text: "SIP Protocol:"
                    font.pixelSize: 24
                }
                ComboBox {
                    id: sipProtoBox
                    Layout.fillWidth: true
                    model: ["UDP", "TCP"]
                    font.pixelSize: 24
                    currentIndex: backend.currentProtocolIndex
                    onCurrentIndexChanged: {
                        backend.setProtocolIndex(currentIndex);
                    }
                }
            }
            RowLayout {
                Label {
                    text: "Input Device:"
                    font.pixelSize: 24
                }
            }
            RowLayout {
                ComboBox {
                    id: inputDeviceComboBox
                    Layout.fillWidth: true
                    font.pixelSize: 24
                    model: backend.inputDevicesList
                    currentIndex: backend.audioInputIndex
                    onCurrentTextChanged: {
                        // console.log("Selected input device: " + currentText);
                        backend.setInputDevice(currentText);
                    }
                }
            }
            RowLayout {
                Label {
                    text: "Output Device:"
                    font.pixelSize: 24
                }
            }
            RowLayout {
                ComboBox {
                    id: outputDeviceComboBox
                    Layout.fillWidth: true
                    font.pixelSize: 24
                    model: backend.inputDevicesList
                    currentIndex: backend.audioOutputIndex
                    onCurrentTextChanged: {
                        // console.log("Selected output device: " + currentText);
                        backend.setOutputDevice(currentText);
                    }
                }
            }

            RowLayout {
                Label {
                }
                RoundButton {
                    id: saveButton
                    radius: height / 4
                    font.pixelSize: 24
                    text: "Save"
                    onClicked: backend.on_saveButton_clicked()
                }
            }
        }
    }

    // Error dialog
    Dialog {
        id: errorDialog
        title: "Error"
        anchors.centerIn: parent
        standardButtons: Dialog.Ok
        onAccepted: backend.handleError("")

        Column {
            Text {
                id: errorMessageText
                text: backend.errorMessage
            }
        }
    }

    Connections {
        target: backend
        function onErrorMessageChanged() {
            if (backend.errorMessage !== "") {
                errorMessageText.text = backend.errorMessage;
                errorDialog.open();
            }
        }

        function onAudioInputsChanged() {
            // Get the current input device string
            var currentInputDeviceStr = backend.getInputDeviceStr();

            // Check if the string is not empty
            if (currentInputDeviceStr !== "") {
                // Get the input devices from the model
                var devices = backend.getInputDevices();
                var index = devices.indexOf(currentInputDeviceStr);
                // console.log("device`s index: " + index);

                // Check if the value exists in the model
                if (index !== -1) {
                    // Set the current index of the ComboBox
                    inputDeviceComboBox.currentIndex = index;
                }
            }
        }

        // function onAudioOutputChanged() {
        //     // Get the current input device string
        //     var currentOutputDeviceStr = backend.getOutputDeviceStr();

        //     // Check if the string is not empty
        //     if (currentOutputDeviceStr !== "") {
        //         // Get the input devices from the model
        //         var devices = backend.getOutputDevices();
        //         var index = devices.indexOf(currentOutputDeviceStr);

        //         // Check if the value exists in the model
        //         if (index !== -1) {
        //             // Set the current index of the ComboBox
        //             outputDeviceComboBox.currentIndex = index;
        //         }
        //     }
        // }
    }
}// StackLayout end

