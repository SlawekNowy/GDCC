//-----------------------------------------------------------------------------
//
// Copyright (C) 2014-2019 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// ZDoom ACS initializer generator.
//
//-----------------------------------------------------------------------------

#include "BC/ZDACS/Info.hpp"

#include "Core/Option.hpp"

#include "IR/Program.hpp"

#include "Target/Info.hpp"

#include <sstream>


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

namespace GDCC::BC::ZDACS
{
   //
   // Info::genIniti
   //
   void Info::genIniti()
   {
      bool isGblArr = isInitiGblArr();
      bool isHubArr = isInitiHubArr();

      if(!isGblArr && !isHubArr)
         return;

      ++numChunkSPTR;

      if(Target::EngineCur == Target::Engine::Zandronum)
         ++numChunkSPTR, ++numChunkSFLG;

      // Extra information for named init script.
      if(InitScriptNamed)
      {
         InitScriptNumber = ~numChunkSNAM;

         ++numChunkSNAM;

         if(Target::EngineCur == Target::Engine::Zandronum)
            ++numChunkSNAM, --InitScriptNumber.data();

         // If no name set, generate one.
         if(!InitScriptName)
         {
            std::ostringstream oss;
            if(char const *s = Core::GetOptionOutput())
               oss << s;
            oss << "$init";

            auto const &s = oss.str();
            InitScriptName = {s.data(), s.size()};
         }
      }

      // Save index for initializer start.
      codeInit = CodeBase() + numChunkCODE;

      if(isInitScriptEvent())
      {
         // Check event type.
         // Push_LocReg Jcnd_Lit Drop_Nul Rscr
         numChunkCODE += 28;
      }

      // Initialize world arrays.
      if(isHubArr)
      {
         // Check if already initialized.
         // push_lit push_arr cjmp_tru
         numChunkCODE += 24;

         // Count instructions needed for initializers.
         for(auto &itr : prog->rangeSpaceHubArs()) genInitiSpace(itr);
      }

      // Initialize global arrays.
      if(isGblArr)
      {
         // Check if already initialized.
         // push_lit push_arr cjmp_tru
         numChunkCODE += 24;

         // Count instructions needed for initializers.
         for(auto &itr : prog->rangeSpaceGblArs()) genInitiSpace(itr);
         genInitiSpace(prog->getSpaceSta());
      }

      // Delay before setting initialized flag(s).
      if(InitDelay)
      {
         // wait_lit
         numChunkCODE += 8;
      }

      if(isHubArr)
      {
         // Mark as initialized.
         // push_lit push_lit drop_arr
         numChunkCODE += 24;
      }

      if(isGblArr)
      {
         // Mark as initialized.
         // push_lit push_lit drop_arr
         numChunkCODE += 24;
      }

      // Save index for initializer end.
      codeInitEnd = CodeBase() + numChunkCODE;

      // Terminate script.
      // term
      numChunkCODE += 4;
   }

   //
   // Info::genInitiSpace
   //
   void Info::genInitiSpace(IR::Space &space_)
   {
      auto const &ini = init[&space_];

      // Count instructions needed for initializers.
      for(auto const &val : ini.vals) switch(val.second.tag)
      {
      case InitTag::Empty: break;

      case InitTag::Fixed:
         if(val.second.val)
            numChunkCODE += 24;
         break;

      case InitTag::Funct: numChunkCODE += 24; break;
      case InitTag::StrEn: numChunkCODE += 28; break;
      }
   }
}

// EOF

