Name: buteo-sync-plugins-google
Version: 0.1.0
Release: 1
Summary: Buteo Google Synchronization plugins
Group: System/Libraries
URL: https://github.com/nemomobile/buteo-sync-plugins-google
License: LGPLv2.1
Source0: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires: pkgconfig(glib-2.0)
BuildRequires: buteo-syncfw-devel
BuildRequires: qt4-devel, qtcontacts-sqlite
BuildRequires: libqtcontacts-devel

%description
%{summary}.

%files
%defattr(-,root,root,-)
%config %{_sysconfdir}/sync
%{_libdir}/sync/*.so

%package doc
Summary: Documentation for %{name}
Group: Documentation

%description doc
%{summary}.

%files doc
%defattr(-,root,root,-)
%{_docdir}/sync-app-doc


%package tests
Summary: Tests for %{name}
Group: System/Libraries
Requires: %{name} = %{version}-%{release}

%description tests
%{summary}.

%files tests
%defattr(-,root,root,-)
%{_bindir}/*-tests
%{_datadir}/sync-app-tests
%{_datadir}/%{name}-tests


%prep
%setup -q


%build
qmake
make %{?_smp_mflags}


%install
rm -rf %{buildroot}

make INSTALL_ROOT=%{buildroot} install


%clean
rm -rf %{buildroot}
