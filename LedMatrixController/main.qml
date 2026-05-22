import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

ApplicationWindow {
    id: root
    visible: true
    width: 620
    height: 700
    minimumWidth: 580
    minimumHeight: 660
    title: "LED Matrix Controller — ESP-12E"
    color: "#0d0d0d"

    // ─── Palette colori ───────────────────────────────────────────────
    readonly property color bgDeep:       "#0d0d0d"
    readonly property color bgPanel:      "#141414"
    readonly property color bgCard:       "#1a1a1a"
    readonly property color borderColor:  "#2a2a2a"
    readonly property color ledOff:       "#1e1e1e"
    readonly property color ledOn:        "#ff6a00"
    readonly property color ledGlow:      "#ff8c00"
    readonly property color accent:       "#ff6a00"
    readonly property color textPrimary:  "#f0f0f0"
    readonly property color textMuted:    "#666666"
    readonly property color success:      "#22c55e"
    readonly property color danger:       "#ef4444"

    // ─── Stato drag painting ─────────────────────────────────────────
    property bool isPainting: false
    property bool paintValue: true

    // ─── Stato della griglia 8×8 ─────────────────────────────────────
    // 64 elementi bool, indice = riga*8 + colonna
    property var gridState: {
        var arr = []
        for (var i = 0; i < 64; i++) arr.push(false)
        return arr
    }

    // Converte gridState in lista di 8 stringhe binarie per SerialController
    function buildMatrixRows() {
        var rows = []
        for (var r = 0; r < 8; r++) {
            var s = ""
            for (var c = 0; c < 8; c++) {
                s += gridState[r * 8 + c] ? "1" : "0"
            }
            rows.push(s)
        }
        return rows
    }

    // Imposta tutta la griglia a off
    function clearGrid() {
        var arr = []
        for (var i = 0; i < 64; i++) arr.push(false)
        gridState = arr
    }

    // Imposta tutta la griglia a on
    function fillGrid() {
        var arr = []
        for (var i = 0; i < 64; i++) arr.push(true)
        gridState = arr
    }

    // Toggle singola cella
    function toggleCell(index) {
        var arr = gridState.slice()
        arr[index] = !arr[index]
        gridState = arr
    }

    // Inverte tutto
    function invertGrid() {
        var arr = gridState.slice()
        for (var i = 0; i < 64; i++) arr[i] = !arr[i]
        gridState = arr
    }

    // ─── Log messaggi seriali ─────────────────────────────────────────
    property var logMessages: []

    function appendLog(msg) {
        var arr = logMessages.slice()
        var time = Qt.formatTime(new Date(), "hh:mm:ss")
        arr.push("[" + time + "] " + msg)
        if (arr.length > 50) arr = arr.slice(arr.length - 50)
        logMessages = arr
        // Scroll automatico
        logListView.positionViewAtEnd()
    }

    // Connette i segnali del controller
    Connections {
        target: serialCtrl
        function onSerialDataReceived(data) { appendLog(data) }
        function onStatusMessageChanged()   { appendLog(serialCtrl.statusMessage) }
    }

    // ─── Layout principale ────────────────────────────────────────────
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 16

        // Titolo
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Rectangle {
                width: 4; height: 32
                color: accent
                radius: 2
            }

            Text {
                text: "LED MATRIX"
                font.pixelSize: 22
                font.family: "Courier New"
                font.bold: true
                font.letterSpacing: 4
                color: textPrimary
            }

            Text {
                text: "8×8"
                font.pixelSize: 22
                font.family: "Courier New"
                font.bold: true
                font.letterSpacing: 2
                color: accent
            }

            Item { Layout.fillWidth: true }

            // Indicatore connessione
            Rectangle {
                width: 10; height: 10
                radius: 5
                color: serialCtrl.connected ? success : "#444"

                SequentialAnimation on opacity {
                    running: serialCtrl.connected
                    loops: Animation.Infinite
                    NumberAnimation { to: 0.3; duration: 800 }
                    NumberAnimation { to: 1.0; duration: 800 }
                }
            }

            Text {
                text: serialCtrl.connected ? "ONLINE" : "OFFLINE"
                font.pixelSize: 11
                font.family: "Courier New"
                font.letterSpacing: 2
                color: serialCtrl.connected ? success : textMuted
            }
        }

        // ─── Sezione porta seriale ─────────────────────────────────
        Rectangle {
            Layout.fillWidth: true
            height: 60
            color: bgCard
            radius: 8
            border.color: borderColor
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 10

                Text {
                    text: "PORTA"
                    font.pixelSize: 11
                    font.family: "Courier New"
                    font.letterSpacing: 2
                    color: textMuted
                    Layout.alignment: Qt.AlignVCenter
                }

                // ComboBox porta
                ComboBox {
                    id: portCombo
                    Layout.preferredWidth: 160
                    Layout.fillHeight: true
                    model: serialCtrl.availablePorts
                    enabled: !serialCtrl.connected

                    background: Rectangle {
                        color: portCombo.enabled ? bgPanel : "#111"
                        border.color: portCombo.enabled ? borderColor : "#222"
                        border.width: 1
                        radius: 5
                    }

                    contentItem: Text {
                        text: portCombo.displayText.length > 0 ? portCombo.displayText : "Seleziona..."
                        color: portCombo.enabled ? textPrimary : textMuted
                        font.pixelSize: 13
                        font.family: "Courier New"
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: 10
                    }

                    delegate: ItemDelegate {
                        width: portCombo.width
                        contentItem: Text {
                            text: modelData
                            color: textPrimary
                            font.pixelSize: 13
                            font.family: "Courier New"
                        }
                        background: Rectangle {
                            color: hovered ? "#2a2a2a" : bgPanel
                        }
                    }

                    popup: Popup {
                        y: portCombo.height + 2
                        width: portCombo.width
                        padding: 0
                        background: Rectangle { color: bgPanel; border.color: borderColor; border.width: 1; radius: 5 }
                        contentItem: ListView {
                            clip: true
                            implicitHeight: contentHeight
                            model: portCombo.delegateModel
                        }
                    }
                }

                // Pulsante refresh
                Button {
                    text: "↻"
                    Layout.preferredWidth: 36
                    Layout.fillHeight: true
                    enabled: !serialCtrl.connected
                    onClicked: serialCtrl.refreshPorts()

                    background: Rectangle {
                        color: parent.pressed ? "#333" : (parent.hovered ? "#252525" : bgPanel)
                        border.color: borderColor
                        border.width: 1
                        radius: 5
                    }
                    contentItem: Text {
                        text: parent.text
                        color: textMuted
                        font.pixelSize: 16
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                Item { Layout.fillWidth: true }

                // Pulsante connetti/disconnetti
                Button {
                    id: connectBtn
                    text: serialCtrl.connected ? "DISCONNETTI" : "CONNETTI"
                    Layout.preferredWidth: 120
                    Layout.fillHeight: true
                    enabled: serialCtrl.connected || portCombo.currentText.length > 0

                    onClicked: {
                        if (serialCtrl.connected)
                            serialCtrl.disconnectPort()
                        else
                            serialCtrl.connectToPort(portCombo.currentText)
                    }

                    background: Rectangle {
                        color: {
                            if (!connectBtn.enabled) return "#1a1a1a"
                            if (serialCtrl.connected)
                                return connectBtn.pressed ? "#b91c1c" : (connectBtn.hovered ? "#dc2626" : "#991b1b")
                            else
                                return connectBtn.pressed ? "#c05500" : (connectBtn.hovered ? "#ea6a00" : "#c25400")
                        }
                        radius: 5
                        Behavior on color { ColorAnimation { duration: 120 } }
                    }
                    contentItem: Text {
                        text: connectBtn.text
                        color: connectBtn.enabled ? "#fff" : textMuted
                        font.pixelSize: 11
                        font.family: "Courier New"
                        font.bold: true
                        font.letterSpacing: 1.5
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }

        // ─── Griglia LED 8×8 ──────────────────────────────────────────
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: width  // quadrato
            color: bgCard
            radius: 10
            border.color: borderColor
            border.width: 1

            // Etichette colonne 0-7
            Row {
                id: colLabels
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 0
                x: 28

                Repeater {
                    model: 8
                    Text {
                        width: (gridContainer.width) / 8
                        text: index
                        color: textMuted
                        font.pixelSize: 10
                        font.family: "Courier New"
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }

            // Etichette righe 0-7
            Column {
                id: rowLabels
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.top: colLabels.bottom
                anchors.topMargin: 2
                spacing: 0

                Repeater {
                    model: 8
                    Text {
                        height: (gridContainer.height) / 8
                        text: index
                        color: textMuted
                        font.pixelSize: 10
                        font.family: "Courier New"
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }

            // Griglia cliccabile
            Grid {
                id: gridContainer
                anchors.top: colLabels.bottom
                anchors.topMargin: 2
                anchors.left: rowLabels.right
                anchors.leftMargin: 2
                anchors.right: parent.right
                anchors.rightMargin: 14
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 14

                rows: 8
                columns: 8
                spacing: 4

                property real cellSize: Math.min(
                    (width - spacing * 7) / 8,
                    (height - spacing * 7) / 8
                )

                Repeater {
                    id: cellRepeater
                    model: 64

                    Rectangle {
                        id: cell
                        width: gridContainer.cellSize
                        height: gridContainer.cellSize
                        radius: 4

                        property bool lit: gridState[index] === true
                        color: lit ? ledOn : ledOff
                        border.color: lit ? ledGlow : "#282828"
                        border.width: lit ? 1 : 1

                        // Glow effect per LED accesi
                        layer.enabled: lit
                        layer.effect: null

                        Rectangle {
                            anchors.centerIn: parent
                            width: parent.width * 0.45
                            height: parent.height * 0.45
                            radius: 3
                            color: parent.lit ? "#ffcc88" : "transparent"
                            opacity: parent.lit ? 0.5 : 0
                        }

                        Behavior on color { ColorAnimation { duration: 60 } }
                        Behavior on border.color { ColorAnimation { duration: 60 } }

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true

                            onPressed: {
                                root.isPainting = true
                                root.paintValue = !gridState[index]
                                toggleCell(index)
                            }
                            onReleased: {
                                root.isPainting = false
                            }
                            // Drag per disegnare tenendo premuto
                            onEntered: {
                                if (root.isPainting) {
                                    var arr = gridState.slice()
                                    arr[index] = root.paintValue
                                    gridState = arr
                                }
                            }
                        }
                    }
                }
            }
        }

        // ─── Anteprima binaria + pulsanti azione ──────────────────────
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            // Anteprima testuale
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 80
                color: bgCard
                radius: 8
                border.color: borderColor
                border.width: 1
                clip: true

                Column {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 0

                    Repeater {
                        model: 8
                        Text {
                            property int rowIndex: index
                            text: {
                                var s = ""
                                for (var c = 0; c < 8; c++)
                                    s += gridState[rowIndex * 8 + c] ? "█" : "·"
                                return s
                            }
                            color: accent
                            font.pixelSize: 9
                            font.family: "Courier New"
                            font.letterSpacing: 1
                        }
                    }
                }
            }

            // Pulsanti utility
            ColumnLayout {
                spacing: 6

                Button {
                    text: "CLEAR"
                    Layout.preferredWidth: 80
                    Layout.preferredHeight: 28
                    onClicked: clearGrid()
                    background: Rectangle { color: parent.hovered ? "#2a2a2a" : bgCard; border.color: borderColor; border.width: 1; radius: 5 }
                    contentItem: Text { text: parent.text; color: textMuted; font.pixelSize: 10; font.family: "Courier New"; font.letterSpacing: 1.5; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                }
                Button {
                    text: "FILL"
                    Layout.preferredWidth: 80
                    Layout.preferredHeight: 28
                    onClicked: fillGrid()
                    background: Rectangle { color: parent.hovered ? "#2a2a2a" : bgCard; border.color: borderColor; border.width: 1; radius: 5 }
                    contentItem: Text { text: parent.text; color: textMuted; font.pixelSize: 10; font.family: "Courier New"; font.letterSpacing: 1.5; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                }
                Button {
                    text: "INVERT"
                    Layout.preferredWidth: 80
                    Layout.preferredHeight: 28
                    onClicked: invertGrid()
                    background: Rectangle { color: parent.hovered ? "#2a2a2a" : bgCard; border.color: borderColor; border.width: 1; radius: 5 }
                    contentItem: Text { text: parent.text; color: textMuted; font.pixelSize: 10; font.family: "Courier New"; font.letterSpacing: 1.5; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                }
            }
        }

        // ─── Pulsante INVIA ───────────────────────────────────────────
        Button {
            id: sendBtn
            Layout.fillWidth: true
            Layout.preferredHeight: 48
            enabled: serialCtrl.connected
            text: serialCtrl.connected ? "▶  INVIA ALLA MATRICE" : "CONNETTI UNA PORTA PER INVIARE"

            onClicked: {
                var rows = buildMatrixRows()
                serialCtrl.sendMatrix(rows)
                appendLog("Invio matrice: " + rows.join("|"))
            }

            background: Rectangle {
                color: {
                    if (!sendBtn.enabled) return "#1a1a1a"
                    return sendBtn.pressed ? "#c05500" : (sendBtn.hovered ? "#ea6a00" : "#c25400")
                }
                radius: 8
                border.color: sendBtn.enabled ? (sendBtn.hovered ? ledGlow : accent) : borderColor
                border.width: 1
                Behavior on color { ColorAnimation { duration: 100 } }
            }
            contentItem: Text {
                text: sendBtn.text
                color: sendBtn.enabled ? "#fff" : textMuted
                font.pixelSize: 13
                font.family: "Courier New"
                font.bold: true
                font.letterSpacing: 2
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        // ─── Log seriale ──────────────────────────────────────────────
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 80
            color: bgCard
            radius: 8
            border.color: borderColor
            border.width: 1
            clip: true

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 8
                spacing: 4

                Text {
                    text: "LOG SERIALE"
                    font.pixelSize: 9
                    font.family: "Courier New"
                    font.letterSpacing: 2
                    color: textMuted
                }

                ListView {
                    id: logListView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: logMessages
                    clip: true

                    delegate: Text {
                        width: logListView.width
                        text: modelData
                        color: {
                            if (modelData.includes("Errore")) return danger
                            if (modelData.includes("Matrice") || modelData.includes("ONLINE")) return success
                            return "#888"
                        }
                        font.pixelSize: 10
                        font.family: "Courier New"
                        wrapMode: Text.WrapAnywhere
                    }

                    ScrollBar.vertical: ScrollBar { policy: ScrollBar.AlwaysOff }
                }
            }
        }
    }
}
