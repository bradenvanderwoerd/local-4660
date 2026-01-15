# ==========================================
#   FPGA CLOUD WORKFLOW - CONFIGURATION
# ==========================================

# --- Azure Settings ---
RESOURCE_GROUP = fpga-quartus-rg
VM_NAME        = quartus-linux
VM_USER        = braden

# --- Project Settings ---
PROJECT_NAME   = blink
LOCAL_SRC      = ./src
VM_DIR         = ~/fpga_projects/$(PROJECT_NAME)

# --- Remote Paths ---
# Updated to 24.1 as requested
QUARTUS_BIN    = ~/intelFPGA_lite/24.1/quartus/bin

# ==========================================
#   AUTOMATION LOGIC
# ==========================================

# 1. Get the Dynamic IP
VM_IP := $(shell az vm show -d -g $(RESOURCE_GROUP) -n $(VM_NAME) --query publicIps -o tsv 2>/dev/null)

.PHONY: all start stop status sync build download program ssh clean check-ip

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
sync:
	@echo "🔄 Syncing code to Cloud ($(VM_IP))..."
	ssh -o StrictHostKeyChecking=no $(VM_USER)@$(VM_IP) "mkdir -p $(VM_DIR)/output_files"
	rsync -avz --exclude '.git' --exclude 'build' ./ $(VM_USER)@$(VM_IP):$(VM_DIR)

build:
	@echo "🔨 Triggering Cloud Build (Quartus 24.1)..."
	# 1. Compile
	ssh -o StrictHostKeyChecking=no $(VM_USER)@$(VM_IP) "cd $(VM_DIR) && $(QUARTUS_BIN)/quartus_sh --flow compile $(PROJECT_NAME)"
	# 2. Convert to Uncompressed RBF (Safer for JTAG)
	ssh -o StrictHostKeyChecking=no $(VM_USER)@$(VM_IP) "cd $(VM_DIR) && $(QUARTUS_BIN)/quartus_cpf -c -o bitstream_compression=off output_files/$(PROJECT_NAME).sof output_files/$(PROJECT_NAME).rbf"

download:
	@echo "⬇️ Downloading Bitstream..."
	mkdir -p build
	scp -o StrictHostKeyChecking=no $(VM_USER)@$(VM_IP):$(VM_DIR)/output_files/$(PROJECT_NAME).rbf ./build/

program:
	@echo "⚡ Flashing DE10-Nano..."
	# Removed -r to stop the board from reloading the Factory Image
	openFPGALoader -b de10nano --freq 2500000 --probe-firmware ./blaster_6810.hex -v ./build/$(PROJECT_NAME).rbf
	
ssh:
	ssh $(VM_USER)@$(VM_IP)

clean:
	rm -rf build sim/*.vcd sim/*_sim