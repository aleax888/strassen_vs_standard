#!/bin/bash
set -e

PROJECT_ROOT="$(pwd)"
VENV_PATH="src/plotting/venv"

echo "Creating virtual environment in src/plotting/venv..."
python3 -m venv "$VENV_PATH"

echo "Activating virtual environment..."
source "$VENV_PATH/bin/activate"

echo "Upgrading pip..."
pip install --upgrade pip

echo "Installing dependencies..."
pip install pandas matplotlib

echo "Creating output directory if it does not exist..."
mkdir -p outputs/plots

echo "Running plotting script..."
python src/plotting/plot_benchmark.py

echo "Plots saved in outputs/plots ✅"
