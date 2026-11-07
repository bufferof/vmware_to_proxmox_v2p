/*
  Qt Design Studio compatible declarative UI.
  Requires backend context property and the properties/invokables described below.
*/
import QtQuick
import QtQuick.Controls
import V2p_gui

Rectangle {
    id: root
    width: 560
    height: 840
    color: "#111318"

    property color accent: "#5978f5"
    property color surface: "#1b1e26"
    property color stroke: "#343947"
    property color muted: "#939baa"

    Column {
        id: content
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.leftMargin: 26
        anchors.rightMargin: 26
        anchors.topMargin: 26
        spacing: 16


            Column {
                width: parent.width
                spacing: 4
                Text { text: "VMware to Proxmox"; color: "#f6f7fb"; font.pixelSize: 22; font.bold: true }
                Text { text: "Virtual machine migration workspace"; color: root.muted; font.pixelSize: 12 }
            }

            Rectangle { width: parent.width; height: 1; color: root.stroke }

            Column {
                width: parent.width; spacing: 9
                Text { text: "Source virtual machine"; color: "#f3f5f9"; font.pixelSize: 15; font.bold: true }
                Text { text: "Select the folder containing your VMware VM files."; color: root.muted; font.pixelSize: 12 }
                Row {
                    width: parent.width; height: 44; spacing: 8
                    TextField {
                        id: vmFolderField
                        objectName: "vmFolderField"
                        width: parent.width - 100; height: 44
                        text: backend.vmFolder
                        readOnly: true
                        placeholderText: "Choose a VM folder..."
                        color: "#f5f6fa"; placeholderTextColor: "#727b8b"
                        font.pixelSize: 13
                        verticalAlignment: TextInput.AlignVCenter
                        topPadding: 0; bottomPadding: 0
                        leftPadding: 13
                        background: Rectangle { radius: 9; color: root.surface; border.color: root.stroke }
                    }
                    Rectangle {
                        id: vmBrowseButton
                        width: 92
                        height: 44
                        radius: 9
                        color: vmBrowseArea.pressed ? "#343a49" : vmBrowseArea.containsMouse ? "#303747" : "#292e3b"
                        border.color: root.stroke

                        Text {
                            anchors.centerIn: parent
                            text: "Browse"
                            color: "#f5f6fa"
                            font.pixelSize: 12
                            font.bold: true
                        }

                        MouseArea {
                            id: vmBrowseArea
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: backend.selectFile()
                        }
                    }
                }
            }

            Rectangle { width: parent.width; height: 1; color: root.stroke }

            Column {
                width: parent.width; spacing: 10
                Text { text: "Proxmox destination"; color: "#f3f5f9"; font.pixelSize: 15; font.bold: true }
                Row {
                    width: parent.width; spacing: 10
                    Column {
                        width: parent.width * 0.68 - 5; spacing: 7
                        Text { text: "Host / IP address"; color: "#c9cfdb"; font.pixelSize: 12 }
                        TextField {
                            id: proxmoxHostField; objectName: "proxmoxHostField"
                            width: parent.width; height: 44
                            placeholderText: "192.168.1.100"
                            color: "#f5f6fa"; placeholderTextColor: "#727b8b"
                            font.pixelSize: 13; verticalAlignment: TextInput.AlignVCenter
                            topPadding: 0; bottomPadding: 0; leftPadding: 13
                            background: Rectangle { radius: 9; color: root.surface; border.color: root.stroke }
                        }
                    }
                    Column {
                        width: parent.width * 0.32 - 5; spacing: 7
                        Text { text: "SSH port"; color: "#c9cfdb"; font.pixelSize: 12 }
                        TextField {
                            id: sshPortField; objectName: "sshPortField"
                            width: parent.width; height: 44; text: "22"
                            validator: IntValidator { bottom: 1; top: 65535 }
                            color: "#f5f6fa"; font.pixelSize: 13; verticalAlignment: TextInput.AlignVCenter
                            topPadding: 0; bottomPadding: 0; leftPadding: 13
                            background: Rectangle { radius: 9; color: root.surface; border.color: root.stroke }
                        }
                    }
                }
                Column {
                    width: parent.width; spacing: 7
                    Text { text: "SSH username"; color: "#c9cfdb"; font.pixelSize: 12 }
                    TextField {
                        id: sshUserField; objectName: "sshUserField"
                        width: parent.width; height: 44; text: "root"
                        color: "#f5f6fa"; font.pixelSize: 13; verticalAlignment: TextInput.AlignVCenter
                            topPadding: 0; bottomPadding: 0; leftPadding: 13
                        background: Rectangle { radius: 9; color: root.surface; border.color: root.stroke }
                    }
                }
            }

            Rectangle { width: parent.width; height: 1; color: root.stroke }

            Column {
                width: parent.width; spacing: 9
                Text { text: "SSH authentication"; color: "#f3f5f9"; font.pixelSize: 15; font.bold: true }
                Text { text: "Choose a private key authorized on the Proxmox host."; color: root.muted; font.pixelSize: 12 }
                Row {
                    width: parent.width; height: 44; spacing: 8
                    TextField {
                        id: sshKeyField; objectName: "sshKeyField"
                        width: parent.width - 100; height: 44
                        text: backend.sshKeyPath
                        readOnly: true
                        placeholderText: "Select SSH private key..."
                        color: "#f5f6fa"; placeholderTextColor: "#727b8b"
                        font.pixelSize: 13; verticalAlignment: TextInput.AlignVCenter
                            topPadding: 0; bottomPadding: 0; leftPadding: 13
                        background: Rectangle { radius: 9; color: root.surface; border.color: root.stroke }
                    }
                    Rectangle {
                        id: sshBrowseButton
                        width: 92
                        height: 44
                        radius: 9
                        color: sshBrowseArea.pressed ? "#343a49" : sshBrowseArea.containsMouse ? "#303747" : "#292e3b"
                        border.color: root.stroke

                        Text {
                            anchors.centerIn: parent
                            text: "Browse"
                            color: "#f5f6fa"
                            font.pixelSize: 12
                            font.bold: true
                        }

                        MouseArea {
                            id: sshBrowseArea
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: backend.selectSshKey()
                        }
                    }
                }
            }

            Rectangle {
                width: parent.width; height: 90; radius: 12
                color: root.surface; border.color: root.stroke
                Column {
                    anchors.fill: parent; anchors.margins: 13; spacing: 7
                    Text { text: "VM PREVIEW"; color: root.muted; font.pixelSize: 10; font.bold: true; font.letterSpacing: 1.2 }
                    Text { text: "Windows Server 2025"; color: "#f7f8fa"; font.pixelSize: 15; font.bold: true }
                    Text { text: "4 vCPU     •     16 GB RAM     •     120 GB disk"; color: "#abb3c2"; font.pixelSize: 12 }
                }
            }

    }

    Rectangle {
        id: footer
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 128
        color: root.color
        Rectangle { width: parent.width; height: 1; color: root.stroke }
        Column {
            anchors.fill: parent
            anchors.leftMargin: 26
            anchors.rightMargin: 26
            anchors.topMargin: 14
            anchors.bottomMargin: 16
            spacing: 10
            Item {
                width: parent.width
                height: 20

                Text {
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter

                    text: "Migration progress"
                    color: "#dfe3eb"
                    font.pixelSize: 12
                    font.bold: true
                }

                Text {
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter

                    text: Math.round(progressBar.value) + "%"
                    color: "#a9bbff"
                    font.pixelSize: 12
                    font.bold: true
                }
            }
            ProgressBar {
                id: progressBar; objectName: "migrationProgressBar"
                width: parent.width; height: 8; from: 0; to: 100; value: 0
                background: Rectangle { radius: 4; color: "#2a2f3b" }
                contentItem: Item {
                    Rectangle {
                        width: progressBar.visualPosition * parent.width
                        height: parent.height; radius: 4; color: root.accent
                    }
                }
            }
            Rectangle {
                id: startButton
                width: parent.width
                height: 46
                radius: 10
                color: startButtonArea.pressed ? "#3f5ad0" : startButtonArea.containsMouse ? "#6b87ff" : root.accent

                Text {
                    anchors.centerIn: parent
                    text: "Start Migration"
                    color: "#ffffff"
                    font.pixelSize: 14
                    font.bold: true
                }

                MouseArea {
                    id: startButtonArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: backend.startMigration()
                }
            }
        }
    }
}
