with import <nixpkgs> {};
with xorg;
pkgs.mkShell rec {
  name = "dwm";
  buildInputs = [ libX11 libXinerama libXft libXcursor ];
}
