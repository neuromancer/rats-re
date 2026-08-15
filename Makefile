# Minimal RATS.EXE reconstruction scaffold.
#
# The original binary was most likely built with Visual C++ 4.1.  MSVC 4.20 is
# close enough to start the reconstruction and is the oldest complete compiler
# kit currently used by the surrounding projects.

UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)

# ---------------------------------------------------------------------------
# Original toolchain
# ---------------------------------------------------------------------------

WIBO = ./wibo
CC = $(WIBO) compilers/msvc420/bin/CL.EXE
LINK = $(WIBO) compilers/msvc420/bin/LINK.EXE

MSVC_INC = compilers\msvc420\include
MSVC_LIB = compilers\msvc420\lib

# Initial evidence points to an unoptimised, static release CRT build targeting
# a 386-class CPU.  These flags are a starting point and should change only as
# comparisons against RATS.EXE provide better evidence.
CFLAGS = \
	/nologo \
	/c \
	/MT \
	/Od \
	/G3 \
	/Iinclude \
	/W3

LINKFLAGS = \
	/nologo \
	/SUBSYSTEM:WINDOWS \
	/ENTRY:WinMainCRTStartup \
	/MACHINE:IX86 \
	/ALIGN:4096 \
	/STACK:10240 \
	/INCREMENTAL:NO

GAME_LIBS = \
	kernel32.lib \
	user32.lib \
	gdi32.lib \
	winmm.lib

# ---------------------------------------------------------------------------
# Project files
# ---------------------------------------------------------------------------

ORIGINAL_EXE = RATS.EXE
OUT_DIR = out
TARGET = $(OUT_DIR)/RATS_RE.EXE
MAPFILE = $(OUT_DIR)/RATS_RE.map
SOURCES = \
	src/rats.c \
	src/scores.c \
	src/globals.c
OBJECTS = $(patsubst src/%.c,$(OUT_DIR)/%.obj,$(SOURCES))
ASSEMBLIES = $(patsubst src/%.c,$(OUT_DIR)/%.asm,$(SOURCES))
PROJECT_HEADERS = $(wildcard include/*.h)

RUN_DIR = $(OUT_DIR)/run
RUN_EXE = $(RUN_DIR)/RATS.EXE
ORIGINAL_RUN_DIR = $(OUT_DIR)/run-original
ORIGINAL_RUN_EXE = $(ORIGINAL_RUN_DIR)/RATS.EXE

# ---------------------------------------------------------------------------
# Host tools
# ---------------------------------------------------------------------------

ifeq ($(UNAME_S),Linux)
WIBO_PRESET = release64-clang
WIBO_BIN = wibo-src/build/release64-clang/wibo
else
WIBO_PRESET = release-macos
WIBO_BIN = wibo-src/build/release/wibo
endif

MSVCRT40_URL = https://raw.githubusercontent.com/neuromancer/my-teacher-is-an-alien-re/3d1bfe60522ae05b86bbd2252fd01c8d0a11c3df/3rdparty/msvcrt40.dll
MSVCRT40_SHA256 = ab55a2de2b6faf3daacd3e69473d385ceaead8033f7c79beb6bbf802f230f030
MSVCRT_SOURCE = 3rdparty/msvcrt40.dll
MSVCRT_DLL = compilers/msvc420/bin/msvcrt40.dll

$(WIBO): wibo-src/CMakeLists.txt
	cd wibo-src && cmake --preset $(WIBO_PRESET) && cmake --build --preset $(WIBO_PRESET)
	ln -sf $(WIBO_BIN) $@

wibo-src/CMakeLists.txt:
	@echo "Error: wibo submodule is missing." >&2
	@echo "Run: git submodule update --init --recursive" >&2
	@exit 1

compilers/msvc420/bin/CL.EXE:
	@echo "Error: MSVC 4.20 submodule is missing." >&2
	@echo "Run: git submodule update --init --recursive" >&2
	@exit 1

$(MSVCRT_DLL): $(MSVCRT_SOURCE) | compilers/msvc420/bin/CL.EXE
	cp -f $< $@

$(MSVCRT_SOURCE):
	@mkdir -p $(dir $@)
	@echo "Downloading wibo-compatible msvcrt40.dll..."
	@curl -fL --retry 3 -o "$@.tmp" "$(MSVCRT40_URL)"
	@printf '%s  %s\n' "$(MSVCRT40_SHA256)" "$@.tmp" | \
		shasum -a 256 -c - >/dev/null || \
		(rm -f "$@.tmp"; echo "Error: msvcrt40.dll checksum mismatch." >&2; exit 1)
	@mv "$@.tmp" "$@"

toolchain: $(WIBO) $(MSVCRT_DLL)

# ---------------------------------------------------------------------------
# Build
# ---------------------------------------------------------------------------

all: $(TARGET)

build: $(TARGET)

$(TARGET): $(OBJECTS) | $(MSVCRT_DLL)
	@mkdir -p $(OUT_DIR)
	env LIB='$(MSVC_LIB)' $(LINK) $(LINKFLAGS) /MAP:$(MAPFILE) \
		$(OBJECTS) $(GAME_LIBS) /OUT:$@

$(OUT_DIR)/%.obj: src/%.c $(PROJECT_HEADERS) | $(WIBO) $(MSVCRT_DLL)
	@mkdir -p $(OUT_DIR)
	@env INCLUDE='$(MSVC_INC)' $(CC) $(CFLAGS) $< \
		/Fo$@ \
		/Fa$(OUT_DIR)/$*.asm \
		> $(OUT_DIR)/$*.stdout

# ---------------------------------------------------------------------------
# Assembly comparison
# ---------------------------------------------------------------------------

BINARY_COMP ?= binary-comp
BC_CONFIG = config/binary-comp.json
BC_TARGET = rats

compare-func: $(TARGET)
	@test -n "$(FUNC)" || \
		(echo "usage: make compare-func FUNC=<name> ADDR=<8-hex-address>" >&2; exit 1)
	@test -n "$(ADDR)" || \
		(echo "usage: make compare-func FUNC=<name> ADDR=<8-hex-address>" >&2; exit 1)
	@test -f "ghidra/FUN_$(ADDR).disassembled.txt" || \
		(echo "missing Ghidra export for $(ADDR)" >&2; exit 1)
	@$(BINARY_COMP) compare \
		--config $(BC_CONFIG) \
		--target $(BC_TARGET) \
		--no-build \
		$(FUNC) \
		ghidra/FUN_$(ADDR).disassembled.txt

# ---------------------------------------------------------------------------
# DREAMM runtime
# ---------------------------------------------------------------------------

DREAMM_DIR = .dreamm
DREAMM_VERSION = 4.0x21
DREAMM_BASE_URL = https://dreamm.aarongiles.com/releases/4.0x

ifeq ($(UNAME_S),Darwin)
DREAMM_ARCHIVE = dreamm-$(DREAMM_VERSION)-macos.dmg
DREAMM_BIN = $(DREAMM_DIR)/DREAMM.app/Contents/MacOS/dreamm
TIMEOUT_BIN ?= gtimeout
else
ifeq ($(UNAME_M),aarch64)
DREAMM_ARCHIVE = dreamm-$(DREAMM_VERSION)-linux-arm64.tgz
else
DREAMM_ARCHIVE = dreamm-$(DREAMM_VERSION)-linux-x64.tgz
endif
DREAMM_BIN = $(DREAMM_DIR)/dreamm
TIMEOUT_BIN ?= timeout
endif

DREAMM = $(CURDIR)/$(DREAMM_BIN)
DREAMM_STAMP = $(DREAMM_DIR)/.$(DREAMM_ARCHIVE).stamp
DREAMM_TEST_SECONDS ?= 5

$(DREAMM_STAMP):
	@mkdir -p $(DREAMM_DIR)
	@echo "Downloading DREAMM $(DREAMM_VERSION)..."
	@curl -fL --retry 3 -o $(DREAMM_DIR)/$(DREAMM_ARCHIVE) \
		$(DREAMM_BASE_URL)/$(DREAMM_ARCHIVE)
ifeq ($(UNAME_S),Darwin)
	@rm -rf $(DREAMM_DIR)/mnt
	@hdiutil attach $(DREAMM_DIR)/$(DREAMM_ARCHIVE) \
		-mountpoint $(DREAMM_DIR)/mnt -nobrowse -quiet
	@rm -rf $(DREAMM_DIR)/DREAMM.app
	@cp -R $(DREAMM_DIR)/mnt/DREAMM.app $(DREAMM_DIR)/
	@hdiutil detach $(DREAMM_DIR)/mnt -quiet
	@xattr -dr com.apple.quarantine $(DREAMM_DIR)/DREAMM.app
else
	@rm -rf $(DREAMM_DIR)/dreamm
	@tar xzf $(DREAMM_DIR)/$(DREAMM_ARCHIVE) -C $(DREAMM_DIR) \
		--strip-components=1
endif
	@rm $(DREAMM_DIR)/$(DREAMM_ARCHIVE)
	@rm -f $(DREAMM_DIR)/.dreamm-*.stamp
	@touch "$(DREAMM_STAMP)"

$(DREAMM_BIN): $(DREAMM_STAMP)
	@test -x "$(DREAMM_BIN)" || \
		(echo "Error: DREAMM did not unpack to $(DREAMM_BIN)." >&2; exit 1)

dreamm: $(DREAMM_BIN)

$(RUN_EXE): $(TARGET)
	@mkdir -p $(RUN_DIR)
	cp -f $(TARGET) $@

$(ORIGINAL_RUN_EXE): $(ORIGINAL_EXE)
	@mkdir -p $(ORIGINAL_RUN_DIR)
	cp -f $(ORIGINAL_EXE) $@

run: $(RUN_EXE) | $(DREAMM_BIN)
	cd $(RUN_DIR) && "$(DREAMM)" -mount rw:C=. -launch RATS.EXE

run-original: $(ORIGINAL_RUN_EXE) | $(DREAMM_BIN)
	cd $(ORIGINAL_RUN_DIR) && "$(DREAMM)" -mount rw:C=. -launch RATS.EXE

debug: $(RUN_EXE) | $(DREAMM_BIN)
	cd $(RUN_DIR) && "$(DREAMM)" -mount rw:C=. -debug -launch RATS.EXE

# A zero exit means the placeholder returned normally.  A timeout also counts
# as success because a reconstructed game is expected to remain running.
test: test-dreamm

test-dreamm: $(RUN_EXE) | $(DREAMM_BIN)
	@command -v $(TIMEOUT_BIN) >/dev/null 2>&1 || \
		(echo "Error: $(TIMEOUT_BIN) is required for the DREAMM smoke test." >&2; exit 1)
	@status=0; \
		cd $(RUN_DIR) && \
		$(TIMEOUT_BIN) --signal=TERM --kill-after=1s \
			$(DREAMM_TEST_SECONDS)s "$(DREAMM)" \
			-mount rw:C=. -launch RATS.EXE || status=$$?; \
		case $$status in \
			0) echo "DREAMM smoke test passed." ;; \
			124|137) echo "DREAMM launched RATS.EXE for $(DREAMM_TEST_SECONDS) seconds." ;; \
			*) echo "Error: DREAMM exited with status $$status." >&2; exit $$status ;; \
		esac

test-original: $(ORIGINAL_RUN_EXE) | $(DREAMM_BIN)
	@command -v $(TIMEOUT_BIN) >/dev/null 2>&1 || \
		(echo "Error: $(TIMEOUT_BIN) is required for the DREAMM smoke test." >&2; exit 1)
	@status=0; \
		cd $(ORIGINAL_RUN_DIR) && \
		$(TIMEOUT_BIN) --signal=TERM --kill-after=1s \
			$(DREAMM_TEST_SECONDS)s "$(DREAMM)" \
			-mount rw:C=. -launch RATS.EXE || status=$$?; \
		case $$status in \
			0) echo "Original RATS.EXE exited normally." ;; \
			124|137) echo "Original RATS.EXE ran for $(DREAMM_TEST_SECONDS) seconds." ;; \
			*) echo "Error: DREAMM exited with status $$status." >&2; exit $$status ;; \
		esac

# ---------------------------------------------------------------------------
# Cleanup
# ---------------------------------------------------------------------------

clean:
	rm -rf $(OUT_DIR)

clean-dreamm:
	rm -rf $(DREAMM_DIR)

help:
	@echo "make                 build out/RATS_RE.EXE"
	@echo "make run             launch the rebuilt executable in DREAMM"
	@echo "make run-original    launch the original executable in DREAMM"
	@echo "make test            smoke-test the rebuilt executable in DREAMM"
	@echo "make test-original   smoke-test the original executable in DREAMM"
	@echo "make debug           launch the rebuilt executable in DREAMM's debugger"
	@echo "make compare-func FUNC=Name ADDR=00401000"

.PHONY: \
	all \
	build \
	clean \
	clean-dreamm \
	compare-func \
	debug \
	dreamm \
	help \
	run \
	run-original \
	test \
	test-dreamm \
	test-original \
	toolchain
