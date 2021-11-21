import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    id: window
    minimumWidth:  350
    minimumHeight:  600
    visible: true
    title: qsTr("")

    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 5
        spacing: 5

        ColumnLayout{
            Label {
                id: label
                text: qsTr("Путь к первой директории")
                Layout.fillWidth: true
                }
             TextField {
                id: textField
                placeholderText: qsTr("введите путь")
                Layout.fillWidth: true
                }
             Item {
                 height: 20
             }
             Label {
                 id: label1
                 text: qsTr("Путь ко второй директории")
                 Layout.fillWidth: true
                 }
              TextField {
                 id: textField1
                 placeholderText: qsTr("введите путь")
                 Layout.fillWidth: true
                 }
              Item {
                  height: 20
              }
              Label {
                  id: label2
                  text: qsTr("Результат")
                  Layout.fillWidth: true
                  }

              ListView
              {
                  id: listview
                  height: 300
                  Layout.fillWidth: true
                  spacing: 5
                  model: app.model
                  delegate: Rectangle {
                          height: 25
                          width: 200
                          Text { text: modelData }
                        }
              }
              Item {
                  height: 20
              }


        }
        RowLayout{
            Layout.fillWidth: true
            Button{
                Layout.fillWidth: true
                text: "Method 1"
                onClicked: app.findeEqfileM1(textField.text,textField1.text)

            }
            Button{
                Layout.fillWidth: true
                text: "Method 2"
                onClicked: app.findeEqfileM2(textField.text,textField1.text)
            }
        }
    }
}
