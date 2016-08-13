//-----------------------------------------------------------------------------
//
// Copyright (C) 2013-2016 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// Source Representation generalized attribute handling.
//
//-----------------------------------------------------------------------------

#ifndef GDCC__SR__Attribute_H__
#define GDCC__SR__Attribute_H__

#include "../Core/Array.hpp"
#include "../Core/Counter.hpp"
#include "../Core/Number.hpp"
#include "../Core/Origin.hpp"

#include "../IR/Addr.hpp"


//----------------------------------------------------------------------------|
// Types                                                                      |
//

namespace GDCC
{
   namespace Core
   {
      class Token;
   }

   namespace IR
   {
      enum class CallType;
      enum class Linkage;
      enum class ScriptType;

      class Exp;
   }

   namespace SR
   {
      class Type;

      //
      // Attribute
      //
      class Attribute
      {
      public:
         Attribute();
         Attribute(Attribute const &attr);
         Attribute(Attribute &&attr);
         ~Attribute();

         void setName(Core::Token const &tok);

         Core::CounterPtr<IR::Exp const> addrI;
         Core::CounterPtr<IR::Exp const> addrL;
         Core::String                    addrS;
         Core::CounterPtr<IR::Exp const> allocAut;
         IR::CallType                    callt;
         IR::Linkage                     linka;
         Core::String                    name;
         Core::Origin                    namePos;
         Core::Array<Attribute>          param;
         Core::FastU                     paramOpt;
         IR::AddrSpace                   space;
         IR::ScriptType                  stype;
         Core::CounterPtr<Type const>    type;
         Core::String                    warnUse;

         bool declAuto : 1;

         bool funcInline   : 1;
         bool funcNoParam  : 1;
         bool funcNoReturn : 1;

         bool isTypedef : 1;

         bool objNoInit : 1;

         bool sflagClS : 1;
         bool sflagNet : 1;

         bool storeAuto   : 1;
         bool storeExt    : 1;
         bool storeGbl    : 1;
         bool storeHub    : 1;
         bool storeInt    : 1;
         bool storeReg    : 1;
         bool storeThread : 1;
      };
   }
}

#endif//GDCC__SR__Attribute_H__
