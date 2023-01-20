GBDK_HOME = ../../

LCC = $(GBDK_HOME)bin/lcc 
LCCFLAGS = -Wa-l -Wl-m -Wl-j
BGB = $(GBDK_HOME)/bgb/bgb.exe

PROJECTNAME    = rom

SRCDIR      = src
OBJDIR      = obj
RESDIR      = res
BINS	    = $(PROJECTNAME).gb
CSOURCES    = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(SRCDIR)/**,$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(RESDIR)/**,$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES  = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.s)))
OBJS       = $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.s=$(OBJDIR)/%.o)

all:	$(BINS)

$(OBJDIR)/%.o:	$(SRCDIR)/**/%.c
	$(LCC) $(LCCFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	$(LCC) $(LCCFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:	$(RESDIR)/**/%.c
	$(LCC) $(LCCFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:	$(RESDIR)/%.c
	$(LCC) $(LCCFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:	$(SRCDIR)/%.s
	$(LCC) $(LCCFLAGS) -c -o $@ $<

$(OBJDIR)/%.s:	$(SRCDIR)/%.c
	$(LCC) $(LCCFLAGS) -S -o $@ $<

$(OBJDIR)/linkfile.lk:	$(OBJS)
	rm -f $@
	@for obj in $(OBJS); do \
		echo $$obj >>$@; \
	done

$(BINS): $(OBJDIR)/linkfile.lk
	$(LCC) $(LCCFLAGS) -Wm-yc -o $(BINS) -Wl-f$<
	$(MAKE) run

run:
	$(BGB) rom.gb

clean:
	rm -f  *.map *.noi *.ihx *.gb
	rm -f  $(OBJDIR)/*.*