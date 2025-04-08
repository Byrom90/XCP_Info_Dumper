# XCP Info Dumper (xcpid)

A Dashlaunch plugin designed to debug print the information of digital content being downloaded on Xbox 360 consoles.

> [!IMPORTANT]  
> The aim of this project is to aid in the preservation of digital content.  
> **I DO NOT CONDONE PIRACY!**  

> [!NOTE]
> This is NOT an ongoing project.  
> I do not plan to update or maintain it in any way.

Consoles will need to be setup to view debug prints.

Methods:
- UART directly hooked up to the console.
- Over the network using xbWatson (xbdm.xex required)
- Over the network using kdnet (Devkit kernels only).

Features:
 - Debug prints information of digital content (.xcp) as it's downloaded. Key parts being the URL and encryption key.
 - Disc tray bypass support - Plugin will detect the tray state during init and unload if it's open.
 - Unload support - Plugin can be unloaded using tools etc.

Credits:
 - FreestyleDash Team - xkelib
 - iMoD1998 - Detour files. https://gist.github.com/iMoD1998/4aa48d5c990535767a3fc3251efc0348
 - GoobyCorp aka Visual Studio - Incredibly useful python scripts including one to utilise the encryption key dumped by this plugin. https://github.com/GoobyCorp/Xbox_360_Crypto