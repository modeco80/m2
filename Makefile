# Top-level makefile for m2
# Is kind of shoddy atm

define build_dir
	$(MAKE) -C $(1)
endef

define clean_dir
	$(MAKE) -C $(1) clean
endef

.PHONY: all clean

all:
	$(call build_dir, base/libc/kernel)
	$(call build_dir, base/kernel)

clean:
	$(call clean_dir, base/libc/kernel)
	$(call clean_dir, base/kernel)
