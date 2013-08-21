AniSimProjekt
=====================

Animation & Simulation Projekt
Partikelsimulation und co. kg.

________________________________

How To Inschtall in Eclipse CDT mit OpenGL n stuff:

+ Dateien von GitHub klonen ( Clone in Desktop, am besten vorher Default Storage Directory auf Eclipse Workspace setzen)
+ in Eclipse C++ Projekt mit Namen AniSimProjekt erstellen (Warnung: "Ordner mit gleichem Namen bereits vorhanden" Ignorieren)
+ in Eclipse Projekteinstellungen -> C/C++ Build -> Settings -> Tool Settings -> GCC C++ Compiler -> Includes
  - hinzufügen -> Workspace... -> AniSimProjektEclipses/BasisApplication und alle anderen Ordner einzeln hinzufügen
+ MinGW C++ Linker -> Libraries 
  - hinzufügen: opengl32
                glut32
                glu32
+ Rechtsklick auf Projekt -> Build Project ( main() befindet ich in EmptyGLUTWnd.cpp )

________________________________

Vor jedem mal arbeiten -> immer erst brav die aktuelle Dateien vom Server ziehen
Nach jedem mal arbeiten -> Dateien am besten per GitHub committen UND synchronisieren (pushen)
