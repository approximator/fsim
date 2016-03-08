/*!
* Copyright © 2015-2016 Oleksii Aliakin. All rights reserved.
* Author: Oleksii Aliakin (alex@nls.la)
* Author: Andrii Shelest
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

import qbs
import qbs.FileInfo

CppApplicationBase {
    targetName: project.appAppTarget

    Depends { name: "Qt"; submodules: ["qml", "quick", "gui", "svg"] }
    Depends { name: "qml_material" }
    Depends { name: "libqtqmltricks-qtqmlmodels" }
    Depends { name: "libqtqmltricks-qtsupermacros" }

    Group {
        name: "Sources"
        files: [
            "*.cpp",
            "*.h"
        ]
    }

    Group {
        name: "resources"
        files: "*.qrc"
    }

    cpp.defines: project.generalDefines.concat('QTQMLTRICKS_NO_PREFIX_ON_GETTERS')

    Properties {
        condition: project.justRunExperiments
        cpp.defines: project.generalDefines.concat(['JUST_RUN_EXPERIMENTS', 'QTQMLTRICKS_NO_PREFIX_ON_GETTERS'])
    }

    targetInstallDir: project.appInstallDir
    targetInstallPrefix: project.appBinDir
}
