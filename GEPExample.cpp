// GEPExample.cpp
// by Andrew Santosa <santosa_1999@yahoo.com>, National University of
// Singapore
// 
// This software is in the public domain.

#include "llvm/DebugInfo.h"
#include "llvm/Pass.h"
#include "llvm/PassManager.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/LinkAllPasses.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/SourceMgr.h"

int main(int argc, char **argv) {
  llvm::LLVMContext &context = llvm::getGlobalContext();
  llvm::SMDiagnostic err;
  llvm::Module *M = llvm::ParseIRFile(argv[1], err, context);
  if (!M) {
    llvm::errs() << "failed to read IR file" << argv[1] << "\n";
    return 1;
  }

  for (llvm::Module::iterator fit = M->begin(), fie = M->end(); fit != fie; ++fit) {
    for (llvm::Function::iterator bit = fit->begin(), bie = fit->end(); bit != bie; ++bit) {
      for (llvm::BasicBlock::iterator it = bit->begin(), ie = bit->end(); it != ie; ++it) {
        switch (it->getOpcode()) {
        case llvm::Instruction::Store: {
	  llvm::ConstantExpr *ptrOp = llvm::dyn_cast<llvm::ConstantExpr>(it->getOperand(0));
	  if (ptrOp) {
	    switch (ptrOp->getOpcode()) {
	    case llvm::Instruction::BitCast: {
	      ptrOp = llvm::dyn_cast<llvm::ConstantExpr>(ptrOp->getOperand(0));
	      if (ptrOp) {
		switch (ptrOp->getOpcode()) {
		case llvm::Instruction::GetElementPtr: {
		  for (unsigned i=0; i < ptrOp->getNumOperands(); ++i) {
		    ptrOp->getOperand(i)->dump();
		  }
		  break;
		}
		default:
		  break;
		}
	      }
	      break;
	    }
	    default:
	      break;
	    }
	  }
	  break;
	}
	default:
	  break;
	}
      }
    }
  }
  return 0;
}
