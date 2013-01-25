; plee-the-bear.nsi
;
; Windows installer for Plee the Bear

;--------------------------------

; The name of the installer
Name "Plee the Bear Windows installer"

; The file to write
OutFile plee-the-bear.exe

; The default installation directory
InstallDir "$PROGRAMFILES\Plee the Bear"
InstallDirRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\plee-the-bear" "UninstallString"

XPStyle on

;--------------------------------

Page license
Page directory
Page instfiles

;--------------------------------

LicenseData ..\..\GPL

;--------------------------------
Section "Install"

  ; Set output path to the installation directory.
  SetOutPath "$INSTDIR\data"
  
  File "..\data\credits.txt"
  File /r "..\data\animation"
  File /r "..\data\font"
  File /r "..\data\gfx"
  File /r "..\data\level"
  File /r "..\data\mini-game"
  File /r "..\data\model"
  File /r "..\data\music"
  File /r "..\data\script"
  File /r "..\data\sound"

  SetOutPath "$INSTDIR\bin"

  File "..\game\*.dll"
  File "..\bin\*.dll"
  File "..\..\bear-engine\bin\running-bear.exe"
  File "..\..\bear-engine\bin\*.dll"

  SetOutPath "$INSTDIR\share\locale\fr\LC_MESSAGES"

  File /oname=plee-the-bear.mo "..\desktop\locale\plee-the-bear\fr.gmo"
  File /oname=bear-engine.mo "..\..\bear-engine\desktop\locale\bear-engine\fr.gmo"
  File /oname=libclaw.mo "..\desktop\locale\libclaw\fr.gmo"

  SetOutPath "$INSTDIR\share\locale\nn\LC_MESSAGES"

  File /oname=plee-the-bear.mo "..\desktop\locale\plee-the-bear\nn.gmo"
  File /oname=bear-engine.mo "..\..\bear-engine\desktop\locale\bear-engine\nn.gmo"

  SetOutPath "$INSTDIR"

  FileOpen $9 "$INSTDIR\plee-the-bear.bat" w
  FileWrite $9 "bin\running-bear --log-level=error "
  FileWrite $9 "--stats-destination=http://plee-the-bear.sourceforge.net/stats.php "
  FileWrite $9 "$\"--game-name=Plee the Bear$\" --screen-width=800 "
  FileWrite $9 "--screen-height=600 --active-area=500 --data-path=data\ "
  FileWrite $9 "--item-library=bin\libbear_generic_items.dll "
  FileWrite $9 "--item-library=bin\libplee_the_bear.dll "
  FileWrite $9 "--start-level=level/dummy.cl$\r$\n"
  FileClose $9

  File ..\..\GPL
  File ..\..\CCPL
  File ..\desktop\win\ptb.ico

  CreateDirectory "$SMPROGRAMS\Plee the Bear"

  SetOutPath "$INSTDIR"

  CreateShortCut "$SMPROGRAMS\Plee the Bear\Plee the Bear.lnk" "$INSTDIR\plee-the-bear.bat" "" "$INSTDIR\ptb.ico"
  CreateShortCut "$SMPROGRAMS\Plee the Bear\Uninstall.lnk" "$INSTDIR\uninst-plee-the-bear.exe"
  CreateShortCut "$DESKTOP\Plee the Bear.lnk" "$INSTDIR\plee-the-bear.bat" "" "$INSTDIR\ptb.ico"
SectionEnd ; end of "Install"

;--------------------------------
Section -PostInstall
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\plee-the-bear" "DisplayName" "Plee the Bear (uninstall)"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\plee-the-bear" "UninstallString" '"$INSTDIR\uninst-plee-the-bear.exe"'
  WriteUninstaller "uninst-plee-the-bear.exe"
SectionEnd

UninstallText "Ready to uninstall Plee the Bear."

;--------------------------------
Section "Uninstall"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\plee-the-bear"
  Delete "$INSTDIR\uninst-plee-the-bear.exe"
  Delete "$INSTDIR\plee-the-bear.bat"
  Delete "$INSTDIR\GPL"
  Delete "$INSTDIR\CCPL"
  Delete "$INSTDIR\ptb.ico"
  Delete "$DESKTOP\Plee the Bear.lnk"

  RMDir /r "$SMPROGRAMS\Plee the Bear"
  RMDir /r "$INSTDIR\data"
  RMDir /r "$INSTDIR\share"
  RMDir /r "$INSTDIR\bin"

SectionEnd
