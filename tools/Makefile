# ==========================================
#   FPGA CLOUD WORKFLOW - SHARED LOGIC
#   This file is included by project Makefiles
#   PROJECT_NAME must be set before including this file
# ==========================================

# --- Azure Settings ---
RESOURCE_GROUP = fpga-quartus-rg
VM_NAME        = quartus-linux
VM_USER        = braden

# --- Project Settings (PROJECT_NAME should be set by including Makefile) ---
LOCAL_SRC      = ./src
VM_DIR         = ~/fpga_projects/$(PROJECT_NAME)

# --- Remote Paths ---
# Updated to 24.1 as requested
QUARTUS_BIN    = ~/intelFPGA_lite/24.1/quartus/bin

# --- Local Simulation Settings ---
OBJ_DIR        = obj_dir
SIM_DIR        = ./sim
SRCS           = $(wildcard $(LOCAL_SRC)/*.sv)
TBS            = $(wildcard $(SIM_DIR)/*_tb.sv)
TB_MODULE      = $(shell grep -h "^module" $(TBS) 2>/dev/null | sed 's/module[[:space:]]*\([a-zA-Z0-9_]*\).*/\1/' | head -1)

# ==========================================
#   AUTOMATION LOGIC
# ==========================================

# 1. Get the Dynamic IP
VM_IP := $(shell az vm show -d -g $(RESOURCE_GROUP) -n $(VM_NAME) --query publicIps -o tsv 2>/dev/null)

.PHONY: all start stop status sync build download program ssh clean check-ip sim clean_sim

# Default Action
all: check-ip sync build download program

# --- Verification ---
check-ip:
	@if [ -z "$(VM_IP)" ]; then \
		echo "❌ Error: VM IP not found. Is the VM running?"; \
		echo "👉 Run 'make start' first."; \
		exit 1; \
	fi

# --- Azure Management ---
start:
	@echo "🚀 Starting Azure VM..."
	az vm start -g $(RESOURCE_GROUP) -n $(VM_NAME)
	@echo "✅ VM Started. You can now run 'make all'."

stop:
	@echo "🛑 Deallocating VM..."
	az vm deallocate -g $(RESOURCE_GROUP) -n $(VM_NAME)
	@echo "zzz VM is sleeping."

status:
	@echo "VM Status: $(shell az vm get-instance-view -g $(RESOURCE_GROUP) -n $(VM_NAME) --query instanceView.statuses[1].displayStatus -o tsv)"
	@echo "Current IP: $(VM_IP)"

# --- Development Flow ---
sync: update-qsf
	@echo "🔄 Syncing code to Cloud ($(VM_IP))..."
	ssh -o StrictHostKeyChecking=no $(VM_USER)@$(VM_IP) "mkdir -p $(VM_DIR)/output_files"
	rsync -avz --exclude '.git' --exclude 'build' --exclude '$(OBJ_DIR)' ./ $(VM_USER)@$(VM_IP):$(VM_DIR)

build:
	@echo "🔨 Triggering Cloud Build (Quartus 24.1)..."
	@mkdir -p build
	# 1. Compile (capture output with tee)
	@echo "📝 Compilation log will be saved to build/compilation_report.txt"
	ssh -o StrictHostKeyChecking=no $(VM_USER)@$(VM_IP) "cd $(VM_DIR) && $(QUARTUS_BIN)/quartus_sh --flow compile $(PROJECT_NAME)" 2>&1 | tee build/compilation_report.txt
	# 2. Convert to Uncompressed RBF (Safer for JTAG)
	@echo "🔄 Converting to RBF format..."
	ssh -o StrictHostKeyChecking=no $(VM_USER)@$(VM_IP) "cd $(VM_DIR) && $(QUARTUS_BIN)/quartus_cpf -c -o bitstream_compression=off output_files/$(PROJECT_NAME).sof output_files/$(PROJECT_NAME).rbf" 2>&1 | tee -a build/compilation_report.txt
	@echo "✅ Build complete. Report saved to build/compilation_report.txt"

download:
	@echo "⬇️ Downloading Bitstream..."
	mkdir -p build
	scp -o StrictHostKeyChecking=no $(VM_USER)@$(VM_IP):$(VM_DIR)/output_files/$(PROJECT_NAME).rbf ./build/

program:
	@echo "⚡ Flashing DE10-Nano..."
	# Removed -r to stop the board from reloading the Factory Image
	openFPGALoader -b de10nano --freq 2500000 --probe-firmware ../tools/blaster_6810.hex -v ./build/$(PROJECT_NAME).rbf
	
ssh:
	ssh $(VM_USER)@$(VM_IP)

# --- Auto-Update Project File ---
update-qsf:
	@echo "⚙️  Refreshing .qsf file list..."
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
	@echo "✅ QSF updated: synced with src/ directory."

# --- Local Simulation (Verilator + Surfer) ---
sim:
	@echo "🔬 Running local simulation with Verilator..."
	@if [ -z "$(TBS)" ]; then \
		echo "❌ Error: No testbench found in $(SIM_DIR)/"; \
		echo "   Expected file: $(SIM_DIR)/*_tb.sv"; \
		exit 1; \
	fi
	@if [ -z "$(SRCS)" ]; then \
		echo "❌ Error: No source files found in $(LOCAL_SRC)/"; \
		exit 1; \
	fi
	@echo "   Source files: $(SRCS)"
	@echo "   Testbench: $(TBS)"
	@echo "   Top module: $(TB_MODULE)"
	# 1. Compile with Verilator
	verilator --binary --timing --trace -j 0 --top-module $(TB_MODULE) $(SRCS) $(TBS)
	# 2. Run the simulation
	./$(OBJ_DIR)/V$(TB_MODULE)

surfer:
	@echo "📊 Opening Surfer..."
	@if [ -f dump.vcd ]; then \
		if command -v surfer >/dev/null 2>&1; then \
			surfer dump.vcd; \
		else \
			echo "❌ Error: 'surfer' command not found. Please install Surfer to view waveforms."; \
		fi \
	else \
		echo "❌ Error: dump.vcd not found. Please run 'make sim' first to generate the waveform file."; \
	fi

clean_sim:
	@echo "🧹 Cleaning simulation artifacts..."
	rm -rf $(OBJ_DIR) dump.vcd

clean: clean_sim
	rm -rf build sim/*.vcd sim/*_sim

