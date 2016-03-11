import QtQuick 2.1
import QtQuick.Controls 1.0

ApplicationWindow {
    id: applicationWindow1
    title: qsTr("Hello World")
    width: 640
    height: 480

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Label {
        id: motorDataLabel
        color: "#9f9d9d"
        text: qsTr("Motor Speeds (1-4)")
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 8
        enabled: false
    }

    Label {
        id: gyroDataLabel
        x: 158
        color: "#9f9d9d"
        text: qsTr("Gyro Axis")
        anchors.top: parent.top
        anchors.topMargin: 8
        enabled: false
    }

    Image {
        id: fpvImageCapture
        x: 420
        width: 212
        height: 122
        anchors.top: parent.top
        anchors.topMargin: 31
        anchors.right: parent.right
        anchors.rightMargin: 8
        source: "qrc:/qtquickplugin/images/template_image.png"
    }

    Label {
        id: fpvImageLabel
        x: 420
        color: "#9f9d9d"
        text: qsTr("FPV Capture")
        anchors.right: parent.right
        anchors.rightMargin: 135
        anchors.top: parent.top
        anchors.topMargin: 8
        enabled: false
    }

    Image {
        id: geoImage
        width: 200
        height: 167
        anchors.top: parent.top
        anchors.topMargin: 182
        anchors.left: parent.left
        anchors.leftMargin: 8
        source: "qrc:/qtquickplugin/images/template_image.png"
    }

    Label {
        id: geoLocationLabel
        color: "#9f9d9d"
        text: qsTr("GEO Location")
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 159
        enabled: false
    }

    Label {
        id: tempLabel
        x: 463
        y: 423
        color: "#9f9d9d"
        text: qsTr("CPU Temp (Degrees)")
        anchors.right: parent.right
        anchors.rightMargin: 37
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        enabled: false
    }

    ProgressBar {
        id: tempStatBar
        x: 609
        y: 255
        width: 23
        height: 185
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        anchors.right: parent.right
        anchors.rightMargin: 8
        enabled: false
        orientation: 0
        maximumValue: 90
        indeterminate: false
    }

    Grid {
        id: motorData
        width: 125
        height: 122
        anchors.top: parent.top
        anchors.topMargin: 31
        anchors.left: parent.left
        anchors.leftMargin: 14

        ProgressBar {
            id: motor1StatBar
            width: 23
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            enabled: false
            orientation: 0
        }

        ProgressBar {
            id: motor2StatBar
            width: 23
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            enabled: false
            orientation: 0
        }

        ProgressBar {
            id: motor3StatBar
            width: 23
            anchors.left: parent.left
            anchors.leftMargin: 60
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            enabled: false
            orientation: 0
        }

        ProgressBar {
            id: motor4StatBar
            width: 23
            anchors.left: parent.left
            anchors.leftMargin: 90
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            enabled: false
        orientation: 0
    }



    }

    Grid {
        id: gyroData
        x: 158
        width: 200
        height: 122
        anchors.top: parent.top
        anchors.topMargin: 31

        ProgressBar {
            id: gyroXaxis
            orientation: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
        }

        ProgressBar {
            id: gyroYaxis
            orientation: 0
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
        }

        ProgressBar {
            id: gyroZaxis
            anchors.left: parent.left
            anchors.leftMargin: 60
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            orientation: 0
        }



    }

    Button {
        id: connect
        y: 447
        width: 92
        height: 27
        text: qsTr("Connect")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 8
    }

    TextInput {
        id: ipField
        y: 416
        width: 96
        height: 25
        text: qsTr("Connect")
        anchors.bottom: connect.top
        anchors.bottomMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 10
        inputMask: qsTr("000.000.000.000;_")
        cursorVisible: false
        horizontalAlignment: TextInput.AlignLeft
        font.underline: false
        font.bold: false
        font.italic: false
        font.pixelSize: 14
    }

    Label {
        id: ipAddrLabel
        y: 393
        width: 75
        height: 17
        color: "#9f9d9d"
        text: qsTr("IP Address:")
        enabled: false
        anchors.bottom: ipField.top
        anchors.bottomMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    TextEdit {
        id: textEdit1
        text: qsTr("============== QuadView v0.1 ==============")
        anchors.top: fpvImageCapture.bottom
        anchors.topMargin: 29
        anchors.right: tempStatBar.left
        anchors.rightMargin: 6
        anchors.left: geoImage.right
        anchors.leftMargin: 6
        anchors.bottom: tempLabel.top
        anchors.bottomMargin: 6
        antialiasing: true
        readOnly: true
        cursorVisible: true
        selectionColor: "#7878f8"
        font.pixelSize: 16
    }

    TextField {
        id: textField1
        y: 448
        height: 25
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 7
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: connect.right
        anchors.leftMargin: 6
        placeholderText: qsTr("Enter Commands")
    }
}
