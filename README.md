# Maki

Standing for "Maki is A KDE Inspector", Maki enables quick previewing of files akin to GNOME's Sushi or MacOS' Quick Look.
Once open, the user can open the default app directly from Maki.

## Note

Maki is currently in development. Please report any issues you find!

### Supported file types

Maki works by checking the file mime using KDE's frameworks. All files that KDE considers text, audio, video and image files are fully supported. PDF documents are also fully supported.
Files that are not supported will show their default icon.

### Future support

Support for archives and document formats such as .odt and .doc/.docx are planned. Open for suggestions!

## Installation

Maki can be installed by running the install script from the project root. 
It will move the executable to `/usr/bin/`, the .desktop file to `/usr/share/applications/` and the servicemenu to `/usr/share/kio/servicemenus/`.
By this point, you should be able to use Maki by right clicking in Dolphin and selecting `Quick Preview`. If not, you might need to restart or run `kbuildsycoca6` on Plasma 6 to reload service menus.

## Uninstallation

Maki can be uninstalled by simply running the uninstall script from the project root. This will remove all of the installed files. 
Should `Quick Preview` still be available in Dolphin, you might need to restart or run `kbuildsycoca6` again.

## How does it work? 

To use Maki, you need to right click on a file in Dolphin and select `Quick Preview`.
This will grab the URL, which Maki uses to get the file mime, meaning what type of file (audio, video, etc.) the file is.
It will then select the right window to open for the preview.

## How does it look?

### Audio files

<img width="502" height="310" alt="image" src="https://github.com/user-attachments/assets/cc3331a0-6916-4796-8478-cb7827cdde6b" />

### Video files

<img width="640" height="375" alt="image" src="https://github.com/user-attachments/assets/aa1958d5-aca7-4aff-9032-9d33055f858a" />

### Image files

<img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/1e5f8d15-2026-4e01-846f-259a7b0b74a7" />
