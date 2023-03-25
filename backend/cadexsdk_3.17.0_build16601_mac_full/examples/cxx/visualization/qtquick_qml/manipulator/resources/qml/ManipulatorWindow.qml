import QtQuick 2.12
import QtQuick.Controls 2.3
import CadEx 1.2

BaseViewerWindow {
    id: root

    property int transformationType: 0
    property int transformationValue: 0
    property bool transformationActive: false
    property bool isAttached: false

    signal resetTransformation()
    signal manipulatorModeChanged (var theMode)

    onTransformationActiveChanged: {
        if (!transformationActive && transformationType == 0) {
            transformationValue = 0
        }
    }

    onTransformationTypeChanged: {
        transformationValue = 0
    }

    enum ManipulatorModes {
        None        = 0x00,
        Translation = 0x01,
        Rotation    = 0x02
    }

    Menu {
        id: manipulatorModeMenu
        title: qsTr("&Manipulator mode")

        property var manipulatorModeMask: ManipulatorWindow.ManipulatorModes.Translation
                                          | ManipulatorWindow.ManipulatorModes.Rotation

        onManipulatorModeMaskChanged: {
            manipulatorModeChanged (manipulatorModeMask);
        }

        function updateMask (theMode, checked)
        {
            manipulatorModeMask = checked ? manipulatorModeMask | theMode
                                          : manipulatorModeMask & ~theMode;
        }

        MenuItem {
            text: qsTr("&Translation")
            checkable: true
            checked: true
            onCheckedChanged: {
                manipulatorModeMenu.updateMask (ManipulatorWindow.ManipulatorModes.Translation, checked);
            }
        }
        MenuItem {
            text: qsTr("&Rotation")
            checkable: true
            checked: true
            onCheckedChanged: {
                manipulatorModeMenu.updateMask (ManipulatorWindow.ManipulatorModes.Rotation, checked)
            }
        }
    }

    onMenuCompleted: {
        menuBarItem.addMenu (manipulatorModeMenu);
    }

    Rectangle {
        id: transformationBar
        radius: 3
        width: 300
        height: 200
        anchors.margins: 10
        anchors.top: parent.top
        anchors.right: parent.right
        color: "#CCFFFFFF"
        border.color: "#55000000"
        readonly property string textColor: "#BB000000"

        Column {
            padding: 20
            spacing: 20
            width: parent.width

            Text {
                width: parent.width - 40
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 14
                font.bold: true
                color: transformationBar.textColor
                text: qsTr ("Transformation")
            }

            Text {
                width: parent.width - 40
                visible: !isAttached || (isAttached && transformationType == 0)
                text: !isAttached ? qsTr ("Please select any part") : qsTr ("Transform or rotate")
                font.pointSize: 13
                font.italic: true
                color: transformationBar.textColor
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                visible: isAttached && transformationType !=0
                text: qsTr ("Type: ") + (transformationType == 1 ? qsTr ("Translation") : qsTr ("Rotation"))
                font.pointSize: 13
                color: transformationBar.textColor
            }

            Text {
                visible: isAttached && transformationType !=0
                text: qsTr ("Result: ") + transformationValue
                font.pointSize: 13
                color: transformationBar.textColor
            }

            Button {
                width: parent.width - 40
                anchors.horizontalCenter: parent.horizontalCenter
                visible: isAttached && transformationType !=0
                enabled: !transformationActive
                text: qsTr ("Reset transformation")
                onClicked: {
                    resetTransformation();
                }
            }
        }
    }
}
