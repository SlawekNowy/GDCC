//-----------------------------------------------------------------------------
//
// Copyright (C) 2014-2018 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// Source Representation nullable expression bases.
//
//-----------------------------------------------------------------------------

#ifndef GDCC__SR__Exp__Nullable_H__
#define GDCC__SR__Exp__Nullable_H__

#include "../../SR/Exp/Binary.hpp"


//----------------------------------------------------------------------------|
// Types                                                                      |
//

namespace GDCC::SR
{
   //
   // Exp_NulAnd
   //
   class Exp_NulAnd : public Exp_Binary
   {
      GDCC_Core_CounterPreamble(GDCC::SR::Exp_NulAnd, GDCC::SR::Exp_Binary);
      GDCC_SR_Exp_BinaryCreator(Exp_NulAnd);

   protected:
      virtual void v_genStmnt(GenStmntCtx const &ctx, Arg const &dst) const;

      virtual IRExpCRef v_getIRExp() const;

      virtual bool v_isIRExp() const;
   };

   //
   // Exp_NulOrI
   //
   class Exp_NulOrI : public Exp_Binary
   {
      GDCC_Core_CounterPreamble(GDCC::SR::Exp_NulOrI, GDCC::SR::Exp_Binary);
      GDCC_SR_Exp_BinaryCreator(Exp_NulOrI);

   protected:
      virtual void v_genStmnt(GenStmntCtx const &ctx, Arg const &dst) const;

      virtual IRExpCRef v_getIRExp() const;

      virtual bool v_isIRExp() const;
   };
}

#endif//GDCC__SR__Exp__Nullable_H__
