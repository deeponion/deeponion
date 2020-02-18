package=attr
$(package)_version=2.4.47
$(package)_download_path=http://download.savannah.gnu.org/releases/attr/
$(package)_file_name=$(package)-$($(package)_version).src.tar.gz
$(package)_sha256_hash=25772f653ac5b2e3ceeb89df50e4688891e21f723c460636548971652af0a859

define $(package)_set_vars
#$(package)_config_opts_arm_linux += -platform linux-g++ -xplatform bitcoin-linux-g++
#$(package)_config_opts_i686_linux  = -xplatform linux-g++-32
#$(package)_config_opts_x86_64_linux = -xplatform linux-g++-64
#$(package)_config_opts_aarch64_linux = -xplatform linux-aarch64-gnu-g++
#$(package)_config_opts_powerpc64_linux = -platform linux-g++ -xplatform bitcoin-linux-g++
#$(package)_config_opts_powerpc64le_linux = -platform linux-g++ -xplatform bitcoin-linux-g++
#$(package)_config_opts_riscv64_linux = -platform linux-g++ -xplatform bitcoin-linux-g++
#$(package)_config_opts_s390x_linux = -platform linux-g++ -xplatform bitcoin-linux-g++
#  $(package)_config_opts+=$($(package)_cflags) $($(package)_cppflags)
#  $(package)_config_opts_linux=--with-pic
#  $(package)_config_opts_x86_64_linux=linux-x86_64
#  $(package)_config_opts_i686_linux=linux-generic32
#  $(package)_config_opts_arm_linux=linux-generic32
#  $(package)_config_opts_aarch64_linux=linux-generic64
#  $(package)_config_opts_aarch64_linux = -xplatform linux-aarch64-gnu-g++
#  $(package)_config_opts_mipsel_linux=linux-generic32
#  $(package)_config_opts_mips_linux=linux-generic32
#  $(package)_config_opts_powerpc_linux=linux-generic32
endef

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
