//-----------------------------------------------------------------------------
//
// Copyright (C) 2014 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// Abstract Syntax Tree comparator expression bases.
//
//-----------------------------------------------------------------------------

#include "AST/Exp/Cmp.hpp"

#include "IR/Exp.hpp"


//----------------------------------------------------------------------------|
// Macros                                                                     |
//

//
// GDCC_AST_Exp_CmpImpl
//
#define GDCC_AST_Exp_CmpImpl(class, ir) \
   IR::Exp::CRef class::v_getIRExp() const \
   { \
      return IR::ExpCreate_##ir( \
         expL->getIRExp(), expR->getIRExp(), pos); \
   }


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

namespace GDCC
{
   namespace AST
   {
      GDCC_AST_Exp_CmpImpl(Exp_CmpEQ, BranchCmpEQ)
      GDCC_AST_Exp_CmpImpl(Exp_CmpGE, BranchCmpGE)
      GDCC_AST_Exp_CmpImpl(Exp_CmpGT, BranchCmpGT)
      GDCC_AST_Exp_CmpImpl(Exp_CmpLE, BranchCmpLE)
      GDCC_AST_Exp_CmpImpl(Exp_CmpLT, BranchCmpLT)
      GDCC_AST_Exp_CmpImpl(Exp_CmpNE, BranchCmpNE)
   }
}

// EOF
