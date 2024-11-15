//-----------------------------------------------------------------------------
//
// Copyright (C) 2013-2018 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// Intermediary Representation expression base.
//
//-----------------------------------------------------------------------------

#include "IR/Exp.hpp"

#include "IR/IArchive.hpp"
#include "IR/OArchive.hpp"

#include "Core/Exception.hpp"


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

namespace GDCC::IR
{
   //
   // Exp constructor
   //
   Exp::Exp(IArchive &in) : pos{GetIR(in, pos)}
   {
   }

   //
   // Exp::operator == Exp
   //
   bool Exp::operator == (Exp const &e) const
   {
      return this == &e || v_isEqual(&e) || e.v_isEqual(this) ||
         (isValue() && e.isValue() && getValue() == e.getValue());
   }

   //
   // Exp::getType
   //
   Type Exp::getType() const
   {
      try {return v_getType();}
      catch(TypeError const &)
      {
         Core::Error(pos, "type mismatch");
      }
   }

   //
   // Exp::getValue
   //
   Value Exp::getValue() const
   {
      try {return v_getValue();}
      catch(TypeError const &)
      {
         Core::Error(pos, "type mismatch");
      }
   }

   //
   // Exp::isNonzero
   //
   bool Exp::isNonzero() const
   {
      return isValue() && getValue();
   }

   //
   // Exp::isZero
   //
   bool Exp::isZero() const
   {
      return isValue() && !getValue();
   }

   //
   // Exp::putIR
   //
   OArchive &Exp::putIR(OArchive &out) const
   {
      return v_putIR(out << getName());
   }

   //
   // Exp::v_putIR
   //
   OArchive &Exp::v_putIR(OArchive &out) const
   {
      return out << pos;
   }

   //
   // Exp::v_isEqual
   //
   bool Exp::v_isEqual(Exp const *) const
   {
      return false;
   }

   //
   // GetIR_T<Exp::CPtr>::GetIR_F
   //
   Exp::CPtr GetIR_T<Exp::CPtr>::GetIR_F(IArchive &in)
   {
      switch(GetIR<Core::StringIndex>(in))
      {
      case Core::STR_None: return nullptr;

      case Core::STR_Add:       return ExpGetIR_Add      (in);
      case Core::STR_AddPtrRaw: return ExpGetIR_AddPtrRaw(in);
      case Core::STR_Array:     return ExpGetIR_Array    (in);
      case Core::STR_Assoc:     return ExpGetIR_Assoc    (in);
      case Core::STR_BitAnd:    return ExpGetIR_BitAnd   (in);
      case Core::STR_BitOrI:    return ExpGetIR_BitOrI   (in);
      case Core::STR_BitOrX:    return ExpGetIR_BitOrX   (in);
      case Core::STR_CmpEQ:     return ExpGetIR_CmpEQ    (in);
      case Core::STR_CmpGE:     return ExpGetIR_CmpGE    (in);
      case Core::STR_CmpGT:     return ExpGetIR_CmpGT    (in);
      case Core::STR_CmpLE:     return ExpGetIR_CmpLE    (in);
      case Core::STR_CmpLT:     return ExpGetIR_CmpLT    (in);
      case Core::STR_CmpNE:     return ExpGetIR_CmpNE    (in);
      case Core::STR_Cnd:       return ExpGetIR_Cnd      (in);
      case Core::STR_Cst:       return ExpGetIR_Cst      (in);
      case Core::STR_Div:       return ExpGetIR_Div      (in);
      case Core::STR_Glyph:     return ExpGetIR_Glyph    (in);
      case Core::STR_Inv:       return ExpGetIR_Inv      (in);
      case Core::STR_Mod:       return ExpGetIR_Mod      (in);
      case Core::STR_Mul:       return ExpGetIR_Mul      (in);
      case Core::STR_Neg:       return ExpGetIR_Neg      (in);
      case Core::STR_Not:       return ExpGetIR_Not      (in);
      case Core::STR_NulAnd:    return ExpGetIR_NulAnd   (in);
      case Core::STR_NulOrI:    return ExpGetIR_NulOrI   (in);
      case Core::STR_LogAnd:    return ExpGetIR_LogAnd   (in);
      case Core::STR_LogOrI:    return ExpGetIR_LogOrI   (in);
      case Core::STR_LogOrX:    return ExpGetIR_LogOrX   (in);
      case Core::STR_ShL:       return ExpGetIR_ShL      (in);
      case Core::STR_ShR:       return ExpGetIR_ShR      (in);
      case Core::STR_Sub:       return ExpGetIR_Sub      (in);
      case Core::STR_Tuple:     return ExpGetIR_Tuple    (in);
      case Core::STR_Union:     return ExpGetIR_Union    (in);
      case Core::STR_Value:     return ExpGetIR_Value    (in);

      default:
         Core::Error({}, "invalid Exp");
      }
   }

   //
   // GetIR_T<Exp::CRef>::GetIR_F
   //
   Exp::CRef GetIR_T<Exp::CRef>::GetIR_F(IArchive &in)
   {
      if(auto exp = GetIR<Exp::CPtr>(in))
         return static_cast<Exp::CRef>(exp);

      Core::Error({}, "invalid Exp::Ref");
   }

   //
   // operator OArchive << Exp const *
   //
   OArchive &operator << (OArchive &out, Exp const *in)
   {
      if(in)
         return in->putIR(out);
      else
         return out << Core::STR_None;
   }

   //
   // ExpCreate_Zero
   //
   Exp::CRef ExpCreate_Zero()
   {
      static Exp::CRef const exp =
         ExpCreate_Value(Value_Fixed(0, {1, 0, false, false}), {nullptr, 0});

      return exp;
   }
}

// EOF
