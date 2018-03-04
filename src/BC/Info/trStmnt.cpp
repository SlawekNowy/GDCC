//-----------------------------------------------------------------------------
//
// Copyright (C) 2016-2018 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// Generic translation functions.
//
//-----------------------------------------------------------------------------

#include "BC/Info.hpp"

#include "Core/Exception.hpp"

#include "IR/Block.hpp"


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

namespace GDCC::BC
{
   //
   // Info::trStmntStk2
   //
   void Info::trStmntStk2()
   {
      CheckArgC(stmnt, 2);

      moveArgStk_dst(stmnt->args[0]);
      moveArgStk_src(stmnt->args[1]);
   }

   //
   // Info::trStmntStk3
   //
   void Info::trStmntStk3(bool ordered)
   {
      CheckArgC(stmnt, 3);

      moveArgStk_dst(stmnt->args[0]);

      auto size = stmnt->args[1].getSize();

      try
      {
         moveArgStk_src(stmnt->args[1]);
      }
      catch(ResetStmnt const &)
      {
         if(ordered && stmnt->next->args[2].a == IR::ArgBase::Stk)
            block->addStmnt(stmnt->next, IR::Code::Swap_W,
               IR::Arg_Stk(size), IR::Arg_Stk(size));

         throw;
      }

      moveArgStk_src(stmnt->args[2]);
   }

   //
   // Info::trStmntShift
   //
   bool Info::trStmntShift(bool moveLit)
   {
      CheckArgC(stmnt, 3);

      if(stmnt->args[1].a != IR::ArgBase::Stk &&
         stmnt->args[2].a == IR::ArgBase::Stk)
         throw Core::ExceptStr(stmnt->pos, "trStmntShift disorder");

      moveArgStk_dst(stmnt->args[0]);
      moveArgStk_src(stmnt->args[1]);

      if(!moveLit && stmnt->args[2].a == IR::ArgBase::Lit)
         return true;

      moveArgStk_src(stmnt->args[2]);
      return false;
   }
}

// EOF

