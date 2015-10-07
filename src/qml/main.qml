import QtQuick 2.4
import Material 0.1
import Qt.labs.settings 1.0

ApplicationWindow {
    id: mainWindow
    property string themeStyle: "dark" // default

    title: "Forces simulation"

    Component.onCompleted: {
        if (themeStyle === "dark") {
            Theme.light.light = false;
            theme.primaryColor = Palette.colors["blueGrey"]["500"];
            theme.primaryDarkColor = Palette.colors["grey"]["900"];
            theme.accentColor = Palette.colors["deepOrange"]["600"]
        } else {
            Theme.light.light = true;
            theme.primaryColor = Palette.colors["blue"]["500"];
            theme.primaryDarkColor = Palette.colors["blueGrey"]["700"];
            theme.accentColor = Palette.colors["teal"]["500"]
        }
    }

    width: 1280
    height: 720
    visible: true

    CanvasPage {
        id: startpage
    }

    initialPage: startpage

    Settings {
        property alias x: mainWindow.x
        property alias y: mainWindow.y
        property alias width:  mainWindow.width
        property alias height: mainWindow.height
    }
}



