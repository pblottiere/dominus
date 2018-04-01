WIRINGPINP_VERSION = 6e76e15c9b4293ba1281caf1b2fee612ac59aee7
WIRINGPINP_SITE = https://github.com/friendlyarm/WiringNP
WIRINGPINP_SITE_METHOD = git

define WIRINGPINP_BUILD_CMDS
	cd $(@D); \
	cd wiringPi; \
	$(TARGET_MAKE_ENV) CC=arm-linux-gcc $(MAKE); \
	$(TARGET_MAKE_ENV) $(MAKE) DESTDIR=$(TARGET_DIR) PREFIX=/usr install; \
	$(TARGET_MAKE_ENV) $(MAKE) DESTDIR=$(STAGING_DIR) PREFIX=/usr install; \
	$(TARGET_MAKE_ENV) $(MAKE) DESTDIR=$(STAGING_DIR) PREFIX=/usr install-headers; \
	cd ../devLib; \
	$(TARGET_MAKE_ENV) CC=arm-linux-gcc CPATH=../wiringPi $(MAKE); \
	$(TARGET_MAKE_ENV) $(MAKE) DESTDIR=$(TARGET_DIR) PREFIX=/usr install; \
	cd ../gpio; \
	mkdir -p $(TARGET_DIR)/usr/bin; \
	$(TARGET_MAKE_ENV) CC=arm-linux-gcc DESTDIR=$(TARGET_DIR) PREFIX=/usr CPATH=../devLib $(MAKE) ;\
	$(TARGET_MAKE_ENV) $(MAKE) DESTDIR=$(TARGET_DIR) PREFIX=/usr install
endef

$(eval $(generic-package))
