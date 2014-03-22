//-----------------------------------------------------------------------------
//
// Copyright (C) 2013-2014 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// Abstract Syntax Tree compound statement.
//
//-----------------------------------------------------------------------------

#include "AST/Statement/Multi.hpp"


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

namespace GDCC
{
   namespace AST
   {
      //
      // Statement_Multi::v_genLabel
      //
      void Statement_Multi::v_genLabel(IR::Block &block) const
      {
         for(auto const &stmnt : stmnts)
            stmnt->genLabel(block);
      }

      //
      // Statement_Multi::v_genStmnt
      //
      void Statement_Multi::v_genStmnt(GenStmntCtx const &ctx) const
      {
         for(auto const &stmnt : stmnts)
            stmnt->genStmnt(ctx);
      }

      //
      // Statement_Multi::v_isBranch
      //
      bool Statement_Multi::v_isBranch() const
      {
         for(auto const &stmnt : stmnts)
            if(stmnt->isBranch()) return true;

         return false;
      }

      //
      // Statement_Multi::v_isEffect
      //
      bool Statement_Multi::v_isEffect() const
      {
         for(auto const &stmnt : stmnts)
            if(stmnt->isEffect()) return true;

         return false;
      }

      //
      // Statement_Multi::v_isLabel
      //
      bool Statement_Multi::v_isLabel() const
      {
         for(auto const &stmnt : stmnts)
            if(stmnt->isLabel()) return true;

         return false;
      }

      //
      // StatementCreate_Multi
      //
      Statement::CRef StatementCreate_Multi(Statement::Labels const &labels,
         Core::Origin pos, Statement::Stmnts const &stmnts)
      {
         return Statement_Multi::Create(labels, pos, stmnts);
      }

      //
      // StatementCreate_Multi
      //
      Statement::CRef StatementCreate_Multi(Statement::Labels const &labels,
         Core::Origin pos, Statement::Stmnts &&stmnts)
      {
         return Statement_Multi::Create(labels, pos, std::move(stmnts));
      }

      //
      // StatementCreate_Multi
      //
      Statement::CRef StatementCreate_Multi(Statement::Labels &&labels,
         Core::Origin pos, Statement::Stmnts const &stmnts)
      {
         return Statement_Multi::Create(std::move(labels), pos, stmnts);
      }

      //
      // StatementCreate_Multi
      //
      Statement::CRef StatementCreate_Multi(Statement::Labels &&labels,
         Core::Origin pos, Statement::Stmnts &&stmnts)
      {
         return Statement_Multi::Create(std::move(labels), pos, std::move(stmnts));
      }

      //
      // StatementCreate_Multi
      //
      Statement::CRef StatementCreate_Multi(Core::Origin pos,
         Statement::Stmnts const &stmnts)
      {
         return Statement_Multi::Create(pos, stmnts);
      }

      //
      // StatementCreate_Multi
      //
      Statement::CRef StatementCreate_Multi(Core::Origin pos,
         Statement::Stmnts &&stmnts)
      {
         return Statement_Multi::Create(pos, std::move(stmnts));
      }
   }
}

// EOF

