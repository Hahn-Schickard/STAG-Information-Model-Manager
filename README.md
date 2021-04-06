[![pipeline status](https://git.hahn-schickard.de/hahn-schickard/software-sollutions/application-engineering/internal/opc_ua_dev_group/gateway-project/information-model-manager/badges/master/pipeline.svg)](https://git.hahn-schickard.de/hahn-schickard/software-sollutions/application-engineering/internal/opc_ua_dev_group/gateway-project/information-model-manager/-/commits/master)
[![coverage report](https://git.hahn-schickard.de/hahn-schickard/software-sollutions/application-engineering/internal/opc_ua_dev_group/gateway-project/information-model-manager/badges/master/coverage.svg)](https://git.hahn-schickard.de/hahn-schickard/software-sollutions/application-engineering/internal/opc_ua_dev_group/gateway-project/information-model-manager/-/commits/master)

<img src="docs/code_documentation/vendor-logo.png" alt="" width="200"/>

# Information Model Manager

STAG Information Model Manager, provides concrete [Information Model](https://git.hahn-schickard.de/hahn-schickard/software-sollutions/application-engineering/internal/opc_ua_dev_group/gateway-project/information-model) Interface Implementations, as well as concrete [Event_Source](https://git.hahn-schickard.de/hahn-schickard/software-sollutions/application-engineering/internal/cpp-projects/event-model) implementation for [Technology Adapter Interface](https://git.hahn-schickard.de/hahn-schickard/software-sollutions/application-engineering/internal/opc_ua_dev_group/gateway-project/technology-adapter-interface) and [Data Consumer Adapter Interface](https://git.hahn-schickard.de/hahn-schickard/software-sollutions/application-engineering/internal/opc_ua_dev_group/gateway-project/data-consumer-adapter-interface) to hook up to. 

## Dependencies
### Required

* cmake - build system generator
* python3 - used by utilities
* conan - dependnecy handler, see [SSO Wiki](https://ssowiki.hsg.privat/en/Softwareentwicklung/Cpp/Conan_Package_Manager)

### Optional

* clang-format - to use formating tools
* clang-tidy - to use static code analysis
* doxygen - to generate documentation from code

## Visual Studio Code Support

### Recomended Plugins:
* [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)  - provides linking to inellisense and code debuggers
* [C++ Intellisense](https://marketplace.visualstudio.com/items?itemName=austin.code-gnu-global) - provides code highlithing and quick navigation
* [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) - provides CMake highlithing, configruing, building
* [Clang-Format](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format) - provides code formating
* [Test Explorer UI](https://marketplace.visualstudio.com/items?itemName=hbenl.vscode-test-explorer) - provides test runner integration
* [C++ TestMate](https://marketplace.visualstudio.com/items?itemName=matepek.vscode-catch2-test-adapter) - provides google-test framework adapter for Test Explorer UI

### Cmake Integration
A CMake variant file is provided with this repository for easy cmake configuration setup. This functionallity requires [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) plugin to be installed. After Visual Code has been started Open Controll Panel with *Cntrl + Shift + P* and type in CMake: Select Variant to start configuring your cmake project configuration. 
