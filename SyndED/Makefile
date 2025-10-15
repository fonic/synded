# ------------------------------------------------------------------------------
#                                                                              -
#  Syndicate Editor - Makefile                                                 -
#                                                                              -
#  Created by Fonic <https://github.com/fonic>                                 -
#  Date: 10/08/25 - 10/14/25                                                   -
#                                                                              -
# ------------------------------------------------------------------------------


# --------------------------------------
#                                      -
#  Variables                           -
#                                      -
# --------------------------------------

APPLICATION_NAME         :=  SyndED
BUILD_DIR                :=  build
INCLUDE_DIR              :=  include
LIBRARY_DIR              :=  lib
SOURCE_DIR               :=  src
HEADER_FILES             :=  $(wildcard $(SOURCE_DIR)/*.h) $(wildcard $(INCLUDE_DIR)/*.h)
SOURCE_FILES             :=  $(wildcard $(SOURCE_DIR)/*.c)
LIBRARY_NAMES            :=
LIBRARY_FILES            :=  $(LIBRARY_NAMES:%=$(LIBRARY_DIR)/lib%.so)

LIBRARY_COPY_DIR         :=  $(BUILD_DIR)/lib
LIBRARY_COPY_FILES       :=  $(LIBRARY_FILES:$(LIBRARY_DIR)/%.so=$(LIBRARY_COPY_DIR)/%.so)

EXEFIL_BASE_DIR          :=  $(BUILD_DIR)/bin
EXEFIL_STATIC_RELEASE    :=  $(EXEFIL_BASE_DIR)/$(APPLICATION_NAME)_static_release
EXEFIL_STATIC_DEBUG      :=  $(EXEFIL_BASE_DIR)/$(APPLICATION_NAME)_static_debug
EXEFIL_DYNAMIC_RELEASE   :=  $(EXEFIL_BASE_DIR)/$(APPLICATION_NAME)_dynamic_release
EXEFIL_DYNAMIC_DEBUG     :=  $(EXEFIL_BASE_DIR)/$(APPLICATION_NAME)_dynamic_debug
EXEFIL_ASANDYN_RELEASE   :=  $(EXEFIL_BASE_DIR)/$(APPLICATION_NAME)_asandyn_release
EXEFIL_ASANDYN_DEBUG     :=  $(EXEFIL_BASE_DIR)/$(APPLICATION_NAME)_asandyn_debug

OBJDIR_BASE_DIR          :=  $(BUILD_DIR)/obj
OBJDIR_STATIC_RELEASE    :=  $(OBJDIR_BASE_DIR)/static_release
OBJDIR_STATIC_DEBUG      :=  $(OBJDIR_BASE_DIR)/static_debug
OBJDIR_DYNAMIC_RELEASE   :=  $(OBJDIR_BASE_DIR)/dynamic_release
OBJDIR_DYNAMIC_DEBUG     :=  $(OBJDIR_BASE_DIR)/dynamic_debug
OBJDIR_ASANDYN_RELEASE   :=  $(OBJDIR_BASE_DIR)/asandyn_release
OBJDIR_ASANDYN_DEBUG     :=  $(OBJDIR_BASE_DIR)/asandyn_debug

OBJFIL_STATIC_RELEASE    :=  $(SOURCE_FILES:$(SOURCE_DIR)/%.c=$(OBJDIR_STATIC_RELEASE)/%.o)
OBJFIL_STATIC_DEBUG      :=  $(SOURCE_FILES:$(SOURCE_DIR)/%.c=$(OBJDIR_STATIC_DEBUG)/%.o)
OBJFIL_DYNAMIC_RELEASE   :=  $(SOURCE_FILES:$(SOURCE_DIR)/%.c=$(OBJDIR_DYNAMIC_RELEASE)/%.o)
OBJFIL_DYNAMIC_DEBUG     :=  $(SOURCE_FILES:$(SOURCE_DIR)/%.c=$(OBJDIR_DYNAMIC_DEBUG)/%.o)
OBJFIL_ASANDYN_RELEASE   :=  $(SOURCE_FILES:$(SOURCE_DIR)/%.c=$(OBJDIR_ASANDYN_RELEASE)/%.o)
OBJFIL_ASANDYN_DEBUG     :=  $(SOURCE_FILES:$(SOURCE_DIR)/%.c=$(OBJDIR_ASANDYN_DEBUG)/%.o)

CC                       :=  gcc

CFLAGS_COMMON            :=  -std=c23 -g -Wall -Wextra -O2 -I.
CFLAGS_STATIC_RELEASE    :=  $(CFLAGS_COMMON) -DRELEASE
CFLAGS_STATIC_DEBUG      :=  $(CFLAGS_COMMON) -DDEBUG
CFLAGS_DYNAMIC_RELEASE   :=  $(CFLAGS_COMMON) -DRELEASE
CFLAGS_DYNAMIC_DEBUG     :=  $(CFLAGS_COMMON) -DDEBUG
CFLAGS_ASANDYN_RELEASE   :=  $(CFLAGS_COMMON) -fsanitize=address -fno-omit-frame-pointer -DRELEASE
CFLAGS_ASANDYN_DEBUG     :=  $(CFLAGS_COMMON) -fsanitize=address -fno-omit-frame-pointer -DDEBUG

LDFLAGS_COMMON           :=  -L$(LIBRARY_DIR) -Wl,-rpath=\$$ORIGIN/../lib
LDFLAGS_STATIC_RELEASE   :=  $(LDFLAGS_COMMON) -static -s
LDFLAGS_STATIC_DEBUG     :=  $(LDFLAGS_COMMON) -static
LDFLAGS_DYNAMIC_RELEASE  :=  $(LDFLAGS_COMMON) -s
LDFLAGS_DYNAMIC_DEBUG    :=  $(LDFLAGS_COMMON)
LDFLAGS_ASANDYN_RELEASE  :=  $(LDFLAGS_COMMON) -fsanitize=address -fno-omit-frame-pointer
LDFLAGS_ASANDYN_DEBUG    :=  $(LDFLAGS_COMMON) -fsanitize=address -fno-omit-frame-pointer

LDLIBS_COMMON            :=  $(LIBRARY_NAMES:%=-l%)
LDLIBS_STATIC_RELEASE    :=  $(LDLIBS_COMMON)
LDLIBS_STATIC_DEBUG      :=  $(LDLIBS_COMMON)
LDLIBS_DYNAMIC_RELEASE   :=  $(LDLIBS_COMMON)
LDLIBS_DYNAMIC_DEBUG     :=  $(LDLIBS_COMMON)
LDLIBS_ASANDYN_RELEASE   :=  $(LDLIBS_COMMON)
LDLIBS_ASANDYN_DEBUG     :=  $(LDLIBS_COMMON)


# --------------------------------------
#                                      -
#  Targets                             -
#                                      -
# --------------------------------------

# Phony targets that don't actually produce files of the same name (e.g.
# target 'clean' never creates a file named 'clean')
.PHONY: all static_release static_debug dynamic_release dynamic_debug asandyn_release asandyn_debug clean

# Target incorporating all main targets; when running 'make' without any
# arguments, it starts with the first target it finds (i.e. 'all' here)
all: static_release static_debug dynamic_release dynamic_debug asandyn_release asandyn_debug

# Targets creating builds (main targets)
static_release: $(EXEFIL_STATIC_RELEASE)
static_debug: $(EXEFIL_STATIC_DEBUG)
dynamic_release: $(EXEFIL_DYNAMIC_RELEASE) $(LIBRARY_COPY_FILES)
dynamic_debug: $(EXEFIL_DYNAMIC_DEBUG) $(LIBRARY_COPY_FILES)
asandyn_release: $(EXEFIL_ASANDYN_RELEASE) $(LIBRARY_COPY_FILES)
asandyn_debug: $(EXEFIL_ASANDYN_DEBUG) $(LIBRARY_COPY_FILES)

# Targets producing executable files (linking)
$(EXEFIL_STATIC_RELEASE): $(OBJFIL_STATIC_RELEASE)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS_STATIC_RELEASE) $^ $(LDLIBS_STATIC_RELEASE) -o $@
$(EXEFIL_STATIC_DEBUG): $(OBJFIL_STATIC_DEBUG)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS_STATIC_DEBUG) $^ $(LDLIBS_STATIC_DEBUG) -o $@
$(EXEFIL_DYNAMIC_RELEASE): $(OBJFIL_DYNAMIC_RELEASE)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS_DYNAMIC_RELEASE) $^ $(LDLIBS_DYNAMIC_RELEASE) -o $@
$(EXEFIL_DYNAMIC_DEBUG): $(OBJFIL_DYNAMIC_DEBUG)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS_DYNAMIC_DEBUG) $^ $(LDLIBS_DYNAMIC_DEBUG) -o $@
$(EXEFIL_ASANDYN_RELEASE): $(OBJFIL_ASANDYN_RELEASE)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS_ASANDYN_RELEASE) $^ $(LDLIBS_ASANDYN_RELEASE) -o $@
$(EXEFIL_ASANDYN_DEBUG): $(OBJFIL_ASANDYN_DEBUG)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS_ASANDYN_DEBUG) $^ $(LDLIBS_ASANDYN_DEBUG) -o $@

# Targets producing object files (compiling)
$(OBJDIR_STATIC_RELEASE)/%.o: $(SOURCE_DIR)/%.c $(HEADER_FILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS_STATIC_RELEASE) -c $< -o $@
$(OBJDIR_STATIC_DEBUG)/%.o: $(SOURCE_DIR)/%.c $(HEADER_FILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS_STATIC_DEBUG) -c $< -o $@
$(OBJDIR_DYNAMIC_RELEASE)/%.o: $(SOURCE_DIR)/%.c $(HEADER_FILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS_DYNAMIC_RELEASE) -c $< -o $@
$(OBJDIR_DYNAMIC_DEBUG)/%.o: $(SOURCE_DIR)/%.c $(HEADER_FILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS_DYNAMIC_DEBUG) -c $< -o $@
$(OBJDIR_ASANDYN_RELEASE)/%.o: $(SOURCE_DIR)/%.c $(HEADER_FILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS_ASANDYN_RELEASE) -c $< -o $@
$(OBJDIR_ASANDYN_DEBUG)/%.o: $(SOURCE_DIR)/%.c $(HEADER_FILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS_ASANDYN_DEBUG) -c $< -o $@

# Target copying library files (.so) for dynamic builds
$(LIBRARY_COPY_DIR)/%.so: $(LIBRARY_DIR)/%.so
	@mkdir -p $(@D)
	cp $< $@

# Target to clean up files produced by builds
clean:
	@#rm -rf $(BUILD_DIR)/*
	$(RM) -r $(BUILD_DIR)/*
