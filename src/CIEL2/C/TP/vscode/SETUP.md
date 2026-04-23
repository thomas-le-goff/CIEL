# Setup de VSCode

## Extensions

```shell
code --install-extension ms-azuretools.vscode-containers
code --install-extension ms-python.debugpy
code --install-extension ms-python.python
code --install-extension ms-python.vscode-pylance
code --install-extension ms-python.vscode-python-envs
code --install-extension ms-vscode-remote.remote-containers
code --install-extension ms-vscode.cmake-tools
code --install-extension ms-vscode.cpptools
code --install-extension ms-vscode.cpptools-extension-pack
code --install-extension ms-vscode.cpptools-themes
code --install-extension ms-vscode.makefile-tools
code --install-extension ms-vscode.powershell
```

## Configuration globale

```json
{
    "workbench.colorTheme": "Visual Studio 2017 Dark - C++",
    "[c]": {
        "editor.defaultFormatter": "ms-vscode.cpptools"
    },
    "[markdown]": {
        "editor.defaultFormatter": "tehnix.vscode-tidymarkdown"
    },
    "makefile.configureOnOpen": true,
    "debug.disassemblyView.showSourceCode": false,
    "files.autoSave": "afterDelay",
    "C_Cpp.codeAnalysis.clangTidy.enabled": true,
    "C_Cpp.codeAnalysis.runAutomatically": true
}
```