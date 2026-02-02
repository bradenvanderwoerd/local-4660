# ==========================================
#   FPGA CLOUD WORKFLOW - EXTENDED (Nios V Ready)
#   This file is included by project Makefiles
#   PROJECT_NAME must be set before including this file
# ==========================================

# --- Color Codes for Pretty Output ---
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
CYAN    = \033[0;36m
NC      = \033[0m  # No Color

# --- Azure Settings ---
RESOURCE_GROUP = fpga-quartus-rg
VM_NAME        = quartus-linux

# --- Project Settings (PROJECT_NAME should be set by including Makefile) ---
LOCAL_SRC      = ./src
VM_DIR         = ~/fpga_projects/$(PROJECT_NAME)

# --- Remote Paths ---
# Updated to 24.1 as requested
QUARTUS_BIN    = ~/intelFPGA_lite/24.1/quartus/bin
NIOSV_BIN      = ~/intelFPGA_lite/24.1/niosv/bin
RISCFREE_BIN   = ~/intelFPGA_lite/24.1/riscfree/toolchain/riscv32-unknown-elf/bin/

# --- License Configuration ---
LICENSE_FILE   = ~/.altera/LR-281343_License.dat
LICENSE_EXPORT = export LM_LICENSE_FILE=$(LICENSE_FILE) && export QUARTUS_ROOTDIR=~/intelFPGA_lite/24.1/quartus && export SOPC_KIT_NIOS2=~/intelFPGA_lite/24.1/niosv

# --- Local Simulation Settings ---
OBJ_DIR        = obj_dir
SIM_DIR        = ./sim
SRCS           = $(wildcard $(LOCAL_SRC)/*.sv)
TBS            = $(wildcard $(SIM_DIR)/*_tb.sv)
TB_MODULE      = $(shell grep -h "^module" $(TBS) 2>/dev/null | sed 's/module[[:space:]]*\([a-zA-Z0-9_]*\).*/\1/' | head -1)

# --- Software Build Settings (Nios V) ---
HAS_SOFTWARE   = $(shell [ -d ./software/app ] && echo 1 || echo 0)
HAS_QSYS       = $(shell [ -f ./$(PROJECT_NAME).qsys ] && echo 1 || echo 0)
SOPCINFO_FILE  = output_files/$(PROJECT_NAME).sopcinfo
BSP_DIR        = ./software/bsp
APP_DIR        = ./software/app
APP_SOURCES    = $(wildcard $(APP_DIR)/*.c)

# -- Memory Initialization File for Baking ---
MEM_INIT_FILE = hello.hex

# ==========================================
#   AUTOMATION LOGIC
# ==========================================

.PHONY: all start stop status sync build download program ssh clean check-ip sim clean_sim bsp app software qsys

# Default Action
all: check-ip sync build download program

# --- Verification ---
check-ip:
	@if [ -z "$(VM_IP)" ]; then \
		echo "$(RED)❌ Error: VM IP not found. Is the VM running?$(NC)"; \
		echo "$(CYAN)👉 Run 'make start' first.$(NC)"; \
		exit 1; \
	fi

# --- Azure Management ---
start:
	@echo "$(BLUE)🚀 Starting Azure VM...$(NC)"
	az vm start -g $(RESOURCE_GROUP) -n $(VM_NAME)
	@echo "$(GREEN)✅ VM Started. You can now run 'make all'.$(NC)"

stop:
	@echo "$(BLUE)🛑 Deallocating VM...$(NC)"
	az vm deallocate -g $(RESOURCE_GROUP) -n $(VM_NAME)
	@echo "$(CYAN)zzz VM is sleeping.$(NC)"

status:
	@echo "VM Status: $(shell az vm get-instance-view -g $(RESOURCE_GROUP) -n $(VM_NAME) --query instanceView.statuses[1].displayStatus -o tsv)"
	@echo "Current IP: $(VM_IP)"

# --- Development Flow ---
sync: update-qsf
	@echo "$(BLUE)🔄 Syncing code to Cloud...$(NC)"
	ssh azure-vm "mkdir -p $(VM_DIR)/output_files"
	rsync -avz --exclude '.git' --exclude 'build' --exclude '$(OBJ_DIR)' ./ azure-vm:$(VM_DIR)

build: check-qsys-build qsys-if-needed
	@echo "$(BLUE)🔨 Triggering Cloud Build (Quartus 24.1)...$(NC)"
	@mkdir -p build
	# 1. Compile (capture output with tee)
	@echo "$(CYAN)📝 Compilation log will be saved to build/compilation_report.txt$(NC)"
	ssh azure-vm "$(LICENSE_EXPORT) && cd $(VM_DIR) && $(QUARTUS_BIN)/quartus_sh --flow compile $(PROJECT_NAME)" 2>&1 | tee build/compilation_report.txt
	# 2. Convert to Uncompressed RBF (Safer for JTAG)
	@echo "$(BLUE)🔄 Converting to RBF format...$(NC)"
	ssh azure-vm "$(LICENSE_EXPORT) && cd $(VM_DIR) && $(QUARTUS_BIN)/quartus_cpf -c -o bitstream_compression=off output_files/$(PROJECT_NAME).sof output_files/$(PROJECT_NAME).rbf" 2>&1 | tee -a build/compilation_report.txt
	@echo "$(GREEN)✅ Build complete. Report saved to build/compilation_report.txt$(NC)"

download:
	@echo "$(BLUE)⬇️  Downloading Bitstream...$(NC)"
	mkdir -p build
	scp azure-vm:$(VM_DIR)/output_files/$(PROJECT_NAME).rbf ./build/
	@echo "$(GREEN)✅ Bitstream downloaded$(NC)"

program:
	@echo "$(BLUE)⚡ Flashing DE10-Nano...$(NC)"
	openFPGALoader -b de10nano --freq 2500000 --probe-firmware ../tools/blaster_6810.hex -v ./build/$(PROJECT_NAME).rbf
	@echo "$(GREEN)✅ Programming complete!$(NC)"

ssh:
	ssh azure-vm

# --- Nios V Software Build Targets ---

check-software:
	@if [ "$(HAS_SOFTWARE)" != "1" ]; then \
		echo "$(RED)❌ Error: No software found in ./software/app/$(NC)"; \
		exit 1; \
	fi
	@if [ "$(HAS_QSYS)" != "1" ]; then \
		echo "$(RED)❌ Error: No QSYS file ($(PROJECT_NAME).qsys) found in project root$(NC)"; \
		exit 1; \
	fi

check-qsys-build:
	@if [ "$(HAS_QSYS)" = "1" ]; then \
		echo "$(YELLOW)📦 Nios V System detected. Will compile QSYS and embed software.$(NC)"; \
	fi

qsys-if-needed:
	@if [ "$(HAS_QSYS)" = "1" ] && [ ! -f output_files/$(PROJECT_NAME).qip ]; then \
		$(MAKE) qsys; \
	fi

# FIX: Added --qsys argument and proper output path
qsys: sync
	@echo "$(BLUE)⚙️  Generating QSYS IP files...$(NC)"
	ssh azure-vm "$(LICENSE_EXPORT) && cd $(VM_DIR) && ~/intelFPGA_lite/24.1/quartus/sopc_builder/bin/qsys-generate $(PROJECT_NAME).qsys --synthesis=VERILOG"
	@echo "$(GREEN)✅ QSYS generation complete.$(NC)"

# FIX: Added -t=hal (Hardware Abstraction Layer) and corrected sopcinfo pathing
bsp: check-software sync
	@echo "$(BLUE)🛠️  Generating Nios V BSP (Board Support Package)...$(NC)"
	ssh azure-vm "$(LICENSE_EXPORT) && cd $(VM_DIR) && \
		$(NIOSV_BIN)/niosv-bsp -c -t=hal --sopcinfo=$(SOPCINFO_FILE) software/bsp/settings.bsp" 2>&1 | tee build/bsp_report.txt
	@echo "$(GREEN)✅ BSP generation complete.$(NC)"

# FIX: Added $(NIOSV_BIN) to PATH so 'niosv-stack-report' can be found
app: bsp
	@echo "$(BLUE)🔍 Verifying RiscFree toolchain location...$(NC)"
	ssh azure-vm "ls $(RISCFREE_BIN)/riscv32-unknown-elf-gcc >/dev/null 2>&1 || (echo '$(RED)❌ Compiler not found at $(RISCFREE_BIN)$(NC)' && exit 1)"
	
	@echo "$(BLUE)🔨 Configuring application with niosv-app...$(NC)"
	ssh azure-vm "$(LICENSE_EXPORT) && cd $(VM_DIR) && \
		$(NIOSV_BIN)/niosv-app --app-dir=software/app --bsp-dir=software/bsp --srcs=software/app/$(PROJECT_NAME).c --elf-name=$(PROJECT_NAME).elf" 2>&1 | tee build/app_report.txt
	
	@echo "$(BLUE)🔨 Running CMake and Make (using RiscFree Toolchain)...$(NC)"
	ssh azure-vm "$(LICENSE_EXPORT) && \
		export PATH=$(RISCFREE_BIN):$(NIOSV_BIN):\$$PATH && \
		cd $(VM_DIR)/software/app && \
		rm -rf build && mkdir -p build && cd build && \
		cmake .. -G 'Unix Makefiles' \
			-DCMAKE_C_COMPILER=$(RISCFREE_BIN)/riscv32-unknown-elf-gcc \
			-DCMAKE_CXX_COMPILER=$(RISCFREE_BIN)/riscv32-unknown-elf-g++ \
			-DCMAKE_ASM_COMPILER=$(RISCFREE_BIN)/riscv32-unknown-elf-gcc \
			-DCMAKE_BUILD_TYPE=Release && \
		make" 2>&1 | tee -a build/app_report.txt
	@echo "$(GREEN)✅ Application ELF generated at software/app/build/$(PROJECT_NAME).elf$(NC)"

# FIX: ELF is generated inside the 'build' subdirectory created by CMake
app-download: app
	@echo "$(BLUE)⬇️  Downloading application ELF...$(NC)"
	mkdir -p build
	scp azure-vm:$(VM_DIR)/software/app/build/$(PROJECT_NAME).elf ./build/$(PROJECT_NAME).elf
	@echo "$(GREEN)✅ Application ELF downloaded to ./build/$(PROJECT_NAME).elf$(NC)"

bake: app
	@echo "$(BLUE)👨‍🍳 Baking software into bitstream...$(NC)"
	# 1. Copy the CMake-generated HEX to the file Quartus expects
	ssh azure-vm "$(LICENSE_EXPORT) && cd $(VM_DIR) && \
		cp software/app/build/onchip_memory2_0.hex $(MEM_INIT_FILE)"
	
	# 2. Update the SOF with the new HEX file
	ssh azure-vm "$(LICENSE_EXPORT) && cd $(VM_DIR) && \
		$(QUARTUS_BIN)/quartus_cdb --update_mif $(PROJECT_NAME) && \
		$(QUARTUS_BIN)/quartus_asm $(PROJECT_NAME)"
	
	# 3. Convert the NEW .sof to .rbf (THIS WAS MISSING!)
	@echo "$(BLUE)🔄 Converting to RBF...$(NC)"
	ssh azure-vm "$(LICENSE_EXPORT) && cd $(VM_DIR) && \
		$(QUARTUS_BIN)/quartus_cpf -c -o bitstream_compression=off \
		output_files/$(PROJECT_NAME).sof output_files/$(PROJECT_NAME).rbf"
	
	# 4. Download the Stuffed RBF
	$(MAKE) download
	@echo "$(GREEN)✅ Baked bitstream ready. Run 'make program' to boot immediately.$(NC)"

software: app-download download
	@echo "$(GREEN)✅ Software build pipeline complete (BSP + App + Bitstream Downloaded)$(NC)"
	@echo "$(CYAN)💡 Tip: Run 'make program' to flash the FPGA, or 'make all' for full rebuild.$(NC)"

# --- Auto-Update Project File ---
update-qsf:
	@echo "$(BLUE)⚙️  Refreshing .qsf file list...$(NC)"
	@# 1. Create a backup just in case
	@cp $(PROJECT_NAME).qsf $(PROJECT_NAME).qsf.bak
	
	@# 2. Filter out ALL existing references to files in src/
	@#    We use a temporary file because editing in-place is tricky across Mac/Linux
	@grep -v "src/.*\.sv" $(PROJECT_NAME).qsf > $(PROJECT_NAME).qsf.tmp
	
	@# 3. Add all current files from src/ to the temp file
	@for f in src/*.sv; do \
		echo "set_global_assignment -name SYSTEMVERILOG_FILE $$f" >> $(PROJECT_NAME).qsf.tmp; \
	done
	
	@# 4. Overwrite the original file
	@mv $(PROJECT_NAME).qsf.tmp $(PROJECT_NAME).qsf
	@echo "$(GREEN)✅ QSF updated: synced with src/ directory.$(NC)"

# --- Local Simulation (Verilator + Surfer) ---
sim:
	@echo "$(BLUE)🔬 Running local simulation with Verilator...$(NC)"
	@if [ -z "$(TBS)" ]; then \
		echo "$(RED)❌ Error: No testbench found in $(SIM_DIR)/$(NC)"; \
		echo "$(CYAN)   Expected file: $(SIM_DIR)/*_tb.sv$(NC)"; \
		exit 1; \
	fi
	@if [ -z "$(SRCS)" ]; then \
		echo "$(RED)❌ Error: No source files found in $(LOCAL_SRC)/$(NC)"; \
		exit 1; \
	fi
	@echo "$(CYAN)   Source files: $(SRCS)$(NC)"
	@echo "$(CYAN)   Testbench: $(TBS)$(NC)"
	@echo "$(CYAN)   Top module: $(TB_MODULE)$(NC)"
	# 1. Compile with Verilator
	verilator --binary --timing --trace -j 0 --top-module $(TB_MODULE) $(SRCS) $(TBS)
	# 2. Run the simulation
	./$(OBJ_DIR)/V$(TB_MODULE)

surfer:
	@echo "$(BLUE)📊 Opening Surfer...$(NC)"
	@if [ -f dump.vcd ]; then \
		if command -v surfer >/dev/null 2>&1; then \
			surfer dump.vcd; \
		else \
			echo "$(RED)❌ Error: 'surfer' command not found. Please install Surfer to view waveforms.$(NC)"; \
		fi \
	else \
		echo "$(RED)❌ Error: dump.vcd not found. Please run 'make sim' first to generate the waveform file.$(NC)"; \
	fi

clean_sim:
	@echo "$(BLUE)🧹 Cleaning simulation artifacts...$(NC)"
	rm -rf $(OBJ_DIR) dump.vcd
	@echo "$(GREEN)✅ Cleanup complete$(NC)"

clean: clean_sim
	rm -rf build sim/*.vcd sim/*_sim
	@echo "$(GREEN)✅ Full cleanup complete$(NC)"
