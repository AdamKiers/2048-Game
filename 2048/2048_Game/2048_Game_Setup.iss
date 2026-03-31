; Script Inno Setup pour 2048 Game

[Setup]
AppName=2048 Game
AppVersion=1.0
DefaultDirName={pf}\2048 Game
DefaultGroupName=2048 Game
OutputBaseFilename=2048_Game_Installer
Compression=lzma
SolidCompression=yes

[Languages]
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Files]
; Copie de l'exe et des DLL
Source: "2048.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "sfml-graphics-3.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "sfml-window-3.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "sfml-system-3.dll"; DestDir: "{app}"; Flags: ignoreversion

; Copie du dossier assets (polices, images...)
Source: "assets\*"; DestDir: "{app}\assets"; Flags: recursesubdirs createallsubdirs


[Icons]
Name: "{userdesktop}\2048 Game"; Filename: "{app}\2048.exe"; WorkingDir: "{app}"