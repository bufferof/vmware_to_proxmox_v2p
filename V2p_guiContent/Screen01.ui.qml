/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML.
*/

import QtQuick
import QtQuick.Controls
import V2p_gui

Rectangle {
    width: 520
    height: 560
    color: "#18191d"

    Column {
        anchors {
            fill: parent
            leftMargin: 32
            rightMargin: 32
            topMargin: 32
            bottomMargin: 32
        }

        spacing: 18

        // Header
        Column {
            width: parent.width
            spacing: 4

            Text {
                text: "VMware to Proxmox"
                color: "#ffffff"
                font.pixelSize: 22
                font.bold: true
            }

            Text {
                text: "Simple Migration Tool"
                color: "#9297a3"
                font.pixelSize: 13
            }
        }

        // Source
        Column {
            width: parent.width
            spacing: 7

            Text {
                text: "Source"
                color: "#dfe2e8"
                font.pixelSize: 13
                font.bold: true
            }

            Row {
                width: parent.width
                height: 42
                spacing: 8

                TextField {
                    width: parent.width - 82
                    height: 42

                    text: "Select Your VM Folder"

                    font.pointSize: 10
                    font.family: "Arial"

                    color: "#ffffff"
                    placeholderTextColor: "#666b76"

                    horizontalAlignment: TextInput.AlignLeft
                    verticalAlignment: TextInput.AlignVCenter

                    background: Rectangle {
                        radius: 8
                        color: "#191b20"
                        border.color: "#343740"
                        border.width: 1
                    }

                    leftPadding: 12
                    rightPadding: 12
                }

                Button {
                    width: 74
                    height: 42

                    text: "Browse"

                    background: Rectangle {
                        radius: 8
                        color: parent.down
                               ? "#30343d"
                               : "#292c34"
                        border.color: "#3b3f49"
                        border.width: 1
                    }

                    contentItem: Text {
                        text: parent.text
                        color: "#ffffff"
                        font.pixelSize: 12

                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }

        // Destination
        Column {
            width: parent.width
            spacing: 7

            Text {
                text: "Destination"
                color: "#dfe2e8"
                font.pixelSize: 13
                font.bold: true
            }

            TextField {
                width: parent.width
                height: 42

                text: "Proxmox Host (e.g. pve01.example.com)"

                font.pointSize: 10
                font.family: "Arial"

                color: "#ffffff"
                placeholderTextColor: "#666b76"

                horizontalAlignment: TextInput.AlignLeft
                verticalAlignment: TextInput.AlignVCenter

                background: Rectangle {
                    radius: 8
                    color: "#191b20"
                    border.color: "#343740"
                    border.width: 1
                }

                leftPadding: 12
                rightPadding: 12
            }
        }

        // VM Information
        Rectangle {
            width: parent.width
            height: 90

            radius: 10
            color: "#1c1e23"

            Column {
                anchors.fill: parent
                anchors.margins: 14
                spacing: 6

                Text {
                    text: "Virtual Machine"
                    color: "#9297a3"
                    font.pixelSize: 11
                }

                Text {
                    text: "Windows Server 2025"
                    color: "#ffffff"
                    font.pixelSize: 14
                    font.bold: true
                }

                Text {
                    text: "4 CPU  •  16 GB RAM  •  120 GB Disk"
                    color: "#aeb3bd"
                    font.pixelSize: 12
                }
            }
        }

        // Progress Bar
        ProgressBar {
            id: progressBar

            width: parent.width
            height: 15

            from: 0
            to: 100
            value: 0

            background: Rectangle {
                implicitHeight: 8

                radius: 4
                color: "#191b20"
                border.color: "#343740"
                border.width: 1
            }

            contentItem: Item {
                Rectangle {
                    width: progressBar.visualPosition * parent.width
                    height: parent.height

                    radius: 4
                    color: "#1a2c7d"

                    Behavior on width {
                        NumberAnimation {
                            duration: 200
                            easing.type: Easing.OutCubic
                        }
                    }
                }
            }
        }

        // Start Migration
        Button {
            width: parent.width
            height: 46

            text: "Start Migration"

            onClicked: {
                backend.startMigration()
            }

            background: Rectangle {
                radius: 9

                color: parent.down
                       ? "#16245f"
                       : "#1a2c7d"
            }

            contentItem: Text {
                text: parent.text
                color: "#ffffff"

                font.pixelSize: 14
                font.bold: true

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}