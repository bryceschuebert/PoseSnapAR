import CadEx 1.2
import QtQuick 2.7
import QtQuick.Controls 2.3

BaseWindow {

    Menu {
        id: optionsMenu
        title: qsTr("&Options")

        MenuItem {
            id: gridPlaneOptionsMenuItem
            text: qsTr("&Grid plane")
            checkable: true
            checked: viewPort.gridPlaneEnabled
            onCheckedChanged: {
                viewPort.gridPlaneEnabled = checked;
            }
        }

        MenuItem {
            id: trihedronOptionsMenuItem
            text: qsTr("&Trihedron")
            checkable: true
            checked: viewPort.trihedronEnabled
            onCheckedChanged: {
                viewPort.trihedronEnabled = checked;
            }
        }

        MenuItem {
            id: viewCubeOptionsMenuItem
            text: qsTr("&View cube")
            checkable: true
            checked: viewPort.viewCubeEnabled
            onCheckedChanged: {
                viewPort.viewCubeEnabled = checked;
            }
        }
    }

    menuBarItem.background: Rectangle {
        color: viewCubeStyleItem.normalColor
        anchors.fill: parent
    }

    fileMenuItem.background: Rectangle {
        color: viewCubeStyleItem.normalColor
        implicitWidth: 200
    }

    onMenuCompleted: {
        menuBarItem.addMenu (optionsMenu);
    }

    ModelPrsQtQuick_ViewPort {
        id: viewPort
        objectName: "viewPort"
        anchors.fill: parent
        antialiasing: false
        selectionEnabled: true
        highlightEnabled: true
        trihedronEnabled: true
        gridPlaneEnabled: true
        viewCubeEnabled:  true

        backgroundStyle: ModelPrsQtQuick_BackgroundStyle {
            topColor: "#303030"
            bottomColor: "#303030"
        }
        viewCubeStyle: ModelPrsQtQuick_ViewCubeStyle {
            id: viewCubeStyleItem
            normalColor: "#6e6e6e"
            hoveredColor: "#545454"
            pressedColor: "#474747"
            textColor: "#BBBBBB"
            trihedronTextColor: "#BBBBBB"
        }

        property int viewCubeSize: Math.max (Math.min (viewPort.width, viewPort.height) / 5, 200)
        property int viewCubeMargins: 10

        viewCubeGeometry: Qt.rect (viewPort.width - viewCubeMargins - viewCubeSize,
                                   viewCubeMargins,
                                   viewCubeSize,
                                   viewCubeSize)
    }
}
