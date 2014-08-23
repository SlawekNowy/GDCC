//-----------------------------------------------------------------------------
//
// Copyright (C) 2013-2014 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// C fixed-point types.
//
//-----------------------------------------------------------------------------

#include "CC/Type/Fixed.hpp"

#include "IR/Type.hpp"

#include "Platform/Platform.hpp"


//----------------------------------------------------------------------------|
// Static Variables                                                           |
//

// Table: Type_Fixed::getBaseType
static GDCC::AST::Type::CRef const FixedTable_BaseType[6] =
{
   GDCC::CC::GetTypeFixedPrUH(),
   GDCC::CC::GetTypeFixedPrSH(),
   GDCC::CC::GetTypeFixedPrU(),
   GDCC::CC::GetTypeFixedPrS(),
   GDCC::CC::GetTypeFixedPrUL(),
   GDCC::CC::GetTypeFixedPrSL(),
};

// Table: Type_Fract::getBaseType
static GDCC::AST::Type::CRef const FractTable_BaseType[6] =
{
   GDCC::CC::GetTypeFractPrUH(),
   GDCC::CC::GetTypeFractPrSH(),
   GDCC::CC::GetTypeFractPrU(),
   GDCC::CC::GetTypeFractPrS(),
   GDCC::CC::GetTypeFractPrUL(),
   GDCC::CC::GetTypeFractPrSL(),
};

// Table: Type_Integ::getBaseType
static GDCC::AST::Type::CRef const IntegTable_BaseType[10] =
{
   GDCC::CC::GetTypeIntegPrUHH(),
   GDCC::CC::GetTypeIntegPrSHH(),
   GDCC::CC::GetTypeIntegPrUH(),
   GDCC::CC::GetTypeIntegPrSH(),
   GDCC::CC::GetTypeIntegPrU(),
   GDCC::CC::GetTypeIntegPrS(),
   GDCC::CC::GetTypeIntegPrUL(),
   GDCC::CC::GetTypeIntegPrSL(),
   GDCC::CC::GetTypeIntegPrULL(),
   GDCC::CC::GetTypeIntegPrSLL(),
};


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

namespace GDCC
{
   namespace CC
   {
      GDCC_CC_Type_ImplGet(FixedPrS,  Fixed, 1, true,  true )
      GDCC_CC_Type_ImplGet(FixedPrSH, Fixed, 0, true,  true )
      GDCC_CC_Type_ImplGet(FixedPrSL, Fixed, 2, true,  true )
      GDCC_CC_Type_ImplGet(FixedPrU,  Fixed, 1, true,  false)
      GDCC_CC_Type_ImplGet(FixedPrUH, Fixed, 0, true,  false)
      GDCC_CC_Type_ImplGet(FixedPrUL, Fixed, 2, true,  false)
      GDCC_CC_Type_ImplGet(FixedSaS,  Fixed, 1, false, true )
      GDCC_CC_Type_ImplGet(FixedSaSH, Fixed, 0, false, true )
      GDCC_CC_Type_ImplGet(FixedSaSL, Fixed, 2, false, true )
      GDCC_CC_Type_ImplGet(FixedSaU,  Fixed, 1, false, false)
      GDCC_CC_Type_ImplGet(FixedSaUH, Fixed, 0, false, false)
      GDCC_CC_Type_ImplGet(FixedSaUL, Fixed, 2, false, false)

      GDCC_CC_Type_ImplGet(FractPrS,  Fract, 1, true,  true )
      GDCC_CC_Type_ImplGet(FractPrSH, Fract, 0, true,  true )
      GDCC_CC_Type_ImplGet(FractPrSL, Fract, 2, true,  true )
      GDCC_CC_Type_ImplGet(FractPrU,  Fract, 1, true,  false)
      GDCC_CC_Type_ImplGet(FractPrUH, Fract, 0, true,  false)
      GDCC_CC_Type_ImplGet(FractPrUL, Fract, 2, true,  false)
      GDCC_CC_Type_ImplGet(FractSaS,  Fract, 1, false, true )
      GDCC_CC_Type_ImplGet(FractSaSH, Fract, 0, false, true )
      GDCC_CC_Type_ImplGet(FractSaSL, Fract, 2, false, true )
      GDCC_CC_Type_ImplGet(FractSaU,  Fract, 1, false, false)
      GDCC_CC_Type_ImplGet(FractSaUH, Fract, 0, false, false)
      GDCC_CC_Type_ImplGet(FractSaUL, Fract, 2, false, false)

      GDCC_CC_Type_ImplGet(IntegPrS,   Integ, 2, true,  true )
      GDCC_CC_Type_ImplGet(IntegPrSH,  Integ, 1, true,  true )
      GDCC_CC_Type_ImplGet(IntegPrSHH, Integ, 0, true,  true )
      GDCC_CC_Type_ImplGet(IntegPrSL,  Integ, 3, true,  true )
      GDCC_CC_Type_ImplGet(IntegPrSLL, Integ, 4, true,  true )
      GDCC_CC_Type_ImplGet(IntegPrU,   Integ, 2, true,  false)
      GDCC_CC_Type_ImplGet(IntegPrUH,  Integ, 1, true,  false)
      GDCC_CC_Type_ImplGet(IntegPrUHH, Integ, 0, true,  false)
      GDCC_CC_Type_ImplGet(IntegPrUL,  Integ, 3, true,  false)
      GDCC_CC_Type_ImplGet(IntegPrULL, Integ, 4, true,  false)

      //
      // Type_FixedBase constructor
      //
      Type_FixedBase::Type_FixedBase(unsigned size_, bool prim_, bool sign_) :
         size{size_},
         prim{prim_},
         satu{!prim_},
         sign{sign_},
         unsi{!sign_}
      {
      }

      //
      // Type_FixedBase::getIRType
      //
      IR::Type Type_FixedBase::getIRType() const
      {
         return IR::Type_Fixed(getSizeBitsI(), getSizeBitsF(), getSizeBitsS(),
            isTypeSaturate());
      }

      //
      // Type_Fixed constructor
      //
      Type_Fixed::Type_Fixed(unsigned size_, bool prim_, bool sign_) :
         Super{size_, prim_, sign_}
      {
      }

      //
      // Type_Fixed::getBaseType
      //
      AST::Type::CRef Type_Fixed::getBaseType() const
      {
         if(prim) throw AST::TypeError();
         return FixedTable_BaseType[(size << 1) | sign];
      }

      //
      // Type_Fixed::getRankC
      //
      AST::TypeRankC Type_Fixed::getRankC() const
      {
         switch(size)
         {
         case 0: return AST::TypeRankC::FixedH;
         case 1: return AST::TypeRankC::Fixed;
         case 2: return AST::TypeRankC::FixedL;
         }

         return AST::TypeRankC::None;
      }

      //
      // Type_Fixed::getSignType
      //
      AST::Type::CRef Type_Fixed::getSignType() const
      {
         return FixedTable_BaseType[(size << 1) | 1];
      }

      //
      // Type_Fixed::getSizeAlign
      //
      Core::FastU Type_Fixed::getSizeAlign() const
      {
         switch(Platform::TargetCur)
         {
         case Platform::Target::MageCraft: return 4;
         default:                          return 1;
         }
      }

      //
      // Type_Fixed::getSizeBitsF
      //
      Core::FastU Type_Fixed::getSizeBitsF() const
      {
         switch(Platform::TargetCur)
         {
         case Platform::Target::MageCraft: return (8 << size) - 1;
         default:                          return size > 1 ? 32 : 16;
         }
      }

      //
      // Type_Fixed::getSizeBitsI
      //
      Core::FastU Type_Fixed::getSizeBitsI() const
      {
         switch(Platform::TargetCur)
         {
         case Platform::Target::MageCraft: return (24 << size) + unsi;
         default:                          return (size > 1 ? 31 : 15) + unsi;
         }
      }

      //
      // Type_Fixed::getSizeBytes
      //
      Core::FastU Type_Fixed::getSizeBytes() const
      {
         switch(Platform::TargetCur)
         {
         case Platform::Target::MageCraft: return 4 << size;
         default:                          return size > 1 ? 2 : 1;
         }
      }

      //
      // Type_Fixed::getSizePoint
      //
      Core::FastU Type_Fixed::getSizePoint() const
      {
         switch(Platform::TargetCur)
         {
         case Platform::Target::MageCraft: return 1 << size;
         default:                          return size > 1 ? 2 : 1;
         }
      }

      //
      // Type_Fixed::getSizeShift
      //
      Core::FastU Type_Fixed::getSizeShift() const
      {
         switch(Platform::TargetCur)
         {
         case Platform::Target::MageCraft: return 4;
         default:                          return 1;
         }
      }

      //
      // Type_Fixed::getSizeWords
      //
      Core::FastU Type_Fixed::getSizeWords() const
      {
         switch(Platform::TargetCur)
         {
         case Platform::Target::MageCraft: return 1 << size;
         default:                          return size > 1 ? 2 : 1;
         }
      }

      //
      // Type_Fixed::getUnsiType
      //
      AST::Type::CRef Type_Fixed::getUnsiType() const
      {
         return FixedTable_BaseType[(size << 1) | 0];
      }

      //
      // Type_Fract constructor
      //
      Type_Fract::Type_Fract(unsigned size_, bool prim_, bool sign_) :
         Super{size_, prim_, sign_}
      {
      }

      //
      // Type_Fract::getBaseType
      //
      AST::Type::CRef Type_Fract::getBaseType() const
      {
         if(prim) throw AST::TypeError();
         return FractTable_BaseType[(size << 1) | sign];
      }

      //
      // Type_Fract::getRankC
      //
      AST::TypeRankC Type_Fract::getRankC() const
      {
         switch(size)
         {
         case 0: return AST::TypeRankC::FractH;
         case 1: return AST::TypeRankC::Fract;
         case 2: return AST::TypeRankC::FractL;
         }

         return AST::TypeRankC::None;
      }

      //
      // Type_Fract::getSignType
      //
      AST::Type::CRef Type_Fract::getSignType() const
      {
         return FractTable_BaseType[(size << 1) | 1];
      }

      //
      // Type_Fract::getSizeAlign
      //
      Core::FastU Type_Fract::getSizeAlign() const
      {
         switch(Platform::TargetCur)
         {
         case Platform::Target::MageCraft: return 1 << size;
         default:                          return 1;
         }
      }

      //
      // Type_Fract::getSizeBitsF
      //
      Core::FastU Type_Fract::getSizeBitsF() const
      {
         return (8 << size) - sign;
      }

      //
      // Type_Fract::getSizeBytes
      //
      Core::FastU Type_Fract::getSizeBytes() const
      {
         switch(Platform::TargetCur)
         {
         case Platform::Target::MageCraft: return 1 << size;
         default:                          return 1;
         }
      }

      //
      // Type_Fract::getSizePoint
      //
      Core::FastU Type_Fract::getSizePoint() const
      {
         return 1;
      }

      //
      // Type_Fract::getSizeShift
      //
      Core::FastU Type_Fract::getSizeShift() const
      {
         switch(Platform::TargetCur)
         {
         case Platform::Target::MageCraft: return 1 << size;
         default:                          return 1;
         }
      }

      //
      // Type_Fract::getSizeWords
      //
      Core::FastU Type_Fract::getSizeWords() const
      {
         return 1;
      }

      //
      // Type_Fract::getUnsiType
      //
      AST::Type::CRef Type_Fract::getUnsiType() const
      {
         return FractTable_BaseType[(size << 1) | 0];
      }

      //
      // Type_Integ constructor
      //
      Type_Integ::Type_Integ(unsigned size_, bool prim_, bool sign_) :
         Super{size_, prim_, sign_}
      {
      }

      //
      // Type_Integ::getRankC
      //
      AST::TypeRankC Type_Integ::getRankC() const
      {
         switch(size)
         {
         case 0: return AST::TypeRankC::IntegHH;
         case 1: return AST::TypeRankC::IntegH;
         case 2: return AST::TypeRankC::Integ;
         case 3: return AST::TypeRankC::IntegL;
         case 4: return AST::TypeRankC::IntegLL;
         }

         return AST::TypeRankC::None;
      }

      //
      // Type_Integ::getSignType
      //
      AST::Type::CRef Type_Integ::getSignType() const
      {
         return IntegTable_BaseType[(size << 1) | 1];
      }

      //
      // Type_Integ::getSizeAlign
      //
      Core::FastU Type_Integ::getSizeAlign() const
      {
         switch(Platform::TargetCur)
         {
         case Platform::Target::MageCraft: return size < 2 ? 1 << size : 4;
         default:                          return 1;
         }
      }

      //
      // Type_Integ::getSizeBitsI
      //
      Core::FastU Type_Integ::getSizeBitsI() const
      {
         switch(Platform::TargetCur)
         {
         case Platform::Target::MageCraft: return (8 << size) - sign;
         default:                          return (size > 2 ? 64 : 32) - sign;
         }
      }

      //
      // Type_Integ::getSizeBytes
      //
      Core::FastU Type_Integ::getSizeBytes() const
      {
         switch(Platform::TargetCur)
         {
         case Platform::Target::MageCraft: return 1 << size;
         default:                          return size > 2 ? 2 : 1;
         }
      }

      //
      // Type_Integ::getSizePoint
      //
      Core::FastU Type_Integ::getSizePoint() const
      {
         switch(Platform::TargetCur)
         {
         case Platform::Target::MageCraft: return size > 2 ? 1 << (size - 2) : 1;
         default:                          return size > 2 ? 2 : 1;
         }
      }

      //
      // Type_Integ::getSizeShift
      //
      Core::FastU Type_Integ::getSizeShift() const
      {
         switch(Platform::TargetCur)
         {
         case Platform::Target::MageCraft: return size < 2 ? 1 << size : 4;
         default:                          return 1;
         }
      }

      //
      // Type_Integ::getSizeWords
      //
      Core::FastU Type_Integ::getSizeWords() const
      {
         switch(Platform::TargetCur)
         {
         case Platform::Target::MageCraft: return size > 2 ? 1 << (size - 2) : 1;
         default:                          return size > 2 ? 2 : 1;
         }
      }

      //
      // Type_Integ::getUnsiType
      //
      AST::Type::CRef Type_Integ::getUnsiType() const
      {
         return IntegTable_BaseType[(size << 1) | 0];
      }
   }
}

// EOF

