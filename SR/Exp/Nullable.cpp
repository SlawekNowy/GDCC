//-----------------------------------------------------------------------------
//
// Copyright (C) 2014-2019 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// Source Representation nullable expression bases.
//
//-----------------------------------------------------------------------------

#include "SR/Exp/Nullable.hpp"

#include "SR/Arg.hpp"
#include "SR/Function.hpp"
#include "SR/Temporary.hpp"
#include "SR/Type.hpp"

#include "IR/Block.hpp"
#include "IR/Exp.hpp"
#include "IR/Glyph.hpp"


//----------------------------------------------------------------------------|
// Static Functions                                                           |
//

namespace GDCC::SR
{
   //
   // GenStmnt_Nullable
   //
   static void GenStmnt_Nullable(Exp_Binary const *exp,
      GenStmntCtx const &ctx, Arg const &dst, bool valShrt)
   {
      IR::Code codeShrt = valShrt ? IR::CodeBase::Jcnd_Tru : IR::CodeBase::Jcnd_Nil;

      // Only evaluating for side-effects?
      if(dst.type->getQualAddr().base == IR::ArgBase::Nul)
      {
         // If right operand has no side effects, then it does not need to
         // be evaluated regardless of the value of the left.
         if(!exp->expR->isEffect())
         {
            exp->expL->genStmnt(ctx);
         }
         else
         {
            // If left operand would short, then do not bother doing codegen
            // for right.
            if((!valShrt && exp->expL->isZero()) ||
               (valShrt && exp->expL->isNonzero()))
            {
               exp->expL->genStmnt(ctx);
            }
            else
            {
               IR::Glyph labelEnd = {ctx.prog, ctx.fn->genLabel()};

               exp->expL->genStmntStk(ctx);
               ctx.block.setArgSize()
                  .addStmnt(codeShrt, exp->expL->getIRArgStk(), labelEnd);

               exp->expR->genStmnt(ctx);
               ctx.block.addLabel(labelEnd);
            }
         }

         return;
      }

      // Is left operand known to not short?
      if((valShrt && exp->expL->isZero()) ||
         (!valShrt && exp->expL->isNonzero()))
      {
         exp->expL->genStmnt(ctx);

         // Use the result of expR.
         exp->expR->genStmnt(ctx, dst);

         return;
      }

      // Inversely, if the left operand was known to short, exp would pass
      // isIRExp and this would only be called to evaluate side effects.

      IR::Glyph labelEnd   = {ctx.prog, ctx.fn->genLabel()};
      IR::Glyph labelShort = {ctx.prog, ctx.fn->genLabel()};

      {
         // Evaluate left operand to stack and store.

         exp->expL->genStmntStk(ctx);

         Temporary tmp{ctx, exp->pos, exp->expL->getType()->getSizeWords()};
         ctx.block.addStmnt(IR::CodeBase::Move, tmp.getArg(), tmp.getArgStk());

         ctx.block.setArgSize().addStmnt(codeShrt, tmp.getArg(), labelShort);

         // Evaluate right operand to stack.
         exp->expR->genStmntStk(ctx);
         ctx.block.setArgSize().addStmnt(IR::CodeBase::Jump, labelEnd);

         // Shorted result.
         ctx.block.addLabel(labelShort);
         ctx.block.addStmnt(IR::CodeBase::Move, dst.getIRArgStk(), tmp.getArg());
      }

      // End.
      ctx.block.addLabel(labelEnd);

      // Move to destination.
      GenStmnt_MovePart(exp, ctx, dst, false, true);
   }
}


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

namespace GDCC::SR
{
   //
   // Exp_NulAnd::v_genStmnt
   //
   void Exp_NulAnd::v_genStmnt(GenStmntCtx const &ctx, Arg const &dst) const
   {
      GenStmnt_Nullable(this, ctx, dst, false);
   }

   //
   // Exp_NulAnd::v_getIRExp
   //
   IR::Exp::CRef Exp_NulAnd::v_getIRExp() const
   {
      if(expL->isZero())
         return IR::ExpCreate_Value(expL->getIRExp()->getValue(), pos);

      if(expL->isNonzero() && expR->isIRExp())
         return IR::ExpCreate_Value(expR->getIRExp()->getValue(), pos);

      return IR::ExpCreate_NulAnd(expL->getIRExp(), expR->getIRExp(), pos);
   }

   //
   // Exp_NulAnd::v_isIRExp
   //
   bool Exp_NulAnd::v_isIRExp() const
   {
      if(expL->isZero())                       return true;
      if(expL->isNonzero() && expR->isIRExp()) return true;

      return Super::v_isIRExp();
   }

   //
   // Exp_NulOrI::v_genStmnt
   //
   void Exp_NulOrI::v_genStmnt(GenStmntCtx const &ctx, Arg const &dst) const
   {
      GenStmnt_Nullable(this, ctx, dst, true);
   }

   //
   // Exp_NulOrI::v_getIRExp
   //
   IR::Exp::CRef Exp_NulOrI::v_getIRExp() const
   {
      if(expL->isNonzero())
         return IR::ExpCreate_Value(expL->getIRExp()->getValue(), pos);

      if(expL->isZero() && expR->isIRExp())
         return IR::ExpCreate_Value(expR->getIRExp()->getValue(), pos);

      return IR::ExpCreate_NulOrI(expL->getIRExp(), expR->getIRExp(), pos);
   }

   //
   // Exp_NulOrI::v_isIRExp
   //
   bool Exp_NulOrI::v_isIRExp() const
   {
      if(expL->isNonzero())                 return true;
      if(expL->isZero() && expR->isIRExp()) return true;

      return Super::v_isIRExp();
   }
}

// EOF
