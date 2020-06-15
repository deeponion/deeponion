package=libseccomp
$(package)_version=2.4.2
$(package)_download_path=https://github.com/seccomp/libseccomp/releases/download/v2.4.2/
$(package)_file_name=$(package)-$($(package)_version).tar.gz
$(package)_sha256_hash=b54f27b53884caacc932e75e6b44304ac83586e2abe7a83eca6daecc5440585b

define $(package)_set_vars
  $(package)_config_opts=--disable-shared --disable-openssl --disable-libseccomp-regress --disable-samples
  $(package)_config_opts_release=--disable-debug-mode
  $(package)_config_opts_linux=--with-pic
endef

define $(package)_config_cmds
  $($(package)_autoconf)
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) install
endef

define $(package)_postprocess_cmds
endef
