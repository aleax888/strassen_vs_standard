#!/usr/bin/env bash
set -e

PROJECT_ROOT="$(pwd)"
VENV_PATH="src/plotting/venv"

echo "Creating virtual environment in $VENV_PATH..."
PY_BIN="$(command -v python3 || command -v python || true)"
if [ -z "$PY_BIN" ]; then
  echo "Python not found. Install Python 3 and try again." >&2
  exit 1
fi

"$PY_BIN" -m venv "$VENV_PATH"

# Prefer activating if possible, but fall back to using pip/python directly from the venv (supports Windows and Unix layouts)
if [ -f "$VENV_PATH/bin/activate" ]; then
  echo "Activating virtual environment..."
  # shellcheck source=/dev/null
  source "$VENV_PATH/bin/activate"
  VENV_PIP="$VENV_PATH/bin/pip"
  VENV_PY="$VENV_PATH/bin/python"
elif [ -f "$VENV_PATH/Scripts/activate" ]; then
  echo "Detected Windows-style venv. Using pip/python from the venv directly (no shell activation)."
  VENV_PIP="$VENV_PATH/Scripts/pip.exe"
  VENV_PY="$VENV_PATH/Scripts/python.exe"
elif [ -x "$VENV_PATH/bin/pip" ]; then
  VENV_PIP="$VENV_PATH/bin/pip"
  VENV_PY="$VENV_PATH/bin/python"
elif [ -x "$VENV_PATH/Scripts/pip.exe" ]; then
  VENV_PIP="$VENV_PATH/Scripts/pip.exe"
  VENV_PY="$VENV_PATH/Scripts/python.exe"
else
  echo "Could not locate pip/python inside the virtual environment. Please activate it manually and install dependencies." >&2
  exit 1
fi

echo "Upgrading pip..."
"$VENV_PY" -m pip install --upgrade pip

echo "Installing dependencies..."
"$VENV_PY" -m pip install pandas matplotlib

echo "Creating output directory if it does not exist..."
mkdir -p outputs/plots

echo "Running plotting script..."
"$VENV_PY" src/plotting/plot_benchmark.py

echo "Plots saved in outputs/plots ✅"
