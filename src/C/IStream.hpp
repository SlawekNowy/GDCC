//-----------------------------------------------------------------------------
//
// Copyright (C) 2013 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// C input stream.
//
//-----------------------------------------------------------------------------

#ifndef C__IStream_H__
#define C__IStream_H__

#include "GDCC/CommentBuf.hpp"
#include "GDCC/EscapeBuf.hpp"
#include "GDCC/FeatureHold.hpp"
#include "GDCC/OriginBuf.hpp"

#include <istream>


//----------------------------------------------------------------------------|
// Types                                                                      |
//

namespace GDCC
{
   struct Token;
}

namespace C
{
   //
   // IStream
   //
   class IStream : public std::istream
   {
   public:
      IStream(std::streambuf &buf, GDCC::String file) : std::istream{&ebuf},
         obuf{buf, file}, ebuf{obuf} {}

      void disableComments() {rdbuf(&obuf);}

      void enableComments() {rdbuf(&obuf);}

      GDCC::Origin getOrigin() const {return obuf.getOrigin();}

      GDCC::FeatureHold<IStream, &IStream::disableComments, &IStream::enableComments> holdComments()
         {return GDCC::FeatureHold<IStream, &IStream::disableComments, &IStream::enableComments>(*this);}

   protected:
      typedef GDCC::OriginBuf<>                      OBuf;
      typedef GDCC::EscapeBufStrip<'\n', '\\', OBuf> EBuf;

      OBuf obuf;
      EBuf ebuf;
   };
}

//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

namespace C
{
   IStream &operator >> (IStream &in, GDCC::Token &out);
}

#endif//C__IStream_H__

