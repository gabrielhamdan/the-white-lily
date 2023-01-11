GBDK_HOME = ../../

LCC = $(GBDK_HOME)bin/lcc 
LCCFLAGS = -Wa-l -Wl-m -Wl-j
BGB = C:\Users\gabri\Desktop\Gabriel\GameDev\gbdk\bgb\bgb.exe

PROJECTNAME    = rom

SRCDIR      = src
OBJDIR      = obj
RESDIR      = res
BINS	    = $(PROJECTNAME).gb
CSOURCES    = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(SRCDIR)/**,$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(RESDIR)/**,$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES  = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.s)))
OBJS       = $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.s=$(OBJDIR)/%.o)

#all:	prepare $(BINS)
all:	$(BINS)

$(OBJDIR)/%.o:	$(SRCDIR)/**/%.c
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# Compile .c files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	$(LCC) $(LCCFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:	$(RESDIR)/**/%.c
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# Compile .c files in "res/" to .o object files
$(OBJDIR)/%.o:	$(RESDIR)/%.c
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# Compile .s assembly files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.s
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# If needed, compile .c files in "src/" to .s assembly files
# (not required if .c is compiled directly to .o)
$(OBJDIR)/%.s:	$(SRCDIR)/%.c
	$(LCC) $(LCCFLAGS) -S -o $@ $<


$(OBJDIR)/linkfile.lk:	$(OBJS)
	rm -f $@
	@for obj in $(OBJS); do \
		echo $$obj >>$@; \
	done

# Link the compiled object files (via linkerfile) into a .gb ROM file
$(BINS):	$(OBJDIR)/linkfile.lk
	$(LCC) $(LCCFLAGS) -Wm-yc -o $(BINS) -Wl-f$<
	$(MAKE) run

prepare:
	mkdir -p $(OBJDIR)
	mkdir -p $(RESDIR)

run:
	$(BGB) rom.gb

clean:
	rm -f  *.map *.noi
	rm -f  $(OBJDIR)/*.*