//-----------------------------------------------------------------------------
//
// Copyright (C) 2013-2018 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// ZDoom ACS glyph preparation.
//
//-----------------------------------------------------------------------------

#include "BC/ZDACS/Info.hpp"

#include "IR/CallType.hpp"
#include "IR/Linkage.hpp"
#include "IR/Program.hpp"


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

namespace GDCC::BC::ZDACS
{
   //
   // Info::preFunc
   //
   void Info::preFunc()
   {
      if(func->defin) switch(func->ctype)
      {
      case IR::CallType::StdCall:
      case IR::CallType::StkCall:
         prog->getGlyphData(func->glyph).type = IR::Type_Funct(func->ctype);
         break;

      default: break;
      }

      if(func->defin && func->allocAut)
         preStmntCall("___GDCC__Plsa", 1, 1);

      InfoBase::preFunc();
   }

   //
   // Info::preObj
   //
   void Info::preObj()
   {
      // TODO: Normalize usage of unused space name to be "", not null.
      if(!obj->space.name)
         obj->space.name = Core::STR_;
   }

   //
   // Info::preStmnt
   //
   void Info::preStmnt()
   {
      switch(stmnt->code)
      {
      case IR::Code::AdXU: preStmnt_AdXU(); break;
      case IR::Code::AddF: preStmnt_AddF(); break;
      case IR::Code::AddI: preStmnt_AddU(); break;
      case IR::Code::AddU: preStmnt_AddU(); break;
      case IR::Code::Bclo: preStmnt_Bclz(true);  break;
      case IR::Code::Bclz: preStmnt_Bclz(false); break;

      case IR::Code::CmpF_EQ: preStmnt_CmpF_EQ(); break;
      case IR::Code::CmpF_GE: preStmnt_CmpF_GE(); break;
      case IR::Code::CmpF_GT: preStmnt_CmpF_GT(); break;
      case IR::Code::CmpF_LE: preStmnt_CmpF_LE(); break;
      case IR::Code::CmpF_LT: preStmnt_CmpF_LT(); break;
      case IR::Code::CmpF_NE: preStmnt_CmpF_NE(); break;

      case IR::Code::CmpI_EQ:
      case IR::Code::CmpU_EQ:
         preStmnt_CmpU_EQ(IR::Code::CmpU_EQ);
         break;

      case IR::Code::CmpI_GE: preStmnt_CmpI_GE(); break;
      case IR::Code::CmpI_GT: preStmnt_CmpI_GT(); break;
      case IR::Code::CmpI_LE: preStmnt_CmpI_LE(); break;
      case IR::Code::CmpI_LT: preStmnt_CmpI_LT(); break;

      case IR::Code::CmpI_NE:
      case IR::Code::CmpU_NE:
         preStmnt_CmpU_EQ(IR::Code::CmpU_NE);
         break;

      case IR::Code::CmpU_GE: preStmnt_CmpU_GE(); break;
      case IR::Code::CmpU_GT: preStmnt_CmpU_GT(); break;
      case IR::Code::CmpU_LE: preStmnt_CmpU_LE(); break;
      case IR::Code::CmpU_LT: preStmnt_CmpU_LT(); break;

      case IR::Code::DiXI: preStmnt_DiXI(); break;
      case IR::Code::DiXU: preStmnt_DiXU(); break;
      case IR::Code::DivF: preStmnt_DivF(); break;
      case IR::Code::DivI: preStmnt_DiXI(); break;
      case IR::Code::DivK: preStmnt_DivX(IR::Code::DiXU); break;
      case IR::Code::DivU: preStmnt_DiXU(); break;
      case IR::Code::DivX: preStmnt_DivX(IR::Code::DiXI); break;

      case IR::Code::LAnd:
      case IR::Code::LOrI:
         if(auto n = getStmntSize(); n > 1)
            preStmntCall(1, n * 2);
         break;

      case IR::Code::ModI: preStmnt_DiXI(); break;
      case IR::Code::ModU: preStmnt_DiXU(); break;
      case IR::Code::MuXU: preStmnt_MuXU(); break;
      case IR::Code::MulF: preStmnt_MulF(); break;
      case IR::Code::MulI: preStmnt_MulU(); break;
      case IR::Code::MulK: preStmnt_MulK(); break;
      case IR::Code::MulU: preStmnt_MulU(); break;
      case IR::Code::MulX: preStmnt_MulX(); break;
      case IR::Code::Retn: preStmnt_Retn(); break;
      case IR::Code::ShLF: preStmnt_ShLF(); break;
      case IR::Code::ShLU: preStmnt_ShLU(); break;
      case IR::Code::ShRF: preStmnt_ShLF(); break;
      case IR::Code::ShRI: preStmnt_ShLU(); break;
      case IR::Code::ShRU: preStmnt_ShLU(); break;
      case IR::Code::SuXU: preStmnt_SuXU(); break;
      case IR::Code::SubF: preStmnt_SubF(); break;
      case IR::Code::SubI: preStmnt_SubU(); break;
      case IR::Code::SubU: preStmnt_SubU(); break;

      default:
         break;
      }
   }

   //
   // Info::preStmntCall
   //
   void Info::preStmntCall(Core::FastU retrn, Core::FastU param)
   {
      preStmntCall(getCallName(stmnt->code, getStmntSize()), retrn, param);
   }

   //
   // Info::preStmntCall
   //
   void Info::preStmntCall(Core::String name, Core::FastU retrn, Core::FastU param)
   {
      if(!prog->findFunction(name))
      {
         auto &newFn = prog->getFunction(name);

         newFn.ctype = IR::CallType::StkCall;
         newFn.linka = IR::Linkage::ExtC;
         newFn.param = param;
         newFn.retrn = retrn;

         newFn.alloc = true;

         prog->getGlyphData(name).type = IR::Type_Funct(newFn.ctype);

         // Signal iterator to start over.
         throw ResetFunc();
      }
   }

   //
   // Info::preStr
   //
   void Info::preStr()
   {
      prog->getGlyphData(str->glyph).type = IR::Type_StrEn();
   }
}

// EOF

