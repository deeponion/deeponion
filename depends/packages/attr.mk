package=attr
$(package)_version=2.4.47
$(package)_download_path=http://download.savannah.gnu.org/releases/attr/
$(package)_file_name=$(package)-$($(package)_version).src.tar.gz
$(package)_sha256_hash=25772f653ac5b2e3ceeb89df50e4688891e21f723c460636548971652af0a859

define $(package)_config_cmds
  $($(package)_autoconf)
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) prefix=$(host_prefix) install-dev install-lib
endef

define $(package)_postprocess_cmds
endef
