import QtQuick
import V2p_gui

Window {
    width: 560
    height: 840

    minimumWidth: 560
    maximumWidth: 560

    minimumHeight: 840
    maximumHeight: 840

    visible: true
    title: "VMware to Proxmox"

    Screen01 {
        id: mainScreen

        anchors.centerIn: parent
    }

}

