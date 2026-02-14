# FPGA Hybrid Development Workflow (Mac + Remote Build)

This repository contains a streamlined workflow for developing FPGA projects (specifically for the **DE0-Nano-SoC** and DE10-Nano) on macOS using VS Code, while offloading the heavy compilation to a remote server (Azure VM/School Lab).

It features **automated project creation**, **local high-speed simulation**, **Nios V software integration**, and a **"Smart Makefile"** that handles file management and USB-over-SSH debugging.

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
You need these tools to write code, simulate locally, and program the board.

* **VS Code** (with SystemVerilog extension)
* **Verilator** (Simulation Engine): `brew install verilator`
* **Surfer** (Waveform Viewer): `brew install surfer`
* **OpenFPGALoader**: `brew install openfpgaloader`
* **VirtualHere Server**: (Required for JTAG UART terminal access). Download the free server for macOS.

### 2. Remote Build Server (Azure VM / Linux)
This is the heavy lifter. You need an x86 Linux machine (Quartus does not run on ARM).

**Azure VM Setup Guide:**
1.  **Create VM:** Use an **Ubuntu 22.04 LTS** image. A standard B2s (2 vCPUs, 4GB RAM) is sufficient and cheap (~$0.04/hr).
2.  **Install Quartus:** Download Quartus Prime Lite (Linux) and the Nios V tools. Upload to the VM via SCP and install to `~/intelFPGA_lite/`.
3.  **Install USB Drivers (CRITICAL):** Azure kernels strip USB drivers by default. You must reinstall them to use VirtualHere:
    ```bash
    sudo apt-get update
    sudo apt-get install -y linux-modules-extra-$(uname -r)
    sudo modprobe vhci-hcd
    ```
4.  **Install VirtualHere Client:**
    ```bash
    wget [https://www.virtualhere.com/sites/default/files/usbclient/vhclientx86_64](https://www.virtualhere.com/sites/default/files/usbclient/vhclientx86_64)
    chmod +x vhclientx86_64
    ```

## 🚀 Getting Started

### 1. Setup the Tools
Ensure you have the `tools/` folder in your root directory containing the shared `Makefile` and `project.qsf.template`.

### 2. Create a New Project
Don't copy-paste old folders! Use the generator script.

```bash
./new_project.sh lab2_timer
```
This creates the folder structure, generates a customized `.qsf` with default pin mappings, and links the Makefile.

---

## ⚡ The Workflow Loop

### Step 1: Write Code
* **Hardware:** Put SystemVerilog source modules in `lab2_timer/src/`.
* **Simulation:** Put testbenches in `lab2_timer/sim/`.
* **Software:** Put C code in `lab2_timer/software/app/`.

*Note: The system automatically detects all `.sv` and `.c` files. You do not need to list them manually.*

### Step 2: Simulate Hardware Locally (Fast)
Before building, verify your logic on your Mac. This uses Verilator and opens Surfer automatically.

```bash
make sim
```

### Step 3: Build & Program (Remote)
Once simulation works, choose the appropriate build command:

#### A. The "Hardware Loop" (Slow)
Use this when you change **SystemVerilog (`.sv`)** files or **Pin Assignments (`.qsf`)**.
It syncs code, runs full Quartus compilation (~10 mins), downloads the bitstream, and flashes the board.

```bash
make build       # Compiles hardware
make download    # Downloads .rbf to Mac
make program     # Flashes board via USB
```
*Or run `make all` to do everything in one go.*

#### B. The "Software Loop" (Fast)
Use this when you only change **C Code (`.c`)** for the Nios V processor.
It compiles the C code, injects it into the *existing* FPGA bitstream, and flashes the board (~15 seconds).

```bash
make bake
make program
```

#### C. The "System Loop"
Use this if you modify the **Platform Designer (`.qsys`)** system (adding timers, UARTs, etc).

```bash
make qsys        # Generates hardware from Qsys
make build       # Compiles hardware
```

---

## 🔌 JTAG UART Terminal (VirtualHere)

To see `printf` output from the Nios V processor, you must bridge your Mac's USB connection to the Linux VM.

1.  **Start VirtualHere Server** on your Mac.
2.  **SSH with Tunneling:**
    You must forward port 7575 for the tools to talk.
    ```bash
    ssh -R 7575:localhost:7575 azure-vm
    ```
3.  **Connect Device on Linux:**
    Inside the SSH session:
    ```bash
    sudo ./vhclientx86_64 -n &                        # Start client background
    sudo ./vhclientx86_64 -t "MANUAL HUB ADD,127.0.0.1:7575" # Link to Mac
    sudo ./vhclientx86_64 -t "LIST"                   # Find device address
    sudo ./vhclientx86_64 -t "USE,<ADDRESS>"          # Grab device
    ```
    *(If it says "API Timeout", check your Mac screen for an "Allow Accessory" popup).*
4.  **Run Terminal:**
    ```bash
    juart-terminal
    ```

---

## ⚙️ Makefile Targets Reference

| Target | Description | Usage Scenario |
| :--- | :--- | :--- |
| `make all` | Checks IP, Syncs, Builds, Downloads, Programs. | First run / Full rebuild. |
| `make qsys` | Generates HDL from `.qsys` file. | Modifying Qsys components. |
| `make build` | Compiles `.sv` files to `.rbf` (Remote). | Changing Hardware logic. |
| `make bake` | Compiles C code and updates bitstream (Remote). | Changing Nios Software. |
| `make program` | Programs FPGA with most recent built version. | Reprogramming prebuilt solutions. |
| `make sim` | Runs Verilator simulation (Local). | Verifying logic before build. |
| `make surfer` | Opens waveform viewer. | Debugging simulation. |
| `make start` | Boots up the Azure VM. | Start of day. |
| `make stop` | Deallocates Azure VM (Saves $$$). | End of day. |
| `make clean` | Removes build artifacts. | Troubleshooting. |
