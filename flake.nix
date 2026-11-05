{
  description = "ICS 53 development environment";

  inputs = {
    nixpkgs.url = "https://channels.nixos.org/nixpkgs-unstable/nixexprs.tar.zst";
    nixpkgs-stable.url = "github:NixOS/nixpkgs/nixos-25.05";
  };

  outputs = inputs: {
    devShells = builtins.mapAttrs (system: pkgs: {

      default =
        let
          stable = inputs.nixpkgs-stable.legacyPackages.${system};
        in
        (pkgs.mkShell.override {
          stdenv = stable.gcc11Stdenv;
        })
          {
            packages = with pkgs; [
              gdb
              gnumake
              valgrind
              stable.readline
              stable.ncurses
              clang-tools
              criterion
              pkg-config
            ];

            buildInputs = [
              stable.readline
            ];

            shellHook = ''
              cat > .clang-format <<'EOF'
              BasedOnStyle: LLVM
              IndentWidth: 4
              UseTab: Never
              ReflowComments: false
              EOF

              cat > compile_flags.txt <<'EOF'
              -Iinclude
              EOF
            '';
          };
    }) inputs.nixpkgs.legacyPackages;
  };
}
