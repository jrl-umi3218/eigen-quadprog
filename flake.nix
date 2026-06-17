{
  description = "eigen-quadprog is a c++ wrapper around the fortran's quadprog solver";

  inputs.mc-rtc-nix.url = "github:mc-rtc/nixpkgs";

  outputs =
    inputs:
    inputs.mc-rtc-nix.lib.mkFlakoboros inputs (
      { lib, ... }:
      {
        overrideAttrs.eigen-quadprog =
          { drv-prev, pkgs-final, ... }:
          {
            src = lib.cleanSource ./.;
            buildInputs = (drv-prev.buildInputs or [ ]) ++ [ pkgs-final.jrl-cmakemodules ];
          };
      }
    );
}
