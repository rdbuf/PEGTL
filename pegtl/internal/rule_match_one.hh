// Copyright (c) 2014-2015 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef PEGTL_INTERNAL_RULE_MATCH_ONE_HH
#define PEGTL_INTERNAL_RULE_MATCH_ONE_HH

#include <type_traits>

#include "../nothing.hh"

#include "../apply_mode.hh"
#include "../error_mode.hh"

#include "utility.hh"

#include "rule_match_two.hh"

namespace pegtl
{
   namespace internal
   {
      template< typename Rule, apply_mode A, error_mode E, template< typename ... > class Action, template< typename ... > class Control, typename Input, typename ... States >
      bool rule_match_one( Input & in, States && ... st )
      {
         return rule_match_two< Rule, A, E, Action, Control, std::is_base_of< nothing< Rule >, Action< Rule > >::value ? merge( A, apply_here::NOTHING ) : merge( A, apply_here::ACTION ) >::template match( in, st ... );
      }

   } // internal

} // pegtl

#endif