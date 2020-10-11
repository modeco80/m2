# libc-includes.mk: An extension to the libc build that will
# place EVERY single libc include file that's public

define verbose_place
	$(info Placing libc include $(1))
	@place $(1)
endef

post: target-post
	$(call verbose_place,../include/string.h)
	$(call verbose_place,../include/stdlib.h)
	$(call verbose_place,../include/sys/cdefs.h)