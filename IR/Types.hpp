//-----------------------------------------------------------------------------
//
// Copyright (C) 2018-2019 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// Common typedefs and class forward declarations.
//
//-----------------------------------------------------------------------------

#ifndef GDCC__IR__Types_H__
#define GDCC__IR__Types_H__

#include "../Target/Types.hpp"

#if !GDCC_Core_BigNum
#error "GDCC::IR requires GDCC_Core_BigNum"
#endif


//----------------------------------------------------------------------------|
// Types                                                                      |
//

namespace GDCC::IR
{
   using Target::AddrBase;
   using Target::AddrSpace;
   using Target::CallType;

   enum class CodeBase;
   enum class Linkage;
   enum class TypeBase;

   class Arg;
   class ArgPart;
   class ArgPtr1;
   class ArgPtr2;
   class Block;
   class Code;
   class CodeType;
   class DJump;
   class Glyph;
   template<typename T>
   struct GetIR_T;
   template<typename T>
   class GetIRCaller;
   class Exp;
   class Exp_Add;
   class Exp_AddPtrRaw;
   class Exp_Array;
   class Exp_Assoc;
   class Exp_Binary;
   class Exp_BitAnd;
   class Exp_BitOrI;
   class Exp_BitOrX;
   class Exp_BraBin;
   class Exp_BraTer;
   class Exp_BraUna;
   class Exp_Branch;
   class Exp_CmpEQ;
   class Exp_CmpGE;
   class Exp_CmpGT;
   class Exp_CmpLE;
   class Exp_CmpLT;
   class Exp_CmpNE;
   class Exp_Cnd;
   class Exp_Cst;
   class Exp_Div;
   class Exp_Glyph;
   class Exp_Inv;
   class Exp_LogAnd;
   class Exp_LogOrI;
   class Exp_LogOrX;
   class Exp_Mod;
   class Exp_Mul;
   class Exp_Neg;
   class Exp_Not;
   class Exp_NulAnd;
   class Exp_NulOrI;
   class Exp_ShL;
   class Exp_ShR;
   class Exp_Sub;
   class Exp_Tuple;
   class Exp_Unary;
   class Exp_Union;
   class Function;
   class Glyph;
   class GlyphData;
   class IArchive;
   class Import;
   class OArchive;
   class Object;
   class Program;
   class Space;
   class Statement;
   class StrEnt;
   class Type;
   class TypeAssoc;
   class TypeError;
   class Value;

   typedef AddrBase ArgBase;
   typedef TypeBase ValueBase;

   #define GDCC_Target_AddrList(name) class Arg_##name;
   #include "../Target/AddrList.hpp"

   #define GDCC_IR_TypeList(name) class Type_##name;
   #include "../IR/TypeList.hpp"

   #define GDCC_IR_TypeList(name) class Value_##name;
   #include "../IR/TypeList.hpp"
}

#endif//GDCC__IR__Types_H__
