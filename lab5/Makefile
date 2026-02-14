# ==========================================
#   FPGA CLOUD WORKFLOW - EXTENDED (Nios V)
#   Project: $(PROJECT_NAME)
# ==========================================

# --- 1. Settings & Configuration ---

# Azure Configuration
PROJECT_NAME   = lab5
RESOURCE_GROUP = fpga-quartus-rg
VM_NAME        = quartus-linux
VM_DIR         = ~/fpga_projects/$(PROJECT_NAME)

# Local Paths
LOCAL_SRC      = ./src
OBJ_DIR        = obj_dir
SIM_DIR        = ./sim

# Remote Toolchain Paths (Quartus 24.1)
QUARTUS_BIN    = ~/intelFPGA_lite/24.1/quartus/bin
NIOSV_BIN      = ~/intelFPGA_lite/24.1/niosv/bin
RISCFREE_BIN   = ~/intelFPGA_lite/24.1/riscfree/toolchain/riscv32-unknown-elf/bin/

# License Setup
LICENSE_FILE   = ~/.altera/LR-281343_License.dat
LICENSE_EXPORT = export LM_LICENSE_FILE=$(LICENSE_FILE) && \
                 export QUARTUS_ROOTDIR=~/intelFPGA_lite/24.1/quartus && \
                 export SOPC_KIT_NIOS2=~/intelFPGA_lite/24.1/niosv

# Nios V Settings
HAS_SOFTWARE   = $(shell [ -d ./software/app ] && echo 1 || echo 0)
HAS_QSYS       = $(shell [ -f ./$(PROJECT_NAME).qsys ] && echo 1 || echo 0)
SOPCINFO_FILE  = $(PROJECT_NAME).sopcinfo
BSP_DIR        = ./software/bsp
APP_DIR        = ./software/app
MEM_INIT_FILE  = hello.hex

# Simulation Settings
SRCS           = $(wildcard $(LOCAL_SRC)/*.sv)
TBS            = $(wildcard $(SIM_DIR)/*_tb.sv)
TB_MODULE      = $(shell grep -h "^module" $(TBS) 2>/dev/null | sed 's/module[[:space:]]*\([a-zA-Z0-9_]*\).*/\1/' | head -1)

# --- 2. Color Codes ---
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
CYAN    = \033[0;36m
NC      = \033[0m

# ==========================================
#   MAIN TARGETS
# ==========================================
.PHONY: all start stop status ssh sync build download program qsys bsp app bake sim surfer clean

# Default: Full Hardware Pipeline
all: check-ip sync build download program

# --- Azure Management ---
start:
	@echo "$(BLUE)🚀 Starting Azure VM...$(NC)"
	az vm start -g $(RESOURCE_GROUP) -n $(VM_NAME)
	@echo "$(GREEN)✅ VM Started. Run 'make all' to build.$(NC)"

stop:
	@echo "$(BLUE)🛑 Deallocating VM...$(NC)"
	az vm deallocate -g $(RESOURCE_GROUP) -n $(VM_NAME)
	@echo "$(CYAN)zzz VM is sleeping.$(NC)"

status:
	@echo "VM Status: $(shell az vm get-instance-view -g $(RESOURCE_GROUP) -n $(VM_NAME) --query instanceView.statuses[1].displayStatus -o tsv)"
	@echo "Current IP: $(VM_IP)"

ssh:
	ssh azure-vm

# ==========================================
#   HARDWARE WORKFLOW (Quartus)
# ==========================================

# Sync Local Source -> Cloud
sync: update-qsf
	@echo "$(BLUE)🔄 Syncing code to Cloud...$(NC)"
	ssh azure-vm "mkdir -p $(VM_DIR)/output_files"
	rsync -avz --exclude '.git' --exclude 'build' --exclude '$(OBJ_DIR)' ./ azure-vm:$(VM_DIR)

# Auto-update .qsf file with new SystemVerilog files
update-qsf:
	@echo "$(BLUE)⚙️  Refreshing .qsf file list...$(NC)"
	@cp $(PROJECT_NAME).qsf $(PROJECT_NAME).qsf.bak
	@grep -v "src/.*\.sv" $(PROJECT_NAME).qsf > $(PROJECT_NAME).qsf.tmp
	@for f in src/*.sv; do \
		echo "set_global_assignment -name SYSTEMVERILOG_FILE $$f" >> $(PROJECT_NAME).qsf.tmp; \
	done
	@mv $(PROJECT_NAME).qsf.tmp $(PROJECT_NAME).qsf
	@echo "$(GREEN)✅ QSF updated.$(NC)"

# Trigger Qsys Generation
qsys: sync
	@echo "$(BLUE)⚙️  Generating QSYS IP files...$(NC)"
	ssh azure-vm "$(LICENSE_EXPORT) && cd $(VM_DIR) && \
		~/intelFPGA_lite/24.1/quartus/sopc_builder/bin/qsys-generate $(PROJECT_NAME).qsys --synthesis=VERILOG"
	scp azure-vm:$(VM_DIR)/$(PROJECT_NAME)/synthesis/$(PROJECT_NAME).qip build/
	@echo "$(GREEN)✅ QSYS generation complete.$(NC)"

# Full Hardware Build (Compile .sof -> Convert to .rbf)
build: check-qsys-build qsys-if-needed
	@echo "$(BLUE)🔨 Triggering Cloud Build (Quartus 24.1)...$(NC)"
	@mkdir -p build
	@echo "$(CYAN)📝 Log: build/compilation_report.txt$(NC)"
	# 1. Compile
	ssh azure-vm "$(LICENSE_EXPORT) && cd $(VM_DIR) && \
		$(QUARTUS_BIN)/quartus_sh --flow compile $(PROJECT_NAME)" 2>&1 | tee build/compilation_report.txt
	# 2. Convert to RBF
	@echo "$(BLUE)🔄 Converting to RBF format...$(NC)"
	ssh azure-vm "$(LICENSE_EXPORT) && cd $(VM_DIR) && \
		$(QUARTUS_BIN)/quartus_cpf -c -o bitstream_compression=off output_files/$(PROJECT_NAME).sof output_files/$(PROJECT_NAME).rbf" 2>&1 | tee -a build/compilation_report.txt
	@echo "$(GREEN)✅ Build complete.$(NC)"

# Download Artifacts
download:
	@echo "$(BLUE)⬇️  Downloading Bitstream...$(NC)"
	mkdir -p build
	scp azure-vm:$(VM_DIR)/output_files/$(PROJECT_NAME).rbf ./build/
	@echo "$(GREEN)✅ Bitstream downloaded$(NC)"

# Program FPGA
program:
	@echo "$(BLUE)⚡ Flashing DE10-Nano...$(NC)"
	openFPGALoader -b de10nano --freq 2500000 --probe-firmware ../tools/blaster_6810.hex -v ./build/$(PROJECT_NAME).rbf
	@echo "$(GREEN)✅ Programming complete!$(NC)"

# ==========================================
#   SOFTWARE WORKFLOW (Nios V)
# ==========================================

# Generate Board Support Package
bsp: check-software sync
	@echo "$(BLUE)🛠️  Generating Nios V BSP...$(NC)"
	ssh azure-vm "$(LICENSE_EXPORT) && cd $(VM_DIR) && \
		$(NIOSV_BIN)/niosv-bsp -c -t=hal --sopcinfo=$(SOPCINFO_FILE) software/bsp/settings.bsp" 2>&1 | tee build/bsp_report.txt
	@echo "$(GREEN)✅ BSP generation complete.$(NC)"

# Compile C Application (CMake)
app: bsp
	@echo "$(BLUE)🔍 Verifying RiscFree toolchain...$(NC)"
	ssh azure-vm "ls $(RISCFREE_BIN)/riscv32-unknown-elf-gcc >/dev/null 2>&1 || (echo '$(RED)❌ Compiler not found$(NC)' && exit 1)"
	
	@echo "$(BLUE)🔨 Configuring application...$(NC)"
	ssh azure-vm "$(LICENSE_EXPORT) && cd $(VM_DIR) && \
		$(NIOSV_BIN)/niosv-app --app-dir=software/app --bsp-dir=software/bsp --s=software/app" 2>&1 | tee build/app_report.txt
	
	@echo "$(BLUE)🔨 Compiling Software...$(NC)"
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
	@echo "$(GREEN)✅ ELF generated at software/app/build/$(PROJECT_NAME).elf$(NC)"

# FAST UPDATE: Inject Software -> Update RBF -> Download
bake: app
	@echo "$(BLUE)👨‍🍳 Baking software into bitstream...$(NC)"
	# 1. Copy HEX
	ssh azure-vm "$(LICENSE_EXPORT) && cd $(VM_DIR) && \
		cp software/app/build/mem.hex $(MEM_INIT_FILE)"
	# 2. Update SOF
	ssh azure-vm "$(LICENSE_EXPORT) && cd $(VM_DIR) && \
		$(QUARTUS_BIN)/quartus_cdb --update_mif $(PROJECT_NAME) && \
		$(QUARTUS_BIN)/quartus_asm $(PROJECT_NAME)"
	# 3. Convert to RBF
	@echo "$(BLUE)🔄 Converting to RBF...$(NC)"
	ssh azure-vm "$(LICENSE_EXPORT) && cd $(VM_DIR) && \
		$(QUARTUS_BIN)/quartus_cpf -c -o bitstream_compression=off \
		output_files/$(PROJECT_NAME).sof output_files/$(PROJECT_NAME).rbf"
	# 4. Download & Program
	$(MAKE) download
	@echo "$(GREEN)✅ Baked bitstream ready. Run 'make program' to boot.$(NC)"

# Helper: Download just the ELF
app-download: app
	@echo "$(BLUE)⬇️  Downloading application ELF...$(NC)"
	mkdir -p build
	scp azure-vm:$(VM_DIR)/software/app/build/$(PROJECT_NAME).elf ./build/$(PROJECT_NAME).elf

# Helper: Full Software Rebuild + Download
software: app-download download
	@echo "$(GREEN)✅ Software build pipeline complete.$(NC)"

# ==========================================
#   LOCAL SIMULATION
# ==========================================
sim:
	@echo "$(BLUE)🔬 Running local simulation (Verilator)...$(NC)"
	@if [ -z "$(TBS)" ]; then echo "$(RED)❌ No Testbench found$(NC)"; exit 1; fi
	@if [ -z "$(SRCS)" ]; then echo "$(RED)❌ No Source files found$(NC)"; exit 1; fi
	verilator --binary --timing --trace -j 0 --top-module $(TB_MODULE) $(SRCS) $(TBS)
	./$(OBJ_DIR)/V$(TB_MODULE)

surfer:
	@echo "$(BLUE)📊 Opening Surfer...$(NC)"
	@if [ -f dump.vcd ]; then surfer dump.vcd; else echo "$(RED)❌ No dump.vcd found$(NC)"; fi

# ==========================================
#   UTILITIES / CLEANUP
# ==========================================
clean: clean_sim
	rm -rf build sim/*.vcd sim/*_sim
	@echo "$(GREEN)✅ Full cleanup complete$(NC)"

clean_sim:
	@echo "$(BLUE)🧹 Cleaning simulation artifacts...$(NC)"
	rm -rf $(OBJ_DIR) dump.vcd

# --- Internal Checks ---
check-ip:
	@if [ -z "$(VM_IP)" ]; then \
		echo "$(RED)❌ Error: VM IP not found. Is the VM running?$(NC)"; \
		echo "$(CYAN)👉 Run 'make start' first.$(NC)"; \
		exit 1; \
	fi

check-software:
	@if [ "$(HAS_SOFTWARE)" != "1" ]; then echo "$(RED)❌ Error: No software found in ./software/app/$(NC)"; exit 1; fi
	@if [ "$(HAS_QSYS)" != "1" ]; then echo "$(RED)❌ Error: No QSYS file found$(NC)"; exit 1; fi

check-qsys-build:
	@if [ "$(HAS_QSYS)" = "1" ]; then echo "$(YELLOW)📦 Nios V System detected.$(NC)"; fi

qsys-if-needed:
	@if [ "$(HAS_QSYS)" = "1" ] && [ ! -f build/$(PROJECT_NAME).qip ]; then $(MAKE) qsys; fi