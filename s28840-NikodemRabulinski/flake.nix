{
  inputs = {
    flake-parts.url = "github:hercules-ci/flake-parts";
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
  };

  outputs = inputs @ {
    flake-parts,
    ...
  }:
    flake-parts.lib.mkFlake {inherit inputs;} {
      systems = [
        "x86_64-darwin"
        "aarch64-darwin"
        "x86_64-linux"
        "aarch64-linux"
      ];

      perSystem = {
        pkgs,
        ...
      }: {
        devShells.default = with pkgs; (mkShell.override {
          stdenv = gccStdenv;
        }) {
          packages = [ clang-tools ];
          nativeBuildInputs = [ meson ninja ];
        };
      
        formatter = pkgs.alejandra;
        };
    };
}
