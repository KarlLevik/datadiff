Name:    datadiff
Version: 1
Release: 1%{?dist}
Summary: Retrieves data from two data sources, compares the contents of the result sets, and generates SQL statements to cancel out the differences.

License: Public Domain
Source0: datadiff

%description
Generate SQL to cancel out differences between two result sets.

%install
mkdir -p %{buildroot}%{_bindir}
install -p -m 755 %{SOURCE0} %{buildroot}%{_bindir}

%files
%{_bindir}/datadiff

%changelog

