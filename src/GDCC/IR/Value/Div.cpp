//-----------------------------------------------------------------------------
//
// Copyright (C) 2013 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// Intermediary Representation expression value operator /.
//
//-----------------------------------------------------------------------------

#include "Util.hpp"


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

namespace GDCC
{
   namespace IR
   {
      GDCC_IR_ValueBinOpImplEq(/, Fixed);

      //
      // operator Value_Fixed /= Value_Fixed
      //
      Value_Fixed &operator /= (Value_Fixed &l, Value_Fixed const &r)
      {
         GDCC_IR_ValueBinOpBits();

         l.value <<= l.vtype.bitsF;

         if(l.vtype.bitsF > r.vtype.bitsF)
            l.value /= r.value << (l.vtype.bitsF - r.vtype.bitsF);
         else
            l.value /= r.value;

         return l.clamp();
      }
   }
}

// EOF
