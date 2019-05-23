%define bdbv 4.8.30
%global selinux_variants mls strict targeted

%if 0%{?_no_gui:1}
%define _buildqt 0
%define buildargs --with-gui=no
%else
%define _buildqt 1
%if 0%{?_use_qt4}
%define buildargs --with-qrencode --with-gui=qt4
%else
%define buildargs --with-qrencode --with-gui=qt5
%endif
%endif

Name:		DeepOnion
Version:	2.0.2
Release:	2%{?dist}
Summary:	Peer to Peer Cryptographic Currency

Group:		Applications/System
License:	MIT
URL:		https://deeponion.org/
Source0:	https://bitcoin.org/bin/bitcoin-core-%{version}/bitcoin-%{version}.tar.gz
Source1:	http://download.oracle.com/berkeley-db/db-%{bdbv}.NC.tar.gz

Source10:	https://raw.githubusercontent.com/bitcoin/bitcoin/v%{version}/contrib/debian/examples/bitcoin.conf

#man pages
Source20:	https://raw.githubusercontent.com/bitcoin/bitcoin/v%{version}/doc/man/bitcoind.1
Source21:	https://raw.githubusercontent.com/bitcoin/bitcoin/v%{version}/doc/man/bitcoin-cli.1
Source22:	https://raw.githubusercontent.com/bitcoin/bitcoin/v%{version}/doc/man/bitcoin-qt.1

#selinux
Source30:	https://raw.githubusercontent.com/bitcoin/bitcoin/v%{version}/contrib/rpm/bitcoin.te
# Source31 - what about bitcoin-tx and bench_bitcoin ???
Source31:	https://raw.githubusercontent.com/bitcoin/bitcoin/v%{version}/contrib/rpm/bitcoin.fc
Source32:	https://raw.githubusercontent.com/bitcoin/bitcoin/v%{version}/contrib/rpm/bitcoin.if

Source100:	https://upload.wikimedia.org/wikipedia/commons/4/46/Bitcoin.svg

%if 0%{?_use_libressl:1}
BuildRequires:	libressl-devel
%else
BuildRequires:	openssl-devel
%endif
BuildRequires:	boost-devel
BuildRequires:	miniupnpc-devel
BuildRequires:	autoconf automake libtool
BuildRequires:	libevent-devel


Patch0:		bitcoin-0.12.0-libressl.patch


%description
DeepOnion is a digital cryptographic currency that uses peer-to-peer technology to
operate with no central authority or banks; managing transactions and the
issuing of ONIONs is carried out collectively by the network.

%if %{_buildqt}
%package core
Summary:	Peer to Peer Cryptographic Currency
Group:		Applications/System
Obsoletes:	%{name} < %{version}-%{release}
Provides:	%{name} = %{version}-%{release}
%if 0%{?_use_qt4}
BuildRequires:	qt-devel
%else
BuildRequires:	qt5-qtbase-devel
# for /usr/bin/lrelease-qt5
BuildRequires:	qt5-linguist
%endif
BuildRequires:	protobuf-devel
BuildRequires:	qrencode-devel
BuildRequires:	%{_bindir}/desktop-file-validate
# for icon generation from SVG
BuildRequires:	%{_bindir}/inkscape
BuildRequires:	%{_bindir}/convert

%description core
DeepOnion is a digital cryptographic currency that uses peer-to-peer technology to
operate with no central authority or banks; managing transactions and the
issuing of ONIONss is carried out collectively by the network.

This package contains the Qt based graphical client and node. If you are looking
to run a DeepOnion wallet, this is probably the package you want.
%endif


%package libs
Summary:	DeepOnion shared libraries
Group:		System Environment/Libraries

%description libs
This package provides the DeepOnionconsensus shared libraries. These libraries
may be used by third party software to provide consensus verification
functionality.

Unless you know need this package, you probably do not.

%package devel
Summary:	Development files for DeepOnion
Group:		Development/Libraries
Requires:	%{name}-libs = %{version}-%{release}

%description devel
This package contains the header files and static library for the
DeepOnionconsensus shared library. If you are developing or compiling software
that wants to link against that library, then you need this package installed.

Most people do not need this package installed.

%package server
Summary:	The DeepOnion daemon
Group:		System Environment/Daemons
Requires:	DeepOnion-utils = %{version}-%{release}
Requires:	selinux-policy policycoreutils-python
Requires(pre):	shadow-utils
Requires(post):	%{_sbindir}/semodule %{_sbindir}/restorecon %{_sbindir}/fixfiles %{_sbindir}/sestatus
Requires(postun):	%{_sbindir}/semodule %{_sbindir}/restorecon %{_sbindir}/fixfiles %{_sbindir}/sestatus
BuildRequires:	systemd
BuildRequires:	checkpolicy
BuildRequires:	%{_datadir}/selinux/devel/Makefile

%description server
This package provides a stand-alone DeepOnion-core daemon. For most users, this
package is only needed if they need a full-node without the graphical client.

Some third party wallet software will want this package to provide the actual
DeepOnion-core node they use to connect to the network.

If you use the graphical DeepOnion-core client then you almost certainly do not
need this package.

%package utils
Summary:	DeepOnion utilities
Group:		Applications/System

%description utils
This package provides several command line utilities for interacting with a
DeepOnion-core daemon.

The DeepOnion-cli utility allows you to communicate and control a DeepOnion daemon
over RPC, the DeepOnion-tx utility allows you to create a custom transaction, and
the bench_DeepOnion utility can be used to perform some benchmarks.

This package contains utilities needed by the DeepOnion-server package.


%prep
%setup -q
%patch0 -p1 -b .libressl
cp -p %{SOURCE10} ./DeepOnion.conf.example
tar -zxf %{SOURCE1}
cp -p db-%{bdbv}.NC/LICENSE ./db-%{bdbv}.NC-LICENSE
mkdir db4 SELinux
cp -p %{SOURCE30} %{SOURCE31} %{SOURCE32} SELinux/


%build
CWD=`pwd`
cd db-%{bdbv}.NC/build_unix/
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=${CWD}/db4
make install
cd ../..

./autogen.sh
%configure LDFLAGS="-L${CWD}/db4/lib/" CPPFLAGS="-I${CWD}/db4/include/" --with-miniupnpc --enable-glibc-back-compat %{buildargs}
make %{?_smp_mflags}

pushd SELinux
for selinuxvariant in %{selinux_variants}; do
	make NAME=${selinuxvariant} -f %{_datadir}/selinux/devel/Makefile
	mv deeponion.pp deeponion.pp.${selinuxvariant}
	make NAME=${selinuxvariant} -f %{_datadir}/selinux/devel/Makefile clean
done
popd


%install
make install DESTDIR=%{buildroot}

mkdir -p -m755 %{buildroot}%{_sbindir}
mv %{buildroot}%{_bindir}/DeepOniond %{buildroot}%{_sbindir}/DeepOniond

# systemd stuff
mkdir -p %{buildroot}%{_tmpfilesdir}
cat <<EOF > %{buildroot}%{_tmpfilesdir}/DeepOnion.conf
d /run/DeepOniond 0750 deeponion deeponion -
EOF
touch -a -m -t 201504280000 %{buildroot}%{_tmpfilesdir}/DeepOnion.conf

mkdir -p %{buildroot}%{_sysconfdir}/sysconfig
cat <<EOF > %{buildroot}%{_sysconfdir}/sysconfig/DeepOnion
# Provide options to the DeepOnion daemon here, for example
# OPTIONS="-testnet -disable-wallet"

OPTIONS=""

# System service defaults.
# Don't change these unless you know what you're doing.
CONFIG_FILE="%{_sysconfdir}/DeepOnion/DeepOnion.conf"
DATA_DIR="%{_localstatedir}/lib/DeepOnion"
PID_FILE="/run/DeepOniond/DeepOniond.pid"
EOF
touch -a -m -t 201504280000 %{buildroot}%{_sysconfdir}/sysconfig/DeepOnion

mkdir -p %{buildroot}%{_unitdir}
cat <<EOF > %{buildroot}%{_unitdir}/deeponion.service
[Unit]
Description=DeepOnion daemon
After=syslog.target network.target

[Service]
Type=forking
ExecStart=%{_sbindir}/DeepOniond -daemon -conf=\${CONFIG_FILE} -datadir=\${DATA_DIR} -pid=\${PID_FILE} \$OPTIONS
EnvironmentFile=%{_sysconfdir}/sysconfig/DeepOnion
User=deeponion
Group=deeponion

Restart=on-failure
PrivateTmp=true
TimeoutStopSec=120
TimeoutStartSec=60
StartLimitInterval=240
StartLimitBurst=5

[Install]
WantedBy=multi-user.target
EOF
touch -a -m -t 201504280000 %{buildroot}%{_unitdir}/deeponion.service
#end systemd stuff

mkdir %{buildroot}%{_sysconfdir}/DeepOnion
mkdir -p %{buildroot}%{_localstatedir}/lib/DeepOnion

#SELinux
for selinuxvariant in %{selinux_variants}; do
	install -d %{buildroot}%{_datadir}/selinux/${selinuxvariant}
	install -p -m 644 SELinux/deeponion.pp.${selinuxvariant} %{buildroot}%{_datadir}/selinux/${selinuxvariant}/deeponion.pp
done

%if %{_buildqt}
# qt icons
install -D -p share/pixmaps/deeponion.ico %{buildroot}%{_datadir}/pixmaps/deeponion.ico
install -p share/pixmaps/nsis-header.bmp %{buildroot}%{_datadir}/pixmaps/
install -p share/pixmaps/nsis-wizard.bmp %{buildroot}%{_datadir}/pixmaps/
install -p %{SOURCE100} %{buildroot}%{_datadir}/pixmaps/deeponion.svg
%{_bindir}/inkscape %{SOURCE100} --export-png=%{buildroot}%{_datadir}/pixmaps/deeponion16.png -w16 -h16
%{_bindir}/inkscape %{SOURCE100} --export-png=%{buildroot}%{_datadir}/pixmaps/deeponion32.png -w32 -h32
%{_bindir}/inkscape %{SOURCE100} --export-png=%{buildroot}%{_datadir}/pixmaps/deeponion64.png -w64 -h64
%{_bindir}/inkscape %{SOURCE100} --export-png=%{buildroot}%{_datadir}/pixmaps/deeponion128.png -w128 -h128
%{_bindir}/inkscape %{SOURCE100} --export-png=%{buildroot}%{_datadir}/pixmaps/deeponion256.png -w256 -h256
%{_bindir}/convert -resize 16x16 %{buildroot}%{_datadir}/pixmaps/deeponion256.png %{buildroot}%{_datadir}/pixmaps/deeponion16.xpm
%{_bindir}/convert -resize 32x32 %{buildroot}%{_datadir}/pixmaps/deeponion256.png %{buildroot}%{_datadir}/pixmaps/deeponion32.xpm
%{_bindir}/convert -resize 64x64 %{buildroot}%{_datadir}/pixmaps/deeponion256.png %{buildroot}%{_datadir}/pixmaps/deeponion64.xpm
%{_bindir}/convert -resize 128x128 %{buildroot}%{_datadir}/pixmaps/deeponion256.png %{buildroot}%{_datadir}/pixmaps/deeponion128.xpm
%{_bindir}/convert %{buildroot}%{_datadir}/pixmaps/deeponion256.png %{buildroot}%{_datadir}/pixmaps/deeponion256.xpm
touch %{buildroot}%{_datadir}/pixmaps/*.png -r %{SOURCE100}
touch %{buildroot}%{_datadir}/pixmaps/*.xpm -r %{SOURCE100}

# Desktop File - change the touch timestamp if modifying
mkdir -p %{buildroot}%{_datadir}/applications
cat <<EOF > %{buildroot}%{_datadir}/applications/deeponion-core.desktop
[Desktop Entry]
Encoding=UTF-8
Name=DeepOnion
Comment=DeepOnion P2P Cryptocurrency
Comment[fr]=DeepOnion, monnaie virtuelle cryptographique pair à pair
Comment[tr]=DeepOnion, eşten eşe kriptografik sanal para birimi
Exec=DeepOnion-qt %u
Terminal=false
Type=Application
Icon=deeponion128
MimeType=x-scheme-handler/DeepOnion;
Categories=Office;Finance;
EOF
# change touch date when modifying desktop
touch -a -m -t 201511100546 %{buildroot}%{_datadir}/applications/deeponion-core.desktop
%{_bindir}/desktop-file-validate %{buildroot}%{_datadir}/applications/deeponion-core.desktop

# KDE protocol - change the touch timestamp if modifying
mkdir -p %{buildroot}%{_datadir}/kde4/services
cat <<EOF > %{buildroot}%{_datadir}/kde4/services/deeponion-core.protocol
[Protocol]
exec=DeepOnion-qt '%u'
protocol=deeponion
input=none
output=none
helper=true
listing=
reading=false
writing=false
makedir=false
deleting=false
EOF
# change touch date when modifying protocol
touch -a -m -t 201511100546 %{buildroot}%{_datadir}/kde4/services/deeponion-core.protocol
%endif

# man pages
install -D -p %{SOURCE20} %{buildroot}%{_mandir}/man1/deeponiond.1
install -p %{SOURCE21} %{buildroot}%{_mandir}/man1/deeponion-cli.1
%if %{_buildqt}
install -p %{SOURCE22} %{buildroot}%{_mandir}/man1/deeponion-qt.1
%endif

# nuke these, we do extensive testing of binaries in %%check before packaging
rm -f %{buildroot}%{_bindir}/test_*

%check
make check
srcdir=src test/bitcoin-util-test.py
test/functional/test_runner.py --extended

%post libs -p /sbin/ldconfig

%postun libs -p /sbin/ldconfig

%pre server
getent group deeponion >/dev/null || groupadd -r deeponion
getent passwd deeponion >/dev/null ||
	useradd -r -g deeponion -d /var/lib/deeponion -s /sbin/nologin \
	-c "DeepOnion wallet server" deeponion
exit 0

%post server
%systemd_post deeponion.service
# SELinux
if [ `%{_sbindir}/sestatus |grep -c "disabled"` -eq 0 ]; then
for selinuxvariant in %{selinux_variants}; do
	%{_sbindir}/semodule -s ${selinuxvariant} -i %{_datadir}/selinux/${selinuxvariant}/deeponion.pp &> /dev/null || :
done
%{_sbindir}/semanage port -a -t deeponion_port_t -p tcp 17570
%{_sbindir}/semanage port -a -t deeponion_port_t -p tcp 17571
%{_sbindir}/semanage port -a -t deeponion_port_t -p tcp 18580
%{_sbindir}/semanage port -a -t deeponion_port_t -p tcp 18581
%{_sbindir}/semanage port -a -t deeponion_port_t -p tcp 18582
%{_sbindir}/semanage port -a -t deeponion_port_t -p tcp 18583
%{_sbindir}/fixfiles -R deeponion-server restore &> /dev/null || :
%{_sbindir}/restorecon -R %{_localstatedir}/lib/deeponion || :
fi

%posttrans server
%{_bindir}/systemd-tmpfiles --create

%preun server
%systemd_preun deeponion.service

%postun server
%systemd_postun deeponion.service
# SELinux
if [ $1 -eq 0 ]; then
	if [ `%{_sbindir}/sestatus |grep -c "disabled"` -eq 0 ]; then
	%{_sbindir}/semanage port -d -p tcp 17570
	%{_sbindir}/semanage port -d -p tcp 17571
	%{_sbindir}/semanage port -d -p tcp 18580
	%{_sbindir}/semanage port -d -p tcp 18581
	%{_sbindir}/semanage port -d -p tcp 18582
	%{_sbindir}/semanage port -d -p tcp 18583
	for selinuxvariant in %{selinux_variants}; do
		%{_sbindir}/semodule -s ${selinuxvariant} -r deeponion &> /dev/null || :
	done
	%{_sbindir}/fixfiles -R deeponion-server restore &> /dev/null || :
	[ -d %{_localstatedir}/lib/deeponion ] && \
		%{_sbindir}/restorecon -R %{_localstatedir}/lib/deeponion &> /dev/null || :
	fi
fi

%clean
rm -rf %{buildroot}

%if %{_buildqt}
%files core
%defattr(-,root,root,-)
%license COPYING db-%{bdbv}.NC-LICENSE
%doc COPYING DeepOnion.conf.example doc/README.md doc/bips.md doc/files.md doc/multiwallet-qt.md doc/reduce-traffic.md doc/release-notes.md doc/tor.md
%attr(0755,root,root) %{_bindir}/DeepOnion-qt
%attr(0644,root,root) %{_datadir}/applications/deeponion-core.desktop
%attr(0644,root,root) %{_datadir}/kde4/services/deeponion-core.protocol
%attr(0644,root,root) %{_datadir}/pixmaps/*.ico
%attr(0644,root,root) %{_datadir}/pixmaps/*.bmp
%attr(0644,root,root) %{_datadir}/pixmaps/*.svg
%attr(0644,root,root) %{_datadir}/pixmaps/*.png
%attr(0644,root,root) %{_datadir}/pixmaps/*.xpm
%attr(0644,root,root) %{_mandir}/man1/deeponion-qt.1*
%endif

%files libs
%defattr(-,root,root,-)
%license COPYING
%doc COPYING doc/README.md doc/shared-libraries.md
%{_libdir}/lib*.so.*

%files devel
%defattr(-,root,root,-)
%license COPYING
%doc COPYING doc/README.md doc/developer-notes.md doc/shared-libraries.md
%attr(0644,root,root) %{_includedir}/*.h
%{_libdir}/*.so
%{_libdir}/*.a
%{_libdir}/*.la
%attr(0644,root,root) %{_libdir}/pkgconfig/*.pc

%files server
%defattr(-,root,root,-)
%license COPYING db-%{bdbv}.NC-LICENSE
%doc COPYING DeepOnion.conf.example doc/README.md doc/REST-interface.md doc/bips.md doc/dnsseed-policy.md doc/files.md doc/reduce-traffic.md doc/release-notes.md doc/tor.md
%attr(0755,root,root) %{_sbindir}/DeepOniond
%attr(0644,root,root) %{_tmpfilesdir}/DeepOnion.conf
%attr(0644,root,root) %{_unitdir}/deeponion.service
%dir %attr(0750,deeponion,deeponion) %{_sysconfdir}/DeepOnion
%dir %attr(0750,deeponion,deeponion) %{_localstatedir}/lib/DeepOnion
%config(noreplace) %attr(0600,root,root) %{_sysconfdir}/sysconfig/DeepOnion
%attr(0644,root,root) %{_datadir}/selinux/*/*.pp
%attr(0644,root,root) %{_mandir}/man1/deeponiond.1*

%files utils
%defattr(-,root,root,-)
%license COPYING
%doc COPYING DeepOnion.conf.example doc/README.md
%attr(0755,root,root) %{_bindir}/DeepOnion-cli
%attr(0755,root,root) %{_bindir}/DeepOnion-tx
%attr(0755,root,root) %{_bindir}/bench_DeepOnion
%attr(0644,root,root) %{_mandir}/man1/deeponion-cli.1*



%changelog
* Fri Feb 26 2016 Alice Wonder <buildmaster@librelamp.com> - 0.12.0-2
- Rename Qt package from DeepOnoin to DeepOnion-core
- Make building of the Qt package optional
- When building the Qt package, default to Qt5 but allow building
-  against Qt4
- Only run SELinux stuff in post scripts if it is not set to disabled

* Wed Feb 24 2016 Alice Wonder <buildmaster@librelamp.com> - 0.12.0-1
- Initial spec file for 0.12.0 release

# This spec file is written from scratch but a lot of the packaging decisions are directly
# based upon the 0.11.2 package spec file from https://www.ringingliberty.com/bitcoin/
