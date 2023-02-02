#include "riscvIla.hpp"
#include <ilang/ilang++.h>
using namespace ilang;

void GenerateVerifyTarget(Ila & model) {

  RtlVerifyConfig vtg_cfg;


  vtg_cfg.PortDeclStyle = _vtg_config::PortDeclStyleT::NEW;
  vtg_cfg.ForceInstCheckReset = false;
  vtg_cfg.YosysSmtArrayForRegFile = false;
  vtg_cfg.SanityCheck_ValueRecorderOverlyConstrained = false;
  vtg_cfg.SanityCheck_ValueRecorderTriggeredBeforeCommit = false;

  std::string RootPath = "/home/yan/EnvSynSamples/ILAng/PICO";
  std::string VerilogPath = RootPath + "/verilog/";
  std::string RefrelPath = RootPath + "/refinement/";
  std::string OutputPath = RootPath + "/verification/";

  IlaVerilogRefinementChecker vg(
      model,
      {},                            // no include
      { VerilogPath + "picorv32.v"}, // designs
      "picorv32",                                             // top_module_name
      RefrelPath + "vmap.json",            // variable mapping
      RefrelPath + "cond.json",          // conditions of start/ready
      OutputPath,                                            // output path
      ModelCheckerSelection::PONO, // backend: COSA
      vtg_cfg);  // target generator configuration
  // VerilogVerificationTargetGenerator vg(
  //     {},                                                 // no include
  //     {os_portable_append_dir(dirName, "simple_pipe.v")}, // vlog files
  //     "pipeline_v",                                       // top_module_name
  //     os_portable_append_dir(rfDir,
  //                            "vmap-rfmap-pvholder-reset.json"), // variable mapping
  //     os_portable_append_dir(rfDir,
  //                            "cond-rfmap-pvholder-reset.json"), // instruction-mapping
  //     os_portable_append_dir(dirName, "verify_pvholder_reset"), // verification dir
  //     ila_model.get(),                                    // ILA model
  //     ModelCheckerSelection::PONO, // engine
  //     cfg
  // );


}


int main() {
  // TODO

  riscvILA_user riscvILA(0);
  riscvILA.addInstructions(); // 37 base integer instructions

  GenerateVerifyTarget(riscvILA.model);

  return 0;
}

