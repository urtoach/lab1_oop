{ pkgs }: {
	deps = [
		pkgs.cmake
  pkgs.valgrind-light
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}