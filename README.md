# FPGA Hybrid Development Workflow (Mac + Remote Build)

This repository contains a streamlined workflow for developing FPGA projects (specifically for the DE0-Nano-SoC) on macOS using VS Code, while offloading the heavy compilation to a remote server (Azure VM/School Lab).

It features **automated project creation**, **local high-speed simulation**, and a **"Smart Makefile"** that handles file management for you.

## 📂 Directory Structure

Your workspace should look like this:

```text
local-7660/
├── new_fpga_project.sh      # Script to generate projects
└── tools/
    ├── Makefile.shared      # The build & sim logic
    ├── blaster_6810.hex     # Programming driver 
    └── project.qsf.template # Master Pin Assignments
```

## 🛠 Prerequisites
### 1. Local Machine (macOS)

You need these tools to write code and run simulations locally.

* VS Code (with SystemVerilog extension)
* Verilator (Simulation Engine): `brew install verilator`
* Surfer (Waveform Viewer): `brew install surfer`
* OpenFPGALoader: If you are programming the board locally via USB. `brew install openfpgaloader`

### 2. Remote Build Server (Azure VM / Linux)

This is the most invovled part of the setup.

* Setup a VM from Microsoft Azure. You can get a B2s type machine for around $0.04-$0.08 / hour. **You can also apply to recieve over $100 as a student to cover this cost**. The Linux machine I use has (I think) 4 cores, 4 GB RAM, and 128 GB Premium SSD (probably way overkill).
* Ask AI how to set this up exactly, I don't remember everything I did. The most important thing is that it's a x86 machine (**not ARM**) as Quartus will not run on ARM machines.
* Setup the VM with `ssh` so you can access from a command line on your computer. The Makefile uses the Azure CLI to access the VM. You likely have to use the command `av login` or something similar so your computer gains access to the VM.

The Makefile has commands `make start` and `make stop` to start and stop (deallocate) the VM, which takes a minute or two, but will save some money.

Once the VM is setup and you have ssh access, you can get Quartus by downloading the `.tar` file from the website (~8 GB) **to your computer**. Then you can transfer the file over to the VM by ssh, unzip, and install.

## 🚀 Getting Started
### 1. Setup the Tools

Ensure you have the tools/ folder in your root directory containing the shared `Makefile` and `project.qsf.template`.

### 2. Create a New Project

Don't copy-paste old folders! Use the generator script.

`./new_project.sh lab2_timer`

This creates the folder structure, generates a customized .qsf with your default pin mappings, and creates a ready-to-go Makefile.

## ⚡ The Workflow Loop
### Step 1: Write Code

Put your source modules in `lab2_timer/src/`.

Put your testbenches in `lab2_timer/sim/`.

Note: You do NOT need to add files to the .qsf or Makefile manually. The system automatically detects all .sv files in these folders.

### Step 2: Simulate Locally (Fast)

Before building, verify your logic on your Mac. This uses Verilator and opens Surfer automatically.

`make sim`

### Step 3: Build Hardware (Remote)

Once the simulation works, compile the actual FPGA bitstream. This command sends the source to the remote VM and runs Quartus.

`make all`

This uploads code to the VM, builds the project, downloads the bitstream from the VM, and programs the board.

### Other Commands

Use `build`, `download`, and `program` to only run parts of the entire build process to save time.

## ⚙️ Customization
### Pin Assignments

The default pin mappings (LEDs, Switches, GPIO headers) are defined in tools/project.qsf.template.

If you need to change pins for all future projects, edit the template.

If you need to change pins for just one project, edit the .qsf file inside that project folder.

### Adding New Files

Just create the file in src/. The Makefile uses wildcards (src/*.sv), so it will be included in the next build automatically.