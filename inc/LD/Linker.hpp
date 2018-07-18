//-----------------------------------------------------------------------------
//
// Copyright (C) 2015-2018 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// Utilities for program linking and output.
//
//-----------------------------------------------------------------------------

#ifndef GDCC__LD__Linker_H__
#define GDCC__LD__Linker_H__

#include "../LD/Types.hpp"

#include <memory>
#include <ostream>


//----------------------------------------------------------------------------|
// Extern Objects                                                             |
//

namespace GDCC::LD
{
   extern bool OutputIR;
}


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

namespace GDCC::LD
{
   std::unique_ptr<BC::Info> GetBytecodeInfo(Platform::Target target,
      Platform::Format format);

   void Link(IR::Program &prog, char const *outName);

   void ProcessIR(IR::Program &prog, BC::Info *info);

   void PutBytecode(std::ostream &out, IR::Program &prog, BC::Info *info);
   void PutIR(std::ostream &out, IR::Program &prog, BC::Info *info);
}

#endif//GDCC__LD__Linker_H__

