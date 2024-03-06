import QtQuick 2.12

Item {
    id: root
    property color color: "green"
    property color haverColor: "red"
    property color clickColor: "limegreen"
    property alias station: rectext
    property alias area: recarea
    property bool flag: false

    Rectangle {
        width: root.width
        height: root.height
        color: root.color
        // opacity: 0.5
        radius: root.width

        Text {
            id: rectext
            text: ""
            visible: false
            anchors.centerIn: parent
        }

        MouseArea {
            id: recarea
            anchors.fill: parent
            hoverEnabled: true

            onClicked: {
                if (flag === false) {
                    flag = true
                    parent.color = root.clickColor
                }
                else {
                    flag = false
                    parent.color = root.color
                }
            }
        }
    }
}
