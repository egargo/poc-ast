{
  pkgs ? import <nixpkgs> {
    config = {
      allowUnfree = true;
    };
  },
}:

pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    gcc
    gnumake
  ];

  buildInputs = with pkgs; [
    glibc
  ];

  shellHook = ''
    export C_INCLUDE_PATH=${pkgs.glibc.dev}/include
    export LD_LIBRARY_PATH=${pkgs.glibc.dev}/lib
    export LIBRARY_PATH=${pkgs.glibc.dev}/lib
  '';
}
