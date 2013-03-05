; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Kasuku"
#define MyAppVersion "1.1.0"
#define MyAppPublisher "Tanzania Developers Foundation (TanDF)"
#define MyAppURL "http://hosannahighertech.co.tz/board"
#define MyAppExeName "kasuku.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{5441C1C1-8989-4ADE-AB6B-B111473E577D}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
LicenseFile=C:\hosanna\kasuku\Application\eula\gpl.txt
OutputDir=C:\hosanna\kasuku\output
SetupIconFile=C:\hosanna\kasuku\output\setup.ico
OutputBaseFilename=setup
Compression=lzma/ultra
SolidCompression=yes
AppCopyright=Copyright 2013, Tanzania Developers Foundation
AppContact=stefano@hosannahighertech.co.tz
AppSupportPhone=+255754710410
UninstallDisplayName=Kasuku Player Uninstaller
UninstallDisplayIcon={app}\kasuku.exe
InternalCompressLevel=ultra
CompressionThreads=2

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\hosanna\kasuku\output\ApplicationWin32.exe"; DestDir: "{app}"; DestName: "kasuku.exe"
Source: "C:\hosanna\kasuku\output\plugins\*"; DestDir: "{app}\plugins"; Flags: createallsubdirs recursesubdirs
Source: "C:\hosanna\kasuku\Application\eula\gpl.txt"; DestDir: "{userappdata}\eula"; DestName: "licence.txt"
Source: "C:\hosanna\kasuku\output\libvlc.dll"; DestDir: "{app}"
Source: "C:\hosanna\kasuku\output\libvlccore.dll"; DestDir: "{app}"
Source: "C:\hosanna\kasuku\output\wxbase295u_gcc_custom.dll"; DestDir: "{app}"
Source: "C:\hosanna\kasuku\output\wxmsw295u_adv_gcc_custom.dll"; DestDir: "{app}"
Source: "C:\hosanna\kasuku\output\wxmsw295u_aui_gcc_custom.dll"; DestDir: "{app}"
Source: "C:\hosanna\kasuku\output\wxmsw295u_core_gcc_custom.dll"; DestDir: "{app}"

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

