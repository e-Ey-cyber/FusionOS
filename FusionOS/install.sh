#!/bin/bash

# Install required packages
echo "Installing required packages..."
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    pkg-config \
    libgtk-3-dev

# Check for GTK dependencies
if ! dpkg -l | grep -q libgtk-3-dev; then
    echo "Installing GTK development libraries..."
    sudo apt-get install -y libgtk-3-dev
fi

echo "FusionOS Installation Script"
echo "==========================="

# Check if running as root
if [ "$EUID" -ne 0 ]; then 
    echo "Please run as root"
    exit 1
fi

# Select target device
echo "Available devices:"
lsblk
echo -n "Enter target device (e.g. /dev/sdb): "
read TARGET_DEVICE

# Confirm installation
echo "WARNING: This will erase all data on $TARGET_DEVICE"
echo -n "Are you sure you want to continue? (y/N): "
read CONFIRM

if [ "$CONFIRM" != "y" ]; then
    echo "Installation cancelled"
    exit 1
fi

# Launch GUI installer instead of CLI
echo "Launching FusionOS Installer..."
./build/fusion_os --gui

echo "Installation complete!"
