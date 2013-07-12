//-----------------------------------------------------------------------------
//
// Copyright (C) 2013 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// Intermediary Representation expression: glyph.
//
//-----------------------------------------------------------------------------

#include "ValueGlyph.hpp"


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

namespace GDCC
{
   namespace IR
   {
      //
      // Exp_ValueGlyph::v_getValue
      //
      Value Exp_ValueGlyph::v_getValue() const
      {
         if(auto value = glyph.getData().value)
            return value->getValue();
         else
            return Value();
      }

      //
      // ExpCreate_ValueGlyph
      //
      Exp::Ref ExpCreate_ValueGlyph(Glyph glyph, Origin pos)
      {
         return static_cast<Exp::Ref>(new Exp_ValueGlyph(glyph, pos));
      }
   }
}

// EOF

