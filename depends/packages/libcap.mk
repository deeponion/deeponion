package=libcap
$(package)_version=2.24
$(package)_download_path=https://www.kernel.org/pub/linux/libs/security/linux-privs/libcap2/
$(package)_file_name=$(package)-$($(package)_version).tar.xz
$(package)_sha256_hash=cee4568f78dc851d726fc93f25f4ed91cc223b1fe8259daa4a77158d174e6c65
$(package)_dependencies=attr
$(package)_install_libdir=$(build_prefix)/lib/

define $(package)_set_vars
  $(package)_config_opts_linux=--with-pic
  $(package)_config_opts_x86_64_linux=linux-x86_64
  $(package)_config_opts_i686_linux=linux-generic32
  $(package)_config_opts_arm_linux=linux-generic32
  $(package)_config_opts_aarch64_linux=linux-generic64
  $(package)_config_opts_mipsel_linux=linux-generic32
  $(package)_config_opts_mips_linux=linux-generic32
  $(package)_config_opts_powerpc_linux=linux-generic32
endef

define $(package)_config_cmds
  export PKG_CONFIG_LIBDIR=$(host_prefix)/lib/
endef


define $(package)_build_cmds
  echo "MAKE: " $(MAKE) && \
  echo "STAGING: " $($(package)_staging_dir) && \
  echo "LIB: " $(host_prefix)/lib/ && \
  pwd && \
  cp -r $(host_prefix)/lib/* libcap/. && \
  $(MAKE) BUILD_CC=gcc prefix=$(host_prefix) AR="$($(package)_ar)" RANLIB="$($(package)_ranlib)" CC="$($(package)_cc)"
endef

define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) prefix=$(host_prefix) RAISE_SETFCAP=no install && \
  mv $($(package)_staging_dir)$(host_prefix)/lib64 $($(package)_staging_dir)$(host_prefix)/lib
endef

define $(package)_postprocess_cmds
endef

