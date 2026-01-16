#!/bin/bash

# ==========================================
#   FPGA Project Generator
#   Creates a new FPGA project based on the de10_blink template
# ==========================================

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check if project name is provided
if [ $# -eq 0 ]; then
    echo -e "${RED}Error: Project name is required${NC}"
    echo "Usage: $0 <project_name>"
    echo "Example: $0 lab1_counter"
    exit 1
fi

PROJECT_NAME="$1"

# Validate project name (alphanumeric and underscore only, no spaces)
if [[ ! "$PROJECT_NAME" =~ ^[a-zA-Z0-9_]+$ ]]; then
    echo -e "${RED}Error: Project name must contain only alphanumeric characters and underscores${NC}"
    exit 1
fi

# Check if project directory already exists
if [ -d "$PROJECT_NAME" ]; then
    echo -e "${RED}Error: Directory '$PROJECT_NAME' already exists${NC}"
    exit 1
fi

# Get the script directory (workspace root)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TOOLS_DIR="$SCRIPT_DIR/tools"

# Check if required files exist
if [ ! -f "$TOOLS_DIR/Makefile" ]; then
    echo -e "${RED}Error: Shared Makefile not found: $TOOLS_DIR/Makefile${NC}"
    exit 1
fi

if [ ! -f "$TOOLS_DIR/project.qsf.template" ]; then
    echo -e "${RED}Error: Template file not found: $TOOLS_DIR/project.qsf.template${NC}"
    exit 1
fi

# Create project directory structure
echo -e "${GREEN}Creating project structure for '$PROJECT_NAME'...${NC}"
mkdir -p "$PROJECT_NAME/src"
mkdir -p "$PROJECT_NAME/sim"
mkdir -p "$PROJECT_NAME/build"

# Generate minimal Makefile that includes shared Makefile
echo "Generating Makefile..."
cat > "$PROJECT_NAME/Makefile" << EOF
# Project-specific configuration
PROJECT_NAME = $PROJECT_NAME

# Include shared Makefile with all the workflow logic
include ../tools/Makefile
EOF

# Generate .qsf file from template
echo "Generating Quartus settings file..."
sed "s/PROJECT_NAME_PLACEHOLDER/$PROJECT_NAME/g" "$TOOLS_DIR/project.qsf.template" > "$PROJECT_NAME/$PROJECT_NAME.qsf"

echo -e "${GREEN}✅ Project '$PROJECT_NAME' created successfully!${NC}"
echo ""
echo "Project structure:"
echo "  $PROJECT_NAME/"
echo "    ├── src/          (SystemVerilog source files)"
echo "    ├── sim/          (Simulation testbenches)"
echo "    ├── build/        (Build artifacts)"
echo "    ├── Makefile      (Build automation)"
echo "    └── $PROJECT_NAME.qsf  (Quartus settings)"
echo ""
echo "Next steps:"
echo "  1. Add your SystemVerilog source file: $PROJECT_NAME/src/$PROJECT_NAME.sv"
echo "  2. Update pin assignments in $PROJECT_NAME/$PROJECT_NAME.qsf if needed"
echo "  3. Run 'make start' to start the Azure VM"
echo "  4. Run 'make all' to build and program the board"

