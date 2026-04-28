# SPDX-FileCopyrightText: 2026 Alex Huber <alex.huber743@gmail.com>
# SPDX-License-Identifier: BSD-2-Clause

#!/bin/bash

BUILD_TYPE="${1:-Release}"

echo "Building Maki in $BUILD_TYPE mode..."

cmake -B build/ -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
cmake --build build/
sudo cmake --install build/

echo "Maki was installed successfully!"