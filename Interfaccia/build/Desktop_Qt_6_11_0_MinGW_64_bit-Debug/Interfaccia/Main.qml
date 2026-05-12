import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    property string currentMode: "reactive"  // ← era mancante
    property var mp: typeof musicProvider !== "undefined" ? musicProvider : null

    width: 1200
    height: 750
    visible: true
    title: "Q9 Music LED Visualizer"
    color: "#111111"

    // Token Spotify — va nel Window, non nel RowLayout
    Component.onCompleted: {
        if (mp) mp.setSpotifyToken("IL_TUO_ACCESS_TOKEN")
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // SINISTRA - cover canzone + lyrics
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#0d0d1a"

            Image {
                id: albumCover
                anchors.fill: parent
                source: mp && mp.coverUrl !== "" ? mp.coverUrl : "cover.jpg"
                fillMode: Image.PreserveAspectCrop

                Rectangle {
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: 120
                    gradient: Gradient {
                        orientation: Gradient.Vertical
                        GradientStop { position: 0.0; color: "transparent" }
                        GradientStop { position: 1.0; color: "#cc000000" }
                    }
                }

                // Nome canzone sovrapposto
                Column {
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.margins: 16
                    spacing: 4

                    Text {
                        text: mp && mp.title   !== "" ? mp.title  : "Just Dance"
                        color: "#ffffff"
                        font.pixelSize: 22
                        font.bold: true
                    }
                    Text {
                        text: mp && mp.artist  !== "" ? mp.artist : "Lady Gaga ft. Colby O'Donis"
                        color: "#aaaaaa"
                        font.pixelSize: 13
                    }
                    Text {
                        text: mp && mp.album   !== "" ? mp.album  : "The Fame"
                        color: "#666666"
                        font.pixelSize: 11
                    }
                }
            }

            // Pannello lyrics in basso
            Rectangle {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 160
                color: "#0a0a0a"
                border.color: "#222222"
                border.width: 1

                Text {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.margins: 14
                    text: "CURRENT LYRICS"
                    color: "#666666"
                    font.pixelSize: 11
                    font.letterSpacing: 1.5
                }

                ListView {
                    anchors.top: parent.top
                    anchors.topMargin: 30
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.margins: 14
                    clip: true

                    model: mp ? mp.lyrics : []
                    currentIndex: mp ? mp.currentLyricIndex : 0

                    onCurrentIndexChanged: positionViewAtIndex(currentIndex, ListView.Center)

                    delegate: Text {
                        width: ListView.view.width
                        text: modelData
                        color: index === (mp ? mp.currentLyricIndex : 0) ? "#ffffff" : "#555555"
                        font.pixelSize: index === (mp ? mp.currentLyricIndex : 0) ? 15 : 13
                        font.bold: index === (mp ? mp.currentLyricIndex : 0)
                        wrapMode: Text.WordWrap
                        topPadding: 2
                        bottomPadding: 2

                        Behavior on color { ColorAnimation { duration: 200 } }
                        Behavior on font.pixelSize { NumberAnimation { duration: 150 } }
                    }
                }
            }
        }

        // DESTRA - pannello controlli
        Rectangle {
            width: 250
            Layout.fillHeight: true
            color: "#1a1a1a"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 12

                Text {
                    text: "MODE SELECTOR"
                    color: "#888888"
                    font.pixelSize: 11
                    font.letterSpacing: 1.5
                }

                // Bottone Modalità Reattiva
                Rectangle {
                    Layout.fillWidth: true
                    height: 65
                    color: currentMode === "reactive" ? "#0d1f17" : "#111111"
                    border.color: currentMode === "reactive" ? "#2ecc71" : "#333333"
                    border.width: 2
                    radius: 6

                    Column {
                        anchors.centerIn: parent
                        spacing: 2
                        Text {
                            text: "MODALITÀ REATTIVA"
                            color: currentMode === "reactive" ? "#2ecc71" : "#cccccc"
                            font.pixelSize: 12
                            font.bold: true
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                        Text {
                            text: "(AUDIO)"
                            color: "#555555"
                            font.pixelSize: 10
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: currentMode = "reactive"
                    }
                }

                // Bottone Modalità Manuale
                Rectangle {
                    Layout.fillWidth: true
                    height: 65
                    color: currentMode === "manual" ? "#0d1525" : "#111111"
                    border.color: currentMode === "manual" ? "#3498db" : "#333333"
                    border.width: 2
                    radius: 6

                    Column {
                        anchors.centerIn: parent
                        spacing: 2
                        Text {
                            text: "MODALITÀ MANUALE"
                            color: currentMode === "manual" ? "#3498db" : "#cccccc"
                            font.pixelSize: 12
                            font.bold: true
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                        Text {
                            text: "(STATICA)"
                            color: "#555555"
                            font.pixelSize: 10
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: currentMode = "manual"
                    }
                }

                // Brightness
                Text {
                    text: "Brightness:"
                    color: "#888888"
                    font.pixelSize: 11
                }

                Slider {
                    id: brightnessSlider
                    Layout.fillWidth: true
                    from: 0
                    to: 255
                    value: 180
                }

                Text {
                    text: Math.round(brightnessSlider.value)
                    color: "#cccccc"
                    font.pixelSize: 11
                }

                Item { Layout.fillHeight: true }

                // Bottone START
                Rectangle {
                    Layout.fillWidth: true
                    height: 45
                    color: "#2ecc71"
                    radius: 6

                    Text {
                        anchors.centerIn: parent
                        text: "▶  START VISUALIZER"
                        color: "#000000"
                        font.pixelSize: 13
                        font.bold: true
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: console.log("START")
                    }
                }

                // Bottone STOP
                Rectangle {
                    Layout.fillWidth: true
                    height: 45
                    color: "#e74c3c"
                    radius: 6
                    Layout.bottomMargin: 4

                    Text {
                        anchors.centerIn: parent
                        text: "■  STOP"
                        color: "#ffffff"
                        font.pixelSize: 13
                        font.bold: true
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: console.log("STOP")
                    }
                }

                // Color picker - solo in modalità manuale
                Rectangle {
                    id: colorPicker          // ← aggiungi un id
                    Layout.fillWidth: true
                    height: 40
                    color: "transparent"
                    visible: currentMode === "manual"

                    property string selectedColor: "#e74c3c"  // ← rimane qui

                    Row {
                        anchors.centerIn: parent
                        spacing: 8

                        Repeater {
                            model: ["#e74c3c", "#2ecc71", "#3498db", "#1abc9c", "#9b59b6", "#f1c40f", "#ecf0f1"]

                            Rectangle {
                                width: 24
                                height: 24
                                radius: 4
                                color: modelData
                                border.color: colorPicker.selectedColor === modelData ? "#ffffff" : "transparent"
                                border.width: 2

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: colorPicker.selectedColor = modelData  // ← usa l'id diretto
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}