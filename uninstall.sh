# SPDX-FileCopyrightText: 2026 Alex Huber <alex.huber743@gmail.com>
# SPDX-License-Identifier: BSD-2-Clause

#!/bin/bash

#Check if the build directory exists
if [ -d "build" ]; then
    echo "Uninstalling Maki..."
    sudo cmake --build build/ --target uninstall
    echo "Maki was uninstalled successfully!"
else
    echo "Error: Build directory not found. If you installed Maki, run this script from the project root (right next to the build folder)!"
    exit 1
fi